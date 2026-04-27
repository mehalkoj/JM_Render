#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
//#include <algorithm>
#include "JM_Math.h"



class Model {
	std::vector<Vertex> verts;
	std::vector<int> faces;

public:
	Model(const std::string filename);
	int numverts() const;
	int numfaces() const;
	Vertex vert(const int i) const;
	Vertex vert(const int iface, const int nthvert) const;
};
