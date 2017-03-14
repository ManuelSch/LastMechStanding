#include <iostream>
#include <memory>
#include <glfw3.h>

using namespace std;

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

	// initialize new window:
	auto window = glfwCreateWindow(width, height, "Window title", nullptr, nullptr);
	if (!window) {
		cerr << "ERROR: Could not open window" << endl;
		glfwTerminate();
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	// define the window as active:
	glfwMakeContextCurrent(window);

	// for calculating the fps
	auto time = glfwGetTime();

	// keep window open as long as isn't closed manually:
	while (!glfwWindowShouldClose(window)) {

		// calculate and output the fps:
		auto time_new = glfwGetTime();
		auto time_delta = (float)(time_new - time);
		time = time_new;
		cout << "frame time: " << time_delta*1000 << "ms \t= " << 1.0/time_delta << "fps" << endl;


		glfwSwapBuffers(window);
		glfwPollEvents();

		// close window if the Esc button is pressed:
		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	// close glfw library:
	glfwTerminate();

	return EXIT_SUCCESS;
}