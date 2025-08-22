//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spl_InsertText.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormInsertText *FormInsertText;
//---------------------------------------------------------------------------
__fastcall TFormInsertText::TFormInsertText(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormInsertText::ToolButton4Click(TObject *Sender)
{
	if(FontDialog->Execute())
    {
		RichEdit->Font->Assign(FontDialog->Font);
		Label->Font->Assign(FontDialog->Font);
        ToolButton4->Caption = FontDialog->Font->Name;
    }
}
//---------------------------------------------------------------------------
