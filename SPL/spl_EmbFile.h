//---------------------------------------------------------------------------
#ifndef spl_EmbFileH
#define spl_EmbFileH
//---------------------------------------------------------------------------
#include "spl_Region.h"
#include "spl_EmbLib.h"
#include "spl_Digitizer.h"
//---------------------------------------------------------------------------
void spl_CenterStithcs(spl_Rect &Frame,spl_GlobalStitchPath &GlobalStitchPath);
void spl_ScaleStithcs(double Scale,spl_GlobalStitchPath &GlobalStitchPath);
void spl_ReverseStithcs(double Height,spl_GlobalStitchPath &GlobalStitchPath);
void spl_ReConstructStitchs(double Epsilon,spl_GlobalStitchPath &iGlobalStitchPath,spl_GlobalStitchPath &oGlobalStitchPath);
void spl_MakeTatami(spl_GlobalStitchPath &iGlobalStitchPath,spl_GlobalStitchPath &oGlobalStitchPath);
void spl_AdjustStitchs(bool ApplyPattern,spl_Point &op,spl_GlobalStitchPath &GlobalStitchPath,spl_StitchPath &StitchPath);
//---------------------------------------------------------------------------
#endif
