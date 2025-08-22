//---------------------------------------------------------------------------
#ifndef spl_ImageProcessingH
#define spl_ImageProcessingH
//---------------------------------------------------------------------------
#include "spl_ColorQuantizer.h"
#include "spl_Types.h"
//---------------------------------------------------------------------------
// Color Processing:
// 32 bit: Color = DWORD(Color)
// 24 bit: Color = DWORD(Color)
// 16 bit: Color = Word (Color)
// 08 bit: Color = Byte (Color)
// 01 bit: Color = bool (Byte(Color))
//---------------------------------------------------------------------------
void spl_FlushImage(spl_Image *pImage,DWORD Color);
//---------------------------------------------------------------------------
void spl_InvertImage(spl_Image *pImage);
//---------------------------------------------------------------------------
void spl_SmoothImageColors(spl_Image *pImage,Byte FilterDim,spl_Image *pResult);
//---------------------------------------------------------------------------
void spl_SmoothDigitizedImageColors(spl_Image *pIndices,int ColorsCount,Byte FilterDim);
//---------------------------------------------------------------------------
void spl_FrameImage(spl_Image *pImage,DWORD Color,spl_UInt Border);
//---------------------------------------------------------------------------
enum {gmArtificial=0,gmRed,gmGreen,gmBlue,gmNatural};
void spl_ConvertToGray(spl_Image *pImage,Byte Methode,spl_Image *pResult);
//---------------------------------------------------------------------------
void spl_ReverseImage(spl_Image *pImage,spl_Image *pResult);
//---------------------------------------------------------------------------
typedef spl_UInt spl_Histogram[256];
typedef double spl_LHistogram[256];
//---------------------------------------------------------------------------
spl_UByte spl_FisherTow(spl_Histogram hist);
void spl_LogHistogram(spl_Histogram hist,spl_LHistogram lhst);
spl_UByte spl_EntropyTow(spl_Histogram hst,double *lhst);
spl_UByte spl_EntropyTow(spl_Histogram Histogram);
void spl_Monochrome(spl_Image *pImage,spl_UByte Threshold,spl_Image *pResult);
void spl_GetHistogram(spl_Image *pImage,spl_Histogram Histogram);
void spl_Monochrome8bit(spl_Image *pImage,spl_UByte Threshold,spl_Image *pResult);
//---------------------------------------------------------------------------
void spl_ErosionDigitizedImageColors(spl_Image *pIndices,Byte FilterDim);
void spl_DilationDigitizedImageColors(spl_Image *pIndices,Byte FilterDim);
void spl_IsolateWords(spl_Image *pIndices,Byte nWordColorIndex,int nRadius);
//---------------------------------------------------------------------------
enum {etEllipse,etRectangle};
void spl_Halftone(spl_Image *pImage,spl_UByte ElementType,bool bNormalMethode,HDC hdc);
void spl_Halftone(spl_Image *pImage,spl_UByte ElementType,bool bNormalMethode,spl_Image *pResult);
void spl_Halftone_New(spl_Image *pImage,spl_UByte ElementType,bool bNormalMethode,HDC hdc);
//---------------------------------------------------------------------------
#endif
