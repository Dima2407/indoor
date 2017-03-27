#include "imath.h"

#include "kalman_interface.h"

ObjectState Math::kalman(const ObjectState &currState, const ObjectState &beaconState, const ObjectState &accState) {
    ObjectState newState = currState;
    newState.timestamp = std::max(beaconState.timestamp, accState.timestamp);

    Point filteredPos = currState.position;
    double k = 0.0;
    if (accState.valid()) {
        newState.velocity = accState.velocity;
        newState.acceleration = accState.acceleration;
    }
    if (beaconState.valid()) {
        if (accState.valid()) {
            filteredPos = ((currState.position + accState.velocity) + accState.acceleration / 2.0) * (1.0 - k) + beaconState.position * k;
        } else {
            filteredPos = beaconState.position;
        }
    } else if (accState.valid()) {
            //filteredPos = ((currState.position + accState.velocity) + accState.acceleration / 2.0);
        filteredPos = Point();
        filteredPos.x = 3;
        filteredPos.y = 3;
        filteredPos.z = 0;
    } else {
        newState.timestamp = -1;
    }
    newState.position = filteredPos;
    return newState;
}

Types::ObjectState Math::kalman(const Types::ObjectState &currState, const Types::ObjectState &measure) {
    /** Model is next:
     * acceleration is constant and zero
     * velocity is constant
     * position is lineary changed
     *
    **/
    Types::ObjectState updated_state;
    if (!currState.valid()) {
        if (measure.valid()) {
            updated_state = measure;
        }
    } else {
        if (!measure.valid()) {
            return updated_state;
        }
        double dt = (measure.timestamp() - currState.timestamp()) * CommonConstants::time_multiplicator;
        KalmanInterface::SimpleState state = KalmanInterface::kalman_object_state(currState);
        eigenkf::KalmanFilter<KalmanInterface::SimpleState, KalmanInterface::ProcessModel> kf;
        kf.state = state;
        kf.processModel.sigma = KalmanInterface::kalman_process_noise();
        kf.predict(dt);
        eigenkf::AbsoluteMeasurement<KalmanInterface::SimpleState> meas;
        meas.measurement = KalmanInterface::kalman_state(measure);
        meas.covariance  = KalmanInterface::kalman_covar(measure);
        kf.correct(meas);
        updated_state.setStateVector(kf.state.x);
        updated_state.setCovarMatrix(kf.state.covariance);
        updated_state.setTimestamp(measure.timestamp());
    }
    return updated_state;
}

std::vector<double>  Math::mean_filter(int n, const std::vector<double> &data, const std::vector<double> &t_weights) {
    if (data.size() < 2) {
        return data;
    }

    std::vector<double> weights = t_weights;
    int win_size = std::min(n, int(data.size()));
    if (weights.empty()) {
        weights = std::vector<double>(win_size, 1.0 / double(win_size));
    } else {
        // weigths normalization
        double sum = 0;
        for (std::vector<double>::const_iterator it = weights.begin(); it != weights.end(); ++it) {
            sum += *it;
        }
        if (sum != 1.0) {
            for (std::vector<double>::iterator it = weights.begin(); it != weights.end(); ++it) {
                *it /= sum;
            }
        }
    }

    std::vector<double> result(data.size(), 0);
    for (int i=0; i<data.size(); ++i) {
        int end_index   = i;
        int start_index = std::max(0, end_index+1 - win_size);
        std::vector<double> temp_data(end_index - start_index + 1);
        std::vector<double> temp_weights(end_index - start_index + 1);
        int ind, pos;
        for (pos = 0, ind = start_index; ind <= end_index; ++ind, ++pos) {
            temp_data[pos] = data[ind];
            temp_weights[pos] = weights[win_size - pos - 1];
        }
        double sum = 0;
        for (std::vector<double>::const_iterator it = temp_weights.begin(); it != temp_weights.end(); ++it) {
            sum += *it;
        }
        if (sum != 1.0) {
            for (std::vector<double>::iterator it = temp_weights.begin(); it != temp_weights.end(); ++it) {
                *it /= sum;
            }
        }
        result[i] = mean(temp_data, temp_weights);
    }
    return result;
}

std::vector<double> Math::smooth(const std::vector<double> &measurements, const std::vector<long> &times, long max_time) {
    if (max_time == 0) {
        return measurements;
    }
    max_time = times[max_time-1];
    // Computing weights
    // Ensures that sum of weigths will be normalized (eq. 1)
    std::vector<double> weights(times.size(), 1.0);
    std::vector<double>::iterator wit = weights.begin();
    std::vector<long>::const_reverse_iterator ref_it = times.rbegin();
    for (std::vector<long>::const_reverse_iterator rit = times.rbegin(); rit != times.rend(); ++rit, ++wit) {
        *wit = double(max_time) - double(std::min(std::abs(*rit-*ref_it), max_time));
    }
    return mean_filter(max_time, measurements, weights);
}

Types::ObjectState kalman(const Types::ObjectState &currentState, const Types::ObjectState &measurement) {
    Types::ObjectState newState = currentState;
    return newState;
}
