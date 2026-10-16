//
// Created by fengxuegt on 2026/8/31.
//

#include "texture.h"

#include <iostream>
#include <ostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
std::map<std::string, Texture*> Texture::mTextureCache{};
void Texture::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}

Texture * Texture::createTexture(const std::string &path, unsigned int unit) {
    auto it = mTextureCache.find(path);
    if (it != mTextureCache.end()) {
        return it->second;
    }
    auto texture = new Texture(path, unit, GL_SRGB_ALPHA);
    mTextureCache[path] = texture;
    return texture;
}

Texture::Texture(const std::string &path, int unitID, unsigned int internalFormat) {
    mUnitID = unitID;
    int width, height;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    auto image_data = stbi_load(path.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha); // unsigned char * data
    if (!image_data) {
        std::cerr << "Failed to load image: " << path << std::endl;
    }

    glGenTextures(1, &mTextureID);
    glActiveTexture(GL_TEXTURE0 + mUnitID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 设置过滤形式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 设置过滤形式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    stbi_image_free(image_data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::Texture(const std::string &path) {
    const char * filePath = path.c_str();
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char * data = stbi_load(filePath, &width, &height, &channels, STBI_rgb_alpha);
    if (!data) {
        std::cerr << "Failed to load image: " << filePath << std::endl;
        return;
    }
    std::cout << "Loaded texture file format: " << channels << std::endl;
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}
Texture::Texture(unsigned int unit, unsigned char *dataIn, uint32_t widthIn, uint32_t heightIn, unsigned int internalFormat) {
    mUnitID = unit;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    uint32_t dataInSize = 0;
    if (!heightIn) {
        dataInSize = widthIn;
    } else {
        dataInSize = widthIn * heightIn * 4;
    }
    unsigned char *data = stbi_load_from_memory(dataIn, dataInSize, &mWidth, &mHeight, &channels, STBI_rgb_alpha);
    glGenTextures(1, &mTextureID);
    glActiveTexture(GL_TEXTURE0 + mUnitID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}
Texture * Texture::createTextureFromMemory(const std::string &path, unsigned int unit, unsigned char *dataIn,
    uint32_t widthIn, uint32_t heightIn) {
    auto it = mTextureCache.find(path);
    if (it != mTextureCache.end()) {
        return it->second;
    }
    auto texture = new Texture(unit, dataIn, widthIn, heightIn, GL_SRGB_ALPHA);
    mTextureCache[path] = texture;
    return texture;
}

Texture::~Texture() {
}
