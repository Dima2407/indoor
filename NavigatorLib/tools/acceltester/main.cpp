//
// Created by Igor Maschikevich on 6/22/2017.
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream> // подключаем файлы
#include "rapidjson_min/include/rapidjson/document.h"
#include "rapidjson_min/include/rapidjson/istreamwrapper.h"

#include "Navigator.h"

using namespace rapidjson;
using namespace std;

using Navigator::Accel::TrajectoryDetection;
using Navigator::Accel::AccelOutputData;
using Navigator::Math::Position3D;

double microsecondInSecon(int timestamp);
Document strimJson (string inFile);

int main() {



    using namespace std;
    ofstream tempOut;
    tempOut.open("out_data.json");
    //    tempOut <<"write file"<< endl;
    const Value& temp = strimJson("in_data.json");
    //    const Value& temp = strimJson("D:\\t.json");


    const Value& d_angles = strimJson(temp["angles"].GetString());
    const Value& d_accelerometer = strimJson(temp["accelerometer"].GetString());

    d_angles.IsArray();
    d_accelerometer.IsArray();


    //    tempOut <<"["<<endl;
 StandardAccelNavigator standardAccelNavigator(rMesh, 0.0, 0.0, 180.0);
    //    for(int i  =0; i < d_angles.Size(); i++){
    for(int i  =0; i < 1; i++){

        const Value& for_angles = d_angles[i];
        const Value& for_accelerometer = d_accelerometer[i];

        for_angles["timestamp"].IsInt();
        for_angles["azimuth"].IsDouble();
        for_angles["pitch"].IsDouble();
        for_angles["roll"].IsDouble();

        for_accelerometer["x"].IsDouble();
        for_accelerometer["y"].IsDouble();
        for_accelerometer["z"].IsDouble();




    }
    //output data (out_data.json)
    //        tempOut <<"{"<<endl;
    //        tempOut <<"\"timestamp\" : "<<microsecondInSecon(for_angles["timestamp"].GetInt())<<","<<endl;
    //        tempOut <<"\"azimuth\" : "<<for_angles["azimuth"].GetDouble()<<","<<endl;
    //        tempOut <<"\"pitch\" : "<<for_angles["pitch"].GetDouble()<<","<<endl;
    //        tempOut <<"\"roll\" : "<<for_angles["roll"].GetDouble()<<","<<endl;

    //        tempOut <<"\"x\" : "<<for_accelerometer["x"].GetDouble()<<","<<endl;
    //        tempOut <<"\"y\" : "<<for_accelerometer["y"].GetDouble()<<","<<endl;
    //        tempOut <<"\"z\" : "<<for_accelerometer["z"].GetDouble()<< endl;
    //        tempOut <<"},"<<endl;
    //    }
    //    tempOut <<"]"<<endl;
    return 0;
}
//converter microsecond in secon
double microsecondInSecon(int timestamp){
    return (double) timestamp / 1000000;
}

// This method makes a miracle
Document strimJson (string inFile){
    ifstream in(inFile);
    IStreamWrapper isw(in);
    Document document;
    document.ParseStream(isw);
    in.close();
    return document;
}
