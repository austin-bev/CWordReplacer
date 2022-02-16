CC = gcc
CFLAGS = -Wall -pedantic -ansi
OBJ = colors.o main.o output.o stringTools.o
EXEC = stringReplace

ifdef INDEX
CFLAGS += -D INDEX
INDEX : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

stringTools.o : stringTools.c stringTools.h
	$(CC) -c -g stringTools.c $(CFLAGS)

colors.o : colors.c colors.h stringTools.c stringTools.h
	$(CC) -c -g colors.c $(CFLAGS) 

output.o : output.c output.h colors.c colors.h stringTools.c stringTools.h
	$(CC) -c -g output.c $(CFLAGS)

main.o : main.c main.h colors.c colors.h output.c output.h
	$(CC) -c -g main.c $(CFLAGS) 



clean :
	rm -f $(OBJ)

clear :
	rm -f $(EXEC) $(OBJ)
