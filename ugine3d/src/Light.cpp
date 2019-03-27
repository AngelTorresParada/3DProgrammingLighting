#include "Light.h"
#include "State.h"

Light::Light(Type _type, const glm::vec3& _color, float _linearAttenuation) {
	type = _type;
	color = _color;
	linearAttenuation = _linearAttenuation;
}


Light::Type Light::getType() const {
	return type;
}


void Light::setType(Type _type) {
	type = _type;
}


const glm::vec3 & Light::getColor() const {
	return color;
}


void Light::setColor(const glm::vec3 & _color) {
	color = _color;
}


float Light::getLinearAttenuation() const {
	return linearAttenuation;
}


void Light::setLinearAttenuation(float _att) {
	linearAttenuation = _att;
}

const glm::vec3 & Light::getPosition() const {
	return position;
}

void Light::setPosition(const glm::vec3 & _pos) {
	position = _pos;
}


void Light::prepare(int index, std::shared_ptr<Shader>& shader) const
{
	//glm::mat4 MVP = State::projectionMatrix * State::viewMatrix * State::modelMatrix;
	const char *locationAtt = std::string("linearatt[" + std::to_string(index) + "]").c_str();
	const char *locationColor = std::string("lightcolor[" + std::to_string(index) + "]").c_str();
	const char *locationPos = std::string("lightpos[" + std::to_string(index) + "]").c_str();
	shader->setFloat(shader->getLocation(locationAtt), linearAttenuation);
	shader->setFloat(shader->getLocation("constatt"), 1);
	shader->setFloat(shader->getLocation("quadratt"), 0);
	shader->setVec3(shader->getLocation(locationColor), color);

	glm::vec4 sendingPosition = glm::vec4(position, type);
	shader->setVec4(shader->getLocation(locationPos), sendingPosition);

}


