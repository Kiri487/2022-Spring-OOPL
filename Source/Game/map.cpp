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
	switch (move) {
	case 0: // up
		if (movestep.moviable(data, bob, move, height, width)) {
			if (data[bob.x][bob.y - 1].ReturnObjectType() == PassibleBlock) {
				data = movestep.movenobox(data, level, move, bob);
			}
			else if (data[bob.x][bob.y - 1].ReturnObjectType() == Sbox) {
				data = movestep.moveSbox(data, level, move, bob);
			}
			else if (data[bob.x][bob.y - 1].ReturnObjectType() == Mbox) {
				int mboxtag = boxtag(CPoint(bob.x, bob.y - 1), Mbox);
				data = movestep.moveMbox(data, level, move, mboxtag, bob);
			}
			bob = movestep.bobmove(bob, move);
		}
		
		break;
	case 1: // down
		if (movestep.moviable(data, bob, move, height, width)) {
			if (data[bob.x][bob.y + 1].ReturnObjectType() == PassibleBlock) {
				data = movestep.movenobox(data, level, move, bob);
			}
			else if (data[bob.x][bob.y + 1].ReturnObjectType() == Sbox) {
				data = movestep.moveSbox(data, level, move, bob);
			}
			else if (data[bob.x][bob.y + 1].ReturnObjectType() == Mbox) {
				int mboxtag = boxtag(CPoint(bob.x, bob.y + 1), Mbox);
				data = movestep.moveMbox(data, level, move, mboxtag, bob);
			}
			bob = movestep.bobmove(bob, move);
		}
		
		break;

	case 2: // left
		if (movestep.moviable(data, bob, move, height, width)) {
			if (data[bob.x - 1][bob.y].ReturnObjectType() == PassibleBlock) {
				data = movestep.movenobox(data, level, move, bob);
			}
			else if (data[bob.x - 1][bob.y].ReturnObjectType() == Sbox) {
				data = movestep.moveSbox(data, level, move, bob);
			}
			else if (data[bob.x - 1][bob.y].ReturnObjectType() == Mbox) {
				int mboxtag = boxtag(CPoint(bob.x - 1, bob.y), Mbox);
				data = movestep.moveMbox(data, level, move, mboxtag, bob);
			}
			bob = movestep.bobmove(bob, move);
		}
		
		break; 

	case 3: // right
		if (movestep.moviable(data, bob, move, height, width)) {
			if (data[bob.x + 1][bob.y].ReturnObjectType() == PassibleBlock) {
				data = movestep.movenobox(data, level, move, bob);
			}
			else if (data[bob.x + 1][bob.y].ReturnObjectType() == Sbox) {
				if (data[bob.x + 2][bob.y].ReturnObjectType() == Sbox) {
					if (data[bob.x + 3][bob.y].ReturnObjectType() == Sbox) {
						data = movestep.moveSbox(data, level, move, CPoint(bob.x + 2, bob.y));
					}
					data = movestep.moveSbox(data, level, move, CPoint(bob.x + 1, bob.y));
				}
				data = movestep.moveSbox(data, level, move, bob);
			}
			else if (data[bob.x + 1][bob.y].ReturnObjectType() == Mbox) {
				int mboxtag = boxtag(CPoint(bob.x + 1, bob.y), Mbox);
				data = movestep.moveMbox(data, level, move, mboxtag, bob);
			}
			bob = movestep.bobmove(bob, move);
		}
		
		break;
	default:
		break;
	}
	MapStep.push(GetNowMap());
	BobStep.push(bob);
}


//CPoint Map::ReturnOri(int level) {
//	return CPoint(0, 0);
//}

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

void Map::MapStepClear() {
	while (!MapStep.empty()) {
		MapStep.pop();
		BobStep.pop();
	}
}