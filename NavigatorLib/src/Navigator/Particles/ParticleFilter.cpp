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
            for (int i = 0; i < config.numPart; ++i) {
                Math::Position2D r;  // Random shift in x,y
                if (config.simulatedRandom) {
                    r = simRandPP.at(i);  // Simulated random shift
                } else {
                    // Generate random
                    r.x = randNorm(config.sigmaX);
                    r.y = randNorm(config.sigmaY);
                }
                tmpParticles[i] = particles[i] + delta + r;
            }
        }
        //===================================================

        void ParticleFilter::calcWeights(const Math::Position2D &z,
                                         const std::function<bool(const Math::Position2D &,
                                                                  const Math::Position2D &)> &allowMove,
                                         const std::function<Math::Position2D(const Math::Position2D &)> &meshCorrect) {
            double sum = 0.0;
            for (int i = 0; i < config.numPart; ++i) {
                if (allowMove(particles[i], tmpParticles[i])) {
                    weights[i] = gauss(tmpParticles[i], z);
                    sum += weights[i];
                } else {
                    weights[i] = 0;
                }
            }
            // printf("sum = %lf \n", sum);
            if (sum < 1.0e-10) {
                // All particles with zero weight, apply mesh correction
                for (int i = 0; i < config.numPart; ++i) {
                    tmpParticles[i] = meshCorrect(tmpParticles[i]);
                    weights[i] = gauss(tmpParticles[i], z);
                    sum += weights[i];
                }
            }
            // Normalize weights
            for (auto &iter : weights) {
                iter /= sum;
            }
        }
        //===================================================

        void ParticleFilter::resample() {
            double maxWeight = 0;   // Find max weight
            for (double iter :weights) {
                if (maxWeight < iter) {
                    maxWeight = iter;
                }
            }

            int i;  // Choose a random particle i
            if (config.simulatedRandom) {
                i = simRandI;
            } else {
                i = randInt(weights.size() - 1);
            }

            for (int j = 0; j < config.numPart; ++j) {
                // Random beta
                double beta;
                if (config.simulatedRandom) {
                    beta = simRandBeta.at(j) * 2 * maxWeight;
                } else {
                    beta = randRange(0, 2 * maxWeight);
                }
                betas[j] = beta;
                while (true) {
                    if (beta > weights[i]) {
                        beta -= weights[i];
                        if (++i == weights.size()) {
                            i = 0;
                        }
                    } else {
                        particles[j] = tmpParticles[i];  // j-th resampled particle
                        break;
                    }
                }
            }


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
            double degX = (particle.x - z.x)*(particle.x - z.x) / (2 * config.sigmaX * config.sigmaX);
            double degY = (particle.y - z.y)*(particle.y - z.y) / (2 * config.sigmaY * config.sigmaY);
            return expr * std::exp(-degX - degY);
        }

    }
}
