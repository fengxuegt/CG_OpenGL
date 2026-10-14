//
// Created by fengxuegt on 2026/10/12.
//

#ifndef RENDER_H
#define RENDER_H
#include <shader.h>
#include <camera.h>
#include <material.h>
#include <mesh.h>
#include <pointlight.h>
#include <scene.h>

#include "ambientlight.h"
#include "directionallight.h"


class Render {
public:
    Render();
    ~Render();
    // 最初Render函数版本
    void render(Scene *scene, Camera* camera, DirectionalLight* directionallight, AmbientLight* ambientLight, PointLight* pointLight);

    // 添加Scene版本
    void RenderObject(Object* object, Camera* camera, DirectionalLight* directionalLight, AmbientLight* ambientLight, PointLight* pointLight);


public:
    Shader *mPhongShader{nullptr};
    Shader *mWhiteShader{nullptr};

private:
    Shader * pickShader(MaterialType type);
};



#endif //RENDER_H
