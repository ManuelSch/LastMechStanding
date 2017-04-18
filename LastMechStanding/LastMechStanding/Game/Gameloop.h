#pragma once

/*
* Manages the gameloop (update and draw) and user inputs
*/

#include "..\commonHeader.h"

#include "..\Game\Display.h"
#include "..\Scene\Camera.h"
#include "..\Scene\Model.h"
#include "..\Shader.h"

class Gameloop
{
public:
	Gameloop(Display* _display, Shader* _shader);
	~Gameloop();

	// starts the game loop:
	void run();

	// input callbacks:
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
	void mouse_callback(GLFWwindow * window, double xpos, double ypos);
	void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);

private:
	Display* display;
	Shader* shader;

	// frame independency:
	GLfloat deltaTime;		// time between current frame and last frame
	GLfloat lastFrame;		// time of last frame

	// camera:
	Camera camera;
	bool keys[1024];			// keyboard key IDs
	GLfloat lastX, lastY;		// cursor position in the last frame
	bool firstMouse = true;		// so the view doesn't jump when the cursor enters the window

	// moves the camera positions based on user input
	void do_movement();
};
