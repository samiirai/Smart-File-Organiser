#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "utils.h"
#include "duplicate.h"

// Struct to hold file info in memory
typedef struct {
    char fileName[MAX_PATH_LEN];
    DWORD fileSize;
} FileData;

void FindDuplicates(const char* directory) {
    WIN32_FIND_DATAA findFileData;
    char searchPath[MAX_PATH_LEN];
    snprintf(searchPath, sizeof(searchPath), "%s\\*.*", directory);

    HANDLE hFind = FindFirstFileA(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) return;

    FileData files[200]; // Assuming max 200 files for college demo
    int fileCount = 0;

    // 1. Gather all files and their sizes
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            strncpy(files[fileCount].fileName, findFileData.cFileName, MAX_PATH_LEN);
            files[fileCount].fileSize = findFileData.nFileSizeLow;
            fileCount++;
        }
    } while (FindNextFileA(hFind, &findFileData) != 0 && fileCount < 200);
    FindClose(hFind);

    printf("\n--- Scanning for Duplicates ---\n");
    int foundDuplicate = 0;

    // 2. Compare sizes, then compare hashes if sizes match
    for (int i = 0; i < fileCount; i++) {
        for (int j = i + 1; j < fileCount; j++) {
            if (files[i].fileSize == files[j].fileSize) {
                char path1[MAX_PATH_LEN], path2[MAX_PATH_LEN];
                char hash1[65], hash2[65];

                snprintf(path1, sizeof(path1), "%s\\%s", directory, files[i].fileName);
                snprintf(path2, sizeof(path2), "%s\\%s", directory, files[j].fileName);

                if (GenerateFileHash(path1, hash1) && GenerateFileHash(path2, hash2)) {
                    if (strcmp(hash1, hash2) == 0) {
                        printf("[DUPLICATE FOUND]\n");
                        printf(" 1: %s\n 2: %s\n", files[i].fileName, files[j].fileName);
                        foundDuplicate = 1;
                    }
                }
            }
        }
    }

    if (!foundDuplicate) {
        printf("No duplicate files found in this directory.\n");
    }
}