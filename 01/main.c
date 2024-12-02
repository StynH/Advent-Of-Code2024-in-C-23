#include <file_handling.h>
#include <ordered_list.h>
#include <string.h>

#define INPUT_FILE_LOCATION "files/input.txt"

int
compare(const void* left, const void* right) {
    const int left_value = *(const int*)left;
    const int right_value = *(const int*)right;

    if (left_value < right_value) {
        return -1;
    }
    if (left_value > right_value) {
        return 1;
    }
    return 0;
}

void
part_one(const FileContext* context) {
    char* rest = strdup(context->content);
    const char* line;

    OrderedListNode* left_list = ordered_list_create(nullptr, compare);
    OrderedListNode* right_list = ordered_list_create(nullptr, compare);

    while ((line = strtok_r(rest, "\n", &rest))) {
        int* left_number = malloc(sizeof(int));
        int* right_number = malloc(sizeof(int));

        sscanf_s(line, "%d   %d", left_number, right_number);

        ordered_list_insert_into(&left_list, left_number);
        ordered_list_insert_into(&right_list, right_number);
    }

    int total = 0;
    while (left_list && right_list) {
        const int left = *(int*)ordered_list_pop(&left_list)->data;
        const int right = *(int*)ordered_list_pop(&right_list)->data;

        total += abs(left - right);
    }

    printf("Total Distance: %d\n", total);
}

void
part_two(const FileContext* context) {
    char* rest = strdup(context->content);
    const char* line;

    OrderedListNode* left_list = ordered_list_create(nullptr, compare);
    OrderedListNode* right_list = ordered_list_create(nullptr, compare);

    while ((line = strtok_r(rest, "\n", &rest))) {
        int* left_number = malloc(sizeof(int));
        int* right_number = malloc(sizeof(int));

        sscanf_s(line, "%d   %d", left_number, right_number);

        ordered_list_insert_into(&left_list, left_number);
        ordered_list_insert_into(&right_list, right_number);
    }

    int total = 0;
    while (left_list) {
        const int left = *(int*)ordered_list_pop(&left_list)->data;
        int subtotal = 0;
        int index = 0;

        int value = -1;
        while (value <= left) {
            const OrderedListNode* node = ordered_list_get(right_list, index);
            if (node == nullptr) {
                break;
            }

            value = *(int*)node->data;
            if (value == left) {
                ++subtotal;
            }
            ++index;
        }

        total += left * subtotal;
    }

    printf("Total Similarity: %d\n", total);
}

int
main(void) {
    printf("Running day 1 of Advent of Code 2024...\n");
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