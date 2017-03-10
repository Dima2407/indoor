#ifndef BEACON_H
#define BEACON_H

#include "common_defs.h"
#include "Point.h"
#include "BeaconMeasurement.h"

namespace Sensors {
    namespace Hardware {

/** \brief Bluetooth beacon class.
 *
 * Do not confuse with the unused Beacon struct from common_types.h !
 *
 * It keeeps the history of measurements (_measurements) and also the history of filtered measurements
 * (_filtered_measurements).
 *
 * For understanding txPower, rssi and distance, see the formula in BMath::get_distance
 */
        class Beacon {
        public:
            //-------------------------------
            // Types
            //-------------------------------

            /// Calibration data for a beacon struct: tx_power + rssi + distance
            struct CalibrationData {
                /// Emittted signal strength
                double tx_power;
                /// Received signal strength
                double rssi;
                /// Distance in m
                double distance;
            };
            /// list<CalibrationData>
            typedef std::list<CalibrationData> CalibrationDataContainer;


            //-------------------------------
            // Constants
            //-------------------------------

            static constexpr double DEFAULT_DAMP = 4.0;
            static constexpr int DEFAULT_DATA_CAPACITY  = 2048;
            static constexpr int DEFAULT_FILTER_WIN_SIZE = 10;

            //-------------------------------
            // Public constructors
            //-------------------------------

            /// Constructor which sets \ref _hash, \ref _damp and \ref _txPower
            Beacon(hash_t hash = -1, double damp = DEFAULT_DAMP, double txPower = 1.0) :
                    _hash(hash),
                    _damp(damp),
                    _txPower(txPower) {}

            //-------------------------------
            // Public methods
            //-------------------------------

            /// Get \ref _position (XYZ)
            const Point &position() const{
                return _position;
            }

            /// Get \ref _hash
            hash_t hash() const {
                return _hash;
            }

            /// Get \ref _damp
            double damp() const{
                return _damp;
            }

            /// Get \ref _txPower
            double txPower() const{
                return _txPower;
            }

            /// Set \ref _damp
            void setDamp(double damp){
                _damp = damp;
            }

            /// Set \ref _txPower
            void setTxPower(double tx_power){
                _txPower = tx_power;
            }

            /// Set \ref _position
            void setPosition(const Point &position){
                _position = position;
            }

            /// Set \ref _hash
            void setHash(hash_t hash) {
                _hash = hash;
            }

            /** \brief WARNING ! This is not a simple setter !
             *
             * The actual behavior is like this:
             *
             * Only if txPower <0, set _txPower to txPower
             *
             * Then, set _useTxPowerFromMeasurements to (s && _txPower < 0)
             *
             * Don't ask me !
             *
             * \param[in]  s         The new value of _useTxPowerFromMeasurements
             * \param[in]  txPower   The new value of _txPower
             */
            void setUseTxPowerFromMeasurements(bool s = true, double txPower = 1.0);

            /// Get \ref _useTxPowerFromMeasurements
            bool useTxPowerFromMeasurements() const{
                return _useTxPowerFromMeasurements;
            }

            /// Remove all measurements (Clear list _measurements)
            void clear() {
                _measurements.clear();
            }

            /// Adds beacon measurement (timestamp should be greater or equal to previous measure time)
            void addMeasurement(const BeaconMeasurement &m);

            /// Adds beacon measurement (timestamp should be greater or equal to previous measure time)
            void addMeasurement(double tx_power, double rssi, timestamp_t timestamp);

            /// Return count last elements of history (List _measurements)
            BeaconMeasurementsContainer history(size_t count) const;

            /// Get i-th measurement from the begining
            BeaconMeasurement measurement(size_t i = 0) const;

            /// Get i-th measurement from the end
            BeaconMeasurement rmeasurement(size_t i = 0) const;

            /// Get i-th filtered measurement from the begining
            BeaconMeasurement measurement_filtered(size_t i = 0) const;

            /// i-th filtered measurement from the end
            BeaconMeasurement rmeasurement_filtered(size_t i = 0) const;

            /** \brief Computes estimated rssi and tx_power for time-point time
             *
             * 1. find latest filtered measurements (at least two) that satisfy abs(rssi.timestamp - time) < interpolation_window
             *
             * 2. computes linear interpolation at point time
             *
             * It is just a wrapper to BMath::inxtrapolate()
             */
            BeaconMeasurement estimation(timestamp_t time) const;

            /** \brief Calibrate the beacon
             *
             * Set \ref _damp and \ref _txPower based on the calibration data
             */
            bool calibrate(const CalibrationDataContainer &c);

            /// Get \ref _maxDataCapacity
            size_t dataCapacity() const{
                return _maxDataCapacity;
            }

            /// Set \ref _maxDataCapacity
            void setDataCapacity(size_t c);

            /// Get size of \ref _measurements
            size_t dataCount() const{
                return _measurements.size();
            }

            /// Get size of \ref _filtered_measurements
            size_t dataCountF() const{
                return _filtered_measurements.size();
            }

            /// Get \ref _filterWinSize
            size_t filterWinSize(){
                return _filterWinSize;
            }

            /// Set \ref _filterWinSize
            void setFilterWinSize(size_t ws) {
                _filterWinSize = ws;
            }

            /// Check if the beacon is valid (_hash >=0)
            bool valid() const{
                return (_hash >= 0);
            }

            double lastDistance(hash_t hash, size_t count);

        private:

            //-------------------------------
            // Private methods
            //-------------------------------

            /** Create a new filtered measurement out of a list of measurements
             *
             * Essentially it applies the averaging function Math::mean() to rssi and timestamp to
             * get the average values.
             *
             * Uses _filterWinSize last items at most.
             */
            BeaconMeasurement filter(const BeaconMeasurementsContainer &mc);

            //-------------------------------
            // Private fields
            //-------------------------------

            /// Beacon position (XYZ)
            Point _position;
            /// Dampening factor
            double _damp;
            /// Emittted power (logarithmic)
            double _txPower;
            /// %Beacon's _hash (hash of the MAC adddress ??)
            hash_t _hash;
            /// This parameter is used for calibration
            bool _useTxPowerFromMeasurements = true;

            /// Max data capacity for both _measurements and _filtered_measurements
            size_t _maxDataCapacity = DEFAULT_DATA_CAPACITY;
            /// Filter window size, a parameter used by filter()
            size_t _filterWinSize = DEFAULT_FILTER_WIN_SIZE;

            /// List of measurements
            BeaconMeasurementsContainer _measurements;
            /// List of filtered measurements
            BeaconMeasurementsContainer _filtered_measurements;
        };

    } // namespace Hardware
} // namespace Sensors

#endif // BEACON_H
