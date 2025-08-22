//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spl_RasterImage.h"
#include "GraphicEx.hpp"
#include "spl_Resize.h"
#include "spl_VectorImage.h"
#include "spl_EmbParams.h"
#include "About.h"
#include "spl_Monochrome.h"
#include "spl_DigitizeDialog.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormRasterImage *FormRasterImage;
//---------------------------------------------------------------------------
__fastcall TFormRasterImage::TFormRasterImage(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormRasterImage::UpdateStatusBar()
{
    MouseColor=Image->Canvas->Pixels[MousePosX][MousePosY];
    MouseRed=GetRValue(MouseColor);
    MouseGreen=GetGValue(MouseColor);
    MouseBlue=GetBValue(MouseColor);

    StatusBar->Panels->Items[0]->Text=FormatFloat("0000",MousePosX)+","+FormatFloat("0000",MousePosY);
    StatusBar->Panels->Items[1]->Text=FormatFloat("000",MouseRed)+","+FormatFloat("000",MouseGreen)+","+FormatFloat("000",MouseBlue);
    StatusBar->Panels->Items[2]->Text=FormatFloat("0000",pImage->Width)+"x"+FormatFloat("0000",pImage->Height)+"x"+FormatFloat("00",pImage->Bits);
    if((pImage->ppLines)&&(pImage->Bits<=8)&&(MousePosX<pImage->Width)&&(MousePosY<pImage->Height))
    {
        StatusBar->Panels->Items[3]->Text=FormatFloat("000",pImage->ppLines[MousePosY][MousePosX]);
    }
    else
    {
        StatusBar->Panels->Items[3]->Text=FormatFloat("000",0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormRasterImage::FormCreate(TObject *Sender)
{
    AppPath=ExtractFilePath(Application->ExeName);

    Left=0;
    Top=0;
    Width=Screen->Width;
    Height=Screen->Height;

    pImage=new spl_Image();
    pRestore=new spl_Image();
    pResult=new spl_Image();
    spl_pGlobalPixelsInfo=new spl_Image();

    Image->Width = 0;
    Image->Height = 0;

    ContourIndex=PrevContourIndex=spl_MaxWord;
    MousePosX=0;
    MousePosY=0;
    UpdateStatusBar();
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::FormDestroy(TObject *Sender)
{
    if(pImage)                  delete pImage;
    if(pRestore)                delete pRestore;
    if(pResult)                 delete pResult;
    if(spl_pGlobalPixelsInfo)   delete spl_pGlobalPixelsInfo;
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::ImageMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(Button==mbLeft)
    {
    }
    else
    {
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::ImageMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    MousePosX=X;
    MousePosY=Y;
    UpdateStatusBar();
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::ImageMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    POINT Pos;
    Byte Pv=1;
    GetCursorPos(&Pos);
    switch(Key)
    {
        case VK_LEFT:
        {
            SetCursorPos(Pos.x-Pv,Pos.y);
            break;
        }
        case VK_RIGHT:
        {
            SetCursorPos(Pos.x+Pv,Pos.y);
            break;
        }
        case VK_UP:
        {
            SetCursorPos(Pos.x,Pos.y-Pv);
            break;
        }
        case VK_DOWN:
        {
            SetCursorPos(Pos.x,Pos.y+Pv);
            break;
        }
        case 100://LEFT
        {
            SetCursorPos(Pos.x-Pv,Pos.y);
            break;
        }
        case 102://RIGHT
        {
            SetCursorPos(Pos.x+Pv,Pos.y);
            break;
        }
        case 104://UP
        {
            SetCursorPos(Pos.x,Pos.y-Pv);
            break;
        }
        case 98://DOWN
        {
            SetCursorPos(Pos.x,Pos.y+Pv);
            break;
        }
        case 103://LEFT_UP
        {
            SetCursorPos(Pos.x-Pv,Pos.y-Pv);
            break;
        }
        case 105://RIGHT_UP
        {
            SetCursorPos(Pos.x+Pv,Pos.y-Pv);
            break;
        }
        case 97://Left_DOWN
        {
            SetCursorPos(Pos.x-Pv,Pos.y+Pv);
            break;
        }
        case 99://RIGHT_DOWN
        {
            SetCursorPos(Pos.x+Pv,Pos.y+Pv);
            break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AFileExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::NewImage()
{
    MousePosX=0;
    MousePosY=0;
    MouseRed=MouseGreen=MouseBlue=255;
    PrevContourIndex=ContourIndex=spl_MaxWord;
    spl_GlobalCurves.erase(spl_GlobalCurves.begin(),spl_GlobalCurves.end());
    spl_pGlobalPixelsInfo->Clear();
    Image->Cursor=crArrow;
    UpdateStatusBar();
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::UpdateImage()
{
        if(pImage->pBitmap->Empty)  return;
        double XRes;
        double YRes;
        double Wdisiem;
        double Hdisiem;

        spl_GetBitmapResulotion_PPDisiem(pImage->pBitmap->Handle,XRes,YRes);
        Wdisiem=pImage->Width/XRes;
        Hdisiem=pImage->Height/YRes;

        FormEmbParams->ImageWidth=pImage->Width;
        FormEmbParams->ImageHeight=pImage->Height;
        FormEmbParams->DesignWidth=Wdisiem/100.0;
        FormEmbParams->DesignHeight=Hdisiem/100.0;
        FormEmbParams->Ratio=FormEmbParams->DesignWidth/FormEmbParams->DesignHeight;

        FormResize->ImageWidth=pImage->Width;
        FormResize->ImageHeight=pImage->Height;
        FormResize->Ratio=FormResize->ImageWidth/FormResize->ImageHeight;
        FormResize->NewWidth=pImage->Width;
        FormResize->NewHeight=pImage->Height;

        Image->Left = 0;
        Image->Top = 0;
        Image->Picture->Assign(pImage->pBitmap);
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AOpenImageExecute(TObject *Sender)
{
    if(OpenPictureDialog1->Execute())
    {
        FileName=OpenPictureDialog1->FileName;
        Caption=spl_EmbTraceCaption+"["+FileName+"]";
        FormMain->AddMessage("Opening ["+FileName+"]...");
        pImage->LoadFromFile(FileName);
    	pImage->SetPixelFormat(pf24bit);
        pRestore->Assign(pImage);
        UpdateImage();
        NewImage();

        FormMain->AVectorImage->Enabled = true;
        FormMain->ARasterImage->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AImportImageExecute(TObject *Sender)
{
    if(FormImportImage->ShowModal()==mrOk)
    {
        FileName="Scanner";
        Caption=spl_EmbTraceCaption+"["+FileName+"]";
        FormMain->AddMessage("Scaning ...");
        pImage->Assign(FormImportImage->ImageScrollBox->Graphic);
        pRestore->Assign(pImage);
        UpdateImage();
        NewImage();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::ASaveImageExecute(TObject *Sender)
{
    if(SavePictureDialog1->Execute())
    {
        pImage->SaveToFile(SavePictureDialog1->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AImagingExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AResizeExecute(TObject *Sender)
{
    if(pImage->pBitmap->Empty)    return;
    FormResize->ImageWidth=pImage->Width;
    FormResize->ImageHeight=pImage->Height;
    FormResize->Ratio=FormResize->ImageWidth/FormResize->ImageHeight;
    FormResize->NewWidth=pImage->Width;
    FormResize->NewHeight=pImage->Height;
    if(FormResize->ShowModal()!=mrOk)   return;
    int NewWidth;
    int NewHeight;
    TResamplingFilter Filter;
    double Radius;

    NewWidth=FormResize->NewWidth;
    NewHeight=FormResize->NewHeight;
    Filter=(TResamplingFilter)FormResize->ComboBox1->ItemIndex;
    Radius=0;

    StartTime=GetTickCount();

    Stretch(NewWidth,NewHeight,Filter,Radius,pImage->pBitmap);

    Delay=(GetTickCount()-StartTime)/1000.0;
    Caption=spl_EmbTraceCaption+"["+FileName+"] <"+FormatFloat("0.000 s>",Delay);
    FormMain->AddMessage("Resizing ["+FileName+"]...<"+FormatFloat("0.000 s>",Delay));

    pImage->UpdateLines();
    UpdateImage();
    NewImage();
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::ARestoreImageExecute(TObject *Sender)
{
    if(pRestore->pBitmap->Empty)    return;
    pImage->Assign(pRestore);
    UpdateImage();
    NewImage();
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AInvertExecute(TObject *Sender)
{
    StartTime=GetTickCount();

    spl_InvertImage(pImage);

    Delay=(GetTickCount()-StartTime)/1000.0;
    Caption=spl_EmbTraceCaption+"["+FileName+"] <"+FormatFloat("0.000 s>",Delay);
    FormMain->AddMessage("Inverting ["+FileName+"]...<"+FormatFloat("0.000 s>",Delay));

    pImage->UpdateLines();

    UpdateImage();
    NewImage();
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::ASmoothExecute(TObject *Sender)
{
    AnsiString strFilterDim="3";
    if(!InputQuery("Thmooth","Enter Filter Dim:",strFilterDim)) return;
    int FilterDim=StrToInt(strFilterDim);
    Application->ProcessMessages();

    StartTime=GetTickCount();

    spl_SmoothImageColors(pImage,FilterDim,pResult);    
    pImage->Assign(pResult->pBitmap);

    Delay=(GetTickCount()-StartTime)/1000.0;
    Caption=spl_EmbTraceCaption+"["+FileName+"] <"+FormatFloat("0.000 s>",Delay);
    FormMain->AddMessage("Smoothing ["+FileName+"]...<"+FormatFloat("0.000 s>",Delay));

    UpdateImage();
    NewImage();
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AReverseExecute(TObject *Sender)
{
    StartTime=GetTickCount();

    spl_ReverseImage(pImage,pResult);    
    pImage->Assign(pResult->pBitmap);

    Delay=(GetTickCount()-StartTime)/1000.0;
    Caption=spl_EmbTraceCaption+"["+FileName+"] <"+FormatFloat("0.000 s>",Delay);
    FormMain->AddMessage("Reversing ["+FileName+"]...<"+FormatFloat("0.000 s>",Delay));

    UpdateImage();
    NewImage();
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AQuantizeExecute(TObject *Sender)
{
    AnsiString strColorsCount="8";
    if(!InputQuery("Color Quantizer","Enter Color Count:",strColorsCount)) return;
    int ColorsCount=StrToInt(strColorsCount);
    Application->ProcessMessages();

    StartTime=GetTickCount();

    spl_QuantizeImageColors(pImage,ColorsCount,false,false);

    Delay=(GetTickCount()-StartTime)/1000.0;
    Caption=spl_EmbTraceCaption+"["+FileName+"] <"+FormatFloat("0.000 s>",Delay);
    FormMain->AddMessage("Quantizing ["+FileName+"]...<"+FormatFloat("0.000 s>",Delay));

    UpdateImage();
    NewImage();
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::ADigitizerExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::ADigitizeExecute(TObject *Sender)
{
    if(FormDigitize->ShowModal()!=mrOk) return;

    int ColorsCount=FormDigitize->CSpinEdit1->Value;
    int FilterDim=FormDigitize->CSpinEdit2->Value;
    int RepeatCount=FormDigitize->CSpinEdit3->Value;
    Application->ProcessMessages();

//    pRestore->Assign(pImage);

    StartTime=GetTickCount();

    // PreProcess
    FormMain->AddMessage("Auto Frame ...");
    pImage->AutoFrame(5,true);
    Application->ProcessMessages();

    FormMain->AddMessage("Quantizing image colors ...");
    spl_QuantizeImageColors(pImage,ColorsCount,true,true);
    Application->ProcessMessages();
    FormMain->AddMessage("Smoothing quantized image ...");
    for(int i=0;i<RepeatCount;i++)
    {
	    spl_SmoothDigitizedImageColors(pImage,FilterDim);
	    Application->ProcessMessages();
    }

    // Auto Frame For Better Continuity
    spl_UInt Border=10;
    pImage->AutoFrame(Border,true);
    spl_FrameImage(pImage,spl_BackgroundIndex,Border);
    spl_DigitizerBorder=Border;
    Application->ProcessMessages();
    
    FormMain->AddMessage("Digitizing ["+FileName+"]...");
    spl_ReverseImage(pImage,pResult);
    spl_ExtractDigitizedContoursForProcessing(pResult);
    Application->ProcessMessages();

    Delay=(GetTickCount()-StartTime)/1000.0;
    Caption=spl_EmbTraceCaption+"["+FileName+"] <"+FormatFloat("0.000 s>",Delay);
    FormMain->AddMessage("Digitizing period <"+FormatFloat("0.000 s>",Delay));

    UpdateImage();

    FormVectorImage->pImage->Assign(pImage);
    FormVectorImage->Image->Picture->Assign(pImage->pBitmap);
    FormVectorImage->Image->Picture->Bitmap->PixelFormat = pf24bit;
    FormVectorImage->Image->Cursor=crHandPoint;
    FormVectorImage->Image->Left = 0;
    FormVectorImage->Image->Top = 0;
    FormVectorImage->Caption="Vector Image ["+FileName+"] <"+FormatFloat("0 Curves>",spl_GlobalCurves.size());
    FormMain->AddMessage("Vector file ["+FileName+"]... contains <"+FormatFloat("0 Curves>",spl_GlobalCurves.size()));
	FormMain->ShowForm(FormVectorImage);
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AGrayExecute(TObject *Sender)
{
    StartTime=GetTickCount();

    spl_ConvertToGray(pImage,0,pResult);
    pImage->Assign(pResult->pBitmap);

    Delay=(GetTickCount()-StartTime)/1000.0;
    Caption=spl_EmbTraceCaption+"["+FileName+"] <"+FormatFloat("0.000 s>",Delay);
    FormMain->AddMessage("Converting to gray ["+FileName+"]...<"+FormatFloat("0.000 s>",Delay));

    UpdateImage();
    NewImage();
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AHelpExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AContentsExecute(TObject *Sender)
{
    Application->HelpFile=AppPath+"EMBTRACE.HLP";
    Application->HelpCommand(HELP_CONTENTS,0);    
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AAboutExecute(TObject *Sender)
{
    FormAbout->ShowModal();    
}
//---------------------------------------------------------------------------

void __fastcall TFormRasterImage::AMonochromeExecute(TObject *Sender)
{
    if(pImage->pBitmap->Empty)    return;
    spl_ConvertToGray(pImage,0,pResult);
    pImage->Assign(pResult->pBitmap);
    FormMonochrom->Image=Image;
    FormMonochrom->pImage=pImage;
    FormMonochrom->pResult=pResult;
    FormMonochrom->ShowModal();
    pImage->Assign(pResult->pBitmap);

    UpdateImage();
    NewImage();
}
//---------------------------------------------------------------------------

