#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

#define MUL_NODE "mul"
#define DO_NODE "do"
#define DONT_NODE "don't"
#define BRACKET_OPEN "("
#define BRACKET_CLOSE ")"
#define COMMA ","

bool
try_parse_number(char* token, int* number){
    int value;
    char extra;

    int matches = sscanf_s(token, "%d", &value, &extra);
    if (matches != 1) {
        return false;
    }

    *number = value;
    return true;
}

AstNode*
parse_mul_node(Vector* token_vector){
    char* next_token = vector_remove_element_at(token_vector, 0);
    if(strcmp(next_token, BRACKET_OPEN) != 0){
        return nullptr;
    }

    next_token = vector_remove_element_at(token_vector, 0);
    int left_operand;
    if(!try_parse_number(next_token, &left_operand)){
        return nullptr;
    }

    next_token = vector_remove_element_at(token_vector, 0);
    if(strcmp(next_token, COMMA) != 0){
        return nullptr;
    }

    next_token = vector_remove_element_at(token_vector, 0);
    int right_operand;
    if(!try_parse_number(next_token, &right_operand)){
        return nullptr;
    }

    next_token = vector_remove_element_at(token_vector, 0);
    if(strcmp(next_token, BRACKET_CLOSE) != 0){
        return nullptr;
    }

    AstNode* mul_node = malloc(sizeof(AstNode));
    mul_node->type = FUNCTION_CALL;

    AstNode* left_node = malloc(sizeof(AstNode));
    left_node->content.value = left_operand;
    left_node->type = NUMERIC;

    AstNode* right_node = malloc(sizeof(AstNode));
    right_node->content.value = right_operand;
    right_node->type = NUMERIC;

    mul_node->content.function_call.name = (char*)MUL_NODE;
    mul_node->content.function_call.arg_count = 2;
    mul_node->content.function_call.arguments = malloc(mul_node->content.function_call.arg_count * sizeof(AstNode));
    mul_node->content.function_call.arguments[0] = left_node;
    mul_node->content.function_call.arguments[1] = right_node;

    return mul_node;
}

AstNode*
parse_dont_node(Vector* token_vector) {
    char* next_token = vector_remove_element_at(token_vector, 0);
    if(strcmp(next_token, BRACKET_OPEN) != 0){
        return nullptr;
    }

    next_token = vector_remove_element_at(token_vector, 0);
    if(strcmp(next_token, BRACKET_CLOSE) != 0){
        return nullptr;
    }

    AstNode* node = malloc(sizeof(AstNode));
    node->type = FUNCTION_CALL;
    node->content.function_call.name = (char*)DONT_NODE;
    node->content.function_call.arg_count = 0;
    return node;
}

AstNode*
parse_do_node(Vector* token_vector) {
    char* next_token = vector_remove_element_at(token_vector, 0);
    if(strcmp(next_token, BRACKET_OPEN) != 0){
        return nullptr;
    }

    next_token = vector_remove_element_at(token_vector, 0);
    if(strcmp(next_token, BRACKET_CLOSE) != 0){
        return nullptr;
    }

    AstNode* node = malloc(sizeof(AstNode));
    node->type = FUNCTION_CALL;
    node->content.function_call.name = (char*)DO_NODE;
    node->content.function_call.arg_count = 0;
    return node;
}

AstNode*
create_node(Vector* token_vector, const char* token){
    if(strcmp(token, MUL_NODE) == 0){
        return parse_mul_node(token_vector);
    }

    if(strcmp(token, DO_NODE) == 0){
        return parse_do_node(token_vector);
    }

    if(strcmp(token, DONT_NODE) == 0){
        return parse_dont_node(token_vector);
    }

    return nullptr;
}

AstNode*
create_node_from_known_function(FunctionTable* function_table, Vector* token_vector, const char* token){
    size_t index = 0;
    while (index < function_table->amount){
        if(strcmp(token, function_table->entries[index]->function_name) == 0){
            return create_node(token_vector, token);
        }
        ++index;
    }
    return nullptr;
}

Vector*
parser_parse(FunctionTable* function_table, Vector* token_vector){
    Vector* node_vector = vector_create();

    while(token_vector->length > 0){
        const char* token = vector_remove_element_at(token_vector, 0);
        AstNode* node = create_node_from_known_function(function_table, token_vector, token);
        if(node != nullptr){
            vector_insert_into(node_vector, node);
        }
    }

    return node_vector;
}
