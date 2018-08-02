# $< 代表第一个依赖文件的名称
# $@ 代表目标文件的名称

#源文件的路径
INCLUDE = ../include
VPATH   = ../src:$(INCLUDE)

#编译
CC = gcc
CFLAGS = -std=c99 -c -lm -I$(INCLUDE) 

STATIC_LIBNAME = libaig.a

OBJ = StringHelper.o TimeHelper.o SortHelper.o SearchHelper.o ProfileHelper.o \
      PathHelper.o FileHelper.o MutexHelper.o MathHelper.o LogHelper.o ListHelper.o \
	  HashHelper.o ConsoleHelper.o ArgvHelper.o

test:$(OBJ) $(STATIC_LIBNAME)
	$(CC) -o $@ main.c $(STATIC_LIBNAME) -lm 

# 生成静态库
$(STATIC_LIBNAME):$(OBJ)
	ar rcs -o $@ $(OBJ)

%.o:%.c	  
	$(CC) $(CFLAGS) $< 

#清除
.PHONY:clean
clean:
	-rm -f prog $(OBJ) $(LIBNAME)
