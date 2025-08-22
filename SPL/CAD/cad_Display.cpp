//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "cad_Display.h"
#include "Main.h"
#include "api_VecApi.h"
#include "cad_Messages.h"
#include "spl_Progress.h"
#include "spl_Digitizer.h"
#include "cad_EMF_Parser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormDisplay *FormDisplay;
//---------------------------------------------------------------------------
const int ALISOFT_REG_CODE_5_2 = 330001309;
//---------------------------------------------------------------------------
__fastcall TFormDisplay::TFormDisplay(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::CreateParams(TCreateParams& Params)
{
    TForm::CreateParams(Params);
    Params.Style=WS_CHILD | WS_CLIPSIBLINGS;
    Params.WndParent=FormMain->Handle;
    Params.X=0;
    Params.Y=0;
    Params.Width=300;
    Params.Height=400;
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::FormCreate(TObject *Sender)
{
    TheEnd=false;

    // Register your copy of Vecad.dll
    vlRegistration(ALISOFT_REG_CODE_5_2);
    
    // Set message handler function
    vlSetMsgHandler(DwgProc);

    // Create VeCAD StatusBar
    vlStatBarCreate( Handle, &SBarH );

    // Create VeCAD window, size will be set in OnSize()
    ghwVec = vlWndCreate( Handle, VL_WS_CHILD|VL_WS_SCROLL|VL_WS_BORDER, 0,0,400,300 );
    if(ghwVec)
    {
        ::PostMessage( Handle, WM_SIZE, 0, 0 );
        vlPropPut( VD_WND_EMPTYTEXT, (int)ghwVec,spl_EmbEditorCaption.c_str());
    }

//    vlFileList(Handle);

    m_strFileName="Untitled";
    FormMain->Caption=spl_EmbEditorCaption;

//    m_pEmbPlugin = new TEmbPlugin();
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::FormDestroy(TObject *Sender)
{
//	if(m_pEmbPlugin)
//    {
//     	delete m_pEmbPlugin;
//        m_pEmbPlugin = NULL;
//    }
    
//AliSoft Bug fix: You don`t need to use vlCleanup() to free memory
//                 because "Borland C++ Builder" free it for you. 
//    vlCleanup();
    vlExecute(VC_FILE_CLOSEALL);    
    TheEnd=true;
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::FormResize(TObject *Sender)
{
    if(TheEnd) return;

    int w, h;
    vlGetWinSize( Handle, &w, &h );
    if(w>0 && h>0)
    {
        // Resize drawing window
        vlWndResize( ghwVec, 0, 0, w, h - SBarH );
        
        // Resize statusbar
        vlStatBarResize();

        // Update View
        vlZoom(VL_ZOOM_ALL);
        vlUpdate();
        vlExecute(VC_ZOOM_ALL);
        vlUpdate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::FileNew()
{
    if(TheEnd) return;

    vlFileNew(ghwVec,"");

    // Background Color
    vlPropPutInt(VD_DWG_COLPAGE,-1,0x00C0DCC0);

    // Grid Color
    vlPropPutInt(VD_GRID_COLOR,-1,clNavy);
    vlPropPutInt(VD_GRID_BCOLOR,-1,clNavy);

    #ifdef spl_EMB_EDITOR
    FormMain->UpdateLayers();
    #endif// spl_EMB_EDITOR
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::FileOpen(bool bShowJumps)
{
    if(TheEnd) return;

    OpenEmbFile(m_strFileName,bShowJumps);

    // Background Color
    vlPropPutInt(VD_DWG_COLPAGE,-1,0x00C0DCC0);

    // Grid Color
    vlPropPutInt(VD_GRID_COLOR,-1,clNavy);
    vlPropPutInt(VD_GRID_BCOLOR,-1,clNavy);

    // Show All
    vlZoom(VL_ZOOM_ALL);
    vlUpdate();
    vlExecute(VC_ZOOM_ALL);
    vlUpdate();

    #ifdef spl_EMB_EDITOR
    FormMain->UpdateLayers();
    #endif// spl_EMB_EDITOR
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::FileSave()
{
    if(TheEnd) return;

    SaveEmbFile(m_strFileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::DrawContour(spl_Contour &Contour,spl_UInt Color)
{
    if(TheEnd) return;

    spl_Point p;
    int VertexCount=0;
    vlPolylineBegin();
    for(spl_UInt i=0;i<Contour.Points.size();i++)
    {
        if(VertexCount>=MaxVertexCount)
        {
            vlAddPolyline(VL_POLY_LINE,false);

            VertexCount=0;
            vlPolylineBegin();
        }
        p=Contour.Points[i];
        vlVertex(p.x,p.y);
        VertexCount++;
    }
    vlAddPolyline(VL_POLY_LINE,false);
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::OpenEmbFile(AnsiString FileName,bool bShowJumps)
{
    if(TheEnd) return;

    int Index=vlFileNew(ghwVec,"");
    vlPropPut(VD_DWG_FILENAME,Index,FileName.c_str());

    FormProgress->Show();
    spl_LoadEmbFromFile(FileName,StitchPath,&EmbHeader,FormProgress->ProgressBar1);
    FormProgress->Hide();

    spl_GlobalStitchPath GlobalStitchPath;
    spl_GlobalStitch GlobalStitch;
    spl_ConvertStitchPathToGlobalStitchPath(StitchPath,GlobalStitchPath);

    spl_Contour Contour;
    spl_Point p;
    spl_RGB rgbColor;
    spl_UInt LayerColor;
    AnsiString LayerName;
    spl_UInt ColorIndex;
    spl_UInt LayerIndex;

    Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
    ColorIndex=0;
    rgbColor=EmbHeader.Colors[ColorIndex];
    LayerColor=RGB(rgbColor.r,rgbColor.g,rgbColor.b);
    LayerName=FormatFloat("Layer 000",ColorIndex);
    LayerIndex=0;
    vlPropPut(VD_LAYER_NAME,LayerIndex,LayerName.c_str());
    vlPropPutInt(VD_LAYER_COLOR,LayerIndex,LayerColor);
    vlPropPutInt(VD_LAYER_FILLCOLOR,LayerIndex,LayerColor);
    ColorIndex++;
    for(spl_UInt i=0;i<GlobalStitchPath.size();i++)
    {
        GlobalStitch=GlobalStitchPath[i];
        switch(GlobalStitch.type)
        {
            case spl_stNormal:
            {
                p.x=GlobalStitch.x;
                p.y=GlobalStitch.y;
                Contour.Points.push_back(p);
                break;
            }
            case spl_stJump:
            {
            	if(bShowJumps)
                {
	                p.x=GlobalStitch.x;
    	            p.y=GlobalStitch.y;
        	        Contour.Points.push_back(p);
                }
                else
                {
	                DrawContour(Contour,LayerColor);
    	            Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
                }
                break;
            }
            case spl_stColorChanged:
            {
                DrawContour(Contour,LayerColor);
                Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());

                if(ColorIndex<EmbHeader.ColorStitchs)
                    rgbColor=EmbHeader.Colors[ColorIndex];
                else
                {
                    rgbColor.r=random(255);
                    rgbColor.g=random(255);
                    rgbColor.b=random(255);
                }
                LayerColor=RGB(rgbColor.r,rgbColor.g,rgbColor.b);
                LayerName=FormatFloat("Layer 000",ColorIndex);
                LayerIndex=vlLayerAdd(LayerName.c_str(),0.25,LayerColor,LayerColor);
                ColorIndex++;
                break;
            }
        }
    }
    if(!Contour.Points.empty())
    {
        DrawContour(Contour,LayerColor);
        Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::DrawGlobalStitchPath(spl_GlobalStitchPath GlobalStitchPath,bool bShowJumps)
{
    if(TheEnd) return;

    spl_Contour Contour;
    spl_Point p;
    spl_RGB rgbColor;
    spl_UInt LayerColor;
    AnsiString LayerName;
    spl_UInt ColorIndex;
    spl_UInt LayerIndex;
    spl_GlobalStitch GlobalStitch;

    Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
    ColorIndex=0;
    rgbColor=EmbHeader.Colors[ColorIndex];
    LayerColor=RGB(rgbColor.r,rgbColor.g,rgbColor.b);
    LayerName=FormatFloat("Layer 000",ColorIndex);
    LayerIndex=0;
    vlPropPut(VD_LAYER_NAME,LayerIndex,LayerName.c_str());
    vlPropPutInt(VD_LAYER_COLOR,LayerIndex,LayerColor);
    vlPropPutInt(VD_LAYER_FILLCOLOR,LayerIndex,LayerColor);
    ColorIndex++;
    for(spl_UInt i=0;i<GlobalStitchPath.size();i++)
    {
        GlobalStitch=GlobalStitchPath[i];
        switch(GlobalStitch.type)
        {
            case spl_stNormal:
            {
                p.x=GlobalStitch.x;
                p.y=GlobalStitch.y;
                Contour.Points.push_back(p);
                break;
            }
            case spl_stJump:
            {
            	if(bShowJumps)
                {
	                p.x=GlobalStitch.x;
    	            p.y=GlobalStitch.y;
        	        Contour.Points.push_back(p);
                }
                else
                {
	                DrawContour(Contour,LayerColor);
    	            Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
                }
                break;
            }
            case spl_stColorChanged:
            {
                DrawContour(Contour,LayerColor);
                Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());

                if(ColorIndex<EmbHeader.ColorStitchs)
                    rgbColor=EmbHeader.Colors[ColorIndex];
                else
                {
                    rgbColor.r=random(255);
                    rgbColor.g=random(255);
                    rgbColor.b=random(255);
                }
                LayerColor=RGB(rgbColor.r,rgbColor.g,rgbColor.b);
                LayerName=FormatFloat("Layer 000",ColorIndex);
                LayerIndex=vlLayerAdd(LayerName.c_str(),0.25,LayerColor,LayerColor);
                ColorIndex++;
                break;
            }
        }
    }
    if(!Contour.Points.empty())
    {
        DrawContour(Contour,LayerColor);
        Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::ExtractLayers(cad_Layers &Layers)
{
    if(TheEnd) return;

    Layers.erase(Layers.begin(),Layers.end());

    spl_SInt LayersCount;
    spl_SInt EntitiesCount;
    spl_SInt DocIndex;
    spl_SInt LayerIndex;
    bool EntityVisible;
    bool EntityDeleted;
    spl_SInt LayerEntitiesCount;
    bool LayerVisible;
    bool LayerPrint;

    LayersCount=vlLayerCount();
    Layers.resize(LayersCount);

    DocIndex=vlDocGetActive();
    EntitiesCount=vlPropGetInt(VD_DWG_N_ENT,DocIndex);
    for(spl_SInt EntityIndex=0;EntityIndex<EntitiesCount;EntityIndex++)
    {
        LayerIndex=vlPropGetInt(VD_ENT_LAYER,EntityIndex);
        LayerVisible=vlPropGetInt(VD_LAYER_VISIBLE,LayerIndex);
        LayerPrint=!vlPropGetInt(VD_LAYER_NOPRINT,LayerIndex);
        LayerEntitiesCount=vlPropGetInt(VD_LAYER_N_REF,LayerIndex);
        if((LayerEntitiesCount>0) && LayerVisible && LayerPrint)
        {
            EntityVisible=vlPropGetInt(VD_ENT_ONSCREEN,EntityIndex);
            EntityDeleted=vlPropGetInt(VD_ENT_DELETED,EntityIndex);
            if(EntityVisible && (!EntityDeleted))
                Layers[LayerIndex].push_back(EntityIndex);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::SaveEmbFile(AnsiString FileName)
{
    if(TheEnd) return;

    spl_GlobalStitchPath GlobalStitchPath;
    spl_GlobalStitch GlobalStitch;
    spl_StitchPath StitchPath;
    spl_Stitch Stitch;
    spl_EmbHeader EmbHeader;
    cad_Layers Layers;

    ExtractLayers(Layers);

    spl_UInt LayersCount;
    spl_UInt EntitiesCount;
    spl_UInt EntityType;
    AnsiString LayerName;
    spl_UInt PointsCount;
    spl_Point P;
    spl_UInt LayerColor;
    spl_UInt LayerIndex;
    double Param;
    spl_UInt EntityIndex;

    // Start Export
    GlobalStitchPath.erase(GlobalStitchPath.begin(),GlobalStitchPath.end());
    EmbHeader.ColorStitchs=0;
    EmbHeader.NormalStitchs=0;
    EmbHeader.JumpStitchs=0;
    strcpy(EmbHeader.Comments,spl_Comments);
    P=splPoint(0,0);

    LayersCount=Layers.size();
    for(spl_UInt LayerIndex=0;LayerIndex<LayersCount;LayerIndex++)
    {
        EntitiesCount=Layers[LayerIndex].size();
        if(EntitiesCount<=0)    continue;

        LayerColor=vlPropGetInt(VD_LAYER_COLOR,LayerIndex);
        EmbHeader.Colors[EmbHeader.ColorStitchs].r=GetRValue(LayerColor);
        EmbHeader.Colors[EmbHeader.ColorStitchs].g=GetGValue(LayerColor);
        EmbHeader.Colors[EmbHeader.ColorStitchs].b=GetBValue(LayerColor);
        EmbHeader.ColorStitchs++;

        for(spl_UInt k=0;k<EntitiesCount;k++)
        {
            EntityIndex=Layers[LayerIndex][k];
            EntityType=vlPropGetInt(VD_ENT_TYPE,EntityIndex);
            switch(EntityType)
            {
                case VL_ENT_POLYLINE:// Polyline
                {
                    PointsCount=vlPropGetInt(VD_POLY_N_VER,EntityIndex);

                    // Jump
                    vlPolyVerGet(EntityIndex,0,&P.x,&P.y,&Param);
                    GlobalStitch.x=P.x;
                    GlobalStitch.y=P.y;
                    GlobalStitch.type=spl_stJump;
                    GlobalStitchPath.push_back(GlobalStitch);
                    EmbHeader.JumpStitchs++;

                    for(spl_UInt PointIndex=0;PointIndex<PointsCount;PointIndex++)
                    {
                        vlPolyVerGet(EntityIndex,PointIndex,&P.x,&P.y,&Param);

                        GlobalStitch.x=P.x;
                        GlobalStitch.y=P.y;
                        GlobalStitch.type=spl_stNormal;
                        GlobalStitchPath.push_back(GlobalStitch);

                        EmbHeader.NormalStitchs++;
                    }
                    break;
                }
            }
        }

        // Change Color
        GlobalStitch.x=P.x;
        GlobalStitch.y=P.y;
        GlobalStitch.type=spl_stColorChanged;
        GlobalStitchPath.push_back(GlobalStitch);
    }

    // Replace Last Color Changed By Jump
    spl_UInt nCount=GlobalStitchPath.size();
    if(nCount > 0)
    {
	    GlobalStitchPath[nCount-1].type=spl_stJump;
    }
    else
    {
     	return;
    }

    // End Export
    EmbHeader.StitchsCount=EmbHeader.ColorStitchs+EmbHeader.NormalStitchs+EmbHeader.JumpStitchs;
    spl_ConvertGlobalStitchPathToStitchPath(GlobalStitchPath,StitchPath);
    FormProgress->Show();
    spl_SaveEmbToFile(FileName,StitchPath,&EmbHeader,FormProgress->ProgressBar1);
    FormProgress->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::ExtractPolylines(spl_Region &Region,bool JustSelected)
{
    if(TheEnd) return;

    cad_Layers Layers;
    ExtractLayers(Layers);

    spl_UInt LayersCount;
    spl_UInt EntitiesCount;
    spl_UInt EntityType;
    spl_UInt EntityIndex;
    bool EntitySelected;
    spl_UInt PointsCount;
    spl_UInt LayerIndex;
    double Param;
    spl_Point P;
    bool Closed;

    LayersCount=Layers.size();
    for(spl_UInt LayerIndex=0;LayerIndex<LayersCount;LayerIndex++)
    {
        EntitiesCount=Layers[LayerIndex].size();
        if(EntitiesCount<=0)    continue;
        for(spl_UInt k=0;k<EntitiesCount;k++)
        {
            EntityIndex=Layers[LayerIndex][k];
            EntityType=vlPropGetInt(VD_ENT_TYPE,EntityIndex);
            if(JustSelected)
            {
                EntitySelected=vlPropGetInt(VD_ENT_SELECT,EntityIndex);
                if(!EntitySelected) continue;
            }
            switch(EntityType)
            {
                case VL_ENT_POLYLINE:// Polyline
                {
                    spl_Contour Contour;
                    PointsCount=vlPropGetInt(VD_POLY_N_VER,EntityIndex);
                    Closed=vlPropGetInt(VD_POLY_CLOSED,EntityIndex);
                    for(spl_UInt PointIndex=0;PointIndex<PointsCount;PointIndex++)
                    {
                        vlPolyVerGet(EntityIndex,PointIndex,&P.x,&P.y,&Param);
                        Contour.Points.push_back(splPoint(P.x,P.y));
                    }
                    if(Closed)
                    {
                        vlPolyVerGet(EntityIndex,0,&P.x,&P.y,&Param);
                        Contour.Points.push_back(splPoint(P.x,P.y));
                    }
                    if(!Contour.Points.empty())
                    {
                        Region.Contours.push_back(Contour);
                    }
                    break;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void spl_DrawPolyline(int nSmoothType,bool bIsClosed,LPPOINT pt,int nTotal)
{
    int VertexCount=0;
    vlPolylineBegin();
 	for(int i=0;i<nTotal;i++)
 	{
        if(VertexCount>=MaxVertexCount)
        {
            vlAddPolyline(nSmoothType,bIsClosed);

            VertexCount=0;
            vlPolylineBegin();
        }
        vlVertex(pt[i].x,pt[i].y);
        VertexCount++;
 	}
    vlAddPolyline(nSmoothType,bIsClosed);
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::DrawMultiLayer(spl_MultiLayer &MultiLayer)
{
    if(TheEnd) return;

    spl_UInt LayerColor;
    AnsiString LayerName;
    int LayerIndex;
    spl_Point p;
    spl_Contour Contour;
    int ObjIndex;

    spl_UInt nLayerIndex = 0;
//    int nLayerIndex = MultiLayer.Layers.size();
/*
    LayerName=FormatFloat("Layer 000",nLayerIndex);
    vlPropPut(VD_LAYER_NAME,nLayerIndex,LayerName.c_str());
    vlPropPutInt(VD_LAYER_COLOR,nLayerIndex,LayerColor);
    vlPropPutInt(VD_LAYER_FILLCOLOR,nLayerIndex,LayerColor);
*/
	for(;nLayerIndex<MultiLayer.Layers.size();nLayerIndex++)
//	for(;nLayerIndex>=0;nLayerIndex--)
    {
    	if(MultiLayer.Layers[nLayerIndex].Regions.size() <= 0)	continue;
    	if(nLayerIndex != 0)
        {
	    	LayerColor = MultiLayer.Layers[nLayerIndex].Regions[0].FillColor;
	        LayerName = FormatFloat("Layer 000",nLayerIndex);
    	    LayerIndex = vlLayerAdd(LayerName.c_str(),0.25,LayerColor,LayerColor);
		    vlPropPutInt(VD_LAYER_COLOR,LayerIndex,LayerColor);
		    vlPropPutInt(VD_LAYER_FILLCOLOR,LayerIndex,LayerColor);
		}

        for(spl_UInt nRegionIndex=0;nRegionIndex<MultiLayer.Layers[nLayerIndex].Regions.size();nRegionIndex++)
        {
			for(spl_UInt nContourIndex=0;nContourIndex<MultiLayer.Layers[nLayerIndex].Regions[nRegionIndex].Contours.size();nContourIndex++)
            {
            	Contour = MultiLayer.Layers[nLayerIndex].Regions[nRegionIndex].Contours[nContourIndex];
			    vlPolylineBegin();
			    for(spl_UInt i=0;i<Contour.Points.size();i++)
			    {
			        p=Contour.Points[i];
			        vlVertex(p.x,p.y);
			    }
			    ObjIndex = vlAddPolyline(VL_POLY_BEZIER,true);
    			vlPropPutInt(VD_ENT_FILLED,ObjIndex,true);
            }
        }
    }

    // Background Color
    vlPropPutInt(VD_DWG_COLPAGE,-1,0x00C0DCC0);

    // Grid Color
    vlPropPutInt(VD_GRID_COLOR,-1,clNavy);
    vlPropPutInt(VD_GRID_BCOLOR,-1,clNavy);

    // Show All
    vlZoom(VL_ZOOM_ALL);
    vlUpdate();
    vlExecute(VC_ZOOM_ALL);
    vlUpdate();

    #ifdef spl_EMB_EDITOR
    FormMain->UpdateLayers();
    #endif// spl_EMB_EDITOR
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::DrawLayer(spl_Layer &Layer)
{
    if(TheEnd) return;

    spl_UInt ObjColor;
    AnsiString LayerName;
    int LayerIndex;
    spl_Point p;
    spl_Contour Contour;
    int ObjIndex;

    spl_UInt nLayerIndex = 0;
    LayerName=FormatFloat("Layer 000",nLayerIndex);
    vlPropPut(VD_LAYER_NAME,nLayerIndex,LayerName.c_str());

    for(spl_UInt nRegionIndex=0;nRegionIndex<Layer.Regions.size();nRegionIndex++)
    {
    	ObjColor = Layer.Regions[nRegionIndex].FillColor;
		for(spl_UInt nContourIndex=0;nContourIndex<Layer.Regions[nRegionIndex].Contours.size();nContourIndex++)
        {
        	Contour = Layer.Regions[nRegionIndex].Contours[nContourIndex];
		    vlPolylineBegin();
		    for(spl_UInt i=0;i<Contour.Points.size();i++)
		    {
		        p=Contour.Points[i];
		        vlVertex(p.x,p.y);
		    }
		    ObjIndex = vlAddPolyline(VL_POLY_BEZIER,true);
    		vlPropPutInt(VD_ENT_FILLED,ObjIndex,true);
    		vlPropPutInt(VD_ENT_COLOR,ObjIndex,ObjColor);
    		vlPropPutInt(VD_ENT_FILLCOLOR,ObjIndex,ObjColor);
        }
    }

    // Background Color
    vlPropPutInt(VD_DWG_COLPAGE,-1,0x00C0DCC0);

    // Grid Color
    vlPropPutInt(VD_GRID_COLOR,-1,clNavy);
    vlPropPutInt(VD_GRID_BCOLOR,-1,clNavy);

    // Show All
    vlZoom(VL_ZOOM_ALL);
    vlUpdate();
    vlExecute(VC_ZOOM_ALL);
    vlUpdate();

    #ifdef spl_EMB_EDITOR
    FormMain->UpdateLayers();
    #endif// spl_EMB_EDITOR
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::FileImport(AnsiString strFileName)
{
	int Index=vlFileNew(ghwVec,"");
    vlPropPut(VD_DWG_FILENAME,Index,strFileName.c_str());

//    spl_MultiLayer MultiLayer;
//    spl_LoadMultiLayer(strFileName.c_str(),MultiLayer);
//    DrawMultiLayer(MultiLayer);

	spl_Layer Layer;
	spl_LoadGlobalCurves(strFileName,Layer);
    DrawLayer(Layer);

    vlRedraw();
}
//---------------------------------------------------------------------------
void __fastcall TFormDisplay::ImportEMF(AnsiString strFileName)
{
	int Index=vlFileNew(ghwVec,"");
    vlPropPut(VD_DWG_FILENAME,Index,strFileName.c_str());

    FormEMF_Parser->RealMetafile->LoadFromFile(strFileName);
    FormEMF_Parser->RealMetafile->Enum();
    vlRedraw();
    vlExecute(VC_ZOOM_ALL);    
}
//---------------------------------------------------------------------------

