//
// Created by fengxuegt on 2026/10/12.
//

#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H
#include "material.h"
#include "texture.h"


class PhongMaterial : public Material {
public:
    PhongMaterial();
    ~PhongMaterial();
public:
    Texture *mDiffuse{nullptr};
    Texture *mSpecularMask{nullptr};
    float mShininess{1.0f};
};



#endif //PHONGMATERIAL_H
