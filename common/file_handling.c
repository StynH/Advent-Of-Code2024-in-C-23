#include "file_handling.h"

#include <string.h>

FileContext*
read_file_into_buffer(const char* path){
    FileContext* context = (FileContext*)malloc(sizeof(FileContext));
    FILE* handle = nullptr;
    fopen_s(&handle, path, "rb");

    if(handle == nullptr){
        context->error_code = FILE_HANDLING_ERR_FILE_NOT_FOUND;
        printf("Error opening %s: %s\n", path, strerror(errno));
        return context;
    }

    long length;
    if (fseek(handle, 0, SEEK_END) != 0) {
        context->error_code = FILE_HANDLING_ERR_FILE_POSITIONING;
        return context;
    }

    if ((length = ftell(handle)) == -1) {
        context->error_code = FILE_HANDLING_ERR_FILE_SEEK_ERROR;
        return context;
    }

    fseek (handle, 0, SEEK_SET);
    char *buffer = malloc(length);
    if (buffer)
    {
        fread (buffer, 1, length, handle);
    }
    fclose (handle);

    context->content = buffer;
    context->error_code = FILE_HANDLING_NO_ERR;
    return context;
}
