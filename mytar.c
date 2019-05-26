#include "mytar.h"
#include "writemytar.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
int main(int argc, char* argv[])
{

    /* Get input state */

    SINPUT* input = paser_parse(argc, argv);

    

    if (!input->valid) {

        fprintf(stderr, "%s\n", input->errMessage);

        exit(EXIT_FAILURE);

    }
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
    write_tar(root_stat, fd_tar, argv[3]);

    return 0;
}

