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
	"resources/2_map.bmp"
		}, RGB(0, 0, 255));

	music.LoadBitmapByString({ "resources/music_on.bmp", "resources/music_off.bmp" });
	music.SetTopLeft(1369, 25);

	sound.LoadBitmapByString({ "resources/sound_on.bmp", "resources/sound_off.bmp" });
	sound.SetTopLeft(1445, 25);

	exit.LoadBitmapByString({ "resources/exit.bmp" });
	exit.SetTopLeft(25, 25);

	character.LoadBitmapByString({ "resources/bob1.bmp" }, RGB(0, 0, 255));

	box1.LoadBitmapByString({ "resources/1_box.bmp" });
	box1.SetTopLeft(802, 228);

	goal1.LoadBitmapByString({ "resources/1_goal.bmp" }, RGB(0, 0, 255));
	goal1.SetTopLeft(802, 471);

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	level++;
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
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
}

void CGameStateRun::show_image_by_level() {
	
	if (level <= 6) {
		background.SetFrameIndexOfBitmap(level - 1);
		background.ShowBitmap();
		map.SetFrameIndexOfBitmap(level - 1);
		map.ShowBitmap();
		character.ShowBitmap();
		music.ShowBitmap();
		sound.ShowBitmap();
		exit.ShowBitmap();
		
		if (level == 1) {
			map.SetTopLeft(487, 136);
			character.SetTopLeft(625, 207);
			box1.ShowBitmap();
			goal1.ShowBitmap();
		}

		if (level == 2) {
			map.SetTopLeft(501, 233);
			character.SetTopLeft(522, 330);
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