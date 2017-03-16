//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//


#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Navigator {
    namespace Beacons {
        /** @brief Beacon UID. Can be compared.
         *
         *
         */
        class BeaconUID : public std::vector<std::uint8_t> {
        public:
            /// Constructor from a string
            BeaconUID(std::string s)
                    : vector(s.begin(), s.end()) {}

            /// Constructor from a string + major + minor
            BeaconUID(std::string s, int major, int minor)
                    : vector(s.begin(), s.end()) {
                push_back(major & 0x00FF);
                push_back((major & 0xFF00) >> 8);
                push_back(minor & 0x00FF);
                push_back((minor & 0xFF00) >> 8);
            }
        };
    }
}

namespace std {
    /// Hash function for BeaconUID
    template<>
    struct hash<Navigator::Beacons::BeaconUID> {
        std::size_t operator()(const Navigator::Beacons::BeaconUID &uid) const {
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



