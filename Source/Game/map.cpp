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

	MapStep.push(GetNowMap());
	BobStep.push(bob);
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

bool Map::boundary(CPoint target, int movetag) {
	bool tag = true;
	switch(movetag){
	case 0:	// up
		if (target.y < 0)
			tag = false;
		break;
	case 1:	// down
		if (target.y > height)
			tag = false;
		break;
	case 2:	// left
		if (target.x < 0)
			tag = false;
		break;
	case 3:	// right
		if (target.x > width)
			tag = false;
		break;
	}
	return tag;
}

CPoint Map::return_move(int movetag) {
	CPoint move = (0, 0);
	ori = ReturnOri(level);
	switch (movetag) {
	case 0:	// up
		move.y = -1;
		break;
	case 1:	// down
		move.y = 1;
		break;
	case 2:	// left
		move.x = -1;
		break;
	case 3:	// right
		move.x = 1;
		break;
	}
	return move;
}

void Map::movenobox(int level, int movetag) {
	CPoint move = return_move(movetag);

	ori = ReturnOri(level);

	if (data[bob.x + move.x][bob.y + move.y].ReturnObjectType() != PassibleBlock)
		return;

	Object temp;
	temp = data[bob.x][bob.y];
	data[bob.x][bob.y] = data[bob.x + move.x][bob.y + move.y];
	data[bob.x + move.x][bob.y + move.y] = temp;
	bob.x += move.x;
	bob.y += move.y;

	data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
}

void Map::moveSbox(int level, int movetype) {

	CPoint move = return_move(movetype);

	if (data[bob.x + 2 * move.x][bob.y + 2 * move.y].ReturnObjectType() == Hole) {
		data[bob.x + 2 * move.x][bob.y + 2 * move.y].changeObjecttype(PassibleBlock);
		data[bob.x + move.x][bob.y + move.y].changeObjecttype(PassibleBlock);
	}
		

	ori = ReturnOri(level);
	Object temp;
	temp = data[bob.x][bob.y];
	data[bob.x][bob.y] = data[bob.x + 2*move.x][bob.y + 2*move.y];
	data[bob.x + 2*move.x][bob.y + 2*move.y] = data[bob.x + move.x][bob.y + move.y];
	data[bob.x + move.x][bob.y + move.y] = temp;
	bob.x += move.x;
	bob.y += move.y;

	data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
	data[bob.x + move.x][bob.y + move.y].SetImage(CPoint(bob.x + move.x, bob.y + move.y), ori);
	
}

void Map::moveMbox(int level, int movetype, int mboxtag) {
	CPoint move = return_move(movetype);
	ori = ReturnOri(level);
	Object temp;
	if (movetype == 0 || movetype == 1) {
		temp = data[mboxtag][bob.y + 2 * move.y];
		data[mboxtag][bob.y + 2 * move.y] = data[mboxtag][bob.y + move.y];
		data[mboxtag][bob.y + move.y] = temp;

		temp = data[mboxtag + 1][bob.y + 2 * move.y];
		data[mboxtag + 1][bob.y + 2 * move.y] = data[mboxtag + 1][bob.y + move.y];
		data[mboxtag + 1][bob.y + move.y] = temp;

		temp = data[bob.x][bob.y + move.y];
		data[bob.x][bob.y + move.y] = data[bob.x][bob.y];
		data[bob.x][bob.y] = temp;
		
		bob.x += move.x;
		bob.y += move.y;
		data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
		data[bob.x + move.x][bob.y + move.y].SetImage(CPoint(bob.x + move.x, bob.y + move.y), ori);
		data[mboxtag][bob.y].SetImage(CPoint(mboxtag, bob.y), ori);
		data[mboxtag + move.x][bob.y + move.y].SetImage(CPoint(mboxtag + move.x, bob.y + move.y), ori);
	}
	else {
		temp = data[bob.x + 3 * move.x][bob.y];
		data[bob.x + 3 * move.x][bob.y] = data[bob.x + 2 * move.x][bob.y];
		data[bob.x + 2 * move.x][bob.y] = temp;

		temp = data[bob.x + 2 * move.x][bob.y];
		data[bob.x + 2 * move.x][bob.y] = data[bob.x + move.x][bob.y];
		data[bob.x + move.x][bob.y] = temp;

		temp = data[bob.x + move.x][bob.y];
		data[bob.x + move.x][bob.y] = data[bob.x][bob.y];
		data[bob.x][bob.y] = temp;

		bob.x += move.x;
		bob.y += move.y;
		data[bob.x][bob.y].SetImage(CPoint(bob.x, bob.y), ori);
		data[bob.x + move.x][bob.y].SetImage(CPoint(bob.x + move.x, bob.y), ori);
		data[bob.x - move.x][bob.y].SetImage(CPoint(bob.x - move.x, bob.y), ori);
		data[bob.x + 2 * move.x][bob.y].SetImage(CPoint(bob.x + 2 * move.x, bob.y), ori);
	}
	
}

int Map::boxtag(CPoint target, ObjectType boxtype) {
	int boxtag = target.x;
	switch (boxtype)
	{
	case Mbox:
		if (data[target.x - 1][target.y].ReturnObjectType() == Mbox)
			boxtag = target.x - 1; // character on box right
		else
			boxtag = target.x; // character on box left
	default:
		break;
	}
	
	
	return boxtag;
}



void Map::MoveObject(int level, int move) {
	ori = ReturnOri(level);
	switch (move) {
	case 0: // up
		if (bob.y - 1 >= 0 && data[bob.x][bob.y - 1].ReturnObjectType() != ImpassibleBlock) {
			// no box
			if (data[bob.x][bob.y - 1].ReturnObjectType() == PassibleBlock)
				movenobox(level, move);

			// has Sbox
			else if (data[bob.x][bob.y - 1].ReturnObjectType() == Sbox) {
				if (bob.y - 2 < 0 || data[bob.x][bob.y - 2].ReturnObjectType() == ImpassibleBlock) {
					break;
				}
				else {
					moveSbox(level, move);
				}
			}

			// has Mbox
			else if (data[bob.x][bob.y - 1].ReturnObjectType() == Mbox) {
				int mboxtag = boxtag(CPoint(bob.x, bob.y - 1), Mbox);
				if (bob.y - 2 < 0 || data[bob.x][bob.y - 2].ReturnObjectType() == ImpassibleBlock || data[mboxtag][bob.y - 2].ReturnObjectType() == ImpassibleBlock) {
					break;
				}
				else {
					moveMbox(level, move, mboxtag);
				}
			}
		}
		break;
	case 1: // down
		if (bob.y + 1 < height &&  data[bob.x][bob.y + 1].ReturnObjectType() != ImpassibleBlock) {
			// no box
			if (data[bob.x][bob.y + 1].ReturnObjectType() == PassibleBlock) {
				movenobox(level, move);
			}

			// has box
			else if (data[bob.x][bob.y + 1].ReturnObjectType() == Sbox) {
				if (bob.y + 2 >= height || data[bob.x][bob.y + 2].ReturnObjectType() == ImpassibleBlock) {
					break;
				}
				else {
					moveSbox(level, move);
				}
			}
			else if (data[bob.x][bob.y + 1].ReturnObjectType() == Mbox) {
				int mboxtag = boxtag(CPoint(bob.x, bob.y + 1), Mbox);
				if (bob.y + 2 >= height || data[bob.x][bob.y + 2].ReturnObjectType() == ImpassibleBlock || data[mboxtag][bob.y + 2].ReturnObjectType() == ImpassibleBlock) {
					break;
				}
				else {
					moveMbox(level, move, mboxtag);
				}
			}
		}
		break;

	case 2: // left
		if (bob.x - 1 >= 0 && data[bob.x - 1][bob.y].ReturnObjectType() != ImpassibleBlock) {
			// no box
			if (data[bob.x - 1][bob.y].ReturnObjectType() == PassibleBlock) {
				movenobox(level, move);
			}

			// has Sbox
			else if (data[bob.x - 1][bob.y].ReturnObjectType() == Sbox) {
				if (bob.x - 2 < 0 || data[bob.x - 2][bob.y].ReturnObjectType() == ImpassibleBlock) {
					break;
				}
				else {
					moveSbox(level, move);
				}
			}

			// has Mbox
			else if (data[bob.x - 1][bob.y].ReturnObjectType() == Mbox) {
				int mboxtag = 0;
				if (bob.x - 3 < 0 || data[bob.x - 3][bob.y].ReturnObjectType() == ImpassibleBlock ) {
					break;
				}
				else {
					moveMbox(level, move, mboxtag);
				}
			}
		}
		break; 

	case 3: // right
		if (bob.x + 1 <=  width && data[bob.x + 1][bob.y].ReturnObjectType() != ImpassibleBlock) {
			// no box
			if (data[bob.x + 1][bob.y].ReturnObjectType() == PassibleBlock) {
				movenobox(level, move);
			}

			// has box
			else if (data[bob.x + 1][bob.y].ReturnObjectType() == Sbox) {
				if (bob.x + 2 >= width || data[bob.x + 2][bob.y].ReturnObjectType() == ImpassibleBlock) {
					break;
				}
				else {
					moveSbox(level, move);
				}
			}

			// has Mbox
			else if (data[bob.x + 1][bob.y].ReturnObjectType() == Mbox) {
				int mboxtag = 0;
				if (bob.x + 3 >= width || data[bob.x + 3][bob.y].ReturnObjectType() == ImpassibleBlock) {
					break;
				}
				else {
					moveMbox(level, move, mboxtag);
				}
			}
		}

		break;
	default:
		break;
	}
	MapStep.push(GetNowMap());
	BobStep.push(bob);
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

std::vector<std::vector<Object>> Map::GetNowMap() {

	std::vector<std::vector<Object>> now_map;

	now_map.clear();
	now_map.resize(width, std::vector<Object>(height));

	now_map = data;

	return now_map;
}

void Map::Undo() {
	if (MapStep.size() != 1) {
		MapStep.pop();
		data = MapStep.top();
		BobStep.pop();
		bob = BobStep.top();
	}
}