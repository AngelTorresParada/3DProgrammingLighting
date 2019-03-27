#include "Material.h"
#include "State.h"

Material::Material(const std::shared_ptr<Texture>& _tex, const std::shared_ptr<Shader>& _shader) {
	texture = _tex;
	shader = _shader;
}

const std::shared_ptr<Shader>& Material::getShader() const {
	if (shader)
		return shader;
	return State::defaultShader;
}

std::shared_ptr<Shader>& Material::getShader() {
	if (shader)
		return shader;
	return State::defaultShader;
}

void Material::setShader(const std::shared_ptr<Shader>& _shader) {
	shader = _shader;
}

const std::shared_ptr<Texture>& Material::getTexture() const {
	return texture;
}

void Material::setTexture(const std::shared_ptr<Texture>& _tex) {
	texture = _tex;
}

void Material::prepare() {
	getShader()->use();

	glm::mat4 MVP = State::projectionMatrix * State::viewMatrix * State::modelMatrix;

	getShader()->setInt(getShader()->getLocation("usetexture"), texture ? 1 : 0);

	getShader()->setMatrix(getShader()->getLocation("MVP"), MVP);

	getShader()->setInt(getShader()->getLocation("texSampler"), 0);

	texture->bind();
}
