//
// Created by  Oleksiy Grechnyev on 8/7/2017.
//

#include "Navigator/Particles/ParticleFilter.h"

namespace Navigator {
    namespace Particles {

        //===================================================
        void ParticleFilter::initialize(const Math::Position2D &pos) {
            // TODO implement seeding particles
        }
        //===================================================

        Math::Position2D &ParticleFilter::process(const Math::Position2D &delta, const Math::Position2D &z,
                                                  const std::function<bool(const Math::Position2D &,
                                                                           const Math::Position2D &)> &allowMove) {


            return lastPosition;
        }
        //===================================================

    }
}