#include "ordered_list.h"

#include <stdlib.h>

OrderedListNode*
ordered_list_create_node(void* data, int(*comparer)(const void*, const void*), OrderedListNode* next){
    OrderedListNode* new_node = malloc(sizeof(OrderedListNode));
    new_node->data = data;
    new_node->comparer = comparer;
    new_node->next = next;
    return new_node;
}

OrderedListNode*
ordered_list_create(void* data, int(*comparer)(const void*, const void*)){
    return ordered_list_create_node(data, comparer, nullptr);
}

void
ordered_list_insert_into(OrderedListNode** list, void* data){
    OrderedListNode* prev_node = nullptr;
    OrderedListNode* current = *list;

    if (current == nullptr) {
        return;
    }

    if (current->data == nullptr) {
        current->data = data;
        return;
    }

    while (current != nullptr) {
        const int result = current->comparer(current->data, data);
        if (result == 1) {
            OrderedListNode* new_node = ordered_list_create_node(data, current->comparer, current);
            if (prev_node == nullptr) {
                *list = new_node;
            }
            else {
                prev_node->next = new_node;
            }

            return;
        }
        prev_node = current;
        current = current->next;
    }

    OrderedListNode* new_node = ordered_list_create_node(data, prev_node->comparer, nullptr);
    prev_node->next = new_node;
}

const OrderedListNode*
ordered_list_get(const OrderedListNode* list, const size_t index){
    size_t counter = 0;
    const OrderedListNode* current = list;
    while(current != nullptr && counter < index){
        current = current->next;
        ++counter;
    }
    return current;
}

OrderedListNode*
ordered_list_pop(OrderedListNode** list){
    OrderedListNode* top = *list;
    *list = (*list)->next;
    top->next = nullptr;
    return top;
}

void
ordered_list_destroy(OrderedListNode* list){
    while(list != nullptr){
        OrderedListNode* next = list->next;
        free(list->data);
        free(list);
        list = next;
    }
}
