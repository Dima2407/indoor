Navigator Library
======
in progress...

__Authors__: Oleksiy Grechnyev & Ivan Kuvaldin

This is a remake/refactoring of `tracking_lib`. At present the library performs bluetooth beacon
navigation (possibly can be used for wifi also):  it calculates the point position (x, y, z) from a sequence of RSSI signals.
Various filters can be applied. The complete information abouu beacons (map data) is required:
`uid`, position, `txpower` and `damp` of every beacon.

__Usage__: To use the library you have to include _Navigator.h_ and create an
instance of the class _TrilatBeaconNavigator_.  See the file `example/main.cpp` for more info. 

__Note__: 

The new library uses _BeaconUID_ (unique ID) as an arbitrary sequence of bytes, with several different
constructors (as opposed to the 8-byte hash of the old library). String+major+minor is the prefererd way
to construct an uid.

The new library returns the position (nan, nan, nan) when the location cannot be established 
(data for less than 3 active beacons available). This is different from the old librrary which gave (0, 0, 0). 
 
__Directories__:

* `src` : The library source code. Contains source files and private headers.
* `include` : The only folder to be included for user
* `lib` : This directory is for external libraries, e.g. Eigen
* `example` : A sample executable
* `unittest` : CppUnit-based unit tests for the library
* `test-tool` (`tester`, `faker`, `autotester`) : A tool for testing the library with events data
 from external _DAT_ or _JSON_ files.
* `test` : A lightweight test tool similar to `tester` 

Only `src`, `include` and `lib` are needed to use the library in your code. The `CMakeLiists.txt` file
in the `src` directory builds the library.

### Doxygen
`Doxyfile` is the *Doxygen* configuration file. It requires `DOT_PATH` and
`PLANTUML_JAR_PATH` if you want to render UML diagrams.