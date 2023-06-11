#include "stdafx.h"
#include "dead.h"

Dead::Dead() {

}

bool Dead::IfDead(int level, Map map, ClearLevel goal) {

	int Sbox_count = 0;
	int Mbox_count = 0;
	int Lbox_count = 0;

	if (level == 2) {
		for (int i = 0; i < map.width; i++) {
			for (int j = 0; j < map.height; j++) {
				if (map.ReturnObjectType(i, j) == Sbox && i < 2) {
					return true;
				}
			}
		}
	}
	else if (level == 4) {
		if (map.ReturnObjectType(1, 1) == Mbox) {
			return true;
		}
	}
	else if (level == 6 || level == 11) {
		for (int i = 0; i < map.width; i++) {
			for (int j = 0; j < map.height; j++) {
				if (map.ReturnObjectType(i, j) == Sbox) {
					Sbox_count = 1;
				}
			}
		}

		if (Sbox_count == 0) {
			return true;
		}
	}

	for (int i = 0; i < map.width; i++) {
		for (int j = 0; j < map.height; j++) {
			if (map.ReturnObjectType(i, j) == Sbox) {
				if (IfBoxMoviable(level, map, i, j, Sbox) == false) {
					if (goal.GetValue(i, j) == 1) {
						map.data[i][j].SetObject(ImpassibleBlock);
					}
				}
			}
			else if (map.ReturnObjectType(i, j) == Mbox && Mbox_count == 0) {
				Mbox_count = 1;
				if (IfBoxMoviable(level, map, i, j, Mbox) == false) {
					if ((goal.GetValue(i, j) == 1) && (goal.GetValue(i + 1, j) == 1)) {
						map.data[i][j].SetObject(ImpassibleBlock);
						map.data[i + 1][j].SetObject(ImpassibleBlock);
					}
				}
			}
			else if (map.ReturnObjectType(i, j) == Lbox && Lbox_count == 0) {
				Lbox_count = 1;
				if (IfBoxMoviable(level, map, i, j, Lbox) == false) {
					if ((goal.GetValue(i, j) == 1) && (goal.GetValue(i, j + 1) == 1) && (goal.GetValue(i + 1, j) == 1) && (goal.GetValue(i + 1, j + 1) == 1)) {
						map.data[i][j].SetObject(ImpassibleBlock);
						map.data[i][j + 1].SetObject(ImpassibleBlock);
						map.data[i + 1][j].SetObject(ImpassibleBlock);
						map.data[i + 1][j + 1].SetObject(ImpassibleBlock);
					}
				}
			}
		}
	}

	Mbox_count = 0;
	Lbox_count = 0;

	for (int i = 0; i < map.width; i++) {
		for (int j = 0; j < map.height; j++) {
			if (map.ReturnObjectType(i, j) == Sbox) {
				if (IfBoxMoviable(level, map, i, j, Sbox) == false) {
					return true;
				}
			}
			else if (map.ReturnObjectType(i, j) == Mbox && Mbox_count == 0) {
				Mbox_count = 1;
				if (IfBoxMoviable(level, map, i, j, Mbox) == false) {
					return true;
				}
			}
			else if (map.ReturnObjectType(i, j) == Lbox && Lbox_count == 0) {
				Lbox_count = 1;
				if (IfBoxMoviable(level, map, i, j, Lbox) == false) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Dead::IfBoxMoviable(int level, Map map, int x, int y, ObjectType box) {

	if (box == Sbox) {
		// left
		if (x == 0) {
			// up
			if (y == 0) {
				return false;
			}
			else if (map.ReturnObjectType(x, y - 1) == ImpassibleBlock || map.ReturnObjectType(x, y - 1) == Hole) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if (map.ReturnObjectType(x, y + 1) == ImpassibleBlock || map.ReturnObjectType(x, y + 1) == Hole) {
				return false;
			}

		}
		else if (map.ReturnObjectType(x - 1, y) == ImpassibleBlock || map.ReturnObjectType(x - 1, y) == Hole) {
			// up
			if (y == 0) {
				return false;
			}
			else if (map.ReturnObjectType(x, y - 1) == ImpassibleBlock || map.ReturnObjectType(x, y - 1) == Hole) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if (map.ReturnObjectType(x, y + 1) == ImpassibleBlock || map.ReturnObjectType(x, y + 1) == Hole) {
				return false;
			}
		}

		// right 
		if (x == (map.width - 1)) {
			// up
			if (y == 0) {
				return false;
			}
			else if (map.ReturnObjectType(x, y - 1) == ImpassibleBlock || map.ReturnObjectType(x, y - 1) == Hole) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if (map.ReturnObjectType(x, y + 1) == ImpassibleBlock || map.ReturnObjectType(x, y + 1) == Hole) {
				return false;
			}
		}
		else if (map.ReturnObjectType(x + 1, y) == ImpassibleBlock || map.ReturnObjectType(x + 1, y) == Hole) {
			// up
			if (y == 0) {
				return false;
			}
			else if (map.ReturnObjectType(x, y - 1) == ImpassibleBlock || map.ReturnObjectType(x, y - 1) == Hole) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if (map.ReturnObjectType(x, y + 1) == ImpassibleBlock || map.ReturnObjectType(x, y + 1) == Hole) {
				return false;
			}
		}
	}
	else if (box == Mbox) {
		// left
		if (x == 0) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) == ImpassibleBlock || map.ReturnObjectType(x, y - 1) == Hole) && (map.ReturnObjectType(x + 1, y - 1) == ImpassibleBlock || map.ReturnObjectType(x + 1, y - 1) == Hole)) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 1) == ImpassibleBlock || map.ReturnObjectType(x, y + 1) == Hole) && (map.ReturnObjectType(x + 1, y + 1) == ImpassibleBlock || map.ReturnObjectType(x + 1, y + 1) == Hole)) {
				return false;
			}
		}
		else if (map.ReturnObjectType(x - 1, y) == ImpassibleBlock || map.ReturnObjectType(x - 1, y) == Hole) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) == ImpassibleBlock || map.ReturnObjectType(x, y - 1) == Hole) && (map.ReturnObjectType(x + 1, y - 1) == ImpassibleBlock || map.ReturnObjectType(x + 1, y - 1) == Hole)) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 1) == ImpassibleBlock || map.ReturnObjectType(x, y + 1) == Hole) && (map.ReturnObjectType(x + 1, y + 1) == ImpassibleBlock || map.ReturnObjectType(x + 1, y + 1) == Hole)) {
				return false;
			}
		}

		// right 
		if ((x + 1) == (map.width - 1)) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) == ImpassibleBlock || map.ReturnObjectType(x, y - 1) == Hole) && (map.ReturnObjectType(x + 1, y - 1) == ImpassibleBlock || map.ReturnObjectType(x + 1, y - 1) == Hole)) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 1) == ImpassibleBlock || map.ReturnObjectType(x, y + 1) == Hole) && (map.ReturnObjectType(x + 1, y + 1) == ImpassibleBlock || map.ReturnObjectType(x + 1, y + 1) == Hole)) {
				return false;
			}
		}
		else if (map.ReturnObjectType(x + 2, y) == ImpassibleBlock || map.ReturnObjectType(x + 2, y) == Hole) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) == ImpassibleBlock || map.ReturnObjectType(x, y - 1) == Hole) && (map.ReturnObjectType(x + 1, y - 1) == ImpassibleBlock || map.ReturnObjectType(x + 1, y - 1) == Hole)) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 1) == ImpassibleBlock || map.ReturnObjectType(x, y + 1) == Hole) && (map.ReturnObjectType(x + 1, y + 1) == ImpassibleBlock || map.ReturnObjectType(x + 1, y + 1) == Hole)) {
				return false;
			}
		}
	}
	else if (box == Lbox) {
		// left
		if (x == 0) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) == ImpassibleBlock || map.ReturnObjectType(x, y - 1) == Hole) && (map.ReturnObjectType(x + 1, y - 1) == ImpassibleBlock || map.ReturnObjectType(x + 1, y - 1) == Hole)) {
				return false;
			}

			// down
			else if ((y + 1) == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 2) == ImpassibleBlock || map.ReturnObjectType(x, y + 2) == Hole) && (map.ReturnObjectType(x + 1, y + 2) == ImpassibleBlock || map.ReturnObjectType(x + 1, y + 2) == Hole)) {
				return false;
			}

		}
		else if ((map.ReturnObjectType(x - 1, y) == ImpassibleBlock || map.ReturnObjectType(x - 1, y) == Hole) && (map.ReturnObjectType(x - 1, y + 1) == ImpassibleBlock || map.ReturnObjectType(x - 1, y + 1) == Hole)) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) == ImpassibleBlock || map.ReturnObjectType(x, y - 1) == Hole) && (map.ReturnObjectType(x + 1, y - 1) == ImpassibleBlock || map.ReturnObjectType(x + 1, y - 1) == Hole)) {
				return false;
			}

			// down
			else if ((y + 1) == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 2) == ImpassibleBlock || map.ReturnObjectType(x, y + 2) == Hole) && (map.ReturnObjectType(x + 1, y + 2) == ImpassibleBlock || map.ReturnObjectType(x + 1, y + 2) == Hole)) {
				return false;
			}
		}

		// right 
		if ((x + 1) == (map.width - 1)) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) == ImpassibleBlock || map.ReturnObjectType(x, y - 1) == Hole) && (map.ReturnObjectType(x + 1, y - 1) == ImpassibleBlock || map.ReturnObjectType(x + 1, y - 1) == Hole)) {
				return false;
			}

			// down
			else if ((y + 1) == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 2) == ImpassibleBlock || map.ReturnObjectType(x, y + 2) == Hole) && (map.ReturnObjectType(x + 1, y + 2) == ImpassibleBlock || map.ReturnObjectType(x + 1, y + 2) == Hole)) {
				return false;
			}
		}
		else if ((map.ReturnObjectType(x + 2, y) == ImpassibleBlock || map.ReturnObjectType(x + 2, y) == Hole) && (map.ReturnObjectType(x + 2, y + 1) == ImpassibleBlock || map.ReturnObjectType(x + 2, y + 1) == Hole)) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) == ImpassibleBlock || map.ReturnObjectType(x, y - 1) == Hole) && (map.ReturnObjectType(x + 1, y - 1) == ImpassibleBlock || map.ReturnObjectType(x + 1, y - 1) == Hole)) {
				return false;
			}

			// down
			else if ((y + 1) == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 2) == ImpassibleBlock || map.ReturnObjectType(x, y + 2) == Hole) && (map.ReturnObjectType(x + 1, y + 2) == ImpassibleBlock || map.ReturnObjectType(x + 1, y + 2) == Hole)) {
				return false;
			}
		}
	}

	return true;
}