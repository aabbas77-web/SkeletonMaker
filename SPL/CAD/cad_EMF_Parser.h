//---------------------------------------------------------------------------

#ifndef cad_EMF_ParserH
#define cad_EMF_ParserH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "wmfeps_utils_RealMeta.h"
#include "spl_Point.h"
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormEMF_Parser : public TForm
{
__published:	// IDE-managed Components
	TRealMetafile *RealMetafile;
	TFormTranslation *FormTranslation1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall RealMetafileEmr(TRealMetafile *Sender,
          const ENHMETARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrAbortPath(TRealMetafile *Sender,
          const EMRSETMETARGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrAngleArc(TRealMetafile *Sender,
          const EMRANGLEARC *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrArc(TRealMetafile *Sender,
          const EMRARC *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrArcTo(TRealMetafile *Sender,
          const EMRARC *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrBeginPath(TRealMetafile *Sender,
          const EMRSETMETARGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrBitBlt(TRealMetafile *Sender,
          const EMRBITBLT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrChord(TRealMetafile *Sender,
          const EMRARC *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrCloseFigure(TRealMetafile *Sender,
          const EMRSETMETARGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrCreateBrushIndirect(TRealMetafile *Sender,
          const EMRCREATEBRUSHINDIRECT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrCreateColorSpace(TRealMetafile *Sender,
          const EMRCREATECOLORSPACE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrCreateDIBPatternBrushPt(
          TRealMetafile *Sender, const EMRCREATEDIBPATTERNBRUSHPT *rec,
          TEnumAction &Action);
	void __fastcall RealMetafileEmrCreateMonoBrush(TRealMetafile *Sender,
          const EMRCREATEMONOBRUSH *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrCreatePalette(TRealMetafile *Sender,
          const EMRCREATEPALETTE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrCreatePen(TRealMetafile *Sender,
          const EMRCREATEPEN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrDeleteColorSpace(TRealMetafile *Sender,
          const EMRSETCOLORSPACE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrDeleteObject(TRealMetafile *Sender,
          const EMRSELECTOBJECT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrEllipse(TRealMetafile *Sender,
          const EMRELLIPSE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrEndPath(TRealMetafile *Sender,
          const EMRSETMETARGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrEof(TRealMetafile *Sender,
          const EMREOF *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrExcludeClipRect(TRealMetafile *Sender,
          const EMREXCLUDECLIPRECT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrExtCreateFontIndirectW(
          TRealMetafile *Sender, const EMREXTCREATEFONTINDIRECTW *rec,
          TEnumAction &Action);
	void __fastcall RealMetafileEmrExtCreatePen(TRealMetafile *Sender,
          const EMREXTCREATEPEN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrExtFloodFill(TRealMetafile *Sender,
          const EMREXTFLOODFILL *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrExtSelectClipRgn(TRealMetafile *Sender,
          const EMREXTSELECTCLIPRGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrExtTextOutA(TRealMetafile *Sender,
          const EMREXTTEXTOUTA *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrExtTextOutW(TRealMetafile *Sender,
          const EMREXTTEXTOUTA *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrFillPath(TRealMetafile *Sender,
          const EMRFILLPATH *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrFillRgn(TRealMetafile *Sender,
          const EMRFILLRGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrFlattenPath(TRealMetafile *Sender,
          const EMRSETMETARGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrFrameRgn(TRealMetafile *Sender,
          const EMRFRAMERGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrGdiComment(TRealMetafile *Sender,
          const EMRGDICOMMENT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrGLSBoundedRecord(TRealMetafile *Sender,
          const EMRGLSBOUNDEDRECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrGLSRecord(TRealMetafile *Sender,
          const EMRGLSRECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrHeader(TRealMetafile *Sender,
          const ENHMETAHEADER *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrIntersectClipRect(TRealMetafile *Sender,
          const EMREXCLUDECLIPRECT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrInvertRgn(TRealMetafile *Sender,
          const EMRINVERTRGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrLineTo(TRealMetafile *Sender,
          const EMRMOVETOEX *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrMaskBlt(TRealMetafile *Sender,
          const EMRMASKBLT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrModifyWorldTransform(TRealMetafile *Sender,
          const EMRMODIFYWORLDTRANSFORM *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrMoveToEx(TRealMetafile *Sender,
          const EMRMOVETOEX *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrOffsetClipRgn(TRealMetafile *Sender,
          const EMROFFSETCLIPRGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPaintRgn(TRealMetafile *Sender,
          const EMRINVERTRGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPie(TRealMetafile *Sender,
          const EMRARC *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPixelFormat(TRealMetafile *Sender,
          const EMRPIXELFORMAT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPlgBlt(TRealMetafile *Sender,
          const EMRPLGBLT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyBezier(TRealMetafile *Sender,
          const EMRPOLYBEZIER *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyBezier16(TRealMetafile *Sender,
          const EMRPOLYBEZIER16 *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyBezierTo(TRealMetafile *Sender,
          const EMRPOLYBEZIER *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyBezierTo16(TRealMetafile *Sender,
          const EMRPOLYBEZIER16 *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyDraw(TRealMetafile *Sender,
          const EMRPOLYDRAW *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyDraw16(TRealMetafile *Sender,
          const EMRPOLYDRAW16 *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolygon(TRealMetafile *Sender,
          const EMRPOLYBEZIER *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolygon16(TRealMetafile *Sender,
          const EMRPOLYBEZIER16 *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyLine(TRealMetafile *Sender,
          const EMRPOLYBEZIER *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyLine16(TRealMetafile *Sender,
          const EMRPOLYBEZIER16 *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyLineTo(TRealMetafile *Sender,
          const EMRPOLYBEZIER *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyLineTo16(TRealMetafile *Sender,
          const EMRPOLYBEZIER16 *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyPolygon(TRealMetafile *Sender,
          const EMRPOLYPOLYLINE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyPolygon16(TRealMetafile *Sender,
          const EMRPOLYPOLYLINE16 *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyPolyLine(TRealMetafile *Sender,
          const EMRPOLYPOLYLINE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyPolyLine16(TRealMetafile *Sender,
          const EMRPOLYPOLYLINE16 *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyTextOutA(TRealMetafile *Sender,
          const EMRPOLYTEXTOUTA *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrPolyTextOutW(TRealMetafile *Sender,
          const EMRPOLYTEXTOUTA *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrRealizePalette(TRealMetafile *Sender,
          const EMRSETMETARGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrRectangle(TRealMetafile *Sender,
          const EMRELLIPSE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrResizePalette(TRealMetafile *Sender,
          const EMRRESIZEPALETTE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrRestoreDC(TRealMetafile *Sender,
          const EMRRESTOREDC *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrRoundRect(TRealMetafile *Sender,
          const EMRROUNDRECT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSaveDC(TRealMetafile *Sender,
          const EMRSETMETARGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrScaleViewportExtEx(TRealMetafile *Sender,
          const EMRSCALEVIEWPORTEXTEX *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrScaleWindowExtEx(TRealMetafile *Sender,
          const EMRSCALEVIEWPORTEXTEX *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSelectClipPath(TRealMetafile *Sender,
          const EMRSETMAPMODE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSelectObject(TRealMetafile *Sender,
          const EMRSELECTOBJECT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSelectPalette(TRealMetafile *Sender,
          const EMRSELECTPALETTE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetArcDirection(TRealMetafile *Sender,
          const EMRSETARCDIRECTION *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetBkColor(TRealMetafile *Sender,
          const EMRSETTEXTCOLOR *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetBkMode(TRealMetafile *Sender,
          const EMRSETMAPMODE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetBrushorgEx(TRealMetafile *Sender,
          const EMRSETWINDOWORGEX *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetColorAdjustment(TRealMetafile *Sender,
          const EMRSETCOLORADJUSTMENT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetColorSpace(TRealMetafile *Sender,
          const EMRSETCOLORSPACE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetDIBitsToDevice(TRealMetafile *Sender,
          const EMRSETDIBITSTODEVICE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetICMMode(TRealMetafile *Sender,
          const EMRSETMAPMODE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetMapMode(TRealMetafile *Sender,
          const EMRSETMAPMODE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetMapperFlags(TRealMetafile *Sender,
          const EMRSETMAPPERFLAGS *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetMetaRgn(TRealMetafile *Sender,
          const EMRSETMETARGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetMiterLimit(TRealMetafile *Sender,
          const EMRSETMITERLIMIT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetPaletteEntries(TRealMetafile *Sender,
          const EMRSETPALETTEENTRIES *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetPixelv(TRealMetafile *Sender,
          const EMRSETPIXELV *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetPolyFillMode(TRealMetafile *Sender,
          const EMRSETMAPMODE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetRop2(TRealMetafile *Sender,
          const EMRSETMAPMODE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetStretchBltMode(TRealMetafile *Sender,
          const EMRSETMAPMODE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetTextAlign(TRealMetafile *Sender,
          const EMRSETMAPMODE *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetTextColor(TRealMetafile *Sender,
          const EMRSETTEXTCOLOR *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetViewportExtEx(TRealMetafile *Sender,
          const EMRSETWINDOWEXTEX *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetViewportOrgEx(TRealMetafile *Sender,
          const EMRSETWINDOWORGEX *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetWindowExtEx(TRealMetafile *Sender,
          const EMRSETWINDOWEXTEX *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetWindowOrgEx(TRealMetafile *Sender,
          const EMRSETWINDOWORGEX *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrSetWorldTransform(TRealMetafile *Sender,
          const EMRSETWORLDTRANSFORM *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrStretchBlt(TRealMetafile *Sender,
          const EMRSTRETCHBLT *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrStretchDIBits(TRealMetafile *Sender,
          const EMRSTRETCHDIBITS *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrStrokeAndFillpath(TRealMetafile *Sender,
          const EMRFILLPATH *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrStrokePath(TRealMetafile *Sender,
          const EMRFILLPATH *rec, TEnumAction &Action);
	void __fastcall RealMetafileEmrWidenPath(TRealMetafile *Sender,
          const EMRSETMETARGN *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmr(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrAnimatePalette(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrArc(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrBitBlt(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrChord(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrCreateBrushIndirect(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrCreateFontIndirect(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrCreatePalette(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrCreatePatternBrush(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrCreatePenIndirect(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrCreateRegion(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrDeleteObject(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrDIBBitBlt(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrDIBCreatePatternBrush(
          TRealMetafile *Sender, const METARECORD *rec,
          TEnumAction &Action);
	void __fastcall RealMetafileWmrDIBStretchBlt(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrEllipse(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrEscape(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrExcludeClipRect(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrExtFloodFill(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrExtTextOut(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrFillRegion(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrFloodFill(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrFrameRegion(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrIntersectClipRect(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrInvertRegion(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrLineTo(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrMoveTo(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrOffSetClipRgn(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrOffSetViewportOrg(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrOffSetWindowOrg(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrPaintRegion(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrPatBlt(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrPie(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrPolygon(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrPolyLine(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrPolyPolygon(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrRealizePalette(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrRectangle(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrResizePalette(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrResToReDC(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrRoundRect(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSaveDC(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrScaleViewportExt(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrScaleWindowExt(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSelectClipRegion(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSelectObject(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSelectPalette(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetBkColor(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetBkMode(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetDIBToDev(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetMapMode(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetMapperFlags(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetPalEntries(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetPixel(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetPolyFillMode(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetRelabs(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetRop2(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetStretchBltMode(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetTextAlign(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetTextCharExtra(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetTextColor(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetTextJustification(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetViewportExt(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetViewportOrg(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetWindowExt(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrSetWindowOrg(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrStretchBlt(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrStretchDIB(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
	void __fastcall RealMetafileWmrTextOut(TRealMetafile *Sender,
          const METARECORD *rec, TEnumAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TFormEMF_Parser(TComponent* Owner);
    spl_Point StartP,EndP;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormEMF_Parser *FormEMF_Parser;
//---------------------------------------------------------------------------
#endif
