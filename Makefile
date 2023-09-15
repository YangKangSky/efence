PIC= -fPIC
CFLAGS += -g -DUSE_SEMAPHORE $(PIC)
LIBS= -lpthread

prefix=/usr
BIN_INSTALL_DIR= $(prefix)/bin
LIB_INSTALL_DIR= $(prefix)/lib
MAN_INSTALL_DIR= $(prefix)/man/man3

CC?= cc
AR?= ar
INSTALL?= install

PACKAGE_SOURCE= README efence.3 Makefile efence.h \
	efence.c page.c print.c eftest.c tstheap.c CHANGES

OBJECTS= efence.o page.o print.o
OBJECTS_WRAPPER= efence_wrap.o page.o print.o

OBJECTS_ALL = $(OBJECTS) $(OBJECTS_WRAPPER)

TARGET_LIST = libefence.a libefence_wrapper.a libefence.so libefence_wrapper.so tstheap eftest

.PHONY: all clean sample $(SUBDIRS) $(TARGET_LIST) $(OBJECTS_ALL)

all: ${TARGET_LIST}
	make sample_build
	echo "done"

install: libefence.a efence.3 libefence.so.0.0
	$(INSTALL) -m 755 ef.sh $(BIN_INSTALL_DIR)/ef
	$(INSTALL) -m 644 libefence.a $(LIB_INSTALL_DIR)
	$(INSTALL) -m 755 libefence.so.0.0 $(LIB_INSTALL_DIR)
	- rm -f $(LIB_INSTALL_DIR)/libefence.so.0
	ln -s libefence.so.0.0 $(LIB_INSTALL_DIR)/libefence.so.0
	- rm -f $(LIB_INSTALL_DIR)/libefence.so
	ln -s libefence.so.0.0 $(LIB_INSTALL_DIR)/libefence.so
	$(INSTALL) -m 644 efence.3 $(MAN_INSTALL_DIR)/efence.3

clean: sample_clean
	- rm -f $(OBJECTS) efence_wrap.o tstheap.o eftest.o tstheap eftest \
	 libefence.a libefence_wrapper.a libefence.so libefence_wrapper.so libefence.cat ElectricFence.shar
	 make sample_clean

roff:
	nroff -man < efence.3 > efence.cat


ElectricFence.shar: $(PACKAGE_SOURCE)
	shar $(PACKAGE_SOURCE) > ElectricFence.shar

shar: ElectricFence.shar

libefence.a: $(OBJECTS)
	- rm -f libefence.a
	$(AR) crv libefence.a $(OBJECTS)

libefence.so: $(OBJECTS)
	$(CC) -g -shared -Wl,-soname,libefence.so -o libefence.so \
		$(OBJECTS) -lpthread -lc 

libefence_wrapper.a: $(OBJECTS_WRAPPER)
	- rm -f libefence_wrapper.a
	$(AR) crv libefence_wrapper.a $(OBJECTS_WRAPPER)

libefence_wrapper.so: $(OBJECTS_WRAPPER)
	$(CC) -g -shared -Wl,-soname,libefence_wrapper.so -o libefence_wrapper.so \
		$(OBJECTS_WRAPPER) -lpthread -lc 


tstheap: libefence.a tstheap.o
	- rm -f tstheap
	$(CC) $(CFLAGS) tstheap.o libefence.a -o tstheap $(LIBS)

eftest: libefence.a eftest.o
	- rm -f eftest
	$(CC) $(CFLAGS) eftest.o libefence.a -o eftest $(LIBS)

$(OBJECTS) tstheap.o eftest.o: efence.h


$(OBJECTS_ALL) : %.o : %.c
	echo "123"
	$(CC) $(CFLAGS) -c $< -o $@


SAMPLE_DIRS := $(filter $(wildcard sample/sample*), $(wildcard sample/*))


run:
	@ echo
	@ echo "Testing Electric Fence."
	@ echo "After the last test, it should print that the test has PASSED."
	./eftest
	./tstheap 3072
	@ echo
	@ echo "Electric Fence confidence test PASSED." 
	@ echo


.PHONY: $(SAMPLE_DIRS)

sample_build: $(SAMPLE_DIRS)
	
$(SAMPLE_DIRS):
	echo "1 - $(SAMPLE_DIRS)"
	$(MAKE) -C $@

sample_clean:
	for dir in $(SAMPLE_DIRS); do \
		$(MAKE) -C $$dir clean; \
	done
