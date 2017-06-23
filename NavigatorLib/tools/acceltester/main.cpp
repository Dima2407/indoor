//
// Created by Igor Maschikevich on 6/22/2017.
//

#include "Navigator.h"
#include "rapidjson_min/include/rapidjson/document.h"
#include "rapidjson_min/include/rapidjson/istreamwrapper.h"
#include "myjson.h"
using namespace std;
using Navigator::Math::Position3D;
using Navigator::Accel::StandardAccelNavigator;
using Navigator::Accel::AccelReceivedData;

using namespace rapidjson;
using namespace std;

//double microsecondInSecon(int timestamp);
//Document strimJson (string inFile);

int main() {
    using namespace acceltester;

    myjson myj;

    ofstream tempOut;
    tempOut.open("out_data.dt");
    const Value& temp = myj.strimJson("in_data.json");


    const Value& d_angles = myj.strimJson(temp["angles"].GetString());
    const Value& d_accelerometer = myj.strimJson(temp["accelerometer"].GetString());

    d_angles.IsArray();
    d_accelerometer.IsArray();

    StandardAccelNavigator standardAccelNavigator(nullptr, 0.5, 1.2, 50.0);

    tempOut << "p.x" << "      "  << "p.y" << "     "  << "p.z" << " "  << endl;
    for(int i = 0; i < d_angles.Size(); i++){

        const Value& for_angles = d_angles[i];
        const Value& for_accelerometer = d_accelerometer[i];

        /*
        for_angles["timestamp"].IsInt();
        for_angles["azimuth"].IsDouble();
        for_angles["pitch"].IsDouble();
        for_angles["roll"].IsDouble();

        for_accelerometer["x"].IsDouble();
        for_accelerometer["y"].IsDouble();
        for_accelerometer["z"].IsDouble();
         */

        double timestamp = myj.microsecondInSecon(for_angles["timestamp"].GetInt());
        double azimuth = for_angles["azimuth"].GetDouble();
        double pitch = for_angles["pitch"].GetDouble();
        double roll = for_angles["roll"].GetDouble();
        double aX = for_accelerometer["x"].GetDouble();
        double aY = for_accelerometer["y"].GetDouble();
        double aZ = for_accelerometer["z"].GetDouble();

        AccelReceivedData ard{timestamp, aX, aY, aZ, pitch, azimuth, roll};

        Position3D p = standardAccelNavigator.process(ard);

        tempOut << p.x << " "  << p.y << " "  << p.z << " "  << endl;
    }

    return 0;
}
