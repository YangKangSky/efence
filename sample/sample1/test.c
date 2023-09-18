#include <stdio.h>
//#include <malloc.h>
int main(void)
{
    printf("main in\n");
    int *a = (int*)malloc(3*sizeof(int));
  
    return 0;
    printf("main in 1\n");
    for (int i=0;i<=2;i++) {
        a[i] = i;
        printf("%d\n", a[i]);
    }
    printf("free\n"); 
	sleep(10);
    free(a);
    return 0;
}
