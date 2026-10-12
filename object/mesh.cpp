//
// Created by fengxuegt on 2026/10/12.
//

#include "mesh.h"

Mesh::Mesh(Geometry *geometry, Material *material) {
    mGeometry = geometry;
    mMaterial = material;
}

Mesh::~Mesh() {
    if (mGeometry) {
        delete mGeometry;
    }
    if (mMaterial) {
        delete mMaterial;
    }
}
