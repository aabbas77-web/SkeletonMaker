//---------------------------------------------------------------------------
#ifndef spl_RegionH
#define spl_RegionH
//---------------------------------------------------------------------------
#include <vector.h>
//---------------------------------------------------------------------------
#include "spl_Point.h"
#include "spl_Contour.h"
#include "spl_EmbLib.h"
//---------------------------------------------------------------------------
// spl_Region:
// First Contour: The Outter Contour
// Other Contours: Holes
//---------------------------------------------------------------------------
class spl_Region
{
public:
    vector<spl_Contour,allocator<spl_Contour> > Contours;
    DWORD LineColor;
    DWORD FillColor;

    spl_Region():LineColor(0x00000000),FillColor(0x00000000){}
    spl_Region(const spl_Region &Region)
    {
        LineColor=Region.LineColor;
        FillColor=Region.FillColor;
        Contours.erase(Contours.begin(),Contours.end());
        copy(Region.Contours.begin(),Region.Contours.end(),back_inserter(Contours));
    }
    spl_Region &operator =(const spl_Region &Region)
    {
        LineColor=Region.LineColor;
        FillColor=Region.FillColor;
        Contours.erase(Contours.begin(),Contours.end());
        copy(Region.Contours.begin(),Region.Contours.end(),back_inserter(Contours));
        return *this;
    }
};
//---------------------------------------------------------------------------
void spl_SaveRegion(FILE *file,spl_Region &Region);
void spl_LoadRegion(FILE *file,spl_Region &Region);
//---------------------------------------------------------------------------
void spl_SaveRegion(char *FileName,spl_Region &Region);
void spl_LoadRegion(char *FileName,spl_Region &Region);
//---------------------------------------------------------------------------
void spl_DrawRegion(HDC hdc,spl_Region &Region,bool Default);
//---------------------------------------------------------------------------
void spl_DrawRegionForProcessing(HDC hdc,spl_Region &Region,bool bBezier,TColor RegionFillColor,TColor RegionLineColor,int nRegionPenWidth,TColor HoleFillColor,TColor HoleLineColor,int nHolePenWidth);
//---------------------------------------------------------------------------
void spl_DrawPolygonRegion(HDC hdc,spl_Region &Region,bool Layered);
//---------------------------------------------------------------------------
void spl_DrawBezierRegion(HDC hdc,spl_Region &Region,bool Layered);
//---------------------------------------------------------------------------
spl_Rect spl_ComputeFrame(spl_Region &Region);
spl_BoundingBox spl_ComputeBoundingBox(spl_Region &Region);
void spl_ArrangeRegion(spl_Region &iRegion,spl_Region &oRegion);
//---------------------------------------------------------------------------
void spl_ScaleRegion(spl_Region &iRegion,double Scale,bool Minimize,double Error,spl_Region &oRegion);
//---------------------------------------------------------------------------
void spl_ReduceRegion(spl_Region &iRegion,double Scale,double Error,spl_Region &oRegion);
//---------------------------------------------------------------------------
void spl_ConvertBSplineToBezier(spl_Region &iRegion,spl_Region &oRegion);
//---------------------------------------------------------------------------
void spl_DivideCurveByDirection(spl_Region &iRegion,double Step,spl_Region &oRegion);
void spl_DivideCurveByLength(spl_Region &iRegion,double Step,spl_Region &oRegion);
void spl_DivideBezierCurve(spl_Region &iRegion,double Step,double Error,spl_Region &oRegion);
void spl_DivideBezierCurve(spl_Region &iRegion,spl_Image *pPattern,double Error,spl_Region &oRegion);
void spl_DivideBezierCurveByDirection(spl_Region &iRegion,double Step,double Error,spl_Region &oRegion);
//---------------------------------------------------------------------------
void spl_FindNearestPoint(spl_Region &iRegion,spl_Point &p,bool IncludeContour,int &ContourIndex,int &PointIndex,double &Distance);
//---------------------------------------------------------------------------
void spl_FindBestRegion(double Epsilon,spl_Region &iRegion,spl_Region &oRegion);
//---------------------------------------------------------------------------
void spl_SmoothRegion(spl_Region &iRegion,char *Filter,int Order,int Degree,spl_Region &oRegion);
//---------------------------------------------------------------------------
void spl_ReverseCurve(double Height,spl_Region &Region);
//---------------------------------------------------------------------------
void spl_ScaleCurve(double Scale,spl_Region &Region);
//---------------------------------------------------------------------------
void spl_RedefineCurve(spl_Region &Region);
//---------------------------------------------------------------------------
void spl_PrepareCurve(double Space,spl_Region &Region);
//---------------------------------------------------------------------------
void spl_CurveToSnake(spl_Region &Region);
//---------------------------------------------------------------------------
void spl_CloseCurve(spl_Region &Region);
//---------------------------------------------------------------------------
spl_UInt spl_CurveSize(spl_Region &Region);
//---------------------------------------------------------------------------
void spl_ExtrudeBySkeleton(double ExtrudeDistance,spl_Region &Region,spl_Region &Extrude);
//---------------------------------------------------------------------------
bool spl_PointInRegion(spl_Region &Region,spl_Point &P);
//---------------------------------------------------------------------------
#endif
