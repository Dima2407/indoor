#include <string>
#include <memory>

// CImg
#define cimg_use_png
#include <CImg.h>

// Navigator
#include <Navigator.h>

/// Global data and config for PartDemo
struct Glob{
    //========= Config =======
    std::string strDir; /// Working dir
    double pixel; /// Pixel size
    
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