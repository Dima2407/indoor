//
// Created by  Oleksiy Grechnyev on 4/21/2017.
//

#pragma once

#include <vector>

#include "./MeshData.h"
#include "./MaskData.h"

/** @brief Calculate a mask table from a mask
 *
 * Mask consists of size integers where : 0 = white (allowed), 1 = black (forbidden)
 *
 * @param mesh     The  mesh
 * @param mask     The  mask
 * @return
 */
std::vector<int> computeMaskTbl(const MeshData & mesh, const MaskData & mask);