//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <math.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "cad_Messages.h"
#include "api_VecApi.h"
#include "cad_Strings.h"
#include "cad_Display.h"
#include "spl_Progress.h"
#include "Main.h"
#include "spl_Embroidery.h"
#include "spl_GlyphOutlines.h"
#include "spl_Calligrapher.h"
#include "spl_InsertText.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
AnsiString FileName;
spl_Point P;
spl_UInt Color;
double PenWidth;
int LayerIndex;
int LinesCount;
spl_GlobalStitchPath GlobalStitchPath;
spl_GlobalStitch GlobalStitch;
spl_StitchPath StitchPath;
spl_Stitch Stitch;
spl_EmbHeader EmbHeader;
bool IsFirstColor;
bool bClicked;
bool OnlyOne = false;
//---------------------------------------------------------------------------
int g_nEdgeCounts = 3;
AnsiString g_strText = "WWPTC";
TCommandType CommandType = ctNone;
//---------------------------------------------------------------------------
int spl_Cmd_Line(int Msg,int Step,double x,double y);
int spl_Cmd_PolySatin(int Msg,int Step,double x,double y);
int spl_Cmd_Text(int Msg,int Step,double x,double y);
int spl_Cmd_PolyShape(int Msg,int Step,double x,double y);
int spl_Cmd_ExtrudeShape(int Msg,int Step,double x,double y);
//---------------------------------------------------------------------------
void DrawPolyline(spl_Contour &Contour,spl_UInt Color);
void DrawSkeleton(spl_Contour &Contour,spl_Contour &Extrude,spl_UInt Color);
void AddPolyline(spl_Contour &Contour,spl_UInt Color);
//void GetPolylineCenter(spl_Contour &Contour,spl_Point &Center);
void spl_DrawText(int x,int y);
//---------------------------------------------------------------------------
int CALLBACK DwgProc (int iDwg,UINT Msg,int Prm1,int Prm2,double Prm3,double Prm4,void* Prm5)
{
    switch( Msg )
    {
        case VM_GETSTRING:
        {
            return LoadString(Prm1);
        }
        case VM_MENUVER:// Vertex Popup Menu
        {
            return true;
        }
        case VM_MENUEDIT:// Edit Popup Menu
        {
            return true;
        }
        case VM_ZOOM:
        {
            break;
        }
        case VM_ENDPAINT:
        {
            break;
        } 
        case VM_OBJACTIVE:
        {
            if(Prm1==VL_OBJ_PAGE)
            {
            }
            break;
        }
        case VM_DWGSELECT:
        {
    		#ifdef spl_EMB_EDITOR
            FormMain->UpdateLayers();
            #endif// spl_EMB_EDITOR
            break;
        } 
        case VM_EXECUTE:
        {
            break;
        }
        case VM_EXECUTED:
        {
            break;
        }
        case VM_LBDOWN:// Left Button Down
        case VM_MOUSEMOVE:// Mouse Move
        case VM_RBDOWN:// Right Button Down
        {
            break;
        }
        case VM_CMD_CREATE:
        case VM_CMD_OPEN:
        case VM_CMD_CLICK:
        case VM_CMD_DRAG:
        case VM_CMD_REDRAW:
        case VM_CMD_CLOSE:
        {
            switch(Prm1)
            {
                case spl_CMD_LINE:
                {
                	OnlyOne = true;
                    return spl_Cmd_Line(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_POLYLINE:
                {
                	OnlyOne = false;
                    return spl_Cmd_Line(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_POLYSATIN:
                {
                    return spl_Cmd_PolySatin(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_POLYSHAPE:
                {
                    return spl_Cmd_PolyShape(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_TEXT:
                {
                    return spl_Cmd_Text(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_EXTRUDE_POLYSHAPE:
                {
                    return spl_Cmd_ExtrudeShape(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_PLUG_IN:
                {
                	if(FormMain->nCurrPluginIndex < FormMain->pPlugins->Count)
                    {
					    TEmbPlugin *pEmbPlugin;
					    pEmbPlugin = (TEmbPlugin *)FormMain->pPlugins->Objects[FormMain->nCurrPluginIndex];
	                 	return pEmbPlugin->Draw(Msg,Prm2,Prm3,Prm4);
                    }
                    else
                    	return 0;
                }
            }
            break;
        }
        case VM_CLOSEQUERY:
        {
            AnsiString FileName=AnsiString((char *)Prm5);
            int ID=MessageDlg("File ["+FileName+"] Changed! \nSave Changes?",mtInformation,TMsgDlgButtons()<<mbYes<<mbNo,0);
            switch(ID)
            {
                case IDYES:
                {
                    FormDisplay->FileSave();
                    break;
                }
                case IDNO:
                {
                    break;
                }
            }
            return true;
        }
        //////////////////////////////
        // Export Embroidery Format //
        //////////////////////////////
        // Start Exporting
        case VM_EXP_BEGIN:
        {
            FileName=AnsiString((char *)Prm5);
            GlobalStitchPath.erase(GlobalStitchPath.begin(),GlobalStitchPath.end());
            EmbHeader.ColorStitchs=0;
            EmbHeader.NormalStitchs=0;
            EmbHeader.JumpStitchs=0;
            strcpy(EmbHeader.Comments,spl_Comments);
            IsFirstColor=true;
            P=splPoint(0,0);
            return true;
        }
        // End Of Exporting
        case VM_EXP_END:
        {
            FormProgress->Hide();

            EmbHeader.StitchsCount=EmbHeader.ColorStitchs+EmbHeader.NormalStitchs+EmbHeader.JumpStitchs;
            spl_ConvertGlobalStitchPathToStitchPath(GlobalStitchPath,StitchPath);
            FormProgress->Show();
            spl_SaveEmbToFile(FileName,StitchPath,&EmbHeader,FormProgress->ProgressBar1);
            FormProgress->Hide();
            return true;
        }
        // Start Exporting Entities
        case VM_EXP_ENTITY:
        {
            return false;
        }
        // Move To (Jump Stitch)
        case VM_EXP_MOVETO:
        {
            P.x=Prm3;
            P.y=Prm4;

            GlobalStitch.x=P.x;
            GlobalStitch.y=P.y;
            GlobalStitch.type=spl_stJump;
            GlobalStitchPath.push_back(GlobalStitch);
            EmbHeader.JumpStitchs++;
            break;
        }
        // Line To (Normal Stitch)
        case VM_EXP_LINETO:
        {
            P.x=Prm3;
            P.y=Prm4;

            GlobalStitch.x=P.x;
            GlobalStitch.y=P.y;
            GlobalStitch.type=spl_stNormal;
            GlobalStitchPath.push_back(GlobalStitch);

            FormProgress->ProgressBar1->Position++;
            EmbHeader.NormalStitchs++;
            break;
        }
        // Color Changed
        case VM_EXP_COLOR:
        {
/*
            if(!IsFirstColor)
            {
                GlobalStitch.x=P.x;
                GlobalStitch.y=P.y;
                GlobalStitch.type=spl_stColorChanged;
                GlobalStitchPath.push_back(GlobalStitch);

                EmbHeader.Colors[EmbHeader.ColorStitchs].r=GetRValue(Color);
                EmbHeader.Colors[EmbHeader.ColorStitchs].g=GetGValue(Color);
                EmbHeader.Colors[EmbHeader.ColorStitchs].b=GetBValue(Color);
                EmbHeader.ColorStitchs++;
            }
            Color=Prm1;
            IsFirstColor=false;
*/            
            break;
        }
        // Pen Width Changed
        case VM_EXP_WIDTH:
        {
            PenWidth=Prm3;
            break;
        }
        // Layer Changed
        case VM_EXP_LAYER:
        {
            if(!IsFirstColor)
            {
                Color=vlPropGetInt(VD_LAYER_COLOR,LayerIndex);

                GlobalStitch.x=P.x;
                GlobalStitch.y=P.y;
                GlobalStitch.type=spl_stColorChanged;
                GlobalStitchPath.push_back(GlobalStitch);

                EmbHeader.Colors[EmbHeader.ColorStitchs].r=GetRValue(Color);
                EmbHeader.Colors[EmbHeader.ColorStitchs].g=GetGValue(Color);
                EmbHeader.Colors[EmbHeader.ColorStitchs].b=GetBValue(Color);
                EmbHeader.ColorStitchs++;
            }
            LayerIndex=Prm1;
            IsFirstColor=false;
            break;
        }
        // Stop Pen Feed
        case VM_EXP_PUMPOFF:
        {
            break;
        }
        // Explode Into Small Lines
        case VM_EXP_EXPLODE:
        {
            LinesCount=Prm1;
            FormProgress->ProgressBar1->Min=0;
            FormProgress->ProgressBar1->Max=LinesCount;
            FormProgress->ProgressBar1->Step=1;
            FormProgress->ProgressBar1->Position=0;
            FormProgress->Panel1->Caption="Exporting Drawing Into Embroidery Format ...";
            FormProgress->Panel2->Caption=IntToStr(LinesCount);
            FormProgress->Show();
            FormProgress->Update();
            break;
        }
        // Arc To
        case VM_EXP_ARCTO:
        {
            break;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
static double dx;
static double dy;
static spl_Contour Contour;
static spl_Contour Extrude;
static spl_Contour Result;
static double ExtrudeDistance;
static spl_Point Center;

static double Density=3.0;
static bool Default = false;
static bool bMin = true;
//---------------------------------------------------------------------------
void spl_Initialize_Commands()
{
    switch(CommandType)
    {
     	case ctNone:
        {
         	break;
        }
        case ctPolySatin:
        {
	        // Command Need PointsCount Steps
    	    Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
	        Extrude.Points.erase(Extrude.Points.begin(),Extrude.Points.end());
	        Extrude.Points.resize(g_nEdgeCounts);
         	break;
        }
    }
}
//---------------------------------------------------------------------------
int spl_Cmd_Line(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double x0;
    static double y0;
    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need 2 Steps
            return 2;
        }
        case VM_CMD_CLICK:
        {
            switch(Step)
            {
                case 2:// Entered First Point
                {
                    x0=x;
                    y0=y;
                    return 1;
                }
                case 1:// Entered Second Point
                {
                    vlAddLine(x0,y0,x,y);
                    if(OnlyOne)
                    {
                        return 0;// End The Command
                    }
                    else
                    {
                        x0=x;
                        y0=y;
                        return 1;// Don`t End The Command
                    }
                }
            }
            return 0;
        }
        case VM_CMD_DRAG:
        {
            if(Step==1)
            {
                // Drag Line By Mouse While Not Click The Second Point
                vlDrawLine(x0,y0,x,y);
            }
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void DrawPolyline(spl_Contour &Contour,spl_UInt Color)
{
    spl_UInt PointsCount=Contour.Points.size();
    for(spl_UInt i=0;i<PointsCount;i++)
    {
        vlDrawLine(Contour.Points[(i) % PointsCount].x,Contour.Points[(i) % PointsCount].y,Contour.Points[(i+1) % PointsCount].x,Contour.Points[(i+1) % PointsCount].y);
    }
}
//---------------------------------------------------------------------------
void DrawSkeleton(spl_Contour &Contour,spl_Contour &Extrude,spl_UInt Color)
{
    spl_UInt PointsCount=Contour.Points.size();
    for(spl_UInt i=0;i<PointsCount;i++)
    {
        vlDrawLine(Contour.Points[(i) % PointsCount].x,Contour.Points[(i) % PointsCount].y,Contour.Points[(i+1) % PointsCount].x,Contour.Points[(i+1) % PointsCount].y);
        vlDrawLine(Extrude.Points[(i) % PointsCount].x,Extrude.Points[(i) % PointsCount].y,Extrude.Points[(i+1) % PointsCount].x,Extrude.Points[(i+1) % PointsCount].y);
        vlDrawLine(Contour.Points[(i) % PointsCount].x,Contour.Points[(i) % PointsCount].y,Extrude.Points[(i) % PointsCount].x,Extrude.Points[(i) % PointsCount].y);
    }
}
//---------------------------------------------------------------------------
void AddPolyline(spl_Contour &Contour,spl_UInt Color)
{
    spl_UInt PointsCount=Contour.Points.size();
    vlPolylineBegin();
    for(spl_UInt i=0;i<=PointsCount;i++)
    {
        vlVertex(Contour.Points[i % PointsCount].x,Contour.Points[i % PointsCount].y);
    }
    vlAddPolyline(VL_POLY_LINE,true);
}
//---------------------------------------------------------------------------
/*
void GetPolylineCenter(spl_Contour &Contour,spl_Point &Center)
{
    spl_UInt PointsCount=Contour.Points.size();
    Center.x=0;
    Center.y=0;
    for(spl_UInt i=0;i<PointsCount;i++)
    {
        Center.x+=Contour.Points[(i) % PointsCount].x;
        Center.y+=Contour.Points[(i) % PointsCount].y;
    }
    Center.x/=double(PointsCount);
    Center.y/=double(PointsCount);
}
*/
//---------------------------------------------------------------------------
/*
int spl_Cmd_PolySatin(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double dx;
    static double dy;
    static spl_Contour Contour;
    static spl_Contour Extrude;
    static spl_Contour Result;
    static double ExtrudeDistance;
    static spl_UInt Color=clBlack;
    static spl_Point Center;
    static bool Created = false;

    static double Density=3.0;
    static bool Default = false;
    static bool bMin = true;

    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need PointsCount Steps
            Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
            Extrude.Points.erase(Extrude.Points.begin(),Extrude.Points.end());
            Created = true;
            return 1;
        }
        case VM_CMD_CLICK:
        {
			Contour.Points.resize(Contour.Points.size() + 1);
			Contour.Points[Contour.Points.size() - 1].x=x;
            Contour.Points[Contour.Points.size() - 1].y=y;
            // Clear Polyline And Calculate Center
            DrawPolyline(Contour,Color);
            GetPolylineCenter(Contour,Center);
            return 0;
        }
        case VM_CMD_DRAG:
        {
			if(!Created)	return 0;
			Contour.Points.resize(Contour.Points.size() + 1);
			Contour.Points[Contour.Points.size() - 1].x=x;
            Contour.Points[Contour.Points.size() - 1].y=y;
            DrawPolyline(Contour,Color);
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
*/
//---------------------------------------------------------------------------

int spl_Cmd_PolySatin(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double dx;
    static double dy;
    static spl_Contour Contour;
    static spl_Contour Extrude;
    static spl_Contour Result;
    static double ExtrudeDistance;
    static spl_UInt Color=clBlack;
    static spl_Point Center;
    static bool Created = false;

    static double Density=3.0;
    static bool Default = true;
    static bool bMin = true;

    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need PointsCount Steps
            Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
            Extrude.Points.erase(Extrude.Points.begin(),Extrude.Points.end());
//            Contour.Points.resize(g_nEdgeCounts);
            Extrude.Points.resize(g_nEdgeCounts);
            Created = true;
            return g_nEdgeCounts+1;
        }
        case VM_CMD_CLICK:
        {
        	if(Step == g_nEdgeCounts + 1)
            {
            	Contour.Points.resize(g_nEdgeCounts - Step + 2);
            	Contour.Points[g_nEdgeCounts - Step + 1].x=x;
                Contour.Points[g_nEdgeCounts - Step + 1].y=y;
                return Step - 1;
            }
            else
        	if(Step == g_nEdgeCounts)
            {
            	Contour.Points.resize(g_nEdgeCounts - Step + 2);
            	Contour.Points[g_nEdgeCounts - Step + 1].x=x;
                Contour.Points[g_nEdgeCounts - Step + 1].y=y;

                // Clear Line
                vlDrawLine(Contour.Points[g_nEdgeCounts - Step].x,Contour.Points[g_nEdgeCounts - Step].y,Contour.Points[g_nEdgeCounts - Step + 1].x,Contour.Points[g_nEdgeCounts - Step + 1].y);
                return Step - 1;
            }
            else
        	if(Step == 1)// Entered End Point
            {
            	dx=spl_ABS(x-Center.x);
                dy=spl_ABS(y-Center.y);
                ExtrudeDistance=sqrt(dx*dx+dy*dy);

                spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
                spl_EmbroidContour(bMin,ExtrudeDistance,Density,Default,Contour,Result);
                AddPolyline(Result,Color);
                return Step - 1;// End The Command
            }
            else
            {
            	Contour.Points.resize(g_nEdgeCounts - Step + 2);
            	Contour.Points[g_nEdgeCounts - Step + 1].x=x;
                Contour.Points[g_nEdgeCounts - Step + 1].y=y;

                // Clear Polyline And Calculate Center
                DrawPolyline(Contour,Color);
//                GetPolylineCenter(Contour,Center);
                Center = spl_Center(Contour);
                return Step - 1;// End The Command
            }
        }
        case VM_CMD_DRAG:
        {
			if(!Created)	return 0;
            if(Step == g_nEdgeCounts)
            {
            	Contour.Points.resize(g_nEdgeCounts - Step + 2);
                Contour.Points[g_nEdgeCounts - Step + 1].x=x;
                Contour.Points[g_nEdgeCounts - Step + 1].y=y;
                vlDrawLine(Contour.Points[g_nEdgeCounts - Step].x,Contour.Points[g_nEdgeCounts - Step].y,Contour.Points[g_nEdgeCounts - Step + 1].x,Contour.Points[g_nEdgeCounts - Step + 1].y);
            }
            else
            if(Step == 1)
            {
                // Drag Line By Mouse While Not Click The Second Point
                vlDrawLine(Center.x,Center.y,x,y);

                dx=spl_ABS(x-Center.x);
                dy=spl_ABS(y-Center.y);
                ExtrudeDistance=sqrt(dx*dx+dy*dy);

                spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
                DrawSkeleton(Contour,Extrude,Color);
            }
            else
            {
            	Contour.Points.resize(g_nEdgeCounts - Step + 2);
                Contour.Points[g_nEdgeCounts - Step + 1].x=x;
                Contour.Points[g_nEdgeCounts - Step + 1].y=y;
                DrawPolyline(Contour,Color);
            }
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}

//---------------------------------------------------------------------------
int spl_Cmd_ExtrudeShape(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double dx;
    static double dy;
    static spl_Contour Contour;
    static spl_Contour Extrude;
    static spl_Contour Result;
    static double ExtrudeDistance;
    static spl_UInt Color=clBlack;
    static spl_Point Center;
    static bool Created = false;

    static double Density=3.0;
    static bool Default = true;
    static bool bMin = true;

    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need PointsCount Steps
            Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
            Extrude.Points.erase(Extrude.Points.begin(),Extrude.Points.end());
            Created = true;
            return 2;
        }
        case VM_CMD_CLICK:
        {
        	if(Step == 2)
            {
				// Create new shape
                
	        	spl_Point P;
	            float fXRadius = 10.0;
	            float fYRadius = 10.0;

	        	for(float fAngle=0.0;fAngle<360.0;fAngle+=22.5)
	            {
					P.x = x + fXRadius * cos(DegToRad(fAngle));
					P.y = y + fYRadius * sin(DegToRad(fAngle));

	            	Contour.Points.push_back(P);
	            }

/*
				float d = 20;
                Contour.Points.push_back(splPoint(0,3*d/2.0));
                Contour.Points.push_back(splPoint(-d/2.0,d/2.0));
                Contour.Points.push_back(splPoint(-d,d/2.0));
                Contour.Points.push_back(splPoint(-d/2.0,0));
                Contour.Points.push_back(splPoint(-d,-d));
                Contour.Points.push_back(splPoint(0,-d/2.0));
                Contour.Points.push_back(splPoint(d,-d));
                Contour.Points.push_back(splPoint(d/2.0,0));
                Contour.Points.push_back(splPoint(d,d/2.0));
                Contour.Points.push_back(splPoint(d/2.0,d/2.0));
*/
//	        	GetPolylineCenter(Contour,Center);
	        	Center = spl_Center(Contour);
    	        return 1;
            }
            else
        	if(Step == 1)
            {
	        	dx=spl_ABS(x-Center.x);
	            dy=spl_ABS(y-Center.y);
	            ExtrudeDistance=sqrt(dx*dx+dy*dy);

	            spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
	            spl_EmbroidContour(bMin,ExtrudeDistance,Density,Default,Contour,Result);
	            AddPolyline(Result,Color);
    	        return 0;// End The Command
            }
        }
        case VM_CMD_DRAG:
        {
			if(!Created)	return 0;
			dx=spl_ABS(x-Center.x);
            dy=spl_ABS(y-Center.y);
            ExtrudeDistance=sqrt(dx*dx+dy*dy);

            spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
            spl_EmbroidContour(bMin,ExtrudeDistance,Density,Default,Contour,Result);
            DrawPolyline(Result,Color);
            DrawPolyline(Contour,Color);
            DrawPolyline(Extrude,Color);
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
int spl_Cmd_PolyShape(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double dx;
    static double dy;
    static spl_Contour Contour;
    static spl_Contour Extrude;
    static spl_Contour Result;
    static double ExtrudeDistance;
    static spl_UInt Color=clBlack;
    static spl_Point Center;
    static bool Created = false;

    static double Density=1.0;
    static bool Default = false;
    static bool bMin = true;

    static spl_Rect Frame;

    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            Created = false;
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need PointsCount Steps
            Contour.Points.clear();
            Extrude.Points.clear();
            Created = false;
            return 2;
        }
        case VM_CMD_CLICK:
        {
        	if(Step == 2)
            {
				// Create new shape
	        	spl_Point P;
	            float fXRadius = 3.0;
	            float fYRadius = 3.0;

                Contour.Points.clear();
	        	for(float fAngle=0.0;fAngle<360.0;fAngle+=22.5)
	            {
					P.x = x + fXRadius * cos(DegToRad(fAngle));
					P.y = y + fYRadius * sin(DegToRad(fAngle));

	            	Contour.Points.push_back(P);
	            }

                ExtrudeDistance = 10;
	            spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
	            spl_EmbroidContour(bMin,ExtrudeDistance,Density,Default,Contour,Result);
//	        	GetPolylineCenter(Result,Center);
	        	Center = spl_Center(Result);
            	Created = true;
    	        return 1;
            }
            else
        	if(Step == 1)
            {
	            AddPolyline(Contour,Color);
    	        return 0;// End The Command
            }
        }
        case VM_CMD_DRAG:
        {
			if(!Created)	return 0;
			dx=spl_ABS(x-Center.x);
            dy=spl_ABS(y-Center.y);
            ExtrudeDistance=sqrt(dx*dx+dy*dy);

			Frame.left = Center.x - ExtrudeDistance;
			Frame.right = Center.x + ExtrudeDistance;
			Frame.top = Center.y - ExtrudeDistance;
			Frame.bottom = Center.y + ExtrudeDistance;

            spl_ScaleContour(Result,Frame,false,1.0,Contour);
            DrawPolyline(Contour,Color);
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
void spl_DrawText(int x,int y)
{
	AnsiString strText = FormInsertText->RichEdit->Text.Trim();
    UINT Count = strText.Length();
    wchar_t *pGlyphs = new wchar_t[Count];
    HDC hdc = FormInsertText->Label->Canvas->Handle;
    spl_TextToGlyphs(hdc,strText.c_str(),pGlyphs,Count);

    spl_Point Origin;
    Origin = splPoint(x,y);

    for(UINT i=0;i<Count;i++)
    {
		GetCharacterGlyphs(hdc,pGlyphs[i],false,Origin);
    }

    if(pGlyphs)
    {
     	delete[] pGlyphs;
        pGlyphs = NULL;
    }
}
//---------------------------------------------------------------------------
int spl_Cmd_Text(int Msg,int Step,double x,double y)
{
    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
			if(FormInsertText->ShowModal() != mrOk)	return 0;
            vlRedraw();
            return 1;
        }
        case VM_CMD_CLICK:
        {
        	if(Step == 1)// Entered End Point
            {
            	spl_DrawText(x,y);

                return Step - 1;// End The Command
            }
            return 0;
        }
        case VM_CMD_DRAG:
        {
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
/*
int spl_Cmd_PolySatin(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double dx;
    static double dy;
    static spl_Contour Contour;
    static spl_Contour Extrude;
    static spl_Contour Result;
    static double ExtrudeDistance;
    static spl_UInt Color=clBlack;
    static spl_Point Center;
    static double Density=2.0;

    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need PointsCount Steps
            Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
            Extrude.Points.erase(Extrude.Points.begin(),Extrude.Points.end());
            Contour.Points.resize(3);
            Extrude.Points.resize(3);
            return 3+1;
        }
        case VM_CMD_CLICK:
        {
            switch(Step)
            {
                case 4:// Entered First Point
                {
                    Contour.Points[0].x=x;
                    Contour.Points[0].y=y;
                    return 3;
                }
                case 3:// Entered Second Point
                {
                    Contour.Points[1].x=x;
                    Contour.Points[1].y=y;

                    // Clear Line
                    vlDrawLine(Contour.Points[0].x,Contour.Points[0].y,Contour.Points[1].x,Contour.Points[1].y);
                    return 2;
                }
                case 2:// Entered Third Point
                {
                    Contour.Points[2].x=x;
                    Contour.Points[2].y=y;

                    // Clear Polyline And Calculate Center
                    DrawPolyline(Contour,Color);
                    GetPolylineCenter(Contour,Center);
                    return 1;// End The Command
                }
                case 1:// Entered Forth Point
                {
                    dx=spl_ABS(x-Center.x);
                    dy=spl_ABS(y-Center.y);
                    ExtrudeDistance=sqrt(dx*dx+dy*dy);

                    spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
                    spl_EmbroidContour(ExtrudeDistance,Density,true,Contour,Result);
                    AddPolyline(Result,Color);
                    return 0;// End The Command
                }
            }
            return 0;
        }
        case VM_CMD_DRAG:
        {
            if(Step==3)
            {
                Contour.Points[1].x=x;
                Contour.Points[1].y=y;
                vlDrawLine(Contour.Points[0].x,Contour.Points[0].y,Contour.Points[1].x,Contour.Points[1].y);
            }
            else
            if(Step==2)
            {
                Contour.Points[2].x=x;
                Contour.Points[2].y=y;
                DrawPolyline(Contour,Color);
            }
            else
            if(Step==1)
            {
                // Drag Line By Mouse While Not Click The Second Point
                vlDrawLine(Center.x,Center.y,x,y);

                dx=spl_ABS(x-Center.x);
                dy=spl_ABS(y-Center.y);
                ExtrudeDistance=sqrt(dx*dx+dy*dy);

                spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
                DrawSkeleton(Contour,Extrude,Color);
            }
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
*/
//---------------------------------------------------------------------------

