//
// Created by fengxuegt on 2026/10/12.
//

#include "render.h"

#include <phongmaterial.h>
#include <whitematerial.h>

Render::Render() {
    // 构造函数中初始化程序支持的Shader
    mPhongShader = new Shader("assets/shaders/phong.vert", "assets/shaders/phong.frag");
    mWhiteShader = new Shader("assets/shaders/white.vert", "assets/shaders/white.frag");
}

Render::~Render() {
    if (mPhongShader) {
        delete mPhongShader;
    }
}

void Render::render(Scene *scene, Camera *camera, DirectionalLight *directionallight,
    AmbientLight *ambientLight, PointLight* pointLight) {
    // 设置状态机基本状态
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 渲染物体
    RenderObject(scene, camera, directionallight, ambientLight, pointLight);
}

void Render::RenderObject(Object *object, Camera *camera, DirectionalLight *directionalLight, AmbientLight *ambientLight,
    PointLight *pointLight) {
    // if mesh
    if (object->mType == ObjectType::Mesh) {
        Mesh* mesh = static_cast<Mesh*>(object);
        Geometry *geometry = mesh->mGeometry;
        Material *material = mesh->mMaterial;
        Shader * shader = pickShader(material->mType);
        shader->UseProgram();
        switch (material->mType) {
            case MaterialType::PhongMaterial: {
                PhongMaterial *phongmaterial = (PhongMaterial*)material;

                shader->SetUniformMat4("model", mesh->GetModelMatrix());
                shader->SetUniformMat4("view", camera->getViewMatrix());
                shader->SetUniformMat4("perspective", camera->getProjectionMatrix());
                shader->SetUniformMat4("normalMatrix", glm::transpose(glm::inverse(mesh->GetModelMatrix())));
                shader->SetUniform3fv("cameraPos",camera->mPosition);
                shader->SetUniform1f("mShiness",phongmaterial->mShininess);
                shader->SetUniform1f("mSpecularIntensity", pointLight->mSpecularIntensity);
                shader->SetUniform3fv("ambient", ambientLight->mColor);
                shader->SetUniform3fv("lightColor", pointLight->mColor);
                shader->SetUniform1f("k1",pointLight->mK1);
                shader->SetUniform1f("k2",pointLight->mK2);
                shader->SetUniform1f("kc",pointLight->mKc);
                shader->SetUniform3fv("lightPosition",pointLight->mPosition);

                glBindVertexArray(geometry->getVao());
                phongmaterial->mDiffuse->Bind(0);
                shader->SetUniform1i("box", 0);
                phongmaterial->mSpecularMask->Bind(1);
                shader->SetUniform1i("boxMask", 1);
                glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, (void*)0);
                break;
            }
            case MaterialType::WhiteMaterial: {
                WhiteMaterial *whitematerial = (WhiteMaterial*)material;

                shader->SetUniformMat4("model", mesh->GetModelMatrix());
                shader->SetUniformMat4("view", camera->getViewMatrix());
                shader->SetUniformMat4("perspective", camera->getProjectionMatrix());

                glBindVertexArray(geometry->getVao());

                glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, (void*)0);
                break;
            }
            default:
                break;
        }
    }

    // child
    for (int i = 0; i < object->mChildren.size(); i++) {
        RenderObject(object->mChildren[i], camera, directionalLight, ambientLight, pointLight);
    }

}

Shader * Render::pickShader(MaterialType type) {
    Shader * ans = nullptr;
    switch (type) {
        case MaterialType::PhongMaterial:
            ans = mPhongShader;
            break;
        case MaterialType::WhiteMaterial:
            ans = mWhiteShader;
            break;
        default:
            std::cerr << "Unknown material type" << std::endl;
        break;
    }
    return ans;
}
