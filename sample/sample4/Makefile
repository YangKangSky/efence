CC?= cc
AR?= ar
INSTALL?= install

PIC= -fPIC
CFLAGS += -Wall -Werror  $(PIC)
LDFLAGS +=  -Wl,--wrap,malloc -Wl,--wrap,realloc -Wl,--wrap,calloc -Wl,--wrap,free  -Wl,--whole-archive  -L./../../  -l:libefence_wrapper.a -Wl,--no-whole-archive -lpthread 

LIB_NAME = libMemoryOverrun.so
SRCS := test.c MemoryOverrun.c
OBJS := ${SRCS:c=o} 
#PROGS := ${SRCS:.c=}
PROGS := test $(LIB_NAME) 

.PHONY: $(PROGS) $(LIB_NAME)

all: $(LIB_NAME) $(PROGS) 


test: test.o $(LIB_NAME) 
	$(CC) $(CFLAGS) -o test test.o  -lpthread -L. -lMemoryOverrun 

$(LIB_NAME): MemoryOverrun.o 
	$(CC) $(CFLAGS) -shared -fPIC -o $(LIB_NAME) MemoryOverrun.o -lpthread $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@
clean:
	rm -f $(LIB_NAME) $(PROGS)  $(OBJS)

run:
	rm -rf ./libefence_wrapper.so
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./test
#LD_PRELOAD=/path/to/mylib.so ./myprogram
#LD_PRELOAD=./libefence.so ./test
