#pragma once
class Model
{
public:
	Model();
	~Model();
	void Draw();
	void Light();
private:
	VertexProcessor vprocessor;
};

