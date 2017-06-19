//
// Created by  Oleksiy Grechnyev on 4/21/2017.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdio>

// Disable it if you don't have libpng
#define cimg_use_png

#include <CImg.h>

#include "MeshData.h"
#include "MaskData.h"
#include "computeMaskTbl.h"


static void showUsage(){
                          
    using namespace std;
    
    
    cout << "Usage:\n";
    cout << " maskgen2 <map_file> <pixel_size> <square_size> \n";
    cout << "\n";
    cout << "map_file = Igage file with map, e.g. maps/map1.png \n";
    cout << "Black pixels in the map are treated as obstacles. \n";
    cout << "\n";

    cout << "pixel_size (double) =  map pixels size in meters, e.g. 0.007 \n";
    cout << "square_size(double) =  mesh square size in meters, 0.3 \n";
    
    cout << "Examples : \n";
    cout << " maskgen2 maps\\map1.png 0.007  0.3\n";
    cout << " maskgen2 maps\\map2.png 0.0062 0.3" << endl;

    exit(1);
}
//=============================================================================================
// Read an image file and create mesh and mask
static void readImage(const char *mapFileName, 
                      double pixel,
                      double square,
                      MeshData & mesh,
                      MaskData & mask) {
                          
    using namespace std;
    using namespace cimg_library;
    
    
    cout << "Reading image file " << mapFileName << endl;
    CImg<unsigned char> image(mapFileName);

    // Image parameters
    int inWidth = image.width();
    int inHeight = image.height();
    int inSize = inWidth * inHeight;
    int spectrum = image.spectrum();

    cout << "width = " << inWidth;
    cout << ",  height = " << inHeight;
    cout << ",  spectrum = " << spectrum << endl;
    
    cout << "Creating mask from the image ..." << endl;
    
    // Create the rescaler
    // Rescaler res(square/pixel, inWidth, inHeight);
    
    // Create mesh for pixels
    MeshData pixelMesh = MeshData(inWidth, inHeight, pixel, pixel, 0.0, 0.0);
    
    // Rescaling is done as (nxNew -1)* square = (inWidth - 1) * pixel
    const int nxNew = round(1.0 + pixel*(inWidth-1.0)/square);
    const int nyNew = round(1.0 + pixel*(inHeight-1.0)/square);
    
    
    // Create mesh and mask for the rescaled size
    mesh = MeshData(nxNew, nyNew, square, square, 0.0, 0.0);
    mask = MaskData(mesh.nx * mesh.ny); 
    
    // Write the mesh
    ofstream mout("mesh.in");
    mout << mesh.nx << " " << mesh.ny << " ";
    mout << mesh.dx << " " << mesh.dy << " ";
    mout << mesh.x0 << " " << mesh.y0 << "    ";
    mout << "   # nx ny dx dy x0 y0 \n";
    mout.close();
    
    
    // Fill the mask from the input image
    for (int ix=0; ix < mesh.nx; ++ix)
        for (int iy=0; iy < mesh.ny; ++iy) {
            int ind = ix*mesh.ny + iy;
            
            // x, y  rescaled to pixels
            int x1 = pixelMesh.x2ix(mesh.ix2x(ix));
            int y1 = pixelMesh.y2iy(mesh.iy2y(iy));
            
            // Check for blackness
            unsigned char tmp = 0;
            // Loop over color channels
            for (int c=0; c < spectrum; c++)
                tmp |= image(x1, y1, 0, c);
            
            // Now tmp==0 only if the pixel is black
            // Mask valuue 1 is for black pixels
            mask.data[ind] = ( tmp == 0) ? 1 : 0;
        }
        
    // Write the mask
    ofstream maout("mask.in");
    for (int i=0; i< mesh.nx*mesh.ny ; i++)
        maout << mask.data[i] << "\n";
    
    maout.close();
}


//=============================================================================================
int main(int argc, char *argv[]) {
    using namespace std;
    using namespace cimg_library;

    if (argc != 4) 
        showUsage();

    // Parse arguments
    const char * mapFileName = argv[1];
    double pixelSize = atof(argv[2]);
    double squareSize = atof(argv[3]);

    if (pixelSize <= 1.e-4 || pixelSize > 100 ||
        squareSize <= 1.e-4 || squareSize > 100)
         showUsage();
    
    
    // Create mesh and mask
    MeshData mesh;

    MaskData mask;

    // Read image file and create mesh and mask
    readImage(mapFileName, pixelSize, squareSize, mesh, mask);
    
    int width = mesh.nx;
    int height = mesh.ny;
    int size = width * height;
    
    cout << "Rescaled size:  ";
    cout << "width = " << width << ", height = " << height << "\n";
    
    cout << "Calculating the mask table ...\n";
    
    // Calculate the mask table from the mask
    vector<int> maskTbl = computeMaskTbl(mesh, mask);
    
    // Write the mask table
    ofstream out("masktable.out");
    cout << "Writing mask table to file masktable.out \n";
    
    /* for (int ix = 0; ix < width; ++ix) {
        for (int iy = 0; iy < height; ++iy) {
            out << setfill(' ') << setw(4) << maskTbl[mesh.index(ix, iy)] << " ";
        }
        out << endl;
    } */
    for (int i = 0; i < width*height; ++i)
        out << setfill(' ') << setw(3) << maskTbl[i] << "\n";
    
    out.close();
    
    // That's all for maskgeg2, maskdemo had more stufff here

    return 0;
}
