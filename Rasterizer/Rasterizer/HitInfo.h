#pragma once
struct HitInfo
{
public:
	bool hasHit = false;
	WFloat4 hitPoint;
	HitInfo();
	~HitInfo();
};

