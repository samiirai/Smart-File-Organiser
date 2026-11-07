#ifndef UTILS_H
#define UTILS_H

#define MAX_PATH_LEN 512
#define HASH_SIZE 32

int GenerateFileHash(const char* filePath, char* outputHashStr);

#endif