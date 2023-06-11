#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>
#include <ctime>

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
	map.Matrix(level);
	start_time = time(NULL);
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	transition.LoadBitmapByString({
	"resources/transition1.bmp",
	"resources/transition2.bmp",
	"resources/transition3.bmp",
	"resources/transition4.bmp",
	"resources/transition5.bmp",
	"resources/transition6.bmp"
		}, RGB(0, 0, 255));
	transition.SetTopLeft(0, 0);
	transition.SetAnimation(70, true);
	transition.ToggleAnimation();

	clear_pic.LoadBitmapByString({
	"resources/clear1.bmp",
	"resources/clear2.bmp",
	"resources/clear3.bmp",
	"resources/clear4.bmp",
	"resources/clear5.bmp",
	"resources/clear6.bmp",
	"resources/clear7.bmp"
		}, RGB(0, 0, 255));
	clear_pic.SetTopLeft(0, 0);
	clear_pic.SetAnimation(55, true);
	clear_pic.ToggleAnimation();

	dead_pic.LoadBitmapByString({
	"resources/dead1.bmp",
	"resources/dead2.bmp",
	"resources/dead3.bmp",
	"resources/dead4.bmp",
	"resources/dead5.bmp",
	"resources/dead6.bmp",
	"resources/dead7.bmp"
		}, RGB(0, 0, 255));
	dead_pic.SetTopLeft(0, 0);
	dead_pic.SetAnimation(55, true);
	dead_pic.ToggleAnimation();

	background.LoadBitmapByString({
	"resources/1_background.bmp",
	"resources/2_background.bmp",
	"resources/3_background.bmp",
	"resources/4_background.bmp",
	"resources/5_background.bmp",
	"resources/6_background.bmp",
	"resources/7_background.bmp",
	"resources/8_background.bmp",
	"resources/9_background.bmp",
	"resources/10_background.bmp",
	"resources/11_background.bmp",
	"resources/12_background.bmp",
	"resources/13_background.bmp",
	"resources/14_background.bmp",
	"resources/15_background.bmp",
	"resources/16_background.bmp"
		});
	background.SetTopLeft(0, 0);

	music_icon.LoadBitmapByString({ "resources/music_on.bmp", "resources/music_off.bmp" });
	music_icon.SetTopLeft(1369, 25);

	sound_icon.LoadBitmapByString({ "resources/sound_on.bmp", "resources/sound_off.bmp" });
	sound_icon.SetTopLeft(1445, 25);

	exit_icon.LoadBitmapByString({ "resources/exit.bmp" });
	exit_icon.SetTopLeft(25, 25);

	CAudio::Instance() -> Load(AUDIO_BGM, "resources/bgm.wav");
	CAudio::Instance() -> Play(AUDIO_BGM, true);

	CAudio::Instance() -> Load(AUDIO_WALK, "resources/walking.wav");
	CAudio::Instance() -> Load(AUDIO_TRANS, "resources/trans.wav");

	choose_level.Init();
	clear_level.GoalLocation(level);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// enter

	if (nChar == VK_RETURN) {

		if (clear) {
			level++;
			if (level <= 16) {
				if (sound_icon.GetFrameIndexOfBitmap() == 0) {
					CAudio::Instance() -> Play(AUDIO_TRANS);
				}
				clear_level.GoalLocation(level);
				map.MapStepClear();
				map.Matrix(level);
				clear = false;
				death = false;
				transition.ToggleAnimation();
				start_time = time(NULL);
			}
		}
	}
	else if (nChar == VK_UP || nChar == 'W') {
		if (clear == false /*&& death == false*/) {
			map.MoveObject(level, 0);
			clear = clear_level.IfClear(level, map);
			death = dead.IfDead(level, map, clear_level);
			if (sound_icon.GetFrameIndexOfBitmap() == 0) {
				CAudio::Instance() -> Play(AUDIO_WALK);
			}
			if (clear_level.IfClear(level, map)) {
				clear_pic.ToggleAnimation();
			}
			else if (death) {
				dead_pic.ToggleAnimation();
			}
		}
	}
	else if (nChar == VK_DOWN || nChar == 'S') {
		if (clear == false /*&& death == false*/) {
			map.MoveObject(level, 1);
			clear = clear_level.IfClear(level, map);
			death = dead.IfDead(level, map, clear_level);
			if (sound_icon.GetFrameIndexOfBitmap() == 0) {
				CAudio::Instance() -> Play(AUDIO_WALK);
			}
			if (clear_level.IfClear(level, map)) {
				clear_pic.ToggleAnimation();
			}
			else if (death) {
				dead_pic.ToggleAnimation();
			}
		}
	}
	else if (nChar == VK_LEFT || nChar == 'A') {
		if (clear == false /*&& death == false*/) {
			map.MoveObject(level, 2);
			clear = clear_level.IfClear(level, map);
			death = dead.IfDead(level, map, clear_level);
			if (sound_icon.GetFrameIndexOfBitmap() == 0) {
				CAudio::Instance() -> Play(AUDIO_WALK);
			}
			if (clear_level.IfClear(level, map)) {
				clear_pic.ToggleAnimation();
			}
			else if (death) {
				dead_pic.ToggleAnimation();
			}
		}
	}
	else if (nChar == VK_RIGHT || nChar == 'D') {
		if (clear == false /*&& death == false*/) {
			map.MoveObject(level, 3);
			clear = clear_level.IfClear(level, map);
			death = dead.IfDead(level, map, clear_level);
			if (sound_icon.GetFrameIndexOfBitmap() == 0) {
				CAudio::Instance() -> Play(AUDIO_WALK);
			}
			if (clear_level.IfClear(level, map)) {
				clear_pic.ToggleAnimation();
			}
			else if (death) {
				dead_pic.ToggleAnimation();
			}
		}
	}
	else if (nChar == 'R') {
		if (clear == false) {
			map.MapStepClear();
			map.Matrix(level);
			clear = false;
			death = false;
			start_time = time(NULL);
		}
	}
	else if (nChar == 'U') {
		if (clear == false && timer()[0] < '6') {
			map.Undo();
			clear = clear_level.IfClear(level, map);
			death = dead.IfDead(level, map, clear_level);
		}
	}
	else if (nChar == VK_TAB && level < 16) {
		level ++;
		if (sound_icon.GetFrameIndexOfBitmap() == 0) {
			CAudio::Instance() -> Play(AUDIO_TRANS);
		}
		clear_level.GoalLocation(level);
		map.MapStepClear();
		map.Matrix(level);
		clear = false;
		death = false;
		transition.ToggleAnimation();
		start_time = time(NULL);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	// music_on_off
	if (point.x >= music_icon.GetLeft() && point.x <= music_icon.GetLeft() + music_icon.GetWidth() && point.y >= music_icon.GetTop() && point.y <= music_icon.GetTop() + music_icon.GetHeight()) {
		if (music_icon.GetFrameIndexOfBitmap() == 0) {
			music_icon.SetFrameIndexOfBitmap(1);
			CAudio::Instance() -> Stop(AUDIO_BGM);
		}
		else {
			music_icon.SetFrameIndexOfBitmap(0);
			CAudio::Instance() -> Play(AUDIO_BGM, true);
		}	
	}

	//sound_on_off
	if (point.x >= sound_icon.GetLeft() && point.x <= sound_icon.GetLeft() + sound_icon.GetWidth() && point.y >= sound_icon.GetTop() && point.y <= sound_icon.GetTop() + sound_icon.GetHeight()) {
		if (sound_icon.GetFrameIndexOfBitmap() == 0) {
			sound_icon.SetFrameIndexOfBitmap(1);
		}
		else {
			sound_icon.SetFrameIndexOfBitmap(0);
		}
	}

	//exit
	if (choose_level.state == false) {
		if (point.x >= exit_icon.GetLeft() && point.x <= exit_icon.GetLeft() + exit_icon.GetWidth() && point.y >= exit_icon.GetTop() && point.y <= exit_icon.GetTop() + exit_icon.GetHeight()) {
			choose_level.state = true;
			transition.ToggleAnimation();
			if (sound_icon.GetFrameIndexOfBitmap() == 0) {
				CAudio::Instance() -> Play(AUDIO_TRANS);
			}
		}
	}

	// choose level
	if (choose_level.state == true) {
		if (choose_level.press_level_button(point) >= 0 && choose_level.press_level_button(point) <= 17) {
			level = choose_level.press_level_button(point);
			clear_level.GoalLocation(level);
			map.MapStepClear();
			map.Matrix(level);
			clear = false;
			death = false;
			transition.ToggleAnimation();
			start_time = time(NULL);
			choose_level.state = false;
			if (sound_icon.GetFrameIndexOfBitmap() == 0) {
				CAudio::Instance() -> Play(AUDIO_TRANS);
			}
		}
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	if (choose_level.state == true) {

		choose_level.Show();
		music_icon.ShowBitmap();
		sound_icon.ShowBitmap();
		CDC *pDC = CDDraw::GetBackCDC();
		choose_level.LevelText(pDC);
		CDDraw::ReleaseBackCDC();
		show_transition();
	}

	else if (choose_level.state == false) {

		show_image_by_level();
		show_text_by_level();
		map.Show();
		show_transition();

		if (clear) {
			clear_pic.ShowBitmap();
		}
		/*else if (death) {
			dead_pic.ShowBitmap();
		}*/
	}
}

void CGameStateRun::show_image_by_level() {
	
	if (level <= 16) {
		background.SetFrameIndexOfBitmap(level - 1);
		background.ShowBitmap();
		music_icon.ShowBitmap();
		sound_icon.ShowBitmap();
		exit_icon.ShowBitmap();
	}
}

void CGameStateRun::show_text_by_level() {

	CDC *pDC = CDDraw::GetBackCDC();

	//CTextDraw::Print(pDC, 100, 100, std::to_string(test.width) + " " + std::to_string(test.height));
	
	if (level >= 1 && level <= 16) {
		CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(0, 0, 0));
		text_art.TextBorder(pDC, 15, 695, 4, "LEVEL " + std::to_string(level));
		CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(255, 255, 255));
		CTextDraw::Print(pDC, 15, 695, "LEVEL " + std::to_string(level));

		CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(0, 0, 0));
		text_art.TextBorder(pDC, 1280, 660, 4, "STEP: " + std::to_string(step_counter(map.MapStep)));
		CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(255, 255, 255));
		CTextDraw::Print(pDC, 1280, 660, "STEP: " + std::to_string(step_counter(map.MapStep)));

		CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(0, 0, 0));
		text_art.TextBorder(pDC, 1280, 695, 4, "TIME: " + timer());
		CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(255, 255, 255));
		CTextDraw::Print(pDC, 1280, 695, "TIME: " + timer());

		//CTextDraw::Print(pDC, 100, 100, std::to_string(map.width) + " " + std::to_string(map.height));

		CPoint ori = moveori.ReturnOri(level);
		for (int i = 0; i < map.width; i++) {
			for (int j = 0; j < map.height; j++) {
				CTextDraw::Print(pDC, ori.x + 83 * i, ori.y + 83 * j, std::to_string(i) + ", " + std::to_string(j));
				CTextDraw::Print(pDC, ori.x + 83 * i, ori.y + 83 * j + 20, map.PrintObjectType(i, j));
			}
		}

		for (int i = 0; i < clear_level.width; i++) {
			for (int j = 0; j < clear_level.height; j++) {
				CTextDraw::Print(pDC, ori.x + 83 * i, ori.y + 83 * j + 40, std::to_string(clear_level.GetValue(i, j)));
			}
		}
		

		CTextDraw::Print(pDC, 15, 100, "Clear? = " + std::to_string(clear));
		CTextDraw::Print(pDC, 15, 130, "Dead? = " + std::to_string(death)); 

		//CTextDraw::Print(pDC, 200, 100, imagedatashow[Character]);
		
	}

	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::show_transition() {
	if (level <= 16) {
		transition.ShowBitmap();
	}
}

string CGameStateRun::timer() {
	double pass_time;
	int m, s;
	string m_text = "0", s_text = "0";

	if (clear == false && death == false) {
		end_time = time(NULL);
	}
	pass_time = difftime(end_time, start_time);
	m = (int) pass_time / 60;
	s = (int) pass_time % 60;
	fflush(stdout);

	(m >= 0 && m < 10) ? (m_text = "0" + std::to_string(m)) : (m_text = std::to_string(m));
	(s >= 0 && s < 10) ? (s_text = "0" + std::to_string(s)) : (s_text = std::to_string(s));

	if (m >= 60) {
		death = true;
	}

	return(m_text + ":" + s_text);
}

int CGameStateRun::step_counter(std::stack<std::vector<std::vector<Object>>> MapStep) {
	return (MapStep.size() - 1);
}