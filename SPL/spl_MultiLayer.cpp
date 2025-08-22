//---------------------------------------------------------------------------
#include <stdio.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_MultiLayer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void spl_SaveMultiLayer(FILE *file,spl_MultiLayer &MultiLayer)
{
    int count=MultiLayer.Layers.size();
    fwrite(&count,sizeof(int),1,file);
    for(int i=0;i<count;i++)
    {
        spl_SaveLayer(file,MultiLayer.Layers[i]);
    }
}
//---------------------------------------------------------------------------
void spl_LoadMultiLayer(FILE *file,spl_MultiLayer &MultiLayer)
{
    int count;
    fread(&count,sizeof(int),1,file);
    MultiLayer.Layers.erase(MultiLayer.Layers.begin(),MultiLayer.Layers.end());
    MultiLayer.Layers.resize(count);
    for(int i=0;i<count;i++)
    {
        spl_LoadLayer(file,MultiLayer.Layers[i]);
    }
}
//---------------------------------------------------------------------------
void spl_SaveMultiLayer(char *FileName,spl_MultiLayer &MultiLayer)
{
    FILE *file;
    file=fopen(FileName,"wb");
    spl_SaveMultiLayer(file,MultiLayer);
    fclose(file);
}
//---------------------------------------------------------------------------
void spl_LoadMultiLayer(char *FileName,spl_MultiLayer &MultiLayer)
{
    FILE *file;
    file=fopen(FileName,"rb");
    spl_LoadMultiLayer(file,MultiLayer);
    fclose(file);
}
//---------------------------------------------------------------------------
void spl_DrawMultiLayer(HDC hdc,spl_MultiLayer &MultiLayer,bool Default)
{
    int count=MultiLayer.Layers.size();
    if(count<=0)
        return;

    for(int i=0;i<count;i++)
    {
        spl_DrawLayer(hdc,MultiLayer.Layers[i],Default);
    }
}
//---------------------------------------------------------------------------
void spl_DrawMultiPolygonLayer(HDC hdc,spl_MultiLayer &MultiLayer,bool Layered)
{
    int count=MultiLayer.Layers.size();
    if(count<=0)
        return;
    for(int i=0;i<count;i++)
    {
        spl_DrawPolygonLayer(hdc,MultiLayer.Layers[i],Layered);
    }
}
//---------------------------------------------------------------------------
void spl_DrawMultiBezierLayer(HDC hdc,spl_MultiLayer &MultiLayer,bool Layered)
{
    int count=MultiLayer.Layers.size();
    if(count<=0)
        return;
    for(int i=0;i<count;i++)
    {
        spl_DrawBezierLayer(hdc,MultiLayer.Layers[i],Layered);
    }
}
//---------------------------------------------------------------------------
spl_Rect spl_ComputeFrame(spl_MultiLayer &MultiLayer)
{
    if(MultiLayer.Layers.empty())
        return spl_Rect(0,0,0,0);
    int count=MultiLayer.Layers.size();
    spl_Rect Frame=spl_Rect(spl_MaxInt,spl_MaxInt,-spl_MaxInt,-spl_MaxInt);
    spl_Rect R;
    for(int i=0;i<count;i++)
    {
        R=spl_ComputeFrame(MultiLayer.Layers[i]);
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
spl_BoundingBox spl_ComputeBoundingBox(spl_MultiLayer &MultiLayer)
{
    if(MultiLayer.Layers.empty()) return spl_BoundingBox();
    spl_BoundingBox BoundingBox=spl_ComputeBoundingBox(MultiLayer.Layers[0]);
    spl_BoundingBox BBox;
    for(UINT i=1;i<MultiLayer.Layers.size();i++)
    {
        BBox=spl_ComputeBoundingBox(MultiLayer.Layers[i]);
        BoundingBox.Add(BBox.left);
        BoundingBox.Add(BBox.top);
        BoundingBox.Add(BBox.right);
        BoundingBox.Add(BBox.bottom);
    }
    BoundingBox.Update();
    return BoundingBox;
}
//---------------------------------------------------------------------------
void spl_ArrangeMultiLayer(spl_MultiLayer &iMultiLayer,spl_MultiLayer &oMultiLayer)
{
    oMultiLayer.Layers.erase(oMultiLayer.Layers.begin(),oMultiLayer.Layers.end());
    spl_BoundingBox BoundingBox;
    vector<spl_ContourOrder> ContourOrders;
    spl_ContourOrder ContourOrder;
    for(UINT i=0;i<iMultiLayer.Layers.size();i++)
    {
        BoundingBox=spl_ComputeBoundingBox(iMultiLayer.Layers[i]);
        ContourOrder.left=BoundingBox.left;
        ContourOrder.index=i;
        ContourOrders.push_back(ContourOrder);
    }
    sort(ContourOrders.begin(),ContourOrders.end());
    for(UINT i=0;i<ContourOrders.size();i++)
    {
        spl_Layer Layer;
        spl_ArrangeLayer(iMultiLayer.Layers[ContourOrders[i].index],Layer);
        oMultiLayer.Layers.push_back(Layer);
    }
}
//---------------------------------------------------------------------------
void spl_ScaleMultiLayer(spl_MultiLayer &iMultiLayer,double Scale,bool Minimize,double Error,spl_MultiLayer &oMultiLayer)
{
    int count=iMultiLayer.Layers.size();
    spl_Layer tLayer;
    oMultiLayer.Layers.erase(oMultiLayer.Layers.begin(),oMultiLayer.Layers.end());
    for(int i=0;i<count;i++)
    {
        spl_ScaleLayer(iMultiLayer.Layers[i],Scale,Minimize,Error,tLayer);
        if(!tLayer.Regions.empty())
            oMultiLayer.Layers.push_back(tLayer);
    }
}
//---------------------------------------------------------------------------
void spl_ReduceMultiLayer(spl_MultiLayer &iMultiLayer,double Scale,double Error,spl_MultiLayer &oMultiLayer)
{
    int count=iMultiLayer.Layers.size();
    spl_Layer tLayer;
    oMultiLayer.Layers.erase(oMultiLayer.Layers.begin(),oMultiLayer.Layers.end());
    for(int i=0;i<count;i++)
    {
        spl_ReduceLayer(iMultiLayer.Layers[i],Scale,Error,tLayer);
        if(!tLayer.Regions.empty())
            oMultiLayer.Layers.push_back(tLayer);
    }
}
//---------------------------------------------------------------------------
void spl_ConvertBSplineToBezier(spl_MultiLayer &iMultiLayer,spl_MultiLayer &oMultiLayer)
{
    int count=iMultiLayer.Layers.size();
    spl_Layer tLayer;
    oMultiLayer.Layers.erase(oMultiLayer.Layers.begin(),oMultiLayer.Layers.end());
    for(int i=0;i<count;i++)
    {
        spl_ConvertBSplineToBezier(iMultiLayer.Layers[i],tLayer);
        if(!tLayer.Regions.empty())
            oMultiLayer.Layers.push_back(tLayer);
    }
}
//---------------------------------------------------------------------------
void spl_DivideCurveByDirection(spl_MultiLayer &iMultiLayer,double Step,spl_MultiLayer &oMultiLayer)
{
    int count=iMultiLayer.Layers.size();
    spl_Layer tLayer;
    oMultiLayer.Layers.erase(oMultiLayer.Layers.begin(),oMultiLayer.Layers.end());
    for(int i=0;i<count;i++)
    {
        spl_DivideCurveByDirection(iMultiLayer.Layers[i],Step,tLayer);
        if(!tLayer.Regions.empty())
            oMultiLayer.Layers.push_back(tLayer);
    }
}
//---------------------------------------------------------------------------
void spl_DivideCurveByLength(spl_MultiLayer &iMultiLayer,double Step,spl_MultiLayer &oMultiLayer)
{
    int count=iMultiLayer.Layers.size();
    spl_Layer tLayer;
    oMultiLayer.Layers.erase(oMultiLayer.Layers.begin(),oMultiLayer.Layers.end());
    for(int i=0;i<count;i++)
    {
        spl_DivideCurveByLength(iMultiLayer.Layers[i],Step,tLayer);
        if(!tLayer.Regions.empty())
            oMultiLayer.Layers.push_back(tLayer);
    }
}
//---------------------------------------------------------------------------
void spl_DivideBezierCurve(spl_MultiLayer &iMultiLayer,double Step,double Error,spl_MultiLayer &oMultiLayer)
{
    int count=iMultiLayer.Layers.size();
    spl_Layer tLayer;
    oMultiLayer.Layers.erase(oMultiLayer.Layers.begin(),oMultiLayer.Layers.end());
    for(int i=0;i<count;i++)
    {
        spl_DivideBezierCurve(iMultiLayer.Layers[i],Step,Error,tLayer);
        if(!tLayer.Regions.empty())
            oMultiLayer.Layers.push_back(tLayer);
    }
}
//---------------------------------------------------------------------------
void spl_DivideBezierCurve(spl_MultiLayer &iMultiLayer,spl_Image *pPattern,double Error,spl_MultiLayer &oMultiLayer)
{
    int count=iMultiLayer.Layers.size();
    spl_Layer tLayer;
    oMultiLayer.Layers.erase(oMultiLayer.Layers.begin(),oMultiLayer.Layers.end());
    for(int i=0;i<count;i++)
    {
        spl_DivideBezierCurve(iMultiLayer.Layers[i],pPattern,Error,tLayer);
        if(!tLayer.Regions.empty())
            oMultiLayer.Layers.push_back(tLayer);
    }
}
//---------------------------------------------------------------------------
void spl_FindNearestPoint(spl_MultiLayer &iMultiLayer,spl_Point &p,int &LayerIndex,int &RegionIndex,int &ContourIndex,int &PointIndex,double &Distance)
{
    ContourIndex=0;
    PointIndex=0;

    double Dist;
    int CIndex;
    int PIndex;
    int RIndex;
    Distance=spl_MaxInt;
    for(UINT LIndex=0;LIndex<iMultiLayer.Layers.size();LIndex++)
    {
        spl_FindNearestPoint(iMultiLayer.Layers[LIndex],p,RIndex,CIndex,PIndex,Dist);
        if(Dist<Distance)
        {
            Distance=Dist;
            LayerIndex=LIndex;
            RegionIndex=RIndex;
            ContourIndex=CIndex;
            PointIndex=PIndex;
            if(Distance<=1.0) break;
        }
    }
}
//---------------------------------------------------------------------------
void spl_FindBestMultiLayer(double Epsilon,spl_MultiLayer &iMultiLayer,spl_MultiLayer &oMultiLayer)
{
    int count=iMultiLayer.Layers.size();
    spl_Layer tLayer;
    oMultiLayer.Layers.erase(oMultiLayer.Layers.begin(),oMultiLayer.Layers.end());
    for(int i=0;i<count;i++)
    {
        spl_FindBestLayer(Epsilon,iMultiLayer.Layers[i],tLayer);
        if(!tLayer.Regions.empty())
            oMultiLayer.Layers.push_back(tLayer);
    }
}
//---------------------------------------------------------------------------
void spl_SmoothMultiLayer(spl_MultiLayer &iMultiLayer,char *Filter,int Order,int Degree,spl_MultiLayer &oMultiLayer)
{
    int count=iMultiLayer.Layers.size();
    spl_Layer tLayer;
    oMultiLayer.Layers.erase(oMultiLayer.Layers.begin(),oMultiLayer.Layers.end());
    for(int i=0;i<count;i++)
    {
        spl_SmoothLayer(iMultiLayer.Layers[i],Filter,Order,Degree,tLayer);
        if(!tLayer.Regions.empty())
            oMultiLayer.Layers.push_back(tLayer);
    }
}
//---------------------------------------------------------------------------
void spl_ReverseCurve(double Height,spl_MultiLayer &MultiLayer)
{
    for(spl_UInt i=0;i<MultiLayer.Layers.size();i++)
    {
        spl_ReverseCurve(Height,MultiLayer.Layers[i]);
    }
}
//---------------------------------------------------------------------------
void spl_ScaleCurve(double Scale,spl_MultiLayer &MultiLayer)
{
    for(spl_UInt i=0;i<MultiLayer.Layers.size();i++)
    {
        spl_ScaleCurve(Scale,MultiLayer.Layers[i]);
    }
}
//---------------------------------------------------------------------------
void spl_RedefineCurve(spl_MultiLayer &MultiLayer)
{
    for(spl_UInt i=0;i<MultiLayer.Layers.size();)
    {
        spl_RedefineCurve(MultiLayer.Layers[i]);
        if(MultiLayer.Layers[i].Regions.empty())
        {
			MultiLayer.Layers.erase(&MultiLayer.Layers[i]);
        }
        else
        {
         	i++;
        }
    }
}
//---------------------------------------------------------------------------
void spl_PrepareCurve(double Space,spl_MultiLayer &MultiLayer)
{
    for(spl_UInt i=0;i<MultiLayer.Layers.size();i++)
    {
        spl_PrepareCurve(Space,MultiLayer.Layers[i]);
    }
}
//---------------------------------------------------------------------------
void spl_CurveToSnake(spl_MultiLayer &MultiLayer)
{
    for(spl_UInt i=0;i<MultiLayer.Layers.size();i++)
    {
        spl_CurveToSnake(MultiLayer.Layers[i]);
    }
}
//---------------------------------------------------------------------------
void spl_CloseCurve(spl_MultiLayer &MultiLayer)
{
    for(spl_UInt i=0;i<MultiLayer.Layers.size();i++)
    {
        spl_CloseCurve(MultiLayer.Layers[i]);
    }
}
//---------------------------------------------------------------------------
spl_UInt spl_CurveSize(spl_MultiLayer &MultiLayer)
{
    spl_UInt Size=0;
    for(spl_UInt i=0;i<MultiLayer.Layers.size();i++)
    {
        Size+=spl_CurveSize(MultiLayer.Layers[i]);
    }
    return Size;
}
//---------------------------------------------------------------------------

