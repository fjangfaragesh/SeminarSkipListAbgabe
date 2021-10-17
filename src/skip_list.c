#include <stdlib.h>


/*
skip_list_node_t* skip_list__newNode() {
    skip_list_node_t* ret = malloc(sizeof(skip_list_node_t));
    if (ret == NULL) {
        printf("Speicher voll\n");
        exit(1);
    }
    return ret;
}

list_element_t* skip_list__newElement(LIST_KEY_TYPE key) {
    list_element_t* el = malloc(sizeof(list_element_t));
    if (el == NULL) {
        printf("Speicher voll\n");
        exit(1);
    }
    // Pointer Magie: ganz einfach: el->key ist Konstant, aber ich will rein schreiben:
    // Addresse ermitteln, pointer zu nicht konstantem casten, dereferenzieren, rein schreiben
    *((LIST_KEY_TYPE*)(&(el->key))) = key;
    return el;
}
*/




list_element_t skip_list__element_buffer[16777216];
int skip_list__element_buffer_pos = 0;
skip_list_node_t skip_list__node_buffer[16777216];
int skip_list__node_buffer_pos = 0;

skip_list_node_t* skip_list__newNode() {
    return &(skip_list__node_buffer[skip_list__node_buffer_pos++]);
}
list_element_t* skip_list__newElement(LIST_KEY_TYPE key) {
    list_element_t* el = &(skip_list__element_buffer[skip_list__element_buffer_pos++]);
    *((LIST_KEY_TYPE*)(&(el->key))) = key; // Pointer Magie: ganz einfach: el->key ist Konstant, aber ich will rein schreiben.
    return el;
}


void skip_list__init(skip_list_t* list) {
    list_element_t* se = skip_list__newElement(LIST_KEY_SENTINEL);
    
    list->sentinelTop = skip_list__newNode();
    list->sentinelTop->next = NULL;
    list->sentinelTop->down = NULL;
    
    list->sentinelTop->element = se;
    list->_size = 0;
    list->_layers = 1;
}

list_element_t* skip_list__get_element(skip_list_t* list, LIST_KEY_TYPE key) {
    skip_list_node_t* before = list->sentinelTop;
    skip_list_node_t* current = before->next;
    int delta;
    while (1) {
        delta = current == NULL ? -1 : LIST_KEY_COMPARE(key, current->element->key);
        if (delta == 0) return current->element;
        if (delta > 0) {
            // keep on this layer
            before = current;
            current = current->next;
        } else {
            // back, layer down, next
            current = before->down;
            if (current == NULL) return NULL; //layer down not possible
            before = current;
            current = current->next;
        }
    }
}

LIST_VALUE_TYPE skip_list__get(skip_list_t* list, LIST_KEY_TYPE key) {
    list_element_t* el = skip_list__get_element(list, key);
    if (el == NULL) return LIST_VALUE_NOT_FOUND;
    return el->value;
}


// TODO multithread?????
skip_list_node_t** skip_list__overshootStack;
int skip_list__overshootStackMaxSize = 1024;

void skip_list__overshoot_init() {
    skip_list__overshootStack = malloc(sizeof(skip_list_node_t*) * skip_list__overshootStackMaxSize);
    if (skip_list__overshootStack == NULL) {
        printf("Speicher voll\n");
        exit(1);
    }
}
void skip_list__overshoot_larger() {
    skip_list__overshootStackMaxSize *= 2;
    skip_list__overshootStack = realloc(skip_list__overshootStack, sizeof(skip_list_node_t*) * skip_list__overshootStackMaxSize);
    if (skip_list__overshootStack == NULL) {
        printf("Speicher voll\n");
        exit(1);
    }
}


void skip_list__set(skip_list_t* list, LIST_KEY_TYPE key, LIST_VALUE_TYPE value) {
    if (skip_list__overshootStack == NULL) skip_list__overshoot_init();
    
    
    int overshootStackCounter = 0;
    
    skip_list_node_t* before = list->sentinelTop;
    skip_list_node_t* current = before->next;
    int delta;
        
    while (1) {
        delta = current == NULL ? -1 : LIST_KEY_COMPARE(key, current->element->key);
        if (delta == 0) {
            current->element->value = value;
            return;
        }
        if (delta > 0) {
            // keep on this layer
            before = current;
            current = current->next;
        } else {
            // back, layer down, next
            
            if (overshootStackCounter >= skip_list__overshootStackMaxSize) skip_list__overshoot_larger();
            
            skip_list__overshootStack[overshootStackCounter++] = before;
            current = before->down;
            before = current;
            if (current == NULL) {
                // neues element dazwischen schieben
                skip_list_node_t* newNode;
                skip_list_node_t* newNodeBefore = NULL;
                list_element_t* el = skip_list__newElement(key);
                el->value = value;
                do {
                    skip_list_node_t* newNode = skip_list__newNode();
                    newNode->element = el;
                    newNode->down = newNodeBefore;
                    if (overshootStackCounter == 0) {
                        // neuer Layer erstellen
                        skip_list_node_t* newSentinelTop = skip_list__newNode();
                        newSentinelTop->down = list->sentinelTop;
                        newSentinelTop->next = newNode;
                        newSentinelTop->element = list->sentinelTop->element;
                        
                        list->sentinelTop = newSentinelTop;
                        
                        newNode->next = NULL;
                        
                        list->_layers++;
                    } else {
                        // knoten auf aktueller Schicht neu verbinden
                        overshootStackCounter--;
                        newNode->next = skip_list__overshootStack[overshootStackCounter]->next;
                        skip_list__overshootStack[overshootStackCounter]->next = newNode;
                        
                    }
                    newNodeBefore = newNode;
                } while (rand() & 1);//50% probabilidy
                list->_size++;
                return;
            }
            

            skip_list__overshootStack[overshootStackCounter++] = before;
            before = current;
            current = current->next;
        }
    }
}


int skip_list__size(skip_list_t* list) {
    return list->_size;
}


int skip_list__layers(skip_list_t* list) {
    return list->_layers;
}






























