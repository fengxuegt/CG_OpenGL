//
// Created by fengxuegt on 2026/8/27.
//

#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include "basecore.h"
using namespace std;


class Shader {
public:
    void UseProgram();
    void SetUniform1i(const string &name, int i);
    void SetUniform1f(const string &name, float f);
    void SetUniformMat4(const string &name, glm::mat4 m);
    void SetUniform3fv(const string &name, glm::vec3 v);
public:
    Shader(std::string vertexPath, std::string fragmentPath);
    ~Shader();
private:
    std::string FileContent(std::string path);

private:
    GLuint mProgram{0};

};



#endif //SHADER_H
