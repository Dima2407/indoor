//
// Created by Igor Maschikevich on 6/22/2017.
//
#pragma once
#include <iostream>
#include <fstream> // подключаем файлы


#include "rapidjson_min/include/rapidjson/document.h"
#include "rapidjson_min/include/rapidjson/istreamwrapper.h"

using namespace rapidjson;
using namespace std;

namespace acceltester {

class myjson {

public:
    //converter microsecond in secon
    double microsecondInSecon(int timestamp){
        return (double) timestamp / 1000000;
    }

    Document strimJson(string inFile);




};

}
