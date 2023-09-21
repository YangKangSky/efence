CC?= cc
AR?= ar
INSTALL?= install

PIC= -fPIC
CFLAGS += -O0 -g -ggdb -Wall -Werror $(PIC)
#LDFLAGS += libMemoryOverrun.so
LIB_NAME := libMemoryOverrun.so
WRAPPER_LIB_NAME := libMemoryOverrun_wrap.so

#WRAPPER_LDFLAGS += libMemoryOverrun_wrap.so
WRAPPER_LDFLAGS :=  -Wl,--wrap,malloc -Wl,--wrap,realloc -Wl,--wrap,calloc -Wl,--wrap,free -lpthread  -L./../../ -lefence_wrapper
WRAPPER_LIB_NAME := libMemoryOverrun_wrap.so

SRCS := test.c MemoryOverrun.c
OBJS := ${SRCS:c=o} 
#PROGS := ${SRCS:.c=}
PROGS := s2_test  s2_test_wrapper_share

.PHONY:  $(PROGS) $(LIB_NAME) $(WRAPPER_LIB_NAME)

all: s2_test  s2_test_wrapper_share

s2_test: test.o $(LIB_NAME) 
	$(CC) $(CFLAGS) -o s2_test test.c -L. -lMemoryOverrun  -lpthread 

s2_test_wrapper_share: test.o $(WRAPPER_LIB_NAME) 
	$(CC) $(CFLAGS) -o s2_test_wrapper_share test.c -L. -lMemoryOverrun_wrap  -lpthread  $(LDFLAGS)

$(LIB_NAME): MemoryOverrun.o
	$(CC) $(CFLAGS) -shared -o $(LIB_NAME) MemoryOverrun.o -lpthread 

$(WRAPPER_LIB_NAME): MemoryOverrun.o
	$(CC) $(CFLAGS) -shared -fPIC -o $(WRAPPER_LIB_NAME) MemoryOverrun.o -lpthread $(WRAPPER_LDFLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@
clean:
	rm -f $(LIB_NAME) $(WRAPPER_LIB_NAME) $(PROGS) $(OBJS)

#LD_PRELOAD=/path/to/mylib.so ./myprogram
run:
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. LD_PRELOAD=./../../libefence.so  ./test
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./s2_test_wrapper_share
