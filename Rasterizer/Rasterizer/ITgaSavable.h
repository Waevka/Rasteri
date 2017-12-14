#pragma once
class ITgaSavable
{
public:
	virtual bool writeToFile(Buffer buffer) = 0;
};

