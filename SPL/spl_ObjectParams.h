//---------------------------------------------------------------------------

#ifndef spl_ObjectParamsH
#define spl_ObjectParamsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include "spl_EmbFile.h"
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormObjectParams : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TGroupBox *GroupBox1;
    TLabel *Label3;
    TLabel *Label4;
    TCSpinEdit *CSpinEdit3;
    TCSpinEdit *CSpinEdit4;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TGroupBox *GroupBox2;
    TCheckBox *CheckBox2;
    TComboBox *ComboBox5;
    TLabel *Label10;
    TComboBox *ComboBox6;
    TCheckBox *CheckBox1;
    TComboBox *ComboBox4;
    TBevel *Bevel1;
    TBevel *Bevel2;
    TLabel *Label9;
    TCSpinEdit *CSpinEdit7;
    TLabel *Label12;
    TComboBox *ComboBox1;
    TLabel *Label6;
    TComboBox *ComboBox2;
    TLabel *Label7;
    TLabel *Label8;
    TCSpinEdit *CSpinEdit6;
    TComboBox *ComboBox3;
    TLabel *Label1;
    TCSpinEdit *CSpinEdit1;
	TPanel *Panel3;
	TImage *Image1;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox4;
	TFormTranslation *FormTranslation1;
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ComboBox4DrawItem(TWinControl *Control, int Index,
          TRect &Rect, TOwnerDrawState State);
private:	// User declarations
public:		// User declarations
    __fastcall TFormObjectParams(TComponent* Owner);
    spl_UInt ObjectIndex;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormObjectParams *FormObjectParams;
//---------------------------------------------------------------------------
#endif
