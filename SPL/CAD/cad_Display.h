//---------------------------------------------------------------------------

#ifndef cad_DisplayH
#define cad_DisplayH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include <vector.h>
#include "spl_EmbFile.h"
#include "FormTranslation.h"
//---------------------------------------------------------------------------
const int MaxVertexCount=20000;
//---------------------------------------------------------------------------
typedef vector<spl_UInt> cad_Entities;
//---------------------------------------------------------------------------
typedef vector<cad_Entities> cad_Layers;
//---------------------------------------------------------------------------
class TFormDisplay : public TForm
{
__published:	// IDE-managed Components
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
private:	// User declarations
    void __fastcall CreateParams(TCreateParams& Params);
public:		// User declarations
    __fastcall TFormDisplay(TComponent* Owner);
    HWND ghwVec;   // VeCAD window to display draw
    int  SBarH;    // height of status bar
    spl_StitchPath StitchPath;
    spl_Stitch Stitch;
    spl_EmbHeader EmbHeader;
    AnsiString m_strFileName;
    bool TheEnd;

    void __fastcall FileNew();
    void __fastcall FileOpen(bool bShowJumps);
    void __fastcall FileSave();
    void __fastcall OpenEmbFile(AnsiString FileName,bool bShowJumps);
    void __fastcall SaveEmbFile(AnsiString FileName);
    void __fastcall DrawContour(spl_Contour &Contour,spl_UInt Color);
    void __fastcall ExtractLayers(cad_Layers &Layers);
    void __fastcall ExtractPolylines(spl_Region &Region,bool JustSelected);
	void __fastcall DrawMultiLayer(spl_MultiLayer &MultiLayer);
	void __fastcall FileImport(AnsiString strFileName);
	void __fastcall DrawLayer(spl_Layer &Layer);
	void __fastcall ImportEMF(AnsiString strFileName);
	void __fastcall DrawGlobalStitchPath(spl_GlobalStitchPath GlobalStitchPath,bool bShowJumps);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDisplay *FormDisplay;
//---------------------------------------------------------------------------
void spl_DrawPolyline(int nSmoothType,bool bIsClosed,LPPOINT pt,int nTotal);
//---------------------------------------------------------------------------
#endif
