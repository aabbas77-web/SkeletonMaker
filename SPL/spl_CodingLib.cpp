//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_CodingLib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
static int _Num=0;
static int _Max=0;
static int _Max2=0;
static int _Counter=0;
static int _Hash=0;
//---------------------------------------------------------------------------
bool spl_EncodeBuffer(Byte Key,Byte *pBuffer,int Size,bool FirstBlock)
{
    if(FirstBlock)
    {
        _Max=256;
        _Max2=_Max/2;
        if((Key==0)||(Key==_Max2)||(Key==_Max-1))
            _Num=(_Max2*(~Key)+(_Max/3) | _Max2) % _Max;
        else
            _Num=Key % _Max;
        _Counter=0;
        _Hash=_Max;
    }
    for(int i=0;i<Size;i++)
    {
        _Counter+=_Num % _Max2;
        _Hash=_Hash ^ _Counter ^ _Num;
        _Num=(_Num+_Hash+_Counter) % _Max;
        pBuffer[i]=pBuffer[i] ^ _Num;
    }
    return true;
}
//---------------------------------------------------------------------------
bool spl_EncodeStream(Byte Key,TMemoryStream *pSource,bool FirstBlock)
{
    return spl_EncodeBuffer(Key,(Byte *)pSource->Memory,pSource->Size,FirstBlock);
}
//---------------------------------------------------------------------------
bool spl_EncodeFile(Byte Key,AnsiString InFile,AnsiString OutFile)
{
    bool Result;
    TMemoryStream *pStream=new TMemoryStream();
    pStream->LoadFromFile(InFile);
    Result=spl_EncodeStream(Key,pStream,true);
    pStream->SaveToFile(OutFile);
    if(pStream) delete pStream;
    return Result;
}
//---------------------------------------------------------------------------

