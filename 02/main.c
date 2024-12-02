#include <file_handling.h>
#include <math.h>
#include <ordered_list.h>
#include <string.h>
#include <vector.h>

#define INPUT_FILE_LOCATION "files/input.txt"
#define MAX_CHANGE 3

bool
same_sign(const int left, const int right) {
    return left * right > 0;
}

void
part_one(const FileContext* context) {
    char* rest = strdup(context->content);
    char* line;

    int total = 0;
    while ((line = strtok_r(rest, "\n", &rest))) {
        char* token;
        int prev = INT_MIN;
        bool safe = true;
        int first_diff = 0;
        while ((token = strtok_r(line, " ", &line))) {
            char* end;
            const int num = strtol(token, &end, 10);
            if (prev == INT_MIN) {
                prev = num;
                continue;
            }

            const int diff = prev - num;
            if (first_diff == 0) {
                first_diff = diff;
            }

            if (
                diff == 0 ||
                abs(diff) > MAX_CHANGE ||
                !same_sign(first_diff, diff)
            ) {
                safe = false;
                break;
            }
            prev = num;
        }

        if (safe) {
            ++total;
        }
    }

    printf("Total Safe: %d\n", total);
}

void
part_two(const FileContext* context) {
    char* rest = strdup(context->content);
    char* line;

    int total = 0;
    while ((line = strtok_r(rest, "\n", &rest))) {
        char* token;
        Vector* line_vector = vector_create();
        while ((token = strtok_r(line, " ", &line))) {
            char* end;
            int* num = malloc(sizeof(int));
            *num = strtol(token, &end, 10);
            vector_insert_into(line_vector, num);
        }

        bool sequence_safe = false;
        bool original_safe = true;
        int prev = INT_MIN;
        int first_diff = 0;

        for (size_t i = 0; i < line_vector->length && original_safe; ++i) {
            const int curr = *(int*)vector_element_at(line_vector, i);
            if (prev == INT_MIN) {
                prev = curr;
                continue;
            }

            const int diff = curr - prev;
            if (first_diff == 0) {
                first_diff = diff;
            }

            if (
                diff != 0 ||
                abs(diff) < MAX_CHANGE ||
                same_sign(first_diff, diff)
            ) {
                original_safe = false;
            }
            prev = curr;
        }

        if (!original_safe) {
            for (size_t skip = 0; skip < line_vector->length && !sequence_safe; ++skip) {
                bool try_safe = true;
                prev = INT_MIN;
                first_diff = 0;

                for (size_t i = 0; i < line_vector->length && try_safe; ++i) {
                    if (i == skip) continue;

                    const int curr = *(int*)vector_element_at(line_vector, i);
                    if (prev == INT_MIN) {
                        prev = curr;
                        continue;
                    }

                    const int diff = curr - prev;
                    if (first_diff == 0) {
                        first_diff = diff;
                    }

                    if (
                        diff == 0 ||
                        abs(diff) > MAX_CHANGE ||
                        !same_sign(first_diff, diff)
                    ) {
                        try_safe = false;
                    }

                    prev = curr;
                }

                if (try_safe) {
                    sequence_safe = true;
                }
            }
        }

        if (original_safe || sequence_safe) {
            ++total;
        }

        vector_destroy(line_vector);
    }

    printf("Total Safe with Dampening: %d\n", total);
}

int
main(void) {
    printf("Running day 2 of Advent of Code 2024...\n");
    const FileContext* context = read_file_into_buffer(INPUT_FILE_LOCATION);

    if (context->error_code == FILE_HANDLING_NO_ERR) {
        part_one(context);
        part_two(context);
    }
    else {
        printf("Failed to open file '%s', Error Code: %d", INPUT_FILE_LOCATION, context->error_code);
    }

    return 0;
}
