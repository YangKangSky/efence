CC = gcc
CFLAGS = -Wall -Werror

LIB_NAME = libMemoryOverrun.so

.PHONY: $(LIB_NAME) 

all: test

LDFLAGS +=  -Wl,--wrap,malloc -Wl,--wrap,realloc -Wl,--wrap,calloc -Wl,--wrap,free  -Wl,--whole-archive  -L./../../  -l:libefence_wrapper.a -Wl,--no-whole-archive -lpthread 

test: test.c $(LIB_NAME) 
	$(CC) $(CFLAGS) -o test test.c  -lpthread -L. -lMemoryOverrun 

$(LIB_NAME): MemoryOverrun.c 
	$(CC) $(CFLAGS) -shared -fPIC -o $(LIB_NAME) MemoryOverrun.c -lpthread $(LDFLAGS)

clean:
	rm -f $(LIB_NAME) test 

run:
	rm -rf ./libefence_wrapper.so
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./test
#LD_PRELOAD=/path/to/mylib.so ./myprogram
#LD_PRELOAD=./libefence.so ./test