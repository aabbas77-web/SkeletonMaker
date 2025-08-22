//---------------------------------------------------------------------------
#ifndef spl_MultiLayerH
#define spl_MultiLayerH
//---------------------------------------------------------------------------
#include "spl_Layer.h"
//---------------------------------------------------------------------------
class spl_MultiLayer
{
public:
    vector<spl_Layer,allocator<spl_Layer> > Layers;

    spl_MultiLayer(){}
    spl_MultiLayer(const spl_MultiLayer &MultiLayer)
    {
        Layers.erase(Layers.begin(),Layers.end());
        copy(MultiLayer.Layers.begin(),MultiLayer.Layers.end(),back_inserter(Layers));
    }
    spl_MultiLayer &operator =(const spl_MultiLayer &MultiLayer)
    {
        Layers.erase(Layers.begin(),Layers.end());
        copy(MultiLayer.Layers.begin(),MultiLayer.Layers.end(),back_inserter(Layers));
        return *this;
    }
};
//---------------------------------------------------------------------------
void spl_SaveMultiLayer(FILE *file,spl_MultiLayer &MultiLayer);
void spl_LoadMultiLayer(FILE *file,spl_MultiLayer &MultiLayer);
//---------------------------------------------------------------------------
void spl_SaveMultiLayer(char *FileName,spl_MultiLayer &MultiLayer);
void spl_LoadMultiLayer(char *FileName,spl_MultiLayer &MultiLayer);
//---------------------------------------------------------------------------
void spl_DrawMultiLayer(HDC hdc,spl_MultiLayer &MultiLayer,bool Default);
void spl_DrawMultiPolygonLayer(HDC hdc,spl_MultiLayer &MultiLayer,bool Layered);
void spl_DrawMultiBezierLayer(HDC hdc,spl_MultiLayer &MultiLayer,bool Layered);
//---------------------------------------------------------------------------
spl_Rect spl_ComputeFrame(spl_MultiLayer &MultiLayer);
spl_BoundingBox spl_ComputeBoundingBox(spl_MultiLayer &MultiLayer);
void spl_ArrangeMultiLayer(spl_MultiLayer &iMultiLayer,spl_MultiLayer &oMultiLayer);
//---------------------------------------------------------------------------
void spl_ScaleMultiLayer(spl_MultiLayer &iMultiLayer,double Scale,bool Minimize,double Error,spl_MultiLayer &oMultiLayer);
//---------------------------------------------------------------------------
void spl_ReduceMultiLayer(spl_MultiLayer &iMultiLayer,double Scale,double Error,spl_MultiLayer &oMultiLayer);
//---------------------------------------------------------------------------
void spl_ConvertBSplineToBezier(spl_MultiLayer &iMultiLayer,spl_MultiLayer &oMultiLayer);
//---------------------------------------------------------------------------
void spl_DivideCurveByDirection(spl_MultiLayer &iMultiLayer,double Step,spl_MultiLayer &oMultiLayer);
void spl_DivideCurveByLength(spl_MultiLayer &iMultiLayer,double Step,spl_MultiLayer &oMultiLayer);
void spl_DivideBezierCurve(spl_MultiLayer &iMultiLayer,double Step,double Error,spl_MultiLayer &oMultiLayer);
void spl_DivideBezierCurve(spl_MultiLayer &iMultiLayer,spl_Image *pPattern,double Error,spl_MultiLayer &oMultiLayer);
//---------------------------------------------------------------------------
void spl_FindNearestPoint(spl_MultiLayer &iMultiLayer,spl_Point &p,int &LayerIndex,int &RegionIndex,int &ContourIndex,int &PointIndex,double &Distance);
//---------------------------------------------------------------------------
void spl_FindBestMultiLayer(double Epsilon,spl_MultiLayer &iMultiLayer,spl_MultiLayer &oMultiLayer);
//---------------------------------------------------------------------------
void spl_SmoothMultiLayer(spl_MultiLayer &iMultiLayer,char *Filter,int Order,int Degree,spl_MultiLayer &oMultiLayer);
//---------------------------------------------------------------------------
void spl_ReverseCurve(double Height,spl_MultiLayer &MultiLayer);
//---------------------------------------------------------------------------
void spl_ScaleCurve(double Scale,spl_MultiLayer &MultiLayer);
//---------------------------------------------------------------------------
void spl_RedefineCurve(spl_MultiLayer &MultiLayer);
//---------------------------------------------------------------------------
void spl_PrepareCurve(double Space,spl_MultiLayer &MultiLayer);
//---------------------------------------------------------------------------
void spl_CurveToSnake(spl_MultiLayer &MultiLayer);
//---------------------------------------------------------------------------
void spl_CloseCurve(spl_MultiLayer &MultiLayer);
//---------------------------------------------------------------------------
spl_UInt spl_CurveSize(spl_MultiLayer &MultiLayer);
//---------------------------------------------------------------------------
#endif
