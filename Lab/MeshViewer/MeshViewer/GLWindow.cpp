#include "GLWindow.h"

GLWindow::GLWindow(const std::string& title, uint32_t width, uint32_t height) : 
	handle(nullptr),
	keyCallback(nullptr),
	cursorPosCallback(nullptr),
	mouseCallback(nullptr),
	scrollCallback(nullptr)
{
	lastMouse.xPos = 0;
	lastMouse.yPos = 0;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

	if (handle == nullptr)
	{
		throw new std::runtime_error("Failed to create window");
	}
	glfwMakeContextCurrent(handle);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw new std::runtime_error("Failed to initialize GLEW");
	}

	glfwSetWindowUserPointer(handle, this);
	glfwSetKeyCallback(handle, internalKeyCallback);
	glfwSetMouseButtonCallback(handle, internalMouseCallback);
	glfwSetCursorPosCallback(handle, internalCursorPosCallback);
	glfwSetScrollCallback(handle, internalScrollCallback);
}

GLWindow::~GLWindow()
{

}

void GLWindow::internalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto handle = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
	if (handle->keyCallback != nullptr)
	{
		handle->keyCallback((KeyCode)key, (Action)action, (Modifier)mods);
	}
}

void GLWindow::internalMouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	auto handle = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
	if (handle->mouseCallback != nullptr)
	{
		handle->mouseCallback((ButtonCode)button, (Action)action, (Modifier)mods, handle->lastMouse.xPos, handle->lastMouse.yPos);
	}
}

void GLWindow::internalCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	auto handle = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
	handle->lastMouse.xPos = xpos;
	handle->lastMouse.yPos = ypos;
	
	if (handle->cursorPosCallback != nullptr)
	{
		handle->cursorPosCallback(xpos, ypos);
	}
}

void GLWindow::internalScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	auto handle = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
	if (handle->scrollCallback != nullptr)
	{
		handle->scrollCallback(xoffset, yoffset);
	}
}

uint32_t GLWindow::getWidth() const
{
	int width, height;
	glfwGetFramebufferSize(getGLFWHandle(), &width, &height);
	return width;
}

uint32_t GLWindow::getHeigth() const
{
	int width, height;
	glfwGetFramebufferSize(getGLFWHandle(), &width, &height);
	return height;
}

void GLWindow::setKeyCallback(const KeyCallback& _keyCallback)
{
	keyCallback = _keyCallback;
}

void GLWindow::setCursorPosCallback(const CursorPosCallback& _cursorPosCallback)
{
	cursorPosCallback = _cursorPosCallback;
}

void GLWindow::setMouseCallback(const MouseCallback& _mouseCallback)
{
	mouseCallback = _mouseCallback;
}

void GLWindow::setScrollCallback(const ScrollCallback& _scrollCallback)
{
	scrollCallback = _scrollCallback;
}

GLFWwindow* GLWindow::getGLFWHandle() const
{
	return handle;
}
