//---------------------------------------------------------------------------

#ifndef spl_EmbOpenDialogH
#define spl_EmbOpenDialogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "ShellControls.hpp"
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <FileCtrl.hpp>
#include "ShellLink.hpp"
#include "ShellBrowser.hpp"
//---------------------------------------------------------------------------
#include "spl_EmbLib.h"
#include <Menus.hpp>
#include <ImgList.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormEmbOpenDialog : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel5;
	TJamShellCombo *JamShellCombo;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TPanel *Panel6;
	TPanel *Panel7;
	TButton *Button1;
	TButton *Button2;
	TEdit *Edit;
	TLabel *Label1;
	TLabel *Label2;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TPanel *PanelJumpStitchs;
	TPanel *PanelNormalStitchs;
	TPanel *PanelTotalStitchs;
	TPanel *PanelComment;
	TPanel *PanelColorStitchs;
	TPanel *PanelWidth;
	TPanel *PanelHeight;
	TFilterComboBox *FilterComboBox;
	TPanel *Panel8;
	TJamShellList *JamShellList;
	TJamShellLink *JamShellLink;
	TCheckBox *CheckBoxPreview;
	TPanel *Panel9;
	TImage *Image;
	TMainMenu *MainMenu1;
	TMenuItem *ViewStyle1;
	TMenuItem *Icon2;
	TMenuItem *List1;
	TMenuItem *Report1;
	TMenuItem *SmallIcon1;
	TImageList *ImageList;
	TCheckBox *CheckBoxShowJumps;
	TFormTranslation *FormTranslation1;
	void __fastcall FilterComboBoxChange(TObject *Sender);
	void __fastcall ToolButton1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall JamShellListDblClick(TObject *Sender);
	void __fastcall JamShellListChange(TObject *Sender, TListItem *Item,
          TItemChange Change);
	void __fastcall JamShellListMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall CheckBoxPreviewClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ToolButton2Click(TObject *Sender);
	void __fastcall Icon2Click(TObject *Sender);
	void __fastcall List1Click(TObject *Sender);
	void __fastcall Report1Click(TObject *Sender);
	void __fastcall SmallIcon1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormEmbOpenDialog(TComponent* Owner);
    AnsiString FileName;
    Graphics::TBitmap *pBitmap;
    TRect Frame;
    spl_EmbHeader EmbHeader;
    spl_StitchPath StitchPath;
    double wd,hd;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormEmbOpenDialog *FormEmbOpenDialog;
//---------------------------------------------------------------------------
#endif
