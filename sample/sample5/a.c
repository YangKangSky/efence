#include "a.h"
#include <stdio.h>

void functionA() {
    // 使用malloc分配内存
    int* ptr = (int*)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 10;
        printf("Allocated memory in functionA: %d\n", *ptr);
        
        // 使用free释放内存
        free(ptr);
        printf("Freed memory in functionA\n");
    }
}

void functionA_0() {
    // 使用malloc分配内存
    int* ptr = (int*)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 10;
        printf("Allocated memory in functionA_0: %d\n", *ptr);
        
        // 使用free释放内存
        free(ptr);
        printf("Freed memory in functionA_0\n");
    }
}