//---------------------------------------------------------------------------
#ifndef spl_TypesH
#define spl_TypesH
//---------------------------------------------------------------------------
#include <vector.h>
//---------------------------------------------------------------------------
// Integer Types
//---------------------------------------------------------------------------
// Byte = 1 Byte
#define     spl_UByte   unsigned char
#define     spl_SByte   signed char
//---------------------------------------------------------------------------
// Word = 2 Bytes
#define     spl_UWord   unsigned short int
#define     spl_SWord   signed short int
//---------------------------------------------------------------------------
// int = 4 Byte
#define     spl_UInt    unsigned int
#define     spl_SInt    signed int
//---------------------------------------------------------------------------
// int64 = 8 Byte
#define     spl_UInt64  unsigned __int64
#define     spl_SInt64  signed __int64
//---------------------------------------------------------------------------
// Real Types
//---------------------------------------------------------------------------
// Single = 32 Byte
#define     spl_USingle     unsigned float
#define     spl_SSingle     signed float
//---------------------------------------------------------------------------
// Double = 64 Bytes
#define     spl_UDouble     unsigned double
#define     spl_SDouble     signed double
//---------------------------------------------------------------------------
// Extended = 80 Byte
#define     spl_UExtended   unsigned long double
#define     spl_SExtended   signed long double
//---------------------------------------------------------------------------
// Usefull Defines
//---------------------------------------------------------------------------
#define     spl_MaxInt          (2147483647.0) // 2^31 - 1
#define     spl_MaxWord         (65535.0) // 2^16 - 1
#define     spl_MaxImageWidth   (10000.0) 
#define     spl_DisiemPerInch   (254.00050800101600203200406400813)
#define     spl_sqrt2           (1.4142135623730950488016887242097)
#define     spl_sqrt1_2         (0.70710678118654752440084436210485)
#define     spl_PI              (3.1415926535897932384626433832795)
#define     spl_Sign(x)         (((x)>0.0)?1.0:(((x)<0.0)?-1.0:0.0))
#define     spl_Round(x)        ((((x)-int(x))>=0.5)?(int(x)+1):(int(x)))
#define     spl_ABS(x)		    (((x)<0)?-(x):(x))
#define     spl_MIN(a,b)	    (((a)<(b))?(a):(b))
#define     spl_MAX(a,b)	    (((a)>(b))?(a):(b))	
//---------------------------------------------------------------------------
#define     spl_ByteToComp(b)       ((spl_SByte)((((spl_UByte)(b)<=127)?(spl_UByte)(b):(spl_UByte)(b)-256)))
#define     spl_CompToByte(b)       ((spl_UByte)(((spl_SByte)(b)>=0)?(spl_SByte)(b):(spl_SByte)(b)+256))
//---------------------------------------------------------------------------
const int   spl_Power2[8]={1,2,4,8,16,32,64,128};
//---------------------------------------------------------------------------
#define     spl_GetBit(b,i)     ((b) &    spl_Power2[(i)])
#define     spl_SetBit(b,i)     ((b) |=   spl_Power2[(i)])
#define     spl_ClrBit(b,i)     ((b) &= (~spl_Power2[(i)]))
//---------------------------------------------------------------------------
const TPoint spl_T1[9]= {
                            TPoint(+1,00),// 0
                            TPoint(+1,+1),// 1
                            TPoint(00,+1),// 2
                            TPoint(-1,+1),// 3
                            TPoint(-1,00),// 4
                            TPoint(-1,-1),// 5
                            TPoint(00,-1),// 6
                            TPoint(+1,-1),// 7
                            TPoint(00,00),// 8
                        };
//---------------------------------------------------------------------------
const TPoint spl_T1R[9]= {
                            TPoint(+1,00),// 0
                            TPoint(+1,-1),// 7
                            TPoint(00,-1),// 6
                            TPoint(-1,-1),// 5
                            TPoint(-1,00),// 4
                            TPoint(-1,+1),// 3
                            TPoint(00,+1),// 2
                            TPoint(+1,+1),// 1
                            TPoint(00,00),// 8
                        };
//---------------------------------------------------------------------------
struct spl_RGB
{
    Byte r;
    Byte g;
    Byte b;
    bool operator == (const spl_RGB &Color)
    {
        return ((r==Color.r)&&(g==Color.g)&&(b==Color.b));
    }
    bool operator != (const spl_RGB &Color)
    {
        return ((r!=Color.r)||(g!=Color.g)||(b!=Color.b));
    }
};
//---------------------------------------------------------------------------
typedef		vector<int> spl_IntArray;
//---------------------------------------------------------------------------
//  Embroidery Parameters
//---------------------------------------------------------------------------
// Stitching Output
//---------------------------------------------------------------------------
#define     spl_soZigZag        (spl_UByte)0
#define     spl_soTatami        (spl_UByte)1
//---------------------------------------------------------------------------
#define     spl_soRun           (spl_UByte)0
#define     spl_soSatin         (spl_UByte)1
//---------------------------------------------------------------------------
// Adjust Methode 
#define     spl_amMethode0     		(spl_UByte)0
#define     spl_amMethode1         	(spl_UByte)1
#define     spl_amMethode2         	(spl_UByte)2
//---------------------------------------------------------------------------
const  spl_SByte spl_MaxStitchLength = 121;
//---------------------------------------------------------------------------
extern spl_SByte spl_RunStitchStep;
extern spl_SByte spl_JumpStitchStep;
extern spl_SByte spl_MinStitchLength;
extern spl_SByte spl_MinJumpLength;// Then Considered Normal Stitch
extern spl_SByte spl_FillStitchDensity;// Distance Betoween Tow Stitchs On Parallel In Disiem
extern spl_SByte spl_LineStitchDensity;// Distance Betoween Tow Stitchs On Parallel In Disiem
extern spl_SByte spl_SatinHeight;
extern bool spl_AdjustFillStitchs;
extern bool spl_AdjustLineStitchs;
extern bool spl_BestJump;
extern bool spl_ReplaceJump;
extern spl_UByte spl_AdjustMethode;
//---------------------------------------------------------------------------
extern char     spl_Comments[13];
extern spl_UByte spl_FillStitchingOutput;
extern spl_UByte spl_LineStitchingOutput;
extern spl_UWord spl_StitchMargin;
extern bool spl_DesignCentered;
extern double spl_DesignScale;
extern bool spl_ReturnToStartPoint;
//---------------------------------------------------------------------------
extern bool spl_ProcessFillColor;
extern bool spl_ProcessLineColor;
//---------------------------------------------------------------------------
struct spl_EmbParameters
{
    spl_SByte FillStitchDensity;
    spl_SByte LineStitchDensity;
    spl_SByte RunStitchStep;
    spl_SByte SatinHeight;

    spl_UByte FillStitchingOutput;
    spl_UByte LineStitchingOutput;
    spl_UWord StitchMargin;

    spl_UByte Dir;
    spl_UByte StartDir;

    bool AdjustFillStitchs;
    bool AdjustLineStitchs;
};
//---------------------------------------------------------------------------
struct spl_CurveInfo
{
    bool UseGlobalParameters;
    spl_EmbParameters EmbParameters;
};
//---------------------------------------------------------------------------
extern spl_EmbParameters spl_Global_EmbParameters;
//---------------------------------------------------------------------------
#endif
