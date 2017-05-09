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
using namespace Navigator::Dijkstra;

//===================================================
static void showUsage(){
                          
    cout << "DijkDemo : visualize routing on a graph. \n\n";
                          
    cout << "Usage:\n";
    cout << " dijkdemo <graph_file> <source> <destination> [<map_file>] \n\n";
    cout << "source and destination are vertex numbers (starting from 0) \n\n";
    
    cout << "Example : \n";
    cout << " dijkdemo graph.txt 1 6 maps\\map1.png" << endl;

    exit(-1);
}

//===================================================
/// Draw a thick line (primitive)
static void myLine(CImg<unsigned char> & img, int x1, int y1, int x2, int y2, const unsigned char *color){
    for (int i = -2; i <= 2; i++) {
        img.draw_line(x1 + i, y1, x2 + i, y2, color);
        img.draw_line(x1, y1 + i, x2, y2 + i, color);
    }
}

//===================================================
static void plotGraph(const vector<Position3D> & path, const PointGraph & pGraph, CImg<unsigned char> & img){
    const unsigned char cRed[] = {255, 0, 0};
    const unsigned char cBlue[] = {0, 0, 255};
    
    // Red : the graph
    
    const vector<Position3D> & vert = pGraph.getVertices();
    
    // Plot the vertices
    for (const Position3D & p : vert){
        int x = round(p.x);
        int y = round(p.y);
        img.draw_circle(x, y, 7, cRed);
    }
    
    // Edges
    for (int i=0; i < pGraph.getSize(); i++) {
        const Position3D & p1 = vert[i];
        int x1 = round(p1.x);
        int y1 = round(p1.y);
        
        for (const Edge & e: pGraph.getEdges()[i] ){
            const Position3D & p2 = vert[e.to];
            int x2 = round(p2.x);
            int y2 = round(p2.y);
            
            myLine(img, x1, y1, x2, y2, cRed);
        }
    }    
    
    if (path.size() < 1)
        return;
    
    // Blue : the path
    double x0 = nan("");
    double y0 = nan("");
    for (const Position3D & p : path){
        int x = round(p.x);
        int y = round(p.y);
        img.draw_circle(x, y, 8, cBlue);
        
        if (!isnan(x0)) {
            myLine(img, x0, y0, x, y, cBlue);
        }
        
        x0 = x;
        y0 = y;
    }
}
//===================================================
int main(int argc, char **argv){
    
    
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
        mapImg.assign(argv[4]); // Read from file
    
        width = mapImg.width();
        height = mapImg.height();  
        spectrum = mapImg.spectrum();        
    } else {
        width = 1000;
        height = 700;
    }
    
    // Create the Output RGB image
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
                // BW MAP : Create a grayscale RGB
                for (int c=0; c < spectrum; c++)
                    img(ix, iy, 0, c) = mapImg(ix, iy, 0, 0);
            } 
            
        }
    }
    
    // Plot the graph
    plotGraph(path, pGraph, img);
    
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