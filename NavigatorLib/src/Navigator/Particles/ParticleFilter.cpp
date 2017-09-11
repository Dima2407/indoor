//
// Created by  Oleksiy Grechnyev on 8/7/2017.
//

#include <iostream>
#include <cstdio>

#include "Navigator/Particles/ParticleFilter.h"

namespace Navigator {
    namespace Particles {

        //===================================================
        void ParticleFilter::initialize(const Math::Position2D &pos,
                                        const std::function<Math::Position2D(const Math::Position2D &)> &meshCorrect) {
            /*for (auto& iter : particles) {
                iter.x = pos.x + randRange(-config.alpha, config.alpha);
                iter.y = pos.x + randRange(-config.alpha, config.alpha);
                iter = meshCorrect(iter);
            }*/

            for (int i = 0; i < particles.size(); ++i) {
                Math::Position2D r;  // Random shift in x,y
                if (config.simulatedRandom) {
                    r = simRandPI.at(i);  // Simulated random shift
                } else {
                    // Generate random
                    r.x = randRange(-config.alpha, config.alpha);
                    r.y = randRange(-config.alpha, config.alpha);
                }
                particles[i] = meshCorrect(pos + r);
            }
        }
        //===================================================

        Math::Position2D &ParticleFilter::process(const Math::Position2D &delta,
                                                  const Math::Position2D &z,
                                                  const std::function<bool(const Math::Position2D &,
                                                                           const Math::Position2D &)> &allowMove,
                                                  const std::function<Math::Position2D(
                                                          const Math::Position2D &)> &meshCorrect) {
            // This is fine, don't change
            moveParticles(delta);
            calcWeights(z, allowMove, meshCorrect);
            if (config.useResampling)
                resample();
            calcLastPosition();

            return lastPosition;
        }
        //===================================================

        void ParticleFilter::moveParticles(const Math::Position2D &delta) {
            oldParticles = particles;
            for (int i = 0; i < particles.size(); ++i) {
                Math::Position2D r;  // Random shift in x,y
                if (config.simulatedRandom) {
                    r = simRandPP.at(i);  // Simulated random shift
                } else {
                    // Generate random
                    r.x = randNorm(config.sigmaX);
                    r.y = randNorm(config.sigmaY);
                }
                particles[i] = oldParticles[i] + delta + r;
            }
        }
        //===================================================

        void ParticleFilter::calcWeights(const Math::Position2D &z,
                                         const std::function<bool(const Math::Position2D &,
                                                                  const Math::Position2D &)> &allowMove,
                                         const std::function<Math::Position2D(const Math::Position2D &)> &meshCorrect) {
            double sum = 0.0;
            for (int i = 0; i < particles.size(); ++i) {
                if (allowMove(oldParticles[i], particles[i])) {
                    // printf("pi = %lf %lf  z = %lf %lf \n", particles[i].x, particles[i].y, z.x, z.y);
                    weights[i] = gauss(particles[i], z);
                    // printf("wi = %lf\n", weights[i]);
                    sum += weights[i];
                } else {
                    weights[i] = 0;
                }
            }
            // printf("sum = %lf \n", sum);
            if (sum < 1.0e-10) {
                for (int i = 0; i < particles.size(); ++i) {
                    particles[i] = meshCorrect(particles[i]);
                    weights[i] = gauss(particles[i], z);
                    sum += weights[i];
                }
            }
            for (auto &iter : weights) {
                iter /= sum;
            }
        }
        //===================================================

        void ParticleFilter::resample() {
            std::vector<Math::Position2D> newParticles;
            newParticles.reserve(config.numPart);
            double maxWeight = 0;
            for (double iter :weights) {
                if (maxWeight < iter) {
                    maxWeight = iter;
                }
            }

            int i;  // Choose a random particle
            if (config.simulatedRandom) {
                i = simRandI;
            } else {
                i = randInt(weights.size() - 1);
            }
            for (int j = 0; j < weights.size(); ++j) {
                double beta; if (config.simulatedRandom) {
                    beta = simRandBeta.at(j) * 2 * maxWeight;
                } else {
                    beta = randRange(0, 2 * maxWeight);
                }
                while (true) {
                    if (beta > weights[i]) {
                        beta -= weights[i];
                        if (++i == weights.size()) {
                            i = 0;
                        }
                    } else {
                        newParticles.push_back(particles[i]);
                        break;
                    }
                }
            }
            particles = std::move(newParticles);
        }
        //===================================================

        void ParticleFilter::calcLastPosition() {
            double sumX = 0;
            double sumY = 0;

            for (const Math::Position2D &iter : particles) {
                sumX += iter.x;
                sumY += iter.y;
            }

            lastPosition.x = sumX / config.numPart;
            lastPosition.y = sumY / config.numPart;
        }
        //===================================================

        double ParticleFilter::gauss(const Math::Position2D &particle, const Math::Position2D &z) {
            double expr = 1 / (config.sigmaX * config.sigmaY * 2 * M_PI);
            double degX = std::pow(particle.x - z.x, 2) / (2 * config.sigmaX * config.sigmaX);
            double degY = std::pow(particle.y - z.y, 2) / (2 * config.sigmaY * config.sigmaY);
            return expr * std::exp(-degX - degY);
        }

    }
}
