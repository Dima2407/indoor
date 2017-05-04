//
// Created by  Oleksiy Grechnyev on 4/21/2017.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdio>
#include <memory>

// Disable it if you don't have libpng
#define cimg_use_png

#include <CImg.h>

#include "MeshData.h"
#include "MaskData.h"
#include "computeMaskTbl.h"

using namespace std;
using namespace cimg_library;

static void showUsage(){
                          
    cout << "Usage:\n";
    cout << " maskdemo <map_file> <pixel_size> <square_size> \n";
    cout << "\n";
    cout << "map_file = Igage file with map, e.g. map1.png \n";
    cout << "Black pixels in the map are treated as obstacles. \n";
    cout << "\n";

    cout << "pixel_size (double) =  map pixels size in meters, e.g. 0.0075 \n";
    cout << "square_size(double) =  mesh square size in meters, 0.3 \n";

    exit(1);
}
//=============================================================================================
// Read an image file and create mesh and mask
static shared_ptr<CImg<unsigned char>> readImage(const char *mapFileName, 
                      double pixel,
                      double square,
                      MeshData & mesh,
                      MaskData & mask,
                      MeshData & pixelMesh) {
    
    cout << "Reading image file " << mapFileName << endl;
    //CImg<unsigned char> image(mapFileName);
    auto imagePtr = make_shared<CImg<unsigned char>>(mapFileName);
    auto const & image = *imagePtr;

    // Image parameters
    int inWidth = image.width();
    int inHeight = image.height();
    int inSize = inWidth * inHeight;
    int spectrum = image.spectrum();

    cout << "width = " << inWidth;
    cout << ",  height = " << inHeight;
    cout << ",  spectrum = " << spectrum << endl;
    
    cout << "Creating mask from the image ..." << endl;
    
    // Create mesh for pixels
    pixelMesh = MeshData(inWidth, inHeight, pixel, pixel, 0.0, 0.0);
    
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
    
    return imagePtr;
}


//=============================================================================================
// Create big map : write only, no display 
void createBigMap(const MeshData & mesh, const vector<int> & maskTbl, const MeshData & pixelMesh, shared_ptr<CImg<unsigned char>> imagePtr){
    
    auto const & image = *imagePtr;
    
    // Original image dimensions, same for bigmap and pixelMesh
    int width = image.width();
    int height = image.height();
    int size = width*height;
    int spectrum = image.spectrum();
    
    // Create the big map image
    CImg<unsigned char> bigMap(width, height, 1, 3, 0);
    
    // Copy the image into bigMap, bigMap has RGB. Loop over all PIXELS
    for (int ix=0; ix < width; ++ix)
        for (int iy=0; iy < height; ++iy) {
            
            // Check for blackness
            unsigned char tmp = 0;
            // Loop over color channels
            for (int c=0; c < spectrum; c++)
                tmp |= image(ix, iy, 0, c);
            
            // tmp == 0  if black
            tmp = tmp ? 255 : 0;
            
            // Create the black or white pixel in the RGB big map
            for (int c=0; c < spectrum; c++)
                bigMap(ix, iy, 0, c) = tmp;
        }
        
    // Now run every pixel through the mesh
    for (int ix=0; ix < width; ++ix)
        for (int iy=0; iy < height; ++iy) {
            // First, we make find mesh points
            int xm = mesh.x2ix( pixelMesh.ix2x(ix) );
            int ym = mesh.y2iy( pixelMesh.iy2y(iy) );
            
            // Then the index  = xm*ny + ym  
            int ind = mesh.index(xm, ym);
            
            // Apply the mask table to the index
            ind = maskTbl[ind];
            
            // Convert the index back to xm, ym
            xm = ind / mesh.ny;
            ym = ind % mesh.ny;
            
            // Now connvert the updated mesh (xm, ym) back to pixels
            int ix1 = pixelMesh.x2ix( mesh.ix2x(xm) );
            int iy1 = pixelMesh.y2iy( mesh.iy2y(ym) );
            
            // Make the pixel (ix1, iy1) red
            bigMap(ix1, iy1, 0, 0) = 255;
            bigMap(ix1, iy1, 0, 1) = 0;
            bigMap(ix1, iy1, 0, 2) = 0;
        }    
    // Write the result
    remove("bigmap.png");
    bigMap.save_png("bigmap.png");
    
}
//=============================================================================================
int main(int argc, char *argv[]) {

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
    
    // Pixel mesh
    MeshData pixelMesh;

    // Read image file and create mesh and mask
    auto imagePtr = readImage(mapFileName, pixelSize, squareSize, mesh, mask, pixelMesh);
    
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
    
    // Create big map : write only, no display 
    createBigMap(mesh, maskTbl, pixelMesh, imagePtr);
    
    // 2 image to display
    
    cout << "Generating the processed image \n";
    
    // The hitcount array: count the times each pixel is obtained
    vector<int> hitcount(size, 0);
    
    // Run the prefiltering for every ix, iy and fill the hitcount
    for (int ix=0; ix < width; ix++)
        for (int iy=0; iy < height; iy++) {
            int ind1 = ix*height + iy;
            int ind2 = maskTbl[ind1];
            hitcount[ind2]++; // Increase hit count for this index
        }
    
    
    // Generate the processed RGB image from the hitcount
    
    CImg<unsigned char> procImage(width, height, 1, 3, 0);
    for (int ix=0; ix < width; ix++)
        for (int iy=0; iy < height; iy++) {
            int count = hitcount[ix*height + iy];
            
            if (count > 1) {
                // Red
                procImage(ix, iy, 0, 0) = 0xff;
            } else if (count == 1) {
                // White
                procImage(ix, iy, 0, 0) = 0xff;
                procImage(ix, iy, 0, 1) = 0xff;
                procImage(ix, iy, 0, 2) = 0xff;
            }
        }
        
    cout << "Saving processed image to processed.png " << endl;
    
    remove("processed.png");
    procImage.save_png("processed.png");
    
    cout << "Finished ..." << endl;
    
    
    // New image: always RGB and with the new size
    CImg<unsigned char> newImage(width, height, 1, 3);
     for (int ix=0; ix < width; ix++)
        for (int iy=0; iy < height; iy++) {
            int ind = ix*height + iy;
            
            unsigned char color = (unsigned char) ( (mask.data[ind])==0 ? 0xff : 0);
            for (int i =0; i<3; i++)
                newImage(ix, iy, 0, i) = color;
        }
    
    CImgDisplay mainWin(newImage, "Click a point");
    CImgDisplay procWin(procImage, "Processed image");
    

    // The game loop
    while (!mainWin.is_closed() &&  !procWin.is_closed()) {
        mainWin.wait();
        if (mainWin.button()) {
            const int x = mainWin.mouse_x();
            const int y = mainWin.mouse_y();

            if (x>=0 && y>=0) {
                int ind1 = x*height + y;
                int ind2 = maskTbl[ind1];
                int xnew = ind2/height;
                int ynew = ind2 % height;
                
                // cout << "(" << x << "," << y << ") -> ("<< xnew << "," << ynew << ")" << endl;
                
                newImage(xnew, ynew, 0, 0) = 0xff;  // Red
                newImage(xnew, ynew, 0, 1) = 0x00;
                newImage(xnew, ynew, 0, 2) = 0x00;
                mainWin.display(newImage);
                //cout << "pixel(0) = " << (int)image(x, y, 0, 0) << endl;
            }

            // cout << "x = " << x << ", y = " << y << endl;

        }
    }

    return 0;
}