//
// Created by  Oleksiy Grechnyev on 4/21/2017.
//

#include <iostream>

#include <CImg.h>

#include "MeshData.h"
#include "MaskData.h"
#include "computeMaskTbl.h"

int main(int argc, char *argv[]) {
    using namespace std;
    using namespace cimg_library;

    if (argc != 2) {
        cout << "Usage: maskdemo <image file> \n";
        return 1;
    }


    cout << "Reading image file " << argv[1] << endl;
    CImg<unsigned char> image(argv[1]);

    int width = image.width();
    int height = image.height();
    int size = width*height;
    int spectrum = image.spectrum();


    cout << "width = " << width << endl;
    cout << "height = " << height << endl;
    cout << "spectrum = " << spectrum << endl;


    cout << "Processing image ..." << endl;
    
    // Create mesh and mask
    MeshData mesh(width, height, 1.0, 1.0, 0.0, 0.0);

    MaskData mask(size);
    
    
    // Fill the mask from the input image
    for (int ix=0; ix < width; ix++)
        for (int iy=0; iy < height; iy++) {
            int ind = ix*height + iy;
            // Uses red channel for color images, 1 = forbidden in the mask
            mask.data[ind] = (image(ix, iy, 0, 0) == 0) ? 1 : 0;
        }
    
    cout << "Calculating the mask table ...\n";
    
    
    // Calculate the mask table from the mask
    vector<int> maskTbl = computeMaskTbl(mesh, mask);
    
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
    
    CImg<unsigned char> procImage(width, height, 1, 3);
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
    
    procImage.save_png("processed.png");
    
    cout << "Finished ..." << endl;
    
    
    // New image: always RGB
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