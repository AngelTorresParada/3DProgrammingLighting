#pragma once
#include "Entity.h"

class Camera : public Entity {
public:
	Camera();
	virtual ~Camera();

	const glm::mat4& getProjection() const;
	void setProjection(const glm::mat4&);

	const glm::ivec4& getViewport() const;
	void setViewport(const glm::ivec4&);

	const glm::vec3& getClearColor() const;
	void setClearColor(const glm::vec3&);

	void prepare();

private:
	glm::mat4 projection;
	glm::vec3 clearColor;
	glm::ivec4 viewport;

};
