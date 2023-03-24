#include "stdafx.h"
#include "map.h"
#include <fstream>

Map::Map(int width, int height) {
	this->width = width;
	this->height = height;
	for (int i = 0; i <= width; i++) {
		data.push_back(std::vector<int>(height, 0));
	}
}

void Map::matrix(int level) {
	std::string filename = "map/map" + std::to_string(level) + ".txt";
	std::ifstream ifs(filename);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			ifs >> data[i][j];
		}
	}

	ifs.close();
}



