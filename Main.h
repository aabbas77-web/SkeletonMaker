//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "spl_Image.h"
#include "spl_Contour.h"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Open1;
	TMenuItem *N1;
	TMenuItem *Saveas1;
	TMenuItem *N2;
	TMenuItem *Exit1;
	TOpenPictureDialog *OpenPictureDialog;
	TSavePictureDialog *SavePictureDialog;
	TScrollBox *ScrollBox1;
	TStatusBar *StatusBar1;
	TImage *Image;
	TMenuItem *Operations1;
	TMenuItem *Skeletonize1;
	void __fastcall Open1Click(TObject *Sender);
	void __fastcall Saveas1Click(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall Skeletonize1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
	void __fastcall Skeletonize(spl_Image *pImage,spl_Contour &Contour);
//	TPoint __fastcall Neighbour(Byte ANeighbour);
	spl_Point __fastcall Neighbour(Byte ANeighbour);
	void __fastcall ClearImage();
    spl_Image *m_pImage;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
