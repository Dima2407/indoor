//
// Created by Igor Maschikevich on 6/9/2017.
//
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <cassert>
#include "rapidjson_min/include/rapidjson/document.h"
#include "rapidjson_min/include/rapidjson/istreamwrapper.h"

#include "Navigator.h"
#include <fstream> // подключаем файлы


using namespace rapidjson;
using namespace std;

using Navigator::Accel::TrajectoryDetection;
using Navigator::Accel::AccelOutputData;
using Navigator::Math::Position3D;
double microsecondInSecon(int timestamp);
Document strim (string inFile);
int main() {

    const Value& temp = strim("D:\\t.json");

    const Value& d_angles = strim(temp["angles"].GetString());
    const Value& d_accelerometer = strim(temp["accelerometer"].GetString());

    d_angles.IsArray();
    d_accelerometer.IsArray();

    //    for(int i  =0; i < d2.Size(); i++){
    for(int i = 0; i < 10; i++){
        const Value& for_angles = d_angles[i];
        const Value& for_accelerometer = d_accelerometer[i];

        for_angles["timestamp"].IsInt();
        for_angles["azimuth"].IsDouble();
        for_angles["pitch"].IsDouble();
        for_angles["roll"].IsDouble();

        for_accelerometer["x"].IsDouble();
        for_accelerometer["y"].IsDouble();
        for_accelerometer["z"].IsDouble();

        cout<<"timestamp = "<<microsecondInSecon(for_angles["timestamp"].GetInt())<<", s"<<endl;
        cout<<"azimuth = "<<for_angles["azimuth"].GetDouble()<< endl;
        cout<<"pitch = "<<for_angles["pitch"].GetDouble()<< endl;
        cout<<"roll = "<<for_angles["roll"].GetDouble()<< endl;

        cout<<"x = "<<for_accelerometer["x"].GetDouble()<< endl;
        cout<<"y = "<<for_accelerometer["y"].GetDouble()<< endl;
        cout<<"z = "<<for_accelerometer["z"].GetDouble()<< endl;
        cout <<endl;
    }
    return 0;
}

double microsecondInSecon(int timestamp){
    return (double) timestamp / 1000000;
}

// This method makes a miracle
Document strim (string inFile){
    ifstream in(inFile);
    IStreamWrapper isw(in);
    Document document;
    document.ParseStream(isw);
    in.close();
    return document;
}
