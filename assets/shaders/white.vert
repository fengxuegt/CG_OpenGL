#version 330 core
layout (location=0) in vec3 vPos;
layout (location=1) in vec2 vUV;
layout (location=2) in vec3 vNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

void main() {
    vec4 ans = perspective * view * model * vec4(vPos, 1.0f);
    gl_Position = ans;
}
