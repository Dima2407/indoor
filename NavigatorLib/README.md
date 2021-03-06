Navigator Library
======
in progress... See `example3` for the latest stuff.

__Authors__: Oleksiy Grechnyev & Ivan Kuvaldin

This is a remake/refactoring of `tracking_lib`. At present the library performs bluetooth beacon
navigation (possibly can be used for WiFi also):  it calculates the point position (x, y, z) from 
a sequence of RSSI signals.
Various filters can be applied. The complete information about beacons (map data) is required:
`uid`, position, `txpower` and `damp` of every beacon. Position post-processing using mesh
and a mask table is implemented.

Calibration routines are also included.

The library is rewritten almost from scratch, only parts of the trilateration routines of the
old `tracking_lib` are used.

__Build__: Directories `src`, `include` and `lib` contain the library source code. To build the library 
(`libNavigator.a`) with
`CMake` use  the `CMakeLists.txt` file in the `src` directory. If you're in the directory `indoor-sdk/NavigatorLib` ,
type in bash/cmd:

mkdir build

cd build

cmake ../src

cmake --build .

__Build__ __everything__: To build everything (library + example + tests + test-tool) with CMake type
(requires `CppUnit`):

mkdir build

cd build

cmake ..

cmake --build .


__Usage__: To use the library you have to add the `indoor-sdk/NavigatorLib/include` directory
 to your incluude path. Then include _Navigator.h_ and create`` an
instance of class _StandardBeaconNavigator_, see `example 3`.   _StandardBeaconNavigator_ is 
trialteration + mesh post-processing + standard settings (Android vs iOS) + 5 second Init Phase combined.

See `example1`,  `example2` for info on _TrilatBeaconNavigator_ (trilateratiion only no mesh, custom settings). 
See `exampleCalibrate` for info on calibration. 
For the mesh+mask post-processing, see `exampleMesh1`, `exampleMesh2`.
For the Dijkstra routing, see `exampleDijkstra` and `dijktool`.

__Note__: 

The new library uses _BeaconUID_ (unique ID) as an arbitrary sequence of bytes, with several different
constructors (as opposed to the 8-byte hash of the old library). String+major+minor is the prefererd way
to construct an `UID`.

The new library returns the position (nan, nan, nan) when the location cannot be established 
(data for less than 3 active beacons available). This is different from the old librrary which gave (0, 0, 0). 
 
__Directories__:

* `src` : The library source code. Contains source files and private headers.
* `include` : The only folder to be included for user
* `lib` : This directory is for external libraries, e.g. Eigen
* `examples` : Examples
* `tools` : Tools, includes `maskgen`, `maskgen2`, `maskdemo`, `maskdemo2` at present, which generates mask table from a black/white mask or a PNG file.
        Also `dijkdemo` for visualizing Dijkstra routing.
* `unittest` : CppUnit-based unit tests for the library
* `test-tool` (`tester`, `faker`, `autotester`) : A tool for testing the library with events data
 from external _DAT_ or _JSON_ files.
* `test` : A lightweight test tool similar to `tester` (by Ivan Kuvaldin)

### Doxygen
`Doxyfile` is the *Doxygen* configuration file. It requires `DOT_PATH` and
`PLANTUML_JAR_PATH` if you want to render UML diagrams.