#ifndef LIST_ELEMENT_H
#define LIST_ELEMENT_H

#include <limits.h>

#define LIST_KEY_TYPE int

#define LIST_VALUE_TYPE int
#define LIST_VALUE_NOT_FOUND INT_MIN

// returns negative number if targetKey is after checkKey, returns positive number if checkKey is after targetKey, returns 0 if equal
#define LIST_KEY_COMPARE(targetKey, checkKey) ((targetKey) - (checkKey))

#define LIST_KEY_SENTINEL INT_MIN

typedef struct list_element {
    const LIST_KEY_TYPE key;
    LIST_VALUE_TYPE value;
} list_element_t;



#endif


