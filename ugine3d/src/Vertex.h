#pragma once
#include "../lib/glm/glm.hpp"

class Vertex {
	public:
		Vertex(float x, float y, float z);
		Vertex(glm::vec3 _pos);
		Vertex(glm::vec3 _pos, glm::vec4 _color);
		Vertex(glm::vec3 _pos, glm::vec4 _color, glm::vec2 _texCoord);
		Vertex(glm::vec3 _pos, glm::vec2 _texCoord, glm::vec3 _normal = glm::vec3(0,0,0));
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
		glm::vec3 normal;
};