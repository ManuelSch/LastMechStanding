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


	// define vertex data for a cube:
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	// positions of the ten cubes:
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
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

	// specify how OpenGL interprets vertex data:
	// position attribute:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// texture attribute:
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
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


	// perspective:
	// model matrix: inside game loop
	// view matrix:
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	GLuint viewLoc = shader->getUniformLocation("view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	// projection matrix:
	glm::mat4 projection;
	projection = glm::perspective((GLfloat)glm::radians(45.0), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	GLuint projectionLoc = shader->getUniformLocation("projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// enable z-buffer:
	glEnable(GL_DEPTH_TEST);



	// game loop:
	while (!glfwWindowShouldClose(window)) {

		// check if any events were triggered:
		glfwPollEvents();

		// clear color and depth buffers:
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind the texture objects:
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		// second texture:
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		
	
		// bind vao that we want to render:
		glBindVertexArray(VAO);

		// draw the ten cubes:
		for (GLuint i = 0; i < 10; i++) {
			// model matrix:
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = glm::radians(20.0f) * i;

			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			GLuint modelLoc = shader->getUniformLocation("model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// unbind vao:  
		glBindVertexArray(0);

		// swap window and color buffer:
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// clean up resources:
	glfwTerminate();

	return 0;
}