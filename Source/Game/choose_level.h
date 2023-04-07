#pragma once
#include "text_art.h"
using namespace game_framework;

class ChooseLevel {
public:
	ChooseLevel();
	bool state;
	void Init();
	void Show();
	void LevelText(CDC *pDC);
	int press_level_button(CPoint point);
private:
	CMovingBitmap background;
	CMovingBitmap level_button[18];
	TextArt text_art;
	int button_x;
	int button_y;
};