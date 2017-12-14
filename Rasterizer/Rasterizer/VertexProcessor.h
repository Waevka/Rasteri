#pragma once
class VertexProcessor
{
public:
	std::vector<WVertex*> vertices;
	std::vector<Light*> lights;
	WFloat4x4 M, V, P;
	VertexProcessor();
	~VertexProcessor();
	void processTransformations(ObjMesh *mesh, WFloat4 OX, WFloat4 OY, WFloat4 OZ, std::vector<Light*> lights);
	//matrices
	void tr();
	void lt();
	void setPerspective(float fov, float ratio, float near, float far);
	void lookAt(WFloat4 up, WFloat4 eye, WFloat4 target);
	void multByTrans(WFloat4 v);
	void multByRot(float a, WFloat4 v);
	void multByScale(WFloat4 v);
	void setIdentity();
	void transform();
};

