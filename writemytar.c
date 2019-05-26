#include "mytar.h"
#include "writemytar.h"


void write_tar(struct stat *root_stat, int tar_fd, char *root_path)
{
    struct dirent *directory = (struct dirent*)malloc(sizeof(struct dirent));
    struct tar_header *root_header = (struct tar_header*)malloc(sizeof(struct tar_header));

    root_header = create_header(root_path);

    traverse_dirs(root_header);
}

void print_header(struct tar_header *header)
{
    printf("name: %s\n",header->name);
    printf("mode: %s\n",header->mode);
    printf("gid: %s\n",header->gid);
    printf("uid: %s\n",header->uid);
    printf("size: %s\n",header->size);
    printf("mtime: %s\n",header->mtime);
    printf("typeflag: %c\n",header->typeflag);
    printf("linkname: %s\n",header->linkname);
    printf("gname: %s\n",header->gname);
    printf("uname: %s\n",header->uname);
    printf("minor: %s\n",header->devminor);
    printf("major: %s\n",header->devmajor);
    printf("version: %s\n",header->version);
}

struct tar_header* create_header(char *path)
{
    struct tar_header *header = (struct tar_header*)malloc(sizeof(struct tar_header));
    struct stat *head_stat = (struct stat*)malloc(sizeof(struct stat));    
    struct group *head_grp = (struct group*)malloc(sizeof(struct group));
    struct passwd *head_pwd = (struct passwd*)malloc(sizeof(struct passwd));


    lstat(path,head_stat);
    header->typeflag = check_type(head_stat->st_mode);
    head_grp = getgrgid(head_stat->st_gid);
    head_pwd = getpwuid(head_stat->st_uid);
    strcpy(header->name, path); 
    sprintf(header->mode, "%o", head_stat->st_mode);
    sprintf(header->gid, "%o", head_stat->st_gid);
    sprintf(header->uid, "%o", head_stat->st_uid);
    sprintf(header->size, "%lo", head_stat->st_size);
    sprintf(header->mtime, "%lo", head_stat->st_mtime);
    strcpy(header->gname, head_grp->gr_name);
    strcpy(header->uname, head_pwd->pw_name);
    sprintf(header->devminor, "%o", minor(head_stat->st_dev));
    sprintf(header->devmajor, "%o", major(head_stat->st_dev));
    strcpy(header->version, "00");
    // sprintf(header->chksum, "%o", head_stat->st_mode);

    if (header->typeflag == '2')
         readlink(path, header->linkname, 100);

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

bool not_empty_dir(DIR *dir)
{
    struct dirent *dir_struct = (struct dirent*)malloc(sizeof(struct dirent));
    int count = 0;

    while((dir_struct = readdir(dir)) != NULL)
    {
        count++;
    }

    if (count > 2)
    {
        return true;
    }

    return false;
}

void traverse_dirs(struct tar_header *header)
{
    struct dirent *contents = (struct dirent*)malloc(sizeof(struct dirent));
    char curr_path [100];

    strcpy(curr_path, header->name);

    printf("\n\ncurr_path: %s\n\n", curr_path);
    DIR *dir = opendir(header->name);

    while ((contents = readdir(dir)) != NULL)
    {
        if((strcmp(contents->d_name,".") != 0) && (strcmp(contents->d_name,"..") != 0))
        {
            struct tar_header *new_hdr = (struct tar_header*)malloc(sizeof(struct tar_header));
            char new_path[100];

            strcpy(new_path,curr_path);
            strcat(new_path,"/");
            strcat(new_path, contents->d_name);

            new_hdr = create_header(new_path);
            print_header(new_hdr);
            // write_to_file

            if((new_hdr->typeflag == '5') && (not_empty_dir(opendir(new_hdr->name))))
                traverse_dirs(new_hdr);
        }
    }
}

