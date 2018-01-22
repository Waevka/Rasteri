#include "stdafx.h"
#include "FragmentProcessor.h"
#define XDELWIDTH BWIDTH * 0.5

FragmentProcessor::FragmentProcessor()
{
	deltaX = 1.0 / (float)BWIDTH;
	deltaY = 1.0 / (float)BHEIGHT;
}


FragmentProcessor::~FragmentProcessor()
{
}

void FragmentProcessor::processTriangle(Buffer & buffer)
{	
	HitInfo hitInfo;
	float currentDepth;
	WColor color;
	//set up buffer min max values
	minmax(buffer.minx, buffer.miny, buffer.maxx, buffer.maxy);

	for (float x = buffer.minx; x < buffer.maxx; x += deltaX)
	{
		for (float y = buffer.miny; y < buffer.maxy; y += deltaY)
		{	
			//keep hit info in a structure
			trngl->intersectTriangle(x, y, hitInfo);
			if (hitInfo.hasHit) {

				//currentDepth = trngl->A->pos.z * hitInfo.hitPoint.x
				//	+ trngl->B->pos.z * hitInfo.hitPoint.y
				//	+ trngl->C->pos.z * hitInfo.hitPoint.z;
				WFloat4 sum = _mm_mul_ps(trngl->getZPositions(), hitInfo.hitPoint.m);
				sum.m = _mm_hadd_ps(sum.m, sum.m);
				sum.m = _mm_hadd_ps(sum.m, sum.m);
				currentDepth = sum.x;

				if (currentDepth <= 1 && currentDepth >= 0)
				{	
					// use halfpixel
					int xDel = XDELWIDTH * (x + 1);
					int	yDel = (float)BHEIGHT * 0.5f * (y + 1);

					if (currentDepth < buffer.depth[(BWIDTH * yDel + xDel)] || buffer.depth[(BWIDTH * yDel + xDel)] == 1)
					{
						color = processColor(hitInfo);
						buffer.writeColor(xDel, yDel, color, currentDepth);
					}
				}
			}
		}
	}
}

WColor FragmentProcessor::processColor(HitInfo hi)
{
	WColor ambientMaterial = (trngl->A->color * hi.hitPoint.x
							+ trngl->B->color * hi.hitPoint.y
							+ trngl->C->color * hi.hitPoint.z);

	WColor result = 0xFF000000;
	//WColor ambient(0);
	//WColor diffuse(0);
	//WColor specular(0);

	/*WFloat4 hitPoint(trngl->A->pos * hi.hitPoint.x 
					+ trngl->B->pos * hi.hitPoint.y 
					+ trngl->C->pos * hi.hitPoint.z);*/
	
	hitPoint.m = _mm_add_ps( _mm_add_ps((
										_mm_mul_ps(trngl->A->pos.m, _mm_set1_ps(hi.hitPoint.x))),
										_mm_mul_ps(trngl->B->pos.m, _mm_set1_ps(hi.hitPoint.y))),
							_mm_mul_ps(trngl->C->pos.m, _mm_set1_ps(hi.hitPoint.z)));

	//hitPoint.m = _mm_add_ps( _mm_add_ps((trngl->A->pos * hi.hitPoint.x).m, (trngl->B->pos * hi.hitPoint.y).m), (trngl->C->pos * hi.hitPoint.z).m);

	/*WFloat4 normal(trngl->A->normal * hi.hitPoint.x 
					+ trngl->B->normal * hi.hitPoint.y
					+ trngl->C->normal * hi.hitPoint.z);*/
	
	normal.m = _mm_add_ps(_mm_add_ps((_mm_mul_ps(trngl->A->normal.m, _mm_set1_ps(hi.hitPoint.x))), _mm_mul_ps(trngl->B->normal.m, _mm_set1_ps(hi.hitPoint.y))), _mm_mul_ps(trngl->C->normal.m, _mm_set1_ps(hi.hitPoint.z)));

	//normal.m = _mm_add_ps(_mm_add_ps((trngl->A->normal * hi.hitPoint.x).m, (trngl->B->normal * hi.hitPoint.y).m), (trngl->C->normal * hi.hitPoint.z).m);

	normal.normalizeSSE();

	for (int i = 0; i < lights.size(); ++i)
	{
		Light *light = lights[i];
		WFloat4 lightDirection = light->getDirection(hitPoint);
		lightDirection.normalizeSSE();
		//diffuse
		float dotN = std::max(0.0f, std::min(lightDirection.dotProductSSE(normal), 1.0f));
		result += (ambientMaterial * (*light->getDiffuse()) * dotN);
		//ambient
		result += (*light->getAmbient());
		//specular
		result += (*light->getSpecular());
	}

	return result;
}

void inline FragmentProcessor::minmax(float & minx, float & miny, float & maxx, float & maxy)
{
	maxx = (trngl->A->pos.x > trngl->B->pos.x) ? trngl->A->pos.x : trngl->B->pos.x;
	maxx = (maxx > trngl->C->pos.x) ? maxx : trngl->C->pos.x;

	minx = (trngl->A->pos.x < trngl->B->pos.x) ? trngl->A->pos.x : trngl->B->pos.x;
	minx = (minx < trngl->C->pos.x) ? minx : trngl->C->pos.x;

	maxy = (trngl->A->pos.y > trngl->B->pos.y) ? trngl->A->pos.y : trngl->B->pos.y;
	maxy = (maxy > trngl->C->pos.y) ? maxy : trngl->C->pos.y;

	miny = (trngl->A->pos.y < trngl->B->pos.y) ? trngl->A->pos.y : trngl->B->pos.y;
	miny = (miny < trngl->C->pos.y) ? miny : trngl->C->pos.y;

	maxx>1 ? maxx = 1 : maxx<-1 ? maxx = -1 : true;
	maxy>1 ? maxy = 1 : maxy<-1 ? maxy = -1 : true;

	minx>1 ? minx = 1 : minx<-1 ? minx = -1 : true;
	miny>1 ? miny = 1 : miny<-1 ? miny = -1 : true;

}

