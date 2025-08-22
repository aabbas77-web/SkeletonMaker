//---------------------------------------------------------------------------
#ifndef spl_ImageH
#define spl_ImageH
//---------------------------------------------------------------------------
#include <Graphics.hpp>
#include "spl_Types.h"
//---------------------------------------------------------------------------
// Support: 1,8,16,24,32 Bits Images
// Data Stored As:
// 0 1 2 3 4 5 6 7 8 9 ...

// In R Mode (1 And 8 bits):
// R R R R R R R R R R ...

// In RGB Mode (16 bits):(C= Contour Index)
// C C C C C C C C C C ...

// In RGB Mode (24 bits):
// B G R B G R B G R ...

// In RGBI Mode (32 bits):(I: Color Index)
// I B G R I B G R I B G R ...
//---------------------------------------------------------------------------
#define spl_GetPixel_1bit(x,y,pImage) ((((pImage)->ppLines[(y)][(x)>>3])&(0x80>>((x)&0x7)))!=0)
#define spl_SetPixel_1bit(x,y,Color,pImage) (Color ? ((pImage)->ppLines[(y)][(x)>>3] |= (0x80>>((x) & 0x7))) : ((pImage)->ppLines[(y)][(x)>>3] &= (0xff7f>>((x) & 0x7))))
//---------------------------------------------------------------------------
#define spl_GetIValue32(rgbi) ( (spl_UByte)((spl_UInt)(rgbi) >> 24) )
#define spl_GetBValue32(rgbi) ( (spl_UByte)((spl_UInt)(rgbi) >> 16) )
#define spl_GetGValue32(rgbi) ( (spl_UByte)((spl_UInt)(rgbi) >> 8 ) )
#define spl_GetRValue32(rgbi) ( (spl_UByte)((spl_UInt)(rgbi)      ) )
//---------------------------------------------------------------------------
#define spl_RGBI32(r,g,b,i) ( ((spl_UInt)((spl_UByte)(r))) | ((spl_UInt)((spl_UByte)(g)) << 8) | ((spl_UInt)((spl_UByte)(b)) << 16) | ((spl_UInt)((spl_UByte)(i)) << 24) )
//---------------------------------------------------------------------------
#define spl_GetLoWord(dw) ( (spl_UWord)((spl_UInt)(dw)      ) )
#define spl_GetHiWord(dw) ( (spl_UWord)((spl_UInt)(dw) >> 16) )
//---------------------------------------------------------------------------
#define spl_DWORD(lw,hw)  ( ((spl_UInt)((spl_UWord)(lw))) | ((spl_UInt)((spl_UWord)(hw)) << 16) )
//---------------------------------------------------------------------------
#define spl_GetLoByte(w) ( (spl_UByte)((spl_UWord)(w)     ) )
#define spl_GetHiByte(w) ( (spl_UByte)((spl_UWord)(w) >> 8) )
//---------------------------------------------------------------------------
#define spl_WORD(lb,hb)  ( ((spl_UWord)((spl_UByte)(lb))) | ((spl_UWord)((spl_UByte)(hb)) << 8) )
//---------------------------------------------------------------------------
typedef struct
{
    TLogPalette lpal;
    TPaletteEntry dummy[256];
} LogPal;
//---------------------------------------------------------------------------
class spl_Image
{
    private:
        void Allocate();
        void DeAllocate();
//        void UpdateLines();
    public:
        spl_Image();
        ~spl_Image();

        // Read Only Properties
        Graphics::TBitmap *pBitmap;
        spl_UByte **ppLines;
        spl_UInt Width;// In Pixel
        spl_UInt Height;// In Pixel
        spl_UByte Border;
        spl_UInt LineSize;// In Byte
        spl_UInt ImageSize;// In Byte (Including Zero Padding)
        spl_UByte Bits;// (1,8,16,24,32) <Default = 1>
        bool Updated;// (Read Only)

        // Call <UpdateLines> After Any Change in Data Size
        // Then (ppLines) Became Available
        // After:
        // 1- Changing Image (Width,Height,PixelFormat)
        // 2- Loading Image
        // 3- Assign Image
        // 3- Changing Image Palette
        void UpdateLines();

        void LoadFromFile(AnsiString FileName);
        void LoadFromFile(AnsiString FileName,TPixelFormat pf);
        void SaveToFile(AnsiString FileName);
        void Assign(spl_Image *pImage);
        void Assign(spl_Image *pImage,spl_UInt W,spl_UInt H);
        void Assign(spl_Image *pImage,TPixelFormat pf);
        void Assign(spl_Image *pImage,spl_UInt W,spl_UInt H,TPixelFormat pf);
        void Assign(TPersistent *pSource);
        void SetWidth(spl_UInt W);
        void SetHeight(spl_UInt H);
        void SetSize(spl_UInt W,spl_UInt H);
        void SetPixelFormat(TPixelFormat pf);
        void SetAll(spl_UInt W,spl_UInt H,TPixelFormat pf);
        void SetFrame(spl_UInt W,spl_UInt Color);
        void Clear();
        void AutoFrame(spl_UByte Border,bool MaxMethode);
		void CreateMonochromePalette();
};
//---------------------------------------------------------------------------
#endif
