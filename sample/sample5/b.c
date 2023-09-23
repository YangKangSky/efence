#include "b.h"
#include <stdio.h>

void functionB() {
    // 使用malloc分配内存
    char* str = (char*)malloc(10 * sizeof(char));
    if (str != NULL) {
        sprintf(str, "Library B");
        printf("Allocated memory in functionB: %s\n", str);
        
        // 使用free释放内存
        free(str);
        printf("Freed memory in functionB\n");
    }
}