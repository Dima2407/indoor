//
// Created by  Oleksiy Grechnyev on 2/6/2017.
//

#include "EventList.h"

#include <iostream>
#include <fstream>
#include <algorithm>

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

        while (in >> e) events.push_back(e);

        in.close();

        return true;
    }

    bool EventList::readJSON(std::string const & fileName) {
        return false;
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
        return false;
    }

    void EventList::sort() {
        std::sort(events.begin(), events.end());
    }
}
