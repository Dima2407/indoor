//
// Created by  Oleksiy Grechnyev 
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
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
using namespace Navigator::Math;
using namespace Navigator::Mesh;

//===================================================
static void showUsage(){
                          
    cout << "MaskDemo2 : visualize existing mesh on a map. \n\n";
                          
    cout << "Usage:\n";
    cout << " maskdemo2 <mesh_file> <map_file> <pixel_size> [<masktable_file>]\n\n";
    cout << "pixel_size (double) =  map pixels size in meters, e.g. 0.007 \n";
    
    cout << "Example : \n";
    cout << " maskdemo2 results\\map1\\mesh.in maps\\map1.png 0.007 results\\map1\\masktable.out " << endl;
    cout << " maskdemo2 results\\map2\\mesh.in maps\\map2.png 0.0062 results\\map2\\masktable.out" << endl;

    exit(-1);
}
//===================================================
int main(int argc, char **argv){
    
    
    if (argc < 4 || argc > 5)
        showUsage();
    
    // Load mesh from the mesh file
    MeshData mesh(argv[1]);
    
    // Read the map image
    int width, height, spectrum;
    CImg<unsigned char> mapImg(argv[2]);
    
    width = mapImg.width();
    height = mapImg.height();  
    spectrum = mapImg.spectrum();    
    
    // Create the pixel mesh
    double pixel = atof(argv[3]);
    MeshData pixelMesh(width, height, pixel, pixel, 0.0, 0.0);
    
    // Do we use the mask ?
    int useMask = (argc == 5);
    
    // Create the Output RGB image
    CImg<unsigned char> img(width, height, 1, 3, 0);
    
    
    // Copy mapImg to img
    for (int ix=0; ix < width; ++ix)
    for (int iy=0; iy < height; ++iy) {
        
        if (spectrum >= 3 ) {
            // RGB(A) MAP : Loop over color channels
            for (int c=0; c < spectrum; c++)
                img(ix, iy, 0, c) = mapImg(ix, iy, 0, c);
        } else {
            // BW MAP : Create a grayscale RGB
            for (int c=0; c < spectrum; c++)
                img(ix, iy, 0, c) = mapImg(ix, iy, 0, 0);
        } 
    }
    
    //--------------------
    // Plot the mesh in red
    const unsigned char cRed[] = {255, 0, 0};
    const unsigned char cGreen[] = {0, 255, 0};
    for (int ix = 0; ix < mesh.nx; ++ix)
        for (int iy = 0; iy < mesh.ny; ++iy){
            // Calculate pixel x, y
            int px = pixelMesh.x2ix(mesh.ix2x(ix));
            int py = pixelMesh.y2iy(mesh.iy2y(iy));
            
            // Small red circle
            img.draw_circle(px, py, 3, cRed);
        }
        
    //----------------------
    // Allowed mesh in green if we have mask
    if (useMask) {
        RectanMesh rMesh(argv[1], argv[4]);
        const vector<int> tbl = rMesh.getMaskTable();
        for (int ix = 0; ix < mesh.nx; ++ix)
        for (int iy = 0; iy < mesh.ny; ++iy){
            int ind = ix*mesh.ny + iy;
            
            if (tbl[ind] == ind) {
            
                // Calculate pixel x, y
                int px = pixelMesh.x2ix(mesh.ix2x(ix));
                int py = pixelMesh.y2iy(mesh.iy2y(iy));
                
                // Small green circle
                img.draw_circle(px, py, 3, cGreen);
            }
        }
        
    }
    
    //--------------------
    // Save the image
    remove("output.png");
    img.save_png("output.png");
    
    // Resize if needed
    while (width > 1000 || height > 700) {
        img = img.resize_halfXY();
        width /= 2;
        height /= 2;
    }
    
    // Display the image
    CImgDisplay mainWin(img, "Dijkstra Demo");
    
    while (!mainWin.is_closed()) {
        mainWin.wait();
    }
    
    return 0;
}