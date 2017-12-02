#pragma once
class Rasterizer
{
public:
	Rasterizer();
	~Rasterizer();
private:
	Buffer buffer;
	std::list<Model> models;
};

