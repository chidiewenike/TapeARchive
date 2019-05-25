#include "mytar.h"
#include "writemytar.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void write(struct stat *root_stat, int tar_fd, char *root_path)
{
    struct dirent *directory = (struct dirent*)malloc(sizeof(struct dirent));
    struct tar_header *root_header = (struct tar_header*)malloc(sizeof(struct tar_header));

    strcpy(root_header->name, root_path); 
    sprintf(root_header->mode, "%o", root_stat->st_mode);
 

    printf("%s\n",root_header->name);
    printf("%s\n",root_header->mode);

    // while((directory = readdir(direct)) != NULL)
    // {
    //     create_archive()
    // }



}

// void create_archive()
// {

// }