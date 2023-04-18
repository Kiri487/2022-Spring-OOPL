#include "stdafx.h"
#include "map.h"
#include <fstream>
#include <string>


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
			if (objtyp == Character) {
				bob.x = j;
				bob.y = i;
			}
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


void Map::MoveObject(int level, int move) {
	ori = ReturnOri(level);
	switch (move) {
	case 0: // up
		if (bob.y - 1 >= 0 && data[bob.x][bob.y - 1].ReturnObjectType() != ImpassibleBlock) {
			// no box
			if (data[bob.x][bob.y - 1].ReturnObjectType() == PassibleBlock) {
				Object temp;
				temp = data[bob.x][bob.y];
				data[bob.x][bob.y] = data[bob.x][bob.y - 1];
				data[bob.x][bob.y - 1] = temp;
				bob.y -= 1;

				data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
			}

			// has Sbox
			else if (data[bob.x][bob.y - 1].ReturnObjectType() == Sbox) {
				if (bob.y - 2 <= 0 || data[bob.x][bob.y - 2].ReturnObjectType() == ImpassibleBlock) {
					break;
				}
				else {
					Object temp;
					temp = data[bob.x][bob.y];
					data[bob.x][bob.y] = data[bob.x][bob.y - 2];
					data[bob.x][bob.y - 2] = data[bob.x][bob.y - 1];
					data[bob.x][bob.y - 1] = temp;
					bob.y -= 1;

					data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
					data[bob.x][bob.y - 1].SetImage(CPoint(bob.x, bob.y - 1), ori);
				}
			}
		}
		break;
	case 1: // down
		if (bob.y + 1 < height &&  data[bob.x][bob.y + 1].ReturnObjectType() != ImpassibleBlock) {
			// no box
			if (data[bob.x][bob.y + 1].ReturnObjectType() == PassibleBlock) {
				Object temp;
				temp = data[bob.x][bob.y];
				data[bob.x][bob.y] = data[bob.x][bob.y + 1];
				data[bob.x][bob.y + 1] = temp;
				bob.y += 1;

				data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
			}

			// has box
			else if (data[bob.x][bob.y + 1].ReturnObjectType() == Sbox) {
				//no box
				if (bob.y + 2 >= height || data[bob.x][bob.y + 2].ReturnObjectType() == ImpassibleBlock) {
					break;
				}
				else {
					Object temp;
					temp = data[bob.x][bob.y];
					data[bob.x][bob.y] = data[bob.x][bob.y + 2];
					data[bob.x][bob.y + 2] = data[bob.x][bob.y + 1];
					data[bob.x][bob.y + 1] = temp;
					bob.y += 1;

					data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
					data[bob.x][bob.y + 1].SetImage(CPoint(bob.x, bob.y + 1), ori);
				}
			}
		}
		break;

	case 2: // left
		if (bob.x - 1 >= 0 && data[bob.x - 1][bob.y].ReturnObjectType() != ImpassibleBlock) {
			// no box
			if (data[bob.x - 1][bob.y].ReturnObjectType() == PassibleBlock) {
				Object temp;
				temp = data[bob.x][bob.y];
				data[bob.x][bob.y] = data[bob.x - 1][bob.y];
				data[bob.x - 1][bob.y] = temp;
				bob.x -= 1;

				data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
			}

			// has box
			else if (data[bob.x - 1][bob.y].ReturnObjectType() == Sbox) {
				if (bob.x - 2 <= 0 || data[bob.x - 2][bob.y].ReturnObjectType() == ImpassibleBlock) {
					break;
				}
				else {
					Object temp;
					temp = data[bob.x][bob.y];
					data[bob.x][bob.y] = data[bob.x - 2][bob.y];
					data[bob.x - 2][bob.y] = data[bob.x - 1][bob.y];
					data[bob.x - 1][bob.y] = temp;
					bob.x -= 1;

					data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
					data[bob.x - 1][bob.y].SetImage(CPoint(bob.x - 1, bob.y), ori);
				}
			}
		}
		break; 

	case 3: // right
		if (bob.x + 1 <=  width && data[bob.x + 1][bob.y].ReturnObjectType() != ImpassibleBlock) {
			// no box
			if (data[bob.x + 1][bob.y].ReturnObjectType() == PassibleBlock) {
				Object temp;
				temp = data[bob.x][bob.y];
				data[bob.x][bob.y] = data[bob.x + 1][bob.y];
				data[bob.x + 1][bob.y] = temp;
				bob.x += 1;

				data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
			}

				// has box
				else if (data[bob.x + 1][bob.y].ReturnObjectType() == Sbox) {
					if (bob.x + 2 >= width || data[bob.x + 2][bob.y].ReturnObjectType() == ImpassibleBlock) {
						break;
					}
					else {
						Object temp;
						temp = data[bob.x][bob.y];
						data[bob.x][bob.y] = data[bob.x + 2][bob.y];
						data[bob.x + 2][bob.y] = data[bob.x + 1][bob.y];
						data[bob.x + 1][bob.y] = temp;
						bob.x += 1;

						data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
						data[bob.x + 1][bob.y].SetImage(CPoint(bob.x + 1, bob.y), ori);
					}
				}
			}

		break;
	default:
		break;
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
	case Character:
		type = "2";
		break;

	default:
		type = "x";
		break;
	}
	
	return type;
}
