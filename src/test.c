#include <stdio.h>
#include <stdlib.h>
// #include "linked_list_malloc.h"
#include "skip_list.h"
#include "arrayhehehe.c"


#include "benchmark.c"



#define SEED 12345



void main() {
    srand(123);
    printf("HAUaa!\n");
  /*  
    skip_list_t liebe;
    skip_list__init(&liebe);
    
    for (int i = 0; i < sizeof(testKeys)/sizeof(int); i++) {
        skip_list__set(&liebe, testKeys[i], i);
        printf("GET %d %d\n", testKeys[i], skip_list__get(&liebe, testKeys[i]));
    }
    */
    
    
    arrayhehehe_t list;
    arrayhehehe__init(&list);
    
    loadBenchmarkFile("benchmark.txt");
/*
    int kys[] = {5,4,3,2,1,6,7,8,9,10};
    for (int i = 0; i < 10; i++) arrayhehehe__set__fast(&list, kys[i] , i);
    for (int i = 0; i < 10; i++)   printf("%d\n",arrayhehehe__get_fast(&list,kys[i]));
    
    */




    benchmarksLala(2000,100000,1000,1000,"set.tsv");
    printf("ciao!");

}









