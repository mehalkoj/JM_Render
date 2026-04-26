#include "model.h"




std::vector<int> faces;
std::vector<Vertex> textures;
std::vector<Vertex> normals;

Model::Model(const std::string file) {
	
	std::fstream in;
	in.open(file, std::fstream::in);

	if (in.fail()) {
		std::cerr << "Failed to open " << file << std::endl;
		return;
	}

	std::string line;

	std::cout << "Loading In Model!" << std::endl;
	while (!in.eof()) {
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;

		if (!line.compare(0, 2, "v ")) {
			iss >> trash;
			Vertex v;
			for (int i : {0, 1, 2}) iss >> v.pos[i];
			verts.push_back(v);
		}
		else if (!line.compare(0, 2, "f ")) {
			iss >> trash;
			int cnt = 0;
			std::string token;
			while (iss >> token) {
				// normalize: turn / or // into space seperated for all obj models
				std::replace(token.begin(), token.end(), '/', ' ');
				std::istringstream ts(token);
				int f;
				ts >> f;
				faces.push_back(--f);
				cnt++;
			}
			if (cnt != 3) {
				std::cerr << "Error: the face has " << cnt << " vertices, expected 3" << std::endl;
				return;
				
			}
		}
	}
	//std::cerr << "# v# " << numverts() << " f# " << numfaces() << std::endl;
	std::cout << "Done!" << std::endl;

}

int Model::numverts() const { return verts.size(); }
int Model::numfaces() const { return faces.size() / 3; }

Vertex Model::vert(const int i) const {
	return verts[i];
}

Vertex Model::vert(const int iface, const int nthvert) const {
	return verts[faces[iface * 3 + nthvert]];
}

