#include "stdafx.h"
#include "VertexProcessor.h"


VertexProcessor::VertexProcessor()
{
}


VertexProcessor::~VertexProcessor()
{
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

		float f_n = 1.0f / (near - far);
		fov *= M_PI / 360;
		float s = std::sin(fov);
		float f = s != 0 ? std::cos(fov) / s : std::cos(fov) / 0.0001f;
		ratio = 1.0f / ratio;

		WFloat4x4 Persp = { { f*ratio, 0, 0, 0 },
							{ 0, f, 0, 0 },
							{ 0, 0, (far + near)*f_n,  (2 * far*near)*f_n },
							{ 0, 0, -1, 0 } };

		P = Persp;
	}
}

void VertexProcessor::lookAt(WFloat4 up, WFloat4 eye, WFloat4 target)
{
	up = up.normalize();
	WFloat4 forward = WFloat4(eye, target).normalize();
	WFloat4 right = WFloat4::crossProduct(up, forward).normalize();
	up = WFloat4::crossProduct(forward, right);

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

void VertexProcessor::translate(WFloat4 v)
{
	WFloat4x4 T = { { 1, 0, 0, v.x },
				{ 0, 1, 0, v.y },
				{ 0, 0, 1, v.z },
				{ 0, 0, 0, 1 } };
	M = T * M;
}

void VertexProcessor::rotate(float a, WFloat4 v)
{
	float rad = M_PI / 180.0f;

	float s = std::sin(a*rad), c = std::cos(a*rad);

	v = v.normalize();

	WFloat4x4 R = { { v.x*v.x*(1 - c) + c, v.x*v.y*(1 - c) - v.z*s, v.x*v.z*(1 - c) + v.y*s, 0 },
					{ v.x*v.y*(1 - c) + v.z*s,  v.y*v.y*(1 - c) + c, v.z*v.y*(1 - c) - v.x*s, 0 },
					{ v.x*v.z*(1 - c) - v.y*s, v.z*v.y*(1 - c) + v.x*s, v.z*v.z*(1 - c) + c , 0 },
					{ 0, 0 , 0 , 1 } };

	M = R * M;
}

void VertexProcessor::scale(WFloat4 v)
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

void VertexProcessor::multByTrans()
{
}

void VertexProcessor::multByRot()
{
}

void VertexProcessor::transform()
{
	WFloat4x4 MVP = P * V * M;
	WFloat4x4 MVT = MVP.transpose();

	for (int i = 0; i < vertexBuffer.size(); i++)
	{	
		std::cout << "Before: " << vertexBuffer[i]->pos.x << " "
			<< vertexBuffer[i]->pos.y << " "
			<< vertexBuffer[i]->pos.z << " "
			<< vertexBuffer[i]->pos.w << std::endl;

		vertexBuffer[i]->transform(MVP, MVT);

		std::cout << "After: " << vertexBuffer[i]->pos.x << " "
			<< vertexBuffer[i]->pos.y << " "
			<< vertexBuffer[i]->pos.z << " "
			<< vertexBuffer[i]->pos.w << std::endl;

	}

	for (int i = 0; i < lightBuffer.size(); i++)
	{
		lightBuffer[i]->operator*=(MVP);

	}
}
