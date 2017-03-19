//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#ifndef TESTTOOL_UTIL_H
#define TESTTOOL_UTIL_H

#include <string>

namespace tester {
    /// Utility class with misc static routines
    class Util {
    public:
        /// Convert string to lower case (string altered, no copies made)
        static void toLowerCase(std::string & s);

        /// Make a lowercase copy of a string
        static std::string lowerCase(std::string s);

        /// Check if fileName has extension .ext, ignoring case
        static bool hasExt(std::string const & fileName, std::string const & ext);


        /** \brief Parse a MAC address string, e.g. "01:17:C5:59:B0:C0" as long long
         *
         * @param[in]  mac         MAC as string
         * @param[out] result      MAC as long long
         * @return                 true is success
         */
        static bool parseMAC(std::string const &mac, long long & result);
    };

}


#endif //TESTTOOL_UTIL_H
