#include "stdafx.h"
#include "FragmentProcessor.h"


FragmentProcessor::FragmentProcessor()
{
}


FragmentProcessor::~FragmentProcessor()
{
}

void FragmentProcessor::processTriangle(Buffer & buffer)
{
	//set up buffer min max values
	minmax(buffer.minx, buffer.miny, buffer.maxx, buffer.maxy);
	//calculate size between each pixel
	float deltaX = 1.0 / buffer.width;
	float deltaY = 1.0 / buffer.height;

	for (float x = buffer.minx; x < buffer.maxx; x += deltaX)
	{
		for (float y = buffer.miny; y < buffer.maxy; y += deltaY)
		{	
			//keep hit info in a structure
			HitInfo hitInfo = trngl->intersectTriangle(x, y);
			if (hitInfo.hasHit) {

				float currentDepth = trngl->A->pos.z * hitInfo.hitPoint.x
					+ trngl->B->pos.z * hitInfo.hitPoint.y
					+ trngl->C->pos.z * hitInfo.hitPoint.z;

				if (currentDepth <= 1 && currentDepth >= 0)
				{	
					// use halfpixel
					int xDel = buffer.width * 0.5f * (x + 1);
					int	yDel = buffer.height * 0.5f * (y + 1);

					//first test
					bool depthTest1;
					if (currentDepth < buffer.depth[(int)(buffer.width * yDel + xDel)]) {
						depthTest1 = true;
					}
					else {
						depthTest1 = false;
					}
					//second test
					bool depthTest2; 
					if (buffer.depth[(int)(buffer.width * yDel + xDel)] == 1) {
						depthTest2 = true;
					}
					else {
						depthTest2 = false;
					}

					if (depthTest1 || depthTest2)
					{
						WColor color = processColor(hitInfo);
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
	WColor ambient(0);
	WColor diffuse(0);
	WColor specular(0);

	/*WFloat4 hitPoint(trngl->A->pos * hi.hitPoint.x 
					+ trngl->B->pos * hi.hitPoint.y 
					+ trngl->C->pos * hi.hitPoint.z);*/
	
	hitPoint.m = _mm_add_ps( _mm_add_ps((trngl->A->pos * hi.hitPoint.x).m, (trngl->B->pos * hi.hitPoint.y).m), (trngl->C->pos * hi.hitPoint.z).m);

	/*WFloat4 normal(trngl->A->normal * hi.hitPoint.x 
					+ trngl->B->normal * hi.hitPoint.y
					+ trngl->C->normal * hi.hitPoint.z);*/
	
	normal.m = _mm_add_ps(_mm_add_ps((trngl->A->normal * hi.hitPoint.x).m, (trngl->B->normal * hi.hitPoint.y).m), (trngl->C->normal * hi.hitPoint.z).m);

	normal.normalizeSSE();

	for (int i = 0; i < lights.size(); i++)
	{
		Light *light = lights[i];
		WFloat4 lightDirection = light->getDirection(hitPoint);
		lightDirection.normalizeSSE();
		//diffuse
		float dotN = std::max(0.0f, std::min(lightDirection.dotProductSSE(normal), 1.0f));
		diffuse += (ambientMaterial * (*light->getDiffuse()) * dotN);
		result += diffuse;
		//ambient
		ambient += (*light->getAmbient());
		result += ambient;
		//specular
		specular += (*light->getSpecular());
		result += specular;
	}

	return result;
}

void FragmentProcessor::minmax(float & minx, float & miny, float & maxx, float & maxy)
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
