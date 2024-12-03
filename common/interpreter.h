#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdlib.h>

enum Type {
    NUMERIC,
    FUNCTION_CALL
};

typedef struct AstNode {
    enum Type type;
    union {
        int value;
        struct {
            char* name;
            struct AstNode** arguments;
            int arg_count;
        } function_call;
    } content;
} AstNode;

typedef int (*CFunction)(const int *args, int arg_count);

typedef struct FunctionEntry{
  const char* function_name;
  bool enabled;
  CFunction method;
} FunctionEntry;

typedef struct FunctionTable{
    FunctionEntry** entries;
    size_t amount;
} FunctionTable;

int interpreter_execute_node(FunctionTable* functionTable, AstNode* node);

#endif //INTERPRETER_H
