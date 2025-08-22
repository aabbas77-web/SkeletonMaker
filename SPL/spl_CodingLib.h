//---------------------------------------------------------------------------
// Unit:    CodingLib.cpp
// Classes: (None)
// Purpose: Define Encoding Functions (High Encoding Methode), With Key.
// Company: AliSoft
// Address: www.AliSoft.com
// Author:  Ali Abbas
// E-Mail:  a.abbas@netcourrier.com
// Cr-Date: 25/10/2002
// la-Date: 28/10/2002
//---------------------------------------------------------------------------
#ifndef spl_CodingLibH
#define spl_CodingLibH
//---------------------------------------------------------------------------
// Encoding Buffer Function
bool spl_EncodeBuffer(Byte Key,Byte *pBuffer,int Size,bool FirstBlock);
//---------------------------------------------------------------------------
bool spl_EncodeStream(Byte Key,TMemoryStream *pSource,bool FirstBlock);
//---------------------------------------------------------------------------
// Encoding File Function
bool spl_EncodeFile(Byte Key,AnsiString InFile,AnsiString OutFile);
//---------------------------------------------------------------------------
#endif
