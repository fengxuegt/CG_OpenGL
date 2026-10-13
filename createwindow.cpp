#include <cameracontrol.h>
#include <geometry.h>
#include <iostream>
#include <material.h>
#include <mesh.h>
#include <perspectivecamera.h>
#include <phongmaterial.h>
#include <plane.h>
#include <pointlight.h>
#include <render.h>
#include <shader.h>
#include <texture.h>
#include <triangle.h>
#include <vector>
#include <whitematerial.h>

#include "basecore.h"
#include "gamecameracontrol.h"
#include "trackballcameracontrol.h"
#define WIDTH 800
#define HEIGHT 600

// camera
Camera *camera = nullptr;
CameraControl *cameraControl = nullptr;

GLuint vao = 0;
GLuint planeVao = 0;
Shader * shader = nullptr;
Shader * planeShader = nullptr;
Geometry *sphere = nullptr;
Plane * plane = nullptr;
GLuint colorAttachment = 0;
DirectionalLight * directionalLight = nullptr;
PointLight * pointLight = nullptr;
AmbientLight * ambientLight = nullptr;

GLuint fbo = 0;

std::vector<Mesh*> meshes;

void prepareGeometry() {
    /*
     *      0 --------- 3
     *      |           |
     *      |           |
     *      |           |
     *      1 --------- 2
     **/
    float verticesPlane[] = {
        // position            // color          // uv
        -1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // 0
        -1.0f, -1.0f, 0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // 1
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // 2
         1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f  // 3
    };
    unsigned int indicesPlane[] = {
        0, 1, 2,
        0, 2, 3
    };
    plane = new Plane(verticesPlane, indicesPlane);
    planeVao = plane->GetVao();


}
void prepare() {
    sphere = Geometry::createBox(2);
    vao = sphere->getVao();
    PhongMaterial * material = new PhongMaterial();
    Texture *box = new Texture("assets/textures/box.png");
    Texture * boxMask = new Texture("assets/textures/sp_mask.png");
    material->mDiffuse = box;
    material->mSpecularMask = boxMask;
    material->mShininess = 16.0f;
    auto mesh = new ::Mesh(sphere, material);
    meshes.push_back(mesh);

    // point light
    auto pointlightge = Geometry::createSphere(0.5f);
    auto whiteMaterial = new WhiteMaterial();
    auto pointmesh = new Mesh(pointlightge, whiteMaterial);
    pointmesh->SetPosition(glm::vec3(4.0f, 0.0f,0.0f));
    meshes.push_back(pointmesh);

    planeShader = new Shader("assets/shaders/plane.vert", "assets/shaders/plane.frag");
}
void prepareLight() {
    glm::vec3 lightDirection = glm::normalize(glm::vec3(-0.3f, -0.5f, -1.0f));
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    directionalLight = new DirectionalLight();
    ambientLight = new AmbientLight();
    directionalLight->mColor = lightColor;
    directionalLight->mDirection = lightDirection;
    directionalLight->mSpecularIntensity = 2.0f;
    ambientLight->mColor = glm::vec3(0.1f, 0.1f, 0.1f);

    // point light
    pointLight = new PointLight();
    pointLight->mColor = lightColor;
    pointLight->SetPosition(glm::vec3(4.0f, 0.0f,0.0f));
	pointLight->mK2 = 0.017f;
	pointLight->mK1 = 0.07f;
	pointLight->mKc = 1.0f;

}

void prepareFramebuffer(int width, int height) {
    // framebuffer
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // color attachment
    // GLuint colorAttachment = 0;
    glGenTextures(1, &colorAttachment);
    glBindTexture(GL_TEXTURE_2D, colorAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // attach
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);

    // depth stencil attachment
    GLuint depthStencilAttachment = 0;
    glGenTextures(1, &depthStencilAttachment);
    glBindTexture(GL_TEXTURE_2D, depthStencilAttachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // attach
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthStencilAttachment, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        return;
    }

}
// callback
void frameSizeCallback(GLFWwindow * window, int width, int height) {
    std::cout << width << " " << height << std::endl;
    if (height == 0) {
        return;
    }

    glViewport(0, 0, width, height);

    auto perspectiveCamera = dynamic_cast<PerspectiveCamera*>(camera);
    if (perspectiveCamera != nullptr) {
        perspectiveCamera->setAspect((float)width / (float)height);
    }
}
void keyCallBack(GLFWwindow * window, int key, int scancode, int action, int mods) {
    std::cout << key << " " << scancode << " " << action << " " << mods << std::endl;
    cameraControl->onKey(key, action, mods);
}
void mouseButtonCallBack(GLFWwindow * window, int button, int action, int mods) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    cameraControl->onMouse(button, action, x, y);
}
void cursorPositionCallBack(GLFWwindow * window, double xpos, double ypos) {
    cameraControl->onCursor(xpos, ypos);
}
void scrollCallback(GLFWwindow * window, double xoffset, double yoffset) {
    cameraControl->onScroll(yoffset);
}
// SetCallback
void SetCallBack(GLFWwindow * window) {
    glfwSetFramebufferSizeCallback(window, frameSizeCallback);
    glfwSetKeyCallback(window, keyCallBack);
    glfwSetMouseButtonCallback(window, mouseButtonCallBack);
    glfwSetCursorPosCallback(window, cursorPositionCallBack);
    glfwSetScrollCallback(window, scrollCallback);
}

// camera
void PrepareCamera() {
    camera = new PerspectiveCamera(60.0f, (float)WIDTH/ (float)HEIGHT, 0.1f, 1000.0f);
    cameraControl = new GameCameraControl();
    // cameraControl = new TrackBallCameraControl();
    cameraControl->setCamera(camera);
    cameraControl->setSensitivity(0.4f);
    ((GameCameraControl*)cameraControl)->setSpeed(0.1f);
}

void Transform() {
    // glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    // glm::vec3 newPos = glm::mat3(rotate * pointLight->GetModelMatrix()) * pointLight->mPosition;
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(sin(glfwGetTime()) * 0.5, 0.0f, 0.0f));
    const glm::vec3 pointLightInitialPosition(4.0f, 0.0f, 0.0f);
    float offsetX =
        std::sin(static_cast<float>(glfwGetTime())) * 2.f;
    glm::vec3 newPos =
        pointLightInitialPosition +
        glm::vec3(offsetX, 0.0f, 0.0f);
    pointLight->SetPosition(newPos);
    meshes[1]->SetPosition(newPos);
}

int main() {


    glfwInit();
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    PrepareCamera();
    SetCallBack(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    int framebufferWidth;
    int framebufferHeight;
    glfwGetFramebufferSize(
        window,
        &framebufferWidth,
        &framebufferHeight
    );

    prepareGeometry();
    prepareFramebuffer(framebufferWidth, framebufferHeight);
    prepare();
    prepareLight();

    // 设置渲染状态
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);


    Render * render = new Render();
    while (!glfwWindowShouldClose(window)) {
        cameraControl->update();


        // pass 1
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        // glViewport(0, 0, WIDTH, HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Transform();
        render->render(meshes, camera, directionalLight, ambientLight, pointLight);


        // pass 2
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, framebufferWidth, framebufferHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        planeShader->UseProgram();
        planeShader->SetUniform1i("sampler", 0);

        glBindVertexArray(planeVao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorAttachment);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, plane->GetIndexCount(), GL_UNSIGNED_INT, (void*)0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

/*
 * 先清屏,然后再交换缓冲区,然后再处理窗口事件
 *
 *
 *
 *
 *
 *
 *
 *
 */
