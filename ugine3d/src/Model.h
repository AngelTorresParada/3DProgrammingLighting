#pragma once
#include "Entity.h"
#include "Mesh.h"
#include <memory>

class Model : public Entity {
public:
	Model(const std::shared_ptr<Mesh>&);
	virtual ~Model();

	virtual void draw() override;

private:
	std::shared_ptr<Mesh> mesh;
};