#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdio.h>
#include <stdlib.h>

#define FILE_HANDLING_NO_ERR -1
#define FILE_HANDLING_ERR_FILE_NOT_FOUND 1
#define FILE_HANDLING_ERR_FILE_POSITIONING 2
#define FILE_HANDLING_ERR_FILE_SEEK_ERROR 3

typedef struct FileContext {
    char* content;
    int error_code;
} FileContext;

FileContext* read_file_into_buffer(const char* path);

#endif //FILE_HANDLING_H
