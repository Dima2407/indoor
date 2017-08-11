//
// Created by  Oleksiy Grechnyev 
//
// Particle Filter demo

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <random>
#include <ctime>

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
using namespace Navigator::Particles;

//=========================================
/// Read config, map, mesh
static void readAll(Glob &glob){
     
    // read config 
    ifstream in(glob.strDir + "/config.in");
    in >> glob.pixel;
    while (true) {
        Position2D p;
        if (!(in >> p.x >> p.y)) 
            break;
        glob.path.push_back(p);
    }
        
    in.close();
    
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
static int pixelX(Glob &glob, const Position2D & p){
    return glob.pMesh->x2ix(p.x);
}
//=========================================
static int pixelY(Glob &glob, const Position2D & p){
    return glob.pMesh->y2iy(p.y);
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
    
    const unsigned char cRed[] = {0xff, 0, 0};
    const unsigned char cGreen[] = {0, 0xff, 0};
    const unsigned char cBlue[] = {0, 0, 0xff};
    
    /*
    // Display the mesh+mask as a test
    for (int ix=0; ix<glob.mesh->nx; ++ix)
    for (int iy=0; iy<glob.mesh->ny; ++iy) {
        // Red dot
        Position2D p(glob.mesh->ix2x(ix), glob.mesh->iy2y(iy));
        glob.imgMap.draw_circle(pixelX(glob, p), pixelY(glob, p), 2, cRed);
        // Green dot
        p = glob.rMesh->process(p);
        glob.imgMap.draw_circle(pixelX(glob, p), pixelY(glob, p), 2, cGreen);
    }
    */
    
    CImg<unsigned char> imgFrame; // Each frame in turn
    CImgDisplay mainWin(glob.imgMap, "Particle Filter"); // Create window
    
    // Seeded random engine
    mt19937 randomEngine(time(nullptr));
    
    // The particle filter
    ParticleFilter pFilter;
    
    // Plot the path
    Position2D p1, p1old, p2, p2old; 
    auto gaussB = normal_distribution<double>(0.0, 1.0);
    auto gaussA = normal_distribution<double>(0.0, 0.2);
    for (int i = 0; i < glob.path.size(); ++i) {
        p1 = glob.path[i];
        // Display the red (exact) path
        glob.imgMap.draw_circle(pixelX(glob, p1), pixelY(glob, p1), 2, cRed);
        if (i > 0)
            glob.imgMap.draw_line(pixelX(glob, p1old), pixelY(glob, p1old), 
                pixelX(glob, p1), pixelY(glob, p1), cRed);
        p1old = p1;        
                
        // Calculate the simulated BLE position (exact + error)        
        Position2D pB = p1;
        pB.x += gaussB(randomEngine);
        pB.y += gaussB(randomEngine);
        
        // Calculate the simulated ACC delta with random noise
        Position2D delta;
        if (i==0) {
            delta = {0, 0};
        } else {
            delta = p1 - p1old;
            delta.x *= 1.0 + gaussA(randomEngine);
            delta.y *= 1.0 + gaussA(randomEngine);
        }
        
        // Run the Particle filter
        /*
        auto meshCorrect = [&glob](const Position2D &p)->Position2D{
            return glob.rMesh->process(p);
        };
        auto allowMove = [&glob](const Position2D &p1, const Position2D &p2) -> bool {
            return  glob.rMesh->checkWall(p1.x, p1.y, p2.x, p2.y);
        };
        
        if (i==0) {
            pFilter.initialize(pB, meshCorrect);
            p2 = pB;
        } else {
            p2 = pFilter.process(delta, pB, allowMove, meshCorrect);
        }*/
        
        p2 = pB; // For now only !
        
        // Display the green (calculated) path
        glob.imgMap.draw_circle(pixelX(glob, p2), pixelY(glob, p2), 2, cGreen);
        if (i > 0)
            glob.imgMap.draw_line(pixelX(glob, p2old), pixelY(glob, p2old), 
                pixelX(glob, p2), pixelY(glob, p2), cGreen);
        p2old = p2;    
        
        // Calculate and Display particles
        imgFrame.assign(glob.imgMap);  // Copy to frame
        
        /*
        // Get particles from the filter
        const vector<Position2D> & particles = pFilter.getParticles();
        */
        
        // Simulated particles
        vector<Position2D> particles;
        for (int j=0; j<20; ++j) {
            Position2D p = p1;
            p.x += gaussB(randomEngine)/2;
            p.y += gaussB(randomEngine)/2;
            particles.push_back(p);
        }
        
        // Draw particles
        for (auto & p : particles) {
            int ix = pixelX(glob, p);
            int iy = pixelY(glob, p);
            imgFrame.draw_circle(ix, iy, 1, cBlue);
        }
        
        // Display the frame        
        mainWin.display(imgFrame); // Display the image
        this_thread::sleep_for(chrono::milliseconds(200));      
        
        /*mainWin.wait();
        while (!mainWin.is_key())
            mainWin.wait();*/
    }
    
    mainWin.wait();    
    while (!mainWin.is_closed() && !mainWin.is_key()) {
        mainWin.wait();
        /*
        // Create new points on-screen if needed
        if (mainWin.button()&1) {
            Position2D p(glob.pMesh->ix2x(mainWin.mouse_x()), glob.pMesh->iy2y(mainWin.mouse_y()));
            cout << p.x << " " << p.y << endl;
        } 
        */        
    }
    
    return 0;
}