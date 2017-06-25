//
// Created by Igor Maschikevich on 6/22/2017.
//

#include <cstdio>

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

    //StandardAccelNavigator standardAccelNavigator(nullptr, 0.5, 1.2, 20.0);
    TrajectoryDetection traj(nullptr, 0.5, 1.2);
    ToGlobal toGlob(20, false);

    tempOut << "p.x" << "      "  << "p.y" << "     "  << "p.z" << " "  << endl;
    
    FILE * fileLog1 = fopen("readLog.dat", "w");
    fprintf(fileLog1, "   t  :  tStamp  iss:    ax         ay         az      :    pitch       roll       yaw \n");
    
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
        aod.ay = -aod.ay;

        Position3D p = traj.process(aod);
                
        // Normal way of processing
        // Position3D p = standardAccelNavigator.process(ard);
                
        fprintf(fileLog1, "%5d : %10.6f %1d: ", i + 1, timestamp, aod.isStationary);
        fprintf(fileLog1, "%10.6f %10.6f %10.6f : ", aX, aY, aZ);
        fprintf(fileLog1, "%10.6f %10.6f %10.6f\n", pitch, roll, azimuth);

        tempOut << p.x << " "  << p.y << " "  << p.z << " "  << endl;
    }
    fclose(fileLog1);

    return 0;
}
