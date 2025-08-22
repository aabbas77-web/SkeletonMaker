//---------------------------------------------------------------------------

#ifndef spl_InsertTextH
#define spl_InsertTextH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormInsertText : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TRichEdit *RichEdit;
	TPanel *Panel2;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TToolBar *ToolBar2;
	TToolButton *ToolButton4;
	TFontDialog *FontDialog;
	TLabel *Label;
	TFormTranslation *FormTranslation1;
	void __fastcall ToolButton4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormInsertText(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInsertText *FormInsertText;
//---------------------------------------------------------------------------
#endif
