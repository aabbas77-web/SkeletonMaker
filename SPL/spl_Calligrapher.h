//---------------------------------------------------------------------------
#ifndef spl_CalligrapherH
#define spl_CalligrapherH
//---------------------------------------------------------------------------
//int spl_GetArabicOffset(HDC hdc);
//void spl_ConvertToArabic(HDC hdc,AnsiString Text,UINT *Indices,UINT *Orders,int *pDx,UINT &Count);
void spl_TextToGlyphs(HDC hdc,char *Text,wchar_t *Glyphs,UINT &Count);
//void spl_DrawChar(UINT CharOrd,double &XOffset,int Dx);
//void spl_DrawString(AnsiString strText);
void spl_DrawPolyBezier(LPPOINT pt,UINT cTotal);
//---------------------------------------------------------------------------
#endif
