#version 330 core
in vec3 fNormal;
in vec2 fUV;
out vec4 FragColor;
uniform sampler2D asuna;

in vec3 worldPos;

uniform vec3 lightDirection;
uniform vec3 lightColor;

uniform float mShiness;
uniform float mSpecularIntensity;

uniform vec3 ambient;

uniform vec3 cameraPos;
void main() {
    vec3 objectColor = texture(asuna, fUV).xyz;
    vec3 normalN = normalize(fNormal);
    vec3 normalL = normalize(lightDirection);
    float diffuse = clamp(dot(-normalL, normalN), 0, 1);
    vec3 diffuseColor = lightColor * objectColor * diffuse;

    vec3 viewDirN = normalize(worldPos - cameraPos);
    vec3 lightReflectN = normalize(reflect(lightDirection, normalN));
    float specular = clamp(dot(lightReflectN, -viewDirN), 0, 1);
    specular = pow(specular, mShiness);

    float flag = step(0, dot(-lightDirection, fNormal));

    vec3 specularColor = lightColor  * specular * flag * mSpecularIntensity;
    vec3 ambientColor = objectColor * ambient;

    FragColor = vec4(diffuseColor + specularColor + ambientColor, 1);
}