//
// Created by fengxuegt on 2026/8/31.
//

#include "texture.h"

#include <iostream>
#include <ostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Texture::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
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

Texture::~Texture() {
}
