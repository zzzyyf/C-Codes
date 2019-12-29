#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

int printFileInfo(char *fileName, int depth){
    // print depth info
    for(int i=0;i<depth;i++){
        printf("  ");
    }
    // print file mode
    struct stat temp;
    if(stat(fileName, &temp)==-1){
        printf("error opening file %s!\n", fileName);
        return 1;
    }else{
        switch (temp.st_mode & __S_IFMT)
        {
        case __S_IFDIR:
            printf("d");
            break;
        case __S_IFLNK:
            printf("l");
            break;
        // omit other types
        default:
            printf("-");
            break;
        }
    
        // print access
        printf("%c", temp.st_mode & S_IRUSR?'r':'-');
        printf("%c", temp.st_mode & S_IWUSR?'w':'-');
        printf("%c", temp.st_mode & S_IXUSR?'x':'-');
        printf("%c", temp.st_mode & S_IRGRP?'r':'-');
        printf("%c", temp.st_mode & S_IWGRP?'w':'-');
        printf("%c", temp.st_mode & S_IXGRP?'x':'-');
        printf("%c", temp.st_mode & S_IROTH?'r':'-');
        printf("%c", temp.st_mode & S_IWOTH?'w':'-');
        printf("%c", temp.st_mode & S_IXOTH?'x':'-');

        // print links num
        printf(" %d ", temp.st_nlink);
        // print owner name
        struct passwd *pwd;
        pwd = getpwuid(temp.st_uid);
        printf("%s ", pwd->pw_name);
        // print group name of owner
        struct group *grp;
        grp = getgrgid(temp.st_gid);
        printf("%s ", grp->gr_name);
        // print file size
        printf("%ld ", temp.st_size);
        // print modify date
        struct tm *mTime = localtime(&temp.st_mtime);
        char timeStr[100];
        strftime(timeStr, 99, "%0m %0d %0H:%0M", mTime);
        printf("%s ", timeStr);
        // print file name
        printf("%s\n", fileName);
    }
    return 0;
}

/**
 * arg1 fileName may be relative path or absolute path.
 */
int traverseDir(char *fileName, int depth, char *parentDirName)
{
    // if current dir item is a file
    // print its info & return
    // else get into the dir and call this function on every sub item
    struct stat temp;
    if(stat(fileName, &temp)==-1){
        printf("error opening file %s!\n", fileName);
        return 1;
    }else{
        if((temp.st_mode & __S_IFMT )== __S_IFDIR){
            // if depth!=0, print info of this dir
            if(depth>0 && printFileInfo(fileName, depth)==1){
                return 1;
            }
            if(parentDirName[0]!=0){
                // printf("\n%s", parentDirName);
            }
            // printf("%s:\n", fileName);
            // get into this dir
            char cwd[4097], oldCwd[4097];
            getcwd(cwd, 4096);
            strcpy(oldCwd, cwd);
            if(fileName[0]!='/'){
                // relative path
                strcat(cwd, "/");
                strcat(cwd, fileName);
                chdir(cwd);
            }else{
                // absolute path
                chdir(fileName);
            }
            DIR *dir = opendir(".");
            struct dirent *dirItem;
            // print info of this dir
            // jump "." and ".."
            while((dirItem = readdir(dir))!=NULL){
                // print every info
                if(dirItem->d_name[0]=='.'){
                    continue;
                }
                if(traverseDir(dirItem->d_name, depth+1, fileName)==1){
                    return 1;
                }
            }
            // get back to original dir
            closedir(dir);
            chdir(oldCwd);
            
        }else{
            if(printFileInfo(fileName, depth)==1){
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]){
    // try to open given dir
    // if given dir is empty, open working dir
    DIR *dir;
    char cwdName[4097];
    if (argc > 0 && argv[1]!=NULL){
        dir = opendir(argv[1]);
        if (dir == NULL){
            printf("error opening given directory!\n");
            return 1;
        }
        strcpy(cwdName, argv[1]);
    }else{
        dir = opendir(getcwd(cwdName, 4096));
        if (dir == NULL){
            printf("error opening current directory!\n");
            return 1;
        }
        strcpy(cwdName, ".");
    }
    // then start print
    return traverseDir(cwdName, 0, "");
    
}