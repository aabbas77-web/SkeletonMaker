//---------------------------------------------------------------------------

#ifndef spl_VectorImageH
#define spl_VectorImageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "spl_Digitizer.h"
#include <ActnList.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormVectorImage : public TForm
{
__published:	// IDE-managed Components
    TScrollBox *ScrollBox1;
    TImage *Image;
    TStatusBar *StatusBar;
    TPanel *Panel1;
    TProgressBar *ProgressBar;
    TActionList *ActionList1;
    TAction *AEmbroidery;
	TAction *AEmrboid;
    TMainMenu *MainMenu1;
    TMenuItem *Embroidery1;
    TMenuItem *Emboid1;
    TSaveDialog *SaveDialogEMB;
    TAction *AFile;
    TAction *ASave;
    TMenuItem *File1;
    TMenuItem *Saveas1;
    TSavePictureDialog *SavePictureDialogEMF;
    TAction *AObject;
    TAction *AProperties;
    TMenuItem *Object1;
    TMenuItem *Properties1;
    TPopupMenu *PopupMenuObject;
    TMenuItem *Properties2;
	TAction *AExport;
	TMenuItem *Embroid1;
	TSaveDialog *SaveDialogML;
	TAction *AExportObject;
	TMenuItem *ExportObject1;
	TMenuItem *ExportObject2;
	TSaveDialog *SaveDialogRGN;
	TFormTranslation *FormTranslation1;
    void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall ImageMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall ImageMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall AEmbroideryExecute(TObject *Sender);
    void __fastcall AEmrboidExecute(TObject *Sender);
    void __fastcall AFileExecute(TObject *Sender);
    void __fastcall ASaveExecute(TObject *Sender);
    void __fastcall AObjectExecute(TObject *Sender);
    void __fastcall APropertiesExecute(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall AExportExecute(TObject *Sender);
	void __fastcall AExportObjectExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormVectorImage(TComponent* Owner);
    void __fastcall UpdateStatusBar();

    spl_MultiLayer MultiLayer;
    spl_Contour Contour;

    spl_UInt MousePosX,MousePosY;
    TColor MouseColor;
    Byte MouseRed,MouseGreen,MouseBlue;
    WORD ContourIndex,PrevContourIndex,PointIndex;
    TColor ContourColor;

    spl_Image *pImage;
    spl_Point P1,P2;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormVectorImage *FormVectorImage;
//---------------------------------------------------------------------------
#endif
