//
// Created by Oleksiy Grechnyev on 2/6/2017.
//

#ifndef TESTTOOL_EVENTLIST_H
#define TESTTOOL_EVENTLIST_H

#include <vector>
#include "Event.h"

namespace tester {
    /** \brief A vector of tester::Event with file IO routines (DAT, JSON)
     *
     * No need for constructor, the default one is fine
     */
    class EventList {
    public:

        /// Read events from a DAT file (true if successful)
        bool readDAT(std::string const & fileName);

        /// Read events from a JSON file (true if successful)
        bool readJSON(std::string const &  fileName);

        /// Read events from a JSON or DAT file (true if successful)
        bool readAuto(std::string const &  fileName);

        /// Write events to a DAT file (true if successful)
        bool writeDAT(std::string const &  fileName);

        /// Write events to a JSON file (true if successful)
        bool writeJSON(std::string const &  fileName);

        /// Write events to a DAT or JSON file (true if successful)
        bool writeAuto(std::string const &  fileName);

        /// Getter
        const std::vector<Event> &getEvents() const {
            return events;
        }

        /// Non-const getter
        std::vector<Event> &getEvents() {
            return events;
        }

        /// Clear the list
        void clear(){
            events.clear();
        }

        /// Sort the list by timestamp
        void sort();

    private:
        /// The list of events
        std::vector<Event> events;
    };
}


#endif //TESTTOOL_EVENTLIST_H
