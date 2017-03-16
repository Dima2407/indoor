//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#include "Util.h"

#include <cstdio>

namespace tester {

    bool Util::hasExt(std::string const & fileName, std::string const & ext) {
        using namespace std;

        string dext = "." + lowerCase(ext); // Extension with dot, lowercase, e.g. ".json"
        string lowName = lowerCase(fileName); // Lowercased file name


        unsigned int len = dext.size();
        if (lowName.size() < len) return false; // File name is too short

        return 0 == lowName.compare(lowName.size() - len, len, dext);
    }

    void Util::toLowerCase(std::string &s) {
        for (int i=0; i< s.size(); i++) s[i] = tolower(s[i]);
    }

    std::string Util::lowerCase(std::string s) {
        toLowerCase(s);
        return s;
    }

    bool Util::parseMAC(std::string const &mac, long long &result) {
        // Example of string to parse "01:17:C5:59:B0:C0"

        if (mac.size() != 17) return false;

        const char * mac_c = mac.c_str();

        int i1, i2, i3, i4, i5, i6;
        long long ll=1;

        // Parse it
        if (sscanf(mac_c, "%2x:%2x:%2x:%2x:%2x:%2x", &i1, &i2, &i3, &i4, &i5, &i6) != 6) return false;

        // Form ll
        ll = i1;
        ll = (ll<<8) + i2;
        ll = (ll<<8) + i3;
        ll = (ll<<8) + i4;
        ll = (ll<<8) + i5;
        ll = (ll<<8) + i6;

        result = ll;
        return true;
    }
}