#include "mytar.h"
#include "writemytar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
    struct dirent *directory;

    struct stat *root_stat = (struct stat*)malloc(sizeof(struct stat)); 

    /* checking for the correct num of args */
    if (argc < 3)
    {
        printf("Error - usage: mytar [ctxvS]f tarfile [path [...] ]\n");
        exit(EXIT_FAILURE);
    }

    /* reading in file name to create the tar file */
    int fd_tar = open(argv[2], O_RDWR|O_CREAT);

    /* obtain stats of the root directory of the tar file */
    stat(argv[3], root_stat);

    /* begin creating the tar file */
    write(root_stat, fd_tar, argv[3]);



    return 0;
}

