//
// Created by  Victor Draban on 6/7/2017.
//

#include <iostream>
#include <vector>
#include "Navigator/Accel/ToGlobal.h"

namespace Navigator {
namespace Accel {
    
        // Quaternion product using std::vector, temporary test, not a member of the ToGlobal class
        /*std::vector<double> myQuatProduct(const std::vector<double> & a, const std::vector<double> & b){
            return std::vector<double>{
                a[0]*b[0] - a[1]*b[1] - a[2]*b[2] - a[3]*b[3],
                a[0]*b[1] + a[1]*b[0] + a[2]*b[3] - a[3]*b[2],
                a[0]*b[2] - a[1]*b[3] + a[2]*b[0] + a[3]*b[1],
                a[0]*b[3] + a[1]*b[2] - a[2]*b[1] + a[3]*b[0]
            };
        }*/

        AccelOutputData ToGlobal::process(const AccelReceivedData & data)
        {
            using namespace Eigen;
            TempData tempData;
            AccelOutputData result;

            filteringAccelerations(data, tempData);
            angleCorrection(data, tempData);
            recognizeState(data, tempData);

            result.isStationary = tempData.isStationary;

            // Always rotate for now : test
            if (true || !result.isStationary) {
                Quaternion<double> quat = initQuaternion(tempData.pitch, tempData.roll, tempData.yaw);
                Quaternion<double> invertQuat = quat.conjugate();
                Quaternion<double> r(0, tempData.ax, tempData.ay, tempData.az);

                Quaternion<double> resultQ = quat * r * invertQuat;

                result.ax = resultQ.x();
                result.ay = resultQ.y();
                
                // We remove az for now
                // result.az = resultQ.z()-1;
                result.az = resultQ.z();
                
                // Check alt quaternion operation without eigen : test. Remove later if OK.
                /*if (true){
                    using namespace std;
                    
                    double p2 = tempData.pitch/2;
                    double r2 = tempData.roll/2;
                    double y2 = tempData.yaw/2;
                    //Quaternion
                    vector<double> q = {
                        cos(p2)*cos(r2)*cos(y2) - sin(p2)*sin(r2)*sin(y2),
                        cos(p2)*sin(r2)*sin(y2) + sin(p2)*cos(r2)*cos(y2),
                        cos(p2)*sin(r2)*cos(y2) - sin(p2)*cos(r2)*sin(y2),
                        cos(p2)*cos(r2)*sin(y2) + sin(p2)*sin(r2)*cos(y2)
                    };
                    // Conjugate quaternion
                    vector<double> qc = {q[0], -q[1], -q[2], -q[3]};
                    // Quaternion made of a
                    vector<double> qa = {0, tempData.ax, tempData.ay, tempData.az};
                    
                    vector<double> qres = myQuatProduct(myQuatProduct(q, qa), qc);
                    
                    result.ax = qres[1];
                    result.ay = qres[2];
                    result.az = qres[3];
                }*/
                
                
            } else {
                result.ax = 0;
                result.ay = 0;
                result.az = 0;
            }

            result.timestamp = data.timestamp;
            if (std::isnan(lastTime)) {
                result.timeDiff = 0;
            } else {
                result.timeDiff = result.timestamp - lastTime;
            }
            lastTime = result.timestamp;
            return result;
        }

// =================================================================================

        void ToGlobal::recognizeState(const AccelReceivedData &in, TempData &out) {
            auto a_norm = sqrt(out.ax*out.ax + out.ay*out.ay + out.az*out.az);
            if (a_norm < ACC_TH) {
                out.isStationary = true;
            } else {
                out.isStationary = false;
            }
        }

// =================================================================================

        void ToGlobal::angleCorrection(const AccelReceivedData &in, TempData &out) {
            out.pitch = in.pitch*(M_PI/180);
            out.roll = in.roll*(M_PI/180);
            out.yaw = (-in.yaw - 180 + mapOrientationAngle)*(M_PI/180);
        }

// =================================================================================

        void ToGlobal::filteringAccelerations(const AccelReceivedData &in, TempData &out) {
            if (useFilter) {
                out.ax = filterAX.process({in.ax, in.timestamp}).val;
                out.ay = filterAY.process({in.ay, in.timestamp}).val;
                out.az = filterAZ.process({in.az, in.timestamp}).val;
            } else {
                out.ax = in.ax;
                out.ay = in.ay;
                out.az = in.az;
            }
        }

// =================================================================================
        
// =================================================================================

/*
 *
 *
 * */
         Eigen::Quaternion<double> ToGlobal::initQuaternion(double pitch, double roll, double yaw) {
             double w = cos(pitch/2)*cos(roll/2)*cos(yaw/2) - sin(pitch/2)*sin(roll/2)*sin(yaw/2);
             double x = cos(pitch/2)*sin(roll/2)*sin(yaw/2) + sin(pitch/2)*cos(roll/2)*cos(yaw/2);
             double y = cos(pitch/2)*sin(roll/2)*cos(yaw/2) - sin(pitch/2)*cos(roll/2)*sin(yaw/2);
             double z = cos(pitch/2)*cos(roll/2)*sin(yaw/2) + sin(pitch/2)*sin(roll/2)*cos(yaw/2);
             return Eigen::Quaternion<double>(w, x, y, z);
         }
    }
}
