#pragma once
class ObjMesh
{
public:
	ObjMesh(std::string name);
	~ObjMesh(); 
	std::vector<std::string> splitString(std::string string, char separator);
	std::vector<WVertex*> vertices;
	std::vector<Triangle*> triangles;

	WFloat4 Tv;
	WFloat4 Rv;
	WFloat4 Sv;
};

