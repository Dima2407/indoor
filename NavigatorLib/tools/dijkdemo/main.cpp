//
// Created by  Oleksiy Grechnyev 
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <memory>

// CImg
// Disable it if you don't have libpng
#define cimg_use_png

#include <CImg.h>

// Navigator
#include "Navigator.h"


using namespace std;
using namespace cimg_library;

static void showUsage(){
                          
    cout << "Usage:\n";
    cout << " dijkdemo <graph_file> <source> <destination> [<map_file>] \n\n";
    cout << "source and destination are vertex numbers (starting from 0) \n";

    exit(-1);
}

//===================================================
int main(int argc, char **argv){
    using namespace std;
    using namespace Navigator::Math;
    using namespace Navigator::Dijkstra;
    
    
    if (argc < 4 || argc > 5)
        showUsage();
    
    // Read the graph from file and calculate the path
    cout << "Reading graph from file " << argv[1] << endl;
    PointGraph pGraph(argv[1]);
    int source = atoi(argv[2]);
    int dest = atoi(argv[3]);
    
    vector<Position3D> path;
    cout << "dist = " << pGraph.dijkstraP(source, dest, path) << endl;
    
    cout << "\nPath : \n";
    for (const Position3D & p : path){
        cout << p.x << " " << p.y << endl;
    }
    
    //=========================================================
    cout << "Creating image ..." << endl;
    
    int width, height, spectrum;
    CImg<unsigned char> mapImg;
    if (5 == argc) {
        mapImg =  CImg<unsigned char>(argv[4]); // Read from file
    
        width = mapImg.width();
        height = mapImg.height();  
        spectrum = mapImg.spectrum();        
    } else {
        width = 1000;
        height = 900;
    }
    
    // Output RGB image
    CImg<unsigned char> img(width, height, 1, 3, 0);
    
    if (5 == argc) {
        // Copy mapImg to img
        
        for (int ix=0; ix < width; ++ix)
        for (int iy=0; iy < height; ++iy) {
            
            if (spectrum >= 3 ) {
                // RGB(A) MAP : Loop over color channels
                for (int c=0; c < spectrum; c++)
                    img(ix, iy, 0, c) = mapImg(ix, iy, 0, c);
            } else {
                // BW MAP :
                for (int c=0; c < spectrum; c++)
                    img(ix, iy, 0, c) = mapImg(ix, iy, 0, 0);
            } 
            
        }
    }
    
    return 0;
}