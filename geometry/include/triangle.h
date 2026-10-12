//
// Created by fengxuegt on 2026/8/28.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <span>

#include "basecore.h"


class Triangle {
public:
    GLuint GetVao() {
        return mVao;
    }
    GLuint GetEbo() {
        return mEbo;
    }
    unsigned int GetIndexCount() {
        return mIndices;
    }


public:
    Triangle();
    Triangle(std::span<const float> vertices, std::span<const unsigned int> indices);
    ~Triangle();


private:
    GLuint mVao{0};
    GLuint mEbo{0};
    unsigned int mIndices{0};
};



#endif //TRIANGLE_H
