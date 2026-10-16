//
// Created by fengxuegt on 2026/10/15.
//

#include "assimploader.h"

#include <tools.h>
#include "phongmaterial.h"

Object * AssimpLoader::load(const std::string &path) {
    // 获取文件名之前的路径
    auto lastIndex = path.find_last_of("/\\");
    auto rootPath = path.substr(0, lastIndex);

    std::cout << "Loading " << rootPath << std::endl;


    // 首先读取模型文件
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);
    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }
    Object *rootNode = new Object();
    processNode(scene->mRootNode, scene, rootNode, rootPath);
    return rootNode;
}

void AssimpLoader::processNode(aiNode *aiRootNode, const aiScene *aiscene, Object *rootNode, std::string &rootPath) {
    Object * node = new Object();
    rootNode->addChild(node);

    glm::mat4 localMatrix = getMat4f(aiRootNode->mTransformation);
    glm::vec3 position, eulerAngle, scale;
    Tools::decompose(localMatrix, position, eulerAngle, scale);
    node->SetPosition(position);
    node->SetAngleX(eulerAngle.x);
    node->SetAngleY(eulerAngle.y);
    node->SetAngleZ(eulerAngle.z);
    node->SetScale(scale);

    // 处理完当前ainode所含的mesh
    for (int i = 0; i < aiRootNode->mNumMeshes; i++) {
        int meshID = aiRootNode->mMeshes[i];
        aiMesh *aimesh = aiscene->mMeshes[meshID];
        auto mesh = processMesh(aimesh, aiscene, rootPath);
        node->addChild(mesh);
    }

    // 处理children
    for (int i = 0; i < aiRootNode->mNumChildren; i++) {
        aiNode *child = aiRootNode->mChildren[i];
        processNode(child, aiscene, node, rootPath);
    }


}

Mesh * AssimpLoader::processMesh(aiMesh *aimesh, const aiScene *aiscene, std::string &rootPath) {
    std::vector<float> positions;
    std::vector<float> normals;
    std::vector<float> uvs;
    std::vector<unsigned int> indices;

    // VBO info
    for (int i = 0; i < aimesh->mNumVertices; i++) {
        // position
        positions.push_back(aimesh->mVertices[i].x);
        positions.push_back(aimesh->mVertices[i].y);
        positions.push_back(aimesh->mVertices[i].z);

        // normals
        normals.push_back(aimesh->mNormals[i].x);
        normals.push_back(aimesh->mNormals[i].y);
        normals.push_back(aimesh->mNormals[i].z);

        // uvs
        // 关注第一张贴图
        if (aimesh->mTextureCoords[0]) {
            uvs.push_back(aimesh->mTextureCoords[0][i].x);
            uvs.push_back(aimesh->mTextureCoords[0][i].y);
        } else {
            uvs.push_back(0);
            uvs.push_back(0);
        }
    }

    // EBO info
    for (int i = 0; i < aimesh->mNumFaces; i++) {
        aiFace aiface = aimesh->mFaces[i];
        for (int j = 0; j < aiface.mNumIndices; j++) {
            indices.push_back(aiface.mIndices[j]);
        }
    }

    auto geometry = new Geometry(positions, normals, uvs, indices);
    auto material = new PhongMaterial();
    material->mShininess = 32;

    // 贴图处理
    if (aimesh->mMaterialIndex >= 0) {
        Texture * texture = nullptr;
        aiMaterial *aimaterial = aiscene->mMaterials[aimesh->mMaterialIndex];
        texture = processTexture(aimaterial, aiTextureType_DIFFUSE, aiscene, rootPath);
        if (texture == nullptr) {
            texture = Texture::createTexture("assets/textures/box.png", 0);
        }
        Texture *specularTexture = Texture::createTexture("assets/textures/sp_mask.png", 1);
        material->mDiffuse = texture;
        material->mSpecularMask = specularTexture;
    }

    return new Mesh(geometry, material);

}

Texture * AssimpLoader::processTexture(const aiMaterial *aimat, const aiTextureType &type, const aiScene *scene,
    const std::string &rootPath) {
    // 处理贴图
    Texture * texture = nullptr;
    aiString aipath;
    aimat->Get(AI_MATKEY_TEXTURE(type, 0), aipath);
    if (!aipath.length) {
        std::cerr << "no texture" << std::endl;
        return nullptr;
    }
    const aiTexture *aitexture = scene->GetEmbeddedTexture(aipath.C_Str());
    if (aitexture) {
        unsigned char* dataIn = reinterpret_cast<unsigned char *>(aitexture->pcData);
        uint32_t widthIn = aitexture->mWidth;
        uint32_t heightIn = aitexture->mHeight;
        texture = Texture::createTextureFromMemory(aipath.C_Str(), 0, dataIn, widthIn, heightIn);
    } else {
        std::string path = rootPath + "/" + aipath.C_Str();
        std::cout << "Texture path " << path << std::endl;
        texture = Texture::createTexture(path.c_str(), 0);
    }
    return texture;
}

glm::mat4 AssimpLoader::getMat4f(aiMatrix4x4 value) {
//     glm::mat4 to(
//     value.a1, value.a2, value.a3, value.a4,
//     value.b1, value.b2, value.b3, value.b4,
//     value.c1, value.c2, value.c3, value.c4,
//     value.d1, value.d2, value.d3, value.d4
// );

    glm::mat4 to(
    value.a1, value.b1, value.c1, value.d1,
    value.a2, value.b2, value.c2, value.d2,
    value.a3, value.b3, value.c3, value.d3,
    value.a4, value.b4, value.c4, value.d4
);

    return to;
}
