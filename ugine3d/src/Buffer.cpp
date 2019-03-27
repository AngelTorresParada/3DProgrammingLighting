#include "Buffer.h"
#include "../lib/glew/GL/glew.h"
#include "../lib/glfw/glfw3.h"

Buffer::Buffer(std::vector<Vertex>& _vertices, std::vector<uint16_t>& _indices)
{
	vertices = _vertices;
	indices = _indices;

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

Buffer::~Buffer()
{
}

void Buffer::draw(const Shader & shader)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	
	shader.setupAttribs();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, nullptr);
}
