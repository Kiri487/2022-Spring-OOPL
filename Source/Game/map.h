#pragma once
#include <vector>
#include <string>

// 地圖定義
#define MAP1 "Resources/map1.txt"

class Map {
private:
	int width, height;
	std::vector<std::vector<int>> data;
	int level;

public:
	Map(int width, int height);
	void matrix(int level);
};


