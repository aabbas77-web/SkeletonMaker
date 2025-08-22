//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_FloodFill.h"
#include "spl_Digitizer.h"
//#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Normal Ordering (1)
static TPoint T2[9]={
                        Point(00,00),// 0
                        Point(00,+1),// 1
                        Point(-1,+1),// 2
                        Point(+1,+1),// 3
                        Point(-1,00),// 4
                        Point(+1,00),// 5
                        Point(-1,-1),// 6
                        Point(00,-1),// 7
                        Point(+1,-1),// 8
                    };
//---------------------------------------------------------------------------
void spl_FloodFillDigitizedRegion(spl_Image *pImage,spl_UInt x,spl_UInt y,Byte NewColor)
{
	if(pImage==NULL)
	{
		return; 
	}
	else
    if(pImage->ppLines==NULL)
	{
        MessageBox(0,"Invalid Image (You Must Call <UpdateLines> Before This Operation)","Error",0);
		return;
	}
    else
    if((x>=pImage->Width)&&(y>=pImage->Height))
    {
		return;
    }
    Byte OldColor=pImage->ppLines[y][x];
    if(OldColor==NewColor)
        return;
    spl_UInt Px=x;
    spl_UInt Py=y;
    spl_UInt P0x=Px;
    spl_UInt P0y=Py;
    spl_UInt NewPx=Px;
    spl_UInt NewPy=Py;
    spl_UInt N;
    vector<spl_UInt> Stackx;
    vector<spl_UInt> Stacky;
    bool IsFirst=true;
    bool Found;
    while(true)
    {
        Found=false;
        if(((Px<=pImage->Width-1)&&(Py<=pImage->Height-1))&&(pImage->ppLines[Py][Px]!=OldColor))
        {
            // Not Found
        }
        else
        if(((Px+T2[1].x>=0)&&(Px+T2[1].x<=pImage->Width-1)&&(Py+T2[1].y>=0)&&(Py+T2[1].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[1].y][Px+T2[1].x]==OldColor))
        {
            NewPx=Px+T2[1].x;
            NewPy=Py+T2[1].y;
            Found=true;
        }
        else
        if(((Px+T2[2].x>=0)&&(Px+T2[2].x<=pImage->Width-1)&&(Py+T2[2].y>=0)&&(Py+T2[2].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[2].y][Px+T2[2].x]==OldColor))
        {
            NewPx=Px+T2[2].x;
            NewPy=Py+T2[2].y;
            Found=true;
        }
        else
        if(((Px+T2[3].x>=0)&&(Px+T2[3].x<=pImage->Width-1)&&(Py+T2[3].y>=0)&&(Py+T2[3].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[3].y][Px+T2[3].x]==OldColor))
        {
            NewPx=Px+T2[3].x;
            NewPy=Py+T2[3].y;
            Found=true;
        }
        else
        if(((Px+T2[4].x>=0)&&(Px+T2[4].x<=pImage->Width-1)&&(Py+T2[4].y>=0)&&(Py+T2[4].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[4].y][Px+T2[4].x]==OldColor))
        {
            NewPx=Px+T2[4].x;
            NewPy=Py+T2[4].y;
            Found=true;
        }
        else
        if(((Px+T2[5].x>=0)&&(Px+T2[5].x<=pImage->Width-1)&&(Py+T2[5].y>=0)&&(Py+T2[5].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[5].y][Px+T2[5].x]==OldColor))
        {
            NewPx=Px+T2[5].x;
            NewPy=Py+T2[5].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewColor;

            if( ((Px+T2[6].x>=0)&&(Px+T2[6].x<=pImage->Width-1)&&(Py+T2[6].y>=0)&&(Py+T2[6].y<=pImage->Height-1))&&
                ((Px+T2[7].x>=0)&&(Px+T2[7].x<=pImage->Width-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=pImage->Height-1))&&
                (pImage->ppLines[Py+T2[6].y][Px+T2[6].x]==OldColor)&&
                (pImage->ppLines[Py+T2[7].y][Px+T2[7].x]!=OldColor)
              )
            {
                if(IsFirst)
                {
                    P0x=Px;
                    P0y=Py;
                }
                else
                {
                    // Return To Previous Spring
                    Found=false;
                    Stackx.push_back(Px);
                    Stacky.push_back(Py);
                }
                IsFirst=false;
            }
        }
        else
        if(((Px+T2[6].x>=0)&&(Px+T2[6].x<=pImage->Width-1)&&(Py+T2[6].y>=0)&&(Py+T2[6].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[6].y][Px+T2[6].x]==OldColor))
        {
            NewPx=Px+T2[6].x;
            NewPy=Py+T2[6].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewColor;

            if( ((Px+T2[7].x>=0)&&(Px+T2[7].x<=pImage->Width-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=pImage->Height-1))&&
                ((Px+T2[8].x>=0)&&(Px+T2[8].x<=pImage->Width-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=pImage->Height-1))&&
                (pImage->ppLines[Py+T2[7].y][Px+T2[7].x]!=OldColor)&&
                (pImage->ppLines[Py+T2[8].y][Px+T2[8].x]==OldColor)
              )
            {
                if(IsFirst)
                {
                    P0x=Px;
                    P0y=Py;
                }
                else
                {
                    // Return To Previous Spring
                    Found=false;
                    Stackx.push_back(Px);
                    Stacky.push_back(Py);
                }
                IsFirst=false;
            }
        }
        else
        if(((Px+T2[7].x>=0)&&(Px+T2[7].x<=pImage->Width-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[7].y][Px+T2[7].x]==OldColor))
        {
            NewPx=Px+T2[7].x;
            NewPy=Py+T2[7].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewColor;
        }
        else
        if(((Px+T2[8].x>=0)&&(Px+T2[8].x<=pImage->Width-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[8].y][Px+T2[8].x]==OldColor))
        {
            NewPx=Px+T2[8].x;
            NewPy=Py+T2[8].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewColor;
        }

        // Invalid NewP
        if(!Found)// Totally Isolated Point (Dirs=0)
        {
            pImage->ppLines[Py][Px]=NewColor;
            LFind:;
            N=0;
            for(spl_UInt i=1;i<=8;i++)
            {
                if(((P0x+T2[i].x>=0)&&(P0x+T2[i].x<=pImage->Width-1)&&(P0y+T2[i].y>=0)&&(P0y+T2[i].y<=pImage->Height-1))&&(pImage->ppLines[P0y+T2[i].y][P0x+T2[i].x]==OldColor))
                {
                    NewPx=P0x+T2[i].x;
                    NewPy=P0y+T2[i].y;
                    N++;
                }
            }
            if(N==0)
            {
                if(Stackx.empty() || Stacky.empty())   return;
                else
                {
                    P0x=Stackx[0];
                    P0y=Stacky[0];
                    Stackx.erase(Stackx.begin());
                    Stacky.erase(Stacky.begin());
                    goto LFind;
                }
            }
        }
        Px=NewPx;
        Py=NewPy;
    }
}
//---------------------------------------------------------------------------
void spl_FloodFillDigitizedRegion(spl_Image *pImage,spl_UInt x,spl_UInt y,Byte NewColor,TFloodFillCallback FloodFillCallback)
{
	if(pImage==NULL)
	{
		return; 
	}
	else
    if(pImage->ppLines==NULL)
	{
        MessageBox(0,"Invalid Image (You Must Call <UpdateLines> Before This Operation)","Error",0);
		return;
	}
    else
    if((x>=pImage->Width)&&(y>=pImage->Height))
    {
		return;
    }
    Byte OldColor=pImage->ppLines[y][x];
    if(OldColor==NewColor)
        return;
    spl_UInt Px=x;
    spl_UInt Py=y;
    spl_UInt P0x=Px;
    spl_UInt P0y=Py;
    spl_UInt NewPx=Px;
    spl_UInt NewPy=Py;
    spl_UInt N;
    vector<spl_UInt> Stackx;
    vector<spl_UInt> Stacky;
    bool IsFirst=true;
    bool Found;
    while(true)
    {
        Found=false;
        if(((Px<=pImage->Width-1)&&(Py<=pImage->Height-1))&&(pImage->ppLines[Py][Px]!=OldColor))
        {
            // Not Found
        }
        else
        if(((Px+T2[1].x>=0)&&(Px+T2[1].x<=pImage->Width-1)&&(Py+T2[1].y>=0)&&(Py+T2[1].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[1].y][Px+T2[1].x]==OldColor))
        {
            NewPx=Px+T2[1].x;
            NewPy=Py+T2[1].y;
            Found=true;
        }
        else
        if(((Px+T2[2].x>=0)&&(Px+T2[2].x<=pImage->Width-1)&&(Py+T2[2].y>=0)&&(Py+T2[2].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[2].y][Px+T2[2].x]==OldColor))
        {
            NewPx=Px+T2[2].x;
            NewPy=Py+T2[2].y;
            Found=true;
        }
        else
        if(((Px+T2[3].x>=0)&&(Px+T2[3].x<=pImage->Width-1)&&(Py+T2[3].y>=0)&&(Py+T2[3].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[3].y][Px+T2[3].x]==OldColor))
        {
            NewPx=Px+T2[3].x;
            NewPy=Py+T2[3].y;
            Found=true;
        }
        else
        if(((Px+T2[4].x>=0)&&(Px+T2[4].x<=pImage->Width-1)&&(Py+T2[4].y>=0)&&(Py+T2[4].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[4].y][Px+T2[4].x]==OldColor))
        {
            NewPx=Px+T2[4].x;
            NewPy=Py+T2[4].y;
            Found=true;
        }
        else
        if(((Px+T2[5].x>=0)&&(Px+T2[5].x<=pImage->Width-1)&&(Py+T2[5].y>=0)&&(Py+T2[5].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[5].y][Px+T2[5].x]==OldColor))
        {
            NewPx=Px+T2[5].x;
            NewPy=Py+T2[5].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewColor;
            FloodFillCallback();

            if( ((Px+T2[6].x>=0)&&(Px+T2[6].x<=pImage->Width-1)&&(Py+T2[6].y>=0)&&(Py+T2[6].y<=pImage->Height-1))&&
                ((Px+T2[7].x>=0)&&(Px+T2[7].x<=pImage->Width-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=pImage->Height-1))&&
                (pImage->ppLines[Py+T2[6].y][Px+T2[6].x]==OldColor)&&
                (pImage->ppLines[Py+T2[7].y][Px+T2[7].x]!=OldColor)
              )
            {
                if(IsFirst)
                {
                    P0x=Px;
                    P0y=Py;
                }
                else
                {
                    // Return To Previous Spring
                    Found=false;
                    Stackx.push_back(Px);
                    Stacky.push_back(Py);
                }
                IsFirst=false;
            }
        }
        else
        if(((Px+T2[6].x>=0)&&(Px+T2[6].x<=pImage->Width-1)&&(Py+T2[6].y>=0)&&(Py+T2[6].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[6].y][Px+T2[6].x]==OldColor))
        {
            NewPx=Px+T2[6].x;
            NewPy=Py+T2[6].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewColor;
            FloodFillCallback();

            if( ((Px+T2[7].x>=0)&&(Px+T2[7].x<=pImage->Width-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=pImage->Height-1))&&
                ((Px+T2[8].x>=0)&&(Px+T2[8].x<=pImage->Width-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=pImage->Height-1))&&
                (pImage->ppLines[Py+T2[7].y][Px+T2[7].x]!=OldColor)&&
                (pImage->ppLines[Py+T2[8].y][Px+T2[8].x]==OldColor)
              )
            {
                if(IsFirst)
                {
                    P0x=Px;
                    P0y=Py;
                }
                else
                {
                    // Return To Previous Spring
                    Found=false;
                    Stackx.push_back(Px);
                    Stacky.push_back(Py);
                }
                IsFirst=false;
            }
        }
        else
        if(((Px+T2[7].x>=0)&&(Px+T2[7].x<=pImage->Width-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[7].y][Px+T2[7].x]==OldColor))
        {
            NewPx=Px+T2[7].x;
            NewPy=Py+T2[7].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewColor;
            FloodFillCallback();
        }
        else
        if(((Px+T2[8].x>=0)&&(Px+T2[8].x<=pImage->Width-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[8].y][Px+T2[8].x]==OldColor))
        {
            NewPx=Px+T2[8].x;
            NewPy=Py+T2[8].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewColor;
            FloodFillCallback();
        }

        // Invalid NewP
        if(!Found)// Totally Isolated Point (Dirs=0)
        {
            pImage->ppLines[Py][Px]=NewColor;
            FloodFillCallback();
            LFind:;
            N=0;
            for(spl_UInt i=1;i<=8;i++)
            {
                if(((P0x+T2[i].x>=0)&&(P0x+T2[i].x<=pImage->Width-1)&&(P0y+T2[i].y>=0)&&(P0y+T2[i].y<=pImage->Height-1))&&(pImage->ppLines[P0y+T2[i].y][P0x+T2[i].x]==OldColor))
                {
                    NewPx=P0x+T2[i].x;
                    NewPy=P0y+T2[i].y;
                    N++;
                }
            }
            if(N==0)
            {
                if(Stackx.empty() || Stacky.empty())   return;
                else
                {
                    P0x=Stackx[0];
                    P0y=Stacky[0];
                    Stackx.erase(Stackx.begin());
                    Stacky.erase(Stacky.begin());
                    goto LFind;
                }
            }
        }
        Px=NewPx;
        Py=NewPy;
    }
}
//---------------------------------------------------------------------------
void spl_FloodFillDigitizedRegionWhileNotEqualColor(spl_Image *pImage,spl_UInt x,spl_UInt y,Byte StopColor,Byte NewColor)
{
	if(pImage==NULL)
	{
		return; 
	}
	else
    if(pImage->ppLines==NULL)
	{
        MessageBox(0,"Invalid Image (You Must Call <UpdateLines> Before This Operation)","Error",0);
		return;
	}
    else
    if((x>=pImage->Width)&&(y>=pImage->Height))
    {
		return;
    }
    if((pImage->ppLines[y][x] == StopColor) || (pImage->ppLines[y][x] == NewColor)) 	return;
    spl_UInt Px=x;
    spl_UInt Py=y;
    spl_UInt P0x=Px;
    spl_UInt P0y=Py;
    spl_UInt NewPx=Px;
    spl_UInt NewPy=Py;
    spl_UInt N;
    vector<spl_UInt> Stackx;
    vector<spl_UInt> Stacky;
    bool IsFirst=true;
    bool Found;
    while(true)
    {
        Found=false;
        if(((Px<=pImage->Width-1)&&(Py<=pImage->Height-1))&&((pImage->ppLines[Py][Px]==StopColor)||(pImage->ppLines[Py][Px]==NewColor)))
        {
            // Not Found
        }
        else
        if(((Px+T2[1].x>=0)&&(Px+T2[1].x<=pImage->Width-1)&&(Py+T2[1].y>=0)&&(Py+T2[1].y<=pImage->Height-1))&&((pImage->ppLines[Py+T2[1].y][Px+T2[1].x]!=StopColor)||(pImage->ppLines[Py+T2[1].y][Px+T2[1].x]!=NewColor)))
        {
            NewPx=Px+T2[1].x;
            NewPy=Py+T2[1].y;
            Found=true;
        }
        else
        if(((Px+T2[2].x>=0)&&(Px+T2[2].x<=pImage->Width-1)&&(Py+T2[2].y>=0)&&(Py+T2[2].y<=pImage->Height-1))&&((pImage->ppLines[Py+T2[2].y][Px+T2[2].x]!=StopColor)||(pImage->ppLines[Py+T2[2].y][Px+T2[2].x]!=NewColor)))
        {
            NewPx=Px+T2[2].x;
            NewPy=Py+T2[2].y;
            Found=true;
        }
        else
        if(((Px+T2[3].x>=0)&&(Px+T2[3].x<=pImage->Width-1)&&(Py+T2[3].y>=0)&&(Py+T2[3].y<=pImage->Height-1))&&((pImage->ppLines[Py+T2[3].y][Px+T2[3].x]!=StopColor)||(pImage->ppLines[Py+T2[3].y][Px+T2[3].x]!=NewColor)))
        {
            NewPx=Px+T2[3].x;
            NewPy=Py+T2[3].y;
            Found=true;
        }
        else
        if(((Px+T2[4].x>=0)&&(Px+T2[4].x<=pImage->Width-1)&&(Py+T2[4].y>=0)&&(Py+T2[4].y<=pImage->Height-1))&&((pImage->ppLines[Py+T2[4].y][Px+T2[4].x]!=StopColor)||(pImage->ppLines[Py+T2[4].y][Px+T2[4].x]!=NewColor)))
        {
            NewPx=Px+T2[4].x;
            NewPy=Py+T2[4].y;
            Found=true;
        }
        else
        if(((Px+T2[5].x>=0)&&(Px+T2[5].x<=pImage->Width-1)&&(Py+T2[5].y>=0)&&(Py+T2[5].y<=pImage->Height-1))&&((pImage->ppLines[Py+T2[5].y][Px+T2[5].x]!=StopColor)||(pImage->ppLines[Py+T2[5].y][Px+T2[5].x]!=NewColor)))
        {
            NewPx=Px+T2[5].x;
            NewPy=Py+T2[5].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewColor;

            if( ((Px+T2[6].x>=0)&&(Px+T2[6].x<=pImage->Width-1)&&(Py+T2[6].y>=0)&&(Py+T2[6].y<=pImage->Height-1))&&
                ((Px+T2[7].x>=0)&&(Px+T2[7].x<=pImage->Width-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=pImage->Height-1))&&
                ((pImage->ppLines[Py+T2[6].y][Px+T2[6].x]!=StopColor)||(pImage->ppLines[Py+T2[6].y][Px+T2[6].x]!=NewColor))&&
                ((pImage->ppLines[Py+T2[7].y][Px+T2[7].x]==StopColor)||(pImage->ppLines[Py+T2[7].y][Px+T2[7].x]==NewColor))
              )
            {
                if(IsFirst)
                {
                    P0x=Px;
                    P0y=Py;
                }
                else
                {
                    // Return To Previous Spring
                    Found=false;
                    Stackx.push_back(Px);
                    Stacky.push_back(Py);
                }
                IsFirst=false;
            }
        }
        else
        if(((Px+T2[6].x>=0)&&(Px+T2[6].x<=pImage->Width-1)&&(Py+T2[6].y>=0)&&(Py+T2[6].y<=pImage->Height-1))&&((pImage->ppLines[Py+T2[6].y][Px+T2[6].x]!=StopColor)||(pImage->ppLines[Py+T2[6].y][Px+T2[6].x]!=NewColor)))
        {
            NewPx=Px+T2[6].x;
            NewPy=Py+T2[6].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewColor;

            if( ((Px+T2[7].x>=0)&&(Px+T2[7].x<=pImage->Width-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=pImage->Height-1))&&
                ((Px+T2[8].x>=0)&&(Px+T2[8].x<=pImage->Width-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=pImage->Height-1))&&
                ((pImage->ppLines[Py+T2[7].y][Px+T2[7].x]==StopColor)||(pImage->ppLines[Py+T2[7].y][Px+T2[7].x]==NewColor))&&
                ((pImage->ppLines[Py+T2[8].y][Px+T2[8].x]!=StopColor)||(pImage->ppLines[Py+T2[8].y][Px+T2[8].x]!=NewColor))
              )
            {
                if(IsFirst)
                {
                    P0x=Px;
                    P0y=Py;
                }
                else
                {
                    // Return To Previous Spring
                    Found=false;
                    Stackx.push_back(Px);
                    Stacky.push_back(Py);
                }
                IsFirst=false;
            }
        }
        else
        if(((Px+T2[7].x>=0)&&(Px+T2[7].x<=pImage->Width-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=pImage->Height-1))&&((pImage->ppLines[Py+T2[7].y][Px+T2[7].x]!=StopColor)||(pImage->ppLines[Py+T2[7].y][Px+T2[7].x]!=NewColor)))
        {
            NewPx=Px+T2[7].x;
            NewPy=Py+T2[7].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewColor;
        }
        else
        if(((Px+T2[8].x>=0)&&(Px+T2[8].x<=pImage->Width-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=pImage->Height-1))&&((pImage->ppLines[Py+T2[8].y][Px+T2[8].x]!=StopColor)||(pImage->ppLines[Py+T2[8].y][Px+T2[8].x]!=NewColor)))
        {
            NewPx=Px+T2[8].x;
            NewPy=Py+T2[8].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewColor;
        }

        // Invalid NewP
        if(!Found)// Totally Isolated Point (Dirs=0)
        {
            pImage->ppLines[Py][Px]=NewColor;
            LFind:;
            N=0;
            for(spl_UInt i=1;i<=8;i++)
            {
                if(((P0x+T2[i].x>=0)&&(P0x+T2[i].x<=pImage->Width-1)&&(P0y+T2[i].y>=0)&&(P0y+T2[i].y<=pImage->Height-1))&&((pImage->ppLines[P0y+T2[i].y][P0x+T2[i].x]!=StopColor)||(pImage->ppLines[P0y+T2[i].y][P0x+T2[i].x]!=NewColor)))
                {
                    NewPx=P0x+T2[i].x;
                    NewPy=P0y+T2[i].y;
                    N++;
                }
            }
            if(N==0)
            {
                if(Stackx.empty() || Stacky.empty())   return;
                else
                {
                    P0x=Stackx[0];
                    P0y=Stacky[0];
                    Stackx.erase(Stackx.begin());
                    Stacky.erase(Stacky.begin());
                    goto LFind;
                }
            }
        }
        Px=NewPx;
        Py=NewPy;
    }
}
//---------------------------------------------------------------------------
/*
void spl_FillDigitizedRegionForProcessing(spl_Image *pImage,spl_UInt x,spl_UInt y,Byte NewIndex,spl_UWord ContourIndex)
{
	if(pImage==NULL)
	{
		return;
	}
	else
    if(pImage->ppLines==NULL)
	{
        MessageBox(0,"Invalid Image (You Must Call <UpdateLines> Before This Operation)","Error",0);
		return;
	}
    else
    if((x>=pImage->Width)&&(y>=pImage->Height))
    {
		return;
    }
    Byte OldIndex=pImage->ppLines[y][x];
    if(OldIndex==NewIndex)
        return;

    spl_UInt Px=x;
    spl_UInt Py=y;
    spl_UInt P0x=Px;
    spl_UInt P0y=Py;
    spl_UInt NewPx=Px;
    spl_UInt NewPy=Py;
    spl_UInt N;
    vector<spl_UInt> Stackx;
    vector<spl_UInt> Stacky;
    bool IsFirst=true;
    bool Found;
    while(true)
    {
        Found=false;
        if(((Px<=pImage->Width-1)&&(Py<=pImage->Height-1))&&(pImage->ppLines[Py][Px]!=OldIndex))
        {
            // Not Found
        }
        else
        if(((Px+T2[1].x>=0)&&(Px+T2[1].x<=pImage->Width-1)&&(Py+T2[1].y>=0)&&(Py+T2[1].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[1].y][Px+T2[1].x]==OldIndex))// Here Errors
        {
            NewPx=Px+T2[1].x;
            NewPy=Py+T2[1].y;
            Found=true;
        }
        else
        if(((Px+T2[2].x>=0)&&(Px+T2[2].x<=pImage->Width-1)&&(Py+T2[2].y>=0)&&(Py+T2[2].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[2].y][Px+T2[2].x]==OldIndex))
        {
            NewPx=Px+T2[2].x;
            NewPy=Py+T2[2].y;
            Found=true;
        }
        else
        if(((Px+T2[3].x>=0)&&(Px+T2[3].x<=pImage->Width-1)&&(Py+T2[3].y>=0)&&(Py+T2[3].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[3].y][Px+T2[3].x]==OldIndex))
        {
            NewPx=Px+T2[3].x;
            NewPy=Py+T2[3].y;
            Found=true;
        }
        else
        if(((Px+T2[4].x>=0)&&(Px+T2[4].x<=pImage->Width-1)&&(Py+T2[4].y>=0)&&(Py+T2[4].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[4].y][Px+T2[4].x]==OldIndex))
        {
            NewPx=Px+T2[4].x;
            NewPy=Py+T2[4].y;
            Found=true;
        }
        else
        if(((Px+T2[5].x>=0)&&(Px+T2[5].x<=pImage->Width-1)&&(Py+T2[5].y>=0)&&(Py+T2[5].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[5].y][Px+T2[5].x]==OldIndex))
        {
            NewPx=Px+T2[5].x;
            NewPy=Py+T2[5].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewIndex;
            spl_SetPixelContour(Px,Py,ContourIndex);

            if( ((Px+T2[6].x>=0)&&(Px+T2[6].x<=pImage->Width-1)&&(Py+T2[6].y>=0)&&(Py+T2[6].y<=pImage->Height-1))&&
                ((Px+T2[7].x>=0)&&(Px+T2[7].x<=pImage->Width-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=pImage->Height-1))&&
                (pImage->ppLines[Py+T2[6].y][Px+T2[6].x]==OldIndex)&&
                (pImage->ppLines[Py+T2[7].y][Px+T2[7].x]!=OldIndex)
              )
            {
                if(IsFirst)
                {
                    P0x=Px;
                    P0y=Py;
                }
                else
                {
                    // Return To Previous Spring
                    Found=false;
                    Stackx.push_back(Px);
                    Stacky.push_back(Py);
                }
                IsFirst=false;
            }
        }
        else
        if(((Px+T2[6].x>=0)&&(Px+T2[6].x<=pImage->Width-1)&&(Py+T2[6].y>=0)&&(Py+T2[6].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[6].y][Px+T2[6].x]==OldIndex))
        {
            NewPx=Px+T2[6].x;
            NewPy=Py+T2[6].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewIndex;
            spl_SetPixelContour(Px,Py,ContourIndex);

            if( ((Px+T2[7].x>=0)&&(Px+T2[7].x<=pImage->Width-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=pImage->Height-1))&&
                ((Px+T2[8].x>=0)&&(Px+T2[8].x<=pImage->Width-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=pImage->Height-1))&&
                (pImage->ppLines[Py+T2[7].y][Px+T2[7].x]!=OldIndex)&&
                (pImage->ppLines[Py+T2[8].y][Px+T2[8].x]==OldIndex)
              )
            {
                if(IsFirst)
                {
                    P0x=Px;
                    P0y=Py;
                }
                else
                {
                    // Return To Previous Spring
                    Found=false;
                    Stackx.push_back(Px);
                    Stacky.push_back(Py);
                }
                IsFirst=false;
            }
        }
        else
        if(((Px+T2[7].x>=0)&&(Px+T2[7].x<=pImage->Width-1)&&(Py+T2[7].y>=0)&&(Py+T2[7].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[7].y][Px+T2[7].x]==OldIndex))
        {
            NewPx=Px+T2[7].x;
            NewPy=Py+T2[7].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewIndex;
            spl_SetPixelContour(Px,Py,ContourIndex);
        }
        else
        if(((Px+T2[8].x>=0)&&(Px+T2[8].x<=pImage->Width-1)&&(Py+T2[8].y>=0)&&(Py+T2[8].y<=pImage->Height-1))&&(pImage->ppLines[Py+T2[8].y][Px+T2[8].x]==OldIndex))
        {
            NewPx=Px+T2[8].x;
            NewPy=Py+T2[8].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewIndex;
            spl_SetPixelContour(Px,Py,ContourIndex);
        }

        // Invalid NewP
        if(!Found)// Totally Isolated Point (Dirs=0)
        {
            pImage->ppLines[Py][Px]=NewIndex;
            spl_SetPixelContour(Px,Py,ContourIndex);
            LFind:;
            N=0;
            for(spl_UInt i=1;i<=8;i++)
            {
                if(((P0x+T2[i].x>=0)&&(P0x+T2[i].x<=pImage->Width-1)&&(P0y+T2[i].y>=0)&&(P0y+T2[i].y<=pImage->Height-1))&&(pImage->ppLines[P0y+T2[i].y][P0x+T2[i].x]==OldIndex))
                {
                    NewPx=P0x+T2[i].x;
                    NewPy=P0y+T2[i].y;
                    N++;
                }
            }
            if(N==0)
            {
                if(Stackx.empty() || Stacky.empty())   return;
                else
                {
                    P0x=Stackx[0];
                    P0y=Stacky[0];
                    Stackx.erase(Stackx.begin());
                    Stacky.erase(Stacky.begin());
                    goto LFind;
                }
            }
        }
        Px=NewPx;
        Py=NewPy;
    }
}
*/
//---------------------------------------------------------------------------
void spl_FillDigitizedRegionForProcessing(spl_Image *pImage,spl_UInt x,spl_UInt y,Byte NewIndex,spl_UWord ContourIndex)
{
	if(pImage==NULL)
	{
		return;
	}
	else
    if(pImage->ppLines==NULL)
	{
        MessageBox(0,"Invalid Image (You Must Call <UpdateLines> Before This Operation)","Error",0);
		return;
	}
    else
    if((x>=pImage->Width)&&(y>=pImage->Height))
    {
		return;
    }
    Byte OldIndex=pImage->ppLines[y][x];
    if(OldIndex==NewIndex)
        return;

    spl_UInt Px=x;
    spl_UInt Py=y;
    spl_UInt P0x=Px;
    spl_UInt P0y=Py;
    spl_UInt NewPx=Px;
    spl_UInt NewPy=Py;
    spl_UInt N;
    vector<spl_UInt> Stackx;
    vector<spl_UInt> Stacky;
    bool IsFirst=true;
    bool Found;
    while(true)
    {
        Found=false;
        if(((Px<pImage->Width-spl_DigitizerBorder)&&(Py<pImage->Height-spl_DigitizerBorder))&&(pImage->ppLines[Py][Px]!=OldIndex))
        {
            // Not Found
        }
        else
        if(((Px+T2[1].x>=spl_DigitizerBorder)&&(Px+T2[1].x<pImage->Width-spl_DigitizerBorder)&&(Py+T2[1].y>=spl_DigitizerBorder)&&(Py+T2[1].y<pImage->Height-spl_DigitizerBorder))&&(pImage->ppLines[Py+T2[1].y][Px+T2[1].x]==OldIndex))
        {
            NewPx=Px+T2[1].x;
            NewPy=Py+T2[1].y;
            Found=true;
        }
        else
        if(((Px+T2[2].x>=spl_DigitizerBorder)&&(Px+T2[2].x<pImage->Width-spl_DigitizerBorder)&&(Py+T2[2].y>=spl_DigitizerBorder)&&(Py+T2[2].y<pImage->Height-spl_DigitizerBorder))&&(pImage->ppLines[Py+T2[2].y][Px+T2[2].x]==OldIndex))
        {
            NewPx=Px+T2[2].x;
            NewPy=Py+T2[2].y;
            Found=true;
        }
        else
        if(((Px+T2[3].x>=spl_DigitizerBorder)&&(Px+T2[3].x<pImage->Width-spl_DigitizerBorder)&&(Py+T2[3].y>=spl_DigitizerBorder)&&(Py+T2[3].y<pImage->Height-spl_DigitizerBorder))&&(pImage->ppLines[Py+T2[3].y][Px+T2[3].x]==OldIndex))
        {
            NewPx=Px+T2[3].x;
            NewPy=Py+T2[3].y;
            Found=true;
        }
        else
        if(((Px+T2[4].x>=spl_DigitizerBorder)&&(Px+T2[4].x<pImage->Width-spl_DigitizerBorder)&&(Py+T2[4].y>=spl_DigitizerBorder)&&(Py+T2[4].y<pImage->Height-spl_DigitizerBorder))&&(pImage->ppLines[Py+T2[4].y][Px+T2[4].x]==OldIndex))
        {
            NewPx=Px+T2[4].x;
            NewPy=Py+T2[4].y;
            Found=true;
        }
        else
        if(((Px+T2[5].x>=spl_DigitizerBorder)&&(Px+T2[5].x<pImage->Width-spl_DigitizerBorder)&&(Py+T2[5].y>=spl_DigitizerBorder)&&(Py+T2[5].y<pImage->Height-spl_DigitizerBorder))&&(pImage->ppLines[Py+T2[5].y][Px+T2[5].x]==OldIndex))
        {
            NewPx=Px+T2[5].x;
            NewPy=Py+T2[5].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewIndex;
            spl_SetPixelContour(Px,Py,ContourIndex);

            if( ((Px+T2[6].x>=spl_DigitizerBorder)&&(Px+T2[6].x<pImage->Width-spl_DigitizerBorder)&&(Py+T2[6].y>=spl_DigitizerBorder)&&(Py+T2[6].y<pImage->Height-spl_DigitizerBorder))&&
                ((Px+T2[7].x>=spl_DigitizerBorder)&&(Px+T2[7].x<pImage->Width-spl_DigitizerBorder)&&(Py+T2[7].y>=spl_DigitizerBorder)&&(Py+T2[7].y<pImage->Height-spl_DigitizerBorder))&&
                (pImage->ppLines[Py+T2[6].y][Px+T2[6].x]==OldIndex)&&
                (pImage->ppLines[Py+T2[7].y][Px+T2[7].x]!=OldIndex)
              )
            {
                if(IsFirst)
                {
                    P0x=Px;
                    P0y=Py;
                }
                else
                {
                    // Return To Previous Spring
                    Found=false;
                    Stackx.push_back(Px);
                    Stacky.push_back(Py);
                }
                IsFirst=false;
            }
        }
        else
        if(((Px+T2[6].x>=spl_DigitizerBorder)&&(Px+T2[6].x<pImage->Width-spl_DigitizerBorder)&&(Py+T2[6].y>=spl_DigitizerBorder)&&(Py+T2[6].y<pImage->Height-spl_DigitizerBorder))&&(pImage->ppLines[Py+T2[6].y][Px+T2[6].x]==OldIndex))
        {
            NewPx=Px+T2[6].x;
            NewPy=Py+T2[6].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewIndex;
            spl_SetPixelContour(Px,Py,ContourIndex);

            if( ((Px+T2[7].x>=spl_DigitizerBorder)&&(Px+T2[7].x<pImage->Width-spl_DigitizerBorder)&&(Py+T2[7].y>=spl_DigitizerBorder)&&(Py+T2[7].y<pImage->Height-spl_DigitizerBorder))&&
                ((Px+T2[8].x>=spl_DigitizerBorder)&&(Px+T2[8].x<pImage->Width-spl_DigitizerBorder)&&(Py+T2[8].y>=spl_DigitizerBorder)&&(Py+T2[8].y<pImage->Height-spl_DigitizerBorder))&&
                (pImage->ppLines[Py+T2[7].y][Px+T2[7].x]!=OldIndex)&&
                (pImage->ppLines[Py+T2[8].y][Px+T2[8].x]==OldIndex)
              )
            {
                if(IsFirst)
                {
                    P0x=Px;
                    P0y=Py;
                }
                else
                {
                    // Return To Previous Spring
                    Found=false;
                    Stackx.push_back(Px);
                    Stacky.push_back(Py);
                }
                IsFirst=false;
            }
        }
        else
        if(((Px+T2[7].x>=spl_DigitizerBorder)&&(Px+T2[7].x<pImage->Width-spl_DigitizerBorder)&&(Py+T2[7].y>=spl_DigitizerBorder)&&(Py+T2[7].y<pImage->Height-spl_DigitizerBorder))&&(pImage->ppLines[Py+T2[7].y][Px+T2[7].x]==OldIndex))
        {
            NewPx=Px+T2[7].x;
            NewPy=Py+T2[7].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewIndex;
            spl_SetPixelContour(Px,Py,ContourIndex);
        }
        else
        if(((Px+T2[8].x>=spl_DigitizerBorder)&&(Px+T2[8].x<pImage->Width-spl_DigitizerBorder)&&(Py+T2[8].y>=spl_DigitizerBorder)&&(Py+T2[8].y<pImage->Height-spl_DigitizerBorder))&&(pImage->ppLines[Py+T2[8].y][Px+T2[8].x]==OldIndex))
        {
            NewPx=Px+T2[8].x;
            NewPy=Py+T2[8].y;
            Found=true;
            pImage->ppLines[Py][Px]=NewIndex;
            spl_SetPixelContour(Px,Py,ContourIndex);
        }

        // Invalid NewP
        if(!Found)// Totally Isolated Point (Dirs=0)
        {
            pImage->ppLines[Py][Px]=NewIndex;
            spl_SetPixelContour(Px,Py,ContourIndex);
            LFind:;
            N=0;
            for(spl_UInt i=1;i<=8;i++)
            {
                if(((P0x+T2[i].x>=spl_DigitizerBorder)&&(P0x+T2[i].x<pImage->Width-spl_DigitizerBorder)&&(P0y+T2[i].y>=spl_DigitizerBorder)&&(P0y+T2[i].y<pImage->Height-spl_DigitizerBorder))&&(pImage->ppLines[P0y+T2[i].y][P0x+T2[i].x]==OldIndex))
                {
                    NewPx=P0x+T2[i].x;
                    NewPy=P0y+T2[i].y;
                    N++;
                }
            }
            if(N==0)
            {
                if(Stackx.empty() || Stacky.empty())   return;
                else
                {
                    P0x=Stackx[0];
                    P0y=Stacky[0];
                    Stackx.erase(Stackx.begin());
                    Stacky.erase(Stacky.begin());
                    goto LFind;
                }
            }
        }
        Px=NewPx;
        Py=NewPy;
    }
}
//---------------------------------------------------------------------------

