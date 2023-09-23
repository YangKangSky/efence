#include "c_a.h"
#include <stdio.h>






void functionA_0() {
    // 使用malloc分配内存
    double* arr = (double*)malloc(5 * sizeof(double));
    if (arr != NULL) {
        for (int i = 0; i < 5; i++) {
            arr[i] = i + 1.5;
        }
        
        printf("Allocated memory in functionA_0 C: ");
        for (int i = 0; i < 5; i++) {
            printf("%.2f ", arr[i]);
        }
        printf("\n");
        
        // 使用free释放内存
        free(arr);
        printf("Freed memory in functionA_0 C\n");
    }
}