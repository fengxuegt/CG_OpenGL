//
// Created by fengxuegt on 2026/8/27.
//

#include "shader.h"
#include <fstream>
#include <sstream>

void Shader::UseProgram() {
    glUseProgram(mProgram);
}

void Shader::SetUniform1i(const string &name, int i) {
    glUniform1i(glGetUniformLocation(mProgram, name.c_str()), i);
}

void Shader::SetUniform1f(const string &name, float f) {
    glUniform1f(glGetUniformLocation(mProgram, name.c_str()), f);
}

void Shader::SetUniformMat4(const string &name, glm::mat4 m) {
    glUniformMatrix4fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::SetUniform3fv(const string &name, glm::vec3 v) {
    glUniform3fv(glGetUniformLocation(mProgram, name.c_str()), 1, glm::value_ptr(v));
}

Shader::Shader(std::string vertexPath, std::string fragmentPath) {
    // 处理string
    std::string vertexString = FileContent(vertexPath).c_str();
    std::string fragmentString = FileContent(fragmentPath).c_str();
    const char * vertexStr = vertexString.c_str();
    const char * fragmentStr = fragmentString.c_str();

    // 顶点Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexStr, NULL);
    glCompileShader(vertexShader);
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "vertexShader: " << infoLog << std::endl;
    }


    // 片元Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentStr, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "fragmentShader: " << infoLog << std::endl;
    }

    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertexShader);
    glAttachShader(mProgram, fragmentShader);
    glLinkProgram(mProgram);
    glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(mProgram, 512, NULL, infoLog);
        std::cout << "Link Program: " << infoLog << std::endl;
    }

}

std::string Shader::FileContent(std::string path) {
    // 读取文件
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file " << path << std::endl;
        return "";
    }
    std::ostringstream contents;
    contents << file.rdbuf();
    file.close();
    return contents.str();
}
