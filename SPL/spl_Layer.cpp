//---------------------------------------------------------------------------
#include <stdio.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_Layer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void spl_SaveLayer(FILE *file,spl_Layer &Layer)
{
    int count=Layer.Regions.size();
    fwrite(&count,sizeof(int),1,file);
    for(int i=0;i<count;i++)
    {
        spl_SaveRegion(file,Layer.Regions[i]);
    }
}
//---------------------------------------------------------------------------
void spl_LoadLayer(FILE *file,spl_Layer &Layer)
{
    int count;
    fread(&count,sizeof(int),1,file);
    Layer.Regions.erase(Layer.Regions.begin(),Layer.Regions.end());
    Layer.Regions.resize(count);
    for(int i=0;i<count;i++)
    {
        spl_LoadRegion(file,Layer.Regions[i]);
    }
}
//---------------------------------------------------------------------------
void spl_SaveLayer(char *FileName,spl_Layer &Layer)
{
    FILE *file;
    file=fopen(FileName,"wb");
    spl_SaveLayer(file,Layer);
    fclose(file);
}
//---------------------------------------------------------------------------
void spl_LoadLayer(char *FileName,spl_Layer &Layer)
{
    FILE *file;
    file=fopen(FileName,"rb");
    spl_LoadLayer(file,Layer);
    fclose(file);
}
//---------------------------------------------------------------------------
void spl_DrawLayer(HDC hdc,spl_Layer &Layer,bool Default)
{
    int count=Layer.Regions.size();
    if(count<=0)
        return;
    for(int i=0;i<count;i++)
    {
        spl_DrawRegion(hdc,Layer.Regions[i],Default);
    }
}
//---------------------------------------------------------------------------
void spl_DrawPolygonLayer(HDC hdc,spl_Layer &Layer,bool Layered)
{
    int count=Layer.Regions.size();
    if(count<=0)
        return;
    if(Layered)
    {
        BeginPath(hdc);
        try
        {
            for(int i=0;i<count;i++)
            {
                spl_DrawPolygonRegion(hdc,Layer.Regions[i],Layered);
            }
            CloseFigure(hdc);
        }
        __finally
        {
            EndPath(hdc);
        }

        HBRUSH hNewBrush,hOldBrush;
        HPEN hNewPen,hOldPen;

        hNewBrush=CreateSolidBrush(Layer.Regions[0].FillColor);
        hOldBrush=SelectObject(hdc,hNewBrush);

        hNewPen=CreatePen(PS_SOLID,1,Layer.Regions[0].LineColor);
        hOldPen=SelectObject(hdc,hNewPen);

        // Uses the current pen and brush styles to paint the canvas.
        StrokeAndFillPath(hdc);

        SelectObject(hdc,hOldBrush);
        DeleteObject(hNewBrush);

        SelectObject(hdc,hOldPen);
        DeleteObject(hNewPen);
    }
    else
    {
        for(int i=0;i<count;i++)
        {
            spl_DrawPolygonRegion(hdc,Layer.Regions[i],Layered);
        }
    }
}
//---------------------------------------------------------------------------
void spl_DrawBezierLayer(HDC hdc,spl_Layer &Layer,bool Layered)
{
    int count=Layer.Regions.size();
    if(count<=0)
        return;
    if(Layered)
    {
        BeginPath(hdc);
        try
        {
            for(int i=0;i<count;i++)
            {
                spl_DrawBezierRegion(hdc,Layer.Regions[i],Layered);
            }
            CloseFigure(hdc);
        }
        __finally
        {
            EndPath(hdc);
        }

        HBRUSH hNewBrush,hOldBrush;
        HPEN hNewPen,hOldPen;

        hNewBrush=CreateSolidBrush(Layer.Regions[0].FillColor);
        hOldBrush=SelectObject(hdc,hNewBrush);

        hNewPen=CreatePen(PS_SOLID,1,Layer.Regions[0].LineColor);
        hOldPen=SelectObject(hdc,hNewPen);

        // Uses the current pen and brush styles to paint the canvas.
        StrokeAndFillPath(hdc);

        SelectObject(hdc,hOldBrush);
        DeleteObject(hNewBrush);

        SelectObject(hdc,hOldPen);
        DeleteObject(hNewPen);
    }
    else
    {
        for(int i=0;i<count;i++)
        {
            spl_DrawBezierRegion(hdc,Layer.Regions[i],Layered);
        }
    }
}
//---------------------------------------------------------------------------
spl_Rect spl_ComputeFrame(spl_Layer &Layer)
{
    if(Layer.Regions.empty())
        return spl_Rect(0,0,0,0);
    int count=Layer.Regions.size();
    spl_Rect Frame=spl_Rect(spl_MaxInt,spl_MaxInt,-spl_MaxInt,-spl_MaxInt);
    spl_Rect R;
    for(int i=0;i<count;i++)
    {
        R=spl_ComputeFrame(Layer.Regions[i]);
        if(R.left<Frame.left)
            Frame.left=R.left;
        if(R.top<Frame.top)
            Frame.top=R.top;
        if(R.right>Frame.right)
            Frame.right=R.right;
        if(R.bottom>Frame.bottom)
            Frame.bottom=R.bottom;
    }
    return Frame;
}
//---------------------------------------------------------------------------
spl_BoundingBox spl_ComputeBoundingBox(spl_Layer &Layer)
{
    if(Layer.Regions.empty()) return spl_BoundingBox();
    spl_BoundingBox BoundingBox=spl_ComputeBoundingBox(Layer.Regions[0]);
    spl_BoundingBox BBox;
    for(UINT i=1;i<Layer.Regions.size();i++)
    {
        BBox=spl_ComputeBoundingBox(Layer.Regions[i]);
        BoundingBox.Add(BBox.left);
        BoundingBox.Add(BBox.top);
        BoundingBox.Add(BBox.right);
        BoundingBox.Add(BBox.bottom);
    }
    BoundingBox.Update();
    return BoundingBox;
}
//---------------------------------------------------------------------------
void spl_ArrangeLayer(spl_Layer &iLayer,spl_Layer &oLayer)
{
    oLayer.Regions.erase(oLayer.Regions.begin(),oLayer.Regions.end());
    spl_BoundingBox BoundingBox;
    vector<spl_ContourOrder> ContourOrders;
    spl_ContourOrder ContourOrder;
    for(UINT i=0;i<iLayer.Regions.size();i++)
    {
        BoundingBox=spl_ComputeBoundingBox(iLayer.Regions[i]);
        ContourOrder.left=BoundingBox.left;
        ContourOrder.index=i;
        ContourOrders.push_back(ContourOrder);
    }
    sort(ContourOrders.begin(),ContourOrders.end());
    for(UINT i=0;i<ContourOrders.size();i++)
    {
        spl_Region Region;
        spl_ArrangeRegion(iLayer.Regions[ContourOrders[i].index],Region);
        oLayer.Regions.push_back(Region);
    }
}
//---------------------------------------------------------------------------
void spl_ScaleLayer(spl_Layer &iLayer,double Scale,bool Minimize,double Error,spl_Layer &oLayer)
{
    int count=iLayer.Regions.size();
    spl_Region tRegion;
    oLayer.Regions.erase(oLayer.Regions.begin(),oLayer.Regions.end());
    for(int i=0;i<count;i++)
    {
        spl_ScaleRegion(iLayer.Regions[i],Scale,Minimize,Error,tRegion);
        if(!tRegion.Contours.empty())
            oLayer.Regions.push_back(tRegion);
    }
}
//---------------------------------------------------------------------------
void spl_ReduceLayer(spl_Layer &iLayer,double Scale,double Error,spl_Layer &oLayer)
{
    int count=iLayer.Regions.size();
    spl_Region tRegion;
    oLayer.Regions.erase(oLayer.Regions.begin(),oLayer.Regions.end());
    for(int i=0;i<count;i++)
    {
        spl_ReduceRegion(iLayer.Regions[i],Scale,Error,tRegion);
        if(!tRegion.Contours.empty())
            oLayer.Regions.push_back(tRegion);
    }
}
//---------------------------------------------------------------------------
void spl_ConvertBSplineToBezier(spl_Layer &iLayer,spl_Layer &oLayer)
{
    int count=iLayer.Regions.size();
    spl_Region tRegion;
    oLayer.Regions.erase(oLayer.Regions.begin(),oLayer.Regions.end());
    for(int i=0;i<count;i++)
    {
        spl_ConvertBSplineToBezier(iLayer.Regions[i],tRegion);
        if(!tRegion.Contours.empty())
            oLayer.Regions.push_back(tRegion);
    }
}
//---------------------------------------------------------------------------
void spl_DivideCurveByDirection(spl_Layer &iLayer,double Step,spl_Layer &oLayer)
{
    int count=iLayer.Regions.size();
    spl_Region tRegion;
    oLayer.Regions.erase(oLayer.Regions.begin(),oLayer.Regions.end());
    for(int i=0;i<count;i++)
    {
        spl_DivideCurveByDirection(iLayer.Regions[i],Step,tRegion);
        if(!tRegion.Contours.empty())
            oLayer.Regions.push_back(tRegion);
    }
}
//---------------------------------------------------------------------------
void spl_DivideCurveByLength(spl_Layer &iLayer,double Step,spl_Layer &oLayer)
{
    int count=iLayer.Regions.size();
    spl_Region tRegion;
    oLayer.Regions.erase(oLayer.Regions.begin(),oLayer.Regions.end());
    for(int i=0;i<count;i++)
    {
        spl_DivideCurveByLength(iLayer.Regions[i],Step,tRegion);
        if(!tRegion.Contours.empty())
            oLayer.Regions.push_back(tRegion);
    }
}
//---------------------------------------------------------------------------
void spl_DivideBezierCurve(spl_Layer &iLayer,double Step,double Error,spl_Layer &oLayer)
{
    int count=iLayer.Regions.size();
    spl_Region tRegion;
    oLayer.Regions.erase(oLayer.Regions.begin(),oLayer.Regions.end());
    for(int i=0;i<count;i++)
    {
        spl_DivideBezierCurve(iLayer.Regions[i],Step,Error,tRegion);
        if(!tRegion.Contours.empty())
            oLayer.Regions.push_back(tRegion);
    }
}
//---------------------------------------------------------------------------
void spl_DivideBezierCurve(spl_Layer &iLayer,spl_Image *pPattern,double Error,spl_Layer &oLayer)
{
    int count=iLayer.Regions.size();
    spl_Region tRegion;
    oLayer.Regions.erase(oLayer.Regions.begin(),oLayer.Regions.end());
    for(int i=0;i<count;i++)
    {
        spl_DivideBezierCurve(iLayer.Regions[i],pPattern,Error,tRegion);
        if(!tRegion.Contours.empty())
            oLayer.Regions.push_back(tRegion);
    }
}
//---------------------------------------------------------------------------
void spl_FindNearestPoint(spl_Layer &iLayer,spl_Point &p,int &RegionIndex,int &ContourIndex,int &PointIndex,double &Distance)
{
    ContourIndex=0;
    PointIndex=0;

    double Dist;
    int CIndex;
    int PIndex;
    Distance=spl_MaxInt;
    for(UINT RIndex=0;RIndex<iLayer.Regions.size();RIndex++)
    {
//        spl_FindNearestPoint(iLayer.Regions[RIndex],p,true,CIndex,PIndex,Dist);
        CIndex=0;
        spl_FindNearestPoint(iLayer.Regions[RIndex].Contours[CIndex],p,PIndex,Dist);
        if(Dist<Distance)
        {
            Distance=Dist;
            RegionIndex=RIndex;
            ContourIndex=CIndex;
            PointIndex=PIndex;
            if(Distance<=1.0) break;
        }
    }
}
//---------------------------------------------------------------------------
void spl_FindBestLayer(double Epsilon,spl_Layer &iLayer,spl_Layer &oLayer)
{
    int count=iLayer.Regions.size();
    spl_Region tRegion;
    oLayer.Regions.erase(oLayer.Regions.begin(),oLayer.Regions.end());
    for(int i=0;i<count;i++)
    {
        spl_FindBestRegion(Epsilon,iLayer.Regions[i],tRegion);
        if(!tRegion.Contours.empty())
            oLayer.Regions.push_back(tRegion);
    }
}
//---------------------------------------------------------------------------
void spl_SmoothLayer(spl_Layer &iLayer,char *Filter,int Order,int Degree,spl_Layer &oLayer)
{
    int count=iLayer.Regions.size();
    spl_Region tRegion;
    oLayer.Regions.erase(oLayer.Regions.begin(),oLayer.Regions.end());
    for(int i=0;i<count;i++)
    {
        spl_SmoothRegion(iLayer.Regions[i],Filter,Order,Degree,tRegion);
        if(!tRegion.Contours.empty())
            oLayer.Regions.push_back(tRegion);
    }
}
//---------------------------------------------------------------------------
void spl_ReverseCurve(double Height,spl_Layer &Layer)
{
    for(spl_UInt i=0;i<Layer.Regions.size();i++)
    {
        spl_ReverseCurve(Height,Layer.Regions[i]);
    }
}
//---------------------------------------------------------------------------
void spl_ScaleCurve(double Scale,spl_Layer &Layer)
{
    for(spl_UInt i=0;i<Layer.Regions.size();i++)
    {
        spl_ScaleCurve(Scale,Layer.Regions[i]);
    }
}
//---------------------------------------------------------------------------
void spl_RedefineCurve(spl_Layer &Layer)
{
    for(spl_UInt i=0;i<Layer.Regions.size();)
    {
        spl_RedefineCurve(Layer.Regions[i]);
        if(Layer.Regions[i].Contours.empty())
        {
			Layer.Regions.erase(&Layer.Regions[i]);
        }
        else
        {
         	i++;
        }
    }
}
//---------------------------------------------------------------------------
void spl_PrepareCurve(double Space,spl_Layer &Layer)
{
    for(spl_UInt i=0;i<Layer.Regions.size();i++)
    {
        spl_PrepareCurve(Space,Layer.Regions[i]);
    }
}
//---------------------------------------------------------------------------
void spl_CurveToSnake(spl_Layer &Layer)
{
    for(spl_UInt i=0;i<Layer.Regions.size();i++)
    {
        spl_CurveToSnake(Layer.Regions[i]);
    }
}
//---------------------------------------------------------------------------
void spl_CloseCurve(spl_Layer &Layer)
{
    for(spl_UInt i=0;i<Layer.Regions.size();i++)
    {
        spl_CloseCurve(Layer.Regions[i]);
    }
}
//---------------------------------------------------------------------------
spl_UInt spl_CurveSize(spl_Layer &Layer)
{
    spl_UInt Size=0;
    for(spl_UInt i=0;i<Layer.Regions.size();i++)
    {
        Size+=spl_CurveSize(Layer.Regions[i]);
    }
    return Size;
}
//---------------------------------------------------------------------------

