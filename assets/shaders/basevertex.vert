#version 330 core
layout (location=0) in vec3 vPos;
layout (location=1) in vec2 vUV;
layout (location=2) in vec3 vNormal;
out vec3 fNormal;
out vec2 fUV;
uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;
uniform mat4 normalMatrix;

out vec3 worldPos;



void main() {
    vec4 transPos = model * vec4(vPos, 1.0f);
    worldPos = transPos.xyz;
    vec4 ans = perspective * view * transPos;
    gl_Position = ans;
    fUV = vUV;
    fNormal = (normalMatrix * vec4(vNormal, 1.0f)).xyz;
}
