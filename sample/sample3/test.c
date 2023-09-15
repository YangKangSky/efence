#include <stdio.h>

extern void memory_overrun();
extern void memory_calloc();
extern void memory_normal();

int main() {
    printf("Calling memory_overrun() from MemoryOverrun library...\n");
	//memory_calloc();
	memory_normal();
    //memory_overrun();
    printf("Returned from memory_overrun()\n");
    return 0;
}