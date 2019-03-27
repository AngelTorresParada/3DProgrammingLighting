#pragma once
#include "Entity.h"
#include "common.h"
#include "Shader.h"

class Light : public Entity {
public:
	enum Type {
		DIRECTIONAL,
		POINT,
	};

	Light(Type _type, const glm::vec3& _color, float _linearAttenuation);

	Type getType() const;
	void setType(Type _type);
	const glm::vec3& getColor() const;
	void setColor(const glm::vec3& _color);
	float getLinearAttenuation() const;
	void setLinearAttenuation(float _att);
	const glm::vec3& getPosition() const;
	void setPosition(const glm::vec3& _pos);
	void prepare(int index, std::shared_ptr<Shader>& shader) const;

private:
	Type type;
	glm::vec3 color;
	float linearAttenuation;
	glm::vec3 position;
};