//
// Created by Igor Maschikevich on 6/22/2017.
//

#include <iostream>
#include <fstream> // подключаем файлы
//////#include <cmath>
//////#include <cassert>

#include "rapidjson_min/include/rapidjson/document.h"
#include "rapidjson_min/include/rapidjson/istreamwrapper.h"

using namespace rapidjson;
using namespace std;

namespace acceltester {



//converter microsecond in secon
double microsecondInSecon(int timestamp)
{

    return (double) timestamp / 1000000;

}


Document strimJson (std::string inFile);


}

