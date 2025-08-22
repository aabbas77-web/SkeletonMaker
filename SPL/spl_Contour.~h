//---------------------------------------------------------------------------
#ifndef spl_ContourH
#define spl_ContourH
//---------------------------------------------------------------------------
#include "spl_Point.h"
#include "spl_Image.h"
//---------------------------------------------------------------------------
#define MAXF 200L		/* Maximum size of the filter */
//---------------------------------------------------------------------------
#define SPLINE			"Spline"			 /* Spline filter (l2-norm) */
#define SPLINE_L2		"Spline L2"			 /* Spline filter (L2-norm) */
#define SPLINE_CENT		"Centered Spline"	 /* Centered Spline filter (l2-norm) */
#define SPLINE_CENT_L2	"Centered Spline L2" /* Centered Spline filter (L2-norm) */
//---------------------------------------------------------------------------
struct spl_ContourInfo
{
    spl_UInt GIndex;// Global Contour Index
    bool ProcessFill;
    bool ProcessLine;
};
//---------------------------------------------------------------------------
class spl_Contour
{
public:
    spl_ContourInfo ContourInfo;
    vector<spl_Point,allocator<spl_Point> > Points;
    spl_Contour(){};
    spl_Contour(const spl_Contour &Contour)
    {
        ContourInfo=Contour.ContourInfo;
        Points.erase(Points.begin(),Points.end());
        copy(Contour.Points.begin(),Contour.Points.end(),back_inserter(Points));
    }
    spl_Contour &operator =(const spl_Contour &Contour)
    {
        ContourInfo=Contour.ContourInfo;
        Points.erase(Points.begin(),Points.end());
        copy(Contour.Points.begin(),Contour.Points.end(),back_inserter(Points));
        return *this;
    }
};
//---------------------------------------------------------------------------
struct spl_ContourOrder
{
    spl_Point left;
    spl_UInt  index;
};
//---------------------------------------------------------------------------
bool operator < (const spl_ContourOrder &c1,const spl_ContourOrder &c2)
{
    return (spl_Compare(&c1.left,&c2.left,&spl_Global_k)>0);
}
//---------------------------------------------------------------------------
void spl_SaveContour(FILE *file,spl_Contour &Contour);
void spl_LoadContour(FILE *file,spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_SaveContour(char *FileName,spl_Contour &Contour);
void spl_LoadContour(char *FileName,spl_Contour &Contour);
//---------------------------------------------------------------------------
spl_Rect spl_ComputeFrame(spl_Contour &Contour);
spl_BoundingBox spl_ComputeBoundingBox(spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_ScaleContour(spl_Contour &iContour,spl_Rect Frame,bool Minimize,double Error,spl_Contour &oContour);
void spl_ScaleContour(spl_Contour &iContour,float fXScale,float fYScale,bool Minimize,double Error,spl_Contour &oContour);
void spl_ReduceContour(spl_Contour &iContour,double Scale,double Error,spl_Contour &oContour);
//---------------------------------------------------------------------------
void spl_ConvertBSplineToBezier(spl_Contour &iContour,spl_Contour &oContour);
//---------------------------------------------------------------------------
void spl_DivideCurveByDirection(spl_Contour &iContour,double Step,spl_Contour &oContour);
void spl_DivideCurveByLength(spl_Contour &iContour,double Step,spl_Contour &oContour);
void spl_DivideBezierCurve(spl_Contour &iContour,double Step,double Error,spl_Contour &oContour);
void spl_DivideBezierCurve(spl_Contour &iContour,spl_Image *pPattern,double Error,spl_Contour &oContour);
void spl_DivideBezierCurveByDirection(spl_Contour &iContour,double Step,double Error,spl_Contour &oContour);
//---------------------------------------------------------------------------
void spl_FindBestContour(double Epsilon,spl_Contour &iContour,spl_Contour &oContour);
void spl_FindBestContour(double Epsilon,DWORD i1,DWORD i2,spl_Contour &iContour,spl_Contour &oContour);
//---------------------------------------------------------------------------
void spl_SmoothContour(spl_Contour &iContour,char *Filter,int Order,int Degree,spl_Contour &oContour);
//---------------------------------------------------------------------------
bool spl_ReduceBezier(spl_Contour &iContour,spl_Contour &oContour);
//---------------------------------------------------------------------------
void spl_DrawFilledContour(HDC hdc,spl_Contour &Contour,TColor FillColor,TColor LineColor);
//---------------------------------------------------------------------------
void spl_DrawPolygonContour(HDC hdc,spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_DrawPolylineContour(HDC hdc,spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_DrawBezierContour(HDC hdc,spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_FindNearestPoint(spl_Contour &iContour,spl_Point &p,int &PointIndex,double &Distance);
//---------------------------------------------------------------------------
void spl_GenerateBezierCurve(spl_Contour &iContour,bool Closed,double Error,spl_Contour &oContour);
//---------------------------------------------------------------------------
void spl_ReverseCurve(double Height,spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_ScaleCurve(double Scale,spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_RedefineCurve(spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_PrepareCurve(double Space,spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_CurveToSnake(spl_Contour &Contour,bool IsHole);
//---------------------------------------------------------------------------
void spl_CloseCurve(spl_Contour &Contour);
//---------------------------------------------------------------------------
spl_UInt spl_CurveSize(spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_ExtrudeBySkeleton(double ExtrudeDistance,spl_Contour &Contour,spl_Contour &Extrude);
//---------------------------------------------------------------------------
bool spl_IsClockwiseVertex(spl_Point *p1,spl_Point *p2,spl_Point *p3);
spl_Point spl_TriCenter(spl_Point *p1,spl_Point *p2,spl_Point *p3);
double spl_TriArea(spl_Point *p1,spl_Point *p2,spl_Point *p3);
double spl_Area(spl_Contour &Contour);
//---------------------------------------------------------------------------
spl_Point spl_Center(spl_Contour &Contour);
spl_Point spl_GeoCenter(spl_Contour &Contour);
double spl_ContourLength(spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_ConvexHull(spl_Contour &Contour,spl_Contour &ConvexHull);
//---------------------------------------------------------------------------
void spl_FindMinimalDistance(spl_Contour &Contour1,spl_Contour &Contour2,int &P1Index,int &P2Index);
//---------------------------------------------------------------------------
void spl_FindSharpEdges(spl_Contour &Contour,double dMinAngle,double dMaxAngle,spl_IntArray &Indices);
//---------------------------------------------------------------------------
// Õ”«» «·ÃÊ·«‰ »Ì‰ ‰ﬁÿ Ì‰ ··„‰Õ‰Ì «· «·Ì
double spl_CalculateTheTour(spl_Contour &Contour,spl_UInt nStartIndex,spl_UInt nEndIndex);
//---------------------------------------------------------------------------
bool spl_PointInContour(spl_Contour &Contour,spl_Point &P);
//---------------------------------------------------------------------------
#endif
