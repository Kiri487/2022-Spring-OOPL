#pragma once
#include <vector>
#include "Object.h"

class Map {
private:
	std::vector<std::vector<Object>> data;
	int level;

public:
	int width, height;
	void Matrix(int level);
	void Show();
	
};


