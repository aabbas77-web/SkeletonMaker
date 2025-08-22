//---------------------------------------------------------------------------
#include <assert.h>
#include <set.h>
#include <algorithm>
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_Digitizer.h"
#include "spl_ImageProcessing.h"
#include "spl_ColorQuantizer.h"
#include "spl_FloodFill.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------Processing--------------------------------------
//---------------------------------------------------------------------------
vector<spl_Curve> spl_GlobalCurves;
spl_Image *spl_pGlobalPixelsInfo=NULL;
spl_UInt spl_DigitizerBorder=4;
spl_UInt spl_ContoursCount;
static spl_UWord _ContourIndex;
//---------------------------------------------------------------------------
// if pixel is on object turn left else turn right
//---------------------------------------------------------------------------
void spl_FollowDigitizedContour(bool bOnObject,bool SimpleMethode,spl_UByte Dir,spl_Image *pIndices,spl_UInt x,spl_UInt y,spl_Contour &Contour)
{
    Contour.Points.clear();
    if(pIndices==NULL)  return;
    if(pIndices->ppLines==NULL) return;
    if((x<spl_DigitizerBorder)||(x>pIndices->Width-1-spl_DigitizerBorder)||(y<spl_DigitizerBorder)||(y>pIndices->Height-1-spl_DigitizerBorder)) return;
    spl_UByte Index=pIndices->ppLines[y][x];
    if(Index==spl_BackgroundIndex)  return;
    spl_UByte CurrIndex;
    spl_UByte PrevIndex;
    spl_UInt StartPointx,StartPointy;
    spl_UInt Px=x;
    spl_UInt Py=y;
    spl_UInt PrevPx,PrevPy;
    spl_UByte StartDir;

    // Find The Start Point
    while(true)
    {
        if((Px>=spl_DigitizerBorder)&&(Px<=pIndices->Width-1-spl_DigitizerBorder)&&(Py>=spl_DigitizerBorder)&&(Py<=pIndices->Height-1-spl_DigitizerBorder))
            CurrIndex=pIndices->ppLines[Py][Px];
        else
            CurrIndex=spl_BackgroundIndex;
        if(CurrIndex!=Index)
        {
            PrevIndex=CurrIndex;
            PrevPx=Px;
            PrevPy=Py;
            Px-=spl_T1[Dir].x;
            Py-=spl_T1[Dir].y;
            // Negate Direction
            Dir=(Dir + 4) % 8;
            break;
        }
        Px+=spl_T1[Dir].x;
        Py+=spl_T1[Dir].y;
    }

    // Start Point (Edge Point)
    // From Left(White) To Right(Black, Current)
    StartPointx=Px;
    StartPointy=Py;
    StartDir = Dir;
    while(true)
    {
        if((Px>=spl_DigitizerBorder)&&(Px<=pIndices->Width-1-spl_DigitizerBorder)&&(Py>=spl_DigitizerBorder)&&(Py<=pIndices->Height-1-spl_DigitizerBorder))
            CurrIndex=pIndices->ppLines[Py][Px];
        else
            CurrIndex=spl_BackgroundIndex;
        if(CurrIndex==Index)// Turn Left
        {
        	if(bOnObject)
            {
	            Contour.Points.push_back(splPoint(Px,Py));
            }
            if(SimpleMethode)
            {
				// Negate Direction
	            Dir=(Dir + 4) % 8;
	            // Turn Right
	            Dir=(Dir + 2) % 8;
	            Px+=spl_T1[Dir].x;
				Py+=spl_T1[Dir].y;
            }
            else
            {
	            if(PrevIndex!=Index)// Return To Previous Pixel And Turn Right
    	        {
        	        Px=PrevPx;
            	    Py=PrevPy;
                	PrevIndex=pIndices->ppLines[Py][Px];

	                // Negate Direction
	                Dir=(Dir + 4) % 8;
	                // Turn Right
	                Dir=(Dir + 2) % 8;
	                Px+=spl_T1[Dir].x;
	                Py+=spl_T1[Dir].y;
	            }
            }
        }
        else// Turn Right
        {
        	if(!bOnObject)
            {
	            Contour.Points.push_back(splPoint(Px,Py));
            }
            PrevPx=Px;
            PrevPy=Py;
            PrevIndex=CurrIndex;

            Dir=(Dir + 2) % 8;
            Px+=spl_T1[Dir].x;
            Py+=spl_T1[Dir].y;
        }

        if((Px==StartPointx)&&(Py==StartPointy)&&(Dir==StartDir))  break;
    }
}
//---------------------------------------------------------------------------
void spl_FollowDigitizedContour(bool SimpleMethode,spl_Image *pIndices,spl_UInt x,spl_UInt y,spl_Contour &Contour)
{
    Contour.Points.clear();
    if(pIndices==NULL)  return;
    if(pIndices->ppLines==NULL) return;
    if((x<spl_DigitizerBorder)||(x>pIndices->Width-1-spl_DigitizerBorder)||(y<spl_DigitizerBorder)||(y>pIndices->Height-1-spl_DigitizerBorder)) return;
    spl_UByte Index=pIndices->ppLines[y][x];
    if(Index==spl_BackgroundIndex)  return;
    spl_UByte CurrIndex;
    spl_UByte PrevIndex;
    spl_UByte Dir=4;
    spl_UInt StartPointx,StartPointy;
    spl_UInt Px=x;
    spl_UInt Py=y;
    spl_UInt PrevPx,PrevPy;

    // Find The Start Point
    while(true)
    {
        if((Px>=spl_DigitizerBorder)&&(Px<=pIndices->Width-1-spl_DigitizerBorder)&&(Py>=spl_DigitizerBorder)&&(Py<=pIndices->Height-1-spl_DigitizerBorder))
            CurrIndex=pIndices->ppLines[Py][Px];
        else
            CurrIndex=spl_BackgroundIndex;
        if(CurrIndex!=Index)
        {
            PrevIndex=CurrIndex;
            PrevPx=Px;
            PrevPy=Py;
            Px-=spl_T1[Dir].x;
            Py-=spl_T1[Dir].y;
            Dir=0;
            break;
        }
        Px+=spl_T1[Dir].x;
        Py+=spl_T1[Dir].y;
    }

    // Start Point (Edge Point)
    // From Left(White) To Right(Black, Current)
    StartPointx=Px;
    StartPointy=Py;
    while(true)
    {
        if((Px>=spl_DigitizerBorder)&&(Px<=pIndices->Width-1-spl_DigitizerBorder)&&(Py>=spl_DigitizerBorder)&&(Py<=pIndices->Height-1-spl_DigitizerBorder))
            CurrIndex=pIndices->ppLines[Py][Px];
        else
            CurrIndex=spl_BackgroundIndex;
        if(CurrIndex==Index)// Turn Left
        {
            Contour.Points.push_back(splPoint(Px,Py));
            if(SimpleMethode)
            {
				// Negate Direction
	            Dir=(Dir + 4) % 8;
	            // Turn Right
	            Dir=(Dir + 2) % 8;
	            Px+=spl_T1[Dir].x;
				Py+=spl_T1[Dir].y;
            }
            else
            {
	            if(PrevIndex!=Index)// Return To Previous Pixel And Turn Right
    	        {
        	        Px=PrevPx;
            	    Py=PrevPy;
                	PrevIndex=pIndices->ppLines[Py][Px];

	                // Negate Direction
	                Dir=(Dir + 4) % 8;
	                // Turn Right
	                Dir=(Dir + 2) % 8;
	                Px+=spl_T1[Dir].x;
	                Py+=spl_T1[Dir].y;
	            }
            }
        }
        else// Turn Right
        {
            PrevPx=Px;
            PrevPy=Py;
            PrevIndex=CurrIndex;

            Dir=(Dir + 2) % 8;
            Px+=spl_T1[Dir].x;
            Py+=spl_T1[Dir].y;
        }

        if((Px==StartPointx)&&(Py==StartPointy)&&(Dir==0))  break;
    }
    spl_RedefineCurve(Contour);
}
//---------------------------------------------------------------------------
void spl_FollowDigitizedContourForProcessing(bool SimpleMethode,spl_UInt x,spl_UInt y,spl_Contour &Contour,set<spl_UWord> &OutterNeighbors)
{
    Contour.Points.clear();
    OutterNeighbors.clear();
    if(spl_pGlobalPixelsInfo==NULL) return;
    if(spl_pGlobalPixelsInfo->ppLines==NULL)    return;
    if((x<spl_DigitizerBorder)||(x>spl_pGlobalPixelsInfo->Width-1-spl_DigitizerBorder)||(y<spl_DigitizerBorder)||(y>spl_pGlobalPixelsInfo->Height-1-spl_DigitizerBorder))   return;
    spl_UWord Index=spl_GetPixelContour(x,y);
    if(Index==spl_MaxWord)  return;
    spl_UWord CurrIndex;
    spl_UWord PrevIndex;
    spl_UByte Dir=4;
    spl_UInt StartPointx,StartPointy;
    spl_UInt Px=x;
    spl_UInt Py=y;
    spl_UInt PrevPx,PrevPy;

    // Find The Start Point
    while(true)
    {
        if((Px>=spl_DigitizerBorder)&&(Px<=spl_pGlobalPixelsInfo->Width-1-spl_DigitizerBorder)&&(Py>=spl_DigitizerBorder)&&(Py<=spl_pGlobalPixelsInfo->Height-1-spl_DigitizerBorder))
            CurrIndex=spl_GetPixelContour(Px,Py);
        else
            CurrIndex=spl_MaxWord;
        if(CurrIndex!=Index)
        {
            PrevIndex=CurrIndex;
            PrevPx=Px;
            PrevPy=Py;
            Px-=spl_T1[Dir].x;
            Py-=spl_T1[Dir].y;
            Dir=0;
            break;
        }
        Px+=spl_T1[Dir].x;
        Py+=spl_T1[Dir].y;
    }

    // Start Point (Edge Point)
    // From Left(White) To Right(Black, Current)
    StartPointx=Px;
    StartPointy=Py;
    while(true)
    {
        if((Px>=spl_DigitizerBorder)&&(Px<=spl_pGlobalPixelsInfo->Width-1-spl_DigitizerBorder)&&(Py>=spl_DigitizerBorder)&&(Py<=spl_pGlobalPixelsInfo->Height-1-spl_DigitizerBorder))
            CurrIndex=spl_GetPixelContour(Px,Py);
        else
            CurrIndex=spl_MaxWord;
        if(CurrIndex==Index)// Turn Left
        {
            Contour.Points.push_back(splPoint(Px,Py));
            if(SimpleMethode)
            {
            	// Negate Direction
                Dir=(Dir + 4) % 8;
                // Turn Right
                Dir=(Dir + 2) % 8;
                Px+=spl_T1[Dir].x;
                Py+=spl_T1[Dir].y;
            }
            else
            {
	            if(PrevIndex!=Index)// Return To Previous Pixel And Turn Right
    	        {
        	        Px=PrevPx;
                    Py=PrevPy;
	                PrevIndex=spl_GetPixelContour(Px,Py);

    	            // Negate Direction
        	        Dir=(Dir + 4) % 8;
            	    // Turn Right
	                Dir=(Dir + 2) % 8;
    	            Px+=spl_T1[Dir].x;
        	        Py+=spl_T1[Dir].y;
	            }
            }
        }
        else// Turn Right
        {
            if(CurrIndex!=spl_MaxWord)  OutterNeighbors.insert(CurrIndex);

            PrevPx=Px;
            PrevPy=Py;
            PrevIndex=CurrIndex;

            Dir=(Dir + 2) % 8;
            Px+=spl_T1[Dir].x;
            Py+=spl_T1[Dir].y;
        }

        if((Px==StartPointx)&&(Py==StartPointy)&&(Dir==0))  break;
    }
    spl_RedefineCurve(Contour);
}
//---------------------------------------------------------------------------
/*
void spl_FollowDigitizedContour(spl_Image *pIndices,spl_UInt x,spl_UInt y,spl_Contour &Contour)
{
    Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
    if(pIndices==NULL)  return;
    if(pIndices->ppLines==NULL) return;
    if((x<spl_DigitizerBorder)||(x>=pIndices->Width-spl_DigitizerBorder)||(y<spl_DigitizerBorder)||(y>=pIndices->Height-spl_DigitizerBorder)) return;
    spl_UByte Index=pIndices->ppLines[y][x];
    if(Index==spl_BackgroundIndex)  return;
    spl_UByte CurrIndex;
    spl_UByte PrevIndex;
    spl_UByte Dir=4;
    spl_UInt StartPointx,StartPointy;
    spl_UInt Px=x;
    spl_UInt Py=y;
    spl_UInt PrevPx,PrevPy;

    // Find The Start Point
    while(true)
    {
        if((Px>=spl_DigitizerBorder)&&(Px<pIndices->Width-spl_DigitizerBorder)&&(Py>=spl_DigitizerBorder)&&(Py<pIndices->Height-spl_DigitizerBorder))
            CurrIndex=pIndices->ppLines[Py][Px];
        else
            CurrIndex=spl_BackgroundIndex;
        if(CurrIndex!=Index)
        {
            PrevIndex=CurrIndex;
            PrevPx=Px;
            PrevPy=Py;
            Px-=spl_T1[Dir].x;
            Py-=spl_T1[Dir].y;
            Dir=0;
            break;
        }
        Px+=spl_T1[Dir].x;
        Py+=spl_T1[Dir].y;
    }

    // Start Point (Edge Point)
    // From Left(White) To Right(Black, Current)
    StartPointx=Px;
    StartPointy=Py;
    while(true)
    {
        if((Px>=spl_DigitizerBorder)&&(Px<pIndices->Width-spl_DigitizerBorder)&&(Py>=spl_DigitizerBorder)&&(Py<pIndices->Height-spl_DigitizerBorder))
            CurrIndex=pIndices->ppLines[Py][Px];
        else
            CurrIndex=spl_BackgroundIndex;
        if(CurrIndex==Index)// Turn Left
        {
            Contour.Points.push_back(splPoint(Px,Py));
            if(PrevIndex!=Index)// Return To Previous Pixel And Turn Right
            {
                Px=PrevPx;
                Py=PrevPy;
                PrevIndex=pIndices->ppLines[Py][Px];

                // Negate Direction
                Dir=(Dir + 4) % 8;
                // Turn Right
                Dir=(Dir + 2) % 8;
                Px+=spl_T1[Dir].x;
                Py+=spl_T1[Dir].y;
            }
        }
        else// Turn Right
        {
            PrevPx=Px;
            PrevPy=Py;
            PrevIndex=CurrIndex;

            Dir=(Dir + 2) % 8;
            Px+=spl_T1[Dir].x;
            Py+=spl_T1[Dir].y;
        }

        if((Px==StartPointx)&&(Py==StartPointy)&&(Dir==0))  break;
    }
    spl_RedefineCurve(Contour);
}
//---------------------------------------------------------------------------
void spl_FollowDigitizedContourForProcessing(spl_UInt x,spl_UInt y,spl_Contour &Contour,set<spl_UWord> &OutterNeighbors)
{
    Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
    OutterNeighbors.erase(OutterNeighbors.begin(),OutterNeighbors.end());
    if(spl_pGlobalPixelsInfo==NULL) return;
    if(spl_pGlobalPixelsInfo->ppLines==NULL)    return;
    if((x<spl_DigitizerBorder)||(x>=spl_pGlobalPixelsInfo->Width-spl_DigitizerBorder)||(y<spl_DigitizerBorder)||(y>=spl_pGlobalPixelsInfo->Height-spl_DigitizerBorder))   return;
    spl_UWord Index=spl_GetPixelContour(x,y);
    if(Index==spl_MaxWord)  return;
    spl_UWord CurrIndex;
    spl_UWord PrevIndex;
    spl_UByte Dir=4;
    spl_UInt StartPointx,StartPointy;
    spl_UInt Px=x;
    spl_UInt Py=y;
    spl_UInt PrevPx,PrevPy;

    // Find The Start Point
    while(true)
    {
        if((Px>=spl_DigitizerBorder)&&(Px<spl_pGlobalPixelsInfo->Width-spl_DigitizerBorder)&&(Py>=spl_DigitizerBorder)&&(Py<spl_pGlobalPixelsInfo->Height-spl_DigitizerBorder))
            CurrIndex=spl_GetPixelContour(Px,Py);
        else
            CurrIndex=spl_MaxWord;
        if(CurrIndex!=Index)
        {
            PrevIndex=CurrIndex;
            PrevPx=Px;
            PrevPy=Py;
            Px-=spl_T1[Dir].x;
            Py-=spl_T1[Dir].y;
            Dir=0;
            break;
        }
        Px+=spl_T1[Dir].x;
        Py+=spl_T1[Dir].y;
    }

    // Start Point (Edge Point)
    // From Left(White) To Right(Black, Current)
    StartPointx=Px;
    StartPointy=Py;
    while(true)
    {
        if((Px>=spl_DigitizerBorder)&&(Px<spl_pGlobalPixelsInfo->Width-spl_DigitizerBorder)&&(Py>=spl_DigitizerBorder)&&(Py<spl_pGlobalPixelsInfo->Height-spl_DigitizerBorder))
            CurrIndex=spl_GetPixelContour(Px,Py);
        else
            CurrIndex=spl_MaxWord;
        if(CurrIndex==Index)// Turn Left
        {
            Contour.Points.push_back(splPoint(Px,Py));
            if(PrevIndex!=Index)// Return To Previous Pixel And Turn Right
            {
                Px=PrevPx;
                Py=PrevPy;
                PrevIndex=spl_GetPixelContour(Px,Py);

                // Negate Direction
                Dir=(Dir + 4) % 8;
                // Turn Right
                Dir=(Dir + 2) % 8;
                Px+=spl_T1[Dir].x;
                Py+=spl_T1[Dir].y;
            }
        }
        else// Turn Right
        {
            if(CurrIndex!=spl_MaxWord)  OutterNeighbors.insert(CurrIndex);

            PrevPx=Px;
            PrevPy=Py;
            PrevIndex=CurrIndex;

            Dir=(Dir + 2) % 8;
            Px+=spl_T1[Dir].x;
            Py+=spl_T1[Dir].y;
        }

        if((Px==StartPointx)&&(Py==StartPointy)&&(Dir==0))  break;
    }
    spl_RedefineCurve(Contour);
}
*/
//---------------------------------------------------------------------------
void spl_ExtractDigitizedContoursForProcessing(spl_Image *pIndices)
{
    // Checking Input
    assert(spl_pGlobalPixelsInfo!=NULL);
    if(pIndices==NULL)  return;
    if(pIndices->ppLines==NULL) return;
    if(spl_ColorsCount<=0)  return;

    spl_pGlobalPixelsInfo->Assign(pIndices,pf16bit);
    spl_FlushImage(spl_pGlobalPixelsInfo,spl_MaxWord);
    spl_GlobalCurves.erase(spl_GlobalCurves.begin(),spl_GlobalCurves.end());

    // Initialization
    spl_Image *pTemp=new spl_Image();
    pTemp->Assign(pIndices);

    // First Scan
    // Fill Regions Informations (Numerations)
    spl_UByte Index;
    vector<spl_UInt> StartPointsx;
    vector<spl_UInt> StartPointsy;
    _ContourIndex=0;
    spl_ContoursCount=0;
    for(spl_UInt y=spl_DigitizerBorder;y<pTemp->Height-spl_DigitizerBorder;y++)
    {
        for(spl_UInt x=spl_DigitizerBorder;x<pTemp->Width-spl_DigitizerBorder;x++)
        {
            Index=pTemp->ppLines[y][x];
            if(Index!=spl_BackgroundIndex)
            {
                StartPointsx.push_back(x);
                StartPointsy.push_back(y);
                // Clear Region And Fill It`s Informations
                spl_FillDigitizedRegionForProcessing(pTemp,x,y,spl_BackgroundIndex,_ContourIndex);
                _ContourIndex++;
                spl_ContoursCount++;
            }
        }
    }
    #ifdef _EMB_TRACE_
    FormMain->AddMessage("Filling Region Informations (Numerations)...");
    #endif // _EMB_TRACE_

    // Second Scan
    // Extract Regions
    spl_UInt Px,Py;
    for(spl_UInt i=0;i<StartPointsx.size();i++)
    {
        Px=StartPointsx[i];
        Py=StartPointsy[i];

        spl_Curve Curve;
        Curve.FillColorIndex=pIndices->ppLines[Py][Px];;
        Curve.LineColorIndex=pIndices->ppLines[Py][Px];;
        Curve.ProcessFillColor=spl_ProcessFillColor;
        Curve.ProcessLineColor=spl_ProcessLineColor;

        spl_FollowDigitizedContourForProcessing(true,Px,Py,Curve.Contour,Curve.OutterNeighbors);

        // Add Contour
        Curve.Contour.ContourInfo.GIndex=i;
        Curve.CurveInfo.UseGlobalParameters=true;
        Curve.CurveInfo.EmbParameters=spl_Global_EmbParameters;
        spl_GlobalCurves.push_back(Curve);
    }
    #ifdef _EMB_TRACE_
    FormMain->AddMessage("Extracting Regions...");
    #endif // _EMB_TRACE_

    // Finding Holes
    spl_UInt HoleIndex;
    for(spl_UInt i=0;i<spl_GlobalCurves.size();i++)
    {
        vector<spl_UWord> Neighbors;
        copy(spl_GlobalCurves[i].OutterNeighbors.begin(),spl_GlobalCurves[i].OutterNeighbors.end(),back_inserter(Neighbors));

        // Simple Holes (Outter Neighbors Count == 1)
        if(Neighbors.size()==1)
        {
            spl_GlobalCurves[Neighbors[0]].Holes.push_back(i);
        }
        else// Complex Holes (Outter Neighbors Count > 1)
        if(Neighbors.size()>1)
        {
            for(spl_UInt j=0;j<Neighbors.size();j++)
            {
                HoleIndex=Neighbors[j];
                if(!spl_GlobalCurves[HoleIndex].OutterNeighbors.count(i))
                {
                    spl_GlobalCurves[HoleIndex].ComplexHoles.push_back(i);
                }
            }
        }
    }
    #ifdef _EMB_TRACE_
    FormMain->AddMessage("Finding Holes...");
    #endif // _EMB_TRACE_

    // Finding Final Holes (Without Complex Holes)
    bool Found;
    pTemp->Assign(pIndices);
    spl_FlushImage(pTemp,spl_BackgroundIndex);
    spl_Curve Curve;
    for(spl_UInt i=0;i<spl_GlobalCurves.size();i++)
    {
        // Complex Holes
        Found=false;
        for(spl_UInt j=0;j<spl_GlobalCurves[i].ComplexHoles.size();j++)
        {
            HoleIndex=spl_GlobalCurves[i].ComplexHoles[j];

            pTemp->pBitmap->Canvas->Pen->Color=clBlack;// Index=0
            pTemp->pBitmap->Canvas->Brush->Color=clBlack;// Index=0
            pTemp->pBitmap->Canvas->Brush->Style=bsSolid;
            spl_DrawPolygonContour(pTemp->pBitmap->Canvas->Handle,spl_GlobalCurves[HoleIndex].Contour);
            Found=true;
        }

        if(Found)
        {
            for(spl_UInt y=spl_DigitizerBorder;y<pTemp->Height-spl_DigitizerBorder;y++)
            {
                for(spl_UInt x=spl_DigitizerBorder;x<pTemp->Width-spl_DigitizerBorder;x++)
                {
                    Index=pTemp->ppLines[y][x];
                    if(Index!=spl_BackgroundIndex)
                    {
                        spl_FollowDigitizedContour(true,pTemp,x,y,Curve.Contour);
                        if(!Curve.Contour.Points.empty())
                        {
                            // Add Contour
                            spl_GlobalCurves[i].Holes.push_back(_ContourIndex);
                            Curve.ProcessFillColor=spl_ProcessFillColor;
                            Curve.ProcessLineColor=spl_ProcessLineColor;
                            Curve.FillColorIndex=Index;
                            Curve.LineColorIndex=Index;
                            Curve.Contour.ContourInfo.GIndex=_ContourIndex;
                            Curve.CurveInfo.UseGlobalParameters=true;
                            Curve.CurveInfo.EmbParameters=spl_Global_EmbParameters;
                            spl_GlobalCurves.push_back(Curve);
                            _ContourIndex++;
                        }

                        // Clear This Region
                        spl_FloodFillDigitizedRegion(pTemp,x,y,spl_BackgroundIndex);
                    }
                }
            }
        }
    }
    #ifdef _EMB_TRACE_
    FormMain->AddMessage("Finalizing ...");
    #endif // _EMB_TRACE_

    // Finalization
    if(pTemp)   delete pTemp;
}
//---------------------------------------------------------------------------
void spl_ConvertGlobalContourToRegion(spl_UInt ContourIndex,bool Smoothed,bool ByBezier,spl_UInt Order,spl_UInt Degree,spl_Region &Region)
{
	Region.Contours.clear();
    if(ContourIndex >= spl_ContoursCount)	return;

    spl_UByte ColorIndex;
    spl_Contour SmoothContour;
    spl_Contour Contour;
    spl_UWord HoleIndex;

    ColorIndex=spl_GlobalCurves[ContourIndex].FillColorIndex;
    Region.LineColor=spl_QuantizedColors[ColorIndex];
    Region.FillColor=spl_QuantizedColors[ColorIndex];
    if(Smoothed)
    {
        // Smooth Contours
        if(ByBezier)
            spl_ConvertBSplineToBezier(spl_GlobalCurves[ContourIndex].Contour,Contour);
        else
        {
            spl_SmoothContour(spl_GlobalCurves[ContourIndex].Contour,SPLINE_CENT_L2,Order,Degree,SmoothContour);
            spl_ConvertBSplineToBezier(SmoothContour,Contour);
        }
        Region.Contours.push_back(Contour);
    }
    else
    {
        Region.Contours.push_back(spl_GlobalCurves[ContourIndex].Contour);
    }

    // Holes
    for(spl_UInt j=0;j<spl_GlobalCurves[ContourIndex].Holes.size();j++)
    {
        HoleIndex=spl_GlobalCurves[ContourIndex].Holes[j];
        if(Smoothed)
        {
            // Smooth Contours
            if(ByBezier)
                spl_ConvertBSplineToBezier(spl_GlobalCurves[HoleIndex].Contour,Contour);
            else
            {
                spl_SmoothContour(spl_GlobalCurves[HoleIndex].Contour,SPLINE_CENT_L2,Order,Degree,SmoothContour);
                spl_ConvertBSplineToBezier(SmoothContour,Contour);
            }
            Region.Contours.push_back(Contour);
        }
        else
        {
            Region.Contours.push_back(spl_GlobalCurves[HoleIndex].Contour);
        }
    }
}
//---------------------------------------------------------------------------
void spl_ConvertGlobalContoursToMultiLayer(bool Smoothed,bool ByBezier,spl_UInt Order,spl_UInt Degree,spl_MultiLayer &MultiLayer)
{
    MultiLayer.Layers.erase(MultiLayer.Layers.begin(),MultiLayer.Layers.end());

    spl_UByte ColorIndex;
    spl_Contour SmoothContour;
    spl_Contour Contour;
    spl_UWord HoleIndex;
    spl_Region Region;

    MultiLayer.Layers.resize(spl_ColorsCount);
    for(spl_UInt i=0;i<spl_ContoursCount;i++)
    {
    	spl_ConvertGlobalContourToRegion(i,Smoothed,ByBezier,Order,Degree,Region);
        ColorIndex=spl_GlobalCurves[i].FillColorIndex;
        if(!Region.Contours.empty())
        {
            MultiLayer.Layers[ColorIndex].Regions.push_back(Region);
        }
    }

    // Clear Empty Layers
    for(spl_UInt i=0;i<MultiLayer.Layers.size();i++)
    {
        if(MultiLayer.Layers[i].Regions.empty())
            MultiLayer.Layers.erase(&MultiLayer.Layers[i]);
    }
}
//---------------------------------------------------------------------------
void spl_ConvertGlobalContoursToMultiLayerForEmbroidery(spl_MultiLayer &MultiLayer)
{
    MultiLayer.Layers.erase(MultiLayer.Layers.begin(),MultiLayer.Layers.end());

    spl_UByte ColorIndex;
    spl_Contour SmoothContour;
    spl_Contour Contour;
    spl_UWord HoleIndex;

    MultiLayer.Layers.resize(spl_ColorsCount);
    for(spl_UInt i=0;i<spl_ContoursCount;i++)
    {
        if(spl_GlobalCurves[i].CurveInfo.UseGlobalParameters)
        {
            spl_GlobalCurves[i].ProcessFillColor=spl_ProcessFillColor;
            spl_GlobalCurves[i].ProcessLineColor=spl_ProcessLineColor;
        }

        if(spl_GlobalCurves[i].ProcessFillColor)
        {
            ColorIndex=spl_GlobalCurves[i].FillColorIndex;

            spl_Region FillRegion;
            FillRegion.LineColor=spl_QuantizedColors[ColorIndex];
            FillRegion.FillColor=spl_QuantizedColors[ColorIndex];
            Contour=spl_GlobalCurves[i].Contour;
            Contour.ContourInfo.ProcessFill=true;
            Contour.ContourInfo.ProcessLine=false;
            FillRegion.Contours.push_back(Contour);

            // Holes
            for(spl_UInt j=0;j<spl_GlobalCurves[i].Holes.size();j++)
            {
                HoleIndex=spl_GlobalCurves[i].Holes[j];
                Contour=spl_GlobalCurves[HoleIndex].Contour;
                Contour.ContourInfo.ProcessFill=true;
                Contour.ContourInfo.ProcessLine=false;
                FillRegion.Contours.push_back(Contour);
            }

            if(!FillRegion.Contours.empty())
                MultiLayer.Layers[ColorIndex].Regions.push_back(FillRegion);
        }

        if(spl_GlobalCurves[i].ProcessLineColor)
        {
            ColorIndex=spl_GlobalCurves[i].LineColorIndex;

            spl_Region LineRegion;
            LineRegion.LineColor=spl_QuantizedColors[ColorIndex];
            LineRegion.FillColor=spl_QuantizedColors[ColorIndex];
            Contour=spl_GlobalCurves[i].Contour;
            Contour.ContourInfo.ProcessFill=false;
            Contour.ContourInfo.ProcessLine=true;
            LineRegion.Contours.push_back(Contour);

            // Holes
            for(spl_UInt j=0;j<spl_GlobalCurves[i].Holes.size();j++)
            {
                HoleIndex=spl_GlobalCurves[i].Holes[j];
                Contour=spl_GlobalCurves[HoleIndex].Contour;
                Contour.ContourInfo.ProcessFill=false;
                Contour.ContourInfo.ProcessLine=true;
                LineRegion.Contours.push_back(Contour);
            }

            if(!LineRegion.Contours.empty())
                MultiLayer.Layers[ColorIndex].Regions.push_back(LineRegion);
        }
    }

    // Clear Empty Layers
    for(spl_UInt i=0;i<MultiLayer.Layers.size();i++)
    {
        if(MultiLayer.Layers[i].Regions.empty())
            MultiLayer.Layers.erase(&MultiLayer.Layers[i]);
    }
}
//---------------------------------------------------------------------------
void spl_ReorderMultiLayerForEmbroidery(spl_Image *pIndices,spl_MultiLayer &MultiLayer)
{
    spl_MultiLayer TempMultiLayer;
/*
    // Reorder Layers For Best Jumps
    spl_UInt Index;
    vector<spl_UInt> Colors;
    typedef vector<spl_UInt>::iterator iterator;
	iterator it;
    for(UINT i=0;i<spl_GlobalCurves.size();i++)
    {
    	Index = spl_GlobalCurves[i].FillColorIndex;
    	iterator it = find(Colors.begin(),Colors.end(),Index);
        if(it == Colors.end())
        {
	    	Colors.push_back(Index);
        }
    }

    spl_Layer Layer;
    for(int i=0;i<spl_ColorsCount;i++)
    {
		TempMultiLayer.Layers.push_back(Layer);
    }

    for(UINT i=0;i<MultiLayer.Layers.size();i++)
    {
//    	if(Colors[i] < TempMultiLayer.Layers.size())
		try
        {
	    	TempMultiLayer.Layers[Colors[i]] = MultiLayer.Layers[i];
        }
        catch(...)
        {
        }
    }

    MultiLayer = TempMultiLayer;
    
    // Clear Empty Layers
    for(spl_UInt i=0;i<MultiLayer.Layers.size();i++)
    {
        if(MultiLayer.Layers[i].Regions.empty())
            MultiLayer.Layers.erase(&MultiLayer.Layers[i]);
    }
*/

    TempMultiLayer.Layers.clear();
    for(int i=MultiLayer.Layers.size()-1;i>=0;i--)
    {
    	TempMultiLayer.Layers.push_back(MultiLayer.Layers[i]);
    }
    MultiLayer = TempMultiLayer;

}
//---------------------------------------------------------------------------
void spl_SaveGlobalCurves(bool Smoothed,bool ByBezier,spl_UInt Order,spl_UInt Degree,AnsiString strFileName)
{
    spl_UByte ColorIndex;
    spl_Contour SmoothContour;
    spl_Contour Contour;
    spl_UWord HoleIndex;

    FILE *file;
    int nRegionsCount = 0;
    file=fopen(strFileName.c_str(),"wb");
    fwrite(&nRegionsCount,sizeof(nRegionsCount),1,file);

    for(spl_UInt i=0;i<spl_ContoursCount;i++)
    {
        ColorIndex=spl_GlobalCurves[i].FillColorIndex;

        spl_Region Region;
        Region.LineColor=spl_QuantizedColors[ColorIndex];
        Region.FillColor=spl_QuantizedColors[ColorIndex];

        if(Smoothed)
        {
            // Smooth Contours
            if(ByBezier)
                spl_ConvertBSplineToBezier(spl_GlobalCurves[i].Contour,Contour);
            else
            {
                spl_SmoothContour(spl_GlobalCurves[i].Contour,SPLINE_CENT_L2,Order,Degree,SmoothContour);
                spl_ConvertBSplineToBezier(SmoothContour,Contour);
            }
            Region.Contours.push_back(Contour);
        }
        else
        {
            Region.Contours.push_back(spl_GlobalCurves[i].Contour);
        }

        // Holes
        for(spl_UInt j=0;j<spl_GlobalCurves[i].Holes.size();j++)
        {
            HoleIndex=spl_GlobalCurves[i].Holes[j];
            if(Smoothed)
            {
                // Smooth Contours
                if(ByBezier)
                    spl_ConvertBSplineToBezier(spl_GlobalCurves[HoleIndex].Contour,Contour);
                else
                {
                    spl_SmoothContour(spl_GlobalCurves[HoleIndex].Contour,SPLINE_CENT_L2,Order,Degree,SmoothContour);
                    spl_ConvertBSplineToBezier(SmoothContour,Contour);
                }
                Region.Contours.push_back(Contour);
            }
            else
            {
                Region.Contours.push_back(spl_GlobalCurves[HoleIndex].Contour);
            }
        }

        
/*
        ColorIndex=spl_GlobalCurves[i].FillColorIndex;

        spl_Region Region;
        Region.LineColor=spl_QuantizedColors[ColorIndex];
        Region.FillColor=spl_QuantizedColors[ColorIndex];
        Contour=spl_GlobalCurves[i].Contour;
        Contour.ContourInfo.ProcessFill=true;
        Contour.ContourInfo.ProcessLine=false;
        Region.Contours.push_back(Contour);

        // Holes
        for(spl_UInt j=0;j<spl_GlobalCurves[i].Holes.size();j++)
        {
            HoleIndex=spl_GlobalCurves[i].Holes[j];
            Contour=spl_GlobalCurves[HoleIndex].Contour;
            Contour.ContourInfo.ProcessFill=true;
            Contour.ContourInfo.ProcessLine=false;
            Region.Contours.push_back(Contour);
        }
*/

        if(!Region.Contours.empty())
        {
		    spl_SaveRegion(file,Region);
            nRegionsCount++;
        }
    }
    // seek to the beginning of the file
   	fseek(file, SEEK_SET, 0);
    fwrite(&nRegionsCount,sizeof(nRegionsCount),1,file);

    fclose(file);
}
//---------------------------------------------------------------------------
void spl_LoadGlobalCurves(AnsiString strFileName,spl_Layer &Layer)
{
	Layer.Regions.clear();
    
    spl_UByte ColorIndex;
    spl_Contour SmoothContour;
    spl_Contour Contour;
    spl_UWord HoleIndex;

    FILE *file;
    int nRegionsCount;
    spl_Region Region;
    file=fopen(strFileName.c_str(),"rb");
    fread(&nRegionsCount,sizeof(nRegionsCount),1,file);

    for(int i=0;i<nRegionsCount;i++)
    {
    	spl_LoadRegion(file,Region);
        if(Region.Contours.size() > 0)
        {
	        Layer.Regions.push_back(Region);
        }
    }

    fclose(file);
}
//---------------------------------------------------------------------------

