#ifndef PARSER_H
#define PARSER_H

/* Includes */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errorno.h>

#include "list.h"

/* Flags */
#define PARSER_CREATE  1<<0
#define PARSER_LIST    1<<1
#define PARSER_EXTRACT 1<<2
#define PARSER_STRICT  1<<3
#define PARSER_VERBOSE 1<<4

/* Types */
typedef struct inputStruct {
    bool valid;
    char* errMessage;

    FILE* archive;
    
    LIST* files;
    LIST* directories;
    
    uint16_t flags;
} SINPUT;

/* Methods */
SINPUT* parser_parse(int argc, char* argv[]);
void parser_dispose(SINPUT* target);
bool parser_flagState(SINPUT* input, uint16_t flag);

#endif
