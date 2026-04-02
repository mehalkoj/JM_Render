#include "mdl_importer.h"





void importer() {
	
	std::fstream file("./teapot.obj");

	std::vector<Vertex> verts;
	std::vector<Vertex> faces;
	std::string line;

	std::cout << "Loading In Model!" << std::endl;
	while (std::getline(file, line)) {
		char myChar = file.get();
		std::getline(file >> std::ws, line);
		if (myChar == 118) {
			//std::cout << line << std::endl;
		}
		else if (myChar == 102) {
			//std::cout << line << std::endl;
		}
	}
	std::cout << "Done!" << std::endl;

	file.close();
}

