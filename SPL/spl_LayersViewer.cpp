//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "spl_LayersViewer.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormLayersViewer *FormLayersViewer;
//---------------------------------------------------------------------------
__fastcall TFormLayersViewer::TFormLayersViewer(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormLayersViewer::CreateParams(TCreateParams& Params)
{
    TForm::CreateParams(Params);
    Params.Style=WS_CHILD | WS_CLIPSIBLINGS;
    Params.WndParent=FormMain->PanelLayersViewer->Handle;
    Params.X=0;
    Params.Y=0;
    Params.Width=300;
    Params.Height=400;
}
//---------------------------------------------------------------------------
void __fastcall TFormLayersViewer::ClearLayers()
{
    ListView->Items->Clear();
    ImageList->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormLayersViewer::AddLayer(AnsiString Name,spl_UInt Color)
{
    // Add Image Icon To ImageList
    pBMP->Canvas->Brush->Color=(TColor)Color;
    pBMP->Canvas->FillRect(Rect(0,0,ImageList->Width,ImageList->Height));
    ImageList->Add(pBMP,NULL);

    // Add Layer Item To the ListView
    TListItem *ListItem;
    ListItem=ListView->Items->Add();
    ListItem->Caption=Name;
    ListItem->ImageIndex=ListItem->Index;
}
//---------------------------------------------------------------------------

void __fastcall TFormLayersViewer::FormCreate(TObject *Sender)
{
    pBMP=new Graphics::TBitmap();
    pBMP->Width=ImageList->Width;
    pBMP->Height=ImageList->Height;
    pBMP->PixelFormat=pf24bit;
    pBMP->Canvas->Brush->Style=bsSolid;
}
//---------------------------------------------------------------------------

void __fastcall TFormLayersViewer::FormDestroy(TObject *Sender)
{
    if(pBMP)    delete pBMP;pBMP=NULL;
}
//---------------------------------------------------------------------------

