#include "Utils.h"
#include <vector>
#include <fstream>
#include <sstream>

std::string readString(const std::string& filename) {
	std::ifstream istream(filename.c_str(), std::ios_base::binary);
	std::stringstream sstream;
	sstream << istream.rdbuf();
	return sstream.str();
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
