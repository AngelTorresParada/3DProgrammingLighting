#include "Entity.h"

Entity::Entity()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::quat();
	scale = glm::vec3(1, 1, 1);
}


Entity::~Entity()
{
}


const glm::vec3& Entity::getPosition() const {
	return position;
}

void Entity::setPosition(const glm::vec3 &_pos) {
	position = _pos;
}

const glm::quat & Entity::getRotation() const {
	return rotation;
}

const void Entity::setRotation(const glm::quat &_rot) {
	rotation = _rot;
}

const glm::vec3 & Entity::getScale() const {
	return scale;
}

void Entity::setScale(const glm::vec3 &_scale) {
	scale = _scale;
}

void Entity::move(const glm::vec3 &_vec) {
	position += rotation * _vec;
}
