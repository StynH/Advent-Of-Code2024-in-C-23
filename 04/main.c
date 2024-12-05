#include <file_handling.h>
#include <vector.h>
#include <string.h>
#include "vector3d.h"

#define INPUT_FILE_LOCATION "files/input.txt"
#define XMAS "XMAS"
#define SAMX "SAMX"
#define MAS "MAS"
#define SAM "SAM"

void
load_text_into_matrix(const FileContext* context, Vector3d* matrix){
    char* rest = strdup(context->content);
    char* line;

    size_t i = 0;
    while ((line = strtok_r(rest, "\n", &rest))) {
        size_t j = 0;
        for (const char *p = line; *p != '\0'; p++) {
            char* mem_token = malloc(sizeof(char));
            *mem_token = *p;
            vector3d_insert_at(matrix, j, i, mem_token);
            ++j;
        }
        ++i;
    }
}

void
part_one(const FileContext* context) {
    Vector3d* matrix = vector3d_create();
    load_text_into_matrix(context, matrix);

    int total = 0;
    int dx[] = { -1, -1, -1,  0,  0,  1,  1,  1 };
    int dy[] = { -1,  0,  1, -1,  1, -1,  0,  1 };
    size_t width = matrix->data[0]->length;
    for(size_t y = 0; y < matrix->heigth; ++y){
        for(size_t x = 0; x < width; ++x){
            char* token = (char*)vector3d_element_at(matrix, x, y);
            if(*token == 'X'){
                bool correct = true;
                for(size_t d = 0; d < 8; ++d){
                    char word[5] = { 'X' };
                    for(size_t e = 1; e < 4; ++e){
                        int row = y + (dy[d] * e);
                        int col = x + (dx[d] * e);

                        if(
                            row >= 0
                            && col >= 0
                            && (size_t)row < matrix->heigth
                            && (size_t)col < width
                        ){
                            word[e] = *(char*)vector3d_element_at(matrix, col, row);
                        }
                        else{
                            correct = false;
                            break;
                        }
                    }

                    if(correct){
                        word[4] = '\0';
                        if(strcmp(word, XMAS) == 0 || strcmp(word, SAMX) == 0){
                            ++total;
                        }
                    }

                    correct = true;
                }
            }
        }
    }

    printf("Total XMAS': %d\n", total);
    vector3d_destroy(matrix);
}

void
part_two(const FileContext* context) {
    Vector3d* matrix = vector3d_create();
    load_text_into_matrix(context, matrix);

    int total = 0;
    size_t width = matrix->data[0]->length;
    for(size_t y = 0; y < matrix->heigth; ++y){
        for(size_t x = 0; x < width; ++x){
            char* token = (char*)vector3d_element_at(matrix, x, y);
            if(*token == 'A'){
                if(
                    (int)x - 1 < 0
                    || (int)y - 1 < 0
                    || y + 1 >= matrix->heigth
                    || x + 1 >= width
                ){
                    continue;
                }

                char* tr = (char*)vector3d_element_at(matrix, x - 1, y + 1);
                char* tl = (char*)vector3d_element_at(matrix, x - 1, y - 1);
                char* br = (char*)vector3d_element_at(matrix, x + 1, y + 1);
                char* bl = (char*)vector3d_element_at(matrix, x + 1, y - 1);

                char ld[4] = { *tl, 'A', *br, '\0' };
                char rd[4] = { *tr, 'A', *bl, '\0' };
                if(
                    (strcmp(ld, MAS) == 0 || strcmp(ld, SAM) == 0) &&
                    (strcmp(rd, MAS) == 0 || strcmp(rd, SAM) == 0)
                )
                {
                    ++total;
                }
            }
        }
    }

    printf("Total X-MAS': %d\n", total);
    vector3d_destroy(matrix);
}

int
main(void) {
    printf("Running day 4 of Advent of Code 2024...\n");
    FileContext* context = read_file_into_buffer(INPUT_FILE_LOCATION);
    if (context->error_code == FILE_HANDLING_NO_ERR) {
        part_one(context);
        part_two(context);
    }
    else {
        printf("Failed to open file '%s', Error Code: %d", INPUT_FILE_LOCATION, context->error_code);
    }

    free(context);
    return 0;
}
