#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void deleteEmptyFolders(const char *path) {
    WIN32_FIND_DATAA findData;
    HANDLE hFind;
    char searchPath[MAX_PATH];
    char folderPath[MAX_PATH];

    sprintf(searchPath, "%s\\*", path);
    hFind = FindFirstFileA(searchPath, &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) {
            continue;
        }

        sprintf(folderPath, "%s\\%s", path, findData.cFileName);

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(findData.cFileName, "tmp") == 0 || strcmp(findData.cFileName, "branches") == 0) {
                continue;
            }

            deleteEmptyFolders(folderPath);
            RemoveDirectoryA(folderPath);
        }
    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
}

int main() {
    char path[MAX_PATH];

    printf("输入项目路径: ");
    fgets(path, sizeof(path), stdin);
    path[strcspn(path, "\r\n")] = 0;  // Remove trailing newline

    deleteEmptyFolders(path);

    printf("Empty folders deleted successfully.\n");

    return 0;
}

