CC?= cc
AR?= ar
INSTALL?= install


PIC= -fPIC
CFLAGS += -g -O0 -ggdb -DUSE_SEMAPHORE $(PIC) -I../../
LDFLAGS += -lpthread  -lc

WRAPPER_LDFLAGS +=  -Wl,--wrap,malloc -Wl,--wrap,realloc -Wl,--wrap,calloc -Wl,--wrap,free  -Wl,--whole-archive  -L./../../  -l:libefence_wrapper.a -Wl,--no-whole-archive -lpthread 

WRAPPER_SHARED_LDFLAGS +=  -Wl,--wrap,malloc -Wl,--wrap,realloc -Wl,--wrap,calloc -Wl,--wrap,free  -Wl,--whole-archive  -L./../../  -lefence_wrapper -Wl,--no-whole-archive -lpthread 




prefix=/usr
BIN_INSTALL_DIR= $(prefix)/bin
LIB_INSTALL_DIR= $(prefix)/lib
MAN_INSTALL_DIR= $(prefix)/man/man3


SRCS := test.c
OBJS := ${SRCS:c=o} 
#PROGS := ${SRCS:.c=}
PROGS := s1_eftest_static s1_eftest_wrapper_static s1_eftest_share s1_eftest_wrapper_share

.PHONY: all $(OBJS) $(PROGS)

all: $(OBJS) $(PROGS)
	echo "done"

s1_eftest_static: test.o
	- rm -f eftest
	$(CC) $(CFLAGS) -o s1_eftest_static test.o ../../libefence.a $(LDFLAGS)
	#$(CC) $(CFLAGS) test.o -L./../../ -l:libefence.a  $(LDFLAGS) -o s1_eftest_static


s1_eftest_wrapper_static: test.o
	- rm -f eftest
	$(CC) $(CFLAGS) -o s1_eftest_wrapper_static test.o  $(WRAPPER_LDFLAGS) $(LDFLAGS)
	#$(CC) $(CFLAGS) test.o -L./../../ -l:libefence.a  $(LDFLAGS) -o eftest_static

s1_eftest_wrapper_share: test.o
	- rm -f eftest
	$(CC) $(CFLAGS) -o s1_eftest_wrapper_share test.o  $(WRAPPER_SHARED_LDFLAGS) $(LDFLAGS)
	#$(CC) $(CFLAGS) test.o -L./../../ -lefence $(LDFLAGS) -o eftest_static




s1_eftest_share:  test.o
	- rm -f eftest
	$(CC) $(CFLAGS) -o s1_eftest_share test.c -L./../../ -lefence  $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

test.o: test.c
	$(CC) $(CFLAGS)  -c $< -o $@
	

clean:
	rm -rf  $(PROGS) test.o

#./eftest_static 
#LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../  ./eftest_share 
run:
	-./s1_eftest_static 
	-LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../  ./eftest_share 


