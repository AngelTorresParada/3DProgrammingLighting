#include "Texture.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb-master/stb_image.h"
#endif

std::shared_ptr<Texture> Texture::load(const char * _file) {
	std::shared_ptr<Texture> texture(new Texture(), [](Texture *p) { delete p; });

	stbi_set_flip_vertically_on_load(true);

	texture->imageBuffer = stbi_load(_file, &texture->size.x, &texture->size.y, nullptr, 4);
	if (!texture->imageBuffer)
		return nullptr;

	glGenTextures(1, &texture->texture);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_TEXTURE_MIN_FILTER);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->size.x, texture->size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->imageBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	

	stbi_image_free(texture->imageBuffer);

	return texture;
}


uint32_t Texture::getId() const {
	return texture;
}


const glm::ivec2 &Texture::getSize() const {
	return size;
}


void Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, texture);
}


Texture::Texture() {
}


Texture::~Texture(){
	
}


