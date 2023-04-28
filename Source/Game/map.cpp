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
			switch (objtyp)
			{
			case Character:
				bob.x = j;
				bob.y = i;
				break;
			case Sbox :
				data[j][i].setbox = TRUE;
				break;
			case Mbox:
				data[j][i].setbox = TRUE;
				if (j > 0 && data[j - 1][i].setbox == TRUE && data[j - 1][i].ReturnObjectType() == Mbox)
					data[j][i].setbox = FALSE;
				break;
			case Lbox:
				data[j][i].setbox = TRUE;
				if (j > 0 && data[j - 1][i].setbox == TRUE && data[j - 1][i].ReturnObjectType() == Lbox)
					data[j][i].setbox = FALSE;
				else if (i > 0 && data[j][i - 1].setbox == TRUE && data[j][i - 1].ReturnObjectType() == Lbox)
					data[j][i].setbox = FALSE;
				else if (i > 0 && j > 0 && data[j - 1][i - 1].setbox == TRUE && data[j - 1][i - 1].ReturnObjectType() == Lbox)
					data[j][i].setbox = FALSE;
				break;
			default:
				data[j][i].setbox = FALSE;
				break;
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

void Map::MoveObject(int level, int move_tag, int move) {
	int x = 0, y = 0;
	switch (move_tag) {
	case 0:	// up
		y = -1;
		break;
	case 1:	// down
		y = 1;
		break;
	case 2:	// left
		x = -1;
		break;
	case 3:	// right
		x = 1;
		break;
	}

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
			else if (data[bob.x][bob.y - 1].ReturnObjectType() == Mbox) {
				int mboxtag = bob.x;
				if (data[bob.x - 1][bob.y - 1].ReturnObjectType() == Mbox)
					mboxtag = bob.x - 1; // character on box right
				else
					mboxtag = bob.x + 1; // character on box left
				if (bob.y - 2 <= 0 || data[bob.x][bob.y - 2].ReturnObjectType() == ImpassibleBlock || data[mboxtag][bob.y - 2].ReturnObjectType() == ImpassibleBlock) {
					break;
				}
				else {
					Object temp[2];
					temp[0] = data[bob.x][bob.y];
					temp[1] = data[mboxtag][bob.y];
					data[bob.x][bob.y] = data[bob.x][bob.y - 2];
					data[bob.x][bob.y - 2] = data[bob.x][bob.y - 1];
					data[mboxtag][bob.y] = data[mboxtag][bob.y - 2];
					data[mboxtag][bob.y - 2] = data[mboxtag][bob.y - 1];
					data[bob.x][bob.y - 1] = temp[0];
					data[mboxtag][bob.y - 1] = temp[1];
					bob.y -= 1;

					data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
					data[bob.x][bob.y - 1].SetImage(CPoint(bob.x, bob.y - 1), ori);
					data[mboxtag][bob.y].SetImage(CPoint(mboxtag, bob.y), ori);
					data[mboxtag][bob.y - 1].SetImage(CPoint(mboxtag, bob.y - 1), ori);
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
			else if (data[bob.x][bob.y + 1].ReturnObjectType() == Mbox) {
				int mboxtag = bob.x;
				if (data[bob.x - 1][bob.y + 1].ReturnObjectType() == Mbox)
					mboxtag = bob.x - 1; // character on box right
				else
					mboxtag = bob.x + 1; // character on box left
				if (bob.y + 2 >= height || data[bob.x][bob.y + 2].ReturnObjectType() == ImpassibleBlock || data[mboxtag][bob.y + 2].ReturnObjectType() == ImpassibleBlock) {
					break;
				}
				else {
					Object temp[2];
					temp[0] = data[bob.x][bob.y];
					temp[1] = data[mboxtag][bob.y];
					data[bob.x][bob.y] = data[bob.x][bob.y + 2];
					data[bob.x][bob.y + 2] = data[bob.x][bob.y + 1];
					data[mboxtag][bob.y] = data[mboxtag][bob.y + 2];
					data[mboxtag][bob.y + 2] = data[mboxtag][bob.y + 1];
					data[bob.x][bob.y + 1] = temp[0];
					data[mboxtag][bob.y + 1] = temp[1];
					bob.y += 1;

					data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
					data[bob.x][bob.y + 1].SetImage(CPoint(bob.x, bob.y + 1), ori);
					data[mboxtag][bob.y].SetImage(CPoint(mboxtag, bob.y), ori);
					data[mboxtag][bob.y + 1].SetImage(CPoint(mboxtag, bob.y + 1), ori);
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


ObjectType Map::ReturnObjectType(int x, int y) {
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
