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

    root_header = create_header(tar_fd, root_path);
 

    printf("%s\n",root_header->name);
    printf("%s\n",root_header->mode);
    printf("%s\n",root_header->gid);
    printf("%s\n",root_header->uid);
    printf("%s\n",root_header->size);
    printf("%s\n",root_header->mtime);
    printf("%s\n",root_header->size);

    // while((directory = readdir(direct)) != NULL)
    // {
    //     create_archive()
    // }



}

struct tar_header* create_header(int tar_fd, char *path)
{
    struct tar_header *header = (struct tar_header*)malloc(sizeof(struct tar_header));
    struct stat *head_stat = (struct stat*)malloc(sizeof(struct stat));    

    stat(path,head_stat);

    strcpy(header->name, path); 
    sprintf(header->mode, "%o", head_stat->st_mode);
    sprintf(header->gid, "%o", head_stat->st_gid);
    sprintf(header->uid, "%o", head_stat->st_uid);
    sprintf(header->size, "%o", head_stat->st_size);
    sprintf(header->mtime, "%o", head_stat->st_mtime);
    // sprintf(header->chksum, "%o", head_stat->st_mode);
    // sprintf(header->typeflag, "%o", check_type(head_stat->st_mode));

    return header;
}

char check_type(mode_t mode)
{
    if (S_ISREG(mode)) 
        return '0';
    else if (S_ISDIR(mode))
        return '5';
    else
        return '2';
}
// void create_archive()
// {

// }