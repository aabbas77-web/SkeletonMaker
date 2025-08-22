//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spl_DigitizeDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormDigitize *FormDigitize;
//---------------------------------------------------------------------------
__fastcall TFormDigitize::TFormDigitize(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormDigitize::SpeedButton1Click(TObject *Sender)
{
    ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormDigitize::SpeedButton2Click(TObject *Sender)
{
    ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

