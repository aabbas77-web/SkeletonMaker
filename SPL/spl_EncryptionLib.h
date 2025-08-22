//---------------------------------------------------------------------------
#ifndef spl_EncryptionLibH
#define spl_EncryptionLibH
//---------------------------------------------------------------------------
bool spl_EncryptBuffer(Byte *pbBuffer,DWORD dwBufferLen,AnsiString Password,bool LastBlock);
bool spl_EncryptStream(TMemoryStream *pSource,AnsiString Password,bool LastBlock);
bool spl_EncryptFile(AnsiString Source,AnsiString Destination,AnsiString Password);
//---------------------------------------------------------------------------
#endif
