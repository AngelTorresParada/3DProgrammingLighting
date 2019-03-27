#include "Camera.h"
#include "State.h"
#include "../lib/glm/gtc/matrix_transform.hpp"
#include "../lib/glfw/glfw3.h"

Camera::Camera() {
	projection = glm::mat4(1.0f);
	clearColor = glm::vec3(0, 0, 0);
	viewport = glm::ivec4(0, 0, 0, 0);
}


Camera::~Camera() {
}

const glm::mat4 & Camera::getProjection() const {
	return projection;
}

void Camera::setProjection(const glm::mat4 &_proj) {
	projection = _proj;
}

const glm::ivec4 & Camera::getViewport() const {
	return viewport;
}

void Camera::setViewport(const glm::ivec4 &_viewport) {
	viewport = _viewport;
}

const glm::vec3 & Camera::getClearColor() const {
	return clearColor;
}

void Camera::setClearColor(const glm::vec3 &_color) {
	clearColor = _color;
}

void Camera::prepare() {
	State::projectionMatrix = projection;

	glm::mat4 view = glm::mat4();
	view = glm::rotate(view, glm::angle(rotation) * -1, glm::axis(rotation));
	view = glm::translate(view, -1.0f * position);
	State::viewMatrix = view;

	glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
	glScissor(viewport.x, viewport.y, viewport.z, viewport.w);

	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
