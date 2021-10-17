// included by test.c

#include <time.h>
// #include "hashmap/hashmap.h"
// #include "hashmap/hashmap.c"


int keysPrepare[16777216];
int keysPrepareC = 0;
int keysSet[16777216];
int keysSetC = 0;
int keysGet[16777216];
int keysGetC = 0;
int keysRemove[16777216];
int keysRemoveC = 0;

/*
void benchmarkPrepareList(arrayhehehe_t* list, int n) {
    for (int i = 0; i < n; i++) {
        arrayhehehe__set__fast(list, keysPrepare[i], i);
    }
}


clock_t benchmarkLala(int n, int m) {
    clock_t tStart, tEnd;
    arrayhehehe_t list;
    arrayhehehe__init(&list);
    benchmarkPrepareList(&list,n);
    
    tStart = clock();
    int dummy = 0;
    for (int i = 0; i < m; i++) {
        //hier die zu testende function eingeben:
        arrayhehehe__set(&list, keysGet[i],i);
    }
    tEnd = clock();
    
    printf("benchmark:set:%d = %d;   dummy=%d\n",n,tEnd-tStart,dummy);
    
    //TODO dispose
    
    return tEnd-tStart;
}*/

void benchmarkPrepareList(skip_list_t* list, int n) {
    for (int i = 0; i < n; i++) {
        skip_list__set(list, keysPrepare[i], i);
    }
}
/*
int hashmpcmp(const void* a, const void* b, void* keineAhnung) {
    return (int)b - (int)a;
}

uint64_t  hashfnkt(const void* item, uint64_t seed0, uint64_t seed1) {
    return (int)item;
}*/

//int nLayers = -1;
clock_t benchmarkLala(int n, int m) {
    clock_t tStart, tEnd;
    skip_list_t list;
    skip_list__init(&list);
    //struct hashmap* map = hashmap_new(sizeof(int), 0,0,0,hashfnkt,hashmpcmp, NULL);
    benchmarkPrepareList(&list,n);
    
    tStart = clock();
    int dummy = 0;
    for (int i = 0; i < m; i++) {
        //hier die zu testende function eingeben:
        dummy += skip_list__get(&list, keysGet[i]);
    }
    tEnd = clock();
    
    printf("benchmark:set:%d = %d;   dummy=%d\n",n,tEnd-tStart,dummy);
    nLayers = list._layers;
    //TODO dispose
    
    return tEnd-tStart;
}


void benchmarksLala(int nMin, int nMax, int nStep, int m, char* fname) {
    FILE* f = fopen( fname, "w");
    for (int i = nMin; i <= nMax; i += nStep) {
        fprintf(f,"%d\t%d\t%d\n",i,benchmarkLala(i,m));
    }
    fclose(f);
}



void loadBenchmarkFile(char* fName) {
    printf("benchmark datei wird geladen...\n");
    FILE* f = fopen( fName, "r");
    int i = 0;
    printf("benchmark keysPrepare wird geladen...\n");
    while (1) {
        if (!fscanf(f,"%d",&(keysPrepare[i]))) break;
        i++;
    }
    keysPrepareC = i;
    
    
    
    fscanf(f,"next");
    i = 0;
    printf("benchmark keysSet wird geladen...\n");
    while (1) {
        if (!fscanf(f,"%d",&(keysSet[i]))) break;
        i++;
    }
    keysSetC = i;
    
    
    fscanf(f,"next");
    i = 0;
    printf("benchmark keysGet wird geladen...\n");
    while (1) {
        if (!fscanf(f,"%d",&(keysGet[i]))) break;
        i++;
    }
    keysGetC = i;
    
    
    fscanf(f,"next");
    i = 0;
    printf("benchmark keysRemove wird geladen...\n");
    while (1) {
        if (!fscanf(f,"%d",&(keysRemove[i]))) break;
        i++;
    }
    keysRemoveC = i;
    printf("benchmark wurde geladen\n");
}

