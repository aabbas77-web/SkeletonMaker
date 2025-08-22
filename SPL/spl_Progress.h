//---------------------------------------------------------------------------

#ifndef spl_ProgressH
#define spl_ProgressH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "FormTranslation.h"
//---------------------------------------------------------------------------
class TFormProgress : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TProgressBar *ProgressBar1;
	TFormTranslation *FormTranslation1;
private:	// User declarations
public:		// User declarations
    __fastcall TFormProgress(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormProgress *FormProgress;
//---------------------------------------------------------------------------
#endif
