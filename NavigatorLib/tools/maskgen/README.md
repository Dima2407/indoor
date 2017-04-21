A simple tool for generating the mask table from a mask

If a rectangular mesh has size nx*ny, then we use index

index = ix*ny + iy

where

ix=0..nx-1, iy=0..ny-1, index = 0..nx*ny-1
 
The mask[index] is and int vector with values either 1 (black, forbidden)
 or 0 (white, allowed).
 
`maskgen` takes a mesh and a mask and calculates the mask table
  
maskTable[index] = index of the nearest white neighbor of site `index`. If `index` is
white, than maskTable[index]=index.

