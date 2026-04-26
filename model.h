#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "JM_Math.h"


struct Face {
	int v[3]; // indices
	int vt[3]; // texture indices
	int vn[3]; // normal indices
};

class Model {
	std::vector<Vertex> verts;
	std::vector<Vec2> texcoords;
	std::vector<Vec3> normals;
	std::vector<int> faces;

public:
	Model(const std::string filename);
	int numverts() const;
	int numfaces() const;
	Vertex vert(const int i) const;
	Vertex vert(const int iface, const int nthvert) const;
};
