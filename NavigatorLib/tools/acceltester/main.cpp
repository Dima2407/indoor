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

    myjson myj;

    ofstream tempOut;
    tempOut.open("out_data.dt");
    const Value& temp = myj.strimJson("in_data.json");


    const Value& d_angles = myj.strimJson(temp["angles"].GetString());
    const Value& d_accelerometer = myj.strimJson(temp["accelerometer"].GetString());

    d_angles.IsArray();
    d_accelerometer.IsArray();

    double startX = 0.5, startY = 1.2;

    AccelConfig config;

    //StandardAccelNavigator standardAccelNavigator(nullptr, startX, startY, config);


    TrajectoryDetection traj(nullptr, startX, startY, config);
    ToGlobal toGlob(config);

    tempOut << "p.x" << "      "  << "p.y" << "     "  << "p.z" << " "  << endl;
    
    FILE * fileLog1 = fopen("readLog.dat", "w");
    FILE * fileLog2 = fopen("procLog.dat", "w");
    fprintf(fileLog1, "   t  :  tStamp  isS:    ax         ay         az           a      :    pitch       roll       yaw \n");
    fprintf(fileLog2, "   t  :  tStamp  isS:    ax         ay         az           a      :    pitch       roll       yaw \n");
    
    for(int i = 0; i < d_angles.Size(); i++){

        const Value& for_angles = d_angles[i];
        const Value& for_accelerometer = d_accelerometer[i];

        /*
        for_angles["timestamp"].IsInt();
        for_angles["azimuth"].IsDouble();
        for_angles["pitch"].IsDouble();
        for_angles["roll"].IsDouble();

        for_accelerometer["x"].IsDouble();
        for_accelerometer["y"].IsDouble();
        for_accelerometer["z"].IsDouble();
         */

        double timestamp = myj.microsecondInSecon(for_angles["timestamp"].GetInt());
        double azimuth = for_angles["azimuth"].GetDouble();
        double pitch = for_angles["pitch"].GetDouble();
        double roll = for_angles["roll"].GetDouble();
        double aX = for_accelerometer["x"].GetDouble();
        double aY = for_accelerometer["y"].GetDouble();
        double aZ = for_accelerometer["z"].GetDouble();
        
        AccelReceivedData ard{timestamp, aX, aY, aZ, pitch, azimuth, roll};

        
        
        // Process by hand for debugging purpose
        AccelOutputData aod = toGlob.process(ard);
        Position3D p = traj.process(aod);
                
        // Normal way of processing
        // Position3D p = standardAccelNavigator.process(ard);
                
        // Log input data        
        fprintf(fileLog1, "%5d : %10.6f %1d: ", i + 1, timestamp, aod.isStationary);
        double aa = std::sqrt(aX*aX + aY*aY + aZ*aZ);
        fprintf(fileLog1, "%10.6f %10.6f %10.6f %10.6f : ", aX, aY, aZ, aa);
        fprintf(fileLog1, "%10.6f %10.6f %10.6f\n", pitch, roll, azimuth);
        
        // LOg a and angles after rotation
        fprintf(fileLog2, "%5d : %10.6f %1d: ", i + 1, timestamp, aod.isStationary);
        aa = std::sqrt(aod.ax*aod.ax + aod.ay*aod.ay + aod.az*aod.az);
        fprintf(fileLog2, "%10.6f %10.6f %10.6f %10.6f : ", aod.ax, aod.ay, aod.az, aa);
        fprintf(fileLog2, "%10.6f %10.6f %10.6f\n", pitch, roll, azimuth);
        
        

        tempOut << p.x << " "  << p.y << " "  << p.z << " "  << endl;
    }
    fclose(fileLog1);
    fclose(fileLog2);

    return 0;
}
