//---------------------------------------------------------------------------

#ifndef spl_ImportImageH
#define spl_ImportImageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "EnImgScr.hpp" // for TImageScrollBox
#include "EnScan.hpp"   // for TScanner
#include "EnDiGrph.hpp" // for TDibGraphic

#include "EnDcxGr.hpp"  // for TDcxGraphic
#include "EnPrint.hpp"  // for TEnvisionPrintMode, TDibGraphicPrinter
#include "EnMisc.hpp"   // for MinFloat
#include "EnTransf.hpp" // for TImageTransform
#include "EnTifGr.hpp"  // for TTifGraphic
#include "EnBmpGr.hpp"  // for TBitmapGraphic
#include "EnIcoGr.hpp"  // for TIconGraphic
#include "EnWmfGr.hpp"  // for TMetaFileGraphic
#include "EnReg.hpp"    // for image format registration

#include "extdlgs.hpp"  // for TOpenPictureDialog
//---------------------------------------------------------------------------
#include <ImgList.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include "spl_Point.h"
#include "FormTranslation.h"
//---------------------------------------------------------------------------
struct TScanInfo
{
 bool MultiPage;

 // supplementary info when MultiPage is True
 TTiffGraphic *Graphic;
 TFileStream *Stream;
 long int ImageCount;
};
typedef TScanInfo *TpScanInfo;
//---------------------------------------------------------------------------
class TFormImportImage : public TForm
{
__published:	// IDE-managed Components
    TToolBar *ToolBar1;
    TToolButton *ToolButton3;
    TPanel *Panel1;
    TImageScrollBox *ImageScrollBox;
    TImageList *ImageList1;
    TOpenPictureDialog *OpenPictureDialog1;
    TSavePictureDialog *SavePictureDialog1;
    TToolButton *ToolButton4;
    TPanel *Panel2;
    TPanel *Panel3;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton1;
	TFormTranslation *FormTranslation1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ToolButton4Click(TObject *Sender);
    void __fastcall ToolButton3Click(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall Panel2Resize(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormImportImage(TComponent* Owner);
    void CheckDirty();
    void __fastcall OnAcquire(const THandle DibHandle,const Word XDpi,const Word YDpi,const int CallBackData);

    bool FDirty;
    AnsiString FileName;
    AnsiString FMultiPageFileName;
    TScanner* FScanner;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImportImage *FormImportImage;
//---------------------------------------------------------------------------
#endif
