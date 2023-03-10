#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

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
	"resources/transition6.bmp",
		}, RGB(0, 0, 255));
	transition.SetTopLeft(0, 0);
	transition.SetAnimation(70, true);
	transition.ToggleAnimation();

	background.LoadBitmapByString({
	"resources/1_background.bmp",
	"resources/2_background.bmp",
	"resources/3_background.bmp",
	"resources/4_background.bmp",
	"resources/5_background.bmp",
		});
	background.SetTopLeft(0, 0);

	map.LoadBitmapByString({
	"resources/1_map.bmp",
	"resources/2_map.bmp",
	"resources/3_map.bmp",
	"resources/4_map.bmp",
	"resources/5_map.bmp"
		}, RGB(0, 0, 255));
	map.SetTopLeft(526, 157);

	music_icon.LoadBitmapByString({ "resources/music_on.bmp", "resources/music_off.bmp" });
	music_icon.SetTopLeft(1369, 25);

	sound_icon.LoadBitmapByString({ "resources/sound_on.bmp", "resources/sound_off.bmp" });
	sound_icon.SetTopLeft(1445, 25);

	exit_icon.LoadBitmapByString({ "resources/exit.bmp" });
	exit_icon.SetTopLeft(25, 25);

	character.LoadBitmapByString({ "resources/bob1.bmp", "resources/bob2.bmp", "resources/bob3.bmp" }, RGB(0, 0, 255));
	character.SetAnimation(165, false);
	character.SetTopLeft(711, 215);
	

	sbox1.LoadBitmapByString({ "resources/box_s.bmp", "resources/box_s_in_hole.bmp" });
	sbox2.LoadBitmapByString({ "resources/box_s.bmp", "resources/box_s_in_hole.bmp" });
	sbox3.LoadBitmapByString({ "resources/box_s.bmp", "resources/box_s_in_hole.bmp" });
	sbox1.SetTopLeft(953, 251);

	mbox.LoadBitmapByString({ "resources/box_m.bmp" });

	baffle.LoadBitmapByString({ "resources/baffle_desert.bmp" });

	goal1.LoadBitmapByString({ "resources/goal.bmp" }, RGB(0, 0, 255));
	goal2.LoadBitmapByString({ "resources/goal.bmp" }, RGB(0, 0, 255));
	goal3.LoadBitmapByString({ "resources/goal.bmp" }, RGB(0, 0, 255));
	goal1.SetTopLeft(953, 583);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// enter
	if (nChar == VK_RETURN) {
		// !!! change level test !!! 
		level++; 
		if (level == 2) {
			map.SetTopLeft(445, 174);
			goal1.SetTopLeft(705, 184);
			goal2.SetTopLeft(954, 184);
			goal3.SetTopLeft(954, 350);
			sbox1.SetTopLeft(622, 267);
			sbox2.SetTopLeft(705, 267);
			sbox3.SetTopLeft(788, 267);
			character.SetTopLeft(463, 231);
			transition.ToggleAnimation();
		}
		// !!! change level test !!! 
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
		}
		else {
			music_icon.SetFrameIndexOfBitmap(0);
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
	if (point.x >= exit_icon.GetLeft() && point.x <= exit_icon.GetLeft() + exit_icon.GetWidth() && point.y >= exit_icon.GetTop() && point.y <= exit_icon.GetTop() + exit_icon.GetHeight()) {
		// to do
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
	show_image_by_level();
	show_text_by_level();
	show_transition();
}

void CGameStateRun::show_image_by_level() {
	
	if (level <= 16) {
		background.SetFrameIndexOfBitmap(level - 1);
		background.ShowBitmap();
		map.SetFrameIndexOfBitmap(level - 1);
		map.ShowBitmap();
		character.ShowBitmap();
		music_icon.ShowBitmap();
		sound_icon.ShowBitmap();
		exit_icon.ShowBitmap();
		
		if (level == 1) {
			goal1.ShowBitmap();
			sbox1.ShowBitmap();
		}

		if (level == 2) {
			goal1.ShowBitmap();
			goal2.ShowBitmap();
			goal3.ShowBitmap();
			sbox1.ShowBitmap();
			sbox2.ShowBitmap();
			sbox3.ShowBitmap();
		}
	}
}

void CGameStateRun::show_text_by_level() {

	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(255, 255, 255));

	if (level == 1) {
		CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(0, 0, 0));
		text_border(pDC, 15, 695, 4, "Level 1");
		CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(255, 255, 255));
		CTextDraw::Print(pDC, 15, 695, "Level 1");
	}
	else if (level == 2) {
		CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(0, 0, 0));
		text_border(pDC, 15, 695, 4, "Level 2");
		CTextDraw::ChangeFontLog(pDC, 15, "Press Start 2P", RGB(255, 255, 255));
		CTextDraw::Print(pDC, 15, 695, "Level 2");
	}

	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::show_transition() {
	if (level <= 16) {
		transition.ShowBitmap();
	}
}

void CGameStateRun::text_border(CDC *pDC, int x, int y, int size, string s) {
	for (int i = 0; i < size; i++) {
		CTextDraw::Print(pDC, x, y + i, s);
		CTextDraw::Print(pDC, x, y - i, s);
		CTextDraw::Print(pDC, x + i, y, s);
		CTextDraw::Print(pDC, x - i, y, s);
		CTextDraw::Print(pDC, x + i, y + i, s);
		CTextDraw::Print(pDC, x + i, y - i, s);
		CTextDraw::Print(pDC, x - i, y + i, s);
		CTextDraw::Print(pDC, x - i, y - i, s);
	}
}