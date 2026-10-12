//
// Created by fengxuegt on 2026/10/12.
//

#ifndef LIGHT_H
#define LIGHT_H
#include "basecore.h"


class Light {
public:
    Light();
    ~Light();
public:
    glm::vec3 mColor{1.0f};
    float mSpecularIntensity{1.0f};
};



#endif //LIGHT_H
