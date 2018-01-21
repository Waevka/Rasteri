#include "stdafx.h"
#include "VertexProcessor.h"

inline __m128 CrossProduct(__m128 u, __m128 v) {
	return _mm_sub_ps(
		_mm_mul_ps(
			_mm_shuffle_ps(u, u, _MM_SHUFFLE(3, 0, 2, 1)),
			_mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 1, 0, 2))),
		_mm_mul_ps(
			_mm_shuffle_ps(u, u, _MM_SHUFFLE(3, 1, 0, 2)),
			_mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 2, 1)))
	);
}

VertexProcessor::VertexProcessor()
{
}


VertexProcessor::~VertexProcessor()
{
}

void VertexProcessor::processTransformations(ObjMesh *mesh, WFloat4 OX, WFloat4 OY, WFloat4 OZ, std::vector<Light*> lights)
{
	vertices = mesh->vertices;
	this->lights = lights;

	multByTrans(mesh->Tv);
	multByRot(mesh->Rv.x, OX);
	multByRot(mesh->Rv.y, OY);
	multByRot(mesh->Rv.z, OZ);
	multByScale(mesh->Sv);
	transform();

}

void VertexProcessor::tr()
{
}

void VertexProcessor::lt()
{
}

void VertexProcessor::setPerspective(float fov, float ratio, float near, float far)
{
	if (far != near) {

		float inv = 1.0f / (near - far);
		fov *= M_PI / 360;
		float s = std::sin(fov);
		float f;

		if (s != 0) {
			f = std::cos(fov) / s;
		}
		else 
		{ 
			f = std::cos(fov) / 0.0001f;
		}

		ratio = 1.0f / ratio;

		WFloat4x4 Perspective = { { f * ratio, 0, 0, 0 },
							{ 0, f, 0, 0 },
							{ 0, 0, (far + near) * inv,  (2 * far * near) * inv },
							{ 0, 0, -1, 0 } };

		P = Perspective;
	}
}

void VertexProcessor::lookAt(WFloat4 up, WFloat4 eye, WFloat4 target)
{
	up = up.normalize();
	WFloat4 forward = WFloat4(eye, target).normalize();
	//WFloat4 right = WFloat4::crossProduct(up, forward).normalize();
	WFloat4 right;
	right.m = CrossProduct(up.m, forward.m);
	right.normalize();
	//up = WFloat4::crossProduct(forward, right);
	up = CrossProduct(forward.m, right.m);

	WFloat4x4 Mov = { { 1, 0, 0, -eye.x },
					{ 0, 1, 0, -eye.y },
					{ 0, 0, 1, -eye.z },
					{ 0, 0, 0, 1 } };

	WFloat4x4 Rot = { { right.x, right.y, right.z, 0 },
					{ up.x, up.y, up.z, 0 },
					{ -forward.x, -forward.y, -forward.z, 0 },
					{ 0, 0, 0, 1 } };

	V = Rot * Mov;
}

void VertexProcessor::multByTrans(WFloat4 v)
{
	WFloat4x4 T = { { 1, 0, 0, v.x },
				{ 0, 1, 0, v.y },
				{ 0, 0, 1, v.z },
				{ 0, 0, 0, 1 } };
	M = T * M;
}

void VertexProcessor::multByRot(float a, WFloat4 v)
{
	float radians = M_PI / 180.0f;
	float s = std::sin(a * radians);
	float c = std::cos(a * radians);
	v = v.normalize();

	WFloat4x4 R = { { v.x * v.x * (1 - c) + c,
					v.x * v.y * (1 - c) - v.z * s,
					v.x * v.z * (1 - c) + v.y * s,
					0 },
					{ v.x * v.y * (1 - c) + v.z * s,
					v.y * v.y * (1 - c) + c,
					v.z * v.y * (1 - c) - v.x * s,
					0 },
					{ v.x * v.z * (1 - c) - v.y * s,
					v.z * v.y * (1 - c) + v.x * s,
					v.z * v.z * (1 - c) + c ,
					0 },
					{ 0, 0 , 0 , 1 } };
	M = R * M;
}

void VertexProcessor::multByScale(WFloat4 v)
{
	WFloat4x4 S = { { v.x, 0,   0,   0 },
					{ 0,   v.y, 0,   0 },
					{ 0,   0,   v.z, 0 },
					{ 0,   0,   0,   1 } };
	M = S * M;
}

void VertexProcessor::setIdentity()
{
	M = WFloat4x4::identity();
	V = WFloat4x4::identity();
	P = WFloat4x4::identity();
}

void VertexProcessor::transform()
{
	WFloat4x4 MVP = P * V * M;
	WFloat4x4 MVT = MVP.transpose();

	for (int i = 0; i < vertices.size(); i++)
	{	
		vertices[i]->transform(MVP, MVT);
	}

	for (int i = 0; i < lights.size(); i++)
	{
		(*lights[i]) *= (MVP);
	}
}
