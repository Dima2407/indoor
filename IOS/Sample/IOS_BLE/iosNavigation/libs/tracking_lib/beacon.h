#ifndef BEACON_H
#define BEACON_H

#include "common_types.h"

namespace Sensors {
namespace Hardware {

class Beacon {
    public:
        struct CalibrationData {
            double tx_power;
            double rssi;
            double distance;
        };
        typedef std::list<CalibrationData> CalibrationDataContainer;

    public:
        static const double DEFAULT_DAMP;
        static const int DEFAULT_DATA_CAPACITY;
        static const int DEFAULT_FILTER_WIN_SIZE;

    public:
        Beacon(hash_t hash = -1, double damp = DEFAULT_DAMP, double txPower = 1.0);

        const Point&    position() const;
        hash_t          hash() const;
        double          damp() const;
        double          txPower() const;

        void setDamp   (double damp);
        void setTxPower(double tx_power);
        void setPosition(const Point &position);
        void setHash(hash_t hash);

        void setUseTxPowerFromMeasurements(bool s = true, double txPower = 1.0);
        bool useTxPowerFromMeasurements() const;

        void clear();
        void addMeasurement(const BeaconMeasurement &m); // adds beacon measurement (timestamp should be greater or equal to previous measure time)
        void addMeasurement(double tx_power, double rssi, timestamp_t timestamp); // adds beacon measurement (timestamp should be greater or equal to previous measure time)
        BeaconMeasurementsContainer  history(size_t count) const;
        BeaconMeasurement    measurement(size_t i = 0) const; // i-th measurement from the begining
        BeaconMeasurement   rmeasurement(size_t i = 0) const; // i-th measurement from the end
        BeaconMeasurement    measurement_filtered(size_t i = 0) const; // i-th filtered measurement from the begining
        BeaconMeasurement   rmeasurement_filtered(size_t i = 0) const; // i-th filtered measurement from the end
        BeaconMeasurement   estimation(timestamp_t time) const; // computes estimated rssi and tx_power for time-point 'time'

        bool calibrate(const CalibrationDataContainer &c);

        size_t dataCapacity() const;
        void   setDataCapacity(size_t c);
        size_t dataCount () const;
        size_t dataCountF() const;

        size_t filterWinSize();
        void   setFilterWinSize(size_t ws);

        bool valid() const;

        double lastDistance(hash_t hash, size_t count);

    protected:
        BeaconMeasurement    filter(const BeaconMeasurementsContainer &mc);

    private:
        Point   _position;
        double  _damp;
        double  _txPower;
        hash_t  _hash;
        bool    _useTxPowerFromMeasurements;

        size_t     _maxDataCapacity;
        size_t     _filterWinSize;

        BeaconMeasurementsContainer _measurements;
        BeaconMeasurementsContainer _filtered_measurements;
};

} // namespace Hardware
} // namespace Sensors

#endif // BEACON_H
