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

	std::string line;
	std::vector<WFloat4> normals;
	std::vector<WFloat4> texcoords;
	std::vector<WColor> colors;

	std::ifstream file;
	file.open(name);

	if (!file.is_open()) {
		std::cout << "Error opening file!";
	}

	while (!file.eof()) {

		std::getline(file, line);
		std::cout << line << std::endl;
		std::vector<std::string> splitStrings = splitString(line, ' ');

		if (!splitStrings.empty()) {

			std::string identifier = splitStrings[0];

			if (identifier == "v") {

				WVertex *v = new WVertex(std::stof(splitStrings[2]),
					std::stof(splitStrings[4]),
					std::stof(splitStrings[6]));

				v->color = randomColor();
				vertices.push_back(v);

			} 
			else if (identifier == "vn") {

				WFloat4 n = {std::stof(splitStrings[2]),
					std::stof(splitStrings[4]),
					std::stof(splitStrings[6])};
				normals.push_back(n);

			}
			else if (identifier == "vt") {

				WFloat4 t = {std::stof(splitStrings[2]),
					std::stof(splitStrings[4]),
					std::stof(splitStrings[6])};
				texcoords.push_back(t);

			}
			else if (identifier == "c") {

				std::string s = splitStrings[1];
				unsigned int color;
				std::stringstream ss;
				ss << std::hex << s;
				ss >> color;
				WColor c = { color };
				colors.push_back(c);

			}
			else if (identifier == "f") {
				std::vector<std::string> f1 = splitString(splitStrings[2], '/');
				std::vector<std::string> f2 = splitString(splitStrings[4], '/');
				std::vector<std::string> f3 = splitString(splitStrings[6], '/');

				WVertex *a = vertices[stoi(f1[0]) - 1];
				WVertex *b = vertices[stoi(f2[0]) - 1];
				WVertex *c = vertices[stoi(f3[0]) - 1];

				WFloat4 atx;
				WFloat4 btx;
				WFloat4 ctx;
				if (f1[1] != "") {
					atx = texcoords[stoi(f1[1]) - 1];
					btx = texcoords[stoi(f1[1]) - 1];
					ctx = texcoords[stoi(f1[1]) - 1];
				} else {
					atx = { 0.0f, 0.0f, 0.0f };
					btx = { 0.0f, 0.0f, 0.0f };
					ctx = { 0.0f, 0.0f, 0.0f };
				}

				WFloat4 an = normals[stoi(f1[2]) - 1];
				WFloat4 bn = normals[stoi(f1[2]) - 1];
				WFloat4 cn = normals[stoi(f1[2]) - 1];

				a->normal = an;
				b->normal = bn;
				c->normal = cn;
				a->uv = atx;
				b->uv = btx;
				c->uv = ctx;

				Triangle *t = new Triangle(a, b, c);
				triangles.push_back(t);
			}
			else if (identifier == "cf") {
				std::vector<std::string> cf = splitString(splitStrings[1], '/');

				Triangle *t = triangles[stoi(cf[0]) - 1];
				WColor c = colors[stoi(cf[0]) - 1];

				t->A->color = c;
				t->B->color = c;
				t->C->color = c;
			}
			else if (identifier == "#") {
				std::cout << "Found comment: " << line << std::endl;
			}
		}
	}

}

ObjMesh::ObjMesh(float a, float b, float c)
{
	WVertex *R = new WVertex(a, 0.0f, 0.0f);
	WVertex *T = new WVertex(0.0f, b, 0.0f);
	WVertex *B = new WVertex(0.0f, 0.0f, c);
	WVertex *L = new WVertex(0.0f, 0.0f, 0.0f);

	R->color = 0xFFFF0000;
	T->color = 0xFF00FF00;
	L->color = 0xFF0000FF;
	B->color = 0xFFFFFFFF;

	vertices.push_back(R);
	vertices.push_back(T);
	vertices.push_back(B);
	vertices.push_back(L);

	Triangle *front = new Triangle(L, T, R);
	Triangle *side = new Triangle(B, T, L);
	Triangle *bottom = new Triangle(B, L, R);

	triangles.push_back(front);
	triangles.push_back(side);
	triangles.push_back(bottom);

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

