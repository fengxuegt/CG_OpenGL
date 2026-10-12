//
// Created by fengxuegt on 2026/9/4.
//

#ifndef PLANE_H
#define PLANE_H
#include <span>

#include "basecore.h"


class Plane {
public:
  Plane();

  Plane(std::span<const float> vertices, std::span<const unsigned int> indices);

  ~Plane();

  GLuint GetVao() {
    return mVao;
  }

  GLuint GetEbo() {
    return mEbo;
  }

  unsigned int GetIndexCount() {
    return mIndices;
  }

private:
  GLuint mVao{0};
  GLuint mEbo{0};
  unsigned int mIndices{0};
};



#endif //PLANE_H
