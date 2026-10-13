//
// Created by fengxuegt on 2026/10/12.
//

#ifndef MESH_H
#define MESH_H
#include <object.h>
#include <geometry/include/geometry.h>
#include <material/include/material.h>


class Mesh : public Object {
public:
    Mesh(Geometry * geometry, Material * material);
    ~Mesh();
public:
    Geometry* mGeometry{nullptr};
    Material* mMaterial{nullptr};
};



#endif //MESH_H
