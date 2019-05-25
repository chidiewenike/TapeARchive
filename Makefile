CC = gcc

HEADERS = mytar.h writemytar.h

SOURCES = mytar.c writemytar.c

.PHONY: clean

mytar : $(SOURCES) $(HEADERS)

	$(CC) $(CFLAGS) -o mytar $(SOURCES) -lm

clean:

	rm -f *.o *.tar test/*.tar 