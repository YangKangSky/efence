#include <stdio.h>
//#include <malloc.h>


void test1(void)
{
    int *a = (int*)malloc(3*sizeof(int));
  
    printf("main in 1\n");
    for (int i=0;i<=2;i++) {
        a[i] = i;
        printf("%d\n", a[i]);
    }
    printf("free\n"); 

    free(a);	
	
}


//char *	allocation;
int
allocateMemory(void)
{
	char *allocation = (char *)malloc(1);

	return 0;
}

int main(void)
{
    printf("main in\n");
	test1();
	allocateMemory();
	sleep(5);
    return 0;
}
