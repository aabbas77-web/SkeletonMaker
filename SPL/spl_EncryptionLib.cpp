//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <wincrypt.h>
#include <stdlib.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "spl_EncryptionLib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#ifdef USE_BLOCK_CIPHER
    // defines for RC2 block cipher
    #define ENCRYPT_ALGORITHM	CALG_RC2
    #define ENCRYPT_BLOCK_SIZE	8
#else
    // defines for RC4 stream cipher
    #define ENCRYPT_ALGORITHM	CALG_RC4
    #define ENCRYPT_BLOCK_SIZE	1
#endif
//---------------------------------------------------------------------------
void Error(AnsiString Text,int Code)
{
 MessageDlg((FormatFloat(Text,Code)).c_str(),mtError,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
bool spl_EncryptBuffer(Byte *pbBuffer,DWORD dwBufferLen,AnsiString Password,bool LastBlock)
{
    HCRYPTPROV hProv   = 0;
    HCRYPTKEY hKey     = 0;
    HCRYPTKEY hXchgKey = 0;
    HCRYPTHASH hHash   = 0;

    PBYTE pbKeyBlob = NULL;
    DWORD dwKeyBlobLen;

    DWORD dwCount;

    BOOL status = FALSE;

    // Get handle to the default provider.
    if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)) {
        Error("Error 0 during CryptAcquireContext!\n", GetLastError());
        goto done;
    }

	// Encrypt the file with a session key derived from a password.

	// Create a hash object.
	if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
	    Error("Error 0 during CryptCreateHash!\n", GetLastError());
	    goto done;
	}

	// Hash in the password data.
	if(!CryptHashData(hHash, Password.c_str(), strlen(Password.c_str()), 0)) {
	    Error("Error 0 during CryptHashData!\n", GetLastError());
	    goto done;
	}

	// Derive a session key from the hash object.
	if(!CryptDeriveKey(hProv, CALG_RC4, hHash, 0, &hKey)) {
	    Error("Error 0 during CryptDeriveKey!\n", GetLastError());
	    goto done;
	}

	// Destroy the hash object.
	CryptDestroyHash(hHash);
	hHash = 0;

    // Encrypt source file and write to Source file.
    // Encrypt data
	if(!CryptEncrypt(hKey, 0, LastBlock, 0, pbBuffer, &dwBufferLen, dwBufferLen)) {
            Error("bytes required:0\n",dwCount);
            Error("Error 0 during CryptEncrypt!\n", GetLastError());
            goto done;
        }

    status = TRUE;

    done:

    // Free memory.
    if(pbKeyBlob) free(pbKeyBlob);
    if(pbBuffer) free(pbBuffer);

    // Destroy session key.
    if(hKey) CryptDestroyKey(hKey);

    // Release key exchange key handle.
    if(hXchgKey) CryptDestroyKey(hXchgKey);

    // Destroy hash object.
    if(hHash) CryptDestroyHash(hHash);

    // Release provider handle.
    if(hProv) CryptReleaseContext(hProv, 0);

    return(status);
}
//---------------------------------------------------------------------------
bool spl_EncryptFile(AnsiString Source,AnsiString Destination,AnsiString Password)
{
    FILE *hSource      = NULL;
    FILE *hDestination = NULL;
    INT eof = 0;

    HCRYPTPROV hProv   = 0;
    HCRYPTKEY hKey     = 0;
    HCRYPTKEY hXchgKey = 0;
    HCRYPTHASH hHash   = 0;

    PBYTE pbKeyBlob = NULL;
    DWORD dwKeyBlobLen;

    PBYTE pbBuffer = NULL;
    DWORD dwBlockLen;
    DWORD dwBufferLen;
    DWORD dwCount;

    BOOL status = FALSE;

    // Open source file.
    if((hSource = fopen(Source.c_str(),"rb")) == NULL) {
	Error("Error opening Plaintext file!\n",0);
        goto done;
    }

    // Open destination file.
    if((hDestination = fopen(Destination.c_str(),"wb")) == NULL) {
	Error("Error opening Ciphertext file!\n",0);
        goto done;
    }

    // Get handle to the default provider.
    if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)) {
        Error("Error 0 during CryptAcquireContext!\n", GetLastError());
        goto done;
    }

    if(Password.c_str() == NULL) {
	// Encrypt the file with a random session key.

	// Create a random session key.
	if(!CryptGenKey(hProv, ENCRYPT_ALGORITHM, CRYPT_EXPORTABLE, &hKey)) {
	    Error("Error 0 during CryptGenKey!\n", GetLastError());
	    goto done;
	}

	// Get handle to key exchange public key.
	if(!CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hXchgKey)) {
	    Error("Error 0 during CryptGetUserKey!\n", GetLastError());
	    goto done;
	}

	// Determine size of the key blob and allocate memory.
	if(!CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, NULL, &dwKeyBlobLen)) {
	    Error("Error 0 computing blob length!\n", GetLastError());
	    goto done;
	}
	if((pbKeyBlob =(PBYTE)malloc(dwKeyBlobLen)) == NULL) {
	    Error("Out of memory!\n",0);
	    goto done;
	}

	// Export session key into a simple key blob.
	if(!CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, pbKeyBlob, &dwKeyBlobLen)) {
	    Error("Error 0 during CryptExportKey!\n", GetLastError());
	    goto done;
	}

	// Release key exchange key handle.
	CryptDestroyKey(hXchgKey);
	hXchgKey = 0;

	// Write size of key blob to destination file.
	fwrite(&dwKeyBlobLen, sizeof(DWORD), 1, hDestination);
	if(ferror(hDestination)) {
	    Error("Error writing header!\n",0);
	    goto done;
	}

	// Write key blob to destination file.
	fwrite(pbKeyBlob, 1, dwKeyBlobLen, hDestination);
	if(ferror(hDestination)) {
	    Error("Error writing header!\n",0);
	    goto done;
	}

    } else {
	// Encrypt the file with a session key derived from a password.

	// Create a hash object.
	if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
	    Error("Error 0 during CryptCreateHash!\n", GetLastError());
	    goto done;
	}

	// Hash in the password data.
	if(!CryptHashData(hHash, Password.c_str(), strlen(Password.c_str()), 0)) {
	    Error("Error 0 during CryptHashData!\n", GetLastError());
	    goto done;
	}

	// Derive a session key from the hash object.
	if(!CryptDeriveKey(hProv, ENCRYPT_ALGORITHM, hHash, 0, &hKey)) {
	    Error("Error 0 during CryptDeriveKey!\n", GetLastError());
	    goto done;
	}

	// Destroy the hash object.
	CryptDestroyHash(hHash);
	hHash = 0;
    }

    // Determine number of bytes to encrypt at a time. This must be a multiple
    // of ENCRYPT_BLOCK_SIZE.
    dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;

    // Determine the block size. If a block cipher is used this must have
    // room for an extra block.
    if(ENCRYPT_BLOCK_SIZE > 1) {
	dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE;
    } else {
	dwBufferLen = dwBlockLen;
    }

    // Allocate memory.
    if((pbBuffer =(PBYTE) malloc(dwBufferLen)) == NULL) {
	Error("Out of memory!\n",0);
	goto done;
    }

    // Encrypt source file and write to Source file.
    do {
	// Read up to 'dwBlockLen' bytes from source file.
	dwCount = fread(pbBuffer, 1, dwBlockLen, hSource);
	if(ferror(hSource)) {
	    Error("Error reading Plaintext!\n",0);
            goto done;
        }
	eof = feof(hSource);

        // Encrypt data
	if(!CryptEncrypt(hKey, 0, eof, 0, pbBuffer, &dwCount, dwBufferLen)) {
            Error("bytes required:0\n",dwCount);
            Error("Error 0 during CryptEncrypt!\n", GetLastError());
            goto done;
        }

	// Write data to destination file.
	fwrite(pbBuffer, 1, dwCount, hDestination);
	if(ferror(hDestination)) {
	    Error("Error writing Ciphertext!\n",0);
            goto done;
        }
    } while(!feof(hSource));

    status = TRUE;

    done:

    // Close files.
    if(hSource) fclose(hSource);
    if(hDestination) fclose(hDestination);

    // Free memory.
    if(pbKeyBlob) free(pbKeyBlob);
    if(pbBuffer) free(pbBuffer);

    // Destroy session key.
    if(hKey) CryptDestroyKey(hKey);

    // Release key exchange key handle.
    if(hXchgKey) CryptDestroyKey(hXchgKey);

    // Destroy hash object.
    if(hHash) CryptDestroyHash(hHash);

    // Release provider handle.
    if(hProv) CryptReleaseContext(hProv, 0);

    return(status);
}
//---------------------------------------------------------------------------
bool spl_EncryptStream(TMemoryStream *pSource,AnsiString Password,bool LastBlock)
{
    return spl_EncryptBuffer((Byte *)pSource->Memory,pSource->Size,Password,LastBlock);
}
//---------------------------------------------------------------------------

