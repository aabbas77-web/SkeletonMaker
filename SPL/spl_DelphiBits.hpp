// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'spl_DelphiBits.pas' rev: 5.00

#ifndef spl_DelphiBitsHPP
#define spl_DelphiBitsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Spl_delphibits
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EBitsError;
class PASCALIMPLEMENTATION EBitsError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EBitsError(const AnsiString Msg) : Sysutils::Exception(Msg
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EBitsError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EBitsError(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EBitsError(int Ident, const System::TVarRec * Args, 
		const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EBitsError(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(
		Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EBitsError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EBitsError(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EBitsError(System::PResStringRec ResStringRec, const 
		System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EBitsError(void) { }
	#pragma option pop
	
};


class DELPHICLASS spl_BitsArray;
class PASCALIMPLEMENTATION spl_BitsArray : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int FSize;
	void *FBits;
	void __fastcall Error(void);
	void __fastcall SetSize(int Value);
	void __fastcall SetBit(int Index, bool Value);
	bool __fastcall GetBit(int Index);
	void * __fastcall GetBuffer(void);
	int __fastcall GetBufferSize(void);
	
public:
	__fastcall virtual ~spl_BitsArray(void);
	int __fastcall OpenBit(void);
	__property bool Bits[int Index] = {read=GetBit, write=SetBit/*, default*/};
	__property int Size = {read=FSize, write=SetSize, nodefault};
	__property void * Buffer = {read=GetBuffer};
	__property int BufferSize = {read=GetBufferSize, nodefault};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall spl_BitsArray(void) : System::TObject() { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Spl_delphibits */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Spl_delphibits;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// spl_DelphiBits
