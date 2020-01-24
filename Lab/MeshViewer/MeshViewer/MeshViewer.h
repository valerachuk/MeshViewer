#pragma once
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
#include "Mesh.h"
#include "Scene.h"
#include "SimpleAstlReader.h"

class MeshViewer {
    static GLRenderSystem* renderSystemPtr;
    static Viewport* viewportPtr;
    static GLWindow* windowPtr;
    static Scene* scenePtr;
    static Shader* unlitShaderPtr;
    static ButtonCode lastMouse;


    static void AddModelFormFile();
    static void selectTarget(double xPos, double yPos);
    static void onMouseButtonCallback(ButtonCode buttonCode, Action action, Modifier, double xPos, double yPos);
    static void onKeyCallback(KeyCode key, Action act, Modifier mods);
    static void onCursorCallback(double xPos, double yPos);
    static void onScrollCallback(double xOffset, double yOffset);

public:
    void startProgram();
};
