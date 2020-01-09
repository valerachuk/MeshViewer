#pragma once
#include <functional>
#include <string>
#include <iostream>
#include <GL\glew.h>	
#include <glfw\glfw3.h>	

enum class Modifier {
	NoModifier = 0,
	Shift = 1,
	Control = 2,
	Alt = 4,
	Super = 8,
};

enum class Action {
	Release = 0,
	Press = 1,
	Repeat = 2,
};

enum class ButtonCode {
	UNKNOWN = -1,
	Left = 0,
	Right = 1,
	Middle = 2,
};

enum class KeyCode {
	UNKNOWN = -1,
	Space = 32,
	LeftShift = 340,
	
	W = 87,
	A = 65,
	S = 83,
	D = 68,

	O = 79,
	C = 67,

	Up = 265,
	Down = 264,
	Right = 262,
	Left = 263,

	F1 = 290,
	F2 = 291,
	F3 = 292,
	F4 = 293,
	F5 = 294,
	F6 = 295,
	F7 = 296,
	F8 = 297,
	F9 = 298,
};

class GLWindow {
public:
	using KeyCallback = std::function<void(KeyCode, Action, Modifier)>;
	using CursorPosCallback = std::function<void(double, double)>;
	using MouseCallback = std::function<void(ButtonCode, Action, Modifier, double, double)>;
	using ScrollCallback = std::function<void(double, double)>;

	GLWindow(const std::string& title, uint32_t width, uint32_t height);
	~GLWindow();

	uint32_t getWidth() const;
	uint32_t getHeigth() const;
	void setKeyCallback(const KeyCallback&);
	void setCursorPosCallback(const CursorPosCallback&);
	void setMouseCallback(const MouseCallback&);
	void setScrollCallback(const ScrollCallback&);

	GLFWwindow* getGLFWHandle() const;

private:
	GLFWwindow* handle;
	KeyCallback keyCallback;
	CursorPosCallback cursorPosCallback;
	MouseCallback mouseCallback;
	ScrollCallback scrollCallback;

	struct {
		double xPos;
		double yPos;
	} lastMouse;

	static void internalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void internalMouseCallback(GLFWwindow* window, int button, int action, int mode);
	static void internalCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void internalScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};