## `maskdemo` : Generate mesh and mask table from a map image file (like `map.png`)

# Usage

maskdemo <map_file> <pixel_size> <square_size>

Where:

`map_file` = Igage file with map, e.g. `map.png`
Black pixels in the map are treated as obstacles.

`pixel_size` (double) =  map pixels size in meters, e.g. 0.0075
`square_size` (double) =  mesh square size in meters, 0.3

It scales the image by factor (`square_size/pixel_size`) to a new (typically smaller) dimensions and creates `mesh.in`
and `masktable.out` for the new dimension. Watch out for small features disappearing after scaling!

See `maskgen` doc for general info on mesh, mask and mask table.

This program requires libpng, it also
needs to link gdi32 or X11 library respectively (you'll need to change CMakeLists.txt for Linux).

This is not final production utility, that will be maskgen2, the truncated version of this.