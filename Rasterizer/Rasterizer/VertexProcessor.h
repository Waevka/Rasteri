#pragma once
class VertexProcessor
{
public:
	VertexProcessor();
	~VertexProcessor();
	//matrices
	void tr();
	void lt();
	void setPerspective();
	void setLookAt();
	void setIdentity();
	void multByTrans();
	void multByRot();
};

