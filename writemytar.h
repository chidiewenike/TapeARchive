#ifndef WRITEMYTAR_H
#define WRITEMYTAR_H

#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
void write_tar(struct stat *root_stat, int tar_fd, char *root_path);
struct tar_header* create_header(char *path);
char check_type(mode_t mode);
bool not_empty_dir(DIR *dir);
void traverse_dirs(struct tar_header *header);
void print_header(struct tar_header *header);

#endif