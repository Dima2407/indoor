//
// Created by  Oleksiy Grechnyev 
//
// Particle Filter demo

#include <iostream>
#include <fstream>
#include <string>

// CImg
#define cimg_use_png
#include <CImg.h>

// Navigator
#include <Navigator.h>

#include "./Glob.h"

using namespace std;
using namespace cimg_library;
using namespace Navigator::Math;
using namespace Navigator::Mesh;

//=========================================
/// Read config, map, mesh
static void readAll(Glob &glob){
     
    // read config 
    ifstream in1(glob.strDir + "/config.in");
    in1 >> glob.pixel;
    in1.close();
    
    // read map image
    string strMap = glob.strDir + "/map.png";
    glob.imgMap.assign(strMap.c_str());
    glob.width = glob.imgMap.width();
    glob.height = glob.imgMap.height();  
    int spectrum = glob.imgMap.spectrum();  
    if (spectrum !=3)
        throw runtime_error("Not an RGB image !");
    // Resize to fit on a typical screen
    while (glob.width > 1200 || glob.height > 800) {
        glob.imgMap = glob.imgMap.resize_halfXY();
        glob.width /= 2;
        glob.height /= 2;
        glob.pixel*=2;
    }
    // Set up the pixel mesh
    glob.pMesh = make_unique<MeshData>(glob.width, glob.height, glob.pixel, glob.pixel, 0.0, 0.0);
    
    // Load mesh+mask
    glob.mesh = make_unique<MeshData>(glob.strDir + "/mesh.in");
    glob.rMesh = make_unique<RectanMesh>(glob.strDir + "/mesh.in", glob.strDir + "/masktable.out");
}
//=========================================
static int pixelX(Glob &glob, Position2D p){
    return glob.mesh.x2ix(p.x);
}
//=========================================
static int pixelY(Glob &glob, Position2D p){
    return glob.mesh.y2iy(p.y);
}
//=========================================
int main(int argc, char *argv[]){
    cout << "partdemo: Particle Filter Demo" << endl;
    
    if (argc < 2) {
        cout << "Usage : partdemo <data.dir>" << endl;
        return 1;
    }
    
    Glob glob; // Global data
    glob.strDir = argv[1];
    
    readAll(glob);
    
    // Display mesh = test
    
    
   
    // Display the image
    CImgDisplay mainWin;
    mainWin.assign(glob.imgMap, "Particle Demo");
    
    while (!mainWin.is_closed()) {
        mainWin.wait();
    }
    
    return 0;
}