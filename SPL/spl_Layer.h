//---------------------------------------------------------------------------
#ifndef spl_LayerH
#define spl_LayerH
//---------------------------------------------------------------------------
#include "spl_Point.h"
#include "spl_Region.h"
//---------------------------------------------------------------------------
class spl_Layer
{
public:
    vector<spl_Region,allocator<spl_Region> > Regions;

    spl_Layer(){}
    spl_Layer(const spl_Layer &Layer)
    {
    	Regions.erase(Regions.begin(),Regions.end());
        copy(Layer.Regions.begin(),Layer.Regions.end(),back_inserter(Regions));
    }
    spl_Layer &operator =(const spl_Layer &Layer)
    {
    	Regions.erase(Regions.begin(),Regions.end());
        copy(Layer.Regions.begin(),Layer.Regions.end(),back_inserter(Regions));
        return *this;
    }
};
//---------------------------------------------------------------------------
void spl_SaveLayer(FILE *file,spl_Layer &Layer);
void spl_LoadLayer(FILE *file,spl_Layer &Layer);
//---------------------------------------------------------------------------
void spl_SaveLayer(char *FileName,spl_Layer &Layer);
void spl_LoadLayer(char *FileName,spl_Layer &Layer);
//---------------------------------------------------------------------------
void spl_DrawLayer(HDC hdc,spl_Layer &Layer,bool Default);
void spl_DrawPolygonLayer(HDC hdc,spl_Layer &Layer,bool Layered);
void spl_DrawBezierLayer(HDC hdc,spl_Layer &Layer,bool Layered);
//---------------------------------------------------------------------------
spl_Rect spl_ComputeFrame(spl_Layer &Layer);
spl_BoundingBox spl_ComputeBoundingBox(spl_Layer &Layer);
void spl_ArrangeLayer(spl_Layer &iLayer,spl_Layer &oLayer);
//---------------------------------------------------------------------------
void spl_ScaleLayer(spl_Layer &iLayer,double Scale,bool Minimize,double Error,spl_Layer &oLayer);
//---------------------------------------------------------------------------
void spl_ReduceLayer(spl_Layer &iLayer,double Scale,double Error,spl_Layer &oLayer);
//---------------------------------------------------------------------------
void spl_ConvertBSplineToBezier(spl_Layer &iLayer,spl_Layer &oLayer);
//---------------------------------------------------------------------------
void spl_DivideCurveByDirection(spl_Layer &iLayer,double Step,spl_Layer &oLayer);
void spl_DivideCurveByLength(spl_Layer &iLayer,double Step,spl_Layer &oLayer);
void spl_DivideBezierCurve(spl_Layer &iLayer,double Step,double Error,spl_Layer &oLayer);
void spl_DivideBezierCurve(spl_Layer &iLayer,spl_Image *pPattern,double Error,spl_Layer &oLayer);
//---------------------------------------------------------------------------
void spl_FindNearestPoint(spl_Layer &iLayer,spl_Point &p,int &RegionIndex,int &ContourIndex,int &PointIndex,double &Distance);
//---------------------------------------------------------------------------
void spl_FindBestLayer(double Epsilon,spl_Layer &iLayer,spl_Layer &oLayer);
//---------------------------------------------------------------------------
void spl_SmoothLayer(spl_Layer &iLayer,char *Filter,int Order,int Degree,spl_Layer &oLayer);
//---------------------------------------------------------------------------
void spl_ReverseCurve(double Height,spl_Layer &Layer);
//---------------------------------------------------------------------------
void spl_ScaleCurve(double Scale,spl_Layer &Layer);
//---------------------------------------------------------------------------
void spl_RedefineCurve(spl_Layer &Layer);
//---------------------------------------------------------------------------
void spl_PrepareCurve(double Space,spl_Layer &Layer);
//---------------------------------------------------------------------------
void spl_CurveToSnake(spl_Layer &Layer);
//---------------------------------------------------------------------------
void spl_CloseCurve(spl_Layer &Layer);
//---------------------------------------------------------------------------
spl_UInt spl_CurveSize(spl_Layer &Layer);
//---------------------------------------------------------------------------
#endif
