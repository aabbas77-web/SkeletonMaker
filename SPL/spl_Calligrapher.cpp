//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_Calligrapher.h"
#include "cad_Display.h"
#include "api_VecApi.h"
//#include "spl_InsertText.h"
//#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*
int spl_GetArabicOffset(HDC hdc)
{
    AnsiString Text = 'Ú';// 0xFEC9
	UINT Count = Text.Length();
 	wchar_t *Glyphs=new wchar_t[Count];

 	spl_ConvertToArabic(hdc,Text,Glyphs,NULL,NULL,Count);
	int nOffset = 0xFEC9 - Glyphs[0];

 	if(Glyphs)	delete[] Glyphs;
    return nOffset;
}
*/
//---------------------------------------------------------------------------
/*
void spl_ConvertToArabic(HDC hdc,AnsiString Text,UINT *Indices,UINT *Orders,int *pDx,UINT &Count)
{
	TEXTMETRIC TextMetrics;
    GetTextMetrics(hdc,&TextMetrics);
    UINT nOffset = 0;

    switch(TextMetrics.tmCharSet)
    {
    	case ARABIC_CHARSET:
        {
        	nOffset = spl_GetArabicOffset(hdc);
         	break;
        }
    }

	Count = Text.Length();
 	wchar_t *Glyphs=new wchar_t[Count];

 	spl_ConvertToArabic(hdc,Text,Glyphs,Orders,pDx,Count);

 	for(UINT i=0;i<Count;i++)
 	{
    	Indices[i] = nOffset + DWORD(Glyphs[i]);
 	}

 	if(Glyphs)	delete[] Glyphs;
}
*/
//---------------------------------------------------------------------------
void spl_TextToGlyphs(HDC hdc,char *Text,wchar_t *Glyphs,UINT &Count)
{
 	GCP_RESULTS TextInfo;
 	DWORD Flag;

 	Flag = GetFontLanguageInfo(hdc);
	Glyphs[0] = 0;

	Count = strlen(Text);

 	TextInfo.lStructSize=sizeof(GCP_RESULTS);
 	TextInfo.lpOutString="";
 	TextInfo.lpOrder=NULL;
 	TextInfo.lpDx=NULL;
 	TextInfo.lpCaretPos=NULL;
 	TextInfo.lpClass=NULL;
 	TextInfo.lpGlyphs=Glyphs;
 	TextInfo.nGlyphs=Count;
 	TextInfo.nMaxFit=Count;
 	GetCharacterPlacement(hdc,Text,Count,0,&TextInfo,Flag);
    Count = TextInfo.nGlyphs;
}
//---------------------------------------------------------------------------
/*
void spl_ConvertToArabic(HDC hdc,AnsiString Text,wchar_t *Glyphs,UINT *Orders,int *pDx,UINT &Count)
{
 	GCP_RESULTS TextInfo;
 	DWORD Flag;
//    char OutString[255];

 	Flag = GetFontLanguageInfo(hdc);
	Glyphs[0] = 0;

	Count = Text.Length();

 	TextInfo.lStructSize=sizeof(GCP_RESULTS);
// 	TextInfo.lpOutString=OutString;
 	TextInfo.lpOutString="";
// 	TextInfo.lpOrder=Orders;
 	TextInfo.lpOrder=NULL;
// 	TextInfo.lpDx=pDx;
 	TextInfo.lpDx=NULL;
 	TextInfo.lpCaretPos=NULL;
 	TextInfo.lpClass=NULL;
 	TextInfo.lpGlyphs=Glyphs;
 	TextInfo.nGlyphs=Count;
 	TextInfo.nMaxFit=Count;
 	GetCharacterPlacement(hdc,Text.c_str(),Count,0,&TextInfo,Flag);
}
*/
//---------------------------------------------------------------------------
/*
void spl_DrawChar(UINT CharOrd,double &XOffset,int Dx)
{
    if(FormDisplay->TheEnd) return;

    TStrokeCollection *Polyline;
    float Ax,Ay,Bx,By;

 	Polyline=FormInsertText->TTFToVec->GetCharacterGlyphs(CharOrd);
         
 	TRect R=Polyline->Bounds;
 	Ax=1.0;
// 	Bx=-Ax*R.Left+XOffset;
 	Bx=XOffset;
 	Ay=1.0;
 	By=0;
//    XOffset += R.Width()*Ax;
//    XOffset += R.Width()*Ax + Dx;
    XOffset += R.Width()*Ax + Dx / 10.0;

 	int GlyphNum=Polyline->Stroke[0].GlyphNumber;
    int VertexCount=0;
    vlPolylineBegin();
    vlVertex(Ax*Polyline->Stroke[0].Pt1.x+Bx,Ay*Polyline->Stroke[0].Pt1.y+By);
 	for(int i=0;i<Polyline->Count;i++)
 	{
  		if(Polyline->Stroke[i].GlyphNumber != GlyphNum)
  		{
    		vlAddPolyline(VL_POLY_LINE,false);
            VertexCount=0;
            vlPolylineBegin();
    		vlVertex(Ax*Polyline->Stroke[i].Pt1.x+Bx,Ay*Polyline->Stroke[i].Pt1.y+By);
//   			Image1->Canvas->Pen->Color=(TColor)RGB(random(255),random(255),random(255));
   			GlyphNum=Polyline->Stroke[i].GlyphNumber;
  		}
//  		Image1->Canvas->MoveTo(Ax*Polyline->Stroke[i].Pt1.x+Bx,Ay*Polyline->Stroke[i].Pt1.y+By);
//  		Image1->Canvas->LineTo(Ax*Polyline->Stroke[i].Pt2.x+Bx,Ay*Polyline->Stroke[i].Pt2.y+By);
        if(VertexCount>=MaxVertexCount)
        {
            vlAddPolyline(VL_POLY_LINE,false);

            VertexCount=0;
            vlPolylineBegin();
        }
        vlVertex(Ax*Polyline->Stroke[i].Pt2.x+Bx,Ay*Polyline->Stroke[i].Pt2.y+By);
        VertexCount++;
 	}
    vlAddPolyline(VL_POLY_LINE,false);
}
//---------------------------------------------------------------------------
void spl_DrawString(AnsiString strText)
{
	UINT Count = strText.Length();
	UINT *Indices = new UINT[Count];
 	UINT *Orders=new UINT[Count];
    int *pDx = new int[Count];
	spl_ConvertToArabic(FormInsertText->Label->Canvas->Handle,strText,Indices,Orders,pDx,Count);

    double XOffset = 0;
	for(UINT i=0;i<Count;i++)
    {
    	if(Indices[i] == 0xFCEF)// Space
        	XOffset += 100;
        else
	    	spl_DrawChar(Indices[i],XOffset,pDx[Orders[i]]);
    }

    if(Indices)
    {
     	delete[] Indices;
        Indices = NULL;
    }
 	if(Orders)
    {
    	delete[] Orders;
        Orders = NULL;
    }
 	if(Orders)
    {
    	delete[] Orders;
        Orders = NULL;
    }
    if(pDx)
    {
     	delete[] pDx;
        pDx = NULL;
    }
}
*/
//---------------------------------------------------------------------------

