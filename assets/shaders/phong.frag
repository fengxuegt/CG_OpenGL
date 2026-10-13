#version 330 core
in vec3 fNormal;
in vec2 fUV;
out vec4 FragColor;
uniform sampler2D box;
uniform sampler2D boxMask;

in vec3 worldPos;

uniform vec3 lightDirection;
uniform vec3 lightColor;

// point light
uniform vec3 lightPosition;
uniform float k1;
uniform float k2;
uniform float kc;

uniform float mShiness;
uniform float mSpecularIntensity;

uniform vec3 ambient;

uniform vec3 cameraPos;
void main() {
    // 通用光照属性
    // 物体颜色
    vec3 objectColor = texture(box, fUV).xyz;
    // 法线
    vec3 normalN = normalize(fNormal);
    // 光线方向
    vec3 normalL = normalize(worldPos - lightPosition);

    // 计算diffuse颜色
    float diffuse = clamp(dot(-normalL, normalN), 0, 1);
    vec3 diffuseColor = lightColor * objectColor * diffuse;

    // 计算衰减
    float dist = length(worldPos - lightPosition);
    float attenuation = 1.0f / (k2 * dist * dist + k1 * dist + kc);

    vec3 viewDirN = normalize(worldPos - cameraPos);
    vec3 lightReflectN = normalize(reflect(normalL, normalN));
    float specular = clamp(dot(lightReflectN, -viewDirN), 0, 1);
    specular = pow(specular, mShiness);

    float flag = step(0, dot(-normalL, fNormal));
    float mask = texture(boxMask, fUV).r;

    vec3 specularColor = lightColor  * specular * flag * mSpecularIntensity * mask;
    vec3 ambientColor = objectColor * ambient;

    FragColor = vec4((diffuseColor + specularColor)*attenuation + ambientColor, 1);
}