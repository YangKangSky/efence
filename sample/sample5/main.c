#include "a.h"
#include "b.h"

int main() {
    // D的实现依赖于库B和库C

    functionA();
	functionA_0();
    functionB();
	
	
	int* ptr = (int*)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 10;
        printf("Allocated memory in main: %d\n", *ptr);
        
        // 使用free释放内存
        free(ptr);
        printf("Freed memory in main\n");
    }
	
	printf("-------------D0 Run--------------------\n");
	system("./D0");
	printf("-------------D0 Done--------------------\n");
    return 0;
}