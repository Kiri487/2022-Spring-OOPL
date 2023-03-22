#pragma once
#include <vector>

// 地圖定義
#define MAP1 "Resources/map1.txt"

class Map {
private:
	int width, height;
	std::vector<std::vector<int>> data;

public:
	Map(int width, int height);

	void matrix();
};


