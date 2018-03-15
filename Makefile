CC		= gcc
VERSION = REC
CFLAGS	= -g3 -Wall
EXEC 	= elevator
OBJS 	= main.o solve.o help.o
SRCS 	= main.c solve.c help.c


.PHONY : all
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

solve.o: solve.c
	$(CC) $(CFLAGS) -D$(VERSION) -c solve.c

help.o: help.c
	$(CC) $(CFLAGS) -c help.c


.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)


.PHONY: run
run:
	./$(EXEC)


.PHONY: check
check:
	valgrind --leak-check=full ./$(EXEC)