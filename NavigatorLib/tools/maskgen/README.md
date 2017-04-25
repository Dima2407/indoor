## `maskgen` : A simple tool for generating the mask table from a mask.

Note, if you are looking for something more fancy to work with image files, try `maskdemo`.

A _mesh_ is a rectangular mesh of points `(x, y)` given by the parameters 
`nx, ny, dx, dy, x0, y0`. Where `(nx, ny)` = mesh size, `(dx, dy)` = mesh steps in `x, y` directions,
and `(x0, y0)` = the corner with lowest values of `x, y`, typically `0, 0`.


Mesh nodes `(ix, iy)` can be numbered by the index

`index = ix*ny + iy`

where

`ix=0..nx-1, iy=0..ny-1, index = 0..nx*ny-1`
 
The `mask[index]` is an int vector with values either 1 (black, forbidden)
or 0 (white, allowed). The idea is to find nearest white node to a given node
if it is black.
 
Using mask to postprocess data is inefficient. That is why we transform mask
into a mask table. Mask table can be later used by `RectMesh` of the Navigator
library.
 
`maskTable[index]` is the index of the nearest white neighbor of site `index`. If `index` is
white, than `maskTable[index]==index`.
 
`maskgen` takes a mesh and a mask and calculates the mask table. If you want your own tool (GUI app, web app or whatever), replace
 `main.cpp` with your own implementation.

Input files (see example) : `mask.in`, `mesh.in`
Output file: `masktable.out`

Files `mask.in`, `masktable.out` has the format `data[index]` :

`data[0] ... data[nx*ny-1]`
 
 The line breaks, if any, are unimportant. Although it's nice to stick to the format
 
 (0,0) ..... (0, ny-1)
 
 (1,0) ..... (1, ny-1)
 
 (1,0) ..... (1, ny-1)
 
 ...
 
 (nx-1,0) ..... (nx-1, ny-1)
