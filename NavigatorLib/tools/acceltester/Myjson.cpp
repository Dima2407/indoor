//
// Created by Igor Maschikevich on 6/20/2017.
//
#include <iostream>
#include <string>
#include <rapidjson/document.h>

#include "Myjson.h"
#include "Vec3.h"

namespace ecceltester{
namespace Myjson {

//bool readVec3(rapidjson::Value const & obj, const char *name, Vec3 &vec3) {
//    using namespace std;
//    using namespace rapidjson;

//    if (!obj.IsObject()) {
//        cerr << "ERROR in readVec3 : obj must be Object. " << endl;
//        return false;
//    }

// Get property iterator by name
//    auto propIt = obj.FindMember(name);
//    if (propIt == obj.MemberEnd()) {
//        cerr << "ERROR in readVec3 : Cannot find Vec3 property :'" << name << "'." << endl;
//        return false;
//    }
//    Value const & v = propIt->value; // Found the value

//    / V must be an array of size 3
//   if ( !v.IsArray() || (v.Size()!=3) || !v[0].IsNumber() || !v[1].IsNumber() || !v[2].IsNumber()) {
//        cerr << "ERROR in readVec3 : Property '" << name << "' must be an arrray of 3 doubles." << endl;
//        return false;
//    }

// Parse X, Y, Z
//    vec3.x = v[0].GetDouble();
//    vec3.y = v[1].GetDouble();
//    vec3.z = v[2].GetDouble();

//    return true; // Success
//}


bool readString(rapidjson::Value const &obj, const char *name, std::string &str) {
    using namespace std;
    using namespace rapidjson;

    if (!obj.IsObject()) {
        cerr << "ERROR in readString : obj must be Object. " << endl;
        return false;
    }

    // Get property iterator by name
    auto propIt = obj.FindMember(name);
    if (propIt == obj.MemberEnd()) {
        cerr << "ERROR in readString : Cannot find String property :'" << name << "'." << endl;
        return false;
    }
    Value const & v = propIt->value; // Found the value

    // v must be a string
    if (! v.IsString()) {
        cerr << "ERROR in readString : Property '" << name << "' must be a string." << endl;
        return false;
    }

    str = v.GetString();

    return true; // Success
}

}
}


///////////////////////////////////////////////////////////////////////////
