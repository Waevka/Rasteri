#include "stdafx.h"
#include "ObjMesh.h"


unsigned int randomColor() {
	unsigned int r = (0xFFFFFF >> 16 & 255) * (float)(rand()%100 / 100.0f);
	unsigned int g = (0xFFFFFF >> 8 & 255) * (float)(rand() % 100 / 100.0f);
	unsigned int b = (0xFFFFFF & 255) * (float)(rand() % 100 / 100.0f);
	unsigned int a = (0xFFFFFF >> 24 & 255) * (float)(rand() % 100 / 100.0f);

	return { (a << 24) + (r << 16) + (g << 8) + b };
}

ObjMesh::ObjMesh(std::string name)
{	
	Tv = { 0.0f, 0.0f, 0.0f };
	Rv = { 0.0f, 0.0f, 0.0f };
	Sv = { 1.0f, 1.0f, 1.0f };

	std::string currentLine;
	std::vector<WColor> colors;
	std::vector<WFloat4> normals;
	std::vector<WFloat4> uvs;

	std::ifstream file;
	file.open(name);

	if (!file.is_open()) {
		std::cout << "Error opening file!";
	}

	while (!file.eof()) {

		std::getline(file, currentLine);
		//std::cout << line << std::endl;
		std::vector<std::string> splitStrings = splitString(currentLine, ' ');

		if (!splitStrings.empty()) {

			//first characters identify line
			//INDICES 1, 2, 3 - VERIFIED FOR BLENDER .OBJ FILES!
			//Might not work with other exporters.
			std::string identifier = splitStrings[0];

			if (identifier == "v") {

				WVertex *v = new WVertex(std::stof(splitStrings[1]),
					std::stof(splitStrings[2]),
					std::stof(splitStrings[3]));

				v->color = randomColor();
				vertices.push_back(v);

			} 
			else if (identifier == "vn") {

				WFloat4 n = {std::stof(splitStrings[1]),
					std::stof(splitStrings[2]),
					std::stof(splitStrings[3])};
				normals.push_back(n);

			}
			else if (identifier == "vt") {

				WFloat4 t = {std::stof(splitStrings[1]),
					std::stof(splitStrings[2]),
					std::stof(splitStrings[3])};
				uvs.push_back(t);

			}
			else if (identifier == "f") {
				std::vector<std::string> f1 = splitString(splitStrings[1], '/');
				std::vector<std::string> f2 = splitString(splitStrings[2], '/');
				std::vector<std::string> f3 = splitString(splitStrings[3], '/');

				WVertex *x = vertices[stoi(f1[0]) - 1];
				WVertex *y = vertices[stoi(f2[0]) - 1];
				WVertex *z = vertices[stoi(f3[0]) - 1];

				WFloat4 atx;
				WFloat4 btx;
				WFloat4 ctx;

				if (f1[1] != "") {
					atx = uvs[stoi(f1[1]) - 1];
					btx = uvs[stoi(f1[1]) - 1];
					ctx = uvs[stoi(f1[1]) - 1];
				}
				else {
					atx = { 0.0f, 0.0f, 0.0f };
					btx = { 0.0f, 0.0f, 0.0f };
					ctx = { 0.0f, 0.0f, 0.0f };
				}

				WFloat4 an = normals[stoi(f1[2]) - 1];
				WFloat4 bn = normals[stoi(f1[2]) - 1];
				WFloat4 cn = normals[stoi(f1[2]) - 1];

				x->normal = an;
				y->normal = bn;
				z->normal = cn;
				x->uv = atx;
				y->uv = btx;
				z->uv = ctx;

				Triangle *trngl = new Triangle(x, y, z);
				triangles.push_back(trngl);
			}
			else if (identifier == "c") {

				std::string s = splitStrings[1];
				unsigned int color;
				std::stringstream ss;
				ss << std::hex << s;
				ss >> color;
				WColor c = color;
				colors.push_back(c);

			}
			else if (identifier == "cf") {
				std::vector<std::string> cf = splitString(splitStrings[1], '/');

				Triangle *trngl = triangles[stoi(cf[0]) - 1];
				WColor c = colors[stoi(cf[0]) - 1];

				trngl->A->color = c;
				trngl->B->color = c;
				trngl->C->color = c;
			}
			else if (identifier == "#") {
				std::cout << "Found comment: " << currentLine << std::endl;
			}
		}
	}

}

ObjMesh::~ObjMesh()
{
}

std::vector<std::string> ObjMesh::splitString(std::string string, char separator)
{
	std::stringstream test(string);
	std::string segment;
	std::vector<std::string> seglist;

	while (std::getline(test, segment, separator))
	{
		seglist.push_back(segment);
	}

	return seglist;
}

