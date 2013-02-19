CFLAGS := -Wall -Werror -g -ggdb -fvisibility=hidden -std=c99 -I. -ltinfo
OBJS := game.o
PROGS := game
ECORE_CFLAGS := $(shell pkg-config --cflags ecore)
ECORE_LIBS   := $(shell pkg-config --libs ecore)
ECORE_EVAS_CFLAGS := $(shell pkg-config --cflags ecore-evas)
ECORE_EVAS_LIBS   := $(shell pkg-config --libs ecore-evas)

all: $(PROGS)

game.o: game.c Makefile
	gcc -c $(CFLAGS) $(ECORE_CFLAGS) $(ECORE_EVAS_CFLAGS) -fPIC -o game.o game.c

game: game.o
	gcc $(ECORE_LIBS) $(ECORE_EVAS_LIBS) -o game game.o

clean:
	rm -f $(PROGS) $(OBJS)
