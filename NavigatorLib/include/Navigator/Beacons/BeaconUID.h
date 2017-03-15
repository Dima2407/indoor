//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//


#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Navi {
    namespace Beacons {
        /** @brief Beacon UID. Can be compared.
         *
         *
         */
        class BeaconUID : public std::vector<std::uint8_t> {
        public:
            /// Constructor from a string
            BeaconUID(std::string s) : vector(s.begin(), s.end()) {}

            /// Constructor from a string + major + minor
            BeaconUID(std::string s, int major, int minor) : vector(s.begin(), s.end()) {
                push_back(major & 0x00FF);
                push_back((major & 0xFF00) >> 8);
                push_back(minor & 0x00FF);
                push_back((minor & 0xFF00) >> 8);
            }

            /// Constructor from a long long hash (for tester, for now)
            BeaconUID(long long h) {
                unsigned long long u = (unsigned long long) h;

                // Push a 8-byte value byte by byte
                for (int i=0; i<8; i++){
                    push_back(0xFF & u);
                    u >>= 8;
                }
            }

        };
    }
}

namespace std {
    /// Hash function for BeaconUID
    template<>
    struct hash<Navi::Beacons::BeaconUID> {
        std::size_t operator()(const Navi::Beacons::BeaconUID &uid) const {
            // A simple hash algorithm
            const int p = 16777619;
            size_t hash = (size_t) 2166136261;

            for (std::uint8_t byte : uid)
                hash = (hash ^ byte) * p;
            
            hash += hash << 13;
            hash ^= hash >> 7;
            hash += hash << 3;
            hash ^= hash >> 17;
            hash += hash << 5;

            return hash;
        }
    };
}



