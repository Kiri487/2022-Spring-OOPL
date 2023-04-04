#include "stdafx.h"
#include "../Library/gameutil.h"
#include "choose_level.h"

ChooseLevel::ChooseLevel() {

}

void ChooseLevel::Init() {
	background.LoadBitmapByString({ "resources/choose_background.bmp" });
	background.SetTopLeft(0, 0);
	int button_x = 487;
	int button_y = 272;

	for (int i = 0; i < 18; i++) {
		if(i == 0 || i == 17) level_button[i].LoadBitmapByString({ "resources/story_button.bmp" });
		else level_button[i].LoadBitmapByString({ "resources/level_button.bmp" });

		if (i >= 0 && i <= 5) {
			level_button[i].SetTopLeft(button_x + i * 100, button_y);
		}
		if (i >= 6 && i <= 11) {
			level_button[i].SetTopLeft(button_x + (i % 6) * 100, button_y + 100);
		}
		if (i >= 12 && i <= 17) {
			level_button[i].SetTopLeft(button_x + (i % 6) * 100, button_y + 200);
		}
	}
}

void ChooseLevel::Show() {

	background.ShowBitmap();

	for (int i = 0; i < 18; i++) {
		level_button[i].ShowBitmap();
	}
}

void ChooseLevel::press_level_button(CPoint point) {

}