#pragma once

/*
* Manages the gameloop (update and draw) and user inputs
*/

#include "..\commonHeader.h"
#include "..\Game\Display.h"
#include "..\Game\ShortKeys.h"
#include "..\Scene\Camera.h"
#include "..\Scene\SceneObjects\Player.h"
#include "..\Scene\SceneObjects\Enemy.h"
#include "..\Scene\SceneObjects\Arena\Arena.h"
#include "..\Scene\SceneObjects\Arena\ArenaWall.h"
#include "..\Scene\SceneObjects\Arena\Container1.h"
#include "..\Scene\SceneObjects\Lamp.h"
#include "..\Scene\GUI.h"
#include "..\Scene\LightSource.h"
#include "..\Util\Framebuffer.h"
#include "..\Util\ShadowMap.h"

class Gameloop
{
public:
	Gameloop(shared_ptr<Display> _display, shared_ptr<Font> _font);
	~Gameloop();

	// starts the game loop:
	void run();

	// input callbacks:
	void keyboardCallback(GLFWwindow * window, int key, int scancode, int action, int mode);
	void mouseCallback(GLFWwindow * window, double xpos, double ypos);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

private:
	shared_ptr<Display> display;
	shared_ptr<Player> player;
	shared_ptr<GUI> gui;
	shared_ptr<ShortKeys> shortKeys;
	shared_ptr<Font> font;
	shared_ptr<Framebuffer> framebuffer;
	shared_ptr<ShadowMap> shadowMap;


	// frame independency:
	GLfloat deltaTime;		// time between current frame and last frame
	GLfloat lastFrame;		// time of last frame

	// camera:
	Camera camera;
	bool keys[1024];			// keyboard key IDs
	bool mouseButtons[8];		// mouse button IDs
	GLfloat lastX, lastY;		// cursor position in the last frame
	bool firstMouse = true;		// so the view doesn't jump when the cursor enters the window

	// scene objects:
	vector<shared_ptr<SceneObject>> sceneObjects;
	vector<shared_ptr<LightSource>> lightSources;

	// moves the player position based on the user input
	void processKeyboardInput(vector<shared_ptr<SceneObject>>* sceneObjects);
	void processMouseButtonInput();
};

