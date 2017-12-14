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
	float stepx = 1.0 / buffer.width;
	float stepy = 1.0 / buffer.height;

	minmax(buffer.minx, buffer.miny, buffer.maxx, buffer.maxy);

	for (float x = buffer.minx; x < buffer.maxx; x += stepx)
	{
		for (float y = buffer.miny; y < buffer.maxy; y += stepy)
		{
			HitInfo hitInfo = trngl->intersect(x, y);
			if (hitInfo.hasHit) {
				float depth = (trngl->A->pos.z * hitInfo.area.x)
					+ (trngl->B->pos.z * hitInfo.area.y)
					+ (trngl->C->pos.z * hitInfo.area.z);
				//interpolate the color between vertices
				if (depth >= 0 && depth <= 1)
				{
					int x1 = (x + 1) * buffer.width * 0.5f;
					int	y1 = (y + 1) * buffer.height * 0.5f;
					bool b1 = (depth < buffer.depth[(int)(buffer.width * y1 + x1)]);
					bool b2 = buffer.depth[(int)(buffer.width * y1 + x1)] == 1;
					if (b1 || b2)
					{
						WColor color = shade(hitInfo);
						buffer.writeColor(x1, y1, color, depth);
					}
				}
			}
		}
	}
}

WColor FragmentProcessor::shade(HitInfo hi)
{
	WColor ambientMaterial = (trngl->A->color * hi.area.x
		+ trngl->B->color * hi.area.y
		+ trngl->C->color * hi.area.z);

	WColor result = 0xFF000000;
	WColor ambient = 0;
	WColor diffuse = 0;
	WColor specular = 0;

	WFloat4 hitPoint(trngl->A->pos * hi.area.x 
		+ trngl->B->pos * hi.area.y 
		+ trngl->C->pos * hi.area.z);

	WFloat4 normal(trngl->A->normal * hi.area.x 
		+ trngl->B->normal * hi.area.y
		+ trngl->C->normal * hi.area.z);
	normal = normal.normalize();

	for (int i = 0; i < lights.size(); i++)
	{
		Light *light = lights[i];

		ambient = ambient + light->getAmbient();

		WFloat4 lightVec = light->getVector(hitPoint);
		lightVec = lightVec.normalize();

		float LdotN = std::min(WFloat4::dotProduct(lightVec, normal), 1.0f);
		diffuse + (ambientMaterial * light->getDiffuse() * std::max(0.0f, LdotN));

		specular = specular + light->getSpecular();
		result = result + ambient + diffuse + specular;
	}

	return result;
}

void FragmentProcessor::minmax(float & minx, float & miny, float & maxx, float & maxy)
{
	//define minmax values for canvas
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
