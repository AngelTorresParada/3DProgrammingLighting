#pragma once
#include <memory>
#include "Shader.h"
#include "Buffer.h"
#include "Vertex.h"
#include "Material.h"
#include <vector>

class Mesh {
	public:
		static std::shared_ptr<Mesh> load(const char* filename, const std::shared_ptr<Shader>& shader = nullptr);
		
		void addBuffer(const std::shared_ptr<Buffer>& _buffer, const Material& _material);

		size_t getNumBuffers() const;

		const std::shared_ptr<Buffer>& getBuffer(size_t _index) const;
		std::shared_ptr<Buffer>& getBuffer(size_t _index);

		const Material& getMaterial(size_t _index) const;
		Material& getMaterial(size_t _index);

		void draw();

private:
	Mesh();
	~Mesh();

	std::shared_ptr<Shader> defaultShader;
	std::vector<std::pair<std::shared_ptr<Buffer>, Material>> buffers;

};