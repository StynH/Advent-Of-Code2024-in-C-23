#include <string.h>
#include <stdio.h>
#include "interpreter.h"

int
interpreter_execute_node(FunctionTable* functionTable, AstNode* node){
    if(node->type == NUMERIC){
        return node->content.value;
    }

    size_t index = 0;
    while (index < functionTable->amount){
        FunctionEntry* entry = functionTable->entries[index];
        if(entry != nullptr && strcmp(entry->function_name, node->content.function_call.name) == 0){
            if(node->content.function_call.arg_count > 0){
                int *args = malloc(node->content.function_call.arg_count * sizeof(int));
                for(size_t i = 0; i < (size_t)node->content.function_call.arg_count; ++i){
                    args[i] = interpreter_execute_node(functionTable, node->content.function_call.arguments[i]);
                }
                int result = entry->method(args, node->content.function_call.arg_count);
                free(args);
                return result;
            }
            else{
                int result = entry->method(nullptr, 0);
                return result;
            }
        }
        ++index;
    }

    printf("No function found with name: %s\n", node->content.function_call.name);
    return -1;
}
