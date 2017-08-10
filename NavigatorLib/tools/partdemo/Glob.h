#include <string>
#include <memory>
#include <vector>

// CImg
#define cimg_use_png
#include <CImg.h>

// Navigator
#include <Navigator.h>

/// Global data and config for PartDemo
struct Glob{
    //========= Config =======
    /// Working dir
    std::string strDir; 
    /// Pixel size
    double pixel; 
    /// Path to travel
    std::vector<Navigator::Math::Position2D> path; 
    
    //========= Map Image
    /// Map Image
    cimg_library::CImg<unsigned char> imgMap;
    /// Its size
    int width, height;
    
    //========= Meshes
    /// Pixel mesh
    std::unique_ptr<Navigator::Mesh::MeshData> pMesh;
    /// Main mesh
    std::unique_ptr<Navigator::Mesh::MeshData> mesh;
    /// RectanMesh (mesh+mask)
    std::unique_ptr<Navigator::Mesh::RectanMesh> rMesh;
    
};