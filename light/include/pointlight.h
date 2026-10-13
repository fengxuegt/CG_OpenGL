//
// Created by fengxuegt on 2026/10/13.
//

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "object.h"

#include "light.h"


class PointLight : public Light, public Object{
public:
    PointLight();
    ~PointLight();

public:
    float mK2 = 1.0f;
    float mK1 = 1.0f;
    float mKc = 1.0f;
};



#endif //POINTLIGHT_H
