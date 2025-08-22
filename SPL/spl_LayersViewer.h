//---------------------------------------------------------------------------

#ifndef spl_LayersViewerH
#define spl_LayersViewerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "spl_EmbFile.h"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TFormLayersViewer : public TForm
{
__published:	// IDE-managed Components
    TPanel *PanelBase;
    TImageList *ImageList;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
    void __fastcall CreateParams(TCreateParams& Params);
public:		// User declarations
    __fastcall TFormLayersViewer(TComponent* Owner);
    Graphics::TBitmap *pBMP;
    void __fastcall ClearLayers();
    void __fastcall AddLayer(AnsiString Name,spl_UInt Color);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLayersViewer *FormLayersViewer;
//---------------------------------------------------------------------------
#endif
