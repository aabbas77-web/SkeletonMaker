//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_Types.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
spl_SByte spl_MinStitchLength=3;
spl_SByte spl_MinJumpLength=10;
spl_SByte spl_FillStitchDensity=5;
spl_SByte spl_LineStitchDensity=5;
spl_SByte spl_RunStitchStep=121;
spl_SByte spl_JumpStitchStep=121;
spl_SByte spl_SatinHeight=10.0;
bool spl_AdjustFillStitchs = true;
bool spl_AdjustLineStitchs = false;
bool spl_BestJump = false;
bool spl_ReplaceJump = false;
spl_UByte spl_AdjustMethode = 0;
//---------------------------------------------------------------------------
char    spl_Comments[13]="WWPTC";
spl_UByte spl_FillStitchingOutput=spl_soZigZag;
spl_UByte spl_LineStitchingOutput=spl_soSatin;
spl_UWord spl_StitchMargin=spl_MaxStitchLength;
bool spl_DesignCentered=true;
double spl_DesignScale=1.0;
bool spl_ReturnToStartPoint=true;
//---------------------------------------------------------------------------
spl_EmbParameters spl_Global_EmbParameters;
//---------------------------------------------------------------------------
bool spl_ProcessFillColor=true;
bool spl_ProcessLineColor=false;
//---------------------------------------------------------------------------

