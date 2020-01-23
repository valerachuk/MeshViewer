#define GLEW_STATIC
#include <GL\glew.h>
#include <glfw\glfw3.h>
#include <glm\glm.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "Shader.h"
#include "GLwindow.h"
#include "GLRenderSystem.h"
#include "Camera.h"
#include "Viewport.h"
#include "Cube.h"
#include "Mesh.h"
#include "Scene.h"
#include "SimpleAstlReader.h"

GLRenderSystem* renderSystemPtr;
Viewport* viewportPtr;
GLWindow* windowPtr;
Scene* scenePtr;
Shader* unlitShaderPtr;

ButtonCode lastMouse = ButtonCode::UNKNOWN;

void AddModelFormFile()
{
    char filePath[MAX_PATH];
    if (!GLWindow::requestFilePath(filePath))
    {
        std::cout << "Canceled..." << std::endl;
        return;
    }
    std::cout << "Opening file..." << std::endl;
    try
    {
        SimpleAstlReader reader(filePath);
        std::shared_ptr<Buffer> buffer(new Buffer(reader.getVertices()));

        scenePtr->addMesh(std::unique_ptr<Mesh>(new Mesh(buffer)));
        std::cout << "File loaded successfully" << std::endl;
    }
    catch (const std::exception & ex)
    {
        std::cout << "Invalid file - " << filePath << std::endl;
        std::cout << "Error code: " << ex.what() << std::endl;
    }

}

void selectTarget(float xPos, float yPos)
{
    GLRenderSystem::clearDisplay(0.0f, 0.0f, 0.0f);
    GLRenderSystem& rs = *renderSystemPtr;
    Scene& scene = *scenePtr;

    Shader* lastUsed = rs.getShaderProgram();
    rs.setShaderProgram(*unlitShaderPtr);

    RenderMode lastMode = renderSystemPtr->getRenderMode();
    renderSystemPtr->setRenderMode(RenderMode::Triangles);

    for (int i = 0; i < scene.getMeshCount(); i++)
    {
        rs.setIsDefaultColor(false);
        rs.setCustomColor(glm::vec3((float)(i+1)/scene.getMeshCount(), 1.0f, 1.0f));
        rs.setWorldMatrix(scene[i].calcWorldMatrix());
        rs.render(scene[i].getBuffer().getVAO(), scene[i].getBuffer().getVertexCount());
    }

    renderSystemPtr->setRenderMode(lastMode);

    GLfloat* color = new GLfloat[3];
    glReadPixels(xPos, windowPtr->getHeigth() - yPos, 1, 1, GL_RGB, GL_FLOAT, color);

    rs.setShaderProgram(*lastUsed);

    int id = (int)glm::roundEven(color[0] * scene.getMeshCount() - 1);
    scene.setSelectionId(id);
    if (scene.isSelected())
    {
        viewportPtr->getCamera().updateTarget(scene.getCurrentSelection().getWorldPosition());
    }
}

void onMouseButtonCallback(ButtonCode buttonCode, Action action, Modifier, float xPos, float yPos) {
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
            //scenePtr->addMesh(new Mesh(QUBE));
        }

        if (mods == Modifier::NoModifier)
        {
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

            case KeyCode::F9:
                renderSystemPtr->setRenderMode((RenderMode)!(bool)renderSystemPtr->getRenderMode());
                break;

            case KeyCode::F10:
                windowPtr->setHalfScreenWindowed();
                break;

            case KeyCode::F11:
                windowPtr->setFullScreen();
                break;
            }

        }

    }
}

void onCursorCallback(float xPos, float yPos)
{
    Camera& cam = viewportPtr->getCamera();
    
    const float sens = 0.2f;
    static float lastX(xPos), lastY(xPos);

    float  deltaX = xPos - lastX;
    float deltaY = yPos - lastY;

    lastX = xPos;
    lastY = yPos;
    
    if (lastMouse == ButtonCode::Right)
    {
        cam.rotate(cam.getTarget(), cam.calcRight(), sens * -deltaY);
        cam.rotate(cam.getTarget(), cam.getUp(), sens * -deltaX);
        //std::cout << deltaX << " " << deltaY << std::endl;
    }
    else if (lastMouse == ButtonCode::Left && scenePtr->isSelected())
    {
        scenePtr->getCurrentSelection().rotate(cam.calcRight(), sens * deltaY);
        scenePtr->getCurrentSelection().rotate(cam.getUp(), sens * deltaX);
    }
}

void onScrollCallback(float xOffset, float yOffset)
{
    Camera& camera = viewportPtr->getCamera();
    const float rotationSpeed = 0.2f;

    camera.setDistnceToTarget(glm::abs(camera.distanceFromEyeToTarget() + yOffset * rotationSpeed));
}

int main()
{
    glfwInit();
    glewInit();

    GLWindow::hideConsole();
    GLWindow window("Ultimate 8D Viewer", 1280, 720);
    windowPtr = &window;

    Viewport viewport;
    viewportPtr = &viewport;

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
        viewport.setViewportSize(window.getWidth(), window.getHeigth());

        GLRenderSystem::clearDisplay(0.2f, 0.2f, 0.2f);

        rs.setViewMatrix(viewport.getCamera().calcViewMatrix());
        rs.setProjMatrix(viewport.calcProjectionMatrix());
        rs.setCameraPos(viewport.getCamera().getEye());

        for (int i = 0; i < scene.getMeshCount(); i++)
        {
            glm::vec3 selectionColor = glm::vec3(0.9f, 0.6f, 0.7f);

            rs.setIsDefaultColor(true);
            rs.setWorldMatrix(scene[i].calcWorldMatrix());
            rs.render(scene[i].getBuffer().getVAO(), scene[i].getBuffer().getVertexCount());
        }

        glfwSwapBuffers(window.getGLFWHandle());
    }

    glfwTerminate();
}
