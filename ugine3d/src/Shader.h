#pragma once
#include "stdint.h"
#include <string>
#include "../lib/glm/glm.hpp"
#include <memory>


class Shader {
	public:
		static std::shared_ptr<Shader> createShader(std::string &_vertexShader, std::string &_fragmentShader);

		// Devuelve el identificador de OpenGL del programa
		uint32_t	getId() const;

		// Obtiene el mensaje de error generado al compilar o enlazar
		const char*	getError() const;

		// Activa el uso de este programa
		void		use() const;

		// Activa la escritura de las variables attribute,
		// y especifica su formato
		void		setupAttribs() const;

		// Obtiene la localización de una variable uniform
		int			getLocation(const char* name) const;

		// Da valor a una variable uniform
		void		setInt(int loc, int val);
		void		setFloat(int loc, float val);
		void		setVec3(int loc, const glm::vec3& vec);
		void		setVec4(int loc, const glm::vec4& vec);
		void		setMatrix(int loc, const glm::mat4& matrix);

	private:
		uint32_t vertexShader;
		uint32_t fragmentShader;

		uint32_t program;
		Shader(std::string &_vertexShader, std::string &_fragmentShader);

		int32_t positionLoc;
		int32_t colorLoc;
		int32_t texCoordLoc;
		int32_t normalLoc;

		const char *error;
		uint32_t id;

};

