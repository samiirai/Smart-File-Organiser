#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "organizer.h"
#include "duplicate.h"
#include "integrity.h"

int main() {
    int choice;
    char targetDir[MAX_PATH_LEN];

    printf("Enter folder path (e.g., C:\\test_folder): ");
    scanf(" %[^\n]s", targetDir);

    do {
        printf("\n========================================\n");
        printf("     SMART FILE MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. Organize Files\n");
        printf("2. Find Duplicate Files\n");
        printf("3. Check File Integrity\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: OrganizeFiles(targetDir); break;
            case 2: FindDuplicates(targetDir); break;
            case 3: CheckIntegrity(targetDir); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
