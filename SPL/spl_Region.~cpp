//---------------------------------------------------------------------------
#include <stdio.h>
#include <math.h>
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_Region.h"
#ifdef spl_Stitch_Curve_
#include "Main.h"
#endif// spl_Stitch_Curve_
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void spl_SaveRegion(FILE *file,spl_Region &Region)
{
    int count=Region.Contours.size();
    fwrite(&Region.LineColor,sizeof(Region.LineColor),1,file);
    fwrite(&Region.FillColor,sizeof(Region.LineColor),1,file);
    fwrite(&count,sizeof(int),1,file);
    for(int i=0;i<count;i++)
    {
        spl_SaveContour(file,Region.Contours[i]);
    }
}
//---------------------------------------------------------------------------
void spl_LoadRegion(FILE *file,spl_Region &Region)
{
    Region.Contours.erase(Region.Contours.begin(),Region.Contours.end());
    int count;
    fread(&Region.LineColor,sizeof(Region.LineColor),1,file);
    fread(&Region.FillColor,sizeof(Region.LineColor),1,file);
    fread(&count,sizeof(int),1,file);
    Region.Contours.resize(count);
    for(int i=0;i<count;i++)
    {
        spl_LoadContour(file,Region.Contours[i]);
    }
}
//---------------------------------------------------------------------------
void spl_SaveRegion(char *FileName,spl_Region &Region)
{
    FILE *file;
    file=fopen(FileName,"wb");
    spl_SaveRegion(file,Region);
    fclose(file);
}
//---------------------------------------------------------------------------
void spl_LoadRegion(char *FileName,spl_Region &Region)
{
    FILE *file;
    file=fopen(FileName,"rb");
    spl_LoadRegion(file,Region);
    fclose(file);
}
//---------------------------------------------------------------------------
void spl_DrawRegion(HDC hdc,spl_Region &Region,bool Default)
{
    int count=Region.Contours.size();
    int *pCounts=new int[count];
    int PointsCount=0;
    for(int i=0;i<count;i++)
    {
        pCounts[i]=Region.Contours[i].Points.size()+1;
        PointsCount+=pCounts[i];
    }
    POINT *pPoints=new POINT[PointsCount];
    int k=0;
    spl_Point P;
    int n;
    for(int i=0;i<count;i++)
    {
        n=Region.Contours[i].Points.size();
        for(int j=0;j<pCounts[i];j++)
        {
            P=Region.Contours[i].Points[j % n];
            pPoints[k].x=P.x;
            pPoints[k].y=P.y;
            k++;
        }
    }

    if(Default)
    {
        HBRUSH hNewBrush,hOldBrush;
        HPEN hNewPen,hOldPen;
                                   
        hNewBrush=CreateSolidBrush(Region.FillColor);
        hOldBrush=SelectObject(hdc,hNewBrush);

        hNewPen=CreatePen(PS_SOLID,1,Region.LineColor);
        hOldPen=SelectObject(hdc,hNewPen);

        PolyPolygon(hdc,pPoints,pCounts,count);

        SelectObject(hdc,hOldBrush);
        DeleteObject(hNewBrush);

        SelectObject(hdc,hOldPen);
        DeleteObject(hNewPen);
    }
    else
    {
        PolyPolygon(hdc,pPoints,pCounts,count);
    }

    if(pCounts)
        delete[] pCounts;
    if(pPoints)
        delete[] pPoints;
}
//---------------------------------------------------------------------------
void spl_DrawPolygonRegion(HDC hdc,spl_Region &Region,bool Layered)
{
    int count=Region.Contours.size();
    if(count<=0)
        return;
    int PointsCount;
    spl_Point P;

    if(Layered)
    {
        for(int i=0;i<count;i++)
        {
            PointsCount=Region.Contours[i].Points.size();
            if(PointsCount<=0)
                continue;
            POINT *pPoints=new POINT[PointsCount];
            for(int j=0;j<PointsCount;j++)
            {
                P=Region.Contours[i].Points[j];
                pPoints[j].x=P.x;
                pPoints[j].y=P.y;
            }

            Polygon(hdc,pPoints,PointsCount);
//            CloseFigure(hdc);

            if(pPoints)
                delete[] pPoints;
        }
    }
    else
    {
        BeginPath(hdc);
        try
        {
            for(int i=0;i<count;i++)
            {
                PointsCount=Region.Contours[i].Points.size();
                if(PointsCount<=0)
                    continue;
                POINT *pPoints=new POINT[PointsCount];
                for(int j=0;j<PointsCount;j++)
                {
                    P=Region.Contours[i].Points[j];
                    pPoints[j].x=P.x;
                    pPoints[j].y=P.y;
                }

                Polygon(hdc,pPoints,PointsCount);
//                CloseFigure(hdc);

                if(pPoints)
                    delete[] pPoints;
            }
        }
        __finally
        {
            EndPath(hdc);
        }

        HBRUSH hNewBrush,hOldBrush;
        HPEN hNewPen,hOldPen;

        hNewBrush=CreateSolidBrush(Region.FillColor);
        hOldBrush=SelectObject(hdc,hNewBrush);

        hNewPen=CreatePen(PS_SOLID,1,Region.LineColor);
        hOldPen=SelectObject(hdc,hNewPen);

        // Uses the current pen and brush styles to paint the canvas.
        StrokeAndFillPath(hdc);

        SelectObject(hdc,hOldBrush);
        DeleteObject(hNewBrush);

        SelectObject(hdc,hOldPen);
        DeleteObject(hNewPen);
    }
}
//---------------------------------------------------------------------------
void spl_DrawRegionForProcessing(HDC hdc,spl_Region &Region,bool bBezier,TColor RegionFillColor,TColor RegionLineColor,int nRegionPenWidth,TColor HoleFillColor,TColor HoleLineColor,int nHolePenWidth)
{
    int count=Region.Contours.size();
    if(count<=0)
        return;
    int PointsCount;
    spl_Point P;

    HBRUSH hNewBrush,hOldBrush;
    HPEN hNewPen,hOldPen;

    // Draw Filled Region
    if(count > 0)
    {
        PointsCount=Region.Contours[0].Points.size();
        if(PointsCount > 0)
        {
	        POINT *pPoints=new POINT[PointsCount+1];
	        for(int j=0;j<=PointsCount;j++)
	        {
	            P=Region.Contours[0].Points[j % PointsCount];
	            pPoints[j].x=P.x;
	            pPoints[j].y=P.y;
	        }

	        BeginPath(hdc);
    	    try
        	{
				if(bBezier)
                {
					PointsCount=3*(PointsCount/3)+1;
    		        PolyBezier(hdc,pPoints,PointsCount);
                }
                else
                {
	    	    	Polygon(hdc,pPoints,PointsCount);
                }
	        }
    	    __finally
        	{
	            EndPath(hdc);
    	    }

            hNewBrush=CreateSolidBrush(RegionFillColor);
            hOldBrush=SelectObject(hdc,hNewBrush);

            hNewPen=CreatePen(PS_SOLID,nRegionPenWidth,RegionLineColor);
            hOldPen=SelectObject(hdc,hNewPen);

	        // Uses the current pen and brush styles to paint the canvas.
            StrokeAndFillPath(hdc);

            SelectObject(hdc,hOldBrush);
            DeleteObject(hNewBrush);

            SelectObject(hdc,hOldPen);
            DeleteObject(hNewPen);

        	if(pPoints)
            {
            	delete[] pPoints;
                pPoints = NULL;
            }
        }
    }

    // Draw Filled Holes
    for(int i=1;i<count;i++)
    {
        PointsCount=Region.Contours[i].Points.size();
        if(PointsCount<=0)
            continue;
        POINT *pPoints=new POINT[PointsCount+1];
        for(int j=0;j<=PointsCount;j++)
        {
            P=Region.Contours[i].Points[j % PointsCount];
            pPoints[j].x=P.x;
            pPoints[j].y=P.y;
        }

        BeginPath(hdc);
        try
        {
            if(bBezier)
            {
                PointsCount=3*(PointsCount/3)+1;
                PolyBezier(hdc,pPoints,PointsCount);
            }
            else
            {
                Polygon(hdc,pPoints,PointsCount);
            }
		}
        __finally
        {
        	EndPath(hdc);
        }

        hNewBrush=CreateSolidBrush(HoleFillColor);
        hOldBrush=SelectObject(hdc,hNewBrush);

        hNewPen=CreatePen(PS_SOLID,nHolePenWidth,HoleLineColor);
        hOldPen=SelectObject(hdc,hNewPen);

        // Uses the current pen and brush styles to paint the canvas.
        StrokeAndFillPath(hdc);

        SelectObject(hdc,hOldBrush);
        DeleteObject(hNewBrush);

        SelectObject(hdc,hOldPen);
        DeleteObject(hNewPen);

        if(pPoints)
        {
            delete[] pPoints;
            pPoints = NULL;
        }
    }
}
//---------------------------------------------------------------------------
void spl_DrawBezierRegion(HDC hdc,spl_Region &Region,bool Layered)
{
    int count=Region.Contours.size();
    if(count<=0)
        return;
    int PointsCount;
    spl_Point P;

    if(Layered)
    {
        for(int i=0;i<count;i++)
        {
            PointsCount=Region.Contours[i].Points.size();
            if(PointsCount<=0)
                continue;
            POINT *pPoints=new POINT[PointsCount+1];
            for(int j=0;j<=PointsCount;j++)
            {
                P=Region.Contours[i].Points[j % PointsCount];
                pPoints[j].x=P.x;
                pPoints[j].y=P.y;
            }

            PointsCount=3*(PointsCount/3)+1;

            PolyBezier(hdc,pPoints,PointsCount);
            CloseFigure(hdc);

            if(pPoints)
                delete[] pPoints;
        }
    }
    else
    {
        BeginPath(hdc);
        try
        {
            for(int i=0;i<count;i++)
            {
                PointsCount=Region.Contours[i].Points.size();
                if(PointsCount<=0)
                    continue;
                POINT *pPoints=new POINT[PointsCount+1];
                for(int j=0;j<=PointsCount;j++)
                {
                    P=Region.Contours[i].Points[j % PointsCount];
                    pPoints[j].x=P.x;
                    pPoints[j].y=P.y;
                }

                PointsCount=3*(PointsCount/3)+1;

                PolyBezier(hdc,pPoints,PointsCount);
                CloseFigure(hdc);

                if(pPoints)
                    delete[] pPoints;
            }
        }
        __finally
        {
            EndPath(hdc);
        }

        HBRUSH hNewBrush,hOldBrush;
        HPEN hNewPen,hOldPen;

        hNewBrush=CreateSolidBrush(Region.FillColor);
        hOldBrush=SelectObject(hdc,hNewBrush);

        hNewPen=CreatePen(PS_SOLID,1,Region.LineColor);
        hOldPen=SelectObject(hdc,hNewPen);

        // Uses the current pen and brush styles to paint the canvas.
        StrokeAndFillPath(hdc);

        SelectObject(hdc,hOldBrush);
        DeleteObject(hNewBrush);

        SelectObject(hdc,hOldPen);
        DeleteObject(hNewPen);
    }
}
//---------------------------------------------------------------------------
spl_Rect spl_ComputeFrame(spl_Region &Region)
{
    if(Region.Contours.empty())
        return spl_Rect(0,0,0,0);
    int count=Region.Contours.size();
    spl_Rect Frame=spl_Rect(spl_MaxInt,spl_MaxInt,-spl_MaxInt,-spl_MaxInt);
    spl_Rect R;
    for(int i=0;i<count;i++)
    {
        R=spl_ComputeFrame(Region.Contours[i]);
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
spl_BoundingBox spl_ComputeBoundingBox(spl_Region &Region)
{
    if(Region.Contours.empty()) return spl_BoundingBox();
    spl_BoundingBox BoundingBox=spl_ComputeBoundingBox(Region.Contours[0]);
    spl_BoundingBox BBox;
    for(UINT i=1;i<Region.Contours.size();i++)
    {
        BBox=spl_ComputeBoundingBox(Region.Contours[i]);
        BoundingBox.Add(BBox.left);
        BoundingBox.Add(BBox.top);
        BoundingBox.Add(BBox.right);
        BoundingBox.Add(BBox.bottom);
    }
    BoundingBox.Update();
    return BoundingBox;
}
//---------------------------------------------------------------------------
void spl_ArrangeRegion(spl_Region &iRegion,spl_Region &oRegion)
{
    oRegion.Contours.erase(oRegion.Contours.begin(),oRegion.Contours.end());
    spl_BoundingBox BoundingBox;
    vector<spl_ContourOrder> ContourOrders;
    spl_ContourOrder ContourOrder;
    for(UINT i=0;i<iRegion.Contours.size();i++)
    {
        BoundingBox=spl_ComputeBoundingBox(iRegion.Contours[i]);
        ContourOrder.left=BoundingBox.left;
        ContourOrder.index=i;
        ContourOrders.push_back(ContourOrder);
    }
    sort(ContourOrders.begin(),ContourOrders.end());
    for(UINT i=0;i<ContourOrders.size();i++)
    {
        oRegion.Contours.push_back(iRegion.Contours[ContourOrders[i].index]);
    }
}
//---------------------------------------------------------------------------
void spl_ScaleRegion(spl_Region &iRegion,double Scale,bool Minimize,double Error,spl_Region &oRegion)
{
    oRegion.LineColor=iRegion.LineColor;
    oRegion.FillColor=iRegion.FillColor;
    if(Scale<=0.0)
        Scale=1.0;

    int count=iRegion.Contours.size();
    spl_Rect R,Frame;
    spl_Contour tContour;
    oRegion.Contours.erase(oRegion.Contours.begin(),oRegion.Contours.end());

    for(int i=0;i<count;i++)
    {
        Frame=spl_ComputeFrame(iRegion.Contours[i]);
        R=spl_Rect(Scale*Frame.left,Scale*Frame.top,Scale*Frame.right,Scale*Frame.bottom);
        spl_ScaleContour(iRegion.Contours[i],R,Minimize,Error,tContour);
        if(!tContour.Points.empty())
            oRegion.Contours.push_back(tContour);
    }
}
//---------------------------------------------------------------------------
void spl_ReduceRegion(spl_Region &iRegion,double Scale,double Error,spl_Region &oRegion)
{
    oRegion.LineColor=iRegion.LineColor;
    oRegion.FillColor=iRegion.FillColor;
    int count=iRegion.Contours.size();
    spl_Contour tContour;
    oRegion.Contours.erase(oRegion.Contours.begin(),oRegion.Contours.end());
    for(int i=0;i<count;i++)
    {
        spl_ReduceContour(iRegion.Contours[i],Scale,Error,tContour);
        if(!tContour.Points.empty())
            oRegion.Contours.push_back(tContour);
    }
}
//---------------------------------------------------------------------------
void spl_ConvertBSplineToBezier(spl_Region &iRegion,spl_Region &oRegion)
{
    oRegion.LineColor=iRegion.LineColor;
    oRegion.FillColor=iRegion.FillColor;
    int count=iRegion.Contours.size();
    spl_Contour tContour;
    oRegion.Contours.erase(oRegion.Contours.begin(),oRegion.Contours.end());
    for(int i=0;i<count;i++)
    {
        spl_ConvertBSplineToBezier(iRegion.Contours[i],tContour);
        if(!tContour.Points.empty())
            oRegion.Contours.push_back(tContour);
    }
}
//---------------------------------------------------------------------------
void spl_DivideCurveByDirection(spl_Region &iRegion,double Step,spl_Region &oRegion)
{
    oRegion.LineColor=iRegion.LineColor;
    oRegion.FillColor=iRegion.FillColor;
    oRegion.Contours.erase(oRegion.Contours.begin(),oRegion.Contours.end());
    int count=iRegion.Contours.size();
    if(count<=0)    return;
    spl_Contour tContour;
    for(int i=0;i<count;i++)
    {
        spl_DivideCurveByDirection(iRegion.Contours[i],Step,tContour);
        if(!tContour.Points.empty())
            oRegion.Contours.push_back(tContour);
    }
}
//---------------------------------------------------------------------------
void spl_DivideCurveByLength(spl_Region &iRegion,double Step,spl_Region &oRegion)
{
    oRegion.LineColor=iRegion.LineColor;
    oRegion.FillColor=iRegion.FillColor;
    oRegion.Contours.erase(oRegion.Contours.begin(),oRegion.Contours.end());
    int count=iRegion.Contours.size();
    if(count<=0)    return;
    spl_Contour tContour;
    for(int i=0;i<count;i++)
    {
        spl_DivideCurveByLength(iRegion.Contours[i],Step,tContour);
        if(!tContour.Points.empty())
            oRegion.Contours.push_back(tContour);
    }
}
//---------------------------------------------------------------------------
void spl_DivideBezierCurveByDirection(spl_Region &iRegion,double Step,double Error,spl_Region &oRegion)
{
    oRegion.LineColor=iRegion.LineColor;
    oRegion.FillColor=iRegion.FillColor;
    int count=iRegion.Contours.size();
    spl_Contour tContour;
    oRegion.Contours.erase(oRegion.Contours.begin(),oRegion.Contours.end());
    for(int i=0;i<count;i++)
    {
        spl_DivideBezierCurveByDirection(iRegion.Contours[i],Step,Error,tContour);
        if(!tContour.Points.empty())
            oRegion.Contours.push_back(tContour);
    }
}
//---------------------------------------------------------------------------
void spl_DivideBezierCurve(spl_Region &iRegion,double Step,double Error,spl_Region &oRegion)
{
    oRegion.LineColor=iRegion.LineColor;
    oRegion.FillColor=iRegion.FillColor;
    int count=iRegion.Contours.size();
    spl_Contour tContour;
    oRegion.Contours.erase(oRegion.Contours.begin(),oRegion.Contours.end());
    for(int i=0;i<count;i++)
    {
        spl_DivideBezierCurve(iRegion.Contours[i],Step,Error,tContour);
        if(!tContour.Points.empty())
            oRegion.Contours.push_back(tContour);
    }
}
//---------------------------------------------------------------------------
void spl_DivideBezierCurve(spl_Region &iRegion,spl_Image *pPattern,double Error,spl_Region &oRegion)
{
    oRegion.LineColor=iRegion.LineColor;
    oRegion.FillColor=iRegion.FillColor;
    int count=iRegion.Contours.size();
    spl_Contour tContour;
    oRegion.Contours.erase(oRegion.Contours.begin(),oRegion.Contours.end());
    for(int i=0;i<count;i++)
    {
        spl_DivideBezierCurve(iRegion.Contours[i],pPattern,Error,tContour);
        if(!tContour.Points.empty())
            oRegion.Contours.push_back(tContour);
    }
}
//---------------------------------------------------------------------------
void spl_FindNearestPoint(spl_Region &iRegion,spl_Point &p,bool IncludeContour,int &ContourIndex,int &PointIndex,double &Distance)
{
    ContourIndex=0;
    PointIndex=0;

    double Dist;
    int PIndex;
    Distance=spl_MaxInt;
    if(IncludeContour)
    {
        for(UINT CIndex=0;CIndex<iRegion.Contours.size();CIndex++)
        {
            spl_FindNearestPoint(iRegion.Contours[CIndex],p,PIndex,Dist);
            if(Dist<Distance)
            {
                Distance=Dist;
                ContourIndex=CIndex;
                PointIndex=PIndex;
                if(Distance<=1.0) break;
            }
        }
    }
    else
    {
        for(UINT CIndex=1;CIndex<iRegion.Contours.size();CIndex++)
        {
            spl_FindNearestPoint(iRegion.Contours[CIndex],p,PIndex,Dist);
            if(Dist<Distance)
            {
                Distance=Dist;
                ContourIndex=CIndex;
                PointIndex=PIndex;
                if(Distance<=1.0) break;
            }
        }
    }
}
//---------------------------------------------------------------------------
void spl_FindBestRegion(double Epsilon,spl_Region &iRegion,spl_Region &oRegion)
{
    oRegion.LineColor=iRegion.LineColor;
    oRegion.FillColor=iRegion.FillColor;
    int count=iRegion.Contours.size();
    spl_Contour tContour;
    oRegion.Contours.erase(oRegion.Contours.begin(),oRegion.Contours.end());
    for(int i=0;i<count;i++)
    {
        spl_FindBestContour(Epsilon,iRegion.Contours[i],tContour);
        if(!tContour.Points.empty())
            oRegion.Contours.push_back(tContour);
    }
}
//---------------------------------------------------------------------------
void spl_SmoothRegion(spl_Region &iRegion,char *Filter,int Order,int Degree,spl_Region &oRegion)
{
    oRegion.LineColor=iRegion.LineColor;
    oRegion.FillColor=iRegion.FillColor;
    int count=iRegion.Contours.size();
    spl_Contour tContour;
    oRegion.Contours.erase(oRegion.Contours.begin(),oRegion.Contours.end());
    for(int i=0;i<count;i++)
    {
        spl_SmoothContour(iRegion.Contours[i],Filter,Order,Degree,tContour);
        if(!tContour.Points.empty())
            oRegion.Contours.push_back(tContour);
    }
}
//---------------------------------------------------------------------------
void spl_ReverseCurve(double Height,spl_Region &Region)
{
    for(spl_UInt i=0;i<Region.Contours.size();i++)
    {
        spl_ReverseCurve(Height,Region.Contours[i]);
    }
}
//---------------------------------------------------------------------------
void spl_ScaleCurve(double Scale,spl_Region &Region)
{
    for(spl_UInt i=0;i<Region.Contours.size();i++)
    {
        spl_ScaleCurve(Scale,Region.Contours[i]);
    }
}
//---------------------------------------------------------------------------
void spl_RedefineCurve(spl_Region &Region)
{
    for(spl_UInt i=0;i<Region.Contours.size();)
    {
        spl_RedefineCurve(Region.Contours[i]);
        if(Region.Contours[i].Points.empty())
        {
			Region.Contours.erase(&Region.Contours[i]);
        }
        else
        {
         	i++;
        }
    }
}
//---------------------------------------------------------------------------
void spl_PrepareCurve(double Space,spl_Region &Region)
{
    for(spl_UInt i=0;i<Region.Contours.size();i++)
    {
        spl_PrepareCurve(Space,Region.Contours[i]);
    }
}
//---------------------------------------------------------------------------
void spl_CurveToSnake(spl_Region &Region)
{
    for(spl_UInt i=0;i<Region.Contours.size();i++)
    {
        spl_CurveToSnake(Region.Contours[i],false);
    }
}
//---------------------------------------------------------------------------
void spl_CloseCurve(spl_Region &Region)
{
    for(spl_UInt i=0;i<Region.Contours.size();i++)
    {
        spl_CloseCurve(Region.Contours[i]);
    }
}
//---------------------------------------------------------------------------
spl_UInt spl_CurveSize(spl_Region &Region)
{
    spl_UInt Size=0;
    for(spl_UInt i=0;i<Region.Contours.size();i++)
    {
        Size+=spl_CurveSize(Region.Contours[i]);
    }
    return Size;
}
//---------------------------------------------------------------------------
void spl_ExtrudeBySkeleton(double ExtrudeDistance,spl_Region &Region,spl_Region &Extrude)
{
    for(spl_UInt i=0;i<Region.Contours.size();i++)
    {
        spl_Contour tContour;
        spl_ExtrudeBySkeleton(ExtrudeDistance,Region.Contours[i],tContour);
        if(!tContour.Points.empty())
        {
            Extrude.Contours.push_back(tContour);
        }
    }
}
//---------------------------------------------------------------------------
bool spl_PointInRegion(spl_Region &Region,spl_Point &P)
{
	if(Region.Contours.empty())	return false;
	bool bPointInHoles = false;
    bool bPointInOutterContour;
    bPointInOutterContour = spl_PointInContour(Region.Contours[0],P); 
	for(UINT i=1;i<Region.Contours.size();i++)
    {
    	if(spl_PointInContour(Region.Contours[i],P))
        {
        	bPointInHoles = true;
			break;
        }
    }
    return (bPointInOutterContour && (!bPointInHoles));
}
//---------------------------------------------------------------------------

