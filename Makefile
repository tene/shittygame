CFLAGS := -Wall -Werror -g -ggdb -fvisibility=hidden -std=c99 -I. -ltinfo
OBJS := game.o
PROGS := game
RESOURCES := ship.edj
EDJE_CFLAGS := $(shell pkg-config --cflags edje)
EDJE_LIBS   := $(shell pkg-config --libs edje)
ECORE_CFLAGS := $(shell pkg-config --cflags ecore)
ECORE_LIBS   := $(shell pkg-config --libs ecore)
ECORE_EVAS_CFLAGS := $(shell pkg-config --cflags ecore-evas evas)
ECORE_EVAS_LIBS   := $(shell pkg-config --libs ecore-evas evas)

all: $(PROGS) $(RESOURCES)

ship.edj: ship.edc
	edje_cc ship.edc ship.edj

game.o: game.c Makefile
	gcc -c $(CFLAGS) $(ECORE_CFLAGS) $(ECORE_EVAS_CFLAGS) $(EDJE_CFLAGS) -fPIC -o game.o game.c

game: game.o
	gcc $(ECORE_LIBS) $(ECORE_EVAS_LIBS) $(EDJE_LIBS) -lm -o game game.o

clean:
	rm -f $(PROGS) $(OBJS) $(RESOURCES)
