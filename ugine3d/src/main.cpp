#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "common.h"
#include "../lib/glfw/glfw3.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "Utils.h"
#include "Buffer.h"
#include "Shader.h"
#include "Vertex.h"
#include "State.h"
#include "Mesh.h"
#include "Model.h"
#include "World.h"
#include "Camera.h"
#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "../lib/glm/gtc/quaternion.hpp"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

std::shared_ptr<Shader> State::defaultShader = nullptr;
glm::mat4 State::modelMatrix = glm::mat4();
glm::mat4 State::projectionMatrix = glm::mat4();
glm::mat4 State::viewMatrix = glm::mat4();

int main() {
	// init glfw
	if ( !glfwInit() ) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}

	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
	if (!win) {
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);

	// initialize opengl extensions
	if ( glewInit() != GLEW_OK ) {
		std::cout << "could not initialize opengl extensions" << std::endl;
		glfwTerminate();
		return -1;
	}

	// load shaders code
	std::string vertexFile = "data/vertex.glsl";
	std::string fragmentFile = "data/fragment.glsl";

	// initialize opengl states
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);

	// set default shader
	State::defaultShader = Shader::createShader(vertexFile, fragmentFile);

	// define mesh
	std::shared_ptr<Mesh> mesh = Mesh::load("data/bunny.msh.xml");

	// define camera
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	camera->setClearColor(glm::vec3(0, 0.5, 1));
	camera->setProjection(glm::perspective(glm::radians(60.0f), (SCREEN_WIDTH * 1.0f) / (SCREEN_HEIGHT * 1.0f), 0.01f, 100.0f));
	camera->setPosition(glm::vec3(0, 0.02f, 0));
	//camera->setRotation(glm::angleAxis(glm::radians(-20.0f), glm::vec3(1, 0, 0)));

	// define world
	std::shared_ptr<Model> model = std::make_shared<Model>(mesh);
	std::shared_ptr<World> world = std::make_shared<World>();
	model->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	world->addEntity(model);
	world->addEntity(camera);

	double lastX = 0, lastY = 0;

	float rotX = 0;
	float rotY = 0;
	float angle = 0;

	// main loop
	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {

		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);
		camera->setViewport(glm::ivec4(0, 0, screenWidth, screenHeight));

		double mouseX, mouseY;
		glfwGetCursorPos(win, &mouseX, &mouseY);
		int speedMX = static_cast<int>(mouseX - lastX);
		int speedMY = static_cast<int>(mouseY - lastY);
		lastX = mouseX;
		lastY = mouseY;

		rotX += speedMX * deltaTime * 45;
		rotY += speedMY * deltaTime * 45;

		camera->setRotation(glm::vec3(-glm::radians(rotY), -glm::radians(rotX),0));

		glm::vec3 movement;
		if (glfwGetKey(win, GLFW_KEY_W) || glfwGetKey(win, GLFW_KEY_UP)) {
			movement = glm::vec3(0, 0, -0.1f * deltaTime);
		}

		if (glfwGetKey(win, GLFW_KEY_S) || glfwGetKey(win, GLFW_KEY_DOWN)) {
			movement += glm::vec3(0, 0, 0.1f * deltaTime);
		}

		if (glfwGetKey(win, GLFW_KEY_A) || glfwGetKey(win, GLFW_KEY_LEFT)) {
			movement += glm::vec3(-0.1f * deltaTime, 0, 0);
		}

		if (glfwGetKey(win, GLFW_KEY_D) || glfwGetKey(win, GLFW_KEY_RIGHT)) {
			movement += glm::vec3(0.1f * deltaTime, 0, 0);
		}

		camera->move(movement);

		// update and draw world
		world->update(deltaTime);
		world->draw();

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown
	glfwTerminate();
}
