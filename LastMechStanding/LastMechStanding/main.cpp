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


	// define vertex data for a rectangle:
	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
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
	// position attribute:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// color attribute:
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// texture attribute:
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// unbind the vao:
	glBindVertexArray(0);


	// create shader object:
	std::unique_ptr<Shader> shader = std::make_unique<Shader>("basic.vert", "basic.frag");
	// use specified shader for rendering:
	shader->useShader();


	// first texture:
	GLuint texture1;
	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(shader->getUniformLocation("ourTexture1"), 0);
	// set the texture wrapping parameters:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load the texture file:
	int texWidth, texHeight;
	unsigned char* image = SOIL_load_image("container.jpg", &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
	// genereate texture:
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	// automatically genereate mipmaps:
	glGenerateMipmap(GL_TEXTURE_2D);
	// free the image memory and unbind the texture object:
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// second texture:
	GLuint texture2;
	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(shader->getUniformLocation("ourTexture2"), 1);
	// set the texture wrapping parameters:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load the texture file:
	int texWidth2, texHeight2;
	unsigned char* image2 = SOIL_load_image("awesomeface.png", &texWidth2, &texHeight2, 0, SOIL_LOAD_RGB);
	// genereate texture:
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth2, texHeight2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	// automatically genereate mipmaps:
	glGenerateMipmap(GL_TEXTURE_2D);
	// free the image memory and unbind the texture object:
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 0);





	// game loop:
	while (!glfwWindowShouldClose(window)) {

		// check if any events were triggered:
		glfwPollEvents();

		// Clear color:
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// bind the texture objects:
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		// second texture:
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// transformation matrix:
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (GLfloat)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		// pass it to the shader:
		GLuint transformLoc = shader->getUniformLocation("transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


		// bind vao that we want to render:
		glBindVertexArray(VAO);

		// draw the object:
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