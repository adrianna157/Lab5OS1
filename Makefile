CC = gcc 
CFLAGS = -g -ggdb -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement
PROG = mystat
PROG2 = csv2bin
DEFINES = DTEST_MODE

all: $(PROG) $(PROG2)

mystat: mystat.o
	$(CC) $(CFLAGS) -o mystat mystat.o 


mystat.o: mystat.c 
	$(CC) $(CFLAGS) -c  mystat.c

csv2bin: csv2bin.o
	$(CC) $(CFLAGS) -o csv2bin csv2bin.o 


csv2bin.o: csv2bin.c 
	$(CC) $(CFLAGS) -c  csv2bin.c

clean:
	rm -f $(PROG) *.o *~ \#*