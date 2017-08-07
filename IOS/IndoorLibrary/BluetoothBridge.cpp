//
//  BluetoothBridge.cpp
//  IndoorLibrary
//
//  Created by AppleFace on 19.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#include "BluetoothBridge.h"


std::shared_ptr<Navigator::Beacons::StandardBeaconNavigator> navigator;
std::shared_ptr<Navigator::Mesh::RectanMesh> mesh;
std::shared_ptr<Navigator::Dijkstra::PointGraph> gr;
Navigator::Beacons::StandardBeaconNavigatorConfig conf;
int destinationPosition;
double mapScale;
double dictance;

extern "C"
void BluetoothBridge_init() {
    if (mesh == nullptr)
    {
        navigator = std::make_shared<Navigator::Beacons::StandardBeaconNavigator>(nullptr,true,conf);
        printf("Create Navigator");
    }
    else{
        navigator = std::make_shared<Navigator::Beacons::StandardBeaconNavigator>(mesh,true,conf);
        printf("Create Mesh Navigator");
        
    }
    
}

extern "C"
void BluetoothBridge_initBeacon(std::string uuidstr, int major, int minor, double txPower, double damp, double x, double y, double z){
    Navigator::Beacons::Beacon beacon(Navigator::Beacons::BeaconUID(uuidstr,major,minor), txPower, damp, Navigator::Math::Position3D(x,y,z), "");
    if(navigator){
    navigator->addBeacon(beacon);
    }
    
}

extern "C"
void BluetoothBridge_proces(double timestamp, std::string uuidStr, int major, int minor, double rssi) {
    Navigator::Beacons::BeaconUID uuid(uuidStr,major,minor);
    Navigator::Beacons::BeaconReceivedData brd(timestamp, uuid, rssi);
    // Process it
    if(navigator){
        navigator->process(brd);
    }
    
}
extern "C"
void BluetoothBridge_getLastPosition(double * output){
    
    
    if (BluetoothBridge_isInitialise())
    {
        
        Navigator::Math::Position3D outPos = navigator->getLastPosition();
        output[0] = outPos.x;
        output[1] = outPos.y;
        output[2] = outPos.z;
    }
    
}
extern "C"
void BluetoothBridge_createMesh(int nx, int ny, double dx, double dy, double x0, double y0){
    
    mesh = std::make_shared<Navigator::Mesh::RectanMesh>(nx, ny, dx, dy, x0, y0);
    
}

extern "C"
void BluetoothBridge_setMaskTable(const std::vector<int> &mTable){
    
    mesh->setMaskTable(mTable);
    
}
extern "C"
void BluetoothBridge_realeseMesh(){
    mesh = NULL;
}
extern "C"
void BluetoothBridge_readGraph(std::string graph, double scale ){
    mapScale = scale;
    if (gr == NULL)
    {
      
   // gr =  std::make_shared<Navigator::Dijkstra::PointGraph>(graph, scale);
        
    }
}
extern "C"
void BluetoothBridge_setDestination(IndoorPosition p ){
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
void BluetoothBridge_getPositionFromGraph(std::vector<IndoorPosition> &way){
    if (BluetoothBridge_isInitialise())
    {
        
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
                
                IndoorPosition p = {
                    .x = static_cast<double>(coordinates.x),
                    .y = static_cast<double>(coordinates.y)
                };
                way.push_back(p);
            }
            
            pointPath.swap(pointPath);
            
        }
    }
    else{
        printf("Navigator is initializing");
    }
}
extern "C"
double BluetoothBridge_getDistance(){
    
    
    return dictance;
}
extern "C"
bool BluetoothBridge_isInitialise(){
    if(navigator){
    return navigator->isInitFinished();
    }
    else{
        return false;
    }
}

extern "C"
void BluetoothBridge_getInitialisePosition(double * output){
    Navigator::Math::Position3D outPos =  navigator->getInitPosition();
    if(!std::isnan(outPos.x) && !std::isnan(outPos.y)){
        output[0] = outPos.x;
        output[1] = outPos.y;
    }
    
    
}
extern "C"
void BluetoothBridge_setConfig(bool useInit, bool use3DTrilat, bool useMapEdges, bool useMeshMask){
    conf = {};
    if (use3DTrilat)
    {
        conf.useNearest = 0;
    }
    if(useInit){
        conf.useInit = true;
    }
    conf.useMeshMask = useMeshMask;
    conf.useMapEdges = useMapEdges;
    
    printf("useInit-----%d",conf.useInit);
    printf("use3DTrilat----%d",conf.useNearest);
    printf("useMapEdges----%d",conf.useMapEdges);
    printf("useMeshMask---%d",conf.useMeshMask);
    
    
}
extern "C"
void BluetoothBridge_stop(){
    navigator = nullptr;
    
}
