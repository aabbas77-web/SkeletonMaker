//---------------------------------------------------------------------------
#ifndef spl_ColorQuantizerH
#define spl_ColorQuantizerH
//---------------------------------------------------------------------------
#include "spl_Image.h"
#include "spl_ImageProcessing.h"
#include "spl_Digitizer.h"
//---------------------------------------------------------------------------
// SPL Scan Line
//---------------------------------------------------------------------------
// B G R    B G R   B G R   ..
// 0 1 2    3 4 5   6 7 8   ..
//---------------------------------------------------------------------------
const Byte spl_BackgroundIndex=255;
//---------------------------------------------------------------------------
const Byte spl_ReservedIndex=254;
//---------------------------------------------------------------------------
extern Byte spl_ColorsCount;
//---------------------------------------------------------------------------
extern DWORD spl_QuantizedColors[256];
//---------------------------------------------------------------------------
extern Byte  spl_QuantizedPalette[768];
//---------------------------------------------------------------------------
// 1<= ColorsCount < spl_BackgroundIndex
// pIndices: (8 bits) Image That Contain Colors Indices
// Where: [0 <=  Indices  < ColorsCount]
void spl_QuantizeImageColors(spl_Image *pImage,spl_UInt ColorsCount,bool CreatePalette,bool bFullPalette);
//---------------------------------------------------------------------------
#endif
