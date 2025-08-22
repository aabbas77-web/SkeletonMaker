//---------------------------------------------------------------------------
#ifndef spl_GlyphOutlinesH
#define spl_GlyphOutlinesH
//---------------------------------------------------------------------------
#include "spl_Point.h"
//---------------------------------------------------------------------------
int PASCAL NEAR IntFromFixed(FIXED f);
FIXED PASCAL NEAR fxDiv2(FIXED fxVal1, FIXED fxVal2);
UINT MakeBezierFromLine( POINT *pPts, POINT startpt, POINT endpt );
UINT MakeBezierFromQBSpline( POINT *pPts, POINTFX *pSpline );
UINT AppendPolyLineToBezier( LPPOINT pt, POINTFX start, LPTTPOLYCURVE lpCurve );
UINT AppendQuadBSplineToBezier( LPPOINT pt, POINTFX start, LPTTPOLYCURVE lpCurve );
UINT CloseContour( LPPOINT pt, UINT cTotal );
void DrawT2Outline(HDC hDC, LPTTPOLYGONHEADER lpHeader, DWORD size,spl_Point Origin); 
void GetCharacterGlyphs(HDC hdc,int nCharCode,bool bUnicode,spl_Point &Origin);
//---------------------------------------------------------------------------
#endif
