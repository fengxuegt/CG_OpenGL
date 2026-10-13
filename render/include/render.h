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

#include "ambientlight.h"
#include "directionallight.h"


class Render {
public:
    Render();
    ~Render();

    void render(const std::vector<Mesh*>& meshes, Camera* camera, DirectionalLight* directionallight, AmbientLight* ambientLight, PointLight* pointLight);
public:
    Shader *mPhongShader{nullptr};
    Shader *mWhiteShader{nullptr};

private:
    Shader * pickShader(MaterialType type);
};



#endif //RENDER_H
