//
// Created by  Oleksiy Grechnyev on 2/6/2017.
//

#include "EventList.h"

#include <iostream>
#include <fstream>
#include <algorithm>

namespace tester {

    bool EventList::readDAT(const char *fileName) {
        using namespace std;

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

    bool EventList::readJSON(const char *fileName) {
        return false;
    }

    bool EventList::writeDAT(const char *fileName) {
        using namespace std;

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

    bool EventList::writeJSON(const char *fileName) {
        return false;
    }

    void EventList::sort() {
        std::sort(events.begin(), events.end());
    }
}
