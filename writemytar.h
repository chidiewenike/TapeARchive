#ifndef WRITEMYTAR_H
#define WRITEMYTAR_H

#include <sys/stat.h>

void write(struct stat *root_stat, int tar_fd, char *root_path);
struct tar_header* create_header(int tar_fd, char *path);
char check_type(mode_t mode);

#endif