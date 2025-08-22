//---------------------------------------------------------------------------

#ifndef spl_RasterImageH
#define spl_RasterImageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include "spl_Embroidery.h"
#include <ComCtrls.hpp>
#include "spl_Digitizer.h"
#include "spl_FloodFill.h"
#include "spl_ALICompression.h"
#include "spl_ImportImage.h"
#include <ActnList.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormRasterImage : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *Open1;
    TMenuItem *Save1;
    TScrollBox *ScrollBox1;
    TImage *Image;
    TTimer *Timer1;
    TPanel *Panel1;
    TProgressBar *ProgressBar;
    TStatusBar *StatusBar;
    TSavePictureDialog *SavePictureDialog1;
    TActionList *ActionList1;
    TAction *AFile;
    TAction *AOpenImage;
    TAction *AImportImage;
    TAction *ASaveImage;
    TMenuItem *ImportImage1;
    TOpenPictureDialog *OpenPictureDialog1;
    TAction *AImaging;
    TAction *AResize;
    TMenuItem *Imaging2;
    TMenuItem *Resize1;
    TAction *ARestoreImage;
    TMenuItem *RestoreImage1;
    TAction *AInvert;
    TMenuItem *Invert2;
    TAction *ASmooth;
    TAction *AReverse;
    TMenuItem *Reverse2;
    TMenuItem *Smooth2;
    TAction *AQuantize;
    TMenuItem *Quantize2;
    TAction *ADigitizer;
    TAction *ADigitize;
    TAction *AGray;
    TMenuItem *Gray1;
    TAction *AHelp;
    TAction *AContents;
    TAction *AAbout;
    TMenuItem *Help1;
    TMenuItem *Contents1;
    TMenuItem *N2;
    TMenuItem *About1;
    TAction *AMonochrome;
    TMenuItem *Monochrome1;
	TFormTranslation *FormTranslation1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall ImageMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall ImageMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall AFileExecute(TObject *Sender);
    void __fastcall AOpenImageExecute(TObject *Sender);
    void __fastcall AImportImageExecute(TObject *Sender);
    void __fastcall ASaveImageExecute(TObject *Sender);
    void __fastcall AImagingExecute(TObject *Sender);
    void __fastcall AResizeExecute(TObject *Sender);
    void __fastcall ARestoreImageExecute(TObject *Sender);
    void __fastcall AInvertExecute(TObject *Sender);
    void __fastcall ASmoothExecute(TObject *Sender);
    void __fastcall AReverseExecute(TObject *Sender);
    void __fastcall AQuantizeExecute(TObject *Sender);
    void __fastcall ADigitizerExecute(TObject *Sender);
    void __fastcall ADigitizeExecute(TObject *Sender);
    void __fastcall AGrayExecute(TObject *Sender);
    void __fastcall AHelpExecute(TObject *Sender);
    void __fastcall AContentsExecute(TObject *Sender);
    void __fastcall AAboutExecute(TObject *Sender);
    void __fastcall AMonochromeExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormRasterImage(TComponent* Owner);
    void __fastcall NewImage();
    void __fastcall UpdateImage();
    void __fastcall UpdateStatusBar();

    AnsiString FileName;
    double StartTime,Delay;

    spl_Image *pImage;
    spl_Image *pRestore;
    spl_Image *pResult;
    
    spl_UInt MousePosX,MousePosY;
    TColor MouseColor;
    Byte MouseRed,MouseGreen,MouseBlue;
    WORD ContourIndex,PrevContourIndex,PointIndex;
    TColor ContourColor;
    AnsiString AppPath;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormRasterImage *FormRasterImage;
//---------------------------------------------------------------------------
#endif
