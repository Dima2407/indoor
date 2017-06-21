//
// Created by Igor Maschikevich on 6/20/2017.
//

#ifndef TESTTOOL_TESTERCONNFIG_H
#define TESTTOOL_TESTERCONNFIG_H


namespace ecceltester {
/// The configuration of tester
class Config {
public:
    /** \brief Read Tester config from JSON
         *
         *  File example
 {
  "accelerometer" : "iOS_accelerometer.json",
  "angles" : "iOS_angles.json"
 }
         *
         * @param fileName   The JSON file name
         * @param verbose    true = print log to stdout
         *
         * @return           true if success
         *
         */
    bool readJSON(std::string fileName, bool verbose = true);

    /// Getters
    const std::string &getAccelerometer() const {
        return accelerometer;
    }

    const std::string &getAngles() const {
        return angles;
    }


private:
    /// Input: beacons file name
    std::string accelerometer;

    /// Input: events file name
    std::string angles;



};
}


#endif //TESTTOOL_TESTERCONNFIG_H
