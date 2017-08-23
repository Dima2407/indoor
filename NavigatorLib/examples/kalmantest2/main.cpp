//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <iomanip>
#include <cmath>
#include <vector>

#include "rapidjson_min/include/rapidjson/document.h"
#include "rapidjson_min/include/rapidjson/istreamwrapper.h"

// This includes everything you need
#include "Navigator.h"

// There are a few namespaces in the librrary
using namespace std;
using namespace Navigator::Beacons;
using namespace Navigator::Beacons::Factory;
using namespace Navigator::Math::Trilat;
using namespace Navigator::Math::Kalman;
using namespace Navigator::Mesh;
using Navigator::Math::Position3D;

using namespace rapidjson;

static void fatal(const string &s) {
    cerr << s << endl;
    exit(1);
}

static vector<Beacon> parseMap() {
    vector<Beacon> beacons;

    ifstream in("in/map.json");
    if (!in)
        fatal("Can't open in/map.json");
    IStreamWrapper isw(in);
    Document document;
    document.ParseStream(isw);
    in.close();

    Value &bArray = document["beacons"];
    if (!bArray.IsArray())
        fatal("JSON parse: beacons not an array");

    beacons.reserve(10);
    for (const auto &v : bArray.GetArray()) {
        BeaconUID uid(v["uuid"].GetString(), v["major"].GetInt(), v["minor"].GetInt());
        Position3D pos(v["x"].GetDouble(), v["y"].GetDouble(), v["z"].GetDouble());
        beacons.emplace_back(uid, v["txpower"].GetDouble(), v["damp"].GetDouble(), pos);
    }

    return beacons;
}

//===========================================================
static bool parseBRD(istream &in, BeaconReceivedData &brd, unsigned long long &ts0, unsigned long long &tsull) {
    string line;
    getline(in, line);
    if (!in) {
        return false;
    }

    stringstream sLine(line);
//    cout << "line = " << line << endl;
    string tmp;
    getline(sLine, tmp, ',');
    tsull = stoull(tmp);
    getline(sLine, tmp, ',');
    string uuid = tmp;
    getline(sLine, tmp, ',');
    int major = stoi(tmp);
    getline(sLine, tmp, ',');
    int minor = stoi(tmp);
    getline(sLine, tmp, ',');
    getline(sLine, tmp);
    double rssi = stod(tmp);

    BeaconUID uid(uuid, major, minor);

    if (0 == ts0) {
        ts0 = tsull;
    }
    double ts = 1.0 * (tsull - ts0) / 1000;

    brd = BeaconReceivedData(ts, uid, rssi);

    return true;
}
//===========================================================

int main() {

    KalmanBeaconNavigatorConfig config;
    KalmanConfig filterConfig;


    KalmanBeaconNavigator navigator(nullptr, config, filterConfig);

    vector<Beacon> beacons = parseMap();

//    for (const auto & b : beacons)
//        cout << b.getUid() << endl;

    navigator.addBeacons(beacons);

    vector<shared_ptr<BeaconProcessor>> processors;
    for (const Beacon &b : beacons) {
        processors.push_back(navigator.findProcessorByUid(b.getUid()));
    }

    ofstream beFile("beacons.out");
    for (int i = 0; i < processors.size(); ++i) {
        beFile << setw(3) << i + 1 << "  " << processors[i]->getBeacon().getUid() << endl;
    }
    beFile.close();

    ifstream in("in/input.csv");
    if (!in)
        fatal("Can't open in/input.csv");
    vector<BeaconReceivedData> brds;
    unsigned long long ts0 = 0;
    unsigned long long tsull = 0;
    unsigned long long tsull0 = 0;
    double lastTs = nan("");
    FILE *fileFiltered = fopen("filtered.out", "w");
    FILE *fileRaw = fopen("raw.out", "w");
    FILE *fileS3 = fopen("strongest3.out", "w");
    FILE *fileSR = fopen("strongestRssi.out", "w");
    FILE *fileTrilat = fopen("trilat.out", "w");
    FILE *filePos = fopen("pos.out", "w");
    BeaconReceivedData brd;
    bool eof = false;
    for (;;) {
        if (!parseBRD(in, brd, ts0, tsull)) // End Of File
            eof = true;

        //    cout << brd.timestamp << " " << brd.rssi << " " << brd.uid << endl;
        if (isnan(lastTs))
            lastTs = brd.timestamp;

        if (fabs(brd.timestamp - lastTs) < 2.0e-3 && !eof) {
            brds.push_back(brd);
        } else {

            // Print raw data
            {
                vector<double> raw(beacons.size(), 0.0);

                // Write raw RSSIs
                fprintf(fileRaw, "%13.8lf ", brds[0].timestamp);
                for (const auto &b:brds) {
                    for (int i = 0; i < beacons.size(); ++i)
                        if (b.uid == beacons[i].getUid())
                            raw[i] = b.rssi;
                }

                for (int i = 0; i < beacons.size(); ++i)
                    fprintf(fileRaw, "%13.8lf ", raw[i]);

                fprintf(fileRaw, "\n");
            }

            // Process the whole bunch of data in a single process() call
            Position3D outPos = navigator.process(brds);
            // Log the output pos
            fprintf(filePos, "%13.8lf ", brds[0].timestamp);
            fprintf(filePos, "%13.8lf %13.8lf", outPos.x, outPos.y);
            fprintf(filePos, "\n");


            // Write trilat reecords
            const auto & tRec = navigator.getTrilatRecords();
            fprintf(fileTrilat, "%13.8lf ", brds[0].timestamp);
            for (const auto & r : tRec)
                fprintf(fileTrilat, "%13.8lf ", r.dist);
            fprintf(fileTrilat, "\n");

            // Write strongest 3
            vector<BeaconUID> strong3 = navigator.getLastTrilatUids();
            fprintf(fileS3, "%13.8lf ", brds[0].timestamp);
            fprintf(fileSR, "%13.8lf ", brds[0].timestamp);
            for (const BeaconUID &u: strong3) {
                // Log beacon numbers
                for (int i = 0; i < processors.size(); ++i)
                    if (processors[i]->getBeacon().getUid() == u)
                            fprintf(fileS3, "%2d ", i+1);
                // Log RSSIs
                const auto proc = navigator.findProcessorByUid(u);
                fprintf(fileSR, "%13.8lf ", proc->getLastRssi());

            }
//            s3File << endl;
            fprintf(fileS3, "\n");
            fprintf(fileSR, "\n");



            // Write all filtered RSSIs
            fprintf(fileFiltered, "%13.8lf ", brds[0].timestamp);
            for (const auto &p : processors) {
                double rssi;
                if (p->isActive())
                    rssi = p->getLastRssi();
                else
                    rssi = 0;
                fprintf(fileFiltered, "%13.8lf ", rssi);
            }
            fprintf(fileFiltered, "\n");
            if (eof)
                break;

            brds.clear();
            brds.push_back(brd);
        }

        lastTs = brd.timestamp;
        tsull0 = tsull;


    }
    fclose(fileFiltered);
    fclose(fileRaw);
    fclose(fileS3);
    fclose(fileSR);
    fclose(fileTrilat);
    fclose(filePos);

    return 0;
}
