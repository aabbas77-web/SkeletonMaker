//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_PathFinder.h"
#include "spl_Digitizer.h"
#include "spl_ColorQuantizer.h"
#include "spl_FloodFill.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
static spl_Image *_pIndices;
static spl_UByte _ColorIndex;
static spl_UInt  _Color;
static spl_Point _K;
static TPoint _NP;
static TPoint _PrevNP;
static spl_UByte _Dir = 4; 
static spl_UByte _CurrDir = 4;
//---------------------------------------------------------------------------
bool spl_IsTowPointOnLine(spl_Point P1,spl_Point P2)
{
    double L = spl_PDistance(&P1,&P2);
    if(L <= 0.0)	return true;
	_K.x = (P2.x - P1.x) / L;
	_K.y = (P2.y - P1.y) / L;

    spl_Point NP;
    NP=P1;
    _PrevNP.x = NP.x;
    _PrevNP.y = NP.y;
    while(
            (int(NP.x)>=0)&&(int(NP.x)<int(_pIndices->Width))&&
            (int(NP.y)>=0)&&(int(NP.y)<int(_pIndices->Height))&&
            (_pIndices->ppLines[int(NP.y)][int(NP.x)]==_ColorIndex)
         )
    {
        NP.x+=_K.x;
        NP.y+=_K.y;
        if((spl_ABS(NP.x - P2.x) <= 1.0) && (spl_ABS(NP.y - P2.y) <= 1.0))
        {
			return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
void spl_GetPointProjection(spl_Point P,spl_Point &NP)
{
    bool Found=false;
    NP=P;
    _PrevNP.x = int(NP.x);
    _PrevNP.y = int(NP.y);
    while(
            (int(NP.x)>=0)&&(int(NP.x)<int(_pIndices->Width))&&
            (int(NP.y)>=0)&&(int(NP.y)<int(_pIndices->Height))&&
            (_pIndices->ppLines[int(NP.y)][int(NP.x)]==_ColorIndex)
         )
    {
        NP.x+=_K.x;
        NP.y+=_K.y;
        _NP.x = int(NP.x);
        _NP.y = int(NP.y);
        if((_NP.x != _PrevNP.x) || (_NP.y != _PrevNP.y))
        {
    		_CurrDir = spl_GetDirection(&_PrevNP,&_NP);
			_PrevNP = _NP;
        }
        Found=true;
    }

    if(Found)
    {
	    while(
    	        (int(NP.x)>=0)&&(int(NP.x)<int(_pIndices->Width))&&
        	    (int(NP.y)>=0)&&(int(NP.y)<int(_pIndices->Height))&&
            	(_pIndices->ppLines[int(NP.y)][int(NP.x)] != _ColorIndex)
	         )
	    {
	        NP.x -= _K.x;
    	    NP.y -= _K.y;
	    }
    }

    NP.x = int(NP.x);
    NP.y = int(NP.y);
}
//---------------------------------------------------------------------------
void spl_GetGuidePoints(spl_Point P1,spl_Point P2,spl_Contour &Guides)
{
	Guides.Points.clear();
	spl_UByte ColorIndex = _ColorIndex;
	spl_UByte PrevColorIndex = _ColorIndex;
    spl_Point nNP,NP,PrevNP;
    NP=P1;

	// Normal Direction
    double L = spl_PDistance(&P1,&P2);
    if(L <= 0.0)	return;
	_K.x = (P2.x - P1.x) / L;
	_K.y = (P2.y - P1.y) / L;

    // P1
    nNP.x = int(NP.x);
    nNP.y = int(NP.y);
    Guides.Points.push_back(nNP);
    PrevNP = NP;

    while(
            (int(NP.x)>=0)&&(int(NP.x)<int(_pIndices->Width))&&
            (int(NP.y)>=0)&&(int(NP.y)<int(_pIndices->Height))
         )
    {
        if((spl_ABS(NP.x - P2.x) <= 1.0) && (spl_ABS(NP.y - P2.y) <= 1.0))
        {
        	// P2
	    	nNP.x = int(NP.x);
	    	nNP.y = int(NP.y);
        	Guides.Points.push_back(nNP);
         	break;
        }

        ColorIndex = _pIndices->ppLines[int(NP.y)][int(NP.x)];
		if(ColorIndex == _ColorIndex)
        {
        	if(PrevColorIndex != _ColorIndex)
            {
	        	// New P
		    	nNP.x = int(NP.x);
	    		nNP.y = int(NP.y);
        		Guides.Points.push_back(nNP);
            }
        }
        else
        {
        	if(PrevColorIndex == _ColorIndex)
            {
	        	// New P
		    	nNP.x = int(PrevNP.x);
	    		nNP.y = int(PrevNP.y);
        		Guides.Points.push_back(nNP);
            }
        }
        PrevColorIndex = ColorIndex;
        PrevNP = NP;

        NP.x+=_K.x;
        NP.y+=_K.y;
    }
}
//---------------------------------------------------------------------------
void spl_GetMinimumGuidePoints(spl_Point P1,spl_Point P2,spl_Contour &Guides)
{
	Guides.Points.clear();
	WORD _ContourIndex = spl_GetPixelContour(P1.x,_pIndices->Height-1-P1.y);
	WORD ContourIndex = _ContourIndex;
	WORD PrevContourIndex = ContourIndex;
    spl_Point nNP,NP,PrevNP;
    vector<WORD> ContourIndices;
    NP=P1;

	// Normal Direction
    double L = spl_PDistance(&P1,&P2);
    if(L <= 0.0)	return;
	_K.x = (P2.x - P1.x) / L;
	_K.y = (P2.y - P1.y) / L;

    // P1
    nNP.x = int(NP.x);
    nNP.y = int(NP.y);
    PrevNP = NP;

    while(
            (int(NP.x)>=0)&&(int(NP.x)<int(_pIndices->Width))&&
            (int(NP.y)>=0)&&(int(NP.y)<int(_pIndices->Height))
         )
    {
        if((spl_ABS(NP.x - P2.x) <= 1.0) && (spl_ABS(NP.y - P2.y) <= 1.0))
        {
         	break;
        }

		ContourIndex = spl_GetPixelContour(int(NP.x),_pIndices->Height-1-int(NP.y));
		if(ContourIndex == _ContourIndex)
        {
        	if(PrevContourIndex != _ContourIndex)
            {
			    ContourIndices.push_back(PrevContourIndex);

	        	// New P
		    	nNP.x = int(NP.x);
	    		nNP.y = int(NP.y);
        		Guides.Points.push_back(nNP);
            }
        }
        else
        {
        	if(PrevContourIndex == _ContourIndex)
            {
			    ContourIndices.push_back(ContourIndex);

	        	// New P
		    	nNP.x = int(PrevNP.x);
	    		nNP.y = int(PrevNP.y);
        		Guides.Points.push_back(nNP);
            }
        }
        PrevContourIndex = ContourIndex;
        PrevNP = NP;

        NP.x+=_K.x;
        NP.y+=_K.y;
    }

    // Remove repeated points (that containe in the same object)
    for(spl_UInt i=0;i<ContourIndices.size();i++)
    {
	    PrevContourIndex = ContourIndices[i];
        for(spl_UInt j=ContourIndices.size()-1;j>=i+1;j--)
        {
			ContourIndex = ContourIndices[j];
			if(ContourIndex == PrevContourIndex)
            {
		        for(spl_UInt k=j-1;k>=i+1;k--)
        		{
					ContourIndices.erase(&ContourIndices[k]);
		            Guides.Points.erase(&Guides.Points[k]);
                }
                break;
            }
        }
    }
    // P1
    nNP.x = int(P1.x);
    nNP.y = int(P1.y);
    Guides.Points.insert(Guides.Points.begin(),nNP);

    // P2
    nNP.x = int(P2.x);
    nNP.y = int(P2.y);
    Guides.Points.push_back(nNP);
}
//---------------------------------------------------------------------------
bool spl_Get2PointOnContour(spl_Point &P1,spl_Point &P2,spl_Point &NP1,spl_Point &NP2)
{
	// Normal Direction
    double L = spl_PDistance(&P1,&P2);
    if(L <= 0.0)	return false;
	_K.x = (P2.x - P1.x) / L;
	_K.y = (P2.y - P1.y) / L;

   	spl_GetPointProjection(P1,NP1);
    _Dir = _CurrDir;

	// Negative Direction
	_K.x *= -1.0;
	_K.y *= -1.0;
   	spl_GetPointProjection(P2,NP2);
    return true;
}
//---------------------------------------------------------------------------
bool spl_FindPathSingle(bool Append,spl_Point P1,spl_Point P2,spl_Contour &Path)
{
	if(!Append)
    {
		Path.Points.clear();
    }
    if(_pIndices->ppLines[int(P2.y)][int(P2.x)] != _ColorIndex)	return false;
    spl_Point NP1,NP2;
    spl_Contour Contour;
    double Distance;
    int Index1,Index2;
    spl_UInt Line1,Line2,Count;
    
    if(spl_IsTowPointOnLine(P1,P2))
    {
	    Path.Points.push_back(P1);
	    Path.Points.push_back(P2);
     	return true;
    }
	if(!spl_Get2PointOnContour(P1,P2,NP1,NP2))	return false;

    spl_FollowDigitizedContour(false,true,_Dir,_pIndices,NP1.x,NP1.y,Contour);
    Count = Contour.Points.size();
    if(Count <= 0)	return false;
    spl_FindNearestPoint(Contour,NP1,Index1,Distance);
    if(Distance > 1.0)	return false;
    spl_FindNearestPoint(Contour,NP2,Index2,Distance);
    if(Distance > 1.0)	return false;

    Path.Points.push_back(P1);
    Path.Points.push_back(NP1);

    if(Index1 <= Index2)
    {
    	Line1 = Index2 - Index1 + 1;
    	Line2 = (Index1 - 0 + 1) + (Count - 1 - Index2 + 1);
	    if(Line1 <= Line2)
	    {
	     	for(int i=Index1;i<=Index2;i++)
	        {
			    Path.Points.push_back(Contour.Points[i]);
	        }
	    }
	    else
	    {
	     	for(int i=Index1;i>=0;i--)
	        {
			    Path.Points.push_back(Contour.Points[i]);
	        }
	     	for(int i=Count-1;i>=Index2;i--)
	        {
			    Path.Points.push_back(Contour.Points[i]);
	        }
	    }
    }
    else
    {
    	Line1 = Index1 - Index2 + 1;
    	Line2 = (Index2 - 0 + 1) + (Count-1 - Index1 + 1);
	    if(Line1 <= Line2)
	    {
	     	for(int i=Index1;i>=Index2;i--)
	        {
			    Path.Points.push_back(Contour.Points[i]);
	        }
	    }
	    else
	    {
	     	for(spl_UInt i=Index1;i<Count;i++)
	        {
			    Path.Points.push_back(Contour.Points[i]);
	        }
	     	for(int i=0;i<=Index2;i++)
	        {
			    Path.Points.push_back(Contour.Points[i]);
	        }
	    }
    }

    Path.Points.push_back(NP2);
    Path.Points.push_back(P2);
	return true;// Path founded
}
//---------------------------------------------------------------------------
void spl_MinimizePath(spl_Contour &Path)
{
	if(Path.Points.size() < 2)	return;
    spl_Point Pi,Pj;
    int Index;

	for(spl_UInt i=0;i<Path.Points.size();i++)
	{
		Pi = Path.Points[i];
	    Index = -1;
	    for(spl_UInt j=Path.Points.size()-1;j>=i+1;j--)
	    {
			Pj = Path.Points[j];
	        if(spl_IsTowPointOnLine(Pi,Pj))
	        {
				Index = j;
                break;
	        }
	    }
	    if(Index >= int(i+1))
	    {
	        for(spl_UInt j=Index-1;j>=i+1;j--)
		    {
				Path.Points.erase(&Path.Points[j]);
	        }
	    }
	}
}
//---------------------------------------------------------------------------
/*
void spl_MinimizePath(spl_Contour &Path)
{
	if(Path.Points.size() < 2)	return;
    spl_Point Pi,Pj;
    int Index;

	for(spl_UInt i=0;i<Path.Points.size();i++)
	{
		Pi = Path.Points[i];
	    Index = -1;
	    for(spl_UInt j=i+1;j<Path.Points.size();j++)
	    {
			Pj = Path.Points[j];
	        if(spl_IsTowPointOnLine(Pi,Pj))
	        {
				Index = j;
	        }
	    }
	    if(Index >= int(i+1))
	    {
	        for(spl_UInt j=Index-1;j>=i+1;j--)
		    {
				Path.Points.erase(&Path.Points[j]);
	        }
	    }
	}
}
*/
//---------------------------------------------------------------------------
bool spl_FindPath(spl_Image *pIndices,spl_Point P1,spl_Point P2,spl_Contour &Path)
{
	Path.Points.clear();
	spl_Contour Guides;
    spl_Point P,OP;
    spl_Image *pImage = new spl_Image();
    pImage->Assign(pIndices);

    spl_FloodFillDigitizedRegion(pImage,P1.x,P1.y,spl_ReservedIndex);

    _pIndices = pImage;
    _ColorIndex = _pIndices->ppLines[int(P1.y)][int(P1.x)];
//    spl_GetMinimumGuidePoints(P1,P2,Guides);
	spl_GetGuidePoints(P1,P2,Guides);
    if(Guides.Points.size() < 2)
    {
	    if(pImage)
    	{
     		delete pImage;
	        pImage = NULL;
	    }
    	return false;
    }
    
    P = Guides.Points[0];
    OP = P;
    for(spl_UInt i=1;i<Guides.Points.size();i++)
    {
	    P = Guides.Points[i];
        if(!spl_FindPathSingle(true,OP,P,Path))
        {
        	Path.Points.clear();
         	return false;
        };
    	OP = P;
    }

	spl_MinimizePath(Path);

    if(pImage)
    {
     	delete pImage;
        pImage = NULL;
    }
	return true;
}
//---------------------------------------------------------------------------

