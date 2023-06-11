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
					if (goal.GetValue(i, j) != 1) {
						return true;
					}
				}
			}
			else if (map.ReturnObjectType(i, j) == Mbox && Mbox_count == 0) {
				Mbox_count = 1;
				if (IfBoxMoviable(level, map, i, j, Mbox) == false) {
					if ((goal.GetValue(i, j) != 1) || (goal.GetValue(i + 1, j) != 1)) {
						return true;
					}
				}
			}
			else if (map.ReturnObjectType(i, j) == Lbox && Lbox_count == 0) {
				Lbox_count = 1;
				if (IfBoxMoviable(level, map, i, j, Lbox) == false) {
					if ((goal.GetValue(i, j) != 1) || (goal.GetValue(i, j + 1) != 1) || (goal.GetValue(i + 1, j) != 1) || (goal.GetValue(i + 1, j + 1) != 1)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Dead::IfBoxMoviable(int level, Map map, int x, int y, ObjectType box) {

	CPoint box_point;

	box_point.x = x;
	box_point.y = y;
	
	bool up, down, left, right;
	
	if (box == Sbox) {
		
		// up
		if (y == 0 || y == (map.height - 1)) {
			up = false;
		}
		else {
			if (map.ReturnObjectType(x, y + 1) == PassibleBlock || map.ReturnObjectType(x, y + 1) == Character) {
				if (map.ReturnObjectType(x, y - 1) == Mbox) {
					up = IfBoxMoviable(level, map, x, y - 1, Mbox);
				}
				else if (map.ReturnObjectType(x, y - 1) == Lbox) {
					up = IfBoxMoviable(level, map, x, y - 1, Lbox);
				}
				else {
					up = move.moviable(map.MapStep.top(), box_point, 0, map.height, map.width);
				}
			}
			else {
				up = false;
			}
		}
		// down
		if (y == 0 || y == (map.height - 1)) {
			down = false;
		}
		else {
			if (map.ReturnObjectType(x, y - 1) == PassibleBlock || map.ReturnObjectType(x, y - 1) == Character) {
				if (map.ReturnObjectType(x, y + 1) == Mbox) {
					down = IfBoxMoviable(level, map, x, y + 1, Mbox);
				}
				else if (map.ReturnObjectType(x, y + 1) == Lbox) {
					down = IfBoxMoviable(level, map, x, y + 1, Lbox);
				}
				else {
					down = move.moviable(map.MapStep.top(), box_point, 1, map.height, map.width);
				}
			}
			else {
				down = false;
			}
		}
		// left
		if (x == 0 || x == (map.width - 1)) {
			left = false;
		}
		else {
			if (map.ReturnObjectType(x + 1, y) == PassibleBlock || map.ReturnObjectType(x + 1, y) == Character) {
				if (map.ReturnObjectType(x - 1, y) == Mbox) {
					left = IfBoxMoviable(level, map, x - 1, y, Mbox);
				}
				else if (map.ReturnObjectType(x - 1, y) == Lbox) {
					left = IfBoxMoviable(level, map, x - 1, y, Lbox);
				}
				else {
					left = move.moviable(map.MapStep.top(), box_point, 2, map.height, map.width);
				}
			}
			else {
				left = false;
			}
		}
		// right
		if (x == 0 || x == (map.width - 1)) {
			right = false;
		}
		else {
			if (map.ReturnObjectType(x - 1, y) == PassibleBlock || map.ReturnObjectType(x - 1, y) == Character) {
				if (map.ReturnObjectType(x + 1, y) == Mbox) {
					right = IfBoxMoviable(level, map, x + 1, y, Mbox);
				}
				else if (map.ReturnObjectType(x + 1, y) == Lbox) {
					right = IfBoxMoviable(level, map, x + 1, y, Lbox);
				}
				else {
					right = move.moviable(map.MapStep.top(), box_point, 3, map.height, map.width);
				}
			}
			else {
				right = false;
			}
		}
	}

	else if (box == Mbox) {
		// up 
		if (y == 0 || y == (map.height - 1)) {
			up = false;
		}
		else {
			if (map.ReturnObjectType(x, y + 1) == PassibleBlock || map.ReturnObjectType(x + 1, y + 1) == PassibleBlock || map.ReturnObjectType(x, y + 1) == Character || map.ReturnObjectType(x + 1, y + 1) == Character) {
				up = (move.moviable(map.MapStep.top(), box_point, 0, map.height, map.width) && move.moviable(map.MapStep.top(), (box_point.x + 1, box_point.y), 0, map.height, map.width));
			}
			else {
				up = false;
			}
		}
		// down
		if (y == 0 || y == (map.height - 1)) {
			down = false;
		}
		else {
			if (map.ReturnObjectType(x, y - 1) == PassibleBlock || map.ReturnObjectType(x + 1, y - 1) == PassibleBlock || map.ReturnObjectType(x, y - 1) == Character || map.ReturnObjectType(x + 1, y - 1) == Character) {
				down = (move.moviable(map.MapStep.top(), box_point, 1, map.height, map.width) && move.moviable(map.MapStep.top(), (box_point.x + 1, box_point.y), 1, map.height, map.width));
			}
			else {
				down = false;
			}
		}
		// left
		if (x == 0 || x == (map.width - 2)) {
			left = false;
		}
		else {
			if (map.ReturnObjectType(x + 2, y) == PassibleBlock || map.ReturnObjectType(x + 2, y) == Character) {
				if (map.ReturnObjectType(x - 1, y) == Lbox) {
					left = IfBoxMoviable(level, map, x - 1, y, Lbox);
				}
				else {
					left = move.moviable(map.MapStep.top(), (box_point.x + 1, box_point.y), 2, map.height, map.width);
				}	
			}
			else {
				left = false;
			}
		}
		// right
		if (x == 0 || x == (map.width - 2)) {
			right = false;
		}
		else {
			if (map.ReturnObjectType(x - 1, y) == PassibleBlock || map.ReturnObjectType(x - 1, y) == Character) {
				if (map.ReturnObjectType(x + 2, y) == Lbox) {
					right = IfBoxMoviable(level, map, x + 2, y, Lbox);
				}
				else {
					right = move.moviable(map.MapStep.top(), box_point, 3, map.height, map.width);
				}
			}
			else {
				right = false;
			}
		}
	}

	else if (box == Lbox) {
		// up
		if (y == 0 || y == (map.height - 2)) {
			up = false;
		}
		else {
			if (map.ReturnObjectType(x, y + 2) == PassibleBlock || map.ReturnObjectType(x + 1, y + 2) == PassibleBlock || map.ReturnObjectType(x, y + 2) == Character || map.ReturnObjectType(x + 1, y + 2) == Character) {
				up = (move.moviable(map.MapStep.top(), (box_point.x, box_point.y + 1), 0, map.height, map.width) && move.moviable(map.MapStep.top(), (box_point.x + 1, box_point.y + 1), 0, map.height, map.width));
			}
			else {
				up = false;
			}
		}
		// down
		if (y == 0 || y == (map.height - 2)) {
			down = false;
		}
		else {
			if (map.ReturnObjectType(x, y - 1) == PassibleBlock || map.ReturnObjectType(x + 1, y - 1) == PassibleBlock || map.ReturnObjectType(x, y - 1) == Character || map.ReturnObjectType(x + 1, y - 1) == Character) {
				down = (move.moviable(map.MapStep.top(), box_point, 1, map.height, map.width) && move.moviable(map.MapStep.top(), (box_point.x + 1, box_point.y), 1, map.height, map.width));
			}
			else {
				down = false;
			}
		}
		// left
		if (x == 0 || x == (map.width - 2)) {
			left = false;
		}
		else {
			if (map.ReturnObjectType(x + 2, y) == PassibleBlock || map.ReturnObjectType(x + 2, y + 1) == PassibleBlock || map.ReturnObjectType(x + 2, y) == Character || map.ReturnObjectType(x + 2, y + 1) == Character) {
				left = (move.moviable(map.MapStep.top(), (box_point.x + 1, box_point.y), 2, map.height, map.width) && move.moviable(map.MapStep.top(), (box_point.x + 1, box_point.y + 1), 2, map.height, map.width));
			}
			else {
				left = false;
			}
		}
		// right
		if (x == 0 || x == (map.width - 2)) {
			right = false;
		}
		else {
			if (map.ReturnObjectType(x - 1, y) == PassibleBlock || map.ReturnObjectType(x - 1, y + 1) == PassibleBlock || map.ReturnObjectType(x - 1, y) == Character || map.ReturnObjectType(x - 1, y + 1) == Character) {
				right = (move.moviable(map.MapStep.top(), box_point, 3, map.height, map.width) && move.moviable(map.MapStep.top(), (box_point.x, box_point.y + 1), 3, map.height, map.width));
			}
			else {
				right = false;
			}
		}
	}

	if (up || down || left || right) {
		return true;
	}
	else {
		return false;
	}
}

/*bool Dead::DirectionMoviable(int level, Map map, int x, int y, ObjectType box, int direction) {
	switch (direction) {
	case 1: // up

	case 2: // down

	case 3: 
	}
	return true;
}*/