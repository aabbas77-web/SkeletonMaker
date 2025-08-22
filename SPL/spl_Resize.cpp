//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spl_Resize.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormResize *FormResize;
//---------------------------------------------------------------------------
__fastcall TFormResize::TFormResize(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormResize::SpeedButton1Click(TObject *Sender)
{
    ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormResize::SpeedButton2Click(TObject *Sender)
{
    ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFormResize::FormCreate(TObject *Sender)
{
    Ratio=1.0;// Ratio = Width / Height
    ComboBox1->ItemIndex=4;// Spline
}
//---------------------------------------------------------------------------
void __fastcall TFormResize::Edit2Change(TObject *Sender)
{
    if(SetWidth)  return;

    double Value;
    try
    {
        Value=StrToFloat(Edit2->Text);
    }
    catch(...)
    {
        return;
    }

    if((Value!=NewWidth)&&(Value>0.0))
    {
        NewWidth=Value;

        if(CheckBox1->Checked)
        {
            NewHeight=NewWidth/Ratio;
            SetHeight=true;
            Edit3->Text=FormatFloat("0",NewHeight);
            SetHeight=false;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormResize::Edit3Change(TObject *Sender)
{
    if(SetHeight)  return;

    double Value;
    try
    {
        Value=StrToFloat(Edit3->Text);
    }
    catch(...)
    {
        return;
    }

    if((Value!=NewHeight)&&(Value>0.0))
    {
        NewHeight=Value;

        if(CheckBox1->Checked)
        {
            NewWidth=NewHeight*Ratio;
            SetWidth=true;
            Edit2->Text=FormatFloat("0",NewWidth);
            SetWidth=false;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormResize::FormActivate(TObject *Sender)
{
    SetWidth=false;
    SetHeight=false;

    Edit2->Text=FormatFloat("0",NewWidth);
    Edit3->Text=FormatFloat("0",NewHeight);
}
//---------------------------------------------------------------------------
