#pragma once
#include <memory>
#include "Entity.h"
#include "Camera.h"
#include <vector>

class World {
public:
	World();
	~World();
	void addEntity(const std::shared_ptr<Entity>&);
	void removeEntity(const std::shared_ptr<Entity>&);
	size_t getNumEntities() const;
	const std::shared_ptr<Entity>& getEntity(size_t) const;
	std::shared_ptr<Entity>& getEntity(size_t);
	void update(float);
	void draw();

private:
	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Camera>> cameras;

};