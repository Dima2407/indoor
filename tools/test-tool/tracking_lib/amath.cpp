#include "amath.h"

#include <iostream>

ObjectState AMath::sensor_navigation(const ObjectState &prevState, const AccMeasurement &accMeasurement) {
    ObjectState newState = prevState;
    newState.acceleration = accMeasurement.values / 1.0;
    newState.timestamp = accMeasurement.timestamp;
    if (prevState.valid()) {
        time_t dt = newState.timestamp - prevState.timestamp;
        newState.velocity.x = prevState.velocity.x + (newState.acceleration.x );
        newState.velocity.y = prevState.velocity.y + (newState.acceleration.y / 15.0);
        newState.position.x = (prevState.position.x + newState.velocity.x) + newState.acceleration.x / 2.0;
        newState.position.y = (prevState.position.y + newState.velocity.y) + newState.acceleration.y / 2.0;
    } else {
        newState.velocity.x = (newState.acceleration.x / 15.0);
        newState.velocity.y = (newState.acceleration.y / 15.0);
        newState.position.x = (newState.acceleration.x / 2.0);
        newState.position.y = (newState.acceleration.y / 2.0);
    }

    std::cout << "ACC [" << newState.acceleration.x << " " << newState.acceleration.y
              << " | "   << newState.velocity.x     << " " << newState.velocity.y
              << " | "   << newState.position.x     << " " << newState.position.y
              << "]"     << std::endl;
    return newState;
}
