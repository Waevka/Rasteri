#include "stdafx.h"
#include "Triangle.h"


Triangle::Triangle()
{
	A = new WVertex();
	B = new WVertex();
	C = new WVertex();
}

Triangle::Triangle(WVertex * _A, WVertex * _B, WVertex * _C)
{
	A = _A;
	B = _B;
	C = _C;
}

Triangle::~Triangle()
{
}

void Triangle::intersectTriangle(float x, float y, HitInfo &hitInfo)
{	

	float BCy = B->pos.y - C->pos.y;
	float CBx = C->pos.x - B->pos.x;
	float ACx = A->pos.x - C->pos.x;
	float CAy = C->pos.y - A->pos.y;
	float xc = x - C->pos.x;
	float yc = y - C->pos.y;

	double AB = (A->pos.x - B->pos.x) * (y - A->pos.y) - (A->pos.y - B->pos.y) * (x - A->pos.x); // P1, P2, P
	double BC = (-CBx) * (y - B->pos.y) - (BCy) * (x - B->pos.x); // P2, P3, P
	double CA = (-ACx) * (yc)-(CAy) * (xc); // P3, P1, P

	hitInfo.hasHit = AB >= 0 && BC >= 0 && CA >= 0;

	if (hitInfo.hasHit) {
		double L1 = ((BCy * xc) + (CBx * yc)) / ((BCy *  ACx) + (CBx * (-CAy)));
		double L2 = ((CAy * xc) + (ACx * yc)) / ((CAy *(-CBx)) + (ACx *   BCy));
		double L3 = 1 - L1 - L2;

		hitInfo.hitPoint.x = L1;
		hitInfo.hitPoint.y = L2;
		hitInfo.hitPoint.z = L3;
	}
}

__m128 Triangle::getZPositions()
{
	return _mm_set_ps(0.0f, C->pos.z, B->pos.z, A->pos.z);
}

