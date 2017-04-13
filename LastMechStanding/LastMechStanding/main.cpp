#include ".\commonHeader.h"


#include ".\Shader.h"
#include ".\Camera.h"

// frame independency:
GLfloat deltaTime;			// time between current frame and last frame
GLfloat lastFrame;  		// time of last frame

// camera:
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX, lastY;		// cursor position in the last frame
bool firstMouse = true;		// so the view doesn't jump when the cursor enters the window


// moves/alters the camera positions based on user input
void do_movement() {
	// camera controls:
	if (keys[GLFW_KEY_W])
		camera.processKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.processKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.processKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.processKeyboard(RIGHT, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

	// esc key -> close window:
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	// calculate cursor offset since last frame:
	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processMouseScroll(yoffset);
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


	// set key, cursor and scrollwheel callbacks:
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


	// define vertex data for a cube:
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	// create shader object:
	std::unique_ptr<Shader> lightingShader = std::make_unique<Shader>("Resources/Shaders/lighting.vert", "Resources/Shaders/lighting.frag");

	// create a vertex array object and bind it:
	GLuint containerVAO;
	glGenVertexArrays(1, &containerVAO);
	glBindVertexArray(containerVAO);

	// create a vertex buffer object, bind it to the array buffer and apply it to the buffer memory for OpenGL to use:
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// specify how OpenGL interprets vertex data:
	// position attribute:
	// parameters (see also: https://learnopengl.com/#!Getting-started/Hello-Triangle):
	// location (see also: basic.vert), size of the vertex attribute (vec3 -> 3 attributes), data type, GL_FALSE -> normalized data, space between two attribute sets, offset  
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute:
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// unbind the vao:
	glBindVertexArray(0);

	

	// create lamp shader object:
	std::unique_ptr<Shader> lampShader = std::make_unique<Shader>("Resources/Shaders/lamp.vert", "Resources/Shaders/lamp.frag");

	// light vao:
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// lamp position:
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);




	// enable z-buffer:
	glEnable(GL_DEPTH_TEST);



	// hide and capture the cursor:
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	
	// set initial cursor position:
	lastX = width / 2.0;
	lastY = height / 2.0;

	
	// frame independency:
	deltaTime = 0.0f;	
	lastFrame = 0.0f;

	// game loop:
	while (!glfwWindowShouldClose(window)) {

		// calculate delta time for frame independency:
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// check if any events were triggered:
		glfwPollEvents();
		do_movement();

		// clear color and depth buffers:
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		/*
		* Container:
		*/

		lightingShader->useShader();

		// apply phong illumination model to container:
		// set light properties:
		GLint lightAmbientLoc = lightingShader->getUniformLocation("light.ambient");
		GLint lightDiffuseLoc = lightingShader->getUniformLocation("light.diffuse");
		GLint lightSpecularLoc = lightingShader->getUniformLocation("light.specular");
		GLint lightPositionLoc = lightingShader->getUniformLocation("light.position");
		glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
		glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f);
		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(lightPositionLoc, lightPos.x, lightPos.x, lightPos.z);
		// send viewer position to the shader:
		GLint viewPosLoc = lightingShader->getUniformLocation("viewPos");
		glUniform3f(viewPosLoc, camera.position.x, camera.position.y, camera.position.z);
		// set container material:
		GLint matAmbientLoc = lightingShader->getUniformLocation("material.ambient");
		GLint matDiffuseLoc = lightingShader->getUniformLocation("material.diffuse");
		GLint matSpecularLoc = lightingShader->getUniformLocation("material.specular");
		GLint matShineLoc = lightingShader->getUniformLocation("material.shininess");
		glUniform3f(matAmbientLoc, 1.0f, 0.5f, 0.31f);
		glUniform3f(matDiffuseLoc, 1.0f, 0.5f, 0.31f);
		glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
		glUniform1f(matShineLoc, 32.0f);

		// model matrix:
		glm::mat4 model;
		GLint modelLoc = lightingShader->getUniformLocation("model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// camera (view) matrix:
		glm::mat4 view;
		view = camera.getViewMatrix();
		GLint viewLoc = lightingShader->getUniformLocation("view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// projection matrix:
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.zoom), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
		GLint projLoc = lightingShader->getUniformLocation("projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// draw the container:
		glBindVertexArray(containerVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		/*
		* Lamp:
		*/

		lampShader->useShader();

		// model matrix:
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		modelLoc = lampShader->getUniformLocation("model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// camera (view) matrix:
		viewLoc = lampShader->getUniformLocation("view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// projection matrix:
		projLoc = lampShader->getUniformLocation("projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// draw the lamp:
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// swap window and color buffer:
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &containerVAO);
	glDeleteBuffers(1, &VBO);

	// clean up resources:
	glfwTerminate();

	return 0;
}