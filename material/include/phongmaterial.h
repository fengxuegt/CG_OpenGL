//
// Created by fengxuegt on 2026/10/12.
//

#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H
#include <material.h>
#include <texture.h>


class PhongMaterial : public Material {
public:
    PhongMaterial();
    ~PhongMaterial();
public:
    Texture *mTexture{nullptr};
    float mShininess{8.0f};
};



#endif //PHONGMATERIAL_H
