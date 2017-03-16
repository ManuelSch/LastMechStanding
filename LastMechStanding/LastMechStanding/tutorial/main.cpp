#include <iostream>
#include <memory>
#include <glfw3.h>

using namespace std;


void init(GLFWwindow* window);
void update();
void draw();
void cleanup();


int main() {

	// initialize glfw library:
	if (!glfwInit()) {
		cerr << "ERROR: Could not init glfw" << endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	// display dimensions:
	const int width = 800;
	const int height = 600;

	// create new window:
	auto window = glfwCreateWindow(width, height, "", nullptr, nullptr);
	if (!window) {
		cerr << "ERROR: Could not open window" << endl;
		glfwTerminate();
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	// define the window as active:
	glfwMakeContextCurrent(window);

	// initialize the window:
	init(window);

	// for calculating the fps
	auto time = glfwGetTime();

	// keep window open as long as isn't closed manually:
	while (!glfwWindowShouldClose(window)) {

		// calculate and output the fps:
		auto time_new = glfwGetTime();
		auto time_delta = (float)(time_new - time);
		time = time_new;
		cout << "frame time: " << time_delta*1000 << "ms \t= " << 1.0/time_delta << "fps" << endl;

		// Game loop: update game logic and render the current frame:
		update();
		draw();


		glfwSwapBuffers(window);
		glfwPollEvents();

		// close window if the Esc button is pressed:
		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	cleanup();

	// close glfw library:
	glfwTerminate();

	return EXIT_SUCCESS;
}



void init(GLFWwindow* window) {
	glfwSetWindowTitle(window, "Window title");
}

void update() {

}

void draw() {

}

void cleanup() {

}