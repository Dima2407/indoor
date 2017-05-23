//
//  BluetoothBridge.cpp
//  IndoorLibrary
//
//  Created by AppleFace on 19.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#include <memory>

#include "BluetoothBridge.h"


//std::shared_ptr<Navigator::Beacons::TrilatBeaconNavigator> navigator;
 std::shared_ptr<Navigator::Beacons::StandardBeaconNavigator> navigator;
std::shared_ptr<Navigator::Mesh::RectanMesh> mesh;
std::shared_ptr<Navigator::Dijkstra::PointGraph> gr;
int destinationPosition;
double mapScale;
double dictance;

extern "C"
void BluetoothBridge_init() {
   
    if (mesh == NULL)
    {
        navigator = std::make_shared<Navigator::Beacons::StandardBeaconNavigator>(nullptr,true);
        printf("Create simple Navigator");
    }
    else{
        navigator = std::make_shared<Navigator::Beacons::StandardBeaconNavigator>(mesh,true);
        printf("Create Mesh Navigator");
    }
        
    
    ///<::Beacons::TrilatBeaconNavigator> (rssiFact, distFact);

    
}

extern "C"
void BluetoothBridge_initBeacon(std::string uuidstr, int major, int minor, double txPower, double damp, double x, double y, double z){
    Navigator::Beacons::Beacon beacon(Navigator::Beacons::BeaconUID(uuidstr,major,minor), txPower, damp, Navigator::Math::Position3D(x,y,z), "");
    
   navigator->addBeacon(beacon);
    
}

extern "C"
void BluetoothBridge_proces(double timestamp, std::string uuidStr, int major, int minor, double rssi) {
    Navigator::Beacons::BeaconUID uuid(uuidStr,major,minor);
    Navigator::Beacons::BeaconReceivedData brd(timestamp, uuid, rssi);
    
    // Process it
    navigator->process(brd);
  
    
}
extern "C"
void BluetoothBridge_getLastPosition(double * output){
Navigator::Math::Position3D outPos = navigator->getLastPosition();
    output[0] = outPos.x;
    output[1] = outPos.y;
    output[2] = outPos.z;
}
extern "C"
void BluetoothBridge_createMesh(int nx, int ny, double dx, double dy, double x0, double y0){
    
    mesh = std::make_shared<Navigator::Mesh::RectanMesh>(nx, ny, dx, dy, x0, y0);
    
}

extern "C"
void BluetoothBridge_setMaskTable(const std::vector<int> &mTable){
    
    mesh -> setMaskTable(mTable);
    
}
extern "C"
void BluetoothBridge_realeseMesh(){
    mesh = NULL;
}
extern "C"
void BluetoothBridge_readGraph(std::string graph, double scale ){
    mapScale = scale;
    gr =  std::make_shared<Navigator::Dijkstra::PointGraph>(graph, scale);
}
extern "C"
void BluetoothBridge_setDestination(struct position p ){
     printf("Set destination  x-%f, y-%f,",p.x, p.y);
    if (gr==NULL)
    {
        printf("Set graph first");
    }
    else{
     destinationPosition = gr->findNearestVertex(Navigator::Math::Position3D(p.x, p.y,0));
       
    }
}

extern "C"
void BluetoothBridge_getPositionFromGraph(std::vector<position> &way){
    if (destinationPosition == 0)
    {
        printf("Set destination first ");
    }
    else{
    std::vector<Navigator::Math::Position3D> pointPath;
        Navigator::Math::Position3D lastPosition = navigator->getLastPosition();
        lastPosition.x = lastPosition.x / mapScale;
        lastPosition.y = lastPosition.y / mapScale;
        
    int startVertext = gr->findNearestVertex(Navigator::Math::Position3D(navigator->getLastPosition()));
    dictance =  gr->dijkstraP(startVertext, destinationPosition, pointPath);
        
    for (int i = 0; i < pointPath.size(); i++) {
        Navigator::Math::Position3D coordinates = pointPath[i];

         position p = {
            .x = static_cast<double>(coordinates.x),
            .y = static_cast<double>(coordinates.y)
        };
        way.push_back(p);
    }

    pointPath.swap(pointPath);
    
    }
}
extern "C"
double BluetoothBridge_getDistance(){
    
 
    return dictance;
}
