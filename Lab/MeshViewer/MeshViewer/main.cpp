#define GLEW_STATIC
#include <GL\glew.h>
#include <glfw\glfw3.h>
#include <glm\glm.hpp>
#include <iostream>
#include <vector>

#include "Shader.h"
#include "GLwindow.h"
#include "GLRenderSystem.h"
#include "Camera.h"
#include "Viewport.h"
#include "Cube.h"
#include "Mesh.h"
#include "Scene.h"
#include "SimpleAstlReader.h"
#include "FileDialog.h"

GLRenderSystem* renderSystemPtr;
Viewport* viewportPtr;
GLWindow* windowPtr;
Scene* scenePtr;
Shader* unlitShaderPtr;

ButtonCode lastMouse = ButtonCode::UNKNOWN;

void AddModelFormFile()
{
    char filePath[1000];
    if (FileDialog::getPath(filePath))
    {
        std::cout << "Opening file..." << std::endl;
        try
        {
            scenePtr->addMesh(new Mesh(SimpleAstlReader::getVertices(filePath), false, glm::vec3(0.8f, 0.9f, 1)));
            std::cout << "File loaded successfully" << std::endl;
        }
        catch (const std::exception & ex)
        {
            std::cout << "Invalid file!" << std::endl;
            std::cout << "Error code: " << ex.what() << std::endl;
        }
    }
    else
    {
        std::cout << "Canceled..." << std::endl;
    }
}

void selectTarget(double xPos, double yPos)
{
    GLRenderSystem::clearDisplay(0.0f, 0.0f, 0.0f);
    GLRenderSystem& rs = *renderSystemPtr;
    Scene& scene = *scenePtr;

    Shader* lastUsed = rs.getShaderProgram();
    rs.setShaderProgram(*unlitShaderPtr);

    for (int i = 0; i < scene.getMeshCount(); i++)
    {
        rs.setIsDefaultColor(false);
        rs.setCustomColor(glm::vec3((float)(i+1)/scene.getMeshCount(), 1.0f, 1.0f));
        rs.setWorldMatrix(scene[i].calcWorldMatrix());
        rs.renderTriangleSoup(scene[i].getVao(), scene[i].getVertexCount());
    }

    GLfloat* color = new GLfloat[3];
    glReadPixels(xPos, windowPtr->getHeigth() - yPos, 1, 1, GL_RGB, GL_FLOAT, color);

    rs.setShaderProgram(*lastUsed);

    int id = (int)glm::roundEven(color[0] * scene.getMeshCount() - 1);
    std::cout << "Selected id: " << id << std::endl;
    if (id >= 0)
    {
        scene.setSelectionId(id);
        viewportPtr->getCamera().updateTarget(scene.getCurrentSelection().getWorldPosition());
    }
}

void onMouseButtonCallback(ButtonCode buttonCode, Action action, Modifier, double xPos, double yPos) {
    if (action == Action::Press)
    {
        if (buttonCode == ButtonCode::Left)
        {
            selectTarget(xPos, yPos);
        }
        glfwSetInputMode(windowPtr->getGLFWHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        lastMouse = buttonCode;
    }
    else if (action == Action::Release)
    {
        glfwSetInputMode(windowPtr->getGLFWHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        lastMouse = ButtonCode::UNKNOWN;
    }
}

void onKeyCallback(KeyCode key, Action act, Modifier mods)
{
    float moveSpeed = 0.1f;
    Camera& cam = viewportPtr->getCamera();
    
    if (act == Action::Press)
    {
        if (key == KeyCode::O && mods == Modifier::Control)
        {
            AddModelFormFile();
        }
        else if (key == KeyCode::C && mods == Modifier::Alt)
        {
            scenePtr->addMesh(new Mesh(QUBE));
        }

        switch(key)
        {
        case KeyCode::F1:
            cam.setFrontView();
            break;
            
        case KeyCode::F2:
            cam.setRightView();
            break;
            
        case KeyCode::F3:
            cam.setRearView();
            break;
            
        case KeyCode::F4:
            cam.setLeftView();
            break;
            
        case KeyCode::F5:
            cam.setBottomView();
            break;
            
        case KeyCode::F6:
            cam.setTopView();
            break;
            
        case KeyCode::F7:
            cam.setIsoView();
            break;

        case KeyCode::F8:
            viewportPtr->setParallelProjection(!viewportPtr->isParalellProjection());
            break;
        }
    }
}

void onCursorCallback(double xPos, double yPos)
{
    Camera& cam = viewportPtr->getCamera();
    
    const float sens = 0.2f;
    static double lastX(xPos), lastY(xPos);

    double  deltaX = xPos - lastX;
    double deltaY = yPos - lastY;

    lastX = xPos;
    lastY = yPos;
    
    if (lastMouse == ButtonCode::Right)
    {
        cam.rotate(cam.getTarget(), cam.calcRight(), sens * -deltaY);
        cam.rotate(cam.getTarget(), glm::cross(cam.calcForward(), cam.calcRight()), sens * deltaX);
        //std::cout << deltaX << " " << deltaY << std::endl;
    }
    else if (lastMouse == ButtonCode::Left && scenePtr->getCurrentSelectionId() >= 0)
    {
        scenePtr->getCurrentSelection().rotate(cam.calcRight(), sens * deltaY);
        scenePtr->getCurrentSelection().rotate(glm::cross(cam.calcForward(), cam.calcRight()), sens * -deltaX);
    }
}

void onScrollCallback(double xOffset, double yOffset)
{
    Camera& camera = viewportPtr->getCamera();
    const float rotationSpeed = 0.2f;

    camera.setDistnceToTarget(glm::abs(camera.distanceFromEyeToTarget() + yOffset * rotationSpeed));
}

int main()
{
    glfwInit();
    glewInit();

    GLWindow window("Ultimate 8D Viewer", 1280, 720);
    windowPtr = &window;

    Viewport viewport;
    viewportPtr = &viewport;

    viewport.setViewportSize(window.getWidth(), window.getHeigth());
    viewport.getCamera().setEyeTargetUp(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    window.setKeyCallback(onKeyCallback);
    window.setCursorPosCallback(onCursorCallback);
    window.setMouseCallback(onMouseButtonCallback);
    window.setScrollCallback(onScrollCallback);

    GLRenderSystem::init();
    GLRenderSystem rs;
    rs.setupLight(glm::vec3(100, 100, 100), 0.4f, 0.5f, 0.6f);
    renderSystemPtr = &rs;

    Scene scene(glm::vec3(2, 0, 0));
    scenePtr = &scene;

    Shader phongShader = Shader("../../shaders/phong/PhongVertexShader.glsl", "../../shaders/phong/PhongFragmentShader.glsl");
    Shader unlitShader = Shader("../../shaders/unlit/vertexShader.glsl", "../../shaders/unlit/fragmentShader.glsl");
    unlitShaderPtr = &unlitShader;
    rs.setShaderProgram(phongShader);

    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window.getGLFWHandle()))
    {
        glfwWaitEvents();
        rs.setViewport(0, 0, window.getWidth(), window.getHeigth());
        GLRenderSystem::clearDisplay(0.2f, 0.2f, 0.2f);

        rs.setViewMatrix(viewport.getCamera().calcViewMatrix());
        rs.setProjMatrix(viewport.calcProjectionMatrix());
        rs.setCameraPos(viewport.getCamera().getEye());

        for (int i = 0; i < scene.getMeshCount(); i++)
        {
            glm::vec3 selectionColor = glm::vec3(0.9f, 0.6f, 0.7f);

            rs.setIsDefaultColor(scene.getCurrentSelectionId() == i ? false : scene[i].isColorDefault());
            rs.setCustomColor(scene.getCurrentSelectionId() == i ? selectionColor : scene[i].getColor());
            rs.setWorldMatrix(scene[i].calcWorldMatrix());
            rs.renderTriangleSoup(scene[i].getVao(), scene[i].getVertexCount());
        }

        glfwSwapBuffers(window.getGLFWHandle());
    }

    glfwTerminate();
}
