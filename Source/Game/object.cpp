#include "stdafx.h"
#include "object.h"
#include "map.h"

void Object::ShowObjectImage() {
}

void Object::LoadObjectImage(ObjectType objecttybe) {
	switch (objecttybe) {
		case Character:
			charater.LoadBitmapByString({ "resources/bob1.bmp", "resources/bob2.bmp", "resources/bob3.bmp"}, RGB(0, 0, 255));
			charater.SetTopLeft(1369, 25);
			charater.SetAnimation(165, false);
			break;
		case Sbox:
			sbox.LoadBitmapByString({ "resources/sbox.bmp" }, RGB(0, 0, 255));
			sbox.SetTopLeft(1369, 25);
			break;
		case Mbox:
			mbox.LoadBitmapByString({ "resources/mbox.bmp" }, RGB(0, 0, 255));
			mbox.SetTopLeft(1369, 25);
			break;
		case Lbox:
			lbox.LoadBitmapByString({ "resources/lbox.bmp" }, RGB(0, 0, 255));
			lbox.SetTopLeft(1369, 25);
			break;
		case Hole:
			hole.LoadBitmapByString({ "resources/hole.bmp" }, RGB(0, 0, 255));
			hole.SetTopLeft(1369, 25);
			break;
	}
}

