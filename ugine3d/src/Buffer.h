#pragma once
#include <vector>
#include "Vertex.h"
#include "Shader.h"

class Buffer {
	public:
		Buffer(std::vector<Vertex> &_vertices, std::vector<uint16_t> &_indices);
		~Buffer();

		std::vector<Vertex> vertices;
		std::vector<uint16_t> indices;

		uint32_t indexBuffer;
		uint32_t vertexBuffer;

		void draw(const Shader &shader);
};