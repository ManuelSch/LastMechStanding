#include ".\commonHeader.h"


#include ".\Shader.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

	// esc key -> close window:
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}


int main()
{

	// initialize glfw:
	glfwInit();

	// define OpenGL version (v3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// use core profile only:
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// make window non resizable:
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// create new window:
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialize glew:
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// set viewport size:
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);


	// set key callback:
	glfwSetKeyCallback(window, key_callback);


	// define vertex data for a square:
	GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};
	GLuint indices[] = {
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};


	// create a vertex array object and bind it:
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// create a vertex buffer object, bind it to the array buffer and apply it to the buffer memory for OpenGL to use:
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// create an element buffer object (since we use indices), bind it and apply it to the buffer memory:
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// specify how OpenGL interprets vertex data:
	// parameters (see also: https://learnopengl.com/#!Getting-started/Hello-Triangle):
	// location (see also: basic.vert), size of the vertex attribute (vec3 -> 3 attributes), data type, GL_FALSE -> normalized data, space between two attribute sets, offset  
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// unbind the vao:
	glBindVertexArray(0);


	// create shader object:
	std::unique_ptr<Shader> shader = std::make_unique<Shader>("basic.vert", "basic.frag");


	// chose between wireframe and fill mode:
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// default mode


	// game loop:
	while (!glfwWindowShouldClose(window)) {

		// check if any events were triggered:
		glfwPollEvents();

		// Clear color:
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// use specified shader for rendering:
		shader->useShader();

		// bind vao that we want to render:
		glBindVertexArray(VAO);
		
		// draw the object (without using indices and EBOs):
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// draw the object (using indices and EBOs):
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// unbind vao:  
		glBindVertexArray(0);

		// swap window and color buffer:
		glfwSwapBuffers(window);
	}

	// clean up resources:
	glfwTerminate();

	return 0;
}