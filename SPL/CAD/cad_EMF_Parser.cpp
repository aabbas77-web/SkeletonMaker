//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.hpp>
#pragma hdrstop

#include "cad_EMF_Parser.h"
#include "api_VecApi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "wmfeps_utils_RealMeta"
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormEMF_Parser *FormEMF_Parser;
//---------------------------------------------------------------------------
__fastcall TFormEMF_Parser::TFormEMF_Parser(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::FormCreate(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::FormDestroy(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmr(TRealMetafile *Sender,
      const ENHMETARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrAbortPath(
      TRealMetafile *Sender, const EMRSETMETARGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrAngleArc(
      TRealMetafile *Sender, const EMRANGLEARC *rec, TEnumAction &Action)
{
	vlAddArc(rec->ptlCenter.x,RealMetafile->MMHeight - rec->ptlCenter.y,rec->nRadius,rec->eStartAngle,rec->eSweepAngle);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrArc(TRealMetafile *Sender,
      const EMRARC *rec, TEnumAction &Action)
{
//	long nRadius =
//	vlAddArc((rec->rclBox.right - rec->rclBox.left)/2.0,(rec->rclBox.bottom - rec->rclBox.top)/2.0,rec->nRadius,rec->ptlStart,rec->ptlEnd);

    int nLeftRect;
    int nTopRect;
    int nRightRect;
    int nBottomRect;
    int nXStartArc;
    int nYStartArc;
    int nXEndArc;
    int nYEndArc;
    double Xcen,Ycen,RadH,RadV,Ang0,Ang1,AngArc,AngRot;

    nLeftRect = rec->rclBox.left;
    nTopRect = rec->rclBox.top;
    nRightRect = rec->rclBox.right;
    nBottomRect = rec->rclBox.bottom;
    nXStartArc = rec->ptlStart.x;
    nYStartArc = rec->ptlStart.y;
    nXEndArc = rec->ptlEnd.x;
    nYEndArc = rec->ptlEnd.y;

    RadH = nBottomRect-nTopRect;
    RadV = nRightRect-nLeftRect;
    Xcen = nLeftRect+RadV/2.0;
    Ycen = nTopRect+RadH/2.0;
    Ang0 = RadToDeg(ArcTan2(nYStartArc-Ycen,nXStartArc-Xcen));
    Ang1 = RadToDeg(ArcTan2(nYEndArc-Ycen,nXEndArc-Xcen));
    AngArc = -(Ang1 - Ang0);
    AngRot = 90;

    vlAddArcEx(Xcen, RealMetafile->MMHeight - Ycen, RadH, RadV, Ang0, AngArc, AngRot);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrArcTo(
      TRealMetafile *Sender, const EMRARC *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrBeginPath(
      TRealMetafile *Sender, const EMRSETMETARGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrBitBlt(
      TRealMetafile *Sender, const EMRBITBLT *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrChord(
      TRealMetafile *Sender, const EMRARC *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrCloseFigure(
      TRealMetafile *Sender, const EMRSETMETARGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrCreateBrushIndirect(
      TRealMetafile *Sender, const EMRCREATEBRUSHINDIRECT *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrCreateColorSpace(
      TRealMetafile *Sender, const EMRCREATECOLORSPACE *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrCreateDIBPatternBrushPt(
      TRealMetafile *Sender, const EMRCREATEDIBPATTERNBRUSHPT *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrCreateMonoBrush(
      TRealMetafile *Sender, const EMRCREATEMONOBRUSH *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrCreatePalette(
      TRealMetafile *Sender, const EMRCREATEPALETTE *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrCreatePen(
      TRealMetafile *Sender, const EMRCREATEPEN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrDeleteColorSpace(
      TRealMetafile *Sender, const EMRSETCOLORSPACE *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrDeleteObject(
      TRealMetafile *Sender, const EMRSELECTOBJECT *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrEllipse(
      TRealMetafile *Sender, const EMRELLIPSE *rec, TEnumAction &Action)
{
	double Xcen;
    double Ycen;
    double RadH;
    double RadV;
    Xcen = (rec->rclBox.left + rec->rclBox.right) / 2; 
    Ycen = (rec->rclBox.top + rec->rclBox.bottom) / 2;
    RadH = (rec->rclBox.right - rec->rclBox.left) / 2;
    RadV = (rec->rclBox.bottom - rec->rclBox.top) / 2;
	vlAddEllipse(Xcen,RealMetafile->MMHeight - Ycen,RadH,RadV,0);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrEndPath(
      TRealMetafile *Sender, const EMRSETMETARGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrEof(TRealMetafile *Sender,
      const EMREOF *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrExcludeClipRect(
      TRealMetafile *Sender, const EMREXCLUDECLIPRECT *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrExtCreateFontIndirectW(
      TRealMetafile *Sender, const EMREXTCREATEFONTINDIRECTW *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrExtCreatePen(
      TRealMetafile *Sender, const EMREXTCREATEPEN *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrExtFloodFill(
      TRealMetafile *Sender, const EMREXTFLOODFILL *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrExtSelectClipRgn(
      TRealMetafile *Sender, const EMREXTSELECTCLIPRGN *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrExtTextOutA(
      TRealMetafile *Sender, const EMREXTTEXTOUTA *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrExtTextOutW(
      TRealMetafile *Sender, const EMREXTTEXTOUTA *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrFillPath(
      TRealMetafile *Sender, const EMRFILLPATH *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrFillRgn(
      TRealMetafile *Sender, const EMRFILLRGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrFlattenPath(
      TRealMetafile *Sender, const EMRSETMETARGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrFrameRgn(
      TRealMetafile *Sender, const EMRFRAMERGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrGdiComment(
      TRealMetafile *Sender, const EMRGDICOMMENT *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrGLSBoundedRecord(
      TRealMetafile *Sender, const EMRGLSBOUNDEDRECORD *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrGLSRecord(
      TRealMetafile *Sender, const EMRGLSRECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrHeader(
      TRealMetafile *Sender, const ENHMETAHEADER *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrIntersectClipRect(
      TRealMetafile *Sender, const EMREXCLUDECLIPRECT *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrInvertRgn(
      TRealMetafile *Sender, const EMRINVERTRGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrLineTo(
      TRealMetafile *Sender, const EMRMOVETOEX *rec, TEnumAction &Action)
{
	EndP.x = rec->ptl.x;	
	EndP.y = rec->ptl.y;
	vlAddLine(StartP.x,RealMetafile->MMHeight - StartP.y,EndP.x,RealMetafile->MMHeight - EndP.y);    	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrMaskBlt(
      TRealMetafile *Sender, const EMRMASKBLT *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrModifyWorldTransform(
      TRealMetafile *Sender, const EMRMODIFYWORLDTRANSFORM *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrMoveToEx(
      TRealMetafile *Sender, const EMRMOVETOEX *rec, TEnumAction &Action)
{
	StartP.x = rec->ptl.x;	
	StartP.y = rec->ptl.y;	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrOffsetClipRgn(
      TRealMetafile *Sender, const EMROFFSETCLIPRGN *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPaintRgn(
      TRealMetafile *Sender, const EMRINVERTRGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPie(TRealMetafile *Sender,
      const EMRARC *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPixelFormat(
      TRealMetafile *Sender, const EMRPIXELFORMAT *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPlgBlt(
      TRealMetafile *Sender, const EMRPLGBLT *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyBezier(
      TRealMetafile *Sender, const EMRPOLYBEZIER *rec, TEnumAction &Action)
{
	vlPolylineBegin();
	for(UINT i=0;i<rec->cptl;i++)
    {
    	vlVertex(rec->aptl[i].x,RealMetafile->MMHeight - rec->aptl[i].y);
    }
    vlAddPolyline(VL_POLY_BEZIER,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyBezier16(
      TRealMetafile *Sender, const EMRPOLYBEZIER16 *rec,
      TEnumAction &Action)
{
	vlPolylineBegin();
	for(UINT i=0;i<rec->cpts;i++)
    {
    	vlVertex(rec->apts[i].x,RealMetafile->MMHeight - rec->apts[i].y);
    }
    vlAddPolyline(VL_POLY_BEZIER,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyBezierTo(
      TRealMetafile *Sender, const EMRPOLYBEZIER *rec, TEnumAction &Action)
{
	vlPolylineBegin();
	for(UINT i=0;i<rec->cptl;i++)
    {
    	vlVertex(rec->aptl[i].x,RealMetafile->MMHeight - rec->aptl[i].y);
    }
    vlAddPolyline(VL_POLY_BEZIER,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyBezierTo16(
      TRealMetafile *Sender, const EMRPOLYBEZIER16 *rec,
      TEnumAction &Action)
{
	vlPolylineBegin();
	for(UINT i=0;i<rec->cpts;i++)
    {
    	vlVertex(rec->apts[i].x,RealMetafile->MMHeight - rec->apts[i].y);
    }
    vlAddPolyline(VL_POLY_BEZIER,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyDraw(
      TRealMetafile *Sender, const EMRPOLYDRAW *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyDraw16(
      TRealMetafile *Sender, const EMRPOLYDRAW16 *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolygon(
      TRealMetafile *Sender, const EMRPOLYBEZIER *rec, TEnumAction &Action)
{
	vlPolylineBegin();
	for(UINT i=0;i<rec->cptl;i++)
    {
    	vlVertex(rec->aptl[i].x,RealMetafile->MMHeight - rec->aptl[i].y);
    }
    vlAddPolyline(VL_POLY_LINE,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolygon16(
      TRealMetafile *Sender, const EMRPOLYBEZIER16 *rec,
      TEnumAction &Action)
{
	vlPolylineBegin();
	for(UINT i=0;i<rec->cpts;i++)
    {
    	vlVertex(rec->apts[i].x,RealMetafile->MMHeight - rec->apts[i].y);
    }
    vlAddPolyline(VL_POLY_LINE,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyLine(
      TRealMetafile *Sender, const EMRPOLYBEZIER *rec, TEnumAction &Action)
{
	vlPolylineBegin();
	for(UINT i=0;i<rec->cptl;i++)
    {
    	vlVertex(rec->aptl[i].x,RealMetafile->MMHeight - rec->aptl[i].y);
    }
    vlAddPolyline(VL_POLY_LINE,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyLine16(
      TRealMetafile *Sender, const EMRPOLYBEZIER16 *rec,
      TEnumAction &Action)
{
	vlPolylineBegin();
	for(UINT i=0;i<rec->cpts;i++)
    {
    	vlVertex(rec->apts[i].x,RealMetafile->MMHeight - rec->apts[i].y);
    }
    vlAddPolyline(VL_POLY_LINE,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyLineTo(
      TRealMetafile *Sender, const EMRPOLYBEZIER *rec, TEnumAction &Action)
{
	vlPolylineBegin();
	for(UINT i=0;i<rec->cptl;i++)
    {
    	vlVertex(rec->aptl[i].x,RealMetafile->MMHeight - rec->aptl[i].y);
    }
    vlAddPolyline(VL_POLY_LINE,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyLineTo16(
      TRealMetafile *Sender, const EMRPOLYBEZIER16 *rec,
      TEnumAction &Action)
{
	vlPolylineBegin();
	for(UINT i=0;i<rec->cpts;i++)
    {
    	vlVertex(rec->apts[i].x,RealMetafile->MMHeight - rec->apts[i].y);
    }
    vlAddPolyline(VL_POLY_LINE,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyPolygon(
      TRealMetafile *Sender, const EMRPOLYPOLYLINE *rec,
      TEnumAction &Action)
{
/*
	int j=0;
	for(UINT nPoly=0;nPoly<rec->nPolys;nPoly++)
    {
		vlPolylineBegin();
		for(UINT i=0;i<rec->aPolyCounts[nPoly];i++)
	    {
	    	vlVertex(rec->aptl[j].x,RealMetafile->MMHeight - rec->aptl[j].y);
            j++;
	    }
    	vlAddPolyline(VL_POLY_LINE,false);
    }
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyPolygon16(
      TRealMetafile *Sender, const EMRPOLYPOLYLINE16 *rec,
      TEnumAction &Action)
{
/*
	int j=0;
    int n = rec->cpts;
	for(UINT nPoly=0;nPoly<rec->nPolys;nPoly++)
    {
		vlPolylineBegin();
		for(UINT i=0;i<rec->aPolyCounts[nPoly];i++)
	    {
	    	vlVertex(rec->apts[j].x,RealMetafile->MMHeight - rec->apts[j].y);
            j++;
	    }
    	vlAddPolyline(VL_POLY_LINE,false);
    }
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyPolyLine(
      TRealMetafile *Sender, const EMRPOLYPOLYLINE *rec,
      TEnumAction &Action)
{
/*
	int j=0;
	for(UINT nPoly=0;nPoly<rec->nPolys;nPoly++)
    {
		vlPolylineBegin();
		for(UINT i=0;i<rec->aPolyCounts[nPoly];i++)
	    {
	    	vlVertex(rec->aptl[j].x,RealMetafile->MMHeight - rec->aptl[j].y);
            j++;
	    }
    	vlAddPolyline(VL_POLY_LINE,false);
    }
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyPolyLine16(
      TRealMetafile *Sender, const EMRPOLYPOLYLINE16 *rec,
      TEnumAction &Action)
{
/*
	int j=0;
	for(UINT nPoly=0;nPoly<rec->nPolys;nPoly++)
    {
		vlPolylineBegin();
		for(UINT i=0;i<rec->aPolyCounts[nPoly];i++)
	    {
	    	vlVertex(rec->apts[j].x,RealMetafile->MMHeight - rec->apts[j].y);
            j++;
	    }
    	vlAddPolyline(VL_POLY_LINE,false);
    }
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyTextOutA(
      TRealMetafile *Sender, const EMRPOLYTEXTOUTA *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrPolyTextOutW(
      TRealMetafile *Sender, const EMRPOLYTEXTOUTA *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrRealizePalette(
      TRealMetafile *Sender, const EMRSETMETARGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrRectangle(
      TRealMetafile *Sender, const EMRELLIPSE *rec, TEnumAction &Action)
{
    vlAddRect(rec->rclBox.left,RealMetafile->MMHeight - rec->rclBox.top,rec->rclBox.right - rec->rclBox.left,rec->rclBox.bottom - rec->rclBox.top,0,0);	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrResizePalette(
      TRealMetafile *Sender, const EMRRESIZEPALETTE *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrRestoreDC(
      TRealMetafile *Sender, const EMRRESTOREDC *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrRoundRect(
      TRealMetafile *Sender, const EMRROUNDRECT *rec, TEnumAction &Action)
{
    vlAddRect(rec->rclBox.left,RealMetafile->MMHeight - rec->rclBox.top,rec->rclBox.right - rec->rclBox.left,rec->rclBox.bottom - rec->rclBox.top,0,rec->szlCorner.cx);	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSaveDC(
      TRealMetafile *Sender, const EMRSETMETARGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrScaleViewportExtEx(
      TRealMetafile *Sender, const EMRSCALEVIEWPORTEXTEX *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrScaleWindowExtEx(
      TRealMetafile *Sender, const EMRSCALEVIEWPORTEXTEX *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSelectClipPath(
      TRealMetafile *Sender, const EMRSETMAPMODE *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSelectObject(
      TRealMetafile *Sender, const EMRSELECTOBJECT *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSelectPalette(
      TRealMetafile *Sender, const EMRSELECTPALETTE *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetArcDirection(
      TRealMetafile *Sender, const EMRSETARCDIRECTION *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetBkColor(
      TRealMetafile *Sender, const EMRSETTEXTCOLOR *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetBkMode(
      TRealMetafile *Sender, const EMRSETMAPMODE *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetBrushorgEx(
      TRealMetafile *Sender, const EMRSETWINDOWORGEX *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetColorAdjustment(
      TRealMetafile *Sender, const EMRSETCOLORADJUSTMENT *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetColorSpace(
      TRealMetafile *Sender, const EMRSETCOLORSPACE *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetDIBitsToDevice(
      TRealMetafile *Sender, const EMRSETDIBITSTODEVICE *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetICMMode(
      TRealMetafile *Sender, const EMRSETMAPMODE *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetMapMode(
      TRealMetafile *Sender, const EMRSETMAPMODE *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetMapperFlags(
      TRealMetafile *Sender, const EMRSETMAPPERFLAGS *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetMetaRgn(
      TRealMetafile *Sender, const EMRSETMETARGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetMiterLimit(
      TRealMetafile *Sender, const EMRSETMITERLIMIT *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetPaletteEntries(
      TRealMetafile *Sender, const EMRSETPALETTEENTRIES *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetPixelv(
      TRealMetafile *Sender, const EMRSETPIXELV *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetPolyFillMode(
      TRealMetafile *Sender, const EMRSETMAPMODE *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetRop2(
      TRealMetafile *Sender, const EMRSETMAPMODE *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetStretchBltMode(
      TRealMetafile *Sender, const EMRSETMAPMODE *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetTextAlign(
      TRealMetafile *Sender, const EMRSETMAPMODE *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetTextColor(
      TRealMetafile *Sender, const EMRSETTEXTCOLOR *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetViewportExtEx(
      TRealMetafile *Sender, const EMRSETWINDOWEXTEX *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetViewportOrgEx(
      TRealMetafile *Sender, const EMRSETWINDOWORGEX *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetWindowExtEx(
      TRealMetafile *Sender, const EMRSETWINDOWEXTEX *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetWindowOrgEx(
      TRealMetafile *Sender, const EMRSETWINDOWORGEX *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrSetWorldTransform(
      TRealMetafile *Sender, const EMRSETWORLDTRANSFORM *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrStretchBlt(
      TRealMetafile *Sender, const EMRSTRETCHBLT *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrStretchDIBits(
      TRealMetafile *Sender, const EMRSTRETCHDIBITS *rec,
      TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrStrokeAndFillpath(
      TRealMetafile *Sender, const EMRFILLPATH *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrStrokePath(
      TRealMetafile *Sender, const EMRFILLPATH *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileEmrWidenPath(
      TRealMetafile *Sender, const EMRSETMETARGN *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
//-----------------Windows Metafile------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmr(TRealMetafile *Sender,
      const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrAnimatePalette(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrArc(TRealMetafile *Sender,
      const METARECORD *rec, TEnumAction &Action)
{
    int nLeftRect;
    int nTopRect;
    int nRightRect;
    int nBottomRect;
    int nXStartArc;
    int nYStartArc;
    int nXEndArc;
    int nYEndArc;
    double Xcen,Ycen,RadH,RadV,Ang0,Ang1,AngArc,AngRot;

    nLeftRect = rec->rdParm[7];
    nTopRect = rec->rdParm[6];
    nRightRect = rec->rdParm[5];
    nBottomRect = rec->rdParm[4];
    nXStartArc = rec->rdParm[3];
    nYStartArc = rec->rdParm[2];
    nXEndArc = rec->rdParm[1];
    nYEndArc = rec->rdParm[0];

    RadH = nBottomRect-nTopRect;
    RadV = nRightRect-nLeftRect;
    Xcen = nLeftRect+RadV/2.0;
    Ycen = nTopRect+RadH/2.0;
    Ang0 = RadToDeg(ArcTan2(nYStartArc-Ycen,nXStartArc-Xcen));
    Ang1 = RadToDeg(ArcTan2(nYEndArc-Ycen,nXEndArc-Xcen));
    AngArc = -(Ang1 - Ang0);
    AngRot = 90;

    vlAddArcEx (Xcen, RealMetafile->MMHeight - Ycen, RadH, RadV, Ang0, AngArc, AngRot);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrBitBlt(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrChord(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrCreateBrushIndirect(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrCreateFontIndirect(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrCreatePalette(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrCreatePatternBrush(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrCreatePenIndirect(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrCreateRegion(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrDeleteObject(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrDIBBitBlt(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrDIBCreatePatternBrush(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrDIBStretchBlt(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrEllipse(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
	double Xcen;
    double Ycen;
    double RadH;
    double RadV;

    HDC hdc;
    int nLeftRect;
    int nTopRect;
    int nRightRect;
    int nBottomRect;

    nBottomRect = rec->rdParm[0];
    nRightRect = rec->rdParm[1];
    nTopRect = rec->rdParm[2];
    nLeftRect = rec->rdParm[3];

    Xcen = (nLeftRect + nRightRect) / 2;
    Ycen = (nTopRect + nBottomRect) / 2;
    RadH = (nRightRect - nLeftRect) / 2;
    RadV = (nBottomRect - nTopRect) / 2;
	vlAddEllipse(Xcen,RealMetafile->MMHeight - Ycen,RadH,RadV,0);
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrEscape(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrExcludeClipRect(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrExtFloodFill(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrExtTextOut(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrFillRegion(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrFloodFill(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrFrameRegion(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrIntersectClipRect(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrInvertRegion(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrLineTo(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
	EndP.x = rec->rdParm[1];	
	EndP.y = rec->rdParm[0];
	vlAddLine(StartP.x,RealMetafile->MMHeight - StartP.y,EndP.x,RealMetafile->MMHeight - EndP.y);    	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrMoveTo(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
	StartP.x = rec->rdParm[1];
	StartP.y = rec->rdParm[0];	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrOffSetClipRgn(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrOffSetViewportOrg(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrOffSetWindowOrg(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrPaintRegion(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrPatBlt(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrPie(TRealMetafile *Sender,
      const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrPolygon(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
/*
	vlPolylineBegin();
    rec->
	for(int i=0;i<rec->cptl;i++)
    {
    	vlVertex(rec->aptl[i].x,RealMetafile->MMHeight - rec->aptl[i].y);
    }
    vlAddPolyline(VL_POLY_LINE,false);
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrPolyLine(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrPolyPolygon(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrRealizePalette(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrRectangle(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrResizePalette(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrResToReDC(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrRoundRect(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSaveDC(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrScaleViewportExt(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrScaleWindowExt(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSelectClipRegion(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSelectObject(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSelectPalette(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetBkColor(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetBkMode(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetDIBToDev(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetMapMode(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetMapperFlags(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetPalEntries(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetPixel(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetPolyFillMode(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetRelabs(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetRop2(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetStretchBltMode(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetTextAlign(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetTextCharExtra(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetTextColor(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetTextJustification(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetViewportExt(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetViewportOrg(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetWindowExt(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrSetWindowOrg(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrStretchBlt(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrStretchDIB(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEMF_Parser::RealMetafileWmrTextOut(
      TRealMetafile *Sender, const METARECORD *rec, TEnumAction &Action)
{
//	
}
//---------------------------------------------------------------------------
