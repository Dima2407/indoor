//
// Created by  Oleksiy Grechnyev on 8/7/2017.
//

#include "Navigator/Particles/ParticleFilter.h"

namespace Navigator {
    namespace Particles {

        //===================================================
        void ParticleFilter::initialize(const Math::Position2D &pos) {
            // TODO implement seeding particles, fills vector 'particles' with positions
            // Input : pos
            // Output : particles
        }
        //===================================================

        Math::Position2D &ParticleFilter::process(const Math::Position2D &delta, const Math::Position2D &z,
                                                  const std::function<bool(const Math::Position2D &,
                                                                           const Math::Position2D &)> &allowMove) {

            // This is fine, don't change
            moveParticles(delta);
            calcWeights(z, allowMove);
            resample();
            calcLastPosition();

            return lastPosition;
        }
        //===================================================

        void ParticleFilter::moveParticles(const Math::Position2D &delta) {
            // TODO move particles to the new position using delta (position shift from accel)
            // and adding a random value
            // Input: particles, delta
            // Output : particles
            double sigma = 0.1; /// -- может вынести в .h-файл или в ParticleFilterConfig???

            for (Math::Position2D iter : particles) { ///-- могу ли я использовать auto вместо Math::Position2D ??? --
                iter.x = lastPosition.x + delta.x + randNorm(sigma);
                iter.y = lastPosition.y + delta.y + randNorm(sigma);
            }
        }
        //===================================================

        void ParticleFilter::calcWeights(const Math::Position2D &z, const std::function<bool(const Math::Position2D &,
                                                                                             const Math::Position2D &)> &allowMove) {
            // TODO calculate particle weights using z (BLE position) and allowMove
            // Input: particles, z, allowMove
            // Output : weights
            double sum = 0;
            double sigma = 0.1; /// -- может вынести в .h-файл или в ParticleFilterConfig???

            for (int i = 0; i < particles.size(); ++i) {
                Math::Position2D particle = particles[i];
                if (allowMove(lastPosition, particle)) {
                    double expression = 1 / (sigma * std::sqrt(2 * M_PI));
                    double degreeEforX = -(std::pow(particle.x - z.x, 2) / (2 * sigma * sigma));
                    double degreeEforY = -(std::pow(particle.y - z.y, 2) / (2 * sigma * sigma));
                    double weightX = expression * std::pow(M_E, degreeEforX);
                    double weightY = expression * std::pow(M_E, degreeEforY);
                    weights[i] = weightX * weightY;
                    sum += weights[i];
                } else {
                    weights[i] = 0;
                }
            }

            for (auto iter : weights) {
                iter /= sum;
            }
        }
        //===================================================

        void ParticleFilter::resample() {
            // TODO resample particles
            // Input : particles, weights
            // Output : particles

            // Note: you will need another vector newParticles, and something like (in the end)
            //  particles=newParticles;
            std::vector<double> newParticles;
            double max = 0;

            for (double iter :weights) {
                if (max < iter) {
                    max = iter;
                }
            }

            double randi = randRange(1, weights.size()); /// диапазон от 0 до N ведь так ??? а не от 1
            double betta = randRange(0, 2 * max);

            while (true) {
                for (int i = 0; i < weights.size(); ++i) {
    //                double betta = randRange(0, 2 * max);
                    if (weights[i] > 0) {
                        if (betta > weights[i]) {
                            betta -= weights[i];
                        } else {
                           newParticles.push_back(weights[i]);
                           betta = randRange(0, 2 * max);
                           if (i == weights.size() - 1) {
                               goto out;
                           }
                        }
                    }
                }
            }
            out:
            particles = newParticles;
        }
        //===================================================

        void ParticleFilter::calcLastPosition() {
            // TODO calculate the position (average over particles)
            // Input : particles
            // Output : lastPosition
            int sumX = 0;
            int sumY = 0;

            for (Math::Position2D iter : particles) {
                sumX += iter.x;
                sumY += iter.y;
            }

            lastPosition.x = sumX;
            lastPosition.y = sumY;
        }
        //===================================================

    }
}
