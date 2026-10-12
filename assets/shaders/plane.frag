#version 330 core
in vec3 fColor;
in vec2 fUV;
out vec4 FragColor;
uniform sampler2D sampler;
void main() {
//    FragColor = texture(sampler, fUV);
//    float average = (FragColor.r + FragColor.g + FragColor.b) / 3.0;
//    FragColor = vec4(average, average, average, 1.0);
    FragColor = texture(sampler, fUV);

}