//
//  SensorBridge.cpp
//  IndoorLibrary
//
//  Created by Lina Pischenko on 03.07.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#include "SensorBridge.h"
#include "BluetoothBridge.h"
std::shared_ptr<Navigator::Accel::StandardAccelNavigator> navigator;
std::shared_ptr<Navigator::Mesh::RectanMesh> mesh;
std::shared_ptr<Navigator::Accel::AccelConfig> config;
Navigator::Math::Position3D outPos;
;

extern "C"
void SensorBridge_init(double startX, double startY) {
    
    if (mesh == NULL)
    {
        navigator = std::make_shared<Navigator::Accel::StandardAccelNavigator>(nullptr,startX, startY,*config);
        printf("Create  Accel Navigator without mesh");
    }
    else{
        navigator = std::make_shared<Navigator::Accel::StandardAccelNavigator>(mesh, startX, startY, *config);
        printf("Create Mesh Accel Navigator");
    }
   
}

extern "C"
void SensorBridge_proces(double timestamp ,double ax, double ay, double az, double pitch, double yaw, double roll) {
       printf("Try AccelReceivedData" );
         printf("\n timestamp   =  %f",timestamp);
          printf("\n ax =  %f",ax);
          printf("\n ay  =   %f",ay);
         printf("\n az   =  %f",az);
         printf("\n pitch   =  %f",pitch);
          printf("\n yaw   =  %f",yaw);
        printf("\n roll   =  %f\n",roll);
    Navigator::Accel::AccelReceivedData ard{timestamp,ax,ay,az,pitch,yaw,roll};
    outPos = navigator->process(ard);
    
    
}
extern "C"
void SensorBridge_getLastPosition(double * output){
    
        output[0] = outPos.x;
        output[1] = outPos.y;
        output[2] = outPos.z;
   
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
//config->mapOrientationAngle = orientationAngle; // Map orientation angle in degrees from the server
//config->useFilter = useFilter;
}
