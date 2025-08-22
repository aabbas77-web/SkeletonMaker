//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spl_Monochrome.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormMonochrom *FormMonochrom;
//---------------------------------------------------------------------------
__fastcall TFormMonochrom::TFormMonochrom(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMonochrom::TrackBar1Change(TObject *Sender)
{
    Panel2->Caption=IntToStr(TrackBar1->Position);
    Threshold=TrackBar1->Position;
    spl_Monochrome(pImage,Threshold,pResult);
    Image->Picture->Assign(pResult->pBitmap);
}
//---------------------------------------------------------------------------
void __fastcall TFormMonochrom::SpeedButton1Click(TObject *Sender)
{
    spl_GetHistogram(pImage,Histogram);
    Threshold=spl_FisherTow(Histogram);
    if(TrackBar1->Position==Threshold)
        TrackBar1Change(this);
    else
        TrackBar1->Position=Threshold;
}
//---------------------------------------------------------------------------
void __fastcall TFormMonochrom::SpeedButton2Click(TObject *Sender)
{
    spl_GetHistogram(pImage,Histogram);
    Threshold=spl_EntropyTow(Histogram);
    if(TrackBar1->Position==Threshold)
        TrackBar1Change(this);
    else
        TrackBar1->Position=Threshold;
}
//---------------------------------------------------------------------------

void __fastcall TFormMonochrom::SpeedButton3Click(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------

