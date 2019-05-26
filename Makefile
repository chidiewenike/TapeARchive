CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
MAIN = mytar
OBJS = mytar.o parser.o list.o writemytar.o
all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

mytar.o : mytar.c mytar.h parser.o writemytar.o
	$(CC) $(CFLAGS) -c mytar.c

parser.o : parser.c parser.h list.o
    $(CC) $(CFLAGS) -c parser.c

list.o : list.c list.h
	$(CC) $(CFLAGS) -c list.c

writemytar.o : writemytar.c writemytar.h
    $(CC) $(CFLAGS) -c writemytar.c

clean :
	rm *.o *.tar test/*.tar $(MAIN)
