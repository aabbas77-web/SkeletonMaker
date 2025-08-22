//---------------------------------------------------------------------------
#ifndef spl_DigitizerH
#define spl_DigitizerH
//---------------------------------------------------------------------------
#include <vector.h>
#include <set.h>
//---------------------------------------------------------------------------
#include "spl_Contour.h"
#include "spl_Image.h"
#include "spl_MultiLayer.h"
//---------------------------------------------------------------------------
#define     spl_SetPixelContour(x,y,c)      (((spl_UWord *)spl_pGlobalPixelsInfo->ppLines[(spl_UInt)(y)])[(spl_UInt)(x)]=((spl_UWord)(c)))
#define     spl_GetPixelContour(x,y)        ((spl_UWord)((((spl_UWord *)spl_pGlobalPixelsInfo->ppLines[(spl_UInt)(y)])[(spl_UInt)(x)])))
//---------------------------------------------------------------------------
class spl_Curve
{
public:
    BYTE FillColorIndex;// The Same Layer Index (Global)
    BYTE LineColorIndex;

    bool ProcessFillColor;
    bool ProcessLineColor;

    spl_CurveInfo CurveInfo;
    spl_Contour   Contour;

    vector<spl_UWord> Holes;// Holes Indices
    vector<spl_UWord> ComplexHoles;// Complex Holes Indices
    set<spl_UWord> OutterNeighbors;// Outter Neighbors Regions Indices

    spl_Curve():FillColorIndex(0),LineColorIndex(0){}
    spl_Curve(const spl_Curve &Curve)
    {
        FillColorIndex=Curve.FillColorIndex;
        LineColorIndex=Curve.LineColorIndex;

        ProcessFillColor=Curve.ProcessFillColor;
        ProcessLineColor=Curve.ProcessLineColor;

        CurveInfo=Curve.CurveInfo;
        Contour.ContourInfo=Curve.Contour.ContourInfo;
        Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
        copy(Curve.Contour.Points.begin(),Curve.Contour.Points.end(),back_inserter(Contour.Points));

        Holes.erase(Holes.begin(),Holes.end());
        copy(Curve.Holes.begin(),Curve.Holes.end(),back_inserter(Holes));
        ComplexHoles.erase(ComplexHoles.begin(),ComplexHoles.end());
        copy(Curve.ComplexHoles.begin(),Curve.ComplexHoles.end(),back_inserter(ComplexHoles));
        OutterNeighbors.erase(OutterNeighbors.begin(),OutterNeighbors.end());
        OutterNeighbors.insert(Curve.OutterNeighbors.begin(),Curve.OutterNeighbors.end());
    }
    spl_Curve &operator =(const spl_Curve &Curve)
    {
        FillColorIndex=Curve.FillColorIndex;
        LineColorIndex=Curve.LineColorIndex;

        ProcessFillColor=Curve.ProcessFillColor;
        ProcessLineColor=Curve.ProcessLineColor;

        CurveInfo=Curve.CurveInfo;
        Contour.ContourInfo=Curve.Contour.ContourInfo;
        Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
        copy(Curve.Contour.Points.begin(),Curve.Contour.Points.end(),back_inserter(Contour.Points));

        Holes.erase(Holes.begin(),Holes.end());
        copy(Curve.Holes.begin(),Curve.Holes.end(),back_inserter(Holes));
        ComplexHoles.erase(ComplexHoles.begin(),ComplexHoles.end());
        copy(Curve.ComplexHoles.begin(),Curve.ComplexHoles.end(),back_inserter(ComplexHoles));
        OutterNeighbors.erase(OutterNeighbors.begin(),OutterNeighbors.end());
        OutterNeighbors.insert(Curve.OutterNeighbors.begin(),Curve.OutterNeighbors.end());
        return *this;
    }
};
//---------------------------------------------------------------------------
extern vector<spl_Curve> spl_GlobalCurves;
extern spl_Image *spl_pGlobalPixelsInfo;
extern spl_UInt spl_DigitizerBorder;
extern spl_UInt spl_ContoursCount;
//---------------------------------------------------------------------------
void spl_FollowDigitizedContour(bool bOnObject,bool SimpleMethode,spl_UByte Dir,spl_Image *pIndices,spl_UInt x,spl_UInt y,spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_FollowDigitizedContour(bool SimpleMethode,spl_Image *pIndices,spl_UInt x,spl_UInt y,spl_Contour &Contour);
//---------------------------------------------------------------------------
void spl_ExtractDigitizedContoursForProcessing(spl_Image *pIndices);
//---------------------------------------------------------------------------
void spl_FollowDigitizedContourForProcessing(bool SimpleMethode,spl_UInt x,spl_UInt y,spl_Contour &Contour,set<spl_UWord> &OutterNeighbors);
//---------------------------------------------------------------------------
void spl_ConvertGlobalContourToRegion(spl_UInt ContourIndex,bool Smoothed,bool ByBezier,spl_UInt Order,spl_UInt Degree,spl_Region &Region);
//---------------------------------------------------------------------------
void spl_ConvertGlobalContoursToMultiLayer(bool Smoothed,bool ByBezier,spl_UInt Order,spl_UInt Degree,spl_MultiLayer &MultiLayer);
//---------------------------------------------------------------------------
void spl_ConvertGlobalContoursToMultiLayerForEmbroidery(spl_MultiLayer &MultiLayer);
//---------------------------------------------------------------------------
void spl_ReorderMultiLayerForEmbroidery(spl_Image *pIndices,spl_MultiLayer &MultiLayer);
//---------------------------------------------------------------------------
void spl_SaveGlobalCurves(bool Smoothed,bool ByBezier,spl_UInt Order,spl_UInt Degree,AnsiString strFileName);
//---------------------------------------------------------------------------
void spl_LoadGlobalCurves(AnsiString strFileName,spl_Layer &Layer);
//---------------------------------------------------------------------------
#endif
