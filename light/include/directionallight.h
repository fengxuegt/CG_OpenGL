//
// Created by fengxuegt on 2026/10/12.
//

#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include "light.h"


class DirectionalLight : public Light{
public:
    DirectionalLight();
    ~DirectionalLight();
public:
    glm::vec3 mDirection{-1.0f};
};



#endif //DIRECTIONALLIGHT_H
