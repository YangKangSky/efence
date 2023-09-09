CC?= cc
AR?= ar
INSTALL?= install

CFLAGS = -Wall -Werror
LIB_NAME = libMemoryOverrun.so

.PHONY: $(LIB_NAME) 

all: test

test: test.c $(LIB_NAME) 
	$(CC) $(CFLAGS) -o test test.c -L. -lMemoryOverrun  -lpthread 

$(LIB_NAME): MemoryOverrun.c 
	$(CC) $(CFLAGS) -shared -fPIC -o $(LIB_NAME) MemoryOverrun.c -lpthread $(LDFLAGS)

clean:
	rm -f $(LIB_NAME) test 

#LD_PRELOAD=/path/to/mylib.so ./myprogram
run:
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. LD_PRELOAD=./../../libefence.so.0.0  ./test