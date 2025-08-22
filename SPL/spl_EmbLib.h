//---------------------------------------------------------------------------
#ifndef spl_EmbLibH
#define spl_EmbLibH
//---------------------------------------------------------------------------
#include <vector.h>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include "spl_Point.h"
#include "spl_CodingLib.h"
//---------------------------------------------------------------------------
const spl_UByte spl_ALI_KEY = 0xE6;
//---------------------------------------------------------------------------
#ifdef spl_Demo_Version
const AnsiString spl_EmbDefaultExtension="ali";
const AnsiString spl_EmbFilter="*.ali";
const AnsiString spl_EmbFullFilter="ALI Files (*.ali)|*.ali";

const AnsiString spl_EmbSimulatorCaption="(Demo) PTC Simulator V1.0 ";
const AnsiString spl_EmbEditorCaption="(Demo) PTC Editor V1.0 ";
const AnsiString spl_EmbBrowserCaption="(Demo) PTC Browser V1.0 ";
const AnsiString spl_EmbTraceCaption="(Demo) PTC Trace V1.0 ";
#else
const AnsiString spl_EmbDefaultExtension="dst";
const AnsiString spl_EmbFilter="*.dst;*.exp;*.dsz;*.dsb;*.ksm;*.ali";
const AnsiString spl_EmbFullFilter="All Files (*.ds?;*.exp;*.ksm;*.ali)|*.ds?;*.exp;*.ksm;*.ali|Tajima Files (*.dst;*.dsb;*.dsz)|*.dst;*.dsb;*.dsz|Melco Files (*.exp)|*.exp|Pfaff Files (*.ksm)|*.ksm|ALI Files (*.ali)|*.ali";

const AnsiString spl_EmbSimulatorCaption="PTC Simulator V1.0 ";
const AnsiString spl_EmbEditorCaption="PTC Editor V1.0 ";
const AnsiString spl_EmbBrowserCaption="PTC Browser V1.0 ";
const AnsiString spl_EmbTraceCaption="PTC Trace V1.0 ";
#endif
//---------------------------------------------------------------------------
// Stitch Type
//---------------------------------------------------------------------------
#define     spl_stNormal        (spl_UByte)0
#define     spl_stJump          (spl_UByte)1
#define     spl_stColorChanged  (spl_UByte)2
#define     spl_stEof           (spl_UByte)3
//---------------------------------------------------------------------------
struct spl_Stitch
{
    // Relative Position Of Stitch
    spl_SByte x;
    spl_SByte y;

    // Stitch Type
    spl_UByte type;
};
//---------------------------------------------------------------------------
typedef vector<spl_Stitch> spl_StitchPath;
//---------------------------------------------------------------------------
struct spl_GlobalStitch
{
    // Global Position Of Stitch
    spl_SInt x;
    spl_SInt y;

    // Stitch Type
    spl_UByte type;
};
//---------------------------------------------------------------------------
typedef vector<spl_GlobalStitch> spl_GlobalStitchPath;
//---------------------------------------------------------------------------
static const spl_UByte spl_MaxTajimaColors=20;
//---------------------------------------------------------------------------
extern spl_UInt spl_TajimaColors[spl_MaxTajimaColors];
//---------------------------------------------------------------------------
// All Dimensions In (dm)
//---------------------------------------------------------------------------
const   spl_UByte spl_MaxColorsCount = 129;
//---------------------------------------------------------------------------
struct spl_EmbHeader
{
    char    Comments[13];
    spl_UInt   StitchsCount;

    spl_UInt   NormalStitchs;
    spl_UInt   JumpStitchs;
    spl_UInt   ColorStitchs;

    // Bounding Box
    spl_SInt    left;
    spl_SInt    top;
    spl_SInt    right;
    spl_SInt    bottom;

    // Start Stitch
    spl_SInt    AX;
    spl_SInt    AY;

    // End Stitch
    spl_SInt    MX;
    spl_SInt    MY;

    // Colors
    spl_RGB     Colors[spl_MaxColorsCount];
};
//---------------------------------------------------------------------------
struct spl_DSXRec
{
    spl_UByte First;
    spl_UByte Second;
    spl_UByte Third;
};
//---------------------------------------------------------------------------
spl_Rect spl_ComputeFrame(spl_GlobalStitchPath &GlobalStitchPath);
//---------------------------------------------------------------------------
void spl_LoadEmbFromStream(TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar);
void spl_LoadEmbFromFile(AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar);
//---------------------------------------------------------------------------
void spl_SaveEmbToStream(TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar);
void spl_SaveEmbToFile(AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar);
//---------------------------------------------------------------------------
void spl_StitchStretchDraw(spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,Graphics::TBitmap *pBMP,TRect &R,int Margin,bool ShowJumps,bool Stretch,bool Real);
//---------------------------------------------------------------------------
void spl_ConvertStitchPathToGlobalStitchPath(spl_StitchPath &StitchPath,spl_GlobalStitchPath &GlobalStitchPath);
//---------------------------------------------------------------------------
void spl_ConvertGlobalStitchPathToStitchPath(spl_GlobalStitchPath &GlobalStitchPath,spl_StitchPath &StitchPath);
//---------------------------------------------------------------------------
#endif
