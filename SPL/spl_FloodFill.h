//---------------------------------------------------------------------------
#ifndef spl_FloodFillH
#define spl_FloodFillH
//---------------------------------------------------------------------------
#include "spl_Image.h"
#include "spl_Contour.h"
//---------------------------------------------------------------------------
typedef void (*TFloodFillCallback)(); 
//---------------------------------------------------------------------------
void spl_FloodFillDigitizedRegion(spl_Image *pImage,spl_UInt x,spl_UInt y,Byte NewColor);
//---------------------------------------------------------------------------
void spl_FloodFillDigitizedRegionWhileNotEqualColor(spl_Image *pImage,spl_UInt x,spl_UInt y,Byte StopColor,Byte NewColor);
//---------------------------------------------------------------------------
void spl_FillDigitizedRegionForProcessing(spl_Image *pImage,spl_UInt x,spl_UInt y,Byte ClearIndex,spl_UWord ContourIndex);
//---------------------------------------------------------------------------
void spl_FloodFillDigitizedRegion(spl_Image *pImage,spl_UInt x,spl_UInt y,Byte NewColor,TFloodFillCallback FloodFillCallback);
//---------------------------------------------------------------------------
#endif
