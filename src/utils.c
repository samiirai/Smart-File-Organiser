#include <stdio.h>
#include <windows.h>
#include <wincrypt.h>
#include "utils.h"

int GenerateFileHash(const char* filePath, char* outputHashStr) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    HANDLE hFile = CreateFileA(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    
    if (hFile == INVALID_HANDLE_VALUE) return 0;

    CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
    CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash);

    BYTE buffer[8192];
    DWORD bytesRead;
    while (ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
        CryptHashData(hHash, buffer, bytesRead, 0);
    }

    BYTE hash[HASH_SIZE];
    DWORD hashLen = HASH_SIZE;
    CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0);

    for (DWORD i = 0; i < hashLen; i++) {
        sprintf(outputHashStr + (i * 2), "%02x", hash[i]);
    }
    outputHashStr[64] = '\0';

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    CloseHandle(hFile);
    return 1;
}