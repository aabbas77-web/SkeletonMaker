//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spl_ImportImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "EnImgScr"
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormImportImage *FormImportImage;
//---------------------------------------------------------------------------
__fastcall TFormImportImage::TFormImportImage(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TFormImportImage::CheckDirty()
{
    // don't check if dirty with multi image files, as multi images files
    // are not saved as a single entity, ie, "append" is used.
    if(FDirty && (FMultiPageFileName == ""))
    {
        switch(MessageDlg("Image is not saved. Save it?",
                            mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo<<mbCancel,0))
        {
            case mrYes:
            {
                ToolButton4Click(this);
                break;
            }
            case mrCancel:
            {
                Abort;
                break;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormImportImage::OnAcquire(const THandle DibHandle,const Word XDpi,const Word YDpi,const int CallBackData)
{
    TDibGraphic *Graphic;
    TpScanInfo pScanInfo;

    pScanInfo = TpScanInfo(CallBackData);

    if((*pScanInfo).MultiPage)
    {
        (*pScanInfo).Graphic->AssignFromDIBHandle(DibHandle);
        (*pScanInfo).Graphic->XDotsPerInch = XDpi;
        (*pScanInfo).Graphic->YDotsPerInch = YDpi;

        if((*pScanInfo).Graphic->ImageFormat == ifBlackWhite)
            (*pScanInfo).Graphic->Compression = tcGroup4;
        else if((*pScanInfo).Graphic->ImageFormat == ifTrueColor)
            (*pScanInfo).Graphic->Compression = tcJPEG;
        else
            (*pScanInfo).Graphic->Compression = tcPackbits;

        (*pScanInfo).Stream->Seek(0, soFromBeginning);
        if((*pScanInfo).ImageCount == 0)
            (*pScanInfo).Graphic->SaveToStream((*pScanInfo).Stream);
        else
            (*pScanInfo).Graphic->AppendToStream((*pScanInfo).Stream);

        // display some visual feedback by displaying each image
        // scanned one by one.
        ImageScrollBox->Graphic = (*pScanInfo).Graphic;
        this->FDirty    = false;

        Application->ProcessMessages();

        (*pScanInfo).ImageCount++;
    }
    else
    {
        Graphic = new TDibGraphic();
        try
        {
            Graphic->AssignFromDIBHandle(DibHandle);
            Graphic->XDotsPerInch = XDpi;
            Graphic->YDotsPerInch = YDpi;

            ImageScrollBox->Graphic = Graphic;
            ImageScrollBox->Redraw(true);
        }
        __finally
        {
            if(Graphic) delete Graphic;
        }

        this->FDirty    = true;
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFormImportImage::FormCreate(TObject *Sender)
{
    FScanner=new TScanner();
}
//---------------------------------------------------------------------------
void __fastcall TFormImportImage::FormDestroy(TObject *Sender)
{
    if(FScanner)    delete FScanner;
}
//---------------------------------------------------------------------------
void __fastcall TFormImportImage::ToolButton4Click(TObject *Sender)
{
    if(SavePictureDialog1->Execute())
    {
        FileName = SavePictureDialog1->FileName;

        if(ExtractFileExt(FileName) == "")
        {
            MessageDlg(" An extension must be specifed to indicate\n the file format.",
                        mtConfirmation,TMsgDlgButtons()<<mbOK,0);
            return;
        }

        if(ImageScrollBox->Graphic==NULL)   return;

        ImageScrollBox->SaveToFile(FileName);

        FDirty = false;

        Caption = FileName;
    }           
}
//---------------------------------------------------------------------------

void __fastcall TFormImportImage::ToolButton3Click(TObject *Sender)
{
    TSaveDialog *SaveDialog;
    TScanInfo *ScanInfo=new TScanInfo();
    AnsiString FileName;

    CheckDirty();

    if(!FScanner->IsConfigured())
    {
        ShowMessage("A scanner is not configured on your computer");
        return;
    }
    if(!FScanner->SelectScanner())
    {
        if(ScanInfo)    delete ScanInfo;
        return;
    }

    FillMemory(ScanInfo, sizeof(TScanInfo), 0);
    ScanInfo->MultiPage = false;

    this->Enabled = false;
    try
    {
        // to hide the user interface and set parameters
        //  FScanner->ShowUI = false;
        FScanner->RequestedXDpi = 100;
        FScanner->RequestedYDpi = 100;
        FScanner->RequestedImageFormat = ifTrueColor;
        FScanner->Acquire(OnAcquire,(long int)ScanInfo);
    }
    __finally
    {
        this->Enabled = true;
        if(ScanInfo->MultiPage)
        {
            if(ScanInfo->Graphic)   delete ScanInfo->Graphic;
            if(ScanInfo->Stream)    delete ScanInfo->Stream;
        }
    }
    if(ScanInfo)    delete ScanInfo;
}
//---------------------------------------------------------------------------

void __fastcall TFormImportImage::SpeedButton1Click(TObject *Sender)
{
    ModalResult=mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TFormImportImage::SpeedButton2Click(TObject *Sender)
{
    ModalResult=mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TFormImportImage::Panel2Resize(TObject *Sender)
{
    Panel3->Left=(Panel2->Width-Panel3->Width)/2;
    Panel3->Top=(Panel2->Height-Panel3->Height)/2;
}
//---------------------------------------------------------------------------

