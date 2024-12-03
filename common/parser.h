#ifndef PARSER_H
#define PARSER_H

#include "interpreter.h"
#include "vector.h"

Vector* parser_parse(FunctionTable* function_table, Vector* token_vector);

#endif //PARSER_H
