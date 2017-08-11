//
//  SensorBridge.cpp
//  IndoorLibrary
//
//  Created by Lina Pischenko on 03.07.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#include "SensorBridge.h"
#include "BluetoothBridge.h"
Navigator::Accel::StandardAccelNavigator *nv = NULL;
std::shared_ptr<Navigator::Mesh::RectanMesh> mesh;
Navigator::Accel::AccelConfig config;
std::shared_ptr<Navigator::Dijkstra::PointGraph> gr;
int destinationPosition;
double mapScale;
double dictance;


extern "C"
void SensorBridge_init(double startX, double startY) {
    printf("\nstartX - %f",startX);
    printf("\nstartY - %f",startY);
    nv = new Navigator::Accel::StandardAccelNavigator(mesh, startX, startY, config);
    printf("\nCreate Mesh Accel Navigator");
    
}

extern "C"
void SensorBridge_process(double timestamp ,double ax, double ay, double az, double pitch, double yaw, double roll) {
    Navigator::Accel::AccelReceivedData ard{
        
        .timestamp = timestamp,
        .ax = ax,
        .ay = ay,
        .az = az,
        .pitch = pitch,
        .yaw = yaw,
        .roll= roll};
    if( nv != NULL){
        nv->process(ard);
    }
    
    
}
extern "C"
void SensorBridge_getLastPosition(double * output){
    if(nv != NULL){
        Navigator::Math::Position3D outPos = nv->getLastPosition();
        output[0] = outPos.x;
        output[1] = outPos.y;
    }
    
}
extern "C"
void SensorBridge_createMesh(double nx, double ny, double dx, double dy, double x0, double y0){
    mesh = std::make_shared<Navigator::Mesh::RectanMesh>(nx, ny, dx, dy, x0, y0);
    printf("setMesh");
}
extern "C"
void SensorBridge_readGraph(std::string graph, double scale ){
    mapScale = scale;
    if (gr == NULL)
    {
    //gr =  std::make_shared<Navigator::Dijkstra::PointGraph>(graph, scale);
    }
}
extern "C"
void SensorBridge_setMaskTable(const std::vector<int> &mTable){
    mesh->setMaskTable(mTable);
    printf("mTable");
}
extern "C"
void SensorBridge_setAccelConfig(int orientationAngle, bool useFilter, bool useMapEdges,bool useWalls,bool useMeshMask){
    printf("setConfig\n");
    printf("orientationAngle-----%d\n",orientationAngle);
    printf("useMapEdges----%d\n",useMapEdges);
    printf("useWalls----%d\n",useWalls);
    printf("useMeshMask---%d\n",useMeshMask);
    config = {};
    config.mapOrientationAngle = orientationAngle; // Map orientation angle in degrees from the server
    config.useFilter = true;
    config.useMapEdges = useMapEdges;
    config.useWalls = useWalls;
    config.useMeshMask = useMeshMask;

    
    
}
extern "C"
void SensorBridge_getPositionFromGraph(std::vector<position> &way){
    if (BluetoothBridge_isInitialise())
    {
        
        if (destinationPosition == 0)
        {
            printf("Set destination first ");
        }
        else{
            std::vector<Navigator::Math::Position3D> pointPath;
            Navigator::Math::Position3D lastPosition = nv->getLastPosition();
            lastPosition.x = lastPosition.x / mapScale;
            lastPosition.y = lastPosition.y / mapScale;
            
            int startVertext = gr->findNearestVertex(Navigator::Math::Position3D(nv->getLastPosition()));
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
    else{
        printf("Navigator is initializing");
    }
}

extern "C"
void SensorBridge_setDestination(struct position p ){
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
void SensorBridge_stop(){
    nv = nullptr;
    
}
