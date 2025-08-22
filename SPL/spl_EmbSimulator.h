//---------------------------------------------------------------------------
#ifndef spl_EmbSimulatorH
#define spl_EmbSimulatorH
//---------------------------------------------------------------------------
#include "G32_Image.hpp"
#include "spl_EmbFile.h"
#include "spl_Contour.h"
//---------------------------------------------------------------------------
class spl_EmbSimulator
{
private:
    int m_nInterval;
    void SetInterval(int Value);
public:
    spl_EmbSimulator(spl_UInt Interval);
    ~spl_EmbSimulator();

    AnsiString m_strFileName;
    spl_Scale m_Scale;
    double m_dHeight;
    double Ax2,Ay2;
    spl_UInt m_nColorsCount;

    TBitmap32 *m_pBitmap;
    TProgressBar *m_pProgressBar;
    TBitmap32 *m_pBk;

    spl_UInt m_nBlockSize;
    spl_StitchPath m_StitchPath;
    spl_EmbHeader m_EmbHeader;
    spl_Rect m_Frame;
    bool m_bShowJumps;
    TColor32 m_BackgroundColor;
    spl_UByte m_Alpha;
    bool m_bLoaded;
    spl_SInt m_ndX;
    spl_SInt m_ndY;
    int m_nWidth;
    int m_nHeight;

    void LoadFromFile(AnsiString FileName);
    void SaveToFile(AnsiString FileName);
    void Show(bool Colored,TColor32 DisableColor);
    void Update();
    void Clear();
    void Start();
    void Play();
    void Pause();
    void Stop();
    void PlayTo(spl_UInt ToIndex);
    spl_UInt GetPosition();
    bool Bof();
    bool Eof();
    void FlushAndFree();
    __property int Interval={read=m_nInterval,write=SetInterval};
};
//---------------------------------------------------------------------------
void spl_StitchStretchDraw32(spl_StitchPath &StitchPath,spl_EmbHeader &EmbHeader,TBitmap32 *pBMP,spl_Rect &Frame,spl_Scale &Scale,TColor32 ClearColor,spl_UByte Alpha,bool ShowJumps,bool Colored,TColor32 DisableColor);
void NextStitch();
//---------------------------------------------------------------------------
extern spl_EmbSimulator *pEmbSimulator;
//---------------------------------------------------------------------------
#endif
