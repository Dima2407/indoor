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
        }
        //===================================================

        void ParticleFilter::calcWeights(const Math::Position2D &z, const std::function<bool(const Math::Position2D &,
                                                                                             const Math::Position2D &)> &allowMove) {
            // TODO calculate particle weights using z (BLE position) and allowMove
            // Input: particles, z, allowMove
            // Output : weights
        }
        //===================================================

        void ParticleFilter::resample() {
            // TODO resample particles
            // Input : particles, weights
            // Output : particles

            // Note: you will need another vector newParticles, and something like (in the end)
            //  particles=newParticles;
        }
        //===================================================

        void ParticleFilter::calcLastPosition() {
            // TODO calculate the position (average over particles)
            // Input : particles
            // Output : lastPosition
        }
        //===================================================

    }
}