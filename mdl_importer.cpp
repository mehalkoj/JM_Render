#include "mdl_importer.h"


struct Model {

};


void importer() {
	
	std::fstream file("./teapot.obj");

	std::vector<Vertex> verts;
	std::vector<Vertex> faces;
	std::string line;

	std::cout << "Loading In Model!" << std::endl;
	while (std::getline(file, line)) {
		// vertices
		if (line.substr(0, 2) == "v ") {
			std::istringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			Vertex vert;
			vert.pos = { x, y, z };
			verts.push_back(vert);
			//std::cout << x << " " << y << " " << z << std::endl;
		}
		
		// texture coordinate
		else if (line.substr(0, 2) == "vt") {
			std::istringstream v(line.substr(3));

		}

		// vertex normals
		else if (line.substr(0, 2) == "vn") {
			std::istringstream v(line.substr(3));

		}

		// faces
		else if (line.substr(0, 2) == "f ") {
			int a, b, c;
			int A, B, C;
		}
	}
	std::cout << "Done!" << std::endl;

	file.close();
}

