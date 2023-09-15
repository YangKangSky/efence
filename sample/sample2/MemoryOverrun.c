#include <stdio.h>
#include <stdlib.h>

void memory_normal() {
    int* ptr = (int*)malloc(sizeof(int) * 5);
    int i;
    for (i = 0; i <= 4; i++) {  // 越界访问数组，访问了 ptr[5]
        printf("%d\n", ptr[i]);
    }
	printf("free\n");
    free(ptr);
	printf("end\n");
}



void memory_overrun() {
    int* ptr = (int*)malloc(sizeof(int) * 5);
    int i;
    for (i = 0; i <= 5; i++) {  // 越界访问数组，访问了 ptr[5]
        printf("%d\n", ptr[i]);
    }
	printf("free\n");
    free(ptr);
	printf("end\n");
}


void memory_calloc() {
    int* numbers = (int*)calloc(5, sizeof(int));
    if (numbers == NULL) {
        printf("malloc faile\n");
        return;
    }

    for (int i = 0; i < 5; i++) {
        numbers[i] = i + 1;
    }
	
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    free(numbers);
}
