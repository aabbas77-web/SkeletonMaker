//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spl_EmbParams.h"
#include "spl_EmbFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormEmbParams *FormEmbParams;
//---------------------------------------------------------------------------
__fastcall TFormEmbParams::TFormEmbParams(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormEmbParams::SpeedButton1Click(TObject *Sender)
{
    spl_MinStitchLength=CSpinEdit1->Value;
    spl_MinJumpLength=CSpinEdit2->Value;
    spl_Global_EmbParameters.FillStitchDensity=CSpinEdit3->Value;
    spl_Global_EmbParameters.LineStitchDensity=CSpinEdit8->Value;
    spl_Global_EmbParameters.RunStitchStep=CSpinEdit4->Value;
    spl_JumpStitchStep=CSpinEdit5->Value;

    spl_Global_EmbParameters.FillStitchingOutput=ComboBox1->ItemIndex;
    spl_Global_EmbParameters.LineStitchingOutput=ComboBox4->ItemIndex;
    spl_Global_EmbParameters.StitchMargin=CSpinEdit6->Value;
    spl_Global_EmbParameters.SatinHeight=CSpinEdit7->Value;

    spl_Global_EmbParameters.Dir=ComboBox2->ItemIndex;
    spl_Global_EmbParameters.StartDir=ComboBox3->ItemIndex;

    strcpy(spl_Comments,Edit1->Text.c_str());
    spl_Global_StartPoint=splPoint(0,0);
    spl_Global_k=splPoint(spl_K1[spl_Global_Dir].x,spl_K1[spl_Global_Dir].y);
    spl_Global_n=splPoint(spl_Global_k.x,-spl_Global_k.y);

    spl_DesignCentered=CheckBox1->Checked;

    spl_ProcessFillColor=CheckBox2->Checked;
    spl_ProcessLineColor=CheckBox3->Checked;

    spl_ReturnToStartPoint=CheckBox4->Checked;

    spl_Global_EmbParameters.AdjustFillStitchs = CheckBox5->Checked;
    spl_Global_EmbParameters.AdjustLineStitchs = CheckBox6->Checked;

    spl_BestJump = CheckBoxBestJump->Checked;
    spl_ReplaceJump = CheckBoxReplaceJump->Checked;
    spl_AdjustMethode = ComboBoxAdjustMethode->ItemIndex;

    ModalResult=mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormEmbParams::SpeedButton2Click(TObject *Sender)
{
    ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFormEmbParams::FormCreate(TObject *Sender)
{
    ComboBox1->ItemIndex=0;    
    ComboBox4->ItemIndex=1;    
    ComboBox2->ItemIndex=1;
    ComboBox3->ItemIndex=1;
    ComboBoxAdjustMethode->ItemIndex = 0;

    Ratio=1.0;// Ratio = Width / Height

    spl_Global_EmbParameters.FillStitchDensity=spl_FillStitchDensity;
    spl_Global_EmbParameters.LineStitchDensity=spl_LineStitchDensity;
    spl_Global_EmbParameters.RunStitchStep=spl_RunStitchStep;
    spl_Global_EmbParameters.SatinHeight=spl_SatinHeight;
    spl_Global_EmbParameters.FillStitchingOutput=spl_FillStitchingOutput;
    spl_Global_EmbParameters.LineStitchingOutput=spl_LineStitchingOutput;
    spl_Global_EmbParameters.StitchMargin=spl_StitchMargin;
    spl_Global_EmbParameters.Dir=spl_Global_Dir;
    spl_Global_EmbParameters.StartDir=spl_Global_StartDir;
    spl_Global_EmbParameters.AdjustFillStitchs=spl_AdjustFillStitchs;
    spl_Global_EmbParameters.AdjustLineStitchs=spl_AdjustLineStitchs;
}
//---------------------------------------------------------------------------
void __fastcall TFormEmbParams::Edit2Change(TObject *Sender)
{
    if(SetDesignWidth)  return;

    double Value;
    try
    {
        Value=StrToFloat(Edit2->Text);
    }
    catch(...)
    {
        return;
    }

    if((Value!=DesignWidth)&&(Value>0.0))
    {
        DesignWidth=Value;
        DesignHeight=DesignWidth/Ratio;

        ScaleX=(DesignWidth*100.0)/ImageWidth;
        ScaleY=(DesignHeight*100.0)/ImageHeight;
        spl_DesignScale=spl_MAX(ScaleX,ScaleY);

        SetDesignHeight=true;
        Edit3->Text=FormatFloat("0.00",DesignHeight);
        SetDesignHeight=false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbParams::Edit3Change(TObject *Sender)
{
    if(SetDesignHeight)  return;

    double Value;
    try
    {
        Value=StrToFloat(Edit3->Text);
    }
    catch(...)
    {
        return;
    }

    if((Value!=DesignHeight)&&(Value>0.0))
    {
        DesignHeight=Value;
        DesignWidth=DesignHeight*Ratio;

        ScaleX=(DesignWidth*100.0)/ImageWidth;
        ScaleY=(DesignHeight*100.0)/ImageHeight;
        spl_DesignScale=spl_MAX(ScaleX,ScaleY);

        SetDesignWidth=true;
        Edit2->Text=FormatFloat("0.00",DesignWidth);
        SetDesignWidth=false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbParams::FormActivate(TObject *Sender)
{
    SetDesignWidth=false;
    SetDesignHeight=false;

    Edit2->Text=FormatFloat("0.00",DesignWidth);
    Edit3->Text=FormatFloat("0.00",DesignHeight);
}
//---------------------------------------------------------------------------

