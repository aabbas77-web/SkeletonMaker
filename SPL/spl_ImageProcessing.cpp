//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_ImageProcessing.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void spl_FlushImage(spl_Image *pImage,DWORD Color)
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
	{
        if(pImage->Bits==32)
		{
			Byte* pPixels;
            Byte i=spl_GetIValue32(Color);
			Byte r=spl_GetRValue32(Color);
			Byte g=spl_GetGValue32(Color);
			Byte b=spl_GetBValue32(Color);
			for(spl_UInt y=0;y<pImage->Height;y++)
			{
				pPixels=pImage->ppLines[y];
				for(spl_UInt x=0;x<pImage->Width;x++)
				{
					*pPixels=i;
					pPixels++;
					*pPixels=b;
					pPixels++;
					*pPixels=g;
					pPixels++;
					*pPixels=r;
					pPixels++;
				}
			}

		}
        else
        if(pImage->Bits==24)
		{
			Byte* pPixels;
			Byte r=GetRValue(Color);
			Byte g=GetGValue(Color);
			Byte b=GetBValue(Color);
			for(spl_UInt y=0;y<pImage->Height;y++)
			{
				pPixels=pImage->ppLines[y];
				for(spl_UInt x=0;x<pImage->Width;x++)
				{
					*pPixels=b;
					pPixels++;
					*pPixels=g;
					pPixels++;
					*pPixels=r;
					pPixels++;
				}
			}

		}
        else
        if(pImage->Bits==16)
		{
			Byte* pPixels;
			Byte L=spl_GetLoByte(Color);
			Byte H=spl_GetHiByte(Color);
			for(spl_UInt y=0;y<pImage->Height;y++)
			{
				pPixels=pImage->ppLines[y];
				for(spl_UInt x=0;x<pImage->Width;x++)
				{
					*pPixels=H;
					pPixels++;
					*pPixels=L;
					pPixels++;
				}
			}

		}
		else
        if(pImage->Bits==8)
		{
            Byte R=Byte(Color);
			for(spl_UInt y=0;y<pImage->Height;y++)
			{
      			memset(pImage->ppLines[y],R,pImage->LineSize);
            }
		}
        else// 1 bit
		{
            Byte R=(bool(Byte(Color))?255:0);
			for(spl_UInt y=0;y<pImage->Height;y++)
			{
      			memset(pImage->ppLines[y],R,pImage->LineSize);
            }
		}
	}
}
//---------------------------------------------------------------------------
void spl_FrameImage(spl_Image *pImage,DWORD Color,spl_UInt Border)
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
	{
        Border=spl_MIN(Border,pImage->Width/2);
        Border=spl_MIN(Border,pImage->Height/2);

        if(pImage->Bits==32)
		{
            Byte i=spl_GetIValue32(Color);
			Byte r=spl_GetRValue32(Color);
			Byte g=spl_GetGValue32(Color);
			Byte b=spl_GetBValue32(Color);
            spl_UInt x=pImage->Width-1;
			for(spl_UInt y=0;y<pImage->Height;y++)
			{
				pImage->ppLines[y][0]=i;
				pImage->ppLines[y][1]=b;
				pImage->ppLines[y][2]=g;
				pImage->ppLines[y][3]=r;

				pImage->ppLines[y][x]=i;
				pImage->ppLines[y][x+1]=b;
				pImage->ppLines[y][x+2]=g;
				pImage->ppLines[y][x+3]=r;
            }
            spl_UInt y=pImage->Height-1;
            for(spl_UInt x=0;x<pImage->Width;x++)
            {
				pImage->ppLines[0][x]=i;
				pImage->ppLines[0][x+1]=b;
				pImage->ppLines[0][x+2]=g;
				pImage->ppLines[0][x+3]=r;

				pImage->ppLines[y][x]=i;
				pImage->ppLines[y][x+1]=b;
				pImage->ppLines[y][x+2]=g;
				pImage->ppLines[y][x+3]=r;
            }
		}
        else
        if(pImage->Bits==24)
		{
			Byte r=GetRValue(Color);
			Byte g=GetGValue(Color);
			Byte b=GetBValue(Color);
            spl_UInt x=pImage->Width-1;
			for(spl_UInt y=0;y<pImage->Height;y++)
			{
				pImage->ppLines[y][0]=b;
				pImage->ppLines[y][1]=g;
				pImage->ppLines[y][2]=r;

				pImage->ppLines[y][x]=b;
				pImage->ppLines[y][x+1]=g;
				pImage->ppLines[y][x+2]=r;
            }
            spl_UInt y=pImage->Height-1;
            for(spl_UInt x=0;x<pImage->Width;x++)
            {
				pImage->ppLines[0][x]=b;
				pImage->ppLines[0][x+1]=g;
				pImage->ppLines[0][x+2]=r;

				pImage->ppLines[y][x]=b;
				pImage->ppLines[y][x+1]=g;
				pImage->ppLines[y][x+2]=r;
            }
		}
        else
        if(pImage->Bits==16)
		{
			Byte L=spl_GetLoByte(Color);
			Byte H=spl_GetHiByte(Color);
            spl_UInt x=pImage->Width-1;
			for(spl_UInt y=0;y<pImage->Height;y++)
			{
				pImage->ppLines[y][0]=H;
				pImage->ppLines[y][1]=L;

				pImage->ppLines[y][x]=H;
				pImage->ppLines[y][x+1]=L;
            }
            spl_UInt y=pImage->Height-1;
            for(spl_UInt x=0;x<pImage->Width;x++)
            {
				pImage->ppLines[0][x]=H;
				pImage->ppLines[0][x+1]=L;

				pImage->ppLines[y][x]=H;
				pImage->ppLines[y][x+1]=L;
            }
		}
		else
        if(pImage->Bits==8)
		{
			Byte r=Byte(Color);
            spl_UInt x,y;
            for(spl_UInt b=0;b<Border;b++)
            {
                x=pImage->Width-1;
    			for(y=0;y<pImage->Height;y++)
    			{
    				pImage->ppLines[y][0+b]=r;
    				pImage->ppLines[y][x-b]=r;
                }
                y=pImage->Height-1;
                for(x=0;x<pImage->Width;x++)
                {
    				pImage->ppLines[0+b][x]=r;
    				pImage->ppLines[y-b][x]=r;
                }
            }
		}
        else// 1 bit
		{
            Byte r=(bool(Byte(Color))?255:0);
            spl_UInt x=pImage->Width-1;
			for(spl_UInt y=0;y<pImage->Height;y++)
			{
                spl_SetPixel_1bit(0,y,r,pImage);
                spl_SetPixel_1bit(x,y,r,pImage);
            }
            spl_UInt y=pImage->Height-1;
            for(spl_UInt x=0;x<pImage->Width;x++)
            {
                spl_SetPixel_1bit(x,0,r,pImage);
                spl_SetPixel_1bit(x,y,r,pImage);
            }
		}
	}
}
//---------------------------------------------------------------------------
void spl_InvertImage(spl_Image *pImage)
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
	{
        Byte* pPixels;
        for(spl_UInt y=0;y<pImage->Height;y++)
        {
            pPixels=pImage->ppLines[y];
            for(spl_UInt x=0;x<pImage->LineSize;x++)
            {
                (*pPixels)=~(*pPixels);
                pPixels++;
            }
        }
	}
}
//---------------------------------------------------------------------------
void spl_SmoothImageColors(spl_Image *pImage,Byte FilterDim,spl_Image *pResult)
{
    pResult->Assign(pImage);

    double r,g,b;
    spl_SInt Dim=FilterDim/2;
    double FilterSize=FilterDim*FilterDim;
    
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
	{
        if(pImage->Bits==24)
		{
            spl_SInt XDim=3*Dim;
			for(spl_UInt y=Dim;y<pImage->Height-Dim;y++)
			{
				for(spl_UInt x=XDim;x<pImage->LineSize-XDim;x+=3)
				{
                    r=g=b=0;
                    for(spl_SInt j=-Dim;j<=Dim;j++)
                    {
                        for(spl_SInt i=-XDim;i<=XDim;i+=3)
                        {
                            b+=pImage->ppLines[y+j][x+i];
                            g+=pImage->ppLines[y+j][x+i+1];
                            r+=pImage->ppLines[y+j][x+i+2];
                        }
                    }
                    pResult->ppLines[y][x]=b/FilterSize;
                    pResult->ppLines[y][x+1]=g/FilterSize;
                    pResult->ppLines[y][x+2]=r/FilterSize;
				}
			}
		}
        else
        if(pImage->Bits==8)
		{
            spl_SmoothDigitizedImageColors(pImage,spl_ColorsCount,FilterDim);
		}
        else// 1 bit
		{
            double FilterSize2=FilterSize/2.0;
			for(spl_UInt y=Dim;y<pImage->Height-Dim;y++)
			{
				for(spl_UInt x=Dim;x<pImage->Width-Dim;x++)
				{
                    r=0;
                    for(spl_SInt j=-Dim;j<=Dim;j++)
                    {
                        for(spl_SInt i=-Dim;i<=Dim;i++)
                        {
                            r+=spl_GetPixel_1bit(x+i,y+j,pImage);
                        }
                    }
                    spl_SetPixel_1bit(x,y,((r>=FilterSize2)?1:0),pResult);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void spl_SmoothDigitizedImageColors(spl_Image *pIndices,int ColorsCount,Byte FilterDim)
{
    if(ColorsCount<=0)
    {
        return;
    }
    else
	if(pIndices==NULL)
	{
		return;
	}
	else
    if(pIndices->ppLines==NULL)
	{
        MessageBox(0,"Invalid Image (You Must Call <UpdateLines> Before This Operation)","Error",0);
		return;
	}
	else
	{
        spl_Image *pResult=new spl_Image();
        pResult->Assign(pIndices);

        spl_SInt Dim=FilterDim/2;
        Byte *Indices=new Byte[ColorsCount];
        Byte Index,MaxIndex,MaxFreq;

        for(spl_UInt y=Dim;y<pIndices->Height-Dim;y++)
        {
            for(spl_UInt x=Dim;x<pIndices->Width-Dim;x++)
            {
                ZeroMemory(Indices,ColorsCount);
                for(spl_SInt j=-Dim;j<=Dim;j++)
                {
                    for(spl_SInt i=-Dim;i<=Dim;i++)
                    {
                        Index=pIndices->ppLines[y+j][x+i];
                        if(Index<ColorsCount)
                            Indices[Index]++;
                    }
                }

                MaxFreq=0;
                MaxIndex=0;
                for(spl_UByte i=0;i<ColorsCount;i++)
                {
                    if(Indices[i]>MaxFreq)
                    {
                        MaxFreq=Indices[i];
                        MaxIndex=i;
                    }
                }
                pResult->ppLines[y][x]=MaxIndex;
            }
        }

        pIndices->Assign(pResult);

        if(Indices)
            delete[] Indices;
        if(pResult)
            delete pResult;
	}
}
//---------------------------------------------------------------------------
void spl_ErosionDigitizedImageColors(spl_Image *pIndices,Byte FilterDim)
{
    if(spl_ColorsCount<=0)
    {
        return;
    }
    else
	if(pIndices==NULL)
	{
		return;
	}
	else
    if(pIndices->ppLines==NULL)
	{
        MessageBox(0,"Invalid Image (You Must Call <UpdateLines> Before This Operation)","Error",0);
		return;
	}
	else
	{
        spl_Image *pResult=new spl_Image();
        pResult->Assign(pIndices);

        spl_SInt Dim=FilterDim/2;
        Byte *Indices=new Byte[spl_ColorsCount];
        Byte Index,MinIndex,MinFreq;

        for(spl_UInt y=Dim;y<pIndices->Height-Dim;y++)
        {
            for(spl_UInt x=Dim;x<pIndices->Width-Dim;x++)
            {
                ZeroMemory(Indices,spl_ColorsCount);
                for(spl_SInt j=-Dim;j<=Dim;j++)
                {
                    for(spl_SInt i=-Dim;i<=Dim;i++)
                    {
                        Index=pIndices->ppLines[y+j][x+i];
                        if(Index<spl_ColorsCount)
                            Indices[Index]++;
                    }
                }

                MinFreq=255;
                MinIndex=0;
                for(spl_UByte i=0;i<spl_ColorsCount;i++)
                {
                    if(Indices[i]<MinFreq)
                    {
                        MinFreq=Indices[i];
                        MinIndex=i;
                    }
                }
                pResult->ppLines[y][x]=MinIndex;
            }
        }

        pIndices->Assign(pResult);

        if(Indices)
            delete[] Indices;
        if(pResult)
            delete pResult;
	}
}
//---------------------------------------------------------------------------
void spl_DilationDigitizedImageColors(spl_Image *pIndices,Byte FilterDim)
{
    if(spl_ColorsCount<=0)
    {
        return;
    }
    else
	if(pIndices==NULL)
	{
		return;
	}
	else
    if(pIndices->ppLines==NULL)
	{
        MessageBox(0,"Invalid Image (You Must Call <UpdateLines> Before This Operation)","Error",0);
		return;
	}
	else
	{
        spl_Image *pResult=new spl_Image();
        pResult->Assign(pIndices);

        spl_SInt Dim=FilterDim/2;
        Byte *Indices=new Byte[spl_ColorsCount];
        Byte Index,MaxIndex,MaxFreq;

        for(spl_UInt y=Dim;y<pIndices->Height-Dim;y++)
        {
            for(spl_UInt x=Dim;x<pIndices->Width-Dim;x++)
            {
                ZeroMemory(Indices,spl_ColorsCount);
                for(spl_SInt j=-Dim;j<=Dim;j++)
                {
                    for(spl_SInt i=-Dim;i<=Dim;i++)
                    {
                        Index=pIndices->ppLines[y+j][x+i];
                        if(Index<spl_ColorsCount)
                            Indices[Index]++;
                    }
                }

                MaxFreq=0;
                MaxIndex=0;
                for(spl_UByte i=0;i<spl_ColorsCount;i++)
                {
                    if(Indices[i]>MaxFreq)
                    {
                        MaxFreq=Indices[i];
                        MaxIndex=i;
                    }
                }
                pResult->ppLines[y][x]=MaxIndex;
            }
        }

        pIndices->Assign(pResult);

        if(Indices)
            delete[] Indices;
        if(pResult)
            delete pResult;
	}
}
//---------------------------------------------------------------------------
void spl_IsolateWords(spl_Image *pIndices,Byte nWordColorIndex,int nRadius)
{
    if(spl_ColorsCount<=0)
    {
        return;
    }
    else
	if(pIndices==NULL)
	{
		return;
	}
	else
    if(pIndices->ppLines==NULL)
	{
        MessageBox(0,"Invalid Image (You Must Call <UpdateLines> Before This Operation)","Error",0);
		return;
	}
	else
	{
        spl_Image *pResult=new spl_Image();
        pResult->Assign(pIndices);
        bool bIsEdge;
        Byte Index;
	    TColor RGBColor = (TColor)spl_QuantizedColors[nWordColorIndex];
        pResult->pBitmap->Canvas->Pen->Color = RGBColor;
        pResult->pBitmap->Canvas->Brush->Color = RGBColor;
        pResult->pBitmap->Canvas->Brush->Style = bsSolid;

        for(spl_UInt y=nRadius;y<pIndices->Height-nRadius;y++)
        {
            for(spl_UInt x=nRadius;x<pIndices->Width-nRadius;x++)
            {
            	Index=pIndices->ppLines[y][x];
                if(Index == nWordColorIndex)
                {
                    bIsEdge = false;
                    for(int i=0;i<8;i++)
                    {
                        Index=pIndices->ppLines[y+spl_T1[i].y][x+spl_T1[i].x];
                        if(Index != nWordColorIndex)
                        {
                        	bIsEdge = true;
                         	break;
                        }
                    }
                    if(bIsEdge)
                    {
						pResult->pBitmap->Canvas->Ellipse(x-nRadius,y-nRadius,x+nRadius,y+nRadius);
                    }
                }
            }
        }
        pIndices->Assign(pResult);
        if(pResult)	delete pResult;
	}
}
//---------------------------------------------------------------------------
void spl_ConvertToGray(spl_Image *pImage,Byte Methode,spl_Image *pResult)
{
    pResult->Assign(pImage);
    pResult->SetPixelFormat(pf24bit);

    spl_UByte m;
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
	{
        for(spl_UInt y=0;y<pImage->Height;y++)
        {
            for(spl_UInt x=0;x<pImage->LineSize;x+=3)
            {
                switch(Methode)
                {
                    case gmArtificial:// Artificial
                    {
                        m=(pImage->ppLines[y][x  ]+pImage->ppLines[y][x+1]+pImage->ppLines[y][x+2])/3.0;
                        break;
                    }
                    case gmRed:// Red
                    {
                        m=pImage->ppLines[y][x+2];
                        break;
                    }
                    case gmGreen:// Green
                    {
                        m=pImage->ppLines[y][x+1];
                        break;
                    }
                    case gmBlue:// Blue
                    {
                        m=pImage->ppLines[y][x  ];
                        break;
                    }
                    default:
                    {
                        m=0.299*pImage->ppLines[y][x+2]+
                          0.587*pImage->ppLines[y][x+1]+
                          0.114*pImage->ppLines[y][x  ];
                        break;
                    }
                }
                pResult->ppLines[y][x]=pResult->ppLines[y][x+1]=pResult->ppLines[y][x+2]=m;
            }
        }
	}
}
//---------------------------------------------------------------------------
void spl_ReverseImage(spl_Image *pImage,spl_Image *pResult)
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
	{
        pResult->Assign(pImage);
        for(spl_UInt y=0;y<pImage->Height;y++)
        {
            CopyMemory(pResult->ppLines[y],pImage->ppLines[pImage->Height-1-y],pImage->LineSize);
        }
	}
}
//---------------------------------------------------------------------------
spl_UByte spl_FisherTow(spl_Histogram hist)
{
    Byte h,k;
    Byte Threshold;
    double s,sc1=0,sd1=0,sc2=0,sd2=0;
    double max=(double)(-MaxInt);
    for(h=2;h<254;h++)
    {
        for(k=0;k<h;k++)
        {
            sc1+=k*hist[k];
            sd1+=hist[k];
        }
        for(k=h;k<255;k++)
        {
            sc2+=k*hist[k];
            sd2+=hist[k];
        }
        s=sc1*sc1/(sd1+0.0001);
        s+=sc2*sc2/(sd2+0.0001);
        if(s>max)
        {
            max=s;
            Threshold=h;
        }
        sc1=sc2=sd1=sd2=0.0;
    }
    return Threshold;
}
//---------------------------------------------------------------------------
void spl_LogHistogram(spl_Histogram hist,spl_LHistogram lhst)
{
    for(int i=0;i<256;i++)
    {
        if(hist[i]>0)
            lhst[i]=log(hist[i]);
        else
            lhst[i]=0.0;
    }
}
//---------------------------------------------------------------------------
spl_UByte spl_EntropyTow(spl_Histogram hst,double *lhst)
{
    spl_UByte i,k;
    spl_UByte Threshold;
    double Shk1=0.0,Shk2=0.0,max=(double)(-MaxInt);
    double Nk1=0.0,Nk2=0.0,sum;
    for(i=2;i<254;i++)
    {
        for(k=0;k<i;k++)
        {
            Shk1+=hst[k]*lhst[k];
            Nk1+=hst[k];
        }
        for(k=i;k<255;k++)
        {
            Shk2+=hst[k]*lhst[k];
            Nk2+=hst[k];
        }
        sum=-Shk1/(Nk1+0.01)-Shk2/(Nk2+0.01)+log(Nk1*Nk2+1);
        if(sum >max)
        {
            max=sum;
            Threshold=i;
        }
        Shk1=Shk2=Nk1=Nk2=sum=0.0;
    }
    return Threshold;
}
//---------------------------------------------------------------------------
spl_UByte spl_EntropyTow(spl_Histogram Histogram)
{
    spl_LHistogram LHistogram;
    spl_LogHistogram(Histogram,LHistogram);
    spl_UByte Threshold=spl_EntropyTow(Histogram,LHistogram);
    return Threshold;
}
//---------------------------------------------------------------------------
void spl_Monochrome(spl_Image *pImage,spl_UByte Threshold,spl_Image *pResult)
{
    pResult->Assign(pImage);
    pResult->SetPixelFormat(pf24bit);

    spl_UByte m;
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
	{
        for(spl_UInt y=0;y<pImage->Height;y++)
        {
            for(spl_UInt x=0;x<pImage->LineSize;x+=3)
            {
                if(pImage->ppLines[y][x] < Threshold)
                {
                    m=0;
                }
                else
                {
                    m=255;
                }
                pResult->ppLines[y][x]=pResult->ppLines[y][x+1]=pResult->ppLines[y][x+2]=m;
            }
        }
	}
}
//---------------------------------------------------------------------------
void spl_Monochrome8bit(spl_Image *pImage,spl_UByte Threshold,spl_Image *pResult)
{
    pResult->Assign(pImage);
    pResult->SetPixelFormat(pf8bit);

    spl_UByte m;
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
	{
        for(spl_UInt y=0;y<pImage->Height;y++)
        {
            for(spl_UInt x=0;x<pImage->Width;x++)
            {
                if(pImage->ppLines[y][x] < Threshold)
                {
                    m=0;
                }
                else
                {
                    m=255;
                }
                pResult->ppLines[y][x]=m;
            }
        }
	}
}
//---------------------------------------------------------------------------
void spl_GetHistogram(spl_Image *pImage,spl_Histogram Histogram)
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
	{
        ZeroMemory(Histogram,256*sizeof(spl_UInt));
        for(spl_UInt y=0;y<pImage->Height;y++)
        {
            for(spl_UInt x=0;x<pImage->LineSize;x+=3)
            {
                Histogram[pImage->ppLines[y][x]]++;
            }
        }
	}
}
//---------------------------------------------------------------------------
void spl_Halftone(spl_Image *pImage,spl_UByte ElementType,bool bNormalMethode,HDC hdc)
{
    pImage->SetPixelFormat(pf8bit);

    double dGrid = 10;
    double dR,dD;
    double dSum;
    int X,Y;
    int N;
    spl_UByte MinC,MaxC;
    double a,b;
    MinC = 0;
    MaxC = 255;
    TCanvas *pCanvas = new TCanvas();
    pCanvas->Handle = hdc;
    pCanvas->Brush->Style = bsSolid;
//    pCanvas->Brush->Style = bsDiagCross;
    pCanvas->Brush->Color = clBlack;
    pCanvas->Pen->Style = psSolid;
    pCanvas->Pen->Color = clBlack;
	if(pImage==NULL)
	{
    	if(pCanvas)
        {
    		pCanvas->Handle = 0;
         	delete pCanvas;
            pCanvas = NULL;
        }
		return;
	}
	else
    if(pImage->ppLines==NULL)
	{
    	if(pCanvas)
        {
    		pCanvas->Handle = 0;
         	delete pCanvas;
            pCanvas = NULL;
        }
        MessageBox(0,"Invalid Image (You Must Call <UpdateLines> Before This Operation)","Error",0);
		return;
	}
	else
	{
        for(spl_UInt y=0;y<pImage->Height-dGrid;y+=dGrid)
        {
            for(spl_UInt x=0;x<pImage->Width-dGrid;x+=dGrid)
            {
            	dSum = 0.0;
            	for(spl_UInt i=x;i<x+dGrid;i++)
                {
                    for(spl_UInt j=y;j<y+dGrid;j++)
                    {
						dSum += pImage->ppLines[j][i];
                    }
                }
                
				a = -1.0/(2.0*dGrid*(MaxC-MinC));
                b = (MaxC*dGrid)/(2.0*(MaxC-MinC));
				dR = a*dSum+b;
                if(dR <= 1.0)	continue;
                dD = 2.0*dR;
                X = x;
                Y = y;
                N = dGrid/dD;
                switch(ElementType)
                {
                 	case etEllipse:
                    {
                    	if(bNormalMethode)
                        {
                        	pCanvas->Ellipse(X,Y,X+dD,Y+dD);
                        }
                        else
                        {
                            if(dR <= 2.0)
                            {
                                pCanvas->Ellipse(X,Y,X+dD,Y+dD);
                            }
                            else
                            {
                                for(int i=0;i<N;i++)
                                {
                                    for(int j=0;j<N;j++)
                                    {
                                        pCanvas->Ellipse(X+i*dD+1,Y+j*dD+1,X+(i+1)*dD,Y+(j+1)*dD);
                                    }
                                }
                            }
                        }
                     	break;
                    }
                 	case etRectangle:
                    {
                    	if(bNormalMethode)
                        {
                        	pCanvas->Rectangle(X,Y,X+dD,Y+dD);
                        }
                        else
                        {
                            if(dR <= 2.0)
                            {
                                pCanvas->Rectangle(X,Y,X+dD,Y+dD);
                            }
                            else
                            {
                                for(int i=0;i<N;i++)
                                {
                                    for(int j=0;j<N;j++)
                                    {
                                        pCanvas->Rectangle(X+i*dD+1,Y+j*dD+1,X+(i+1)*dD,Y+(j+1)*dD);
                                    }
                                }
                            }
                        }
                     	break;
                    }
                }
            }
        }
	}
    if(pCanvas)
    {
    	pCanvas->Handle = 0;
        delete pCanvas;
        pCanvas = NULL;
    }
}
//---------------------------------------------------------------------------
void spl_Halftone(spl_Image *pImage,spl_UByte ElementType,bool bNormalMethode,spl_Image *pResult)
{
    pResult->Assign(pImage);
    pResult->SetPixelFormat(pf24bit);
    spl_FlushImage(pResult,clWhite);
//	spl_Halftone(pImage,ElementType,bNormalMethode,pResult->pBitmap->Canvas->Handle);
	spl_Halftone_New(pImage,ElementType,bNormalMethode,pResult->pBitmap->Canvas->Handle);
/*
    pResult->SetPixelFormat(pf8bit);
	pResult->pBitmap->Palette = CreateHalftonePalette(pResult->pBitmap->Canvas->Handle);
    pResult->pBitmap->Canvas->StretchDraw
    pResult->pBitmap->Canvas->Draw(0,0,pImage->pBitmap);
*/
/*
 	HPALETTE  hpal;
    hpal = CreateHalftonePalette(pResult->pBitmap->Canvas->Handle);
    SelectPalette(pResult->pBitmap->Canvas->Handle, hpal, 0);
    RealizePalette(pResult->pBitmap->Canvas->Handle);

//    pResult->pBitmap->Canvas->Draw(0,0,pImage->pBitmap);
    pResult->pBitmap->Monochrome = true;
    pResult->SetPixelFormat(pf1bit);
    pResult->pBitmap->Canvas->StretchDraw(Rect(0,0,pResult->Width+400,pResult->Height+400),pImage->pBitmap);
*/
}
//---------------------------------------------------------------------------
void spl_Halftone_New(spl_Image *pImage,spl_UByte ElementType,bool bNormalMethode,HDC hdc)
{
    spl_Image *pMask = new spl_Image();
    TCanvas *pCanvas = new TCanvas();
	if(pImage==NULL)
	{
    	if(pCanvas)
        {
    		pCanvas->Handle = 0;
         	delete pCanvas;
            pCanvas = NULL;
        }
        if(pMask)
        {
         	delete pMask;
            pMask = NULL;
        }
		return;
	}
	else
    if(pImage->ppLines==NULL)
	{
    	if(pCanvas)
        {
    		pCanvas->Handle = 0;
         	delete pCanvas;
            pCanvas = NULL;
        }
        if(pMask)
        {
         	delete pMask;
            pMask = NULL;
        }
        MessageBox(0,"Invalid Image (You Must Call <UpdateLines> Before This Operation)","Error",0);
		return;
	}
	else
	{
    	int nLevelsCount = 10;
        int nLevelsStep = 255.0/nLevelsCount;
        int nMinLevel,nMaxLevel;
        int nFilterDim;
        double dGrid;
        double dSum;
        pCanvas->Handle = hdc;
        pCanvas->Brush->Style = bsSolid;
        pCanvas->Brush->Color = clBlack;
        pCanvas->Pen->Style = psSolid;
        pCanvas->Pen->Color = clBlack;

    	pImage->SetPixelFormat(pf8bit);
        
        pMask->Assign(pImage);
        pMask->CreateMonochromePalette();

        for(int nLevel=0;nLevel<nLevelsCount;nLevel++)
        {
        	nMinLevel = nLevel*nLevelsStep;
        	nMaxLevel = (nLevel+1)*nLevelsStep;
//            dGrid = 3+1.0*(nLevelsCount - 1 - nLevel);
            dGrid = 1.0*(nLevelsCount - 1 - nLevel);
            if(dGrid <= 2)	continue;
            spl_FlushImage(pMask,1);
            for(spl_UInt y=0;y<pImage->Height;y++)
            {
                for(spl_UInt x=0;x<pImage->Width;x++)
                {
					if((pImage->ppLines[y][x] >= nMinLevel) && (pImage->ppLines[y][x] <= nMaxLevel))
                    {
               			pMask->ppLines[y][x] = 0;
                    }
                }
            }
            pMask->SaveToFile("c:\\test\\"+FormatFloat("test00",nLevel)+".bmp");
//            spl_SmoothDigitizedImageColors(pMask,2,7);
//            pMask->SaveToFile("c:\\test\\"+FormatFloat("Smooth00",nLevel)+".bmp");

            for(spl_UInt y=0;y<pMask->Height-dGrid;y+=dGrid)
            {
                for(spl_UInt x=0;x<pMask->Width-dGrid;x+=dGrid)
                {
                    dSum = 0.0;
                    for(spl_UInt i=x;i<x+dGrid;i++)
                    {
                        for(spl_UInt j=y;j<y+dGrid;j++)
                        {
                            dSum += pMask->ppLines[j][i];
                        }
                    }
                    if(dSum <= dGrid*dGrid/2.0)
                    {
                    	pCanvas->Ellipse(x,y,x+dGrid,y+dGrid);
//                    	pCanvas->Rectangle(x,y,x+dGrid,y+dGrid);

                        pImage->pBitmap->Canvas->Brush->Style = bsSolid;
                        pImage->pBitmap->Canvas->Brush->Color = clWhite;
                        pImage->pBitmap->Canvas->Pen->Style = psSolid;
                        pImage->pBitmap->Canvas->Pen->Color = clWhite;
                        pImage->pBitmap->Canvas->Rectangle(x,y,x+dGrid,y+dGrid);
                    }
                }
            }
            pImage->SaveToFile("c:\\test\\"+FormatFloat("Image00",nLevel)+".bmp");
        }
	}
    if(pCanvas)
    {
    	pCanvas->Handle = 0;
        delete pCanvas;
        pCanvas = NULL;
    }
    if(pMask)
    {
     	delete pMask;
        pMask = NULL;
    }
}
//---------------------------------------------------------------------------

