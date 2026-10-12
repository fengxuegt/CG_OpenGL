//
// Created by fengxuegt on 2026/8/31.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include "basecore.h"

class Texture {
public:
  void Bind(unsigned int slot = 0) const;

public:
  Texture(const std::string &path);
  ~Texture();

private:
  GLuint mTextureID;
  GLuint mUnitID;
};



#endif //TEXTURE_H
