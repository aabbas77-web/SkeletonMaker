//---------------------------------------------------------------------------

#include <vcl.h>
#include <registry.hpp>
#pragma hdrstop

#include "spl_EmbOpenDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ShellControls"
#pragma link "ShellLink"
#pragma link "ShellBrowser"
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormEmbOpenDialog *FormEmbOpenDialog;
//---------------------------------------------------------------------------
#define	  	c_strPathKey  	"\\Software\\WWPTC\\PTC Embroidery\\LastPath"
#define	  	c_strPathValue 	"Path"
//---------------------------------------------------------------------------
AnsiString GetLastPath()
{
  	AnsiString S = "";
  	TRegistry *Registry = new TRegistry;
  	try
  	{
    	Registry->RootKey = HKEY_LOCAL_MACHINE;
    	// false because we do not want to create it if it doesn’t exist
    	Registry->OpenKey(c_strPathKey, true);
    	S = Registry->ReadString(c_strPathValue);
  	}
  	__finally
  	{
    	delete Registry;
  	}
  	return S;
}
//---------------------------------------------------------------------------
void SetLastPath(AnsiString strValue)
{
  	TRegistry *Registry = new TRegistry;
  	try
  	{
    	Registry->RootKey = HKEY_LOCAL_MACHINE;
    	// false because we do not want to create it if it doesn’t exist
    	Registry->OpenKey(c_strPathKey, true);
    	Registry->WriteString(c_strPathValue,strValue);
  	}
  	__finally
  	{
    	delete Registry;
  	}
}
//---------------------------------------------------------------------------
__fastcall TFormEmbOpenDialog::TFormEmbOpenDialog(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormEmbOpenDialog::FilterComboBoxChange(TObject *Sender)
{
	JamShellList->Filter = FilterComboBox->Mask;	
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbOpenDialog::ToolButton1Click(TObject *Sender)
{
	JamShellList->GoUp();
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbOpenDialog::FormCreate(TObject *Sender)
{
	JamShellCombo->ItemIndex = 0;
	JamShellList->Filter = spl_EmbFullFilter;
    FilterComboBox->Filter = spl_EmbFullFilter;

    Frame = Rect(0,0,Image->Width,Image->Height);

    pBitmap = new Graphics::TBitmap();
	pBitmap->Width = Image->Width;
	pBitmap->Height = Image->Height;

    JamShellList->Path = GetLastPath();
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbOpenDialog::FormDestroy(TObject *Sender)
{
	if(pBitmap)
    {
     	delete pBitmap;
        pBitmap = NULL;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbOpenDialog::JamShellListDblClick(TObject *Sender)
{
	if(JamShellList->SelectedFiles->Count <= 0)	return;
    FileName = IncludeTrailingBackslash(JamShellList->Path)+JamShellList->SelectedFiles->Strings[0];
    if(FileExists(FileName))
    {
		Edit->Text = JamShellList->SelectedFiles->Strings[0];
        ModalResult = mrOk;
    }
    else
    {
		JamShellList->InvokeCommandOnSelected("default");
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbOpenDialog::JamShellListChange(TObject *Sender,
      TListItem *Item, TItemChange Change)
{
	if(JamShellList->SelectedFiles->Count <= 0)	return;
    FileName = IncludeTrailingBackslash(JamShellList->Path)+JamShellList->SelectedFiles->Strings[0];
    if(FileExists(FileName))
    {
    	pBitmap->Canvas->FillRect(Frame);
		if(CheckBoxPreview->Checked)
        {
	        spl_LoadEmbFromFile(FileName,StitchPath,&EmbHeader,NULL);
	        spl_StitchStretchDraw(StitchPath,&EmbHeader,pBitmap,Frame,5,false,false,false);

	        PanelComment->Caption=EmbHeader.Comments;
	        PanelTotalStitchs->Caption=IntToStr(EmbHeader.StitchsCount);
	        PanelNormalStitchs->Caption=IntToStr(EmbHeader.NormalStitchs);
	        PanelJumpStitchs->Caption=IntToStr(EmbHeader.JumpStitchs);
	        PanelColorStitchs->Caption=IntToStr(EmbHeader.ColorStitchs);
	        wd=EmbHeader.right-EmbHeader.left;
    	    hd=EmbHeader.bottom-EmbHeader.top;
	        PanelWidth->Caption=FormatFloat("0.0",wd/10.0);
	        PanelHeight->Caption=FormatFloat("0.0",hd/10.0);
    	}
        Image->Picture->Assign(pBitmap);
	    Edit->Text = JamShellList->SelectedFiles->Strings[0];
    }
    else
    {
		Edit->Text = "";
    }
    SetLastPath(JamShellList->Path);
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbOpenDialog::JamShellListMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(Button != mbRight)	return;
	if(JamShellList->SelectedFiles->Count <= 0)	return;
    JamShellList->ShowContextMenu(Mouse->CursorPos);
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbOpenDialog::CheckBoxPreviewClick(TObject *Sender)
{
	JamShellListChange(Sender,NULL,ctState);
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbOpenDialog::ToolButton2Click(TObject *Sender)
{
	JamShellList->CreateDir("",true);
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbOpenDialog::Icon2Click(TObject *Sender)
{
	JamShellList->ViewStyle = vsIcon; 	
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbOpenDialog::List1Click(TObject *Sender)
{
	JamShellList->ViewStyle = vsList; 	
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbOpenDialog::Report1Click(TObject *Sender)
{
	JamShellList->ViewStyle = vsReport;
}
//---------------------------------------------------------------------------

void __fastcall TFormEmbOpenDialog::SmallIcon1Click(TObject *Sender)
{
	JamShellList->ViewStyle = vsSmallIcon; 	
}
//---------------------------------------------------------------------------

