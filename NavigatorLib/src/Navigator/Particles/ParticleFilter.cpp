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
            oldParticles = particles;

            for (int i = 0; i < particles.size(); ++i) {
                particles[i].x = oldParticles[i].x + delta.x + randNorm(config.sigma);
                particles[i].y = oldParticles[i].y + delta.y + randNorm(config.sigma);
            }
        }
        //===================================================

        void ParticleFilter::calcWeights(const Math::Position2D &z, const std::function<bool(const Math::Position2D &,
                                                                                             const Math::Position2D &)> &allowMove) {
            // TODO calculate particle weights using z (BLE position) and allowMove
            // Input: particles, z, allowMove
            // Output : weights
            double sum = 0;
            for (int i = 0; i < particles.size(); ++i) {
                if (allowMove(oldParticles[i], particles[i])) {
                    weights[i] = gause(particles[i], z);
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
            std::vector<Math::Position2D> newParticles;
            double maxWeight = 0;
            for (double iter :weights) {
                if (maxWeight < iter) {
                    maxWeight = iter;
                }
            }

            bool first = false;
            int randomStart = randRange(0, weights.size());
            double beta = randRange(0, 2 * maxWeight);
            while (true) {
                for (int i = 0; i < weights.size(); ++i) {
                    if (first == false) {
                        i = randomStart;
                        first = true;
                    }
                    if (weights[i] > 0) {
                        if (beta > weights[i]) {
                            beta -= weights[i];
                        } else {
                           newParticles.push_back(particles[i]);
                           if (newParticles.size() == weights.size()) {
                               goto out;
                           }
                           beta = randRange(0, 2 * maxWeight);
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

        double ParticleFilter::gause(const Math::Position2D &particle, const Math::Position2D &z) {
            double expression = 1 / (config.sigma * std::sqrt(2 * M_PI));
            double degreeEforX = -(std::pow(particle.x - z.x, 2) / (2 * config.sigma * config.sigma));
            double degreeEforY = -(std::pow(particle.y - z.y, 2) / (2 * config.sigma * config.sigma));
            double weightX = expression * std::pow(M_E, degreeEforX);
            double weightY = expression * std::pow(M_E, degreeEforY);
            return weightX * weightY;
        }

    }
}
