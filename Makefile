CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
MAIN = mytar
OBJS = mytar.o parser.o list.o
all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

mytar.o : mytar.c mytar.h
	$(CC) $(CFLAGS) -c mytar.c

parser.o : parser.c parser.h
    $(CC) $(CFLAGS) -c parser.c

list.o : list.c list.h
	$(CC) $(CFLAGS) -c list.c

clean :
	rm *.o $(MAIN)
