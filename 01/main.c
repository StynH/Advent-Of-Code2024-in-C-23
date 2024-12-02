#include <file_handling.h>
#include <orderedlist.h>
#include <string.h>

#define INPUT_FILE_LOCATION "files/input.txt"

int compare(const void* left, const void* right) {
    const int left_value = *((const int*)left);
    const int right_value = *((const int*)right);

    if (left_value < right_value) {
        return -1;
    }
    if (left_value > right_value) {
        return 1;
    }
    return 0;
}

int main(void) {
    const FileContext* context = read_file_into_buffer(INPUT_FILE_LOCATION);

    if (context->error_code == FILE_HANDLING_NO_ERR) {
        char* rest = context->content;
        const char* line = nullptr;

        OrderedListNode* left_list = ordered_list_create(nullptr, compare);
        OrderedListNode* right_list = ordered_list_create(nullptr, compare);

        while ((line = strtok_r(rest, "\n", &rest))) {
            int* left_number = malloc(sizeof(int));
            int* right_number = malloc(sizeof(int));
            sscanf(line, "%d   %d", left_number, right_number);

            printf("%d - %d\n", *left_number, *right_number);

            ordered_list_insert_into(&left_list, left_number);
            ordered_list_insert_into(&right_list, right_number);
        }

        int total = 0;
        while (left_list && right_list) {
            const int left = *(int*)ordered_list_pop(&left_list)->data;
            const int right = *(int*)ordered_list_pop(&right_list)->data;

            printf("%d - %d\n", left, right);

            total += abs(left - right);
        }

        printf("Total Distance: %d", total);
    }

    return 0;
}