#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "utils.h"
#include "organizer.h"

void OrganizeFiles(const char* directory) {
    WIN32_FIND_DATAA findFileData;
    char searchPath[MAX_PATH_LEN];
    snprintf(searchPath, sizeof(searchPath), "%s\\*.*", directory);

    HANDLE hFind = FindFirstFileA(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error: Could not open directory.\n");
        return;
    }

    printf("\n--- Organizing Files ---\n");
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            char* ext = strrchr(findFileData.cFileName, '.');
            if (ext != NULL) {
                char targetFolder[MAX_PATH_LEN];
                
                if (strcmp(ext, ".txt") == 0 || strcmp(ext, ".pdf") == 0 || strcmp(ext, ".docx") == 0) {
                    snprintf(targetFolder, sizeof(targetFolder), "%s\\Documents", directory);
                } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".png") == 0) {
                    snprintf(targetFolder, sizeof(targetFolder), "%s\\Images", directory);
                } else {
                    snprintf(targetFolder, sizeof(targetFolder), "%s\\Others", directory);
                }

                CreateDirectoryA(targetFolder, NULL); 

                char oldPath[MAX_PATH_LEN], newPath[MAX_PATH_LEN];
                snprintf(oldPath, sizeof(oldPath), "%s\\%s", directory, findFileData.cFileName);
                snprintf(newPath, sizeof(newPath), "%s\\%s", targetFolder, findFileData.cFileName);

                if (MoveFileA(oldPath, newPath)) {
                    printf("Moved: %s -> %s\n", findFileData.cFileName, targetFolder);
                }
            }
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);
    printf("Organization complete!\n");
}