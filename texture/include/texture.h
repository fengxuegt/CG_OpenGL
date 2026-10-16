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
  static Texture* createTexture(const std::string& path, unsigned int unit);
  Texture(const std::string &path, int unitID, unsigned int internalFormat = GL_RGBA);
  Texture(unsigned int unit,
    unsigned char* dataIn,
    uint32_t widthIn,
    uint32_t heightIn
    , unsigned int internalFormat = GL_RGBA);
  static Texture* createTextureFromMemory(
  const std::string& path,
  unsigned int unit,
  unsigned char* dataIn,
  uint32_t widthIn,
  uint32_t heightIn
);
public:
  Texture(const std::string &path);
  ~Texture();

private:
  GLuint mTextureID;
  GLuint mUnitID;

  int mWidth{0};
  int mHeight{0};

  static std::map<std::string, Texture*> mTextureCache;
};



#endif //TEXTURE_H
