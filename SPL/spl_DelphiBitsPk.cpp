//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("spl_DelphiBitsPk.res");
USEPACKAGE("vcl50.bpi");
USEUNIT("spl_DelphiBits.pas");
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
    return 1;
}
//---------------------------------------------------------------------------
