#include "lexer.h"
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LENGTH 256

bool is_allowed_char(char c) {
    return (c >= 33 && c <= 47)
           || (c >= 58 && c <= 64)
           || (c >= 91 && c <= 96)
           || (c >= 123 && c <= 126);
}

Vector* lexer_tokenize(const char *source) {
    Vector* token_vector = vector_create();
    char current_token[MAX_WORD_LENGTH];
    int token_index = 0;
    bool in_word = false;
    bool in_number = false;

    for (int i = 0; source[i] != '\0'; i++) {
        const char c = source[i];

        //To make "don't" work.
        //Who needs Regex?
        if (c == '\'' && source[i + 1] == 't' && source[i + 2] != '\0' &&
            !isalpha(source[i + 2]) && in_word) {
            current_token[token_index++] = '\'';
            current_token[token_index++] = 't';
            current_token[token_index] = '\0';

            vector_insert_into(token_vector, strdup(current_token));
            token_index = 0;
            in_word = false;
            in_number = false;
            i++;
            continue;
        }

        if (is_allowed_char(c) || (c == '\'' && !in_word)) {
            if (token_index > 0) {
                current_token[token_index] = '\0';
                vector_insert_into(token_vector, strdup(current_token));
                token_index = 0;
            }

            const char special_token[2] = {c, '\0'};
            vector_insert_into(token_vector, strdup(special_token));

            in_word = false;
            in_number = false;
            continue;
        }

        if (isalpha(c)) {
            if (in_number) {
                current_token[token_index] = '\0';
                vector_insert_into(token_vector, strdup(current_token));
                token_index = 0;
            }
            current_token[token_index++] = c;
            in_word = true;
            in_number = false;
        }
        else if (isdigit(c)) {
            if (in_word) {
                current_token[token_index] = '\0';
                vector_insert_into(token_vector, strdup(current_token));
                token_index = 0;
            }
            current_token[token_index++] = c;
            in_number = true;
            in_word = false;
        }
    }

    if (token_index > 0) {
        current_token[token_index] = '\0';
        vector_insert_into(token_vector, strdup(current_token));
    }

    return token_vector;
}
