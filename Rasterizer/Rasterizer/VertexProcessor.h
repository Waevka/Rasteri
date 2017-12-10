#pragma once
class VertexProcessor
{
public:
	std::vector<WVertex*> vertexBuffer;
	std::vector<Light*> lightBuffer;
	WFloat4x4 M, V, P;
	VertexProcessor();
	~VertexProcessor();
	//matrices
	void tr();
	void lt();
	void setPerspective(float fov, float ratio, float near, float far);
	void lookAt(WFloat4 up, WFloat4 eye, WFloat4 target);
	void translate(WFloat4 v);
	void rotate(float a, WFloat4 v);
	void scale(WFloat4 v);
	void setIdentity();
	void multByTrans();
	void multByRot();
	void transform();
};

