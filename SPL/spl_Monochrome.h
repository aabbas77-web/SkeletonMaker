//---------------------------------------------------------------------------

#ifndef spl_MonochromeH
#define spl_MonochromeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include "spl_ImageProcessing.h"
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormMonochrom : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TGroupBox *GroupBox1;
    TTrackBar *TrackBar1;
    TPanel *Panel2;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
	TFormTranslation *FormTranslation1;
    void __fastcall TrackBar1Change(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormMonochrom(TComponent* Owner);
    spl_UByte Threshold;
    spl_Histogram Histogram;
    spl_Image *pImage;
    spl_Image *pResult;
    TImage *Image;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMonochrom *FormMonochrom;
//---------------------------------------------------------------------------
#endif
