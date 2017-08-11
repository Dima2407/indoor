//
//  KalmanBridge.cpp
//  IndoorLibrary
//
//  Created by Lina Pischenko on 09.08.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#include "KalmanBridge.hpp"
std::shared_ptr<Navigator::Beacons::KalmanBeaconNavigator> kalmanNavigator;
std::shared_ptr<Navigator::Mesh::RectanMesh> mesh;
std::shared_ptr<Navigator::Dijkstra::PointGraph> gr;
Navigator::Beacons::KalmanBeaconNavigatorConfig conf;
Navigator::Math::Kalman::KalmanConfig filterConfig;
int destinationPosition;
double mapScale;
double dictance;

extern "C"
void KalmanBridge_init() {
    if (mesh == nullptr)
    {
        kalmanNavigator = std::make_shared<Navigator::Beacons::KalmanBeaconNavigator>(nullptr,conf);
        printf("Create Kalman Navigator");
    }
    else{
         Navigator::Math::Kalman::KalmanConfig filterConfig;
        kalmanNavigator = std::make_shared<Navigator::Beacons::KalmanBeaconNavigator>(mesh,conf,filterConfig);
        printf("Create Kalman Mesh Navigator");
        
    }
    
}

extern "C"
void KalmanBridge_initBeacon(std::string uuidstr, int major, int minor, double txPower, double damp, double x, double y, double z){
    Navigator::Beacons::Beacon beacon(Navigator::Beacons::BeaconUID(uuidstr,major,minor), txPower, damp, Navigator::Math::Position3D(x,y,z), "");
  
    if(kalmanNavigator){
        
        kalmanNavigator->addBeacon(beacon);
    }
    
}


extern "C"
void KalmanBridge_process( const std::vector<Navigator::Beacons::BeaconReceivedData> beacons) {
    // Process it
    if(kalmanNavigator){
       
       kalmanNavigator->process(beacons);
    }
    
}
extern "C"
void KalmanBridge_getLastPosition(double * output){
    
    
    if (KalmanBridge_isInitialise())
    {
        
        Navigator::Math::Position3D outPos = kalmanNavigator->getLastPosition();
        output[0] = outPos.x;
        output[1] = outPos.y;
        output[2] = outPos.z;
    }
    
}
extern "C"
void KalmanBridge_createMesh(int nx, int ny, double dx, double dy, double x0, double y0){
    
    mesh = std::make_shared<Navigator::Mesh::RectanMesh>(nx, ny, dx, dy, x0, y0);
    
}

extern "C"
void KalmanBridge_setMaskTable(const std::vector<int> &mTable){
    
    mesh->setMaskTable(mTable);
    
}
extern "C"
void KalmanBridge_realeseMesh(){
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
void KalmanBridge_setDestination(kalmanPosition p ){
    if (gr==NULL)
    {
        printf("Set graph first");
    }
    else{
        destinationPosition = gr->findNearestVertex(Navigator::Math::Position3D(p.x, p.y,0));
        
    }
}

extern "C"
void KalmanBridge_getPositionFromGraph(std::vector<kalmanPosition> &way){
    if (KalmanBridge_isInitialise())
    {
        
        if (destinationPosition == 0)
        {
            printf("Set destination first ");
        }
        else{
            std::vector<Navigator::Math::Position3D> pointPath;
            Navigator::Math::Position3D lastPosition = kalmanNavigator->getLastPosition();
            lastPosition.x = lastPosition.x / mapScale;
            lastPosition.y = lastPosition.y / mapScale;
            
            int startVertext = gr->findNearestVertex(Navigator::Math::Position3D(kalmanNavigator->getLastPosition()));
            dictance =  gr->dijkstraP(startVertext, destinationPosition, pointPath);
            
            for (int i = 0; i < pointPath.size(); i++) {
                Navigator::Math::Position3D coordinates = pointPath[i];
                
                kalmanPosition p = {
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
double KalmanBridge_getDistance(){
    
    
    return dictance;
}
extern "C"
bool KalmanBridge_isInitialise(){
    if(kalmanNavigator !=NULL)
    {
        return kalmanNavigator->isInitFinished();
    }
    else{
        return false;
    }
}

extern "C"
void KalmanBridge_getInitialisePosition(double * output){
    if (KalmanBridge_isInitialise())
    {
    Navigator::Math::Position3D outPos =  kalmanNavigator->getLastPosition();
    if(!std::isnan(outPos.x) && !std::isnan(outPos.y)){
        output[0] = outPos.x;
        output[1] = outPos.y;
    }
    }
    
}
extern "C"
void KalmanBridge_setConfig(bool useInit, bool use3DTrilat, bool useMapEdges, bool useMeshMask){
    conf = {};
    if (use3DTrilat)
    {
        conf.useNearest = 0;
    }
    conf.useMeshMask = useMeshMask;
    conf.useMapEdges = useMapEdges;
    
    
    
}
extern "C"
void KalmanBridge_stop(){
    kalmanNavigator = nullptr;
    
}
