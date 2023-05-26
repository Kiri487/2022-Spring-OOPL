#include "stdafx.h"
#include "dead.h"

Dead::Dead() {

}

bool Dead::IfDead(int level, Map map) {

	int Mbox_count = 0;
	int Lbox_count = 0;

	for (int i = 0; i < map.width; i++) {
		for (int j = 0; j < map.height; j++) {
			if (map.ReturnObjectType(i, j) == Sbox) {
				if (IfBoxoviable(level, map, i, j, Sbox) == true) {
					return false;
				}
			}
			if (map.ReturnObjectType(i, j) == Mbox && Mbox_count == 0) {
				Mbox_count = 1;
				if (IfBoxoviable(level, map, i, j, Mbox) == true) {
					return false;
				}
			}
			if (map.ReturnObjectType(i, j) == Lbox && Lbox_count == 0) {
				Lbox_count = 1;
				if (IfBoxoviable(level, map, i, j, Lbox) == true) {
					return false;
				}
			}

		}
	}
	return true;
}

bool Dead::IfBoxoviable(int level, Map map, int x, int y, ObjectType box) {

	if (box == Sbox) {
		// left
		if (x == 0) {
			// up
			if (y == 0) {
				return false;
			}
			else if (map.ReturnObjectType(x, y - 1) != PassibleBlock && map.ReturnObjectType(x, y - 1) != Character) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if (map.ReturnObjectType(x, y + 1) != PassibleBlock && map.ReturnObjectType(x, y + 1) != Character) {
				return false;
			}

		}
		else if (map.ReturnObjectType(x - 1, y) != PassibleBlock && map.ReturnObjectType(x - 1, y) != Character) {
			// up
			if (y == 0) {
				return false;
			}
			else if (map.ReturnObjectType(x, y - 1) != PassibleBlock && map.ReturnObjectType(x, y - 1) != Character) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if (map.ReturnObjectType(x, y + 1) != PassibleBlock && map.ReturnObjectType(x, y + 1) != Character) {
				return false;
			}
		}

		// right 
		if (x == (map.width - 1)) {
			// up
			if (y == 0) {
				return false;
			}
			else if (map.ReturnObjectType(x, y - 1) != PassibleBlock && map.ReturnObjectType(x, y - 1) != Character) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if (map.ReturnObjectType(x, y + 1) != PassibleBlock && map.ReturnObjectType(x, y + 1) != Character) {
				return false;
			}
		}
		else if (map.ReturnObjectType(x + 1, y) != PassibleBlock && map.ReturnObjectType(x + 1, y) != Character) {
			// up
			if (y == 0) {
				return false;
			}
			else if (map.ReturnObjectType(x, y - 1) != PassibleBlock && map.ReturnObjectType(x, y - 1) != Character) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if (map.ReturnObjectType(x, y + 1) != PassibleBlock && map.ReturnObjectType(x, y + 1) != Character) {
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
			else if ((map.ReturnObjectType(x, y - 1) != PassibleBlock && map.ReturnObjectType(x, y - 1) != Character) && (map.ReturnObjectType(x + 1, y - 1) != PassibleBlock && map.ReturnObjectType(x + 1, y - 1) != Character)) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 1) != PassibleBlock && map.ReturnObjectType(x, y + 1) != Character) && (map.ReturnObjectType(x + 1, y + 1) != PassibleBlock && map.ReturnObjectType(x + 1, y + 1) != Character)) {
				return false;
			}
		}
		else if (map.ReturnObjectType(x - 1, y) != PassibleBlock && map.ReturnObjectType(x - 1, y) != Character) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) != PassibleBlock && map.ReturnObjectType(x, y - 1) != Character) && (map.ReturnObjectType(x + 1, y - 1) != PassibleBlock && map.ReturnObjectType(x + 1, y - 1) != Character)) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 1) != PassibleBlock && map.ReturnObjectType(x, y + 1) != Character) && (map.ReturnObjectType(x + 1, y + 1) != PassibleBlock && map.ReturnObjectType(x + 1, y + 1) != Character)) {
				return false;
			}
		}

		// right 
		if ((x + 1) == (map.width - 1)) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) != PassibleBlock && map.ReturnObjectType(x, y - 1) != Character) && (map.ReturnObjectType(x + 1, y - 1) != PassibleBlock && map.ReturnObjectType(x + 1, y - 1) != Character)) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 1) != PassibleBlock && map.ReturnObjectType(x, y + 1) != Character) && (map.ReturnObjectType(x + 1, y + 1) != PassibleBlock && map.ReturnObjectType(x + 1, y + 1) != Character)) {
				return false;
			}
		}
		else if (map.ReturnObjectType(x + 2, y) != PassibleBlock && map.ReturnObjectType(x + 2, y) != Character) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) != PassibleBlock && map.ReturnObjectType(x, y - 1) != Character) && (map.ReturnObjectType(x + 1, y - 1) != PassibleBlock && map.ReturnObjectType(x + 1, y - 1) != Character)) {
				return false;
			}

			// down
			else if (y == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 1) != PassibleBlock && map.ReturnObjectType(x, y + 1) != Character) && (map.ReturnObjectType(x + 1, y + 1) != PassibleBlock && map.ReturnObjectType(x + 1, y + 1) != Character)) {
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
			else if ((map.ReturnObjectType(x, y - 1) != PassibleBlock && map.ReturnObjectType(x, y - 1) != Character) && (map.ReturnObjectType(x + 1, y - 1) != PassibleBlock && map.ReturnObjectType(x + 1, y - 1) != Character)) {
				return false;
			}

			// down
			else if ((y + 1) == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 2) != PassibleBlock && map.ReturnObjectType(x, y + 2) != Character) && (map.ReturnObjectType(x + 1, y + 2) != PassibleBlock && map.ReturnObjectType(x + 1, y + 2) != Character)) {
				return false;
			}

		}
		else if ((map.ReturnObjectType(x - 1, y) != PassibleBlock && map.ReturnObjectType(x - 1, y) != Character) && (map.ReturnObjectType(x - 1, y + 1) != PassibleBlock && map.ReturnObjectType(x - 1, y + 1) != Character)) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) != PassibleBlock && map.ReturnObjectType(x, y - 1) != Character) && (map.ReturnObjectType(x + 1, y - 1) != PassibleBlock && map.ReturnObjectType(x + 1, y - 1) != Character)) {
				return false;
			}

			// down
			else if ((y + 1) == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 2) != PassibleBlock && map.ReturnObjectType(x, y + 2) != Character) && (map.ReturnObjectType(x + 1, y + 2) != PassibleBlock && map.ReturnObjectType(x + 1, y + 2) != Character)) {
				return false;
			}
		}

		// right 
		if (x == (map.width - 1)) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) != PassibleBlock && map.ReturnObjectType(x, y - 1) != Character) && (map.ReturnObjectType(x + 1, y - 1) != PassibleBlock && map.ReturnObjectType(x + 1, y - 1) != Character)) {
				return false;
			}

			// down
			else if ((y + 1) == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 2) != PassibleBlock && map.ReturnObjectType(x, y + 2) != Character) && (map.ReturnObjectType(x + 1, y + 2) != PassibleBlock && map.ReturnObjectType(x + 1, y + 2) != Character)) {
				return false;
			}
		}
		else if ((map.ReturnObjectType(x + 1, y) != PassibleBlock && map.ReturnObjectType(x + 1, y) != Character) && (map.ReturnObjectType(x + 1, y + 1) != PassibleBlock && map.ReturnObjectType(x + 1, y + 1) != Character)) {
			// up
			if (y == 0) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y - 1) != PassibleBlock && map.ReturnObjectType(x, y - 1) != Character) && (map.ReturnObjectType(x + 1, y - 1) != PassibleBlock && map.ReturnObjectType(x + 1, y - 1) != Character)) {
				return false;
			}

			// down
			else if ((y + 1) == (map.height - 1)) {
				return false;
			}
			else if ((map.ReturnObjectType(x, y + 2) != PassibleBlock && map.ReturnObjectType(x, y + 2) != Character) && (map.ReturnObjectType(x + 1, y + 2) != PassibleBlock && map.ReturnObjectType(x + 1, y + 2) != Character)) {
				return false;
			}
		}
	}

	return true;
}