#include "Vertex.h"

Vertex::Vertex(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
	color = glm::vec4(1, 1, 1, 1);
}

Vertex::Vertex(glm::vec3 _pos) {
	position = _pos;
}


Vertex::Vertex(glm::vec3 _pos, glm::vec4 _color) {
	position = _pos;
	color = _color;
}


Vertex::Vertex(glm::vec3 _pos, glm::vec4 _color, glm::vec2 _texCoord) {
	position = _pos;
	color = _color;
	texCoord = _texCoord;
}


Vertex::Vertex(glm::vec3 _pos, glm::vec2 _texCoord, glm::vec3 _normal) {
	position = _pos;
	texCoord = _texCoord;
	normal = _normal;
}
