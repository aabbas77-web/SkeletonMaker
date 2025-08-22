//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_EmbLib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//------------------------Utils----------------------------------------------
//---------------------------------------------------------------------------
spl_UInt spl_TajimaColors[spl_MaxTajimaColors]={
                                            0x0000FF00,// 00
                                            0x00FF0000,// 01
                                            0x000000FF,// 02
                                            0x0000FFFF,// 03
                                            0x00FFFF00,// 04
                                            0x00FF00FF,// 05
                                            0x0060C830,// 06
                                            0x00307FB0,// 07
                                            0x00306700,// 08
                                            0x006030CF,// 09
                                            0x003098FF,// 10
                                            0x00CF0090,// 11
                                            0x00903000,// 12
                                            0x00000000,// 13
                                            0x00FFFFFF,// 14
                                            0x00CF7FFF,// 15
                                            0x00FF7870,// 16
                                            0x0030C8CF,// 17
                                            0x002F60C0,// 18
                                            0x00CFFF60,// 19
                                        };
//---------------------------------------------------------------------------
/*
//  Headers
//---------------------------------------------------------------------------
// Load
void spl_DSTRecToStitch(spl_DSXRec *pDSXRec,spl_Stitch *pStitch);
void spl_DSBRecToStitch(spl_DSXRec *pDSXRec,spl_Stitch *pStitch);
void spl_DSZRecToStitch(spl_DSXRec *pDSXRec,spl_Stitch *pStitch);
void spl_KSMRecToStitch(spl_DSXRec *pDSXRec,spl_Stitch *pStitch);
void spl_Load_DSX_From_Stream(char X,TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar);
void spl_Load_EXP_From_Stream(TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar);
void spl_Load_ALI_From_Stream(TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar);

// Save
AnsiString spl_AlignStr(AnsiString S,int Size,bool Left);
AnsiString spl_EmbHeaderToStr(spl_EmbHeader *pHeader);
void spl_GetCoff3(int X);
void spl_GetCoffDST(int X);
void spl_PointToDST(spl_Stitch *pStitch,spl_DSXRec *pDSXRec);
void spl_PointToDSB(spl_Stitch *pStitch,spl_DSXRec *pDSXRec);
void spl_PointToDSZ(spl_Stitch *pStitch,spl_DSXRec *pDSXRec);
void spl_PointToKSM(spl_Stitch *pStitch,spl_DSXRec *pDSXRec);
void spl_Save_DSX_To_Stream(char X,TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar);
void spl_Save_EXP_To_Stream(TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar);
void spl_Save_ALI_To_Stream(TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar);
*/
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
spl_DSXRec StitchToDSXRec(spl_Stitch &Stitch)
{
    spl_DSXRec DSXRec;
    DSXRec.Third=(~Stitch.type);
    DSXRec.Second=(~Stitch.y)^(DSXRec.Third);
    DSXRec.First=(~Stitch.x)^(DSXRec.Third);
    return DSXRec;
}
//---------------------------------------------------------------------------
spl_Stitch DSXRecToStitch(spl_DSXRec &DSXRec)
{
    spl_Stitch Stitch;
    Stitch.type=(~DSXRec.Third);
    Stitch.y=(~((DSXRec.Second)^(DSXRec.Third)));
    Stitch.x=(~((DSXRec.First)^(DSXRec.Third)));
    return Stitch;
}
//---------------------------------------------------------------------------
spl_Rect spl_ComputeFrame(spl_GlobalStitchPath &GlobalStitchPath)
{
    if(GlobalStitchPath.empty())  return spl_Rect(0,0,0,0);
    spl_Rect Frame=spl_Rect(spl_MaxInt,spl_MaxInt,-spl_MaxInt,-spl_MaxInt);
    spl_Point P;
    for(spl_UInt i=0;i<GlobalStitchPath.size();i++)
    {
        P.x=GlobalStitchPath[i].x;
        P.y=GlobalStitchPath[i].y;
        if(P.x<Frame.left)      Frame.left=P.x;
        if(P.y<Frame.top)       Frame.top=P.y;
        if(P.x>Frame.right)     Frame.right=P.x;
        if(P.y>Frame.bottom)    Frame.bottom=P.y;
    }
    return Frame;
}
//---------------------------------------------------------------------------
AnsiString spl_AlignStr(AnsiString S,int Size,bool Left)
{
    AnsiString tmp="";
    int Len=S.Length();
    if(Len>=Size)
    {
        for(int i=0;i<Size;i++) tmp+=S[i+1];
    }
    else
    {
        if(Left)
        {
            for(int i=0;i<Len;i++)  tmp+=S[i+1];
            for(int i=0;i<Size-Len;i++) tmp+=" ";
        }
        else
        {
            for(int i=0;i<Size-Len;i++) tmp+=" ";
            for(int i=0;i<Len;i++)  tmp+=S[i+1];
        }
    }
    return tmp;
}
//---------------------------------------------------------------------------
AnsiString spl_EmbHeaderToStr(spl_EmbHeader *pHeader)
{
    AnsiString tmp="";
    tmp="LA: " +spl_AlignStr(pHeader->Comments,15,true)+char(0x0D)+
        "ST: " +spl_AlignStr(IntToStr(pHeader->StitchsCount),6,false)+char(0x0D)+
        "CO: " +spl_AlignStr(IntToStr(pHeader->ColorStitchs),2,false)+char(0x0D)+
        "+X: " +spl_AlignStr(IntToStr(pHeader->right),4,false)+char(0x0D)+
        "-X: " +spl_AlignStr(IntToStr(pHeader->left),4,false)+char(0x0D)+
        "+Y: " +spl_AlignStr(IntToStr(pHeader->top),4,false)+char(0x0D)+
        "-Y: " +spl_AlignStr(IntToStr(pHeader->bottom),4,false)+char(0x0D)+
        "AX:+ "+spl_AlignStr(IntToStr(pHeader->AX),4,false)+char(0x0D)+
        "AY:+ "+spl_AlignStr(IntToStr(pHeader->AY),4,false)+char(0x0D)+
        "MX:+ "+spl_AlignStr(IntToStr(pHeader->MX),4,false)+char(0x0D)+
        "MY:+ "+spl_AlignStr(IntToStr(pHeader->MY),4,false)+char(0x0D)+
        "PD:******"+char(0x0D);
    tmp+=char(0x1A);
//    for(int i=0;i<512-125;i++)    tmp+=char(0x20);
    return tmp;
}
//---------------------------------------------------------------------------
#ifndef spl_Demo_Version
//---------------------------------------------------------------------------
//---------------------DST---------------------------------------------------
//---------------------------------------------------------------------------
void spl_DSTRecToStitch(spl_DSXRec *pDSXRec,spl_Stitch *pStitch)
{
    pStitch->x=0;
    pStitch->y=0;
    if(pDSXRec->Third & 8) // X= -81
        pStitch->x+=-81;
    if(pDSXRec->Second & 8) // X= -27
        pStitch->x+=-27;
    if(pDSXRec->First & 8) // X= -9
        pStitch->x+=-9;
    if(pDSXRec->Second & 2) // X= -3
        pStitch->x+=-3;
    if(pDSXRec->First & 2) // X= -1
        pStitch->x+=-1;
    if(pDSXRec->First & 1) // X= +1
        pStitch->x+=+1;
    if(pDSXRec->Second & 1) // X= +3
        pStitch->x+=+3;
    if(pDSXRec->First & 4) // X= +9
        pStitch->x+=+9;
    if(pDSXRec->Second & 4) // X= +27
        pStitch->x+=+27;
    if(pDSXRec->Third & 4) // X= +81
        pStitch->x+=+81;

    if(pDSXRec->Third & 16) // Y= -81
        pStitch->y+=-81;
    if(pDSXRec->Second & 16) // Y= -27
        pStitch->y+=-27;
    if(pDSXRec->First & 16) // Y= -9
        pStitch->y+=-9;
    if(pDSXRec->Second & 64) // Y= -3
        pStitch->y+=-3;
    if(pDSXRec->First & 64) // Y= -1
        pStitch->y+=-1;
    if(pDSXRec->First & 128) // Y= +1
        pStitch->y+=+1;
    if(pDSXRec->Second & 128) // Y= +3
        pStitch->y+=+3;
    if(pDSXRec->First & 32) // Y= +9
        pStitch->y+=+9;
    if(pDSXRec->Second & 32) // Y= +27
        pStitch->y+=+27;
    if(pDSXRec->Third & 32) // Y= +81
        pStitch->y+=+81;

    pStitch->type=spl_stNormal;
    if((pDSXRec->First==0x00)&&(pDSXRec->Second==0x00)&&(pDSXRec->Third==0xF3))
        pStitch->type=spl_stEof;
    else
    if((pDSXRec->Third & 128) && (pDSXRec->Third & 64))
        pStitch->type=spl_stColorChanged;
    else
    if(pDSXRec->Third & 128)
        pStitch->type=spl_stJump;
}
//---------------------------------------------------------------------------
static int Power3[5]={1,3,9,27,81};
static int Coff3[5];
//---------------------------------------------------------------------------
void spl_GetCoff3(int X)
{
    ZeroMemory(Coff3,5*sizeof(int));
    for(int i=4;i>=0;i--)
    {
        Coff3[i]=X/Power3[i];
        X-=Coff3[i]*Power3[i];
    }
}
//---------------------------------------------------------------------------
void spl_GetCoffDST(int X)
{
    int Y=abs(X);
    spl_GetCoff3(Y);
    int j;
    for(int i=0;i<5;i++)
    {
        if(Coff3[i]==2)
        {
            Coff3[i]=-1;
            Coff3[i+1]++;
        }
        if(Coff3[i]==3)
        {
            Coff3[i]=0;
            Coff3[i+1]++;
        }
    }
    if(X<0)
    {
        for(int i=0;i<5;i++)    Coff3[i]=-Coff3[i];
    }
}
//---------------------------------------------------------------------------
void spl_PointToDST(spl_Stitch *pStitch,spl_DSXRec *pDSXRec)
{
    pDSXRec->First=0;
    pDSXRec->Second=0;
    pDSXRec->Third=0;

    spl_GetCoffDST(pStitch->x);
    if(Coff3[0]==1)// +1
        spl_SetBit(pDSXRec->First,0);
    else
    if(Coff3[0]==-1)// -1
        spl_SetBit(pDSXRec->First,1);

    if(Coff3[1]==1)// +3
        spl_SetBit(pDSXRec->Second,0);
    else
    if(Coff3[1]==-1)// -3
        spl_SetBit(pDSXRec->Second,1);

    if(Coff3[2]==1)// +9
        spl_SetBit(pDSXRec->First,2);
    else
    if(Coff3[2]==-1)// -9
        spl_SetBit(pDSXRec->First,3);

    if(Coff3[3]==1)// +27
        spl_SetBit(pDSXRec->Second,2);
    else
    if(Coff3[3]==-1)// -27
        spl_SetBit(pDSXRec->Second,3);

    if(Coff3[4]==1)// +81
        spl_SetBit(pDSXRec->Third,2);
    else
    if(Coff3[4]==-1)// -81
        spl_SetBit(pDSXRec->Third,3);

    spl_GetCoffDST(pStitch->y);
    if(Coff3[0]==1)// +1
        spl_SetBit(pDSXRec->First,7);
    else
    if(Coff3[0]==-1)// -1
        spl_SetBit(pDSXRec->First,6);

    if(Coff3[1]==1)// +3
        spl_SetBit(pDSXRec->Second,7);
    else
    if(Coff3[1]==-1)// -3
        spl_SetBit(pDSXRec->Second,6);

    if(Coff3[2]==1)// +9
        spl_SetBit(pDSXRec->First,5);
    else
    if(Coff3[2]==-1)// -9
        spl_SetBit(pDSXRec->First,4);

    if(Coff3[3]==1)// +27
        spl_SetBit(pDSXRec->Second,5);
    else
    if(Coff3[3]==-1)// -27
        spl_SetBit(pDSXRec->Second,4);

    if(Coff3[4]==1)// +81
        spl_SetBit(pDSXRec->Third,5);
    else
    if(Coff3[4]==-1)// -81
        spl_SetBit(pDSXRec->Third,4);

    switch(pStitch->type)
    {
        case spl_stNormal:
        {
            spl_ClrBit(pDSXRec->Third,7);
            spl_ClrBit(pDSXRec->Third,6);
            break;
        }
        case spl_stJump:
        {
            spl_SetBit(pDSXRec->Third,7);
            spl_ClrBit(pDSXRec->Third,6);
            break;
        }
        case spl_stColorChanged:
        {
            spl_SetBit(pDSXRec->Third,7);
            spl_SetBit(pDSXRec->Third,6);
            break;
        }
        case spl_stEof:
        {
            pDSXRec->First=0x00;
            pDSXRec->Second=0x00;
            pDSXRec->Third=0xF3;
            return;
        }
    }
    spl_SetBit(pDSXRec->Third,0);
    spl_SetBit(pDSXRec->Third,1);
}
//---------------------------------------------------------------------------
//---------------------DSB---------------------------------------------------
//---------------------------------------------------------------------------
void spl_DSBRecToStitch(spl_DSXRec *pDSXRec,spl_Stitch *pStitch)
{
    pStitch->x=0;
    pStitch->y=0;
    if(pDSXRec->First & 64)
        pStitch->y+=-pDSXRec->Second;
    else
        pStitch->y+=+pDSXRec->Second;

    if(pDSXRec->First & 32)
        pStitch->x+=-pDSXRec->Third;
    else
        pStitch->x+=+pDSXRec->Third;

    pStitch->type=spl_stNormal;
    if((pDSXRec->First==0xF8)&&(pDSXRec->Second==0x00)&&(pDSXRec->Third==0x00))
        pStitch->type=spl_stEof;
    else
    if(pDSXRec->First & 8)
        pStitch->type=spl_stColorChanged;
    else
    if(pDSXRec->First & 1)
        pStitch->type=spl_stJump;
}
//---------------------------------------------------------------------------
void spl_PointToDSB(spl_Stitch *pStitch,spl_DSXRec *pDSXRec)
{
    pDSXRec->First=0;
    if(pStitch->y>=0)
    {
        spl_ClrBit(pDSXRec->First,6);
        pDSXRec->Second=pStitch->y;
    }
    else
    {
        spl_SetBit(pDSXRec->First,6);
        pDSXRec->Second=-pStitch->y;
    }

    if(pStitch->x>=0)
    {
        spl_ClrBit(pDSXRec->First,5);
        pDSXRec->Third=pStitch->x;
    }
    else
    {
        spl_SetBit(pDSXRec->First,5);
        pDSXRec->Third=-pStitch->x;
    }

    if(pStitch->type==spl_stEof)
    {
        pDSXRec->First=0xF8;
        pDSXRec->Second=0x00;
        pDSXRec->Third=0x00;
    }
    else
    if(pStitch->type==spl_stColorChanged)
        spl_SetBit(pDSXRec->First,3);
    else
    if(pStitch->type==spl_stJump)
        spl_SetBit(pDSXRec->First,0);
}
//---------------------------------------------------------------------------
//---------------------DSZ---------------------------------------------------
//---------------------------------------------------------------------------
void spl_DSZRecToStitch(spl_DSXRec *pDSXRec,spl_Stitch *pStitch)
{
    pStitch->x=0;
    pStitch->y=0;
    if(pDSXRec->Third & 32)
        pStitch->y+=-pDSXRec->First;
    else
        pStitch->y+=+pDSXRec->First;

    if(pDSXRec->Third & 64)
        pStitch->x+=-pDSXRec->Second;
    else
        pStitch->x+=+pDSXRec->Second;

    pStitch->type=spl_stNormal;
    if((pDSXRec->Third & 1)&&(pDSXRec->Third & 2))
        pStitch->type=spl_stColorChanged;
    else
    if(pDSXRec->Third & 1)
        pStitch->type=spl_stJump;
    else
    if((pDSXRec->First==0x00)&&(pDSXRec->Second==0x00)&&(pDSXRec->Third==0x91))
        pStitch->type=spl_stEof;
}
//---------------------------------------------------------------------------
void spl_PointToDSZ(spl_Stitch *pStitch,spl_DSXRec *pDSXRec)
{
    pDSXRec->Third=0;
    if(pStitch->x>=0)
    {
        spl_ClrBit(pDSXRec->Third,6);
        pDSXRec->Second=pStitch->x;
    }
    else
    {
        spl_SetBit(pDSXRec->Third,6);
        pDSXRec->Second=-pStitch->x;
    }

    if(pStitch->y>=0)
    {
        spl_ClrBit(pDSXRec->Third,5);
        pDSXRec->First=pStitch->y;
    }
    else
    {
        spl_SetBit(pDSXRec->Third,5);
        pDSXRec->First=-pStitch->y;
    }

    if(pStitch->type==spl_stEof)
    {
        pDSXRec->First=0x00;
        pDSXRec->Second=0x00;
        pDSXRec->Third=0x91;
    }
    else
    if(pStitch->type==spl_stColorChanged)
    {
        spl_SetBit(pDSXRec->Third,0);
        spl_SetBit(pDSXRec->Third,1);
    }
    else
    if(pStitch->type==spl_stJump)
        spl_SetBit(pDSXRec->Third,0);
}
//---------------------------------------------------------------------------
//---------------------KSM---------------------------------------------------
//---------------------------------------------------------------------------
void spl_KSMRecToStitch(spl_DSXRec *pDSXRec,spl_Stitch *pStitch)
{
    pStitch->x=0;
    pStitch->y=0;
    if(pDSXRec->Third & 32)
        pStitch->y+=-pDSXRec->First;
    else
        pStitch->y+=+pDSXRec->First;

    if(pDSXRec->Third & 64)
        pStitch->x+=-pDSXRec->Second;
    else
        pStitch->x+=+pDSXRec->Second;

    pStitch->type=spl_stNormal;
    if((pDSXRec->First==0x00)&&(pDSXRec->Second==0x00)&&(pDSXRec->Third==0x88))
        pStitch->type=spl_stEof;
    else
    if((pDSXRec->Third & 1)&&(pDSXRec->Third & 2)&&(pDSXRec->Third & 8)&&(pDSXRec->Third & 16))
        pStitch->type=spl_stColorChanged;
    else
    if(pDSXRec->Third & 1)
        pStitch->type=spl_stJump;
}
//---------------------------------------------------------------------------
void spl_PointToKSM(spl_Stitch *pStitch,spl_DSXRec *pDSXRec)
{
    pDSXRec->Third=0;
    if(pStitch->x>=0)
    {
        spl_ClrBit(pDSXRec->Third,6);
        pDSXRec->Second=pStitch->x;
    }
    else
    {
        spl_SetBit(pDSXRec->Third,6);
        pDSXRec->Second=-pStitch->x;
    }

    if(pStitch->y>=0)
    {
        spl_ClrBit(pDSXRec->Third,5);
        pDSXRec->First=pStitch->y;
    }
    else
    {
        spl_SetBit(pDSXRec->Third,5);
        pDSXRec->First=-pStitch->y;
    }

    if(pStitch->type==spl_stEof)
    {
        pDSXRec->First=0x00;
        pDSXRec->Second=0x00;
        pDSXRec->Third=0x88;
    }
    else
    if(pStitch->type==spl_stColorChanged)
    {
        spl_SetBit(pDSXRec->Third,0);
        spl_SetBit(pDSXRec->Third,1);
        spl_SetBit(pDSXRec->Third,2);
        spl_SetBit(pDSXRec->Third,3);
    }
    else
    if(pStitch->type==spl_stJump)
        spl_SetBit(pDSXRec->Third,0);
}
//---------------------------------------------------------------------------
void spl_Load_DSX_From_Stream(char X,TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar)
{
    StitchPath.erase(StitchPath.begin(),StitchPath.end());
    int Length;
    int Count;
    int D;
    AnsiString HeaderStr;
    char c;
    int ic;
    spl_DSXRec DSXRec;
    spl_SInt x;
    spl_SInt y;
    spl_Stitch Stitch;

    pStream->Position=0;
    Length=pStream->Size;
    if(Length<512)  goto LEnd;
    Count=(Length-512)/3;

    // Read DSX Comment
    HeaderStr="";
    c=' ';
    ic=0;
    pStream->Read(pHeader->Comments,3);
    while((c!='\0')&&(ic<13))
    {
        HeaderStr+=c;
        pStream->Read(&c,1);
        ic++;
    }
    ZeroMemory(pHeader->Comments,13);
    strcpy(pHeader->Comments,HeaderStr.c_str());
    
    // Read Colors
    pStream->Position=125;
    pStream->Read(pHeader->Colors,spl_MaxColorsCount*sizeof(spl_RGB));
    if(Count<=0)    goto LEnd;

    // Read DSX Stitchs
    D=Count/50+1;
    if(pProgressBar)
    {
        pProgressBar->Min=0;
        pProgressBar->Max=50;
        pProgressBar->Step=D;
        pProgressBar->Position=0;
    }
    pStream->Position=512;

    pHeader->left=spl_MaxWord;
    pHeader->top=spl_MaxWord;
    pHeader->right=-spl_MaxWord;
    pHeader->bottom=-spl_MaxWord;
    pHeader->NormalStitchs=0;
    pHeader->JumpStitchs=0;
    pHeader->ColorStitchs=1;
    x=0;
    y=0;
    for(int i=0;i<Count;i++)
    {
        if(pProgressBar)
        {
            if(i % D==0)    pProgressBar->Position++;
        }

        pStream->Read(&DSXRec,sizeof(DSXRec));
        switch(X)
        {
            case 't':
            case 'T':
            {
                spl_DSTRecToStitch(&DSXRec,&Stitch);
                break;
            }
            case 'b':
            case 'B':
            {
                spl_DSBRecToStitch(&DSXRec,&Stitch);
                break;
            }
            case 'z':
            case 'Z':
            {
                spl_DSZRecToStitch(&DSXRec,&Stitch);
                break;
            }
            case 'm':
            case 'M':
            {
                spl_KSMRecToStitch(&DSXRec,&Stitch);
                break;
            }
        }
        StitchPath.push_back(Stitch);
        x+=Stitch.x;
        y+=Stitch.y;

        if(x<pHeader->left)
            pHeader->left=x;
        if(y<pHeader->top)
            pHeader->top=y;
        if(x>pHeader->right)
            pHeader->right=x;
        if(y>pHeader->bottom)
            pHeader->bottom=y;

        if(Stitch.type==spl_stNormal)
            pHeader->NormalStitchs++;
        else
        if(Stitch.type==spl_stJump)
            pHeader->JumpStitchs++;
        else
        if(Stitch.type==spl_stColorChanged)
            pHeader->ColorStitchs++;
    }
    pHeader->AX=StitchPath[0].x;
    pHeader->AY=StitchPath[0].y;

    pHeader->MX=x;
    pHeader->MY=y;

    LEnd:;

    // Test Colors
    spl_RGB Color,PrevColor;
    PrevColor=pHeader->Colors[0];
    for(UINT i=1;i<pHeader->ColorStitchs;i++)
    {
        Color=pHeader->Colors[i];
        if(Color==PrevColor)
        {
            for(int j=0;j<spl_MaxTajimaColors;j++)
            {
                pHeader->Colors[j].r=GetRValue(spl_TajimaColors[j]);
                pHeader->Colors[j].g=GetGValue(spl_TajimaColors[j]);
                pHeader->Colors[j].b=GetBValue(spl_TajimaColors[j]);
            }
            break;
        }
        PrevColor=Color;
    }

    pHeader->StitchsCount=Count;
    if(pProgressBar)    pProgressBar->Position=0;
}
//---------------------------------------------------------------------------
void spl_Save_DSX_To_Stream(char X,TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar)
{
    if(!pStream)    return;
    AnsiString HeaderStr;
    int D;
    spl_DSXRec DSXRec;
    spl_Stitch Stitch;

    // Write DSX Header
    HeaderStr=spl_EmbHeaderToStr(pHeader);
    pStream->Position=0;
    pStream->Write(HeaderStr.c_str(),HeaderStr.Length());
    // Write Colors
    pStream->Write(pHeader->Colors,spl_MaxColorsCount*sizeof(spl_RGB));

    // Write DSX Stitchs
    D=pHeader->StitchsCount/50+1;
    if(pProgressBar)
    {
        pProgressBar->Min=0;
        pProgressBar->Max=50;
        pProgressBar->Step=D;
        pProgressBar->Position=0;
    }

    pStream->Position=512;
    for(UINT i=0;i<StitchPath.size();i++)
    {
        if(pProgressBar)
        {
            if(i % D==0)    pProgressBar->Position++;
        }

        Stitch=StitchPath[i];
        switch(X)
        {
            case 't':
            case 'T':
            {
                spl_PointToDST(&Stitch,&DSXRec);
                break;
            }
            case 'b':
            case 'B':
            {
                spl_PointToDSB(&Stitch,&DSXRec);
                break;
            }
            case 'z':
            case 'Z':
            {
                spl_PointToDSZ(&Stitch,&DSXRec);
                break;
            }
            case 'm':
            case 'M':
            {
                spl_PointToKSM(&Stitch,&DSXRec);
                break;
            }
        }
        pStream->Write(&DSXRec,sizeof(DSXRec));
    }
    if(pProgressBar)    pProgressBar->Position=0;
}
//---------------------------------------------------------------------------
//---------------------EXP---------------------------------------------------
//---------------------------------------------------------------------------
void spl_Load_EXP_From_Stream(TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar)
{
    StitchPath.erase(StitchPath.begin(),StitchPath.end());
    int Length;
    int Count;
    int D;
    Byte *Data;
    spl_SInt x;
    spl_SInt y;
    spl_Stitch Stitch;

    pStream->Position=0;
    Length=pStream->Size;
    if(Length<2)    goto LEnd;
    Count=Length/2;
    Length=2*Count;

    // Header
    ZeroMemory(pHeader->Comments,13);
    strcpy(pHeader->Comments,spl_Comments);

    D=Count/50+1;
    if(pProgressBar)
    {
        pProgressBar->Min=0;
        pProgressBar->Max=50;
        pProgressBar->Step=D;
        pProgressBar->Position=0;
    }

    pHeader->NormalStitchs=0;
    pHeader->JumpStitchs=0;
    pHeader->ColorStitchs=1;
    pHeader->left=spl_MaxWord;
    pHeader->top=spl_MaxWord;
    pHeader->right=-spl_MaxWord;
    pHeader->bottom=-spl_MaxWord;
    Data=(Byte *)pStream->Memory;
    x=0;
    y=0;
    for(int i=0;i<Length;)
    {
        if(pProgressBar)
        {
            if(i % D==0)    pProgressBar->Position++;
        }

        // Color Changes
        if((Data[i]==0x80)&&(Data[i+1]==0x01))
        {
            i+=2;

            Stitch.x=spl_ByteToComp(Data[i]);
            Stitch.y=spl_ByteToComp(Data[i+1]);
            Stitch.type=spl_stColorChanged;

            i+=2;
        }
        else
        // Jump Record
        if(((Data[i]==0x80)&&(Data[i+1]==0x02))||
           ((Data[i]==0x80)&&(Data[i+1]==0x04)))
        {
            i+=2;

            Stitch.x=spl_ByteToComp(Data[i]);
            Stitch.y=spl_ByteToComp(Data[i+1]);
            Stitch.type=spl_stJump;

            i+=2;
        }
        else
        {
            Stitch.x=spl_ByteToComp(Data[i]);
            Stitch.y=spl_ByteToComp(Data[i+1]);
            Stitch.type=spl_stNormal;

            i+=2;
        }
        StitchPath.push_back(Stitch);
        x+=Stitch.x;
        y+=Stitch.y;

        if(x<pHeader->left)
            pHeader->left=x;
        if(y<pHeader->top)
            pHeader->top=y;
        if(x>pHeader->right)
            pHeader->right=x;
        if(y>pHeader->bottom)
            pHeader->bottom=y;

        if(Stitch.type==spl_stNormal)
            pHeader->NormalStitchs++;
        else
        if(Stitch.type==spl_stJump)
            pHeader->JumpStitchs++;
        else
        if(Stitch.type==spl_stColorChanged)
            pHeader->ColorStitchs++;
    }
    pHeader->AX=StitchPath[0].x;
    pHeader->AY=StitchPath[0].y;

    pHeader->MX=x;
    pHeader->MY=y;

    LEnd:;

    // Test Colors
    spl_RGB Color,PrevColor;
    PrevColor=pHeader->Colors[0];
    for(UINT i=1;i<pHeader->ColorStitchs;i++)
    {
        Color=pHeader->Colors[i];
        if(Color==PrevColor)
        {
            for(int j=0;j<spl_MaxTajimaColors;j++)
            {
                pHeader->Colors[j].r=GetRValue(spl_TajimaColors[j]);
                pHeader->Colors[j].g=GetGValue(spl_TajimaColors[j]);
                pHeader->Colors[j].b=GetBValue(spl_TajimaColors[j]);
            }
            break;
        }
        PrevColor=Color;
    }

    pHeader->StitchsCount=Count;
    if(pProgressBar)    pProgressBar->Position=0;
}
//---------------------------------------------------------------------------
void spl_Save_EXP_To_Stream(TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar)
{
    int D;
    spl_UByte b;
    spl_UWord w;
    spl_Stitch Stitch;

    if(!pStream)    return;

    D=pHeader->StitchsCount/50+1;
    if(pProgressBar)
    {
        pProgressBar->Min=0;
        pProgressBar->Max=50;
        pProgressBar->Step=D;
        pProgressBar->Position=0;
    }

    pStream->Position=0;
    for(UINT i=0;i<StitchPath.size();i++)
    {
        if(pProgressBar)
        {
            if(i % D==0)    pProgressBar->Position++;
        }

        Stitch=StitchPath[i];
        switch(Stitch.type)
        {
            case spl_stColorChanged:
            {
                w=0x0180;
                pStream->Write(&w,2);
                break;
            }
            case spl_stJump:
            {
                w=0x0280;
                pStream->Write(&w,2);
                break;
            }
        }
        b=spl_CompToByte(Stitch.x);
        pStream->Write(&b,1);
        b=spl_CompToByte(Stitch.y);
        pStream->Write(&b,1);
    }
    if(pProgressBar)    pProgressBar->Position=0;
}
#endif
//---------------------------------------------------------------------------
//---------------------ALI---------------------------------------------------
//---------------------------------------------------------------------------
void spl_Load_ALI_From_Stream(TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar)
{
    StitchPath.erase(StitchPath.begin(),StitchPath.end());
    int Length;
    int Count;
    int D;
    AnsiString HeaderStr;
    char c;
    int ic;
    spl_SInt x;
    spl_SInt y;
    spl_Stitch Stitch;
    spl_DSXRec DSXRec;

    pStream->Position=0;
    Length=pStream->Size;
    if(Length<512)  goto LEnd;
    Count=(Length-512)/3;

    // Read DSX Comment
    HeaderStr="";
    c=' ';
    ic=0;
    pStream->Read(pHeader->Comments,3);
    while((c!='\0')&&(ic<13))
    {
        HeaderStr+=c;
        pStream->Read(&c,1);
        ic++;
    }
    ZeroMemory(pHeader->Comments,13);
    strcpy(pHeader->Comments,HeaderStr.c_str());
    
    // Read Colors
    pStream->Position=125;
    pStream->Read(pHeader->Colors,spl_MaxColorsCount*sizeof(spl_RGB));
    if(Count<=0)    goto LEnd;

    // Read DSX Stitchs
    D=Count/50+1;
    if(pProgressBar)
    {
        pProgressBar->Min=0;
        pProgressBar->Max=50;
        pProgressBar->Step=D;
        pProgressBar->Position=0;
    }
    pStream->Position=512;

    pHeader->left=spl_MaxWord;
    pHeader->top=spl_MaxWord;
    pHeader->right=-spl_MaxWord;
    pHeader->bottom=-spl_MaxWord;
    pHeader->NormalStitchs=0;
    pHeader->JumpStitchs=0;
    pHeader->ColorStitchs=1;
    x=0;
    y=0;
    for(int i=0;i<Count;i++)
    {
        if(pProgressBar)
        {
            if(i % D==0)    pProgressBar->Position++;
        }

        pStream->Read(&DSXRec,sizeof(DSXRec));
        Stitch=DSXRecToStitch(DSXRec);
        StitchPath.push_back(Stitch);
        x+=Stitch.x;
        y+=Stitch.y;

        if(x<pHeader->left)
            pHeader->left=x;
        if(y<pHeader->top)
            pHeader->top=y;
        if(x>pHeader->right)
            pHeader->right=x;
        if(y>pHeader->bottom)
            pHeader->bottom=y;

        if(Stitch.type==spl_stNormal)
            pHeader->NormalStitchs++;
        else
        if(Stitch.type==spl_stJump)
            pHeader->JumpStitchs++;
        else
        if(Stitch.type==spl_stColorChanged)
            pHeader->ColorStitchs++;
    }
    pHeader->AX=StitchPath[0].x;
    pHeader->AY=StitchPath[0].y;

    pHeader->MX=x;
    pHeader->MY=y;

    LEnd:;

    // Test Colors
    spl_RGB Color,PrevColor;
    PrevColor=pHeader->Colors[0];
    for(UINT i=1;i<pHeader->ColorStitchs;i++)
    {
        Color=pHeader->Colors[i];
        if(Color==PrevColor)
        {
            for(int j=0;j<spl_MaxTajimaColors;j++)
            {
                pHeader->Colors[j].r=GetRValue(spl_TajimaColors[j]);
                pHeader->Colors[j].g=GetGValue(spl_TajimaColors[j]);
                pHeader->Colors[j].b=GetBValue(spl_TajimaColors[j]);
            }
            break;
        }
        PrevColor=Color;
    }

    pHeader->StitchsCount=Count;
    if(pProgressBar)    pProgressBar->Position=0;
}
//---------------------------------------------------------------------------
void spl_Save_ALI_To_Stream(TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar)
{
    if(!pStream)    return;
    AnsiString HeaderStr;
    int D;
    spl_DSXRec DSXRec;

    // Write DSX Header
    HeaderStr=spl_EmbHeaderToStr(pHeader);
    pStream->Position=0;
    pStream->Write(HeaderStr.c_str(),HeaderStr.Length());
    // Write Colors
    pStream->Write(pHeader->Colors,spl_MaxColorsCount*sizeof(spl_RGB));

    // Write DSX Stitchs
    D=pHeader->StitchsCount/50+1;
    if(pProgressBar)
    {
        pProgressBar->Min=0;
        pProgressBar->Max=50;
        pProgressBar->Step=D;
        pProgressBar->Position=0;
    }

    pStream->Position=512;
    for(UINT i=0;i<StitchPath.size();i++)
    {
        if(pProgressBar)
        {
            if(i % D==0)    pProgressBar->Position++;
        }

        DSXRec=StitchToDSXRec(StitchPath[i]);
        pStream->Write(&DSXRec,sizeof(DSXRec));
    }
    if(pProgressBar)    pProgressBar->Position=0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void spl_LoadEmbFromStream(TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar)
{
#ifndef spl_Demo_Version
    if(UpperCase(FileName).Pos(".DST")>0)
        spl_Load_DSX_From_Stream('T',pStream,FileName,StitchPath,pHeader,pProgressBar);
    else
    if(UpperCase(FileName).Pos(".EXP")>0)
        spl_Load_EXP_From_Stream(pStream,FileName,StitchPath,pHeader,pProgressBar);
    else
    if(UpperCase(FileName).Pos(".DSZ")>0)
        spl_Load_DSX_From_Stream('Z',pStream,FileName,StitchPath,pHeader,pProgressBar);
    else
    if(UpperCase(FileName).Pos(".DSB")>0)
        spl_Load_DSX_From_Stream('B',pStream,FileName,StitchPath,pHeader,pProgressBar);
    else
    if(UpperCase(FileName).Pos(".KSM")>0)
        spl_Load_DSX_From_Stream('M',pStream,FileName,StitchPath,pHeader,pProgressBar);
    else
#endif
    if(UpperCase(FileName).Pos(".ALI")>0)
    {
        spl_EncodeStream(spl_ALI_KEY,pStream,true);
        spl_Load_ALI_From_Stream(pStream,FileName,StitchPath,pHeader,pProgressBar);
    }
}
//---------------------------------------------------------------------------
void spl_LoadEmbFromFile(AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar)
{
    TMemoryStream *pStream=NULL;
    pStream=new TMemoryStream();
    pStream->LoadFromFile(FileName);
    spl_LoadEmbFromStream(pStream,FileName,StitchPath,pHeader,pProgressBar);
    if(pStream)    delete pStream;pStream=NULL;
}
//---------------------------------------------------------------------------
void spl_SaveEmbToStream(TMemoryStream *pStream,AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar)
{
#ifndef spl_Demo_Version
    if(UpperCase(FileName).Pos(".DST")>0)
        spl_Save_DSX_To_Stream('T',pStream,FileName,StitchPath,pHeader,pProgressBar);
    else
    if(UpperCase(FileName).Pos(".EXP")>0)
        spl_Save_EXP_To_Stream(pStream,FileName,StitchPath,pHeader,pProgressBar);
    else
    if(UpperCase(FileName).Pos(".DSZ")>0)
        spl_Save_DSX_To_Stream('Z',pStream,FileName,StitchPath,pHeader,pProgressBar);
    else
    if(UpperCase(FileName).Pos(".DSB")>0)
        spl_Save_DSX_To_Stream('B',pStream,FileName,StitchPath,pHeader,pProgressBar);
    else
    if(UpperCase(FileName).Pos(".KSM")>0)
        spl_Save_DSX_To_Stream('M',pStream,FileName,StitchPath,pHeader,pProgressBar);
    else
#endif
    if(UpperCase(FileName).Pos(".ALI")>0)
    {
        spl_Save_ALI_To_Stream(pStream,FileName,StitchPath,pHeader,pProgressBar);
        spl_EncodeStream(spl_ALI_KEY,pStream,true);
    }
}
//---------------------------------------------------------------------------
void spl_SaveEmbToFile(AnsiString FileName,spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,TProgressBar *pProgressBar)
{
    TMemoryStream *pStream=NULL;
    pStream=new TMemoryStream();
    spl_SaveEmbToStream(pStream,FileName,StitchPath,pHeader,pProgressBar);
    pStream->SaveToFile(FileName);
    if(pStream)    delete pStream;pStream=NULL;
}
//---------------------------------------------------------------------------
void spl_StitchStretchDraw(spl_StitchPath &StitchPath,spl_EmbHeader *pHeader,Graphics::TBitmap *pBMP,TRect &R,int Margin,bool ShowJumps,bool Stretch,bool Real)
{
    spl_UByte LastStitch;
    spl_Stitch Stitch;
    bool IsFirstNormal;
    bool IsPrevJump;
    int ColorIndex;
    double Ax,Bx;
    double Ay,By;
    double x,y;
    double nx,ny;
    TRect F=Rect(pHeader->left,pHeader->top,pHeader->right,pHeader->bottom);
    double FW,FH;
    FW=F.Width();
    FH=F.Height();
    if((FW<=0)||(FH<=0))    return;
    int H=R.Height();
    spl_RGB Color;
    if(pHeader->ColorStitchs>spl_MaxTajimaColors)	return;// Bug 11.05.2004
    int ColorsCount=spl_MAX(pHeader->ColorStitchs,spl_MaxTajimaColors);

    TBrush *pTempBrush=new TBrush();
    pTempBrush->Assign(pBMP->Canvas->Brush);
    TPen *pTempPen=new TPen();
    pTempPen->Assign(pBMP->Canvas->Pen);

    if(Stretch)
    {
        Ax=double(R.Width()-2.0*Margin)/FW;
        Bx=Margin+R.Left-Ax*F.Left;
        Ay=double(R.Height()-2.0*Margin)/FH;
        By=Margin+R.Top-Ay*F.Top;
    }
    else
    {
        double L=min(R.Width(),R.Height())-2.0*Margin;

        Ax=L/FW;
        Ay=L/FH;
        Bx=(pBMP->Width-L)/2.0+R.Left-Ax*F.Left;
        By=(pBMP->Height-L)/2.0+R.Top-Ay*F.Top;
    }

    IsFirstNormal=true;
    LastStitch=spl_stJump;
    ColorIndex=0;
    if(Real)
    {
        pBMP->Canvas->Pen->Width=2;
        ShowJumps=false;
    }
    else
        pBMP->Canvas->Pen->Width=1;
    Color=pHeader->Colors[ColorIndex];
    pBMP->Canvas->Pen->Color=(TColor)RGB(Color.r,Color.g,Color.b);

    pBMP->Canvas->Brush->Style=bsClear;
    pBMP->Canvas->Pen->Style=psDot;
    ColorIndex++;
    x=0.0;
    y=0.0;
    for(spl_UInt i=0;i<StitchPath.size();i++)
    {
        Stitch=StitchPath[i];
        x+=Stitch.x;
        y+=Stitch.y;
        nx=Ax*x+Bx;
        ny=H-1-(Ay*y+By);
        if(Stitch.type==spl_stNormal)
        {
            if(IsFirstNormal)
                pBMP->Canvas->MoveTo(nx,ny);
            else
            {
                if(ShowJumps)
                {
                    if(IsPrevJump)
                    {
                        pBMP->Canvas->LineTo(nx,ny);
                        pBMP->Canvas->Pen->Style=psDot;
                    }
                    else
                    {
                        pBMP->Canvas->LineTo(nx,ny);
                        pBMP->Canvas->Pen->Style=psSolid;
                    }
                }
                else
                {
                    if(IsPrevJump)
                    {
                        pBMP->Canvas->MoveTo(nx,ny);
                        pBMP->Canvas->Pen->Style=psDot;
                    }
                    else
                    {
                        pBMP->Canvas->LineTo(nx,ny);
                        pBMP->Canvas->Pen->Style=psSolid;
                    }
                }
            }
            LastStitch=spl_stNormal;
            IsFirstNormal=false;
            IsPrevJump=false;
        }
        else
        if(Stitch.type==spl_stJump)
        {
            if(!ShowJumps)
                pBMP->Canvas->MoveTo(nx,ny);
            pBMP->Canvas->Pen->Style=psDot;
            IsPrevJump=true;
            LastStitch=spl_stJump;
        }
        else
        if(Stitch.type==spl_stColorChanged)
        {
            if(LastStitch==spl_stNormal)
            {
                if((ColorIndex >= 0) && (ColorIndex<ColorsCount))
                {
                    Color=pHeader->Colors[ColorIndex];
                    pBMP->Canvas->Pen->Color=(TColor)RGB(Color.r,Color.g,Color.b);
                }
                else
                    pBMP->Canvas->Pen->Color=(TColor)RGB(random(255),random(255),random(255));
                ColorIndex++;
            }
            LastStitch=spl_stColorChanged;
            IsPrevJump=false;
        }
    }

    pBMP->Canvas->Brush->Assign(pTempBrush);
    if(pTempBrush) delete  pTempBrush;
    pBMP->Canvas->Pen->Assign(pTempPen);
    if(pTempPen)   delete  pTempPen;
}
//---------------------------------------------------------------------------
void spl_ConvertStitchPathToGlobalStitchPath(spl_StitchPath &StitchPath,spl_GlobalStitchPath &GlobalStitchPath)
{
    if(StitchPath.empty())  return;
    GlobalStitchPath.erase(GlobalStitchPath.begin(),GlobalStitchPath.end());

    spl_Stitch Stitch;
    spl_GlobalStitch GlobalStitch;

    GlobalStitch.x=0;
    GlobalStitch.y=0;
    for(spl_UInt i=0;i<StitchPath.size();i++)
    {
        Stitch=StitchPath[i];
        GlobalStitch.x+=Stitch.x;
        GlobalStitch.y+=Stitch.y;
        GlobalStitch.type=Stitch.type;
        GlobalStitchPath.push_back(GlobalStitch);
    }
}
//---------------------------------------------------------------------------
void spl_ConvertGlobalStitchPathToStitchPath(spl_GlobalStitchPath &GlobalStitchPath,spl_StitchPath &StitchPath)
{
    if(GlobalStitchPath.empty())  return;
    StitchPath.erase(StitchPath.begin(),StitchPath.end());

    spl_GlobalStitch GlobalStitch;
    spl_Stitch Stitch;
    spl_Point P,OP;
    spl_Point p,op;
    double L;
    spl_Point K;

    OP.x=GlobalStitchPath[0].x;
    OP.y=GlobalStitchPath[0].y;
    op=OP;
    for(spl_UInt i=0;i<GlobalStitchPath.size();i++)
    {
        GlobalStitch=GlobalStitchPath[i];
        P.x=GlobalStitch.x;
        P.y=GlobalStitch.y;

        L=spl_PDistance(&OP,&P);
        if(L>spl_MaxStitchLength)
        {
            K.x=(P.x-OP.x)/L;
            K.y=(P.y-OP.y)/L;
            for(double t=spl_MaxStitchLength;t<L;t+=spl_MaxStitchLength)
            {
                p.x=OP.x+t*K.x;
                p.y=OP.y+t*K.y;

                Stitch.x=p.x-op.x;
                Stitch.y=p.y-op.y;
                Stitch.type=GlobalStitch.type;
                StitchPath.push_back(Stitch);
                op.x+=Stitch.x;
                op.y+=Stitch.y;
            }
        }

        // Last Point
        Stitch.x=P.x-op.x;
        Stitch.y=P.y-op.y;
        Stitch.type=GlobalStitch.type;
        StitchPath.push_back(Stitch);
        op.x+=Stitch.x;
        op.y+=Stitch.y;

        OP=P;
    }
}
//---------------------------------------------------------------------------

