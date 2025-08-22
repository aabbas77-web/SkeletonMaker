//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "cad_Strings.h"
#include "api_VecApi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//  Overwrite VeCAD strings
//  Used to localize VeCAD to other languages
//-------------------------------------------------------------------
int LoadString(int Id)
{
    char* str=NULL;
    int res=1;
    // assign new string according to string's identifier
    switch(Id)
    {
        case VS_PRINT_TITLE:
        {
            str="Print2";
            break;
        }
        case VS_ENTPROP_TITLE:
        {
            str="Objects properties 2";
            break;
        }
        case VS_LINE_TITLE:
        {
            str="Line2";
            break;
        }
        default:
        {
            res=0;  // string was not overwritten
            break;
        }
    }
    // pass new string to VeCAD
    if(res==1)
    {
        vlPropPut(VD_MSG_STRING,0,str);
    }
    return res;
}
//---------------------------------------------------------------------------
