//
// Created by  Oleksiy Grechnyev on 8/7/2017.
//

#include "Navigator/Particles/ParticleFilter.h"

namespace Navigator {
    namespace Particles {

        //===================================================
        void ParticleFilter::initialize(const Math::Position2D &pos,
                            const std::function<Math::Position2D(const Math::Position2D &)> & meshCorrect) {
            for (auto& iter : particles) {
                iter.x = pos.x + randRange(-config.alpha, config.alpha);
                iter.y = pos.x + randRange(-config.alpha, config.alpha);
                iter = meshCorrect(iter);
            }
        }
        //===================================================

        Math::Position2D &ParticleFilter::process(const Math::Position2D &delta,
                                                  const Math::Position2D &z,
                                                  const std::function<bool(const Math::Position2D &,
                                                  const Math::Position2D &)> &allowMove,
                                       const std::function<Math::Position2D(const Math::Position2D &)> & meshCorrect) {
            // This is fine, don't change
            moveParticles(delta);
            calcWeights(z, allowMove, meshCorrect);
            resample();
            calcLastPosition();

            return lastPosition;
        }
        //===================================================

        void ParticleFilter::moveParticles(const Math::Position2D &delta) {
            oldParticles = particles;
            for (int i = 0; i < particles.size(); ++i) {
                particles[i].x = oldParticles[i].x + delta.x + randNorm(config.sigmaX);
                particles[i].y = oldParticles[i].y + delta.y + randNorm(config.sigmaY);
            }
        }
        //===================================================

        void ParticleFilter::calcWeights(const Math::Position2D &z,
                                         const std::function<bool(const Math::Position2D &,
                                         const Math::Position2D &)> &allowMove,
                                         const std::function<Math::Position2D(const Math::Position2D &)> & meshCorrect) {
            double sum = 0.0;
            for (int i = 0; i < particles.size(); ++i) {
                if (allowMove(oldParticles[i], particles[i])) {
                    weights[i] = gauss(particles[i], z);
                    sum += weights[i];
                } else {
                    weights[i] = 0;
                }
            }
            if (sum == 0) {
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
            double maxWeight = 0;
            for (double iter :weights) {
                if (maxWeight < iter) {
                    maxWeight = iter;
                }
            }

            int i = randInt(weights.size() - 1);
            for (int j = 0; j < weights.size(); ++j) {
                double beta = randRange(0, 2 * maxWeight);
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
            particles = newParticles;
        }
        //===================================================

        void ParticleFilter::calcLastPosition() {
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

        double ParticleFilter::gauss(const Math::Position2D &particle, const Math::Position2D &z) {
            double expressionX = 1 / (config.sigmaX * std::sqrt(2 * M_PI));
            double expressionY = 1 / (config.sigmaY * std::sqrt(2 * M_PI));
            double degreeEforX = -(std::pow(particle.x - z.x, 2) / (2 * config.sigmaX * config.sigmaX));
            double degreeEforY = -(std::pow(particle.y - z.y, 2) / (2 * config.sigmaY * config.sigmaY));
            double weightX = expressionX * std::exp(degreeEforX);
            double weightY = expressionY * std::exp(degreeEforY);
            return weightX * weightY;
        }

    }
}
