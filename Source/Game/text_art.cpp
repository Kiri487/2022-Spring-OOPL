#include "stdafx.h"
#include "../Library/gameutil.h"
#include "text_art.h"

TextArt::TextArt() {

}

void TextArt::TextBorder(CDC *pDC, int x, int y, int size, string s) {
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