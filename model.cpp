#include "model.h"


void replace_all(auto begin, auto end, auto target, auto swap) {
	for (auto i = begin; i != end; ++i) {
		if (*i == target) {
			*i = swap;
		}
	}
}



Model::Model(const std::string file) {
	
	std::fstream in;
	in.open(file, std::fstream::in);

	if (in.fail()) {
		std::cerr << "Failed to open " << file << std::endl;
		return;
	}

	std::string line;

	std::cout << "Loading In Model!" << std::endl;
	while (std::getline(in, line)) {
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
			std::vector<int> fIndex;
			std::string token;
			while (iss >> token) {
				// normalize: turn / or // into space seperated for all obj models
				replace_all(token.begin(), token.end(), '/', ' ');
				std::istringstream ts(token);
				int f;
				ts >> f;
				fIndex.push_back(f - 1);
			}
			for (size_t i = 1; i + 1 < fIndex.size(); i++) {
				faces.push_back(fIndex[0]);
				faces.push_back(fIndex[i]);
				faces.push_back(fIndex[i + 1]);
			}
		}
	}
	normalize();
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

void Model::normalize() {
	if (verts.empty()) return;

	auto min = verts[0].pos;
	auto max = verts[0].pos;

	// AAB across all vertices
	for (const Vertex& v : verts) {
		for (int i : {0, 1, 2}) {
			if (v.pos[i] < min[i]) min[i] = v.pos[i];
			if (v.pos[i] > max[i]) max[i] = v.pos[i];
		}
	}

	// Center of bbox
	auto center = (min + max) * 0.5f;
	auto extent = max - min;
	float maxExtent = std::max({ extent[0], extent[1], extent[2] });
	if (maxExtent == 0.f) return;

	// Translate to origin unfiorm scale into [-1, 1]
	float scale = 2.0f / maxExtent;
	for (Vertex& v : verts) {
		for (int i : {0, 1, 2}) {
			v.pos[i] = (v.pos[i] - center[i]) * scale;
		}
	}
}
