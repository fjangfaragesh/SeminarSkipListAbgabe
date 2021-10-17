#ifndef SKIP_LIST_H
#define SKIP_LIST_H



#include "list_element.h"

struct skip_list_node;

typedef struct skip_list_node {
    struct skip_list_node* next;
    struct skip_list_node* down;
    list_element_t* element;
} skip_list_node_t;

typedef struct skip_list {
    skip_list_node_t* sentinelTop;
    int _layers;
    int _size;
} skip_list_t;

void skip_list__init(skip_list_t* list);

LIST_VALUE_TYPE skip_list__get(skip_list_t* list, LIST_KEY_TYPE key);

void skip_list__set(skip_list_t* list, LIST_KEY_TYPE key, LIST_VALUE_TYPE value);

int skip_list__remove(skip_list_t* list, LIST_KEY_TYPE key);

int skip_list__size(skip_list_t* list);

int skip_list__layers(skip_list_t* list);

list_element_t* skip_list__get_element(skip_list_t* list, LIST_KEY_TYPE key);

int skip_list__keys(skip_list_t* list, LIST_KEY_TYPE* buffer, int bufferSize);
 

#include "skip_list.c"


#endif
