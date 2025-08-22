//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector.h>
#include <set.h>
#include <Algorithms.h>
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
spl_Image::spl_Image()
{
    pBitmap=new Graphics::TBitmap();
    Width=0;
    Height=0;
    Bits=1;
    LineSize=0;
    ImageSize=0;
    ppLines=NULL;
    Updated=false;
}
//---------------------------------------------------------------------------
spl_Image::~spl_Image()
{
    DeAllocate();
    if(pBitmap)     delete pBitmap;
}
//---------------------------------------------------------------------------
void spl_Image::Allocate()
{
    if(Height!=0)
    {
        ppLines=new spl_UByte*[Height];
    }
}
//---------------------------------------------------------------------------
void spl_Image::DeAllocate()
{
    if(ppLines)
    {
        delete[] ppLines;
        ppLines=NULL;
    }
}
//---------------------------------------------------------------------------
void spl_Image::UpdateLines()
{
        Updated=false;
        if(Width!=(spl_UInt)pBitmap->Width)
        {
            Width=pBitmap->Width;
            Updated=true;
        }
        if(Height!=(spl_UInt)pBitmap->Height)
        {
            Height=pBitmap->Height;
            Updated=true;
        }
        switch(pBitmap->PixelFormat)
        {
            case pf1bit:
            {
                if(Bits!=1)
                {
                    Bits=1;
                    Updated=true;
                }
                break;
            }
            case pf8bit:
            {
                if(Bits!=8)
                {
                    Bits=8;
                    Updated=true;
                }
                break;
            }
            case pf16bit:
            {
                if(Bits!=16)
                {
                    Bits=16;
                    Updated=true;
                }
                break;
            }
            case pf24bit:
            {
                if(Bits!=24)
                {
                    Bits=24;
                    Updated=true;
                }
                break;
            }
            case pf32bit:
            {
                if(Bits!=32)
                {
                    Bits=32;
                    Updated=true;
                }
                break;
            }
            default:
            {
                if(Bits!=1)
                {
                    Bits=1;
                    Updated=true;
                }
                break;
            }
        }

        if(Updated)
        {
            if(Width*Bits % 8 ==0)
                LineSize=Width*Bits/8;
            else
                LineSize=Width*Bits/8+1;
            ImageSize=LineSize*Height;

            DeAllocate();
            Allocate();
        }

        for(spl_UInt y=0;y<Height;y++)
        {
            ppLines[y]=(spl_UByte *)pBitmap->ScanLine[y];
        }
}
//---------------------------------------------------------------------------
void spl_Image::LoadFromFile(AnsiString FileName)
{
    TPicture *pPicture=new TPicture();
    pPicture->LoadFromFile(FileName);
    pBitmap->Assign(pPicture->Graphic);
    UpdateLines();
    if(pPicture)    delete pPicture;pPicture=NULL;
}
//---------------------------------------------------------------------------
void spl_Image::LoadFromFile(AnsiString FileName,TPixelFormat pf)
{
    LoadFromFile(FileName);
    pBitmap->PixelFormat=pf;
    UpdateLines();
}
//---------------------------------------------------------------------------
void spl_Image::SaveToFile(AnsiString FileName)
{
    TPicture *pPicture=new TPicture();
    pPicture->Assign(pBitmap);
    pPicture->SaveToFile(FileName);
    if(pPicture)    delete pPicture;pPicture=NULL;
}
//---------------------------------------------------------------------------
void spl_Image::Assign(spl_Image *pImage)
{
    pBitmap->Assign(pImage->pBitmap);
    UpdateLines();
}
//---------------------------------------------------------------------------
void spl_Image::Assign(spl_Image *pImage,spl_UInt W,spl_UInt H)
{
    pBitmap->Assign(pImage->pBitmap);
    pBitmap->Width=W;
    pBitmap->Height=H;
    UpdateLines();
}                      
//---------------------------------------------------------------------------
void spl_Image::Assign(spl_Image *pImage,TPixelFormat pf)
{
    pBitmap->Assign(pImage->pBitmap);
    pBitmap->PixelFormat=pf;
    UpdateLines();
}
//---------------------------------------------------------------------------
void spl_Image::Assign(spl_Image *pImage,spl_UInt W,spl_UInt H,TPixelFormat pf)
{
    pBitmap->Assign(pImage->pBitmap);
    pBitmap->Width=W;
    pBitmap->Height=H;
    pBitmap->PixelFormat=pf;
    UpdateLines();
}
//---------------------------------------------------------------------------
void spl_Image::Assign(TPersistent *pSource)
{
    pBitmap->Assign(pSource);
    UpdateLines();
}
//---------------------------------------------------------------------------
void spl_Image::SetWidth(spl_UInt W)
{
    pBitmap->Width=W;
    UpdateLines();
}
//---------------------------------------------------------------------------
void spl_Image::SetHeight(spl_UInt H)
{
    pBitmap->Height=H;
    UpdateLines();
}
//---------------------------------------------------------------------------
void spl_Image::SetSize(spl_UInt W,spl_UInt H)
{
    pBitmap->Width=W;
    pBitmap->Height=H;
    UpdateLines();
}
//---------------------------------------------------------------------------
void spl_Image::Clear()
{
    pBitmap->Width=0;
    pBitmap->Height=0;
    UpdateLines();
}
//---------------------------------------------------------------------------
void spl_Image::SetPixelFormat(TPixelFormat pf)
{
    pBitmap->PixelFormat=pf;
    UpdateLines();
}
//---------------------------------------------------------------------------
void spl_Image::SetAll(spl_UInt W,spl_UInt H,TPixelFormat pf)
{
    pBitmap->Width=W;
    pBitmap->Height=H;
    pBitmap->PixelFormat=pf;
    UpdateLines();
}
//---------------------------------------------------------------------------
void spl_Image::SetFrame(spl_UInt W,spl_UInt Color)
{
    pBitmap->Canvas->Pen->Color=TColor(Color);
    pBitmap->Canvas->Pen->Width=W;
    pBitmap->Canvas->Brush->Style=bsClear;

    spl_UInt w2=W/2;
    spl_UInt d=1-W % 2;
    pBitmap->Canvas->Rectangle(0+w2,0+w2,Width+d-w2,Height+d-w2);
}
//---------------------------------------------------------------------------
void spl_Image::AutoFrame(spl_UByte Border,bool MaxMethode)
{
    this->Border=Border;
    if(Border==0)
        return;

    // Auto Frame
    vector<spl_UInt> vColors;// Repeated Colors
    set<spl_UInt> sColors;// Set Of Not Repeated Colors
    vector<spl_UInt> oColors;// Not Repeated Colors
    for(spl_UInt y=0;y<Height;y++)
    {
        vColors.push_back(pBitmap->Canvas->Pixels[0][y]);
        vColors.push_back(pBitmap->Canvas->Pixels[Width-1][y]);
    }
    for(spl_UInt x=0;x<Width;x++)
    {
        vColors.push_back(pBitmap->Canvas->Pixels[x][0]);
        vColors.push_back(pBitmap->Canvas->Pixels[x][Height-1]);
    }
    for(UINT i=0;i<vColors.size();i++)
    {
        sColors.insert(vColors[i]);
    }
    copy(sColors.begin(),sColors.end(),back_inserter(oColors));

    UINT Count;
    if(MaxMethode)
    {
        UINT MaxCount=0,MaxIndex=0;
        for(UINT i=0;i<oColors.size();i++)
        {
            count(vColors.begin(),vColors.end(),oColors[i],Count);
            if(Count>MaxCount)
            {
                MaxCount=Count;
                MaxIndex=i;
            }
        }
        pBitmap->Canvas->Brush->Color=(TColor)oColors[MaxIndex];
    }
    else
    {
        UINT MinCount=MaxInt,MinIndex=MaxInt;
        for(UINT i=0;i<oColors.size();i++)
        {
            count(vColors.begin(),vColors.end(),oColors[i],Count);
            if(Count<MinCount)
            {
                MinCount=Count;
                MinIndex=i;
            }
        }
        pBitmap->Canvas->Brush->Color=(TColor)oColors[MinIndex];
    }

    Graphics::TBitmap *pTemp=new Graphics::TBitmap();
    pTemp->Assign(pBitmap);
    SetSize(Width+2*Border,Height+2*Border);
    pBitmap->Canvas->Brush->Style=bsSolid;
    pBitmap->Canvas->FillRect(Rect(0,0,pBitmap->Width,pBitmap->Height));
    pBitmap->Canvas->Draw(Border,Border,pTemp);
    if(pTemp)
        delete pTemp;
}
//---------------------------------------------------------------------------
void spl_Image::CreateMonochromePalette()
{
    // Create Palette
    LogPal SysPal;
    FillMemory(SysPal.lpal.palPalEntry,256,PC_RESERVED);
    SysPal.lpal.palVersion = 0x300;
    SysPal.lpal.palNumEntries = 2;

    SysPal.lpal.palPalEntry[0].peRed=0;
    SysPal.lpal.palPalEntry[0].peGreen=0;
    SysPal.lpal.palPalEntry[0].peBlue=0;
    SysPal.lpal.palPalEntry[0].peFlags=PC_RESERVED;

    SysPal.lpal.palPalEntry[1].peRed=255;
    SysPal.lpal.palPalEntry[1].peGreen=255;
    SysPal.lpal.palPalEntry[1].peBlue=255;
    SysPal.lpal.palPalEntry[1].peFlags=PC_RESERVED;

    SetPixelFormat(pf8bit);
    pBitmap->Palette=::CreatePalette(&SysPal.lpal);
    UpdateLines();
}
//---------------------------------------------------------------------------

