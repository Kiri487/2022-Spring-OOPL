#include "stdafx.h"
#include "map.h"

Map::Map(int width, int height) {
	this->width = width;
	this->height = height;
	for (int i = 0; i <= width; i++) {
		data.push_back(std::vector<int>(height, 0));
	}
}

void Map::matrix() {
/*
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (data[i][j] == 0) {
				data[i][j] = 1;
			}
			else {
				data[i][j] = 0;
			}
		}
	}
*/
	data = {
		{1, 1, 1, 1, 1, 1},
		{1, 1, 1, 0, 0, 1},
		{1, 1, 1, 0, 0, 1},
		{0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 1}
	};
}



