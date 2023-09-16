CC?= cc
AR?= ar
INSTALL?= install


PIC= -fPIC
CFLAGS += -g -DUSE_SEMAPHORE $(PIC)
LDFLAGS += -lpthread -lc

prefix=/usr
BIN_INSTALL_DIR= $(prefix)/bin
LIB_INSTALL_DIR= $(prefix)/lib
MAN_INSTALL_DIR= $(prefix)/man/man3


SRCS := test.c
OBJS := ${SRCS:c=o} 
#PROGS := ${SRCS:.c=}
PROGS := eftest_static eftest_share

.PHONY: all $(OBJS) $(PROGS)

all: $(OBJS) $(PROGS)
	echo "done"

eftest_static: test.o
	- rm -f eftest
	$(CC) $(CFLAGS) -o eftest_static test.o ../../libefence.a $(LDFLAGS)

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


