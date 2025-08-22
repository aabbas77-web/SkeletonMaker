//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_ALICompression.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
static TPoint T1[9]={
                Point(+1,00),// 0
                Point(+1,+1),// 1
                Point(00,+1),// 2
                Point(-1,+1),// 3
                Point(-1,00),// 4
                Point(-1,-1),// 5
                Point(00,-1),// 6
                Point(+1,-1),// 7
                Point(00,00),// 8
             };
//---------------------------------------------------------------------------
BYTE _GetDirection(spl_Point *P1,spl_Point *P2)
{
    int dx=(P2->x-P1->x);
    int dy=(P2->y-P1->y);
    int Dir=0;
    if(dx==0)
    {
        if(dy==0)
        {
            Dir=8;
        }
        else
        if(dy>0)
        {
            Dir=2;
        }
        else
        {
            Dir=6;
        }
    }
    else
    if(dx>0)
    {
        if(dy==0)
        {
            Dir=0;
        }
        else
        if(dy>0)
        {
            Dir=1;
        }
        else
        {
            Dir=7;
        }
    }
    else
    {
        if(dy==0)
        {
            Dir=4;
        }
        else
        if(dy>0)
        {
            Dir=3;
        }
        else
        {
            Dir=5;
        }
    }
    return Dir;
}
//---------------------------------------------------------------------------
void spl_ALICompress(spl_Image *pImage,int ColorsCount,TMemoryStream *pStream)
{
    spl_MultiLayer MultiLayer;
    int Degree=1;
    int Order=4;
    spl_QuantizeImageColors(pImage,ColorsCount,0);
//    spl_SmoothDigitizedImageColors(pImage,5);
    spl_ExtractDigitizedContoursForProcessing(pImage,true,Order,Degree,MultiLayer);

    pStream->Clear();

    // Define Header
    spl_ALICompressionHeader Header;
    Header.Width=pImage->Width;
    Header.Height=pImage->Height;
    Header.ColorsCount=ColorsCount;

    // Write Header
    pStream->Write(&Header,sizeof(Header));

    DWORD Color;
    WORD LayersCount;
    WORD RegionsCount;
    WORD ContoursCount;
    WORD PointsCount;
    WORD X,Y;
    spl_Point P;

    // Layers Count
    LayersCount=MultiLayer.Layers.size();
    pStream->Write(&LayersCount,sizeof(LayersCount));

    for(UINT iLayer=0;iLayer<MultiLayer.Layers.size();iLayer++)
    {
        // Color
        Color=MultiLayer.Layers[iLayer].Regions[0].FillColor;
        pStream->Write(&Color,sizeof(Color));

        // Regions Count
        RegionsCount=MultiLayer.Layers[iLayer].Regions.size();
        pStream->Write(&RegionsCount,sizeof(RegionsCount));

        for(UINT iRegion=0;iRegion<MultiLayer.Layers[iLayer].Regions.size();iRegion++)
        {
            // Contours Count
//            ContoursCount=MultiLayer.Layers[iLayer].Regions[iRegion].Contours.size();
            ContoursCount=1;
            pStream->Write(&ContoursCount,sizeof(ContoursCount));

            for(int iContour=0;iContour<ContoursCount;iContour++)
            {
                // Points Count
                PointsCount=MultiLayer.Layers[iLayer].Regions[iRegion].Contours[iContour].Points.size();
                pStream->Write(&PointsCount,sizeof(PointsCount));

                for(UINT iPoint=0;iPoint<MultiLayer.Layers[iLayer].Regions[iRegion].Contours[iContour].Points.size();iPoint++)
                {
                    P=MultiLayer.Layers[iLayer].Regions[iRegion].Contours[iContour].Points[iPoint];
                    X=P.x;
                    Y=P.y;
                    pStream->Write(&X,sizeof(X));
                    pStream->Write(&Y,sizeof(Y));
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void spl_ALIDeCompress(TMemoryStream *pStream,spl_Image *pImage)
{
    // Checking Input
    if(!pImage)  return;
    if(!pStream)    return;

    // Initialization
    pStream->Position=0;

    // Read Header
    spl_ALICompressionHeader Header;
    pStream->Read(&Header,sizeof(Header));
//    pImage->SetAll(Header.Width,Header.Height,pf8bit);
//    spl_FlushImage(pImage,spl_BackgroundIndex);
    pImage->SetAll(Header.Width,Header.Height,pf24bit);
    spl_FlushImage(pImage,clWhite);

    DWORD Color;
    WORD LayersCount;
    WORD RegionsCount;
    WORD ContoursCount;
    WORD PointsCount;
    WORD X,Y;
    spl_Point P;

    // Layers Count
    pStream->Read(&LayersCount,sizeof(LayersCount));

    for(int iLayer=0;iLayer<LayersCount;iLayer++)
    {
        // Color
        pStream->Read(&Color,sizeof(Color));

        // Regions Count
        pStream->Read(&RegionsCount,sizeof(RegionsCount));

        for(int iRegion=0;iRegion<RegionsCount;iRegion++)
        {
            // Contours Count
            pStream->Read(&ContoursCount,sizeof(ContoursCount));

            for(int iContour=0;iContour<ContoursCount;iContour++)
            {
                // Points Count
                pStream->Read(&PointsCount,sizeof(PointsCount));

                spl_Contour Contour;
                for(int iPoint=0;iPoint<PointsCount;iPoint++)
                {
                    pStream->Read(&X,sizeof(X));
                    pStream->Read(&Y,sizeof(Y));
                    P.x=X;
                    P.y=Y;
                    Contour.Points.push_back(P);
                }
                pImage->pBitmap->Canvas->Pen->Color=TColor(Color);
                pImage->pBitmap->Canvas->Brush->Color=TColor(Color);
                pImage->pBitmap->Canvas->Brush->Style=bsSolid;
                spl_DrawPolygonContour(pImage->pBitmap->Canvas->Handle,Contour);
            }
        }
    }
}
//---------------------------------------------------------------------------
/*
static TPoint T1[9]={
                Point(00,00),// 0
                Point(+1,00),// 1
                Point(+1,+1),// 2
                Point(00,+1),// 3
                Point(-1,+1),// 4
                Point(-1,00),// 5
                Point(-1,-1),// 6
                Point(00,-1),// 7
                Point(+1,-1),// 8
             };
//---------------------------------------------------------------------------
BYTE _GetDirection(TPoint *P1,TPoint *P2)
{
    int dx=(P2->x-P1->x);
    int dy=(P2->y-P1->y);
    int Dir=0;
    if(dx==0)
    {
        if(dy==0)
        {
            Dir=0;
        }
        else
        if(dy>0)
        {
            Dir=3;
        }
        else
        {
            Dir=7;
        }
    }
    else
    if(dx>0)
    {
        if(dy==0)
        {
            Dir=1;
        }
        else
        if(dy>0)
        {
            Dir=2;
        }
        else
        {
            Dir=8;
        }
    }
    else
    {
        if(dy==0)
        {
            Dir=5;
        }
        else
        if(dy>0)
        {
            Dir=4;
        }
        else
        {
            Dir=6;
        }
    }
    return Dir;
}
//---------------------------------------------------------------------------
void spl_ExtractDigitizedRegionNormal(int x,int y)
{
    if((x<0)||(x>=_pImage->Width)||(y<0)||(y>=_pImage->Height)) return;
    if(_pImage->ppLines[y][x]==_OldColor)
    {
        _pImage->ppLines[y][x]=_NewColor;
        _P=Point(x,y);
        _Dir=_GetDirection(&_PrevP,&_P);
        _PrevP=_P;
        _pContour->push_back(_Dir);
        if(_pContour->size()>=128)   return;

        spl_ExtractDigitizedRegionNormal(x+1,y+0);
//        spl_ExtractDigitizedRegionNormal(x+1,y+1);
//        spl_ExtractDigitizedRegionNormal(x+0,y+1);
//        spl_ExtractDigitizedRegionNormal(x-1,y+1);
//        spl_ExtractDigitizedRegionNormal(x-1,y+0);
//        spl_ExtractDigitizedRegionNormal(x-1,y-1);
//        spl_ExtractDigitizedRegionNormal(x+0,y-1);
//        spl_ExtractDigitizedRegionNormal(x+1,y-1);
    }
}
//---------------------------------------------------------------------------
void spl_ExtractDigitizedRegionNormal(spl_Image *pImage,int x,int y,Byte NewColor,vector<BYTE> &Contour)
{
    _pImage=pImage;
    _OldColor=pImage->ppLines[y][x];
    _NewColor=NewColor;
    _pContour=&Contour;
    _PrevP=Point(x,y);
    spl_ExtractDigitizedRegionNormal(x,y);
}
//---------------------------------------------------------------------------
void spl_ALICompress(spl_Image *pImage,int ColorsCount,TMemoryStream *pStream)
{
    // Checking Input
    if(!pImage)  return;
    if(!pImage->ppLines) return;
    if(!pStream)    return;

    // Initialization
//    spl_Image *pTemp=new spl_Image();
//    pTemp->Assign(pImage);
    spl_Image *pTemp=pImage;
    spl_Bits *pBits=new spl_Bits();
    pStream->Clear();

    // Define Header
    spl_ALICompressionHeader Header;
    Header.Width=pImage->Width;
    Header.Height=pImage->Height;
    Header.ColorsCount=ColorsCount;

    // Write Header
    pStream->Write(&Header,sizeof(Header));

    // First Scan
    BYTE ColorIndex;
    BYTE BufferSize;
    int BitIndex;
    for(int y=0;y<pTemp->Height;y++)
    {
        for(int x=0;x<pTemp->Width;x++)
        {
            ColorIndex=pTemp->ppLines[y][x];
            if(ColorIndex!=spl_BackgroundIndex)
            {
                vector<BYTE> Contour;
                spl_ExtractDigitizedRegionNormal(pTemp,x,y,spl_BackgroundIndex,Contour);
//                Contour.push_back(0);// Demo
                if(!Contour.empty())
                {
                    // Reserve Memory
                    pBits->Size=Contour.size()*4;
                    ZeroMemory(pBits->Buffer,pBits->BufferSize);

                    // Color Index
                    pStream->Write(&ColorIndex,sizeof(ColorIndex));

                    // Points Buffer Size (In Bytes)
                    BufferSize=pBits->BufferSize;
                    pStream->Write(&BufferSize,sizeof(BufferSize));

                    // Points Buffer (In Bytes)
                    BitIndex=0;
                    for(UINT i=0;i<Contour.size();i++)
                    {
                        pBits->Write(BitIndex,4,Contour[i]);
                        BitIndex+=4;
                    }

                    // Write This Region
                    pStream->Write(pBits->Buffer,pBits->BufferSize);
                }
            }
        }
    }


    // Finalization
    if(pBits)   delete  pBits;
//    if(pTemp)   delete  pTemp;
}
//---------------------------------------------------------------------------
void spl_ALIDeCompress(TMemoryStream *pStream,spl_Image *pImage)
{
    // Checking Input
    if(!pImage)  return;
    if(!pStream)    return;

    // Initialization
    spl_Bits *pBits=new spl_Bits();
    pStream->Position=0;

    // Read Header
    spl_ALICompressionHeader Header;
    pStream->Read(&Header,sizeof(Header));
    pImage->SetAll(Header.Width,Header.Height,pf8bit);
    spl_FlushImage(pImage,spl_BackgroundIndex);

    BYTE ColorIndex;
    BYTE BufferSize;
    int BytesRead;
    BYTE Dir;
    TPoint P,PrevP;

    PrevP=Point(0,0);
    while(true)
    {
        // Color Index
        BytesRead=pStream->Read(&ColorIndex,sizeof(ColorIndex));
        if(BytesRead==0)    break;

        // Points Buffer Size (In Bytes)
        BytesRead=pStream->Read(&BufferSize,sizeof(BufferSize));
        if(BytesRead==0)    break;
        pBits->Size=BufferSize * 8;
        ZeroMemory(pBits->Buffer,pBits->BufferSize);

        // Read This Region
        BytesRead=pStream->Read(pBits->Buffer,BufferSize);
        if(BytesRead==0)    break;

        P=PrevP;
        for(int i=0;i<pBits->Size;i+=4)
        {
            Dir=pBits->Read(i,4);
            P.x+=T1[Dir].x;
            P.y+=T1[Dir].y;
            if((P.x>=0)&&(P.x<pImage->Width)&&(P.y>=0)&&(P.y<pImage->Height))
                pImage->ppLines[P.y][P.x]=ColorIndex;
        }
        while(true)
        {
            if(pImage->ppLines[PrevP.y][PrevP.x]==spl_BackgroundIndex)  break;
            PrevP.x++;
            if(PrevP.x>=Header.Width-2)
            {
                PrevP.x=0;
                PrevP.y++;
                if(PrevP.y>=Header.Height) goto LEnd;
            }
        }
    }

    LEnd:;
    // Finalization
    if(pBits)   delete  pBits;
}
//---------------------------------------------------------------------------
*/
