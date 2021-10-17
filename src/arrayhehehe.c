#define ARRAYHEHEHE_BUFFER_SIZE_INIT 1024
#include "list_element.h"
#include <string.h>

typedef struct arrayhehehe {
    list_element_t* buffer;
    int buffer_size;
    int length;
} arrayhehehe_t;


void arrayhehehe__init(arrayhehehe_t* list) {
    list->buffer_size = ARRAYHEHEHE_BUFFER_SIZE_INIT;
    list->length = 0;
    list->buffer = malloc(sizeof(list_element_t)* list->buffer_size);
}

void arrayhehehe__larger(arrayhehehe_t* list) {
    list->buffer_size *= 2;
    list->buffer = realloc(list->buffer, sizeof(list_element_t) * list->buffer_size);
    if (list->buffer == NULL) {
        printf("arrayhehehe__larger(): speicher voll (realloc(..., %d))",sizeof(list_element_t) * list->buffer_size);
        exit(1);
    }
}

LIST_VALUE_TYPE arrayhehehe__get(arrayhehehe_t* list, LIST_KEY_TYPE key) {
    for (int i = 0; i < list->length; i++) {
        int delta = LIST_KEY_COMPARE(key,list->buffer[i].key);
        if (delta == 0) return list->buffer[i].value;
        if (delta <= 0) return LIST_VALUE_NOT_FOUND;
    }
    return LIST_VALUE_NOT_FOUND;
}

LIST_VALUE_TYPE arrayhehehe__get_fast(arrayhehehe_t* list, LIST_KEY_TYPE key) {
    int iMin = 0;
    int iMax = list->length-1;
    int iOld = -1;
    int i = list->length/2;
    while (iMin <= iMax) {
        int delta = LIST_KEY_COMPARE(key,list->buffer[i].key);
        if (delta == 0) return list->buffer[i].value;
        iOld = i;
        if (delta > 0) {
            iMin = i+1;
            i = (iMin + iMax)/2;
        } else {
            iMax = i-1;
            i = (iMin + iMax)/2;
        }
    }
    return LIST_VALUE_NOT_FOUND;
}

void arrayhehehe__insertBeforeIndex(arrayhehehe_t* list, int i, LIST_KEY_TYPE key, LIST_VALUE_TYPE value)  {
//    printf("i: %d, key:%d, bef: %d, len: %d, bsize: %d\n", i, key, list->buffer[i].key, list->length, list->buffer_size);
    if ((++(list->length)) >= list->buffer_size) arrayhehehe__larger(list);
    memmove(&(list->buffer[i+1]), &(list->buffer[i]), sizeof(list_element_t) * (list->length - i));
    *((LIST_KEY_TYPE*) (&(list->buffer[i].key))) = key;
    list->buffer[i].value = value;
 //   for (int i = 0; i < 10; i++) {
 //       printf("%d ",list->buffer[i].key);
 //   }
 //   printf("\n");
}


void arrayhehehe__set(arrayhehehe_t* list, LIST_KEY_TYPE key, LIST_VALUE_TYPE value) {
    for (int i = 0; i < list->length; i++) {
        int delta = LIST_KEY_COMPARE(key,list->buffer[i].key);
        if (delta == 0) {
            list->buffer[i].value = value;
            return;
        }
        if (delta <= 0) {
            arrayhehehe__insertBeforeIndex(list,i,key,value);
            return;
        }
    }
    arrayhehehe__insertBeforeIndex(list,list->length,key,value);
    return;
}



void arrayhehehe__set__fast(arrayhehehe_t* list, LIST_KEY_TYPE key, LIST_VALUE_TYPE value) {
    if (list->length == 0) {
        arrayhehehe__insertBeforeIndex(list,0,key,value);
        return;
    }
    int iMin = 0;
    int iMax = list->length-1;
    int iOld = -1;
    int i = list->length/2;
    while (1) {
 //       printf("%d[ %d ]%d\n",iMin,i,iMax);
        if (iMin > iMax) {
            arrayhehehe__insertBeforeIndex(list,iMin,key,value);
            return;
        }
        int delta = LIST_KEY_COMPARE(key,list->buffer[i].key);
        if (delta == 0) {
            list->buffer[i].value = value;
            return;
        }
        iOld = i;
        if (delta > 0) {
            iMin = i+1;
            i = (iMin + iMax)/2;
        } else {
            iMax = i-1;
            i = (iMin + iMax)/2;
        }
    }
}
