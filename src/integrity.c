#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "utils.h"
#include "integrity.h"

void CheckIntegrity(const char* directory) {
    char manifestPath[MAX_PATH_LEN];
    snprintf(manifestPath, sizeof(manifestPath), "%s\\manifest.txt", directory);
    
    printf("\n--- File Integrity Checker ---\n");
    printf("1. Create new Manifest\n");
    printf("2. Verify files against Manifest\n");
    printf("Choice: ");
    
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        FILE* mf = fopen(manifestPath, "w");
        if (!mf) return;

        WIN32_FIND_DATAA findFileData;
        char searchPath[MAX_PATH_LEN];
        snprintf(searchPath, sizeof(searchPath), "%s\\*.*", directory);
        HANDLE hFind = FindFirstFileA(searchPath, &findFileData);
        
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && strcmp(findFileData.cFileName, "manifest.txt") != 0) {
                    char filePath[MAX_PATH_LEN], hash[65];
                    snprintf(filePath, sizeof(filePath), "%s\\%s", directory, findFileData.cFileName);
                    if (GenerateFileHash(filePath, hash)) {
                        fprintf(mf, "%s %s\n", hash, findFileData.cFileName);
                    }
                }
            } while (FindNextFileA(hFind, &findFileData) != 0);
            FindClose(hFind);
        }
        fclose(mf);
        printf("Manifest created successfully.\n");

    } else if (choice == 2) {
        FILE* mf = fopen(manifestPath, "r");
        if (!mf) {
            printf("No manifest found.\n");
            return;
        }

        char storedHash[65], fileName[MAX_PATH_LEN];
        while (fscanf(mf, "%64s %511[^\n]", storedHash, fileName) == 2) {
            char filePath[MAX_PATH_LEN], currentHash[65];
            snprintf(filePath, sizeof(filePath), "%s\\%s", directory, fileName);
            
            if (GenerateFileHash(filePath, currentHash)) {
                if (strcmp(storedHash, currentHash) == 0) {
                    printf("[OK] %s\n", fileName);
                } else {
                    printf("[MODIFIED] %s\n", fileName);
                }
            } else {
                printf("[MISSING] %s\n", fileName);
            }
        }
        fclose(mf);
    }
}
