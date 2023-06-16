#include "stdafx.h"
#include "../Library/gameutil.h"
#include "choose_level.h"
#include <string>

ChooseLevel::ChooseLevel() {

}

void ChooseLevel::Init() {
	background.LoadBitmapByString({ "resources/choose_background.bmp" });
	background.SetTopLeft(0, 0);
	button_x = 487;
	button_y = 272;
	state = false;

	for (int i = 0; i < 18; i++) {
		if(i == 0 || i == 17) level_button[i].LoadBitmapByString({ "resources/story_button.bmp" });
		else level_button[i].LoadBitmapByString({ "resources/level_button.bmp" });

		if (i >= 0 && i <= 5) {
			level_button[i].SetTopLeft(button_x + i * 100, button_y);
		}
		else if (i >= 6 && i <= 11) {
			level_button[i].SetTopLeft(button_x + (i % 6) * 100, button_y + 100);
		}
		else if (i >= 12 && i <= 17) {
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

void ChooseLevel::LevelText(CDC *pDC) {

	for (int i = 0; i < 18; i++) {
		if (i >= 1 && i <= 5) {
			CTextDraw::ChangeFontLog(pDC, 20, "Press Start 2P", RGB(0, 0, 0));
			text_art.TextBorder(pDC, button_x + 21 + (i % 6) * 100, button_y + 21, 3, std::to_string(i));
			CTextDraw::ChangeFontLog(pDC, 20, "Press Start 2P", RGB(255, 255, 255));
			CTextDraw::Print(pDC, button_x + 21 + (i % 6) * 100, button_y + 21, std::to_string(i));
		}
		else if (i >= 6 && i <= 9) {
			CTextDraw::ChangeFontLog(pDC, 20, "Press Start 2P", RGB(0, 0, 0));
			text_art.TextBorder(pDC, button_x + 21 + (i % 6) * 100, button_y + 21 + 100, 3, std::to_string(i));
			CTextDraw::ChangeFontLog(pDC, 20, "Press Start 2P", RGB(255, 255, 255));
			CTextDraw::Print(pDC, button_x + 21 + (i % 6) * 100, button_y + 21 + 100, std::to_string(i));
		}
		else if (i >= 10 && i <= 11) {
			CTextDraw::ChangeFontLog(pDC, 20, "Press Start 2P", RGB(0, 0, 0));
			text_art.TextBorder(pDC, button_x + 7 + (i % 6) * 100, button_y + 21 + 100, 3, std::to_string(i));
			CTextDraw::ChangeFontLog(pDC, 20, "Press Start 2P", RGB(255, 255, 255));
			CTextDraw::Print(pDC, button_x + 7 + (i % 6) * 100, button_y + 21 + 100, std::to_string(i));
		}
		else if (i >= 12 && i <= 16) {
			CTextDraw::ChangeFontLog(pDC, 20, "Press Start 2P", RGB(0, 0, 0));
			text_art.TextBorder(pDC, button_x + 7 + (i % 6) * 100, button_y + 21 + 200, 3, std::to_string(i));
			CTextDraw::ChangeFontLog(pDC, 20, "Press Start 2P", RGB(255, 255, 255));
			CTextDraw::Print(pDC, button_x + 7 + (i % 6) * 100, button_y + 21 + 200, std::to_string(i));
		}
	}
}


int ChooseLevel::press_level_button(CPoint point) {
	
	for (int i = 1; i <= 16; i++) {
		if (point.x >= level_button[i].GetLeft() && point.x <= level_button[i].GetLeft() + level_button[i].GetWidth() && point.y >= level_button[i].GetTop() && point.y <= level_button[i].GetTop() + level_button[i].GetHeight()) {
			return i;
		}
	}
	return -1;
}