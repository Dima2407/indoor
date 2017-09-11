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

            /**
             * @brief initialize
             * @param pos
             * @param meshCorrect
             * Initialize with a position (seed particles)
             */
            void initialize(const Math::Position2D &pos,
                            const std::function<Math::Position2D(const Math::Position2D &)> & meshCorrect);


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
                                                                const Math::Position2D &)> & allowMove,
                                       const std::function<Math::Position2D(const Math::Position2D &)> & meshCorrect
                                       );

            const Math::Position2D &getLastPosition() const {
                return lastPosition;
            }

            /**
             * @brief getParticles
             * @return
             */
            const std::vector<Math::Position2D> &getParticles() const {
                return particles;
            }

        private: //======= Methods ==============

            /**
             * @brief moveParticles
             * @param delta
             * calculate new particle coordinates on the base previous coordinates with help
             * use model precess and algorithm IMU
             */
            void moveParticles(const Math::Position2D & delta);

            /**
             * @brief calcWeights
             * @param z
             * @param allowMove
             * @param meshCorrect
             * calculate particle values of weight on the base information about the map and beacons
             */
            void calcWeights(const Math::Position2D & z,
                             const std::function<bool(const Math::Position2D &,
                             const Math::Position2D &)> & allowMove,
                             const std::function<Math::Position2D(const Math::Position2D &)> & meshCorrect);

            /**
             * @brief resample
             * generate a new generation of partices from old generation one witch
             * have the higher weight with help algorithm "The Resempling wheel"
             */
            void resample();

            /**
             * @brief calcLastPosition
             * calculation exit user coordinates
             */
            void calcLastPosition();

        private: //======= Random generators
            /**
             * @brief randRange
             * @param x1
             * @param x2
             * @return
             * Generate uniform random number between x1(inclusive) and x2(inclusive)
             */
            double randRange(double x1, double x2){
                return std::uniform_real_distribution<double>(x1, x2)(randomEngine);
            }

            /**
             * @brief randInt
             * @param border
             * @return
             * Generate uniform random number between 0(inclusive) and border(inclusive)
             */
            int randInt(int border) {
                return std::uniform_int_distribution<int>(0, border)(randomEngine);
            }

            /**
             * @brief randNorm
             * @param sigma
             * @return
             * Generate normal (Gaussian) distributed number with average 0
             */
            double randNorm(double sigma){
                return std::normal_distribution<double>(0.0, sigma)(randomEngine);
            }

            /**
             * @brief gauss
             * @param particle
             * @param z
             * @return
             * Normalized Gaussian distribution for x,y with sigmaX, sigmaY
             */
            double gauss(const Math::Position2D &particle, const Math::Position2D &z);

        private: //======= Fields =====
            /// Config
            ParticleFilterConfig config;

            /// OldLocationParticles
            std::vector<Math::Position2D> oldParticles;

            /// Particles
            std::vector<Math::Position2D> particles;

            /// Weights
            std::vector<double> weights;

            /// Last position
            Math::Position2D lastPosition;

            /// Time-Seeded random engine
            std::mt19937 randomEngine = std::mt19937(time(nullptr));

        public: //======= Fields for simulated random
            /// Simulated random shifts for each particle for initialization (initial seed)
            std::vector<Math::Position2D> simRandPI;

            /// Simulated random shifts for each particle for prediction (particle move)
            std::vector<Math::Position2D> simRandPP;

            /// Simulatted random i (particle chosen at resampling)
            int simRandI;

            /// Simulated betas for N particles
            std::vector<double> simRandBeta;
        };
    }
}
