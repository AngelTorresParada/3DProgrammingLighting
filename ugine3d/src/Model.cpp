#include "Model.h"
#include "State.h"
#include "../lib/glm/gtc/matrix_transform.hpp"

Model::Model(const std::shared_ptr<Mesh> &_mesh) {
	mesh = _mesh;
}

Model::~Model() {
}

void Model::draw() {
	glm::mat4 model = glm::mat4();
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::angle(rotation), glm::axis(rotation));
	model = glm::scale(model, scale);
	State::modelMatrix = model;

	mesh->draw();
}


