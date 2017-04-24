//
// Created by  Oleksiy Grechnyev on 4/21/2017.
//

#pragma once

#include "./MeshData.h"
#include "./MaskData.h"

/** @brief Find the nearest white node to the given black node ix0, iy0
 *
 * The order of serach is important if there are several nodes at the same distance
 * The order is smallest ix, then smallest iy
 *
 * @param[in] mesh    The input mesh data
 * @param[in] mask    The input B/W mask
 * @param[in] ix
 * @param[in] iy
 * @return             Index (ix*ny + iy) of the nearest white node
 */
int findNearest(const MeshData & mesh, const MaskData & mask, int ix0, int iy0);