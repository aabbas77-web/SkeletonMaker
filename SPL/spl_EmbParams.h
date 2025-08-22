//---------------------------------------------------------------------------

#ifndef spl_EmbParamsH
#define spl_EmbParamsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormEmbParams : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TGroupBox *GroupBox1;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TGroupBox *GroupBox2;
    TLabel *Label12;
    TComboBox *ComboBox1;
    TLabel *Label6;
    TComboBox *ComboBox2;
    TComboBox *ComboBox3;
    TLabel *Label7;
    TLabel *Label8;
    TCSpinEdit *CSpinEdit6;
    TLabel *Label11;
    TEdit *Edit1;
    TBevel *Bevel2;
    TCheckBox *CheckBox1;
    TBevel *Bevel3;
    TLabel *Label9;
    TLabel *Label10;
    TEdit *Edit2;
    TEdit *Edit3;
    TBevel *Bevel4;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label5;
    TCSpinEdit *CSpinEdit5;
    TCSpinEdit *CSpinEdit2;
    TCSpinEdit *CSpinEdit1;
    TLabel *Label4;
    TCSpinEdit *CSpinEdit4;
    TLabel *Label3;
    TCSpinEdit *CSpinEdit3;
    TGroupBox *GroupBox3;
    TLabel *Label14;
    TLabel *Label13;
    TLabel *Label15;
    TCSpinEdit *CSpinEdit8;
    TCSpinEdit *CSpinEdit7;
    TComboBox *ComboBox4;
    TCheckBox *CheckBox2;
    TCheckBox *CheckBox3;
    TCheckBox *CheckBox4;
	TPanel *Panel3;
	TImage *Image1;
	TCheckBox *CheckBox5;
	TCheckBox *CheckBox6;
	TCheckBox *CheckBoxBestJump;
	TComboBox *ComboBoxAdjustMethode;
	TCheckBox *CheckBoxReplaceJump;
	TFormTranslation *FormTranslation1;
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Edit2Change(TObject *Sender);
    void __fastcall Edit3Change(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormEmbParams(TComponent* Owner);
    double Ratio;
    double DesignWidth;// cm
    double DesignHeight;// cm
    double ImageWidth;// Pixel
    double ImageHeight;// Pixel
    double ScaleX;
    double ScaleY;

    bool SetDesignWidth;
    bool SetDesignHeight;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormEmbParams *FormEmbParams;
//---------------------------------------------------------------------------
#endif
