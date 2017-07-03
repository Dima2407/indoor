//
// Created by Igor Maschikevich on 6/22/2017.
//

#include "myjson.h"
#include <fstream> // подключаем файлы
#include "rapidjson_min/include/rapidjson/document.h"
#include "rapidjson_min/include/rapidjson/istreamwrapper.h"
namespace acceltester {

Document myjson::strimJson(string inFile)
{
    ifstream in(inFile);
    IStreamWrapper isw(in);
    Document document;
    document.ParseStream(isw);
    in.close();
    return document;
}

}
