#pragma once

/*
* Manages the gameloop (update and draw) and user inputs
*/

#include "..\commonHeader.h"
#include "..\Game\Display.h"
#include "..\Scene\Camera.h"
#include "..\Scene\SceneObjects\Player.h"
#include "..\Scene\SceneObjects\Enemy.h"
#include "..\Scene\SceneObjects\Arena.h"
#include "..\Scene\LightSource.h"

class Gameloop
{
public:
	Gameloop(Display* _display);
	~Gameloop();

	// starts the game loop:
	void run();

	// input callbacks:
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
	void mouse_callback(GLFWwindow * window, double xpos, double ypos);

	void drawHUD();
	void drawHUDelements();
private:
	shared_ptr<Player> player;

	Display* display;

	// frame independency:
	GLfloat deltaTime;		// time between current frame and last frame
	GLfloat lastFrame;		// time of last frame

	// camera:
	Camera camera;
	bool keys[1024];			// keyboard key IDs
	GLfloat lastX, lastY;		// cursor position in the last frame
	bool firstMouse = true;		// so the view doesn't jump when the cursor enters the window

	// scene objects:
	vector<shared_ptr<SceneObject>> sceneObjects;
	vector<shared_ptr<LightSource>> lightSources;

	// moves the camera positions based on user input
	void do_movement();
};

