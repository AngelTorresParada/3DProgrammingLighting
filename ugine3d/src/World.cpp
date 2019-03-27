#include "World.h"

World::World() {
}

World::~World() {
	entities.clear();
	cameras.clear();
}

void World::addEntity(const std::shared_ptr<Entity>&_entity) {
	entities.push_back(_entity);
	std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(_entity);
	if (camera) {
		cameras.push_back(camera);
	}
}

void World::removeEntity(const std::shared_ptr<Entity>&_entity) {
	for (auto e = entities.begin(); e != entities.end(); e++) {
		if (*e == _entity) {
			entities.erase(e);
			break;
		}
	}
	
	std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(_entity);
	if (camera) {
		for (auto c = cameras.begin(); c != cameras.end(); c++) {
			if (*c == camera) {
				cameras.erase(c);
				break;
			}
		}
	}
}

size_t World::getNumEntities() const{
	return entities.size();
}

const std::shared_ptr<Entity>& World::getEntity(size_t _index) const {
	return entities[_index];
}

std::shared_ptr<Entity>& World::getEntity(size_t _index) {
	return entities[_index];
}

void World::update(float _deltaTime) {
	for (auto e : entities) {
		e->update(_deltaTime);
	}
}

void World::draw() {
	for (auto c : cameras) {
		c->prepare();
		for (auto e : entities) {
			e->draw();
		}
	}
}
