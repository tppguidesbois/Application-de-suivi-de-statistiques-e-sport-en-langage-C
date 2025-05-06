CC = gcc
CFLAGS = -Wall -g
OBJS = main.o db.o joueur.o match.o
LIBS = -lsqlite3

all: projet

projet: $(OBJS)
	$(CC) -o projet $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o projet
