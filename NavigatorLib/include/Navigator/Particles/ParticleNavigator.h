//
// Created by  Oleksiy Grechnyev on 8/9/2017.
//

#pragma once

#include <memory>

#include "Navigator/INavigator.h"
#include "Navigator/Beacons/AbstractBeaconNavigator.h"
#include "Navigator/Accel/AbstractAccelNavigator.h"
#include "Navigator/Mesh/RectanMesh.h"

#include "Navigator/Particles/ParticleFilter.h"
#include "Navigator/Particles/ParticleNavigatorConfig.h"

namespace Navigator {
    namespace Particles {
        class ParticleNavigator : public INavigator{
        public: //================ Methods

            /// Run a particle filter step and return last position
            Math::Position3D obtainLastPosition() override;

        private: //=============== Methods
            /// Post-process position using map edges, mesh+mask if needed
            Math::Position3D postProcess(const Math::Position3D & p);

        private: //=============== Fields

            /// Beacon navigator
            std::shared_ptr<Beacons::AbstractBeaconNavigator> bNav;

            /// Accel navigator
            std::shared_ptr<Accel::AbstractAccelNavigator> aNav;

            /// Mesh+mask
            std::shared_ptr<Mesh::RectanMesh> rMesh;

            /// Config
            ParticleNavigatorConfig config;

            /// Particle filter
            ParticleFilter pFilter;

            /// Last position
            Math::Position3D lastPosition;

            /// Is navigator initialized ?
            bool isInitialized = false;

        };
    }
}
