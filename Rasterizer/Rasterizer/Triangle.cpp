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

void Triangle::intersectTriangle(float x, float y, HitInfo *hi)
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

	hi->hasHit = AB >= 0 && BC >= 0 && CA >= 0;

	if (hi->hasHit) {
		double L1 = ((BCy * xc) + (CBx * yc)) / ((BCy *  ACx) + (CBx * (-CAy)));
		double L2 = ((CAy * xc) + (ACx * yc)) / ((CAy *(-CBx)) + (ACx *   BCy));
		double L3 = 1 - L1 - L2;

		hi->hitPoint.x = L1;
		hi->hitPoint.y = L2;
		hi->hitPoint.z = L3;
	}

}

