//---------------------------------------------------------------------------
#ifndef spl_BitsH
#define spl_BitsH
//---------------------------------------------------------------------------
#include "spl_DelphiBits.hpp"
//---------------------------------------------------------------------------
class spl_Bits: public spl_BitsArray
{
private:

public:
    __fastcall spl_Bits();
    __fastcall ~spl_Bits();
    void Write(int Index,BYTE BitsCount,UINT64 Value);
    UINT64 Read(int Index,BYTE BitsCount);
};
//---------------------------------------------------------------------------
#endif
