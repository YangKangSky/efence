CC?= cc
AR?= ar
INSTALL?= install


PIC= -fPIC
CFLAGS += -g -O0 -ggdb -DUSE_SEMAPHORE $(PIC) -I../../
LDFLAGS += -lpthread  -lc

WRAPPER_LDFLAGS +=  -Wl,--wrap,malloc -Wl,--wrap,realloc -Wl,--wrap,calloc -Wl,--wrap,free  -Wl,--whole-archive  -L./../../  -l:libefence_wrapper.a -Wl,--no-whole-archive -lpthread 

prefix=/usr
BIN_INSTALL_DIR= $(prefix)/bin
LIB_INSTALL_DIR= $(prefix)/lib
MAN_INSTALL_DIR= $(prefix)/man/man3


SRCS := test.c
OBJS := ${SRCS:c=o} 
#PROGS := ${SRCS:.c=}
PROGS := eftest_static eftest_wrapper_static eftest_share

.PHONY: all $(OBJS) $(PROGS)

all: $(OBJS) $(PROGS)
	echo "done"

eftest_static: test.o
	- rm -f eftest
	$(CC) $(CFLAGS) -o eftest_static test.o ../../libefence.a $(LDFLAGS)
	#$(CC) $(CFLAGS) test.o -L./../../ -l:libefence.a  $(LDFLAGS) -o eftest_static


eftest_wrapper_static: test.o
	- rm -f eftest
	$(CC) $(CFLAGS) -o eftest_wrapper_static test.o  $(WRAPPER_LDFLAGS) $(LDFLAGS)
	#$(CC) $(CFLAGS) test.o -L./../../ -l:libefence.a  $(LDFLAGS) -o eftest_static


eftest_share:  test.o
	- rm -f eftest
	$(CC) $(CFLAGS) -o eftest_share test.c -L./../../ -lefence  $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

test.o: test.c
	$(CC) $(CFLAGS)  -c $< -o $@
	

clean:
	rm -rf eftest_static eftest_share test.o

#./eftest_static 
#LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../  ./eftest_share 
run:
	-./eftest_static 
	-LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../  ./eftest_share 


