#include <file_handling.h>
#include <lexer.h>
#include <string.h>
#include <vector.h>
#include "parser.h"

#define INPUT_FILE_LOCATION "files/input.txt"
#define MUL_FUNCTION "mul"
#define DO_FUNCTION "do"
#define DONT_FUNCTION "don't"

bool function_mul_enabled = true;

int
function_mul(const int* args, int arg_count){
    if(arg_count != 2){
        printf("Function 'function_mul' expects two arguments, but got %d.", arg_count);
        return -1;
    }

    if(!function_mul_enabled){
        return 0;
    }

    return args[0] * args[1];
}

int
function_do(const int* args, int arg_count){
    function_mul_enabled = true;
    return 0;
}

int
function_dont(const int* args, int arg_count){
    function_mul_enabled = false;
    return 0;
}

void
part_one(const FileContext* context) {
    const char* code = strdup(context->content);

    FunctionTable* function_table = malloc(sizeof(FunctionTable));
    function_table->entries = malloc(sizeof(FunctionEntry));
    function_table->amount = 1;

    FunctionEntry* mul_entry = malloc(sizeof(FunctionEntry));
    mul_entry->function_name = MUL_FUNCTION;
    mul_entry->method = function_mul;
    function_table->entries[0] = mul_entry;

    Vector* token_vector = lexer_tokenize(code);
    Vector* node_vector = parser_parse(function_table, token_vector);

    int total = 0;
    for(size_t i = 0; i < node_vector->length; ++i){
        AstNode* node = (AstNode*)vector_element_at(node_vector, i);
        total += interpreter_execute_node(function_table, node);
    }
    printf("Total Result of Multiplications: %d\n", total);

    vector_destroy(token_vector);
    vector_destroy(node_vector);
    free(function_table);
    free(mul_entry);
}

void
part_two(const FileContext* context) {
    const char* code = strdup(context->content);

    FunctionTable* function_table = malloc(sizeof(FunctionTable));
    function_table->entries = malloc(sizeof(FunctionEntry));
    function_table->amount = 3;

    FunctionEntry* mul_entry = malloc(sizeof(FunctionEntry));
    mul_entry->function_name = MUL_FUNCTION;
    mul_entry->method = function_mul;
    function_table->entries[0] = mul_entry;

    FunctionEntry* do_entry = malloc(sizeof(FunctionEntry));
    do_entry->function_name = DO_FUNCTION;
    do_entry->method = function_do;
    function_table->entries[1] = do_entry;

    FunctionEntry* dont_entry = malloc(sizeof(FunctionEntry));
    dont_entry->function_name = DONT_FUNCTION;
    dont_entry->method = function_dont;
    function_table->entries[2] = dont_entry;

    Vector* token_vector = lexer_tokenize(code);
    Vector* node_vector = parser_parse(function_table, token_vector);

    int total = 0;
    for(size_t i = 0; i < node_vector->length; ++i){
        AstNode* node = (AstNode*)vector_element_at(node_vector, i);
        total += interpreter_execute_node(function_table, node);
    }
    printf("Total Result of Multiplications (2): %d\n", total);

    vector_destroy(token_vector);
    vector_destroy(node_vector);
    free(function_table);
    free(mul_entry);
}

int
main(void) {
    printf("Running day 3 of Advent of Code 2024...\n");
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
