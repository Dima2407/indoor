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
std::shared_ptr<Navigator::Accel::AccelConfig> config;
;
;

extern "C"
void SensorBridge_init(double startX, double startY) {
    
    if (mesh == NULL)
    {
        nv = new Navigator::Accel::StandardAccelNavigator(nullptr,startX, startY,*config);
        printf("\nCreate  Accel Navigator without mesh");
    }
    else{
        nv = new Navigator::Accel::StandardAccelNavigator(nullptr, startX, startY, *config);
        printf("\nCreate Mesh Accel Navigator");
    }
   
}

extern "C"
void SensorBridge_proces(double timestamp ,double ax, double ay, double az, double pitch, double yaw, double roll) {
    
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
        Navigator::Math::Position3D outPos = nv->getLastPositon();
        output[0] = outPos.x;
        output[1] = outPos.y;
        
    }
   
}
extern "C"
void SensorBridge_createMesh(int nx, int ny, double dx, double dy, double x0, double y0){
    
    mesh = std::make_shared<Navigator::Mesh::RectanMesh>(nx, ny, dx, dy, x0, y0);
    
}

extern "C"
void SensorBridge_setMaskTable(const std::vector<int> &mTable){
      printf("Try setMaskTable");
    mesh -> setMaskTable(mTable);
     printf(" setMaskTable");
}
extern "C"
void SensorBridge_setAccelConfig(int orientationAngle, bool useFilter){
    config = std::make_shared<Navigator::Accel::AccelConfig>();
config->mapOrientationAngle = orientationAngle; // Map orientation angle in degrees from the server
config->useFilter = useFilter;
}
