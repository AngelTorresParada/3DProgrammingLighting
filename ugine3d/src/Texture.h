#pragma once
#include "common.h"

class Texture {
	public:
		static std::shared_ptr<Texture> load(const char* _file);
		uint32_t getId() const;
		const glm::ivec2& getSize() const;
		void bind() const;

	private:
		Texture();
		~Texture();

		unsigned char *imageBuffer;
		glm::ivec2 size;

		uint32_t texture;

};