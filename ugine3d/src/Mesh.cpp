#include "Mesh.h"
#include "State.h"
#include "Material.h"
#include "common.h"
#include <iostream>
#include <sstream>
#include "../lib/pugixml-master/src/pugiconfig.hpp"
#include "../lib/pugixml-master/src/pugixml.hpp"

inline std::string extractPath(std::string _filename) {
	while (_filename.find('\\') != std::string::npos)
		_filename.replace(_filename.find('\\'), 1, 1, '/');
	size_t pos = _filename.rfind('/');
	if (pos == std::string::npos) return "";
	_filename = _filename.substr(0, pos);
	if (_filename.size() > 0) _filename += '/';
	return _filename;
}


template<typename T>
std::vector<T> splitString(const std::string& _str, char _delim) {
	std::vector<T> elems;
	if (_str != "") {
		std::stringstream ss(_str);
		std::string item;
		while (std::getline(ss, item, _delim)) {
			T value;
			std::stringstream ss2(item);
			ss2 >> value;
			elems.push_back(value);
		}
	}
	return elems;
}


Mesh::Mesh() {
}


Mesh::~Mesh() {
	buffers.clear();
}


std::shared_ptr<Mesh> Mesh::load(const char * _filename, const std::shared_ptr<Shader>& _shader)
{
	std::shared_ptr<Mesh> mesh(new Mesh(), [](Mesh *p) { delete p; });

	std::string path = extractPath(_filename);
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(_filename);

	if (result) {
		pugi::xml_node meshNode = doc.child("mesh");
		pugi::xml_node buffersNode = meshNode.child("buffers");
		for (pugi::xml_node bufferNode = buffersNode.child("buffer"); bufferNode; bufferNode = bufferNode.next_sibling("buffer")) {

			// get texture
			pugi::xml_node materialNode = bufferNode.child("material");

			pugi::xml_node textureNode = materialNode.child("texture");
			const char *textureFile = textureNode.text().as_string();
			std::string filename = path;
			filename.append(textureFile);

			std::shared_ptr<Texture> tex = Texture::load(filename.c_str());

			std::shared_ptr<Material> mat = nullptr;

			if (!_shader)
				mat = std::make_shared<Material>(tex);
			else
				mat = std::make_shared<Material>(tex, _shader);

			// get vertex coordinates
			pugi::xml_node coordsNode = bufferNode.child("coords");
			const char *coordsString = coordsNode.text().as_string();
			std::vector<float> coordinates = splitString<float>(std::string(coordsString), ',');

			// get vertex texCoords
			pugi::xml_node texcoordsNode = bufferNode.child("texcoords");
			const char *texcoordsString = texcoordsNode.text().as_string();
			std::vector<float> texcoordinates = splitString<float>(std::string(texcoordsString), ',');

			// get vertices
			std::vector<Vertex> vertices = {};
			if (texcoordinates.size() > 0)
				for (int i = 0, j = 0; i < coordinates.size() && j < texcoordinates.size(); i = i + 3, j = j + 2) {
					vertices.push_back(Vertex(glm::vec3(coordinates[i], coordinates[i + 1], coordinates[i + 2]), glm::vec2(texcoordinates[j], texcoordinates[j + 1])));
				}
			else {
				for (int i = 0; i < coordinates.size(); i = i + 3) {
					vertices.push_back(Vertex(glm::vec3(coordinates[i], coordinates[i + 1], coordinates[i + 2])));
				}
			}

			// get indices
			pugi::xml_node indicesNode = bufferNode.child("indices");
			const char *indicesString = indicesNode.text().as_string();
			std::vector<uint16_t> indices = splitString<uint16_t>(std::string(indicesString), ',');


			std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>(vertices, indices);

			mesh->addBuffer(buffer, *mat);

		}
		return mesh;
	}
	else {
		// No se ha podido cargar
		std::cout << result.description() << std::endl;
		return nullptr;
	}
	
}


void Mesh::addBuffer(const std::shared_ptr<Buffer>& _buffer, const Material & _material) {
	buffers.push_back(std::pair<const std::shared_ptr<Buffer>&, Material>(_buffer, _material));
}


size_t Mesh::getNumBuffers() const {
	return buffers.size();
}


const std::shared_ptr<Buffer>& Mesh::getBuffer(size_t _index) const {
	return buffers[_index].first;
}


std::shared_ptr<Buffer>& Mesh::getBuffer(size_t _index) {
	return buffers[_index].first;
}


const Material & Mesh::getMaterial(size_t _index) const {
	return buffers[_index].second;
}


Material & Mesh::getMaterial(size_t _index) {
	return buffers[_index].second;
}


void Mesh::draw() {
	for (auto pair : buffers) {
		std::shared_ptr<Buffer> b = pair.first;
		Material &m = pair.second;
		m.prepare();
		b->draw(*m.getShader());
	}
}
