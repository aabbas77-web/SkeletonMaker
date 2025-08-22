//---------------------------------------------------------------------------
#ifndef spl_ALICompressionH
#define spl_ALICompressionH
//---------------------------------------------------------------------------
#include "spl_Image.h"
#include "spl_ColorQuantizer.h"
#include "spl_Contour.h"
#include "spl_Bits.h"
#include "spl_FloodFill.h"
#include "spl_Digitizer.h"
//---------------------------------------------------------------------------
struct spl_ALICompressionHeader
{
    WORD Width;// Image Width
    WORD Height;// Image Height
    BYTE ColorsCount;// Colors Count = Color Palette Size
};
//---------------------------------------------------------------------------
void spl_ALICompress(spl_Image *pImage,int ColorsCount,TMemoryStream *pStream);
void spl_ALIDeCompress(TMemoryStream *pStream,spl_Image *pImage);
//---------------------------------------------------------------------------
#endif
