CC = gcc
CFLAGS = -fpic

# 库A的源文件和目标文件
A_SRC = a.c
A_OBJ = $(A_SRC:.c=.o)
A_STATIC_LIB = libA.a
A_DYNAMIC_LIB = libA.so

# 库B的源文件和目标文件
B_SRC = b.c
B_OBJ = $(B_SRC:.c=.o)
B_STATIC_LIB = libB.a
B_DYNAMIC_LIB = libB.so

# 库C的源文件和目标文件
C_SRC = c_a.c
C_OBJ = $(C_SRC:.c=.o)
C_STATIC_LIB = libC.a
C_DYNAMIC_LIB = libC.so

# 可执行文件D的源文件和目标文件
D_SRC = main.c
D_OBJ = $(D_SRC:.c=.o)
D_EXEC = D

D0_SRC = D0.c
D0_OBJ = $(D0_SRC:.c=.o)
D0_EXEC = D0


.PHONY: all clean

all: $(D_EXEC) $(D0_EXEC)

$(D_EXEC): $(A_DYNAMIC_LIB) $(B_DYNAMIC_LIB) $(D_OBJ) $(C_DYNAMIC_LIB) 
	$(CC) $(CFLAGS) main.o  -L. -lA -lB -L./../../  -l:libefence.a  -lpthread -o D

$(A_STATIC_LIB): $(A_OBJ)
	ar rcs $@ $^

$(A_DYNAMIC_LIB): $(A_OBJ)
	$(CC) $(CFLAGS) -shared $^ -o $@

$(B_STATIC_LIB): $(B_OBJ)
	ar rcs $@ $^

$(B_DYNAMIC_LIB): $(B_OBJ)
	$(CC) $(CFLAGS) -shared $^ -o $@

$(C_STATIC_LIB): $(C_OBJ)
	ar rcs $@ $^

$(C_DYNAMIC_LIB): $(C_OBJ)
	$(CC) $(CFLAGS) -shared $^ -o $@

$(A_OBJ): $(A_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(B_OBJ): $(B_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(C_OBJ): $(C_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(D_OBJ): $(D_SRC)
	echo "111"
	$(CC) $(CFLAGS) -c $< -o $@

$(D0_OBJ): $(D0_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(D0_EXEC): $(D0_OBJ)
	$(CC) $(CFLAGS) D0.o -o D0

clean:
	rm -f $(A_OBJ) $(B_OBJ) $(C_OBJ) $(D_OBJ) $(A_STATIC_LIB) $(A_DYNAMIC_LIB) $(B_STATIC_LIB) $(B_DYNAMIC_LIB) $(C_STATIC_LIB) $(C_DYNAMIC_LIB) $(D_EXEC)  $(D0_OBJ) $(D0_EXEC)
	
	
run:
	 LD_PRELOAD=./libC.so LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./D
	 
run1:
	 LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./D