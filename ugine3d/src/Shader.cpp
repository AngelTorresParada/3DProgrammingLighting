#include "../lib/glew/GL/glew.h"
#include "../lib/glfw/glfw3.h"
#include "../lib/glm/glm.hpp"
#include <string>
#include "Vertex.h"
#include "Utils.h"
#include "Shader.h"

Shader::Shader(std::string &_vertexShader, std::string &_fragmentShader) {

	error = new char[4096];

	//Generar código shader de vértices
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexCodeStr = readString(_vertexShader);
	const char *vertexCode = vertexCodeStr.c_str();
	glShaderSource(vertexShader, 1, &vertexCode, nullptr);

	//Generar código shader de fragmentos
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentCodeStr = readString(_fragmentShader);
	const char *fragmentCode = fragmentCodeStr.c_str();
	glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);

}

std::shared_ptr<Shader> Shader::createShader(std::string &_vertexShader, std::string &_fragmentShader)
{
	//Crear smart pointer de Shader
	std::shared_ptr<Shader> shader(new Shader(_vertexShader, _fragmentShader), [](Shader *p){ delete p; });
	if (!shader) return nullptr;

	//Compilar shader de vértices
	GLint vertexRetCode;
	glCompileShader(shader->vertexShader);
	glGetShaderiv(shader->vertexShader, GL_COMPILE_STATUS, &vertexRetCode);
	if (vertexRetCode == GL_FALSE) {
		glGetShaderInfoLog(shader->vertexShader, sizeof(shader->error), NULL, const_cast<GLchar *>(shader->error));
		return nullptr;
	}

	GLint fragmentRetCode;
	glCompileShader(shader->fragmentShader);
	glGetShaderiv(shader->fragmentShader, GL_COMPILE_STATUS, &fragmentRetCode);
	if (fragmentRetCode == GL_FALSE) {
		glGetShaderInfoLog(shader->fragmentShader, sizeof(shader->error), NULL, const_cast<GLchar *>(shader->error));
		printf("%s", shader->error);
		return nullptr;
	}

	shader->program = glCreateProgram();
	glAttachShader(shader->program, shader->vertexShader);
	glAttachShader(shader->program, shader->fragmentShader);
	glDeleteShader(shader->vertexShader);
	glDeleteShader(shader->fragmentShader);

	GLint retCode;
	glLinkProgram(shader->program);
	glGetProgramiv(shader->program, GL_LINK_STATUS, &retCode);
	if (retCode == GL_FALSE) {
		glGetProgramInfoLog(shader->program, sizeof(shader->error), NULL, const_cast<GLchar *>(shader->error));
		return nullptr;
	}

	shader->positionLoc = glGetAttribLocation(shader->program, "vpos");
	shader->colorLoc = glGetAttribLocation(shader->program, "vcolor");
	shader->texCoordLoc = glGetAttribLocation(shader->program, "vtex");
	shader->normalLoc = glGetAttribLocation(shader->program, "vnormal");

	return shader;
}

uint32_t Shader::getId() const {
	return id;
}

const char * Shader::getError() const {
	return error;
}

void Shader::use() const {
	glUseProgram(program);
}

void Shader::setupAttribs() const {
	if (positionLoc != -1) {
		glEnableVertexAttribArray(positionLoc);
		glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
	}
	
	if (colorLoc != -1) {
		glEnableVertexAttribArray(colorLoc);
		glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, color)));
	}

	if (texCoordLoc != -1) {
		glEnableVertexAttribArray(texCoordLoc);
		glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, texCoord)));
	}

	if (normalLoc != -1) {
		glEnableVertexAttribArray(normalLoc);
		glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
	}
}

int Shader::getLocation(const char * name) const {
		return glGetUniformLocation(program, name);
}

void Shader::setInt(int loc, int val) {
	if (loc != -1)
		glUniform1i(loc, val);
}

void Shader::setFloat(int loc, float val) {
	if (loc != -1)
		glUniform1f(loc, val);
}

void Shader::setVec3(int loc, const glm::vec3 & vec) {
	if (loc != -1) {
		float x, y, z;
		x = vec.x;
		y = vec.y;
		z = vec.z;
		glUniform3f(loc, x, y, z);
	}
}

void Shader::setVec4(int loc, const glm::vec4 & vec) {
	if (loc != -1) {
		float x, y, z, w;
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
		glUniform4f(loc, x, y, z, w);
	}
}

void Shader::setMatrix(int loc, const glm::mat4 & matrix) {
	glUniformMatrix4fv(loc, 1, false, reinterpret_cast<const GLfloat *>((&matrix)));
}
