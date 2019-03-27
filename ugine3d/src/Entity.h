#pragma once
#include "../lib/glm/glm.hpp"
#include "../lib/glm/gtc/quaternion.hpp"

class Entity {
	public:
		Entity();
		virtual ~Entity();

		const glm::vec3& getPosition() const;
		void setPosition(const glm::vec3&);
		const glm::quat& getRotation() const;
		const void setRotation(const glm::quat&);
		const glm::vec3& getScale() const;
		void setScale(const glm::vec3&);

		void move(const glm::vec3&);

		virtual void update(float deltaTime) {}
		virtual void draw() {}

	protected:
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;
};