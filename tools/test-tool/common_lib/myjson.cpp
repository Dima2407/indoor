//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//
#include "myjson.h"
#include <iostream>

namespace tester{
    namespace myjson {

        bool readVec3(rapidjson::Value const & obj, const char *name, Vec3 &vec3) {
            using namespace std;
            using namespace rapidjson;

            if (!obj.IsObject()) {
                cerr << "ERROR in readVec3 : obj must be Object. " << endl;
                return false;
            }

            // Get property iterator by name
            auto propIt = obj.FindMember(name);
            if (propIt == obj.MemberEnd()) {
                cerr << "ERROR in readVec3 : Cannot find Vec3 property :'" << name << "'." << endl;
                return false;
            }
            Value const & v = propIt->value; // Found the value

            /// V must be an array of size 3
            if ( !v.IsArray() || (v.Size()!=3) || !v[0].IsNumber() || !v[1].IsNumber() || !v[2].IsNumber()) {
                cerr << "ERROR in readVec3 : Property '" << name << "' must be an arrray of 3 doubles." << endl;
                return false;
            }

            // Parse X, Y, Z
            vec3.x = v[0].GetDouble();
            vec3.y = v[1].GetDouble();
            vec3.z = v[2].GetDouble();

            return true; // Success
        }

        bool readDouble(rapidjson::Value const &obj, const char *name, double &d) {
            using namespace std;
            using namespace rapidjson;

            if (!obj.IsObject()) {
                cerr << "ERROR in readDouble : obj must be Object. " << endl;
                return false;
            }

            // Get property iterator by name
            auto propIt = obj.FindMember(name);
            if (propIt == obj.MemberEnd()) {
                cerr << "ERROR in readDouble : Cannot find Vec3 property :'" << name << "'." << endl;
                return false;
            }
            Value const & v = propIt->value; // Found the value

            // v must be a number
            if (! v.IsNumber()) {
                cerr << "ERROR in readDouble : Property '" << name << "' must be a number." << endl;
                return false;
            }

            d = v.GetDouble();

            return true; // Success
        }

        bool readLL(rapidjson::Value const &obj, const char *name, long long &ll, bool verbose) {
            using namespace std;
            using namespace rapidjson;

            if (!obj.IsObject()) {
                if (verbose) cerr << "ERROR in readLL : obj must be Object. " << endl;
                return false;
            }

            // Get property iterator by name
            auto propIt = obj.FindMember(name);
            if (propIt == obj.MemberEnd()) {
                if (verbose) cerr << "ERROR in readLL : Cannot find Int64 property :'" << name << "'." << endl;
                return false;
            }
            Value const & v = propIt->value; // Found the value

            // v must be a number
            if (! v.IsInt64()) {
                cerr << "ERROR in readLL : Property '" << name << "' must be an int64 number." << endl;
                return false;
            }

            ll = v.GetInt64();

            return true; // Success
        }

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

        bool readInt(rapidjson::Value const &obj, const char *name, int &i) {
            using namespace std;
            using namespace rapidjson;

            if (!obj.IsObject()) {
                cerr << "ERROR in readInt : obj must be Object. " << endl;
                return false;
            }

            // Get property iterator by name
            auto propIt = obj.FindMember(name);
            if (propIt == obj.MemberEnd()) {
                cerr << "ERROR in readInt : Cannot find Int property :'" << name << "'." << endl;
                return false;
            }
            Value const & v = propIt->value; // Found the value

            // v must be a number
            if (! v.IsInt64()) {
                cerr << "ERROR in readInt : Property '" << name << "' must be an int number." << endl;
                return false;
            }

            i = v.GetInt();

            return true; // Success
        }
    }
}
