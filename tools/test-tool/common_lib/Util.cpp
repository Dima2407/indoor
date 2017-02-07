//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#include "Util.h"

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
}