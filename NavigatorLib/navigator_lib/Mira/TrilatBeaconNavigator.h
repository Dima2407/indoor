//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#include <map>
#include <memory>

#include "./AbstractBeaconNavigator.h"
#include "./BeaconProcessor.h"

#pragma once
namespace Navi {
    namespace beacon {

        // TODO : implement this class
        class TrilatBeaconNavigator : public AbstractBeaconNavigator {

        private:
            std::map<BeaconUID, std::shared_ptr<BeaconProcessor>> beaconList;
        };
    }
}