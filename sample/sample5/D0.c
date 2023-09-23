#include <stdio.h>
#include <stdlib.h>

int main() {

	printf("D0 In\n");
	int* ptr = (int*)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 10;
        printf("Allocated memory in main: %d\n", *ptr);
        
        // 使用free释放内存
        free(ptr);
        printf("Freed memory in main\n");
    }
	printf("D0 Out\n");
    return 0;
}