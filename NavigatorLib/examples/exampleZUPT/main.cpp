//
// Created by Igor Maschikevich on 6/9/2017.
//
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include "rapidjson_min/include/rapidjson/document.h"
#include "Navigator.h"


// This includes everything you need

using namespace rapidjson;
using namespace std;
using Navigator::Accel::TrajectoryDetection;
using Navigator::Accel::AccelOutputData;
using Navigator::Math::Position3D;

// Test the AlgorithmZUPT
int main() {
    const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123,\"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    printf("Original JSON:\n %s\n", json);

    Document document;
    document.Parse(json);
    //    assert(document.IsObject());
    assert(document["i"].IsInt());
    cout<<document["i"].GetInt()<< endl;
    assert(document["pi"].IsDouble());
    cout<<document["pi"].GetDouble() * 2 - 1<< endl;
    cout<<document["pi"].GetDouble()<< endl;
    const Value& a = document["a"];
    assert(a.IsArray());
    for (SizeType i = 0; i < a.Size(); i++) // Uses SizeType instead of size_t
        printf("a[%d] = %d\n", i, a[i].GetInt());

    return 0;
}
