//---------------------------------------------------------------------------

#ifndef spl_ResizeH
#define spl_ResizeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormResize : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TLabel *Label9;
    TEdit *Edit2;
    TEdit *Edit3;
    TLabel *Label10;
    TCheckBox *CheckBox1;
    TLabel *Label1;
    TComboBox *ComboBox1;
	TFormTranslation *FormTranslation1;
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Edit2Change(TObject *Sender);
    void __fastcall Edit3Change(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormResize(TComponent* Owner);
    double Ratio;
    double NewWidth;// Pixel
    double NewHeight;// Pixel
    double ImageWidth;// Pixel
    double ImageHeight;// Pixel

    bool SetWidth;
    bool SetHeight;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormResize *FormResize;
//---------------------------------------------------------------------------
#endif
