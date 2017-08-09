//
// Created by  Oleksiy Grechnyev on 8/7/2017.
//
#include <vector>
#include <functional>
#include <random>
#include <ctime>
#include "cmath"

#include "Navigator/Math/Position3D.h"

#include "./ParticleFilterConfig.h"

#pragma once

namespace Navigator {
    namespace Particles {
        class ParticleFilter {
        public:  // ========== Methods
            /// Constructor
            ParticleFilter(const ParticleFilterConfig &config = ParticleFilterConfig()) : config(config) {
                // Pre-allocate vectors
                particles = std::vector<Math::Position2D>(config.numPart);
                weights = std::vector<double>(config.numPart);
            }

            /// Initialize with a position (seed particles)
            void initialize(const Math::Position2D &pos);


            /**  @brief  Process one step of the particle filter aglorithm
             *
             * @param delta         The control movement (from Sensors)
             * @param z             The measured coordinate (from BLE)
             * @param allowMove     Callback, returns true if move from p1 to p2 is allowed
             * @return              The measured position
             */
            Math::Position2D & process(const Math::Position2D & delta,
                                       const Math::Position2D & z,
                                       const std::function<bool(const Math::Position2D &,
                                                                const Math::Position2D &)> & allowMove
                                       );

            const Math::Position2D &getLastPosition() const {
                return lastPosition;
            }

        private: //======= Methods ==============

            /// Prediction step of the algorithm, move particles
            void moveParticles(const Math::Position2D & delta);

            /// Correction step of the algorithm : calculate weights
            void calcWeights(const Math::Position2D & z,
                         const std::function<bool(const Math::Position2D &,
                                                  const Math::Position2D &)> & allowMove);

            /// Resample particles
            void resample();

            /// Calculate lastPosition
            void calcLastPosition();

        private: //======= Random generators
            /// Generate uniform random number between x1 and x2
            double randRange(double x1, double x2){
                return std::uniform_real_distribution<double>(x1, x2)(randomEngine);
            }

            /// Generate normal (Gaussian) distributed number with average 0
            double randNorm(double sigma){
                return std::normal_distribution<double>(0.0, sigma)(randomEngine);
            }


        private: //======= Fields =====
            /// Config
            ParticleFilterConfig config;

            /// Particles
            std::vector<Math::Position2D> particles;

            /// Weights
            std::vector<double> weights;

            /// Last position
            Math::Position2D lastPosition;

            // Seeded random engine
            std::mt19937 randomEngine = std::mt19937(time(nullptr));
        };
    }
}

