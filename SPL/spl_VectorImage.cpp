//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spl_VectorImage.h"
#include "spl_EmbParams.h"
#include "spl_ObjectParams.h"
#include "spl_ColorQuantizer.h"
#include "spl_Embroidery.h"
#include "Main.h"
#include "spl_PathFinder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormVectorImage *FormVectorImage;
//---------------------------------------------------------------------------
__fastcall TFormVectorImage::TFormVectorImage(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void DrawContour(spl_Contour &Contour,TColor Color)
{
	if(Contour.Points.size() <= 0)	return;
	spl_Point P;
    P = Contour.Points[0];
    FormVectorImage->Image->Canvas->Pen->Color = Color;
    FormVectorImage->Image->Canvas->MoveTo(P.x,P.y);
	for(spl_UInt i=0;i<Contour.Points.size();i++)
    {
     	P = Contour.Points[i];
		FormVectorImage->Image->Canvas->LineTo(P.x,P.y);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormVectorImage::UpdateStatusBar()
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
    if((spl_pGlobalPixelsInfo->ppLines)&&(MousePosX<spl_pGlobalPixelsInfo->Width)&&(MousePosY<spl_pGlobalPixelsInfo->Height))
    {
        ContourIndex=spl_GetPixelContour(MousePosX,pImage->Height-1-MousePosY);
        StatusBar->Panels->Items[4]->Text=FormatFloat("C000",ContourIndex);

        if(ContourIndex!=PrevContourIndex)
        {
            // Clear Old Contour
            if(PrevContourIndex!=spl_MaxWord)
            {
                Image->Canvas->Pen->Color=(TColor)spl_QuantizedColors[spl_GlobalCurves[PrevContourIndex].FillColorIndex];
                Contour=spl_GlobalCurves[PrevContourIndex].Contour;
                spl_ReverseCurve(pImage->Height,Contour);
                spl_DrawPolylineContour(Image->Canvas->Handle,Contour);
                PrevContourIndex=spl_MaxWord;
            }

            // Draw New Contour
            if(ContourIndex!=spl_MaxWord)
            {
                ContourColor=(TColor)spl_QuantizedColors[spl_GlobalCurves[ContourIndex].FillColorIndex];
                ContourColor=(TColor)RGB(255-GetRValue(ContourColor),255-GetGValue(ContourColor),255-GetBValue(ContourColor));
                Image->Canvas->Pen->Color=ContourColor;
                Contour=spl_GlobalCurves[ContourIndex].Contour;
                spl_ReverseCurve(pImage->Height,Contour);
                spl_DrawPolylineContour(Image->Canvas->Handle,Contour);
                PrevContourIndex=ContourIndex;
            }
            Image->Invalidate();
        }
        
        PrevContourIndex=ContourIndex;
    }
    else
    {
        StatusBar->Panels->Items[4]->Text=FormatFloat("C000",0);
    }
    StatusBar->Panels->Items[5]->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::ImageMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    MousePosX=X;
    MousePosY=Y;
/*
	if(Button == mbLeft)
    {
    	P1 = splPoint(X,Y);
    }
    else
    {
    	P2 = splPoint(X,Y);
		spl_FindPath(pImage,P1,P2,Contour);
        DrawContour(Contour,clBlue);
    }
*/
    if(Button==mbRight)
    {
        TPoint P=Image->ClientToScreen(Point(MousePosX,MousePosY));
        ContourIndex=spl_GetPixelContour(MousePosX,pImage->Height-1-MousePosY);
        PopupMenuObject->Popup(P.x,P.y);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::ImageMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    MousePosX=X;
    MousePosY=Y;
    UpdateStatusBar();
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::ImageMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    MousePosX=X;
    MousePosY=Y;
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::FormCreate(TObject *Sender)
{
    Left=0;
    Top=0;
    Width=Screen->Width;
    Height=Screen->Height;

    SaveDialogEMB->DefaultExt=spl_EmbDefaultExtension;
    SaveDialogEMB->Filter=spl_EmbFullFilter;

    pImage=new spl_Image();

    PrevContourIndex=spl_MaxWord;
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::AEmbroideryExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::AEmrboidExecute(TObject *Sender)
{
    if(pImage->pBitmap->Empty)  return;

    FormEmbParams->Edit1->Text=spl_Comments;
    FormEmbParams->ComboBox1->ItemIndex=spl_Global_EmbParameters.FillStitchingOutput;
    FormEmbParams->ComboBox4->ItemIndex=spl_Global_EmbParameters.LineStitchingOutput;
    FormEmbParams->CSpinEdit6->Value=spl_Global_EmbParameters.StitchMargin;
    FormEmbParams->ComboBox2->ItemIndex=spl_Global_EmbParameters.Dir;
    FormEmbParams->ComboBox3->ItemIndex=spl_Global_EmbParameters.StartDir;

    FormEmbParams->CSpinEdit1->Value=spl_MinStitchLength;
    FormEmbParams->CSpinEdit2->Value=spl_MinJumpLength;
    FormEmbParams->CSpinEdit3->Value=spl_Global_EmbParameters.FillStitchDensity;
    FormEmbParams->CSpinEdit8->Value=spl_Global_EmbParameters.LineStitchDensity;
    FormEmbParams->CSpinEdit4->Value=spl_Global_EmbParameters.RunStitchStep;
    FormEmbParams->CSpinEdit5->Value=spl_JumpStitchStep;

    FormEmbParams->ComboBox1->ItemIndex=spl_Global_EmbParameters.FillStitchingOutput;
    FormEmbParams->ComboBox4->ItemIndex=spl_Global_EmbParameters.LineStitchingOutput;
    FormEmbParams->CSpinEdit6->Value=spl_Global_EmbParameters.StitchMargin;
    FormEmbParams->CSpinEdit7->Value=spl_Global_EmbParameters.SatinHeight;

    FormEmbParams->ComboBox2->ItemIndex=spl_Global_EmbParameters.Dir;
    FormEmbParams->ComboBox3->ItemIndex=spl_Global_EmbParameters.StartDir;

    FormEmbParams->CheckBox1->Checked=spl_DesignCentered;

    FormEmbParams->CheckBox2->Checked=spl_ProcessFillColor;
    FormEmbParams->CheckBox3->Checked=spl_ProcessLineColor;

    FormEmbParams->CheckBox4->Checked=spl_ReturnToStartPoint;

    FormEmbParams->CheckBox5->Checked = spl_Global_EmbParameters.AdjustFillStitchs; 
    FormEmbParams->CheckBox6->Checked = spl_Global_EmbParameters.AdjustLineStitchs; 

    FormEmbParams->CheckBoxBestJump->Checked = spl_BestJump;
    FormEmbParams->CheckBoxReplaceJump->Checked = spl_ReplaceJump;
    FormEmbParams->ComboBoxAdjustMethode->ItemIndex = spl_AdjustMethode;

    if(FormEmbParams->ShowModal()!=mrOk)    return;
    Application->ProcessMessages();
    if(SaveDialogEMB->Execute())
    {
        AnsiString FileName=SaveDialogEMB->FileName;
        spl_StitchPath StitchPath;
        spl_EmbHeader EmbHeader;

/*
        int Degree=4;
        int Order=1;
        bool Smoothed=false;
        bool ByBezier=true;
        spl_ConvertGlobalContoursToMultiLayer(Smoothed,ByBezier,Order,Degree,MultiLayer);
*/
        spl_ConvertGlobalContoursToMultiLayerForEmbroidery(MultiLayer);
	    Application->ProcessMessages();
        spl_ReorderMultiLayerForEmbroidery(pImage,MultiLayer);
	    Application->ProcessMessages();
//        spl_RedefineCurve(MultiLayer);// New
        spl_FillStitchs_EMB(pImage,MultiLayer,StitchPath,EmbHeader);
	    Application->ProcessMessages();
        spl_SaveEmbToFile(FileName,StitchPath,&EmbHeader,ProgressBar);
	    Application->ProcessMessages();
        if(spl_bIsInvalidEmbroidery)
		{
			FormMain->AddMessage("Error: Invalid Embroidery ...["+FileName+"]");
        }
        else
		{
			FormMain->AddMessage("Success: Embroidery is ready ...["+FileName+"]");
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::AFileExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::ASaveExecute(TObject *Sender)
{
    if(SaveDialogML->Execute())
    {
        AnsiString OutputFileName=SaveDialogML->FileName;

//        int Degree=4;
        int Degree=1;
        int Order=1;
        bool Smoothed=true;
        bool ByBezier=false;
/*
        spl_ConvertGlobalContoursToMultiLayer(Smoothed,ByBezier,Order,Degree,MultiLayer);
        spl_SaveMultiLayer(OutputFileName.c_str(),MultiLayer);
*/

		spl_SaveGlobalCurves(Smoothed,ByBezier,Order,Degree,OutputFileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::AObjectExecute(TObject *Sender)
{
//    
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::APropertiesExecute(TObject *Sender)
{
	if(ContourIndex == spl_MaxWord)	return;
    spl_EmbParameters EmbParameters;
    EmbParameters=spl_GlobalCurves[ContourIndex].CurveInfo.EmbParameters;

    FormObjectParams->CSpinEdit3->Value=EmbParameters.FillStitchDensity;
    FormObjectParams->CSpinEdit1->Value=EmbParameters.LineStitchDensity;
    FormObjectParams->CSpinEdit4->Value=EmbParameters.RunStitchStep;

    FormObjectParams->ComboBox1->ItemIndex=EmbParameters.FillStitchingOutput;
    FormObjectParams->ComboBox6->ItemIndex=EmbParameters.LineStitchingOutput;
    FormObjectParams->CSpinEdit6->Value=EmbParameters.StitchMargin;
    FormObjectParams->CSpinEdit7->Value=EmbParameters.SatinHeight;

    FormObjectParams->ComboBox2->ItemIndex=EmbParameters.Dir;
    FormObjectParams->ComboBox3->ItemIndex=EmbParameters.StartDir;

    FormObjectParams->CheckBox1->Checked=spl_GlobalCurves[ContourIndex].ProcessFillColor;
    FormObjectParams->CheckBox2->Checked=spl_GlobalCurves[ContourIndex].ProcessLineColor;

    FormObjectParams->ComboBox4->Items->Clear();
    for(int i=0;i<spl_ColorsCount;i++)
    {
        FormObjectParams->ComboBox4->Items->Add(IntToStr(i));
    }
    FormObjectParams->ComboBox5->Items->Clear();
    for(int i=0;i<spl_ColorsCount;i++)
    {
        FormObjectParams->ComboBox5->Items->Add(IntToStr(i));
    }

    FormObjectParams->ComboBox4->ItemIndex=spl_GlobalCurves[ContourIndex].FillColorIndex;
    FormObjectParams->ComboBox5->ItemIndex=spl_GlobalCurves[ContourIndex].LineColorIndex;

    FormObjectParams->CheckBox3->Checked = EmbParameters.AdjustFillStitchs;
    FormObjectParams->CheckBox4->Checked = EmbParameters.AdjustLineStitchs;

    FormObjectParams->ObjectIndex=ContourIndex;
    FormObjectParams->Caption=FormatFloat("Object Parameters [0]",FormObjectParams->ObjectIndex);
    FormObjectParams->ShowModal();    
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::FormKeyDown(TObject *Sender, WORD &Key,
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

void __fastcall TFormVectorImage::FormDestroy(TObject *Sender)
{
    if(pImage)                  delete pImage;
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::AExportExecute(TObject *Sender)
{
    if(SavePictureDialogEMF->Execute())
    {
        AnsiString OutputFileName=SavePictureDialogEMF->FileName;
        HDC hDCMeta,NewMeta;

        hDCMeta=CreateEnhMetaFile(NULL,(LPSTR)OutputFileName.c_str(),NULL,"");

//        int Degree=4;
        int Degree=1;
        int Order=1;
        bool Smoothed=true;
        bool ByBezier=false;
        spl_ConvertGlobalContoursToMultiLayer(Smoothed,ByBezier,Order,Degree,MultiLayer);
        spl_ReverseCurve(pImage->Height,MultiLayer);
        spl_DrawMultiBezierLayer(hDCMeta,MultiLayer,true);

        NewMeta=CloseEnhMetaFile(hDCMeta);
        DeleteEnhMetaFile(NewMeta);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormVectorImage::AExportObjectExecute(TObject *Sender)
{
	if(ContourIndex == spl_MaxWord)	return;
	if(SaveDialogRGN->Execute())
    {
	    spl_Region Region;
//        int Degree=4;
        int Degree=1;
        int Order=1;
//        bool Smoothed=true;
        bool Smoothed=false;
        bool ByBezier=false;
    	spl_ConvertGlobalContourToRegion(ContourIndex,Smoothed,ByBezier,Order,Degree,Region);
        spl_ReverseCurve(pImage->Height,Region);
     	spl_SaveRegion(SaveDialogRGN->FileName.c_str(),Region);
    }	
}
//---------------------------------------------------------------------------

