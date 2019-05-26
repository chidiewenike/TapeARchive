#include "parser.h"

bool _parser_isDir(char* path) {
    DIR* temp = opendir(path);

    if (temp != NULL) {
        closedir(temp);
        return true;
    }

    return false;
}

bool _parser_isFile(char* path) {
	FILE* temp = fopen(path, "r");
	
	if (temp != NULL) {
		fclose(temp);
		return true;
	}
	
	return false;
}

void _addFlags(SINPUT* sinput, char* flags) {
	/* Running data */
	char* current = flags;
	
	while (*current != '\0') {
		switch (*current) {
            case 'f':
                if (argc >= 3) sinput->valid = true;
                else {
                    sinput->errorMessage = "An archive must be entered.";
                    sinput->valid = false;
                    return;
                }

                break;

            case 'c':
                sinput->flags |= PARSER_CREATE;
                break;

            case 't':
                sinput->flags |= PARSER_LIST;
                break;

            case 'v':
                sinput->flags |= PARSER_VERBOSE;
                break;

            case 'x':
                sinput->flags |= PARSER_EXTRACT;
                break;
        }
		
		/* Next letter */
		current++;
	}
	
	/* f was not entered */
    if (!sinput->valid) {
        sinput->errorMessage = "The option \"f\" must be supplied.";
        sinput->valid = false;
    }
}

SINPUT* parser_parse(int argc, char* argv[]) {
    /* Result data */
    SINPUT* result = malloc(sizeof(SINPUT));
    result->valid = false;
    result->errMsg = "";
    result->archive = NULL;
    result->files = list_init(10);
    result->directories = list_init(10);
    result->flags = 0;

    /* Running data */
    int index;
    char* current;
    char c;
    void* temp;

    /* Check parameter counts */
    if (argc == 1) {
        result->errMessage = "Not enough arguments.";
        return result;
    }

    /* Parse parameters */
    _addFlags(result, argv[1]);
    if (!result->valid) return result;
    
    /* Open archive */
    result->archive = fopen(argv[2], parser_flagState(result, PARSER_CREATE) ? "w" : "r");
    if (result->archive == NULL) {
    	result->valid = false;
    	result->errMessage = strcat("Could not open archive", strerror(errno));
    	return result;
    }
    
    /* Open files */
    if (!parser_flagState(result, PARSER_CREATE)) return result;
    
    for (index = 3; index < argc; index++) {
    	if (_parser_isDir(argv[index])) {
    		list_append(result->directories, opendir(argv[index]));
    	}
    	else if (_parser_isFile(argv[index])) {
    		list_append(result->files, fopen(argv[index], "r"));
    	}
    	else {
    		result->valid = false;
    		sprintf(result->errMessage, "Cannot open \"%s\" as a file or directory.", argv[index]);
    		return result;
    	}
    }
    
    return result;
}

void parser_dispose(SINPUT* target) {
    /* Running data */
    int index;

    /* Close and free file pointers */
    if (target->files != NULL) {
        for (index = 0; index < target->files->count; index++) {
            fclose(*(target->files->data + index));
        }
    
        free(target->files);
    }

    /* Close directories and free directory pointers */
    if (target->directories != NULL) {
        for (index = 0; index < target->dirCount; index++) {
            closedir(*(target->directories->data + index));
        }

        list_dispose(target->directories, false);
    }

    /* Free the archive if available */
    if (target->archive != NULL) {
        fclose(target->archive);
    }

    /* Free structure */
    free(target->errMessage);
    free(target);
}

bool parser_flagState(SINPUT* input, uint16_t flag) {
    if (input == NULL) return false;

    return (input->flags & flag) != 0;
}
