//
// Created by Igor Maschikevich on 6/22/2017.
//

#include <cstdio>
#include <cmath>

#include "Navigator.h"
#include "rapidjson_min/include/rapidjson/document.h"
#include "rapidjson_min/include/rapidjson/istreamwrapper.h"
#include "myjson.h"
using namespace std;
using Navigator::Math::Position3D;
// using Navigator::Accel::StandardAccelNavigator;
// using Navigator::Accel::AccelReceivedData;

using namespace Navigator::Accel;

using namespace rapidjson;
using namespace std;

//double microsecondInSecon(int timestamp);
//Document strimJson (string inFile);

int main() {
    using namespace acceltester;

    cout << "Reading input data ..." << endl;

    myjson myj;

    ofstream tempOut;
    const Value& temp = myj.strimJson("in_data.json");

    const Value& d_angles = myj.strimJson(temp["angles"].GetString());
    const Value& d_accelerometer = myj.strimJson(temp["accelerometer"].GetString());

    d_angles.IsArray();
    d_accelerometer.IsArray();

    double startX = 0.3, startY = 1.0;

    cout << "Calculating trajectory ..." << endl;

    AccelConfig config;
    config.useFilter = true;

    // Filter coefficients for 20 mS (?)
//    config.a = { 1.000000000000000, -6.390364563108539, 18.000338335739894, -29.171099374882836, 29.731375438327440, -19.505631768126626, 8.040995932998929, -1.903668891132583, 0.198100011559791};
//    config.b = {0.00000017625537289281, 0.00000141004298314252, 0.00000493515044099882, 0.00000987030088199763, 0.00001233787610249704, 0.00000987030088199763, 0.00000493515044099882, 0.00000141004298314252, 0.00000017625537289281};

    //StandardAccelNavigator standardAccelNavigator(nullptr, startX, startY, config);

    TrajectoryDetection traj(nullptr, startX, startY, config);
    ToGlobal toGlob(config);

    FILE * fileLog1 = fopen("readLog.dat", "w");
    FILE * fileLog2 = fopen("procLog.dat", "w");
    FILE * filePos = fopen("route.dat", "w");

    fprintf(fileLog1, "   t  :  tStamp  isS:    ax         ay         az           a     :    pitch       roll       yaw \n");
    fprintf(fileLog2, "   t  :  tStamp  isS:    ax         ay         az           a     :    pitch       roll       yaw \n");
    fprintf(filePos,  "   t  :  tStamp    :     x          y\n");

    for(int i = 0; i < min(d_angles.Size(), d_accelerometer.Size()); i++){

        const Value& for_angles = d_angles[i];
        const Value& for_accelerometer = d_accelerometer[i];

//        double timestamp = myj.microsecondInSecon(for_angles["timestamp"].GetInt());
        double timestamp = for_angles["timestamp"].GetDouble();
//        double azimuth = for_angles["azimuth"].GetDouble();
//        double pitch = for_angles["pitch"].GetDouble();
//        double roll = for_angles["roll"].GetDouble();
        double azimuth = for_angles["z"].GetDouble();
        double pitch = for_angles["x"].GetDouble();
        double roll = for_angles["y"].GetDouble();

        double aX = for_accelerometer["x"].GetDouble();
        double aY = for_accelerometer["y"].GetDouble();
        double aZ = for_accelerometer["z"].GetDouble();
        
        AccelReceivedData ard{timestamp, aX, aY, aZ, pitch, azimuth, roll};

        // Process by hand for debugging purposes
        AccelOutputData aod = toGlob.process(ard);
        Position3D p = traj.processDummy(aod);
                
        // Normal way of processing
        // Position3D p = standardAccelNavigator.process(ard);
                
        // Log input data        
        fprintf(fileLog1, "%5d : %10.6f %1d: ", i + 1, timestamp, aod.isStationary);
        double aa = std::sqrt(aX*aX + aY*aY + aZ*aZ);
        fprintf(fileLog1, "%10.6f %10.6f %10.6f %10.6f : ", aX, aY, aZ, aa);
        fprintf(fileLog1, "%10.6f %10.6f %10.6f\n", pitch, roll, azimuth);
        
        // Log a and angles after rotation
        fprintf(fileLog2, "%5d : %10.6f %1d: ", i + 1, timestamp, aod.isStationary);
        aa = std::sqrt(aod.ax*aod.ax + aod.ay*aod.ay + aod.az*aod.az);
        fprintf(fileLog2, "%10.6f %10.6f %10.6f %10.6f : ", aod.ax, aod.ay, aod.az, aa);
        fprintf(fileLog2, "%10.6f %10.6f %10.6f\n", pitch, roll, azimuth);
        
        // Write trajectory
        fprintf(filePos, "%5d : %10.6f : %10.6f %10.6f\n", i + 1, timestamp, p.x, p.y);
    }
    fclose(fileLog1);
    fclose(fileLog2);
    fclose(filePos);

    cout << "Finished." << endl;

    return 0;
}
