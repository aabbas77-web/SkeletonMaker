//---------------------------------------------------------------------------
#include <vcl.h>
#include <assert.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_EmbSimulator.h"
#include "spl_Timer.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
spl_EmbSimulator *pEmbSimulator=NULL;
//---------------------------------------------------------------------------
void spl_StitchStretchDraw32(spl_StitchPath &StitchPath,spl_EmbHeader &EmbHeader,TBitmap32 *pBMP,spl_Rect &Frame,spl_Scale &Scale,TColor32 ClearColor,spl_UByte Alpha,bool ShowJumps,bool Colored,TColor32 DisableColor)
{
    spl_Stitch Stitch;
    bool IsPrevJump;
    spl_UInt ColorIndex;
    double Ax2,Ay2;
    double x,y;
    double nx,ny;
    double w,h;
    double Ratio;
    w=EmbHeader.right-EmbHeader.left;
    h=EmbHeader.bottom-EmbHeader.top;
    if((w<=0)||(h<=0))    return;
    spl_RGB Color;
    double W,H;
    TArrayOfColor32 Stipple;
    int Step;

    Ratio=w/h;
    if(Frame.Width()>=Frame.Height())
    {
        H=Frame.Height();
        W=Ratio*H;
    }
    else
    {
        W=Frame.Width();
        H=W/Ratio;
    }

    Scale.Ax=W/w;
    Scale.Bx=Frame.left-Scale.Ax*EmbHeader.left;
    Scale.Ay=H/h;
    Scale.By=Frame.top-Scale.Ay*EmbHeader.top;

    Ax2=pow(Scale.Ax,2.0);
    Ay2=pow(Scale.Ay,2.0);

    pBMP->BeginUpdate();
    pBMP->SetSize(W,H);
    if(pEmbSimulator)   pEmbSimulator->Clear();

    ColorIndex=0;
    if(Colored)
    {
        Color=EmbHeader.Colors[ColorIndex];
        pBMP->PenColor=Color32(Color.r,Color.g,Color.b,Alpha);
    }
    else
    {
        pBMP->PenColor=DisableColor;
    }

    ColorIndex++;
    x=0.0;
    y=0.0;
    for(spl_UInt i=0;i<EmbHeader.StitchsCount;i++)
    {
        Stitch=StitchPath[i];
        x+=Stitch.x;
        y+=Stitch.y;
        nx=Scale.Ax*x+Scale.Bx;
        ny=H-1-(Scale.Ay*y+Scale.By);
        switch(Stitch.type)
        {
            case spl_stNormal:
            {
                if(i==0)
                    pBMP->MoveToF(nx,ny);
                else
                {
                    if(IsPrevJump)
                    {
                        if(ShowJumps)
                        {
                            if(Colored)
                            {
                                Stipple.set_length(3);
                                Stipple[0]=pBMP->PenColor;
                                Stipple[1]=0;
                                Stipple[2]=pBMP->PenColor;
                                pBMP->SetStipple(Stipple);
                                pBMP->StippleStep=1.0/3.0;

                                pBMP->LineToFSP(nx,ny);
                            }
                            else
                            {
                                pBMP->LineToS(nx,ny);
                            }
                        }
                        else
                        {
                            if(Colored)
                            {
                                pBMP->MoveToF(nx,ny);
                            }
                            else
                            {
                                pBMP->MoveTo(nx,ny);
                            }
                        }
                    }
                    else
                    {
                        if(Colored)
                        {
                            Step=sqrt(Ax2*Stitch.x*Stitch.x+Ay2*Stitch.y*Stitch.y);
                            if(Step>0)
                            {
                                Stipple.set_length(Step);
                                if(pBMP->PenColor==clBlack32)
                                {
                                    Stipple[0]=clGray32;
                                    for(int j=1;j<Step;j++) Stipple[j]=pBMP->PenColor;
                                }
                                else
                                {
                                    Stipple[0]=clBlack32;
                                    for(int j=1;j<Step;j++) Stipple[j]=pBMP->PenColor;
                                }
                                pBMP->SetStipple(Stipple);
                                pBMP->StippleStep=1.0/Step;
                            }
                            else
                            {
                                Stipple.set_length(1);
                                Stipple[0]=clBlack32;
                                pBMP->SetStipple(Stipple);
                                pBMP->StippleStep=1.0;
                            }
                            pBMP->LineToFSP(nx,ny);
                        }
                        else
                        {
                            pBMP->LineToS(nx,ny);
                        }
                    }
                }
                IsPrevJump=false;
                break;
            }
            case spl_stJump:
            {
                IsPrevJump=true;
                break;
            }
            case spl_stColorChanged:
            {
                if(Colored)
                {
                    if(ColorIndex<EmbHeader.ColorStitchs)
                    {
                        Color=EmbHeader.Colors[ColorIndex];
                    }
                    else
                    {
                        Color.r=random(255);
                        Color.g=random(255);
                        Color.b=random(255);
                    }
                    pBMP->PenColor=Color32(Color.r,Color.g,Color.b,Alpha);
                    ColorIndex++;
                }
                IsPrevJump=true;
                break;
            }
            case spl_stEof:
            {
                break;
            }
        }
    }

    pBMP->EndUpdate();
    pBMP->Changed();
}
//---------------------------------------------------------------------------
static double _x;
static double _y;
static double _nx;
static double _ny;
static double __nx;
static double __ny;
static spl_Stitch _Stitch;
static spl_RGB _Color;
static TArrayOfColor32 _Stipple;
static int _Step;
static spl_UInt _StitchIndex;
static spl_UInt _ColorIndex;
static bool _IsPrevJump;
static spl_UInt _ToIndex;
static bool _Finish=true;

static TPanel *_pPanelAbs;
static TPanel *_pPanelRel;
static TPanel *_pPanelSt;
static TPanel *_pPanelStitchIndex;
static TShape *_pShapeMachine;
static TAction *_pAMachine;
static TAction *_pAStopOnNormal;
static TAction *_pAStopOnJump;
static TAction *_pAStopOnColor;
//---------------------------------------------------------------------------
void CALLBACK TimerCallback(UINT wTimerID,UINT msg,DWORD dwUser,DWORD dw1,DWORD dw2)
{
    _Finish=true;
    if(!spl_TimerEnabled)   return;
    if(!pEmbSimulator)  return;
    _Finish=false;

    pEmbSimulator->m_pBitmap->BeginUpdate();

    for(spl_UInt i=0;(i<pEmbSimulator->m_nBlockSize)&&(_StitchIndex<pEmbSimulator->m_EmbHeader.StitchsCount);i++)
    {
        if(!spl_TimerEnabled)   break;
        if(!pEmbSimulator)
        {
            spl_TimerEnabled=false;
            break;
        }
        if((_StitchIndex==_ToIndex)||(_StitchIndex>=pEmbSimulator->m_EmbHeader.StitchsCount-1))
        {
            spl_TimerEnabled=false;
            _ToIndex=pEmbSimulator->m_EmbHeader.StitchsCount-1;
            break;
        }

        _Stitch=pEmbSimulator->m_StitchPath[_StitchIndex];
        _StitchIndex++;
        _x+=_Stitch.x;
        _y+=_Stitch.y;
        _nx=pEmbSimulator->m_Scale.Ax*_x+pEmbSimulator->m_Scale.Bx;
        _ny=pEmbSimulator->m_dHeight-1-(pEmbSimulator->m_Scale.Ay*_y+pEmbSimulator->m_Scale.By);

        _pPanelAbs->Caption=FormatFloat("0",_x)+" , "+FormatFloat("0",_y);
        _pPanelRel->Caption=FormatFloat("0",_Stitch.x)+" , "+FormatFloat("0",_Stitch.y);
        _pPanelStitchIndex->Caption=IntToStr(_StitchIndex);

        if(_pAMachine->Checked)
        {
            _pShapeMachine->Left=_nx+pEmbSimulator->m_ndX;
            _pShapeMachine->Top=_ny+pEmbSimulator->m_ndY;
        }

        switch(_Stitch.type)
        {
            case spl_stNormal:
            {
                _pPanelSt->Caption="Normal";
                _pPanelSt->Font->Color=clBlack;

                if(_StitchIndex==0)
                    pEmbSimulator->m_pBitmap->MoveToF(_nx,_ny);
                else
                {
                    if(_IsPrevJump)
                    {
                        if(pEmbSimulator->m_bShowJumps)
                        {
                            _Stipple.set_length(3);
                            _Stipple[0]=pEmbSimulator->m_pBitmap->PenColor;
                            _Stipple[1]=0;
                            _Stipple[2]=pEmbSimulator->m_pBitmap->PenColor;
                            pEmbSimulator->m_pBitmap->SetStipple(_Stipple);
                            pEmbSimulator->m_pBitmap->StippleStep=1.0/3.0;
                        }
                        else
                        {
                            pEmbSimulator->m_pBitmap->MoveToF(_nx,_ny);
                        }
                    }
                    else
                    {
                        _Step=spl_Round(sqrt(pEmbSimulator->Ax2*_Stitch.x*_Stitch.x+pEmbSimulator->Ay2*_Stitch.y*_Stitch.y));
                        if(_Step > 1)
                        {
                            _Stipple.set_length(_Step);
                            if(pEmbSimulator->m_pBitmap->PenColor==clBlack32)
                            {
                                _Stipple[0]=clGray32;
                                for(int j=1;j<_Step;j++) _Stipple[j]=pEmbSimulator->m_pBitmap->PenColor;
                            }
                            else
                            {
                                _Stipple[0]=clBlack32;
                                for(int j=1;j<_Step;j++) _Stipple[j]=pEmbSimulator->m_pBitmap->PenColor;
                            }
                            pEmbSimulator->m_pBitmap->SetStipple(_Stipple);
                            pEmbSimulator->m_pBitmap->StippleStep=1.0/_Step;
                        }
                        else
                        {
                            _Stipple.set_length(1);
                            _Stipple[0]=clBlack32;
                            pEmbSimulator->m_pBitmap->SetStipple(_Stipple);
                            pEmbSimulator->m_pBitmap->StippleStep=1.0;
                        }
                    }
                    pEmbSimulator->m_pBitmap->LineToFSP(_nx,_ny);
                }
                _IsPrevJump=false;
                if(_pAStopOnNormal->Checked)
                {
                    spl_TimerEnabled=false;
                    goto LEnd;
                }
                break;
            }
            case spl_stJump:
            {
                _pPanelSt->Caption="Jump";
                _pPanelSt->Font->Color=clBlue;

                _IsPrevJump=true;
                if(_pAStopOnJump->Checked)
                {
                    spl_TimerEnabled=false;
                    goto LEnd;
                }
                break;
            }
            case spl_stColorChanged:
            {
                _pPanelSt->Caption="Color";
                _pPanelSt->Font->Color=clRed;

                if(_ColorIndex<pEmbSimulator->m_nColorsCount)
                {
                    _Color=pEmbSimulator->m_EmbHeader.Colors[_ColorIndex];
                }
                else
                {
                    _Color.r=random(255);
                    _Color.g=random(255);
                    _Color.b=random(255);
                }
                pEmbSimulator->m_pBitmap->PenColor=Color32(_Color.r,_Color.g,_Color.b,pEmbSimulator->m_Alpha);
                _ColorIndex++;
                _IsPrevJump=true;
                if(_pAStopOnColor->Checked)
                {
                    spl_TimerEnabled=false;
                    goto LEnd;
                }
                break;
            }
            case spl_stEof:
            {
                _pPanelSt->Caption="EOF";
                _pPanelSt->Font->Color=clGreen;
                break;
            }
        }
    }

    LEnd:;
    pEmbSimulator->m_pBitmap->EndUpdate();
    pEmbSimulator->m_pBitmap->Changed();

    _Finish=true;
}
//---------------------------------------------------------------------------
void NextStitch()
{
    spl_TimerEnabled = true;
	TimerCallback(1,1,1,1,1);
    spl_TimerEnabled = false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
spl_EmbSimulator::spl_EmbSimulator(spl_UInt Interval)
{
    m_nInterval=Interval;

    m_pBitmap=FormMain->Image->Bitmap;
    m_pProgressBar=FormMain->ProgressBar1;

    _pPanelAbs=FormMain->PanelAbs;
    _pPanelRel=FormMain->PanelRel;
    _pPanelSt=FormMain->PanelSt;
    _pPanelStitchIndex=FormMain->PanelStitchIndex;
    _pShapeMachine=FormMain->ShapeMachine;
    _pAMachine=FormMain->AMachine;
    _pAStopOnNormal=FormMain->AStopOnNormal;
    _pAStopOnJump=FormMain->AStopOnJump;
    _pAStopOnColor=FormMain->AStopOnColor;

    spl_TimerEnabled=false;
    spl_CreateTimer(TimerCallback,m_nInterval,0);
    _StitchIndex=0;

    m_Frame=spl_Rect(0,0,400,400);
    m_bShowJumps=false;
    m_nBlockSize=10;
    m_bLoaded=false;

    m_pBk=NULL;
    m_pBk=new TBitmap32();
}
//---------------------------------------------------------------------------
spl_EmbSimulator::~spl_EmbSimulator()
{
    Stop();
    spl_DestroyTimer();
    if(m_pBk)   delete m_pBk;m_pBk=NULL;
}
//---------------------------------------------------------------------------
void spl_EmbSimulator::LoadFromFile(AnsiString FileName)
{
    m_strFileName=FileName;
    spl_LoadEmbFromFile(m_strFileName,m_StitchPath,&m_EmbHeader,m_pProgressBar);
    m_bLoaded=true;

    double XRes;
    double YRes;
    HDC hdc=CreateDC("DISPLAY",NULL,NULL,NULL);
    spl_GetDeviceResulotion_PPDisiem(hdc,XRes,YRes);
    DeleteDC(hdc);
    m_nWidth=(m_EmbHeader.right-m_EmbHeader.left)*XRes;
    m_nHeight=(m_EmbHeader.bottom-m_EmbHeader.top)*YRes;
}
//---------------------------------------------------------------------------
void spl_EmbSimulator::SaveToFile(AnsiString FileName)
{
    m_strFileName=FileName;
    spl_SaveEmbToFile(m_strFileName,m_StitchPath,&m_EmbHeader,m_pProgressBar);
}
//---------------------------------------------------------------------------
void spl_EmbSimulator::Show(bool Colored,TColor32 DisableColor)
{
    spl_StitchStretchDraw32(m_StitchPath,m_EmbHeader,m_pBitmap,m_Frame,m_Scale,m_BackgroundColor,m_Alpha,m_bShowJumps,Colored,DisableColor);
}
//---------------------------------------------------------------------------
void spl_EmbSimulator::Clear()
{
    m_pBitmap->Clear(m_BackgroundColor);
    if(!m_pBk->Empty())
    {
        // Draw Tile
        for(int y=0;y<m_pBitmap->Height;y+=m_pBk->Height)
        {
            for(int x=0;x<m_pBitmap->Width;x+=m_pBk->Width)
            {
                m_pBitmap->Draw(x,y,m_pBk);
            }
        }
    }
}
//---------------------------------------------------------------------------
void spl_EmbSimulator::Update()
{
    Ax2=pow(m_Scale.Ax,2.0);
    Ay2=pow(m_Scale.Ay,2.0);

    m_dHeight=m_pBitmap->Height;

    m_nColorsCount=spl_MAX(m_EmbHeader.ColorStitchs,spl_MaxTajimaColors);
}
//---------------------------------------------------------------------------
void spl_EmbSimulator::Start()
{
    Stop();
    Update();
    Play();
}
//---------------------------------------------------------------------------
void spl_EmbSimulator::Play()
{
    spl_TimerEnabled=true;
}
//---------------------------------------------------------------------------
void spl_EmbSimulator::Pause()
{
    spl_TimerEnabled=false;
}
//---------------------------------------------------------------------------
void spl_EmbSimulator::Stop()
{
    Pause();

    _StitchIndex=0;
    _ColorIndex=0;
    _Color=m_EmbHeader.Colors[_ColorIndex];
    m_pBitmap->PenColor=Color32(_Color.r,_Color.g,_Color.b,m_Alpha);

    _IsPrevJump=false;
    _Stipple.set_length(0);

    _ToIndex=pEmbSimulator->m_EmbHeader.StitchsCount-1;
    
    _ColorIndex++;
    _x=0.0;
    _y=0.0;
}
//---------------------------------------------------------------------------
void spl_EmbSimulator::PlayTo(spl_UInt ToIndex)
{
    Stop();
    Update();
    _ToIndex=ToIndex;
    Play();
}
//---------------------------------------------------------------------------
spl_UInt spl_EmbSimulator::GetPosition()
{
    return _StitchIndex;
}
//---------------------------------------------------------------------------
bool spl_EmbSimulator::Bof()
{
    return (_StitchIndex<=0);
}
//---------------------------------------------------------------------------
bool spl_EmbSimulator::Eof()
{
    return (_StitchIndex>=pEmbSimulator->m_EmbHeader.StitchsCount-1);
}
//---------------------------------------------------------------------------
void spl_EmbSimulator::FlushAndFree()
{
    Stop();
    while(!_Finish)
    {
        Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------
void spl_EmbSimulator::SetInterval(int Value)
{
    if(Value!=m_nInterval)
    {
        m_nInterval=Value;

        bool PrevTimerEnabled=spl_TimerEnabled;
        Pause();
        spl_DestroyTimer();
        spl_CreateTimer(TimerCallback,m_nInterval,0);
        spl_TimerEnabled=PrevTimerEnabled;
    }
}
//---------------------------------------------------------------------------

