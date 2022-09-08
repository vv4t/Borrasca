.PHONY = all clean run

CC = g++
CFLAGS = -Wall -g
SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp, bin/linux/obj/%.o, ${SRC})
LIBS = -lm -lglfw -lGL -lGLEW
ASSETS=$(patsubst assets/%, bin/linux/assets/%, $(wildcard assets/*/*.*))

bin/linux/Borrasca: $(OBJ) $(ASSETS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o bin/linux/Borrasca

bin/linux/obj/%.o: src/%.cpp | bin/linux/obj
	$(CC) $(CFLAGS) -c -o $@ $<

bin/linux/assets/%: assets/% | bin/linux/assets
	cp $< $@

bin/linux/obj: | bin/linux
	mkdir $@

bin/linux/assets: | bin/linux
	mkdir $@
	-mkdir $@/level
	-mkdir $@/shader
	-mkdir $@/sprite

bin/linux:
	mkdir $@

run:
	./bin/linux/Borrasca
