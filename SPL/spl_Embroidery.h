//---------------------------------------------------------------------------
#ifndef spl_EmbroideryH
#define spl_EmbroideryH
//---------------------------------------------------------------------------
#include "spl_Image.h"
#include "spl_ImageProcessing.h"
#include "spl_Digitizer.h"
#include "spl_EmbFile.h"
//---------------------------------------------------------------------------
const int spl_nMaxIterationCount = 10000;
//---------------------------------------------------------------------------
extern bool spl_bIsInvalidEmbroidery;
//---------------------------------------------------------------------------
void spl_FillStitchs_EMB(spl_Image *pIndices,spl_MultiLayer &iMultiLayer,spl_StitchPath &StitchPath,spl_EmbHeader &EmbHeader);
//---------------------------------------------------------------------------
void spl_EmbroidContour(bool bMin,double ExtrudeDistance,double Density,bool Default,spl_Contour &Contour,spl_Contour &Result);
//---------------------------------------------------------------------------
void spl_EmbroidContourByParallel(double ExtrudeDistance,spl_Contour &Contour,spl_Contour &Result);
//---------------------------------------------------------------------------
//void spl_EmbroidRegion(spl_Region &Region,HRGN hRgn,spl_GlobalStitchPath &GlobalStitchPath);
void spl_EmbroidRegion(spl_Region &Region,spl_GlobalStitchPath &GlobalStitchPath);
//---------------------------------------------------------------------------
#endif
