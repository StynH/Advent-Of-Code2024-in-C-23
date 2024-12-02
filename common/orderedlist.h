#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H

#include <stdint.h>

typedef struct OrderedListNode{
    void* data;
    struct OrderedListNode* next;
    int (*comparer)(const void*, const void*);
} OrderedListNode;

OrderedListNode* ordered_list_create(void* data, int(*comparer)(const void*, const void*));
void ordered_list_insert_into(OrderedListNode** list, void* data);
void* ordered_list_get(const OrderedListNode* list, const uint16_t index);
void ordered_list_destroy(OrderedListNode* list);
OrderedListNode* ordered_list_pop(OrderedListNode** list);

#endif //ORDEREDLIST_H
