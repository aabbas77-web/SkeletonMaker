//---------------------------------------------------------------------------
#ifndef spl_PathFinderH
#define spl_PathFinderH
//---------------------------------------------------------------------------
#include "spl_Point.h"
#include "spl_Contour.h"
#include "spl_Image.h"
//---------------------------------------------------------------------------
bool spl_FindPath(spl_Image *pIndices,spl_Point P1,spl_Point P2,spl_Contour &Path);
void DrawContour(spl_Contour &Contour,TColor Color);
//---------------------------------------------------------------------------
#endif
