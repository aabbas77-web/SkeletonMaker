//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spl_ObjectParams.h"
#include "spl_ColorQuantizer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormObjectParams *FormObjectParams;
//---------------------------------------------------------------------------
__fastcall TFormObjectParams::TFormObjectParams(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormObjectParams::SpeedButton1Click(TObject *Sender)
{
    spl_EmbParameters EmbParameters;
    EmbParameters.FillStitchDensity=CSpinEdit3->Value;
    EmbParameters.LineStitchDensity=CSpinEdit1->Value;
    EmbParameters.RunStitchStep=CSpinEdit4->Value;

    EmbParameters.FillStitchingOutput=ComboBox1->ItemIndex;
    EmbParameters.LineStitchingOutput=ComboBox6->ItemIndex;
    EmbParameters.StitchMargin=CSpinEdit6->Value;
    EmbParameters.SatinHeight=CSpinEdit7->Value;

    EmbParameters.Dir=ComboBox2->ItemIndex;
    EmbParameters.StartDir=ComboBox3->ItemIndex;

    EmbParameters.AdjustFillStitchs = CheckBox3->Checked;
    EmbParameters.AdjustLineStitchs = CheckBox4->Checked;

    spl_GlobalCurves[ObjectIndex].FillColorIndex=ComboBox4->ItemIndex;
    spl_GlobalCurves[ObjectIndex].LineColorIndex=ComboBox5->ItemIndex;
    spl_GlobalCurves[ObjectIndex].ProcessFillColor=CheckBox1->Checked;
    spl_GlobalCurves[ObjectIndex].ProcessLineColor=CheckBox2->Checked;
    spl_GlobalCurves[ObjectIndex].ProcessFillColor=CheckBox1->Checked;
    spl_GlobalCurves[ObjectIndex].ProcessLineColor=CheckBox2->Checked;
    spl_GlobalCurves[ObjectIndex].CurveInfo.UseGlobalParameters=false;
    spl_GlobalCurves[ObjectIndex].CurveInfo.EmbParameters=EmbParameters;

    ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormObjectParams::SpeedButton2Click(TObject *Sender)
{
    ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFormObjectParams::FormCreate(TObject *Sender)
{
    ComboBox1->ItemIndex=0;    
    ComboBox6->ItemIndex=1;    
    ComboBox2->ItemIndex=1;
    ComboBox3->ItemIndex=1;
}
//---------------------------------------------------------------------------

void __fastcall TFormObjectParams::ComboBox4DrawItem(TWinControl *Control,
      int Index, TRect &Rect, TOwnerDrawState State)
{
    TComboBox *pComboBox=(TComboBox *)Control;
    if(!pComboBox)  return;

    pComboBox->Canvas->Brush->Style=bsSolid;

    // Clear
    pComboBox->Canvas->Brush->Color=pComboBox->Color;
    pComboBox->Canvas->FillRect(Rect);

    pComboBox->Canvas->Brush->Color=(TColor)spl_QuantizedColors[Index];
    if(Index<pComboBox->Items->Count-1)
        pComboBox->Canvas->FillRect(::Rect(Rect.left+1,Rect.top+1,Rect.right-1,Rect.bottom));
    else
        pComboBox->Canvas->FillRect(::Rect(Rect.left+1,Rect.top+1,Rect.right-1,Rect.bottom-1));
    pComboBox->Canvas->TextOut(Rect.left+2,Rect.top+1,FormatFloat("Color 00",Index));
}
//---------------------------------------------------------------------------

