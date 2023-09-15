CC?= cc
AR?= ar
INSTALL?= install

PIC= -fPIC
CFLAGS += -Wall -Werror $(PIC)
LDFLAGS += libMemoryOverrun.so
LIB_NAME := libMemoryOverrun.so
SRCS := test.c MemoryOverrun.c
OBJS := ${SRCS:c=o} 
#PROGS := ${SRCS:.c=}
PROGS := test 

.PHONY: $(LIB_NAME)  $(PROGS)

all: test

test: test.o $(LIB_NAME) 
	$(CC) $(CFLAGS) -o test test.c -L. -lMemoryOverrun  -lpthread 

$(LIB_NAME): MemoryOverrun.o
	$(CC) $(CFLAGS) -shared -o $(LIB_NAME) MemoryOverrun.o -lpthread 

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@
clean:
	rm -f $(LIB_NAME) $(PROGS) $(OBJS)

#LD_PRELOAD=/path/to/mylib.so ./myprogram
run:
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. LD_PRELOAD=./../../libefence.so  ./test
