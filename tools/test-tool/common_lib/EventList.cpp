//
// Created by  Oleksiy Grechnyev on 2/6/2017.
//

#include "EventList.h"
#include "myjson.h"
#include "Util.h"

#include <iostream>
#include <fstream>
#include <algorithm>


#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace tester {

    bool EventList::readDAT(std::string const & fileName) {
        using namespace std;

        cout << endl << "Reading events from DAT file : " << fileName << endl << endl;

        ifstream in(fileName);

        if (!in) {
            cerr << "ERROR: Cannot open input file : " << fileName << endl;
            return false;
        }

        Event e;

        events.clear();
        while (in >> e) events.push_back(e);

        in.close();

        return true;
    }

    bool EventList::readJSON(std::string const & fileName) {

        using namespace std;
        using namespace rapidjson;

        ifstream in(fileName);

        if (!in) {
            cerr << "ERROR: Cannot open input file : " << fileName << endl;
            return false;
        }

        cout << endl << "Reading events from JSON file : " << fileName << endl << endl;

        // Parse JSON from input file
        // Note: accoding to rapidjson docs it's faster to use C FILE
        // instead of C++ ifstream/ofstream
        // But for small JSON I don't care
        IStreamWrapper isw(in);
        Document d; // DOM document
        d.ParseStream(isw);
        in.close(); // Close stream in, work with Document d

        events.clear();

        // Documnet must be an array (of beacons)
        if (!d.IsArray()) {
            cerr << "ERROR in " << fileName << ": JSON document must be Array. " << endl;
            return false;
        }

        // Loop over all beacons in the array C++11 style
        // ba = beacon Array DOM object
        for (auto &ba: d.GetArray()) {
            if (!ba.IsArray()) {
                cerr << "ERROR in " << fileName << ": beacon entry must be Array. " << endl;
                return false;
            }

            // Loop over all events for each beacon
            for (auto &e : ba.GetArray()) {
                Event event; // A new event to add

                // Read "hash" OR "MACaddress"
                if (!myjson::readLL(e, "hash", event.hash, false)) {

                    // If no "hash", try "MACaddress"
                    string mac;
                    if (!myjson::readString(e, "MACaddress", mac)) return false;

                    if (!Util::parseMAC(mac, event.hash)) return false;
                }

                // Read other data
                if (!myjson::readDouble(e, "TXpower", event.txPower)) return false;
                if (!myjson::readDouble(e, "RSSI", event.rssi)) return false;
                if (!myjson::readLL(e, "TimeStamp", event.timestamp)) return false;

                events.push_back(event);
            }
        }

        return true;
    }

    bool EventList::writeDAT(std::string const & fileName) {
        using namespace std;

        cout << endl << "Writing events to DAT file : " << fileName << endl << endl;

        // Write events to the file
        ofstream out(fileName);

        if (!out) {
            cerr << "ERROR: Cannot create/replace output file : " << fileName << endl;
            return false;
        }

        for (Event const & event: events){
            out << fixed << event << endl;
        }

        if (!out) {
            cerr << "ERROR: Cannot write output file : " << fileName << endl;
            return false;
        }

        out.close();

        return true;
    }

    bool EventList::writeJSON(std::string const & fileName) {
        using namespace std;
        using namespace rapidjson;


        cout << endl << "Writing events to JSON file : " << fileName << endl << endl;


        // In this routine we break up all events by hascode, we'll need a list of hash codes for that
        vector<long long> hashcodes;

        for (Event const & event: events){
            if (std::find(hashcodes.begin(), hashcodes.end(), event.hash) == hashcodes.end()) {
                // Not found: add a new hash
                hashcodes.push_back(event.hash);
            }
        }


        Document d;

        Document::AllocatorType& allocator = d.GetAllocator();

        d.SetArray();

        // Loop over all hashcodes: forms outer array
        for (long long hcode: hashcodes) {
            Value hashArray; // Array of events with a given hashcode
            hashArray.SetArray();

            // Loop over all events with hash=hcode, inner array
            for (Event const & event: events) {
                // Only addd events with hash = hcode to the inner array
                if (event.hash == hcode) {
                    Value eventObj;
                    eventObj.SetObject();

                    // Addd data
                    Value hashVal;
                    hashVal.SetInt64(event.hash);
                    eventObj.AddMember("hash", hashVal, allocator);

                    Value TXpowerVal;
                    TXpowerVal.SetDouble(event.txPower);
                    eventObj.AddMember("TXpower", TXpowerVal, allocator);

                    Value RSSIVal;
                    RSSIVal.SetDouble(event.rssi);
                    eventObj.AddMember("RSSI", RSSIVal, allocator);

                    Value timestampVal;
                    timestampVal.SetInt64(event.timestamp);
                    eventObj.AddMember("TimeStamp", timestampVal, allocator);

                    hashArray.PushBack(eventObj, allocator);
                }
            }

            // Add inner arrray for a given hcode to the document (outer array)
            d.PushBack(hashArray, allocator);
        }

        // Write the result
        ofstream ofs(fileName);
        if (!ofs) return false;

        OStreamWrapper osw(ofs);
        Writer<OStreamWrapper> writer(osw);
        d.Accept(writer);

        return true;
    }

    void EventList::sort() {
        std::sort(events.begin(), events.end());
    }

    bool EventList::readAuto(std::string const &fileName) {
        using namespace std;

        bool status;

        if (Util::hasExt(fileName, "JSON")) {
            status = readJSON(fileName);
        } else {
            status = readDAT(fileName);
        }
        if (!status) return false;

        sort(); // Always sort after reading, important !

        return true;
    }

    bool EventList::writeAuto(std::string const &fileName) {
        using namespace std;

        if (Util::hasExt(fileName, "JSON")) {
            return writeJSON(fileName);
        } else {
            return writeDAT(fileName);
        }
    }
}
