#pragma once

#include <cmath>

/** @brief A simple class used to rescale the map, works with ints with proper ronding
 *
 * The new coord is transformed to the original one, i.e.
 * x in [0, nx-1] -> x1 in [0, w-1], same with y
 */
struct Rescaler{
    /// Constructor
    Rescaler (double scaleFactor, int inWidth, int inHeight) : sFactor(scaleFactor),
                                                               w(inWidth),
                                                               h(inHeight) {
        nx = (int) std::lround(w/sFactor);                                                           
        ny = (int) std::lround(h/sFactor);                                                           
    }
    
    /// Rescale x, the formula should translate 0 => 0 and nx-1 => w-1
    int scaleX(int x) {
        int x1 = (int) std::lround(1.0 * x * (w-1.0) / (nx-1.0));
        
        if (x1 < 0)
            x1 = 0;
        
        if (x1 > w - 1)
            x1 = w -1;
        
        return x1;
    }
    
    /// Rescale y
    int scaleY(int y) {
        int y1 = (int) std::lround(1.0 * y * (h-1.0) / (ny-1.0));
        
        if (y1 < 0)
            y1 = 0;
        
        if (y1 > h - 1)
            y1 = h -1;
        
        return y1;
    }
    
    /// The scale factor = square size/pixel size
    double sFactor;
    
    /// Width and height of the old coordinates
    int w;
    int h;
    
    /// nx and ny of the scaled coordinate system
    int nx;
    int ny;
    
};