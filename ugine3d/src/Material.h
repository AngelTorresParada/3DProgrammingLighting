#pragma once
#include "common.h"
#include "Texture.h"
#include "Shader.h"

class Material {
	public:
		Material(const std::shared_ptr<Texture>& _tex = nullptr, const std::shared_ptr<Shader>& _shader = nullptr);

		const std::shared_ptr<Shader>& getShader() const;
		std::shared_ptr<Shader>& getShader();
		void setShader(const std::shared_ptr<Shader>& _shader);

		const std::shared_ptr<Texture>& getTexture() const;
		void setTexture(const std::shared_ptr<Texture>& _tex);

		void prepare();

private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;

};