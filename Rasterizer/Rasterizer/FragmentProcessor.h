#pragma once
class FragmentProcessor
{
public:
	Triangle* trngl;
	std::vector<Light*> lights;
	FragmentProcessor();
	~FragmentProcessor();
	void processTriangle(Buffer &buffer);
	WFloat4 hitPoint;
	WFloat4 normal;
	float deltaX, deltaY;
private:
	WColor processColor(HitInfo hi, WVertex &VertA, WVertex &VertB, WVertex &VertC);
	void inline minmax(float &minx, float &miny, float &maxx, float &maxy);
};

