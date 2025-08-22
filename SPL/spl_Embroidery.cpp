//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_Embroidery.h"
#include "spl_PathFinder.h"
#ifdef _EMB_TRACE_
	#include "Main.h"
#endif // _EMB_TRACE_
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
bool spl_bIsInvalidEmbroidery = false;
//---------------------------------------------------------------------------
static spl_Image *_pIndices;
static spl_Image *_pPathIndices;
static spl_UByte _ColorIndex;
static spl_UByte _PathColorIndex;
static spl_UInt  _Color;
static spl_UInt  _NegColor;
//---------------------------------------------------------------------------
void spl_FillStitchs_ZigZag(spl_Point &p,spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath);
void spl_FillStitchs_Run(spl_Point &p,spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath);
void spl_FillStitchs_Satin(double SatinHeight,spl_Point &p,spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath);
void spl_FillStitchs_ZigZag_Best_Normal(spl_Point &p,spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath);
void spl_FillStitchs_ZigZag_Best_Jump(spl_Point &p,spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath);
//---------------------------------------------------------------------------
void spl_GetPointProjection(spl_Point &P,spl_Point &NP)
{
    bool Found=false;
    NP.x=int(P.x);
    NP.y=int(P.y);
    while(
            (int(NP.x)>=0)&&(UINT(NP.x)<_pIndices->Width)&&
            (int(NP.y)>=0)&&(UINT(NP.y)<_pIndices->Height)&&
            (_pIndices->ppLines[UINT(NP.y)][UINT(NP.x)]==_ColorIndex)
         )
    {
        NP.x+=spl_T1R[spl_Global_Dir].x;
        NP.y+=spl_T1R[spl_Global_Dir].y;
        Found=true;
    }
    if(Found)
    {
        NP.x-=spl_T1R[spl_Global_Dir].x;
        NP.y-=spl_T1R[spl_Global_Dir].y;
    }
}
//---------------------------------------------------------------------------
void spl_SerializeRegion(spl_Region &Region,spl_Contour &Contour)
{
    Contour.Points.clear();
    if(Region.Contours.empty()) return;
    spl_CurveToSnake(Region);

    // Process Holes
    spl_UInt ContourIndex;
    spl_UInt NContourIndex;
    spl_Point P,NP;
    spl_Point *p,*op,*np;
    spl_Point *c,*nc;
    double Distance;
    int PIndex,CIndex;
    spl_UInt count,ncount;
    spl_Point NPP;
    spl_UInt I,J;
    bool Found;
    spl_UInt nContoursCount = Region.Contours.size();

    for(spl_UInt i=1;i<nContoursCount;i++)
    {
        // Find Best P,NP
        Found=false;
        for(spl_UInt j=0;j<Region.Contours[i].Points.size();j++)
        {
            P=Region.Contours[i].Points[j];
            spl_GetPointProjection(P,NP);
//            DrawLine(P,NP);
//            DrawPoint(P);
            Distance=spl_PDistance(&P,&NP);
            if(Distance <= 0.0)	continue;
            spl_FindNearestPoint(Region,NP,true,CIndex,PIndex,Distance);
            if(UINT(CIndex)!=i)
            {
                I=i;
                J=j;
                NPP=Region.Contours[CIndex].Points[PIndex];
                Found=true;
            }
        }

        if(Found)
        {
            p=&Region.Contours[I].Points[J];
            c=p->pPrev;

            spl_FindNearestPoint(Region,NPP,true,CIndex,PIndex,Distance);
            ncount=Region.Contours[CIndex].Points.size();
            np=&Region.Contours[CIndex].Points[PIndex];
            nc=&Region.Contours[CIndex].Points[(PIndex+1) % ncount];

            np->pNext=p;

            c->pNext=nc;
        }
    }

    spl_Point *i0,*i;
    i0=&Region.Contours[0].Points[0];
    i=i0;
    int nIterationCount = 0;
    while(i->pNext!=i0)
    {
        Contour.Points.push_back(splPoint(i->x,i->y));
        i=i->pNext;

        nIterationCount++;
        if(nIterationCount >= spl_nMaxIterationCount)
        {
        	spl_bIsInvalidEmbroidery = true;
        	break;
        }
    }
}
//---------------------------------------------------------------------------
/*
void spl_GetPointProjection(spl_Point &P,spl_Point &NP)
{
    bool Found=false;
    NP=P;
    while(
            (NP.x>=0)&&(NP.x<_pIndices->Width)&&
            (NP.y>=0)&&(NP.y<_pIndices->Height)&&
            (_pIndices->ppLines[int(NP.y)][int(NP.x)]==_ColorIndex)
         )
    {
        NP.x+=spl_T1R[spl_Global_Dir].x;
        NP.y+=spl_T1R[spl_Global_Dir].y;
        Found=true;
    }
    if(Found)
    {
        NP.x-=spl_T1R[spl_Global_Dir].x;
        NP.y-=spl_T1R[spl_Global_Dir].y;
    }
}
//---------------------------------------------------------------------------
void spl_SerializeRegion(spl_Region &Region,spl_Contour &Contour)
{
    Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
    if(Region.Contours.empty()) return;
    spl_CurveToSnake(Region);

    // Process Holes
    spl_UInt ContourIndex;
    spl_UInt NContourIndex;
    spl_Point P,NP;
    spl_Point *p,*op,*np;
    spl_Point *c,*nc;
    double Dist,Distance,MinDistance;
    int PIndex,CIndex;
    spl_UInt count,ncount;
    spl_Point NPP;
    spl_UInt I,J;
    bool Found;
    spl_UInt nContoursCount = Region.Contours.size();

//    for(spl_UInt i=1;i<Region.Contours.size();i++)
    for(spl_UInt i=1;i<nContoursCount;i++)
    {
        // Find Best P,NP
//        ContourIndex=Region.Contours[i % nContoursCount].ContourInfo.GIndex;
        MinDistance=spl_MaxInt;
        Found=false;
        for(spl_UInt j=0;j<Region.Contours[i % nContoursCount].Points.size();j++)
        {
            P=Region.Contours[i % nContoursCount].Points[j];
            spl_GetPointProjection(P,NP);
            Distance=spl_PDistance(&P,&NP);
            if(Distance<=0.0) continue;
//            NContourIndex=spl_GetPixelContour(NP.x,NP.y);
//            if(ContourIndex==NContourIndex) continue;
            if(Distance<MinDistance)
            {
                MinDistance=Distance;
                I=i % nContoursCount;
                J=j;
                NPP=NP;
                Found=true;
                break;// 17.05.2004
            }
        }

        if(Found)
        {
            p=&Region.Contours[I].Points[J];
            c=p->pPrev;

            spl_FindNearestPoint(Region,NPP,true,CIndex,PIndex,Dist);
            ncount=Region.Contours[CIndex].Points.size();
            np=&Region.Contours[CIndex].Points[PIndex];
            nc=&Region.Contours[CIndex].Points[(PIndex+1) % ncount];

            np->pNext=p;

            c->pNext=nc;
        }
    }

    spl_Point *i0,*i;
    i0=&Region.Contours[0].Points[0];
    i=i0;
    int nIterationCount = 0;
    while(i->pNext!=i0)
    {
        Contour.Points.push_back(splPoint(i->x,i->y));
        i=i->pNext;

        nIterationCount++;
        if(nIterationCount >= spl_nMaxIterationCount)
        {
        	spl_bIsInvalidEmbroidery = true;
        	break;
        }
    }
}
*/
//---------------------------------------------------------------------------
// Region ZigZag-Tatami
//---------------------------------------------------------------------------
void spl_FillStitchs_ZigZag(spl_Point &p,spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath)
{
	if(spl_BestJump)
		spl_FillStitchs_ZigZag_Best_Jump(p,Region,GlobalStitchPath);
    else
		spl_FillStitchs_ZigZag_Best_Normal(p,Region,GlobalStitchPath);
}
//---------------------------------------------------------------------------
void spl_FillStitchs_ZigZag_Best_Normal(spl_Point &p,spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath)
{
	GlobalStitchPath.erase(GlobalStitchPath.begin(),GlobalStitchPath.end());
    if(Region.Contours.empty()) return;

    spl_Contour Contour;
    spl_Point P,NP,OP;
    spl_UInt I;
    spl_SerializeRegion(Region,Contour);
    if(Contour.Points.empty())  return;

    spl_GlobalStitch GlobalStitch;

    // Find Best Start Point (to jump to there)
    I = 0;
    P=Contour.Points[0];
    for(spl_UInt i=0;i<Contour.Points.size();i++)
    {
        P=Contour.Points[i];
        spl_GetPointProjection(P,NP);
        if(spl_PDistance(&P,&NP)*spl_DesignScale>=spl_MinStitchLength)
        {
/*
		    GlobalStitch.x=P.x;
		    GlobalStitch.y=P.y;
//            if(spl_ReplaceJump)
//			    GlobalStitch.type=spl_stNormal;
//            else
			    GlobalStitch.type=spl_stJump;
		    GlobalStitchPath.push_back(GlobalStitch);
*/
            I = i;
            break;
        }
    }

	spl_Contour Path;
    spl_Point pt;
    TPoint P0,P1,P2;
    if(GlobalStitchPath.size() > 0)
    {
	    GlobalStitch = GlobalStitchPath[GlobalStitchPath.size()-1];
	    P0.x = GlobalStitch.x;
    	P0.y = GlobalStitch.y;
    }
    else
	{
	    P0.x = int(p.x);
	    P0.y = int(p.y);
    }
    P1.x = int(P0.x);
    P1.y = int(P0.y);
    P2.x = int(P.x);
    P2.y = int(P.y);
    if(_pPathIndices->ppLines[P1.y][P1.x] != _PathColorIndex)
    {
		for(int i=0;i<8;i++)
        {
            if((P1.x+spl_T1[i].x>=0)&&(UINT(P1.x+spl_T1[i].x)<_pPathIndices->Width)&&(P1.y+spl_T1[i].y>=0)&&(UINT(P1.y+spl_T1[i].y)<_pPathIndices->Height))
            {
			    if(_pPathIndices->ppLines[P1.y+spl_T1[i].y][P1.x+spl_T1[i].x] == _PathColorIndex)
			    {
					P1.x = P1.x+spl_T1[i].x;
					P1.y = P1.y+spl_T1[i].y;
            		break;
	            }
            }
        }
    }
    if(_pPathIndices->ppLines[P2.y][P2.x] != _PathColorIndex)
    {
		for(int i=0;i<8;i++)
        {
            if((P2.x+spl_T1[i].x>=0)&&(UINT(P2.x+spl_T1[i].x)<_pPathIndices->Width)&&(P2.y+spl_T1[i].y>=0)&&(UINT(P2.y+spl_T1[i].y)<_pPathIndices->Height))
            {
			    if(_pPathIndices->ppLines[P2.y+spl_T1[i].y][P2.x+spl_T1[i].x] == _PathColorIndex)
			    {
					P2.x = P2.x+spl_T1[i].x;
					P2.y = P2.y+spl_T1[i].y;
            		break;
	            }
            }
        }
    }
	if(spl_FindPath(_pPathIndices,P1,P2,Path))
    {
    	for(spl_UInt i=0;i<Path.Points.size();i++)
        {
        	pt = Path.Points[i];
	    	GlobalStitch.x=pt.x;
	        GlobalStitch.y=pt.y;
	        GlobalStitch.type=spl_stNormal;
	        GlobalStitchPath.push_back(GlobalStitch);
        }
    }
    else
    {
    	GlobalStitch.x=P.x;
        GlobalStitch.y=P.y;
        GlobalStitch.type=spl_stJump;
        GlobalStitchPath.push_back(GlobalStitch);
    }

	OP = P;
    for(spl_UInt i=I;i<Contour.Points.size();i++)
    {
        P=Contour.Points[i];
        spl_GetPointProjection(P,NP);

        if(spl_PDistance(&P,&OP)*spl_DesignScale>=spl_MinStitchLength)
        {
	        GlobalStitch.x=P.x;
    	    GlobalStitch.y=P.y;
	        GlobalStitch.type=spl_stNormal;
	        GlobalStitchPath.push_back(GlobalStitch);
        }

        if(spl_PDistance(&P,&NP)*spl_DesignScale>=spl_MinStitchLength)
        {
    	    if(spl_PDistance(&P,&NP)*spl_DesignScale>=10.0)
	        {
        	    GlobalStitch.x=NP.x;
            	GlobalStitch.y=NP.y;
	            GlobalStitch.type=spl_stNormal;
    	        GlobalStitchPath.push_back(GlobalStitch);
            }
        }

		OP = P;
    }

    p.x=GlobalStitch.x;
    p.y=GlobalStitch.y;
}
//---------------------------------------------------------------------------
void spl_FillStitchs_ZigZag_Best_Jump(spl_Point &p,spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath)
{
	GlobalStitchPath.erase(GlobalStitchPath.begin(),GlobalStitchPath.end());
    if(Region.Contours.empty()) return;

    spl_Contour Contour;
    spl_Point P,NP,OP;
    spl_SerializeRegion(Region,Contour);
    if(Contour.Points.empty())  return;

    spl_GlobalStitch GlobalStitch;

    P = Contour.Points[0];
    GlobalStitch.x=P.x;
    GlobalStitch.y=P.y;
//    if(spl_ReplaceJump)
//    	GlobalStitch.type=spl_stNormal;
//    else
    	GlobalStitch.type=spl_stJump;
    GlobalStitchPath.push_back(GlobalStitch);

	OP = P;
    for(spl_UInt i=0;i<Contour.Points.size();i++)
    {
        P=Contour.Points[i];
        spl_GetPointProjection(P,NP);

        if(spl_PDistance(&P,&OP)*spl_DesignScale>=spl_MinStitchLength)
        {
	        GlobalStitch.x=P.x;
    	    GlobalStitch.y=P.y;
	        GlobalStitch.type=spl_stNormal;
	        GlobalStitchPath.push_back(GlobalStitch);
        }

        if(spl_PDistance(&P,&NP)*spl_DesignScale>=spl_MinStitchLength)
        {
            GlobalStitch.x=NP.x;
            GlobalStitch.y=NP.y;
            GlobalStitch.type=spl_stNormal;
            GlobalStitchPath.push_back(GlobalStitch);
        }

		OP = P;
    }

    p.x=GlobalStitch.x;
    p.y=GlobalStitch.y;
}
//---------------------------------------------------------------------------
// Region Run
//---------------------------------------------------------------------------
void spl_FillStitchs_Run(spl_Point &p,spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath)
{
    GlobalStitchPath.erase(GlobalStitchPath.begin(),GlobalStitchPath.end());
    if(Region.Contours.empty()) return;

    int PointIndex;
    spl_Point P;
    spl_GlobalStitch GlobalStitch;
    double Distance;
    int count;

    // Outter Contour
    PointIndex=0;

    spl_FindNearestPoint(Region.Contours[0],p,PointIndex,Distance);
    P=Region.Contours[0].Points[PointIndex];

    GlobalStitch.x=P.x;
    GlobalStitch.y=P.y;
    if(spl_PDistance(&p,&P)*spl_DesignScale>=spl_MinJumpLength)
    {
//    	if(spl_ReplaceJump)
//        	GlobalStitch.type=spl_stNormal;
//        else
        	GlobalStitch.type=spl_stJump;
    }
    else
        GlobalStitch.type=spl_stNormal;
    GlobalStitchPath.push_back(GlobalStitch);

    count=Region.Contours[0].Points.size();
    for(int i=0+PointIndex;i<count+PointIndex;i++)
    {
        P=Region.Contours[0].Points[i % count];

        GlobalStitch.x=P.x;
        GlobalStitch.y=P.y;
        GlobalStitch.type=spl_stNormal;
        GlobalStitchPath.push_back(GlobalStitch);
    }

    p.x=GlobalStitch.x;
    p.y=GlobalStitch.y;
}
//---------------------------------------------------------------------------
// Region Satin
//---------------------------------------------------------------------------
void spl_FillStitchs_Satin(double SatinHeight,spl_Point &p,spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath)
{
    GlobalStitchPath.erase(GlobalStitchPath.begin(),GlobalStitchPath.end());
    if(Region.Contours.empty()) return;

    int PointIndex;
    spl_Point P,P1,P2,P3;
    spl_GlobalStitch GlobalStitch;
    double Distance;
    int count;

    // Outter Contour
    PointIndex=0;

    spl_FindNearestPoint(Region.Contours[0],p,PointIndex,Distance);
    P=Region.Contours[0].Points[PointIndex];

    GlobalStitch.x=P.x;
    GlobalStitch.y=P.y;
    if(spl_PDistance(&p,&P)*spl_DesignScale>=spl_MinJumpLength)
    {
//    	if(spl_ReplaceJump)
//        	GlobalStitch.type=spl_stNormal;
//        else
        	GlobalStitch.type=spl_stJump;
    }
    else
        GlobalStitch.type=spl_stNormal;
    GlobalStitchPath.push_back(GlobalStitch);

    count=Region.Contours[0].Points.size();
    if(count<3) return;
    double Sign=1.0;
    P1=Region.Contours[0].Points[(0+PointIndex) % count];
    P2=Region.Contours[0].Points[(1+PointIndex) % count];
    for(int i=2+PointIndex;i<count+2+PointIndex;i++)
    {
        P3=Region.Contours[0].Points[i % count];
        spl_GetSkeletonPoint(Sign*SatinHeight,spl_PI/4.0,&P1,&P2,&P3,&P);
        Sign*=-1.0;

        GlobalStitch.x=P.x;
        GlobalStitch.y=P.y;
        GlobalStitch.type=spl_stNormal;
        GlobalStitchPath.push_back(GlobalStitch);

        P1=P2;
        P2=P3;
    }

    p.x=GlobalStitch.x;
    p.y=GlobalStitch.y;
}
//---------------------------------------------------------------------------
// MultiLayer
//---------------------------------------------------------------------------
void spl_FillStitchs_EMB(spl_Image *pIndices,spl_MultiLayer &iMultiLayer,spl_StitchPath &StitchPath,spl_EmbHeader &EmbHeader)
{
    spl_bIsInvalidEmbroidery = false;
    StitchPath.erase(StitchPath.begin(),StitchPath.end());

    spl_Point P;
    spl_GlobalStitch GlobalStitch;
    spl_GlobalStitchPath TempGlobalStitchPath;
    spl_Stitch Stitch;
    double Distance;
    spl_Image *pTemp=new spl_Image();
    pTemp->Assign(pIndices);
    _pIndices=pTemp;
    spl_Image *pPathTemp=new spl_Image();
    pPathTemp->Assign(pIndices);
    _pPathIndices=pPathTemp;
    spl_Region Region;

    int RegionIndex;
    int ContourIndex;
    int PointIndex;
    int Index;
    spl_Point p,op;
    spl_EmbParameters EmbParameters;
    spl_MultiLayer MultiLayer=iMultiLayer;
    bool EmptyLayer;
    spl_Region PrevRegion;
    spl_Layer PrevLayer; 
    int nRegIndex = 0;
    bool bLayerMethode = false;

    spl_Rect Frame;
    Frame=spl_ComputeFrame(MultiLayer);
    spl_Point Center;
    Center.x=Frame.left+Frame.Width()/2.0;
    Center.y=Frame.top+Frame.Height()/2.0;

    strcpy(EmbHeader.Comments,spl_Comments);
    EmbHeader.StitchsCount=0;
    EmbHeader.NormalStitchs=0;
    EmbHeader.JumpStitchs=0;
    EmbHeader.ColorStitchs=0;

    int IterationNo = 1;

    // Draw All Layers
    spl_FlushImage(_pPathIndices,spl_BackgroundIndex);
    _PathColorIndex = spl_ColorsCount;

    HBRUSH hNewBrush,hOldBrush;
    HPEN hNewPen,hOldPen;
    DWORD Col= RGB(_PathColorIndex,_PathColorIndex,_PathColorIndex);
    HDC hdc = _pPathIndices->pBitmap->Canvas->Handle;

    hNewBrush=CreateSolidBrush(Col);
    hOldBrush=SelectObject(hdc,hNewBrush);

    hNewPen=CreatePen(PS_SOLID,1,Col);
    hOldPen=SelectObject(hdc,hNewPen);

    spl_DrawMultiLayer(_pPathIndices->pBitmap->Canvas->Handle,MultiLayer,false);

    SelectObject(hdc,hOldBrush);
    DeleteObject(hNewBrush);

    SelectObject(hdc,hOldPen);
    DeleteObject(hNewPen);
//    _pPathIndices->pBitmap->SaveToFile("c:\\test\\Image.bmp");


    // MultiLayer
    p=splPoint(0,0);
    op=p;
    // Layer
    for(spl_UInt LayerIndex=0;LayerIndex<MultiLayer.Layers.size();LayerIndex++)
    {
    	#ifdef _EMB_TRACE_
        FormMain->AddMessage("Processing "+FormatFloat("Layer 000",IterationNo)+"...");
        #endif // _EMB_TRACE_

        RegionIndex=0;
        ContourIndex=0;
        PointIndex=0;

        if(MultiLayer.Layers[LayerIndex].Regions.empty())	continue;

        spl_FlushImage(_pIndices,spl_BackgroundIndex);
        _Color=MultiLayer.Layers[LayerIndex].Regions[RegionIndex].FillColor;
        _NegColor = RGB(255-GetRValue(_Color),255-GetGValue(_Color),255-GetBValue(_Color));
        if(EmbHeader.ColorStitchs<spl_MaxColorsCount-1)
        {
            EmbHeader.Colors[EmbHeader.ColorStitchs].r=GetRValue(_Color);
            EmbHeader.Colors[EmbHeader.ColorStitchs].g=GetGValue(_Color);
            EmbHeader.Colors[EmbHeader.ColorStitchs].b=GetBValue(_Color);
            EmbHeader.ColorStitchs++;
        }
        EmptyLayer=true;
        PrevLayer = MultiLayer.Layers[LayerIndex];

        // Region
        while(!MultiLayer.Layers[LayerIndex].Regions.empty())
        {
            RegionIndex=0;
            ContourIndex=0;
            PointIndex=0;
            spl_FindNearestPoint(MultiLayer.Layers[LayerIndex],p,RegionIndex,ContourIndex,PointIndex,Distance);

            if(!bLayerMethode)
	            PrevRegion = MultiLayer.Layers[LayerIndex].Regions[RegionIndex];

            // Embroidery Parameters
            if(!spl_GlobalCurves[MultiLayer.Layers[LayerIndex].Regions[RegionIndex].Contours[0].ContourInfo.GIndex].CurveInfo.UseGlobalParameters)
            {
                EmbParameters=spl_GlobalCurves[MultiLayer.Layers[LayerIndex].Regions[RegionIndex].Contours[0].ContourInfo.GIndex].CurveInfo.EmbParameters;
                spl_FillStitchDensity=EmbParameters.FillStitchDensity;
                spl_LineStitchDensity=EmbParameters.LineStitchDensity;
                spl_RunStitchStep=EmbParameters.RunStitchStep;
                spl_SatinHeight=EmbParameters.SatinHeight;

                spl_FillStitchingOutput=EmbParameters.FillStitchingOutput;
                spl_LineStitchingOutput=EmbParameters.LineStitchingOutput;
                spl_StitchMargin=EmbParameters.StitchMargin;

                spl_Global_Dir=EmbParameters.Dir;
                spl_Global_StartDir=EmbParameters.StartDir;

                spl_AdjustFillStitchs = EmbParameters.AdjustFillStitchs;
                spl_AdjustLineStitchs = EmbParameters.AdjustLineStitchs;
            }
            else
            {
                spl_FillStitchDensity=spl_Global_EmbParameters.FillStitchDensity;
                spl_LineStitchDensity=spl_Global_EmbParameters.LineStitchDensity;
                spl_RunStitchStep=spl_Global_EmbParameters.RunStitchStep;
                spl_SatinHeight=spl_Global_EmbParameters.SatinHeight;

                spl_FillStitchingOutput=spl_Global_EmbParameters.FillStitchingOutput;
                spl_LineStitchingOutput=spl_Global_EmbParameters.LineStitchingOutput;
                spl_StitchMargin=spl_Global_EmbParameters.StitchMargin;

                spl_Global_Dir=spl_Global_EmbParameters.Dir;
                spl_Global_StartDir=spl_Global_EmbParameters.StartDir;

                spl_AdjustFillStitchs = spl_Global_EmbParameters.AdjustFillStitchs;
                spl_AdjustLineStitchs = spl_Global_EmbParameters.AdjustLineStitchs;
            }
            spl_Global_k=splPoint(spl_K1[spl_Global_Dir].x,spl_K1[spl_Global_Dir].y);
            spl_Global_n=splPoint(spl_Global_k.x,-spl_Global_k.y);

            // Embroid Region
            spl_PrepareCurve(1.0,MultiLayer.Layers[LayerIndex].Regions[RegionIndex]);
            if(MultiLayer.Layers[LayerIndex].Regions[RegionIndex].Contours[0].ContourInfo.ProcessFill)
            {
                switch(spl_FillStitchingOutput)
                {
                    case spl_soZigZag:
                    {
//                        spl_DivideCurveByDirection(MultiLayer.Layers[LayerIndex].Regions[RegionIndex],spl_FillStitchDensity/spl_DesignScale,Region);
//                        spl_DrawPolygonRegion(_pIndices->pBitmap->Canvas->Handle,Region,false);
						spl_DivideBezierCurveByDirection(MultiLayer.Layers[LayerIndex].Regions[RegionIndex],spl_FillStitchDensity/spl_DesignScale,0.01,Region);
						spl_DrawRegionForProcessing(_pIndices->pBitmap->Canvas->Handle,MultiLayer.Layers[LayerIndex].Regions[RegionIndex],true,TColor(_Color),TColor(_Color),2,TColor(_NegColor),TColor(_Color),2);
                        if(Region.Contours.empty())
                        {
							if(!bLayerMethode)
                            {
					    	    // Draw Previous Region
						        spl_DrawRegion(_pPathIndices->pBitmap->Canvas->Handle,PrevRegion,true);
//                                _pPathIndices->pBitmap->SaveToFile("c:\\test\\"+FormatFloat("Region0000",nRegIndex)+".bmp");
	                            nRegIndex++;
                            }

                            // Erase Embroided Region
                            MultiLayer.Layers[LayerIndex].Regions.erase(&MultiLayer.Layers[LayerIndex].Regions[RegionIndex]);
                            continue;
                        }
                        _ColorIndex=spl_GlobalCurves[Region.Contours[0].ContourInfo.GIndex].FillColorIndex;
                        spl_FillStitchs_ZigZag(p,Region,TempGlobalStitchPath);
                        if(!TempGlobalStitchPath.empty())   EmptyLayer=false;
                        break;
                    }
                    case spl_soTatami:
                    {
//                        spl_DivideCurveByDirection(MultiLayer.Layers[LayerIndex].Regions[RegionIndex],spl_FillStitchDensity/spl_DesignScale,Region);
//                        spl_DrawPolygonRegion(_pIndices->pBitmap->Canvas->Handle,Region,false);
						spl_DivideBezierCurveByDirection(MultiLayer.Layers[LayerIndex].Regions[RegionIndex],spl_FillStitchDensity/spl_DesignScale,0.01,Region);
						spl_DrawRegionForProcessing(_pIndices->pBitmap->Canvas->Handle,MultiLayer.Layers[LayerIndex].Regions[RegionIndex],true,TColor(_Color),TColor(_Color),2,TColor(_NegColor),TColor(_Color),2);
                        if(Region.Contours.empty())
                        {
				    	    // Draw Previous Region
							if(!bLayerMethode)
                            {
						        spl_DrawRegion(_pPathIndices->pBitmap->Canvas->Handle,PrevRegion,true);
//						        _pPathIndices->pBitmap->SaveToFile("c:\\test\\"+FormatFloat("Region0000",nRegIndex)+".bmp");
        	                    nRegIndex++;
                            }

                            // Erase Embroided Region
                            MultiLayer.Layers[LayerIndex].Regions.erase(&MultiLayer.Layers[LayerIndex].Regions[RegionIndex]);
                            continue;
                        }
                        _ColorIndex=spl_GlobalCurves[Region.Contours[0].ContourInfo.GIndex].FillColorIndex;
                        spl_FillStitchs_ZigZag(p,Region,TempGlobalStitchPath);
                        spl_GlobalStitchPath oGlobalStitchPath;
                        spl_MakeTatami(TempGlobalStitchPath,oGlobalStitchPath);
                        TempGlobalStitchPath=oGlobalStitchPath;
                        if(!TempGlobalStitchPath.empty())   EmptyLayer=false;
                        break;
                    }
                }
                if(spl_DesignCentered)  spl_CenterStithcs(Frame,TempGlobalStitchPath);
                spl_ScaleStithcs(spl_DesignScale,TempGlobalStitchPath);
                spl_AdjustStitchs(spl_AdjustFillStitchs,op,TempGlobalStitchPath,StitchPath);
            }


            if(MultiLayer.Layers[LayerIndex].Regions[RegionIndex].Contours[0].ContourInfo.ProcessLine)
            {
                switch(spl_LineStitchingOutput)
                {
                    case spl_soRun:
                    {
                        spl_ScaleCurve(spl_DesignScale,MultiLayer.Layers[LayerIndex].Regions[RegionIndex]);
//                        spl_DivideCurveByLength(MultiLayer.Layers[LayerIndex].Regions[RegionIndex],spl_LineStitchDensity/spl_DesignScale,Region);
                        spl_DivideBezierCurve(MultiLayer.Layers[LayerIndex].Regions[RegionIndex],spl_LineStitchDensity/spl_DesignScale,spl_LineStitchDensity/spl_DesignScale,Region);
                        spl_PrepareCurve(spl_LineStitchDensity/spl_DesignScale,Region);
                        if(Region.Contours.empty())
                        {
							if(!bLayerMethode)
                            {
					    	    // Draw Previous Region
						        spl_DrawRegion(_pPathIndices->pBitmap->Canvas->Handle,PrevRegion,true);
//						        _pPathIndices->pBitmap->SaveToFile("c:\\test\\"+FormatFloat("Region0000",nRegIndex)+".bmp");
            	                nRegIndex++;
                            }

                            // Erase Embroided Region
                            MultiLayer.Layers[LayerIndex].Regions.erase(&MultiLayer.Layers[LayerIndex].Regions[RegionIndex]);
                            continue;
                        }
                        spl_FillStitchs_Run(p,Region,TempGlobalStitchPath);
                        spl_ScaleStithcs(1.0/spl_DesignScale,TempGlobalStitchPath);
                        if(!TempGlobalStitchPath.empty())   EmptyLayer=false;
                        break;
                    }
                    case spl_soSatin:
                    {
                        spl_ScaleCurve(spl_DesignScale,MultiLayer.Layers[LayerIndex].Regions[RegionIndex]);
//                        spl_DivideCurveByLength(MultiLayer.Layers[LayerIndex].Regions[RegionIndex],spl_LineStitchDensity/spl_DesignScale,Region);
                        spl_DivideBezierCurve(MultiLayer.Layers[LayerIndex].Regions[RegionIndex],spl_LineStitchDensity/spl_DesignScale,spl_LineStitchDensity/spl_DesignScale,Region);
                        spl_PrepareCurve(spl_LineStitchDensity/spl_DesignScale,Region);
                        if(Region.Contours.empty())
                        {
							if(!bLayerMethode)
                            {
					    	    // Draw Previous Region
						        spl_DrawRegion(_pPathIndices->pBitmap->Canvas->Handle,PrevRegion,true);
//						        _pPathIndices->pBitmap->SaveToFile("c:\\test\\"+FormatFloat("Region0000",nRegIndex)+".bmp");
            	                nRegIndex++;
                            }

                            // Erase Embroided Region
                            MultiLayer.Layers[LayerIndex].Regions.erase(&MultiLayer.Layers[LayerIndex].Regions[RegionIndex]);
                            continue;
                        }
                        spl_FillStitchs_Satin(spl_SatinHeight,p,Region,TempGlobalStitchPath);
                        spl_ScaleStithcs(1.0/spl_DesignScale,TempGlobalStitchPath);
                        if(!TempGlobalStitchPath.empty())   EmptyLayer=false;
                        break;
                    }
                }
                if(spl_DesignCentered)  spl_CenterStithcs(Frame,TempGlobalStitchPath);
                spl_ScaleStithcs(spl_DesignScale,TempGlobalStitchPath);
                spl_AdjustStitchs(spl_AdjustLineStitchs,op,TempGlobalStitchPath,StitchPath);
            }

            if(!bLayerMethode)
            {
    	    	// Draw Previous Region
		        spl_DrawRegion(_pPathIndices->pBitmap->Canvas->Handle,PrevRegion,true);
//	            _pPathIndices->pBitmap->SaveToFile("c:\\test\\"+FormatFloat("Region0000",nRegIndex)+".bmp");
    	        nRegIndex++;
            }

            // Erase Embroided Region
            MultiLayer.Layers[LayerIndex].Regions.erase(&MultiLayer.Layers[LayerIndex].Regions[RegionIndex]);
        }

        if(bLayerMethode)
        {
	        // Draw Previous Layer
    	    spl_DrawLayer(_pPathIndices->pBitmap->Canvas->Handle,PrevLayer,true);
//        	_pPathIndices->pBitmap->SaveToFile("c:\\test\\"+FormatFloat("Layer00",LayerIndex)+".bmp");
        }

        // Change Color
        if((!EmptyLayer)&&(!StitchPath.empty()))
        {
            Stitch.x=0;
            Stitch.y=0;
            Stitch.type=spl_stColorChanged;
            StitchPath.push_back(Stitch);

//            GlobalStitch.x=p.x;
//            GlobalStitch.y=p.y;
//	        GlobalStitch.type=spl_stColorChanged;
//    	    TempGlobalStitchPath.push_back(GlobalStitch);
        }

        IterationNo++;
    }

    // Replace Last Color Changed By Jump
    int n=StitchPath.size();
    if(n>0) StitchPath[n-1].type=spl_stJump;

    // Move To Start Point
    if(spl_ReturnToStartPoint)
    {
        TempGlobalStitchPath.erase(TempGlobalStitchPath.begin(),TempGlobalStitchPath.end());
        if(spl_DesignCentered)
        {
            GlobalStitch.x=Center.x;
            GlobalStitch.y=Center.y;
        }
        else
        {
            GlobalStitch.x=0;
            GlobalStitch.y=0;
        }
        GlobalStitch.type=spl_stJump;
        TempGlobalStitchPath.push_back(GlobalStitch);
        if(spl_DesignCentered)  spl_CenterStithcs(Frame,TempGlobalStitchPath);
        spl_ScaleStithcs(spl_DesignScale,TempGlobalStitchPath);
        spl_AdjustStitchs(false,op,TempGlobalStitchPath,StitchPath);
    }

//    if(spl_DesignCentered)  spl_CenterStithcs(Frame,TempGlobalStitchPath);
//    spl_ScaleStithcs(spl_DesignScale,TempGlobalStitchPath);
//    op = splPoint(0,0);
//	spl_AdjustStitchs(spl_AdjustFillStitchs,op,TempGlobalStitchPath,StitchPath);

    // EOF
    Stitch.x=0;
    Stitch.y=0;
    Stitch.type=spl_stNormal;
    StitchPath.push_back(Stitch);

    Stitch.x=0;
    Stitch.y=0;
    Stitch.type=spl_stJump;
    StitchPath.push_back(Stitch);

    Stitch.x=0;
    Stitch.y=0;
    Stitch.type=spl_stEof;
    StitchPath.push_back(Stitch);

    if(pTemp)   delete pTemp;pTemp=NULL;
    if(pPathTemp)	delete pPathTemp;pPathTemp = NULL;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool EmbroidQuad(bool bMin,double Step,spl_Point *P1,spl_Point *P2,spl_Point *P3,spl_Point *P4,spl_Contour &Result)
{
 if(Step<=0.0) return false;
 // Be Attension To The Order Of Vertexs
 spl_Point p;
 double L1=spl_PDistance(P1,P2);
 double L2=spl_PDistance(P3,P4);
 double L;
 if(bMin)
	L=min(L1,L2);
 else
 	L=max(L1,L2);
 double NStep;
 double r;
 int N1,N2,n;

 if(L<=0.0f)
 {
  NStep=Step;
 }
 else
 {
  if(L<=Step)
   NStep=L;
  else
  {
   n=L/Step;
   r=L-n*Step;
   NStep=Step+r/float(n);
//   NStep=Step-(Step-r)/float(n+1);
  }
 }

 N2=L/NStep;
 if(N2<=0)
 {
    Result.Points.push_back(*P1);
    Result.Points.push_back(*P3);
    return true;
 }
 N1=N2;

 if(L1>=L2)
 {
  for(float i=0;i<=N1;i++)
  {
    p.x=(1.0f-(i/float(N1)))*P1->x+(i/float(N1))*P2->x;
    p.y=(1.0f-(i/float(N1)))*P1->y+(i/float(N1))*P2->y;
    Result.Points.push_back(p);

    p.x=(1.0f-(i/float(N2)))*P3->x+(i/float(N2))*P4->x;
    p.y=(1.0f-(i/float(N2)))*P3->y+(i/float(N2))*P4->y;
    Result.Points.push_back(p);
  }

    Result.Points.push_back(*P2);
 }
 else
 {
  for(int i=0;i<=N1;i++)
  {
    p.x=(1.0f-(i/float(N2)))*P1->x+(i/float(N2))*P2->x;
    p.y=(1.0f-(i/float(N2)))*P1->y+(i/float(N2))*P2->y;
    Result.Points.push_back(p);

    p.x=(1.0f-(i/float(N1)))*P3->x+(i/float(N1))*P4->x;
    p.y=(1.0f-(i/float(N1)))*P3->y+(i/float(N1))*P4->y;
    Result.Points.push_back(p);
  }

    Result.Points.push_back(*P4);
 }
 return true;
}
//---------------------------------------------------------------------------
static spl_Point _K;
int __fastcall SortFunc(void *Item1,void *Item2)
{
    return spl_Compare((spl_Point *)Item1,(spl_Point *)Item2,&_K);
}
//---------------------------------------------------------------------------
void SortQuad(spl_Point *P1,spl_Point *P2,spl_Point *P3,spl_Point *P4,spl_Point *K,spl_Point *pOut)
{
    _K=*K;
    TList *pList=new TList();
    pList->Add(P1);
    pList->Add(P2);
    pList->Add(P3);
    pList->Add(P4);
    pList->Sort(SortFunc);
    for(int i=0;i<4;i++)
    {
        pOut[i]=*((spl_Point *)pList->Items[i]);
    }

    if(pList)   delete pList;
}
//---------------------------------------------------------------------------
void EmbroidQuadric(bool bMin,double Step,spl_Point *P1,spl_Point *P2,spl_Point *P3,spl_Point *P4,spl_Contour &Result)
{
 if(Step<=0.0) return;
 // Be Attension To The Order Of Vertexs
 spl_Point First[4];
 spl_Point Second[4];
 spl_Point *p,*p1,*p2,*p3,*p4,K;
 spl_Point A,B,C,D;
 double L;
 spl_GlobalStitch GlobalStitch;

 spl_PVector(P1,P2,&K);
 spl_PNormalizeVector(&K,L);
 if(L<=0.0)
 {
  spl_PVector(P3,P4,&K);
  spl_PNormalizeVector(&K,L);
 }
 if(L<=0.0f)
 {
    Result.Points.push_back(*P1);
    Result.Points.push_back(*P3);
    return;
 }

 if(!spl_ProjectionSegment(P1,P2,P3,&A))
  A=*P3;
 if(!spl_ProjectionSegment(P1,P2,P4,&B))
  B=*P4;
 if(!spl_ProjectionSegment(P3,P4,P1,&C))
  C=*P1;
 if(!spl_ProjectionSegment(P3,P4,P2,&D))
  D=*P2;

 SortQuad(P1,P2,&A,&B,&K,First);
 SortQuad(P3,P4,&C,&D,&K,Second);

 p1=&First[0];
 p3=&Second[0];
 for(int i=1;i<4;i++)
 {
  p2=&First[i];
  p4=&Second[i];
  EmbroidQuad(bMin,Step,p1,p2,p3,p4,Result);
  p1=p2;
  p3=p4;
 }
}
//---------------------------------------------------------------------------
void spl_EmbroidContour(bool bMin,double ExtrudeDistance,double Density,bool Default,spl_Contour &Contour,spl_Contour &Result)
{
    Result.Points.erase(Result.Points.begin(),Result.Points.end());
    if(Contour.Points.empty())  return;
    spl_Contour Extrude;
    spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);

    spl_Point P1,P2,P3,P4;
    spl_UInt count=Contour.Points.size();

    P1=Contour.Points[0];
    P3=Extrude.Points[0];
    for(spl_UInt i=1;i<=count;i++)
    {
        P2=Contour.Points[i % count];
        P4=Extrude.Points[i % count];
        if(Default)
            EmbroidQuadric(bMin,Density,&P1,&P2,&P3,&P4,Result);
        else
            EmbroidQuad(bMin,Density,&P1,&P2,&P3,&P4,Result);
        P1=P2;
        P3=P4;
    }
}
//---------------------------------------------------------------------------
void spl_EmbroidContourByParallel(double ExtrudeDistance,spl_Contour &Contour,spl_Contour &Result)
{
    Result.Points.erase(Result.Points.begin(),Result.Points.end());
    if(Contour.Points.empty())  return;
    spl_Contour Extrude;
    spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);

    spl_Point P1,P2;
    spl_UInt count=Contour.Points.size();

    for(spl_UInt i=0;i<count;i++)
    {
        P1=Contour.Points[i % count];
        P2=Extrude.Points[i % count];
	    Result.Points.push_back(P1);
	    Result.Points.push_back(P2);
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
void spl_EmbroidRegion(spl_Region &Region,HRGN hRgn,spl_GlobalStitchPath &GlobalStitchPath)
{
	GlobalStitchPath.clear();
	spl_Point OP,P,K,p,np,_K;
    spl_GlobalStitch GlobalStitch;
    double L;
    double s,dStep = 1.0;
    double a,b,dy,dx;
    _K.x = cos(spl_PI/4.0);
    _K.y = sin(spl_PI/4.0);

	for(UINT i=0;i<Region.Contours.size();i++)
    {
    	if(Region.Contours[i].Points.empty())	continue;
    	OP = Region.Contours[i].Points[0];
     	for(UINT j=1;j<Region.Contours[i].Points.size();j++)
        {
        	P = Region.Contours[i].Points[j];
            dx = P.x - OP.x;
            dy = P.y - OP.y;
            if(dy == 0.0)
            {
                continue;
            }
            a = dy/dx;
            b = OP.y - a * OP.x;
            if(dx >= dy)
            {
                for(int x=OP.x;x<=P.x;x++)
                {
                    p.x = x;
                    p.y = a*x+b;
                    np = p;
                    s = 0.0;
                    #ifdef spl_Stitch_Curve_
                    FormMain->Image->Canvas->Pixels[spl_Round(np.x)][spl_Round(np.y)] = clBlue;
                    Application->ProcessMessages();
                    #endif// spl_Stitch_Curve_
                    while(PtInRegion(hRgn,spl_Round(np.x),spl_Round(np.y)))
                    {
                        np.x = p.x+s*_K.x;
                        np.y = p.y+s*_K.y;
                        s += 1.0;

                        #ifdef spl_Stitch_Curve_
                    	FormMain->Image->Canvas->Pixels[spl_Round(np.x)][spl_Round(np.y)] = clBlue;
                        Application->ProcessMessages();
                        #endif// spl_Stitch_Curve_
                    }
                    GlobalStitch.x = p.x;
                    GlobalStitch.y = p.y;
                    GlobalStitch.type = spl_stNormal;
                    GlobalStitchPath.push_back(GlobalStitch);
                    GlobalStitch.x = np.x;
                    GlobalStitch.y = np.y;
                    GlobalStitch.type = spl_stNormal;
                    GlobalStitchPath.push_back(GlobalStitch);
                }
            }
            else
            {
            	if(a == 0.0)	continue;
                for(int y=OP.y;y<=P.y;y++)
                {
                    p.x = (y-b)/a;
                    p.y = y;
                    np = p;
                    s = 0.0;
                    #ifdef spl_Stitch_Curve_
                    FormMain->Image->Canvas->Pixels[spl_Round(np.x)][spl_Round(np.y)] = clBlue;
                    Application->ProcessMessages();
                    #endif// spl_Stitch_Curve_
                    while(PtInRegion(hRgn,spl_Round(np.x),spl_Round(np.y)))
                    {
                        np.x = p.x+s*_K.x;
                        np.y = p.y+s*_K.y;
                        s += 1.0;

                        #ifdef spl_Stitch_Curve_
                        FormMain->Image->Canvas->Pixels[spl_Round(np.x)][spl_Round(np.y)] = clBlue;
                        Application->ProcessMessages();
                        #endif// spl_Stitch_Curve_
                    }
                    GlobalStitch.x = p.x;
                    GlobalStitch.y = p.y;
                    GlobalStitch.type = spl_stNormal;
                    GlobalStitchPath.push_back(GlobalStitch);
                    GlobalStitch.x = np.x;
                    GlobalStitch.y = np.y;
                    GlobalStitch.type = spl_stNormal;
                    GlobalStitchPath.push_back(GlobalStitch);
                }
            }
            OP = P;
        }
    }
}
*/
//---------------------------------------------------------------------------
/*
void spl_EmbroidRegion(spl_Region &Region,HRGN hRgn,spl_GlobalStitchPath &GlobalStitchPath)
{
	GlobalStitchPath.clear();
	spl_Point OP,P,K,p,np,_K;
    spl_GlobalStitch GlobalStitch;
    double L;
    double s,dStep = 1.0;
    _K.x = cos(spl_PI/4.0);
    _K.y = sin(spl_PI/4.0);

	for(UINT i=0;i<Region.Contours.size();i++)
    {
    	if(Region.Contours[i].Points.empty())	continue;
    	OP = Region.Contours[i].Points[0];
     	for(UINT j=1;j<Region.Contours[i].Points.size();j++)
        {
        	P = Region.Contours[i].Points[j];
            L = spl_PDistance(&OP,&P);
			if(L < dStep)	continue;
			K.x = (P.x - OP.x)/L;
			K.y = (P.y - OP.y)/L;
			for(double t=0.0;t<=L;t+=dStep)
            {
				p.x = OP.x+t*K.x;
				p.y = OP.y+t*K.y;
                np = p;
                s = 0.0;
                    #ifdef spl_Stitch_Curve_
                    FormMain->Image->Canvas->Pixels[spl_Round(np.x)][spl_Round(np.y)] = clBlue;
                    Application->ProcessMessages();
                    #endif// spl_Stitch_Curve_
                while(PtInRegion(hRgn,spl_Round(np.x),spl_Round(np.y)))
                {
                 	np.x = p.x+s*_K.x;
                 	np.y = p.y+s*_K.y;
                    s += 1.0;

                    #ifdef spl_Stitch_Curve_
//                    FormMain->Image->Canvas->Pixels[spl_Round(np.x)][spl_Round(np.y)] = clBlue;
//                    Application->ProcessMessages();
//                    break;
                    #endif// spl_Stitch_Curve_
                }
                GlobalStitch.x = p.x;
                GlobalStitch.y = p.y;
                GlobalStitch.type = spl_stNormal;
                GlobalStitchPath.push_back(GlobalStitch);
                GlobalStitch.x = np.x;
                GlobalStitch.y = np.y;
                GlobalStitch.type = spl_stNormal;
                GlobalStitchPath.push_back(GlobalStitch);
            }
            OP = P;
        }
    }
}
*/
//---------------------------------------------------------------------------
void spl_EmbroidRegion(spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath)
{
	GlobalStitchPath.clear();
	spl_Point op,OP,P,K,p,np,_K;
    spl_GlobalStitch GlobalStitch;
    double L;
    double s;//,dStep = 5.0;
//    double dStepCount,dInteger,dFraction;
//    double dDistance;
//    double ss;
    int nStepCount;
    int nStep = 5,step;
    bool bFound;
    spl_Rect Frame = spl_ComputeFrame(Region);
    spl_Point _p0 = splPoint(Frame.left,Frame.bottom);
    _K.x = cos(spl_PI/4.0);
    _K.y = sin(spl_PI/4.0);
    step = 0;
	for(UINT i=0;i<Region.Contours.size();i++)
    {
    	if(Region.Contours[i].Points.empty())	continue;
/*
        if(spl_FindPath(_pPathIndices,P1,P2,Path))
        {
            for(spl_UInt i=0;i<Path.Points.size();i++)
            {
                pt = Path.Points[i];
                GlobalStitch.x=pt.x;
                GlobalStitch.y=pt.y;
                GlobalStitch.type=spl_stNormal;
                GlobalStitchPath.push_back(GlobalStitch);
            }
        }
        else
        {
            GlobalStitch.x=P.x;
            GlobalStitch.y=P.y;
            GlobalStitch.type=spl_stJump;
            GlobalStitchPath.push_back(GlobalStitch);
        }
*/
    	OP = Region.Contours[i].Points[0];
        op = OP;
     	for(UINT j=1;j<Region.Contours[i].Points.size();j++)
        {
        	P = Region.Contours[i].Points[j];
            L = spl_PDistance(&OP,&P);
			if(L <= 0.0)	continue;
			K.x = (P.x - OP.x)/L;
			K.y = (P.y - OP.y)/L;
//            ss = 0.0;
			for(double t=0.0;t<=L;t+=1.0)
            {
                step++;
                if(step >= nStep)
                {
                 	step = 0;
                }
                else
                {
                 	continue;
                }

				p.x = OP.x+t*K.x;
				p.y = OP.y+t*K.y;


//				dDistance = spl_Distance(&p,&_p0,&_K);
//                nStepCount = int(dDistance/dStep);
//				if(spl_ABS(dDistance - nStepCount*dStep) >= 1.0)	continue;

//				ss += spl_PDistance(&op,&p);
//				if(ss >= dStep)
//                 	ss = 0.0;
//                else
//                	continue;

                if(i == 0)// Outter Contour
	                s = 1.0;
                else
	                s = 1.0;
                np.x = p.x+s*_K.x;
                np.y = p.y+s*_K.y;
                #ifdef spl_Stitch_Curve_
//                FormMain->Image->Canvas->Pixels[spl_Round(np.x)][spl_Round(np.y)] = clBlue;
//                Application->ProcessMessages();
                #endif// spl_Stitch_Curve_
                bFound = false;
                while(spl_PointInRegion(Region,np))
                {
                 	np.x = p.x+s*_K.x;
                 	np.y = p.y+s*_K.y;
                    s += 1.0;
                    bFound = true;

                    #ifdef spl_Stitch_Curve_
//                    FormMain->Image->Canvas->Pixels[spl_Round(np.x)][spl_Round(np.y)] = clBlue;
//                    Application->ProcessMessages();
//                    break;
                    #endif// spl_Stitch_Curve_
                }
                if(bFound)
                {
                    s -= 1.0;
                 	np.x = p.x+s*_K.x;
                 	np.y = p.y+s*_K.y;
                }

                GlobalStitch.x = p.x;
                GlobalStitch.y = p.y;
                GlobalStitch.type = spl_stNormal;
                GlobalStitchPath.push_back(GlobalStitch);
                GlobalStitch.x = np.x;
                GlobalStitch.y = np.y;
                GlobalStitch.type = spl_stNormal;
                GlobalStitchPath.push_back(GlobalStitch);
                op = p;
            }
            OP = P;
        }
    }
}
//---------------------------------------------------------------------------
/*
void spl_EmbroidRegion(spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath)
{
	spl_Point P;
	int nPointsCount = 0;
    int nPolygonsCount = Region.Contours.size();
    int *pPolygonsCounts = new int[nPolygonsCount];
	int k = 0;
	for(UINT i=0;i<Region.Contours.size();i++)
    {
        pPolygonsCounts[k] = Region.Contours[i].Points.size();
    	nPointsCount += pPolygonsCounts[k];
        k++;
    }
    TPoint *pPoints = new TPoint[nPointsCount];
	k = 0;
	for(UINT i=0;i<Region.Contours.size();i++)
    {
     	for(UINT j=0;j<Region.Contours[i].Points.size();j++)
        {
        	P = Region.Contours[i].Points[j];
			pPoints[k].x = P.x;
			pPoints[k].y = P.y;
            k++;
        }
    }

    HRGN hRgn;
    hRgn = CreatePolyPolygonRgn(pPoints,pPolygonsCounts,nPolygonsCount,ALTERNATE);
//    hRgn = CreatePolyPolygonRgn(pPoints,pPolygonsCounts,nPolygonsCount,WINDING);

    ////////////////// To be removed
    Graphics::TBitmap *pBitmap = new Graphics::TBitmap();
    pBitmap->Width = 1024;
    pBitmap->Height = 768;
    pBitmap->Canvas->Brush->Color = clBlack;
    pBitmap->Canvas->Brush->Style = bsSolid;
	PaintRgn(pBitmap->Canvas->Handle,hRgn);
	pBitmap->SaveToFile("c:\\test\\Region.bmp");

    #ifdef spl_Stitch_Curve_
    FormMain->Image->Picture->Assign(pBitmap);
    #endif// spl_Stitch_Curve_

    if(pBitmap)
    {
		delete pBitmap;
        pBitmap = NULL;
    }
    //////////////////

	spl_EmbroidRegion(Region,hRgn,GlobalStitchPath);

    if(pPolygonsCounts)
    {
     	delete[] pPolygonsCounts;
        pPolygonsCounts = NULL;
    }
    if(pPoints)
    {
     	delete[] pPoints;
        pPoints = NULL;
    }
}
*/
//---------------------------------------------------------------------------

