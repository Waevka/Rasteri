#pragma once


struct Triangle {
public:
	WVertex *A, *B, *C;
	Triangle();
	Triangle(WVertex *_A, WVertex *_B, WVertex *_C);
	/*Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3);
	Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3, WColor _color);
	Triangle(WFloat3 v1, WFloat3 v2, WFloat3 v3,
		WColor _color1, WColor _color2, WColor _color3);
		*/
	~Triangle();
	void intersectTriangle(float x, float y, HitInfo *hi);
	WVertex operator/=(float f);
};

