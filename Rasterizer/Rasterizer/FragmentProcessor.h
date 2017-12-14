#pragma once
class FragmentProcessor
{
public:
	Triangle* trngl;
	std::vector<Light*> lights;
	FragmentProcessor();
	~FragmentProcessor();
	void processTriangle(Buffer &buffer);
private:
	WColor processColor(HitInfo hi);
	void minmax(float &minx, float &miny, float &maxx, float &maxy);
};

