//---------------------------------------------------------------------------

#ifndef spl_DigitizeDialogH
#define spl_DigitizeDialogH
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
class TFormDigitize : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel2;
    TLabel *Label1;
    TCSpinEdit *CSpinEdit1;
    TLabel *Label2;
    TCSpinEdit *CSpinEdit2;
    TPanel *Panel1;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
	TLabel *Label3;
	TCSpinEdit *CSpinEdit3;
	TFormTranslation *FormTranslation1;
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormDigitize(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDigitize *FormDigitize;
//---------------------------------------------------------------------------
#endif
