#include "ObjLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>

ObjLoader::ObjLoader(string filename) {
	ifstream in;
	in.open(filename.c_str(), ios::in);
	if (!in.is_open()) {
		cout << "open File Failed." << endl;
		exit(-1);
	}

	string line;
	while (getline(in, line)) {
		stringstream ss(line);
		string type_str;
		ss >> type_str;
		if (type_str == "v") {
			Vertex v;
			ss >> v;
			vSet.push_back(v);
		} else if (type_str == "f") {
			int a, b, c;
			ss >> a >> b >> c;
			fSet.push_back(Face(vSet[a-1],vSet[b-1],vSet[c-1]));
		}
	}
	in.close();
}

IntersectResult ObjLoader::isIntersected(CRay & _ray)
{
	float minDistance = numeric_limits<float>::max();
	IntersectResult minResult = IntersectResult::noHit();
	int size = fSet.size();

	for (int i = 0; i < size; i++)
	{
		IntersectResult result = fSet[i].isIntersected(_ray);
		if (result.isHit && (result.distance < minDistance))
		{
			minResult.object = &(fSet[i]);
			minDistance = result.distance;
			minResult = result;
		}
	}
	return minResult;
}

void ObjLoader::setMaterial(Material * material)
{
	int size = fSet.size();
	for (int i = 0; i < size; i++) {
		fSet[i].material = material;
	}
}


