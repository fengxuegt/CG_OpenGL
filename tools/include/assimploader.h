//
// Created by fengxuegt on 2026/10/15.
//

#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H
#include <mesh.h>
#include <texture/include/texture.h>

#include "object.h"
#include "basecore.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class AssimpLoader {
public:
    static Object* load(const std::string &path);
private:
    static void processNode(aiNode *aiRootNode, const aiScene *aiscene, Object * rootNode, std::string &rootPath);
    static Mesh * processMesh(aiMesh *aimesh, const aiScene *aiscene, std::string &rootPath);
    static Texture* processTexture(
    const aiMaterial* aimat,
    const aiTextureType& type,
    const aiScene* scene,
    const std::string& rootPath
);
    static glm::mat4 getMat4f(aiMatrix4x4 value);
};



#endif //ASSIMPLOADER_H
