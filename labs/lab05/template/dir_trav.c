#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

void traverseDirectory(char *dirname){
    // open current directory
    DIR *oDir = opendir(dirname);
    if (oDir == NULL) {
        perror("Error opening directory");
        exit(1);
    }
    struct dirent *curDir;
    char *dirPath;
    struct stat stats;

    // Traverse through all entries
    while((curDir = readdir(oDir)) != NULL){
        // skip . and ..
        if (strcmp(curDir->d_name, ".") == 0 || strcmp(curDir->d_name, "..") == 0) {
            continue;
        }

        // concatenate dirname with the directory entry
        // use malloc
        dirPath = (char *) malloc(strlen(curDir->d_name) + strlen(dirname) + 2);
        snprintf(dirPath, strlen(dirname) + strlen(curDir->d_name) + 2, "%s/%s", dirname, curDir->d_name);

        // if entry is a directory
        if (lstat(dirPath, &stats) != -1) {
            if (S_ISDIR(stats.st_mode)) {
                //          print entry name
                //          You may have to get the absolute path
                //          recursively call traverseDirectory
                printf("%s\n", dirPath);
                traverseDirectory(dirPath);
            }
            // if entry is a regular file
            else if (S_ISREG(stats.st_mode)) {
                //          print entry name
                printf("%s\n", dirPath);
            }

            // else
            else {
                //          if entry is symbolic
                if (S_ISLNK(stats.st_mode)) {
                    //              print entry name
                    printf("Symlink found: %s\n", dirPath);
                }
            } 
        }
        free(dirPath);
    }
    // close current directory
    closedir(oDir);
}

int main(int argc, char *argv[]) {

    // Task 1 : Hard link and Soft link
    //          Create a new file argv[1]
    //          Create a hard link argv[2] for argv[1]
    //          Create a soft link argv[3] for argv[1]
    FILE *nFile = fopen(argv[1], "w");
    
    fclose(nFile);

    link(argv[1], argv[2]);
    symlink(argv[1], argv[3]);

    FILE *out = freopen("output.txt", "w", stdout);
    // Task 2 : Traverse directory
    //          Traverse directory argv[4] and report all files and directories
    //          If the directory entry is a soft link, report it
    traverseDirectory(argv[4]);
    fclose(out);
    return 0;
}