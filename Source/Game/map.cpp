#include "stdafx.h"
#include "map.h"
#include <fstream>
#include <string>
#include "log.hpp"


void Map::Matrix(int level) {
	std::string filename = "Resources/map" + std::to_string(level) + ".txt";
	std::ifstream ifs(filename);

	CPoint ori, mapsize;
	ifs >> ori.x;
	ifs >> ori.y;
	ifs >> mapsize.x;
	ifs >> mapsize.y;

	for (int i = 0; i <= width; i++) {
		data[i].clear();
	}
	data.clear();
	this->width = mapsize.x;
	this->height = mapsize.y;
	for (int i = 0; i <= width; i++) {
		data.push_back(std::vector<Object>(height));
	}

	for (int i = 0; i < mapsize.y; i++) {
		int num;
		for (int j = 0; j < mapsize.x; j++) {
			ifs >> num;
			ObjectType objtyp;
			objtyp = static_cast<ObjectType>(num);
			data[j][i].LoadObjectImage(objtyp, CPoint(j, i), ori);
		}
	}

	

	ifs.close();
}

void Map::Show() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			data[i][j].ShowObjectImage();
		}
	}
}

CPoint Map::ReturnOri(int level) {
	std::string filename = "Resources/map" + std::to_string(level) + ".txt";
	std::ifstream ifs(filename);

	CPoint ori;
	ifs >> ori.x;
	ifs >> ori.y;

	return ori;
}


void Map::MoveObject(int level, int x, int y, int move) {
	CPoint ori = ReturnOri(level);
	if (data[x][y].ReturnObjectType() == Character) {
		switch (move) {
		case 0: // up
			if (y - 1 >= 0 && data[x][y-1].ReturnObjectType() != ImpassibleBlock) {
				data[x][y].LoadObjectImage(PassibleBlock, CPoint(x, y), ori);
				data[x][y - 1].LoadObjectImage(Character, CPoint(x, y - 1), ori);
			}
			break;
		case 1: // down
			if (y + 1 <= height && data[x][y + 1].ReturnObjectType() != ImpassibleBlock) {
				if (data[x][y + 1].ReturnObjectType() == Sbox && data[x][y + 2].ReturnObjectType() != ImpassibleBlock) {
					data[x][y + 2].LoadObjectImage(Sbox, CPoint(x, y + 2), ori);
					data[x][y + 1].LoadObjectImage(PassibleBlock, CPoint(x, y + 1), ori);
				}
				data[x][y].LoadObjectImage(PassibleBlock, CPoint(x, y), ori);
				data[x][y + 1].LoadObjectImage(Character, CPoint(x, y + 1), ori);
					
			}
			break;
		case 2: // left
			if (x - 1 >= 0 && data[x - 1][y].ReturnObjectType() != ImpassibleBlock) {
				data[x][y].LoadObjectImage(PassibleBlock, CPoint(x, y), ori);
				data[x - 1][y].LoadObjectImage(Character, CPoint(x - 1, y), ori);
			}
			break; 
		case 3: // right
			if (x + 1 <= width && data[x + 1][y].ReturnObjectType() != ImpassibleBlock) {
				data[x][y].LoadObjectImage(PassibleBlock, CPoint(x, y), ori);
				data[x + 1][y].LoadObjectImage(Character, CPoint(x + 1, y), ori);
			}
			break;
		default:
			break;
		}
	}
}


ObjectType Map::ReturnObjectType(Object object, int x, int y) {
	return data[x][y].ReturnObjectType();
}

string Map::PrintObjectType(int x, int y) {
	ObjectType objecttype = data[x][y].ReturnObjectType();
	string type;
	switch (objecttype) {
	case ImpassibleBlock:
		type = "0";
		break;
	case PassibleBlock:
		type = "1";
		break;
	default:
		type = "x";
		break;
	}
	
	return type;
}

