# Variables
CC=cc68x
CFLAGS=-g
GRAPHICSDRIVER_SRC=graphi~1.c
GRAPHICSDRIVER_OBJ=graphi~1.o
MODELDRIVER_SRC=modelt~1.c
MODELDRIVER_OBJ=modelt~1.o
RENDERERDRIVER_SRC=render~1.c
RENDERERDRIVER_OBJ=render~1.o
DEFENDERGAME_SRC=defend~1.c
DEFENDERGAME_OBJ=defend~1.o
SOUNDDRIVER_SRC=soundd~1.c
SOUNDDRIVER_OBJ=soundd~1.o

# All targets
all: graphi~1.tos modelt~1.tos render~1.tos defend~1.tos #soundd~1.tos

# Compile graphicsTestDriver program
graphi~1.tos: $(GRAPHICSDRIVER_OBJ) bitmap.o raster.o renderer.o model.o events.o psg.o helper.o
	$(CC) $(CFLAGS) $(GRAPHICSDRIVER_OBJ) bitmap.o raster.o renderer.o model.o events.o psg.o helper.o -o graphi~1.tos

$(GRAPHICSDRIVER_OBJ): $(GRAPHICSDRIVER_SRC) bitmap.h raster.h renderer.h model.h events.h defs.h psg.h helper.h
	$(CC) $(CFLAGS) -c $(GRAPHICSDRIVER_SRC)

# Compile modelTestDriver program
modelt~1.tos: $(MODELDRIVER_OBJ) bitmap.o raster.o renderer.o model.o events.o psg.o music.o helper.o
	$(CC) $(CFLAGS) $(MODELDRIVER_OBJ) bitmap.o raster.o renderer.o model.o events.o psg.o music.o helper.o -o modelt~1.tos

$(MODELDRIVER_OBJ): $(MODELDRIVER_SRC) bitmap.h raster.h renderer.h model.h events.h defs.h psg.h music.h helper.h
	$(CC) $(CFLAGS) -c $(MODELDRIVER_SRC)

# Compile rendererTestDriver program
render~1.tos: $(RENDERERDRIVER_OBJ) bitmap.o raster.o renderer.o model.o events.o psg.o music.o helper.o
	$(CC) $(CFLAGS) $(RENDERERDRIVER_OBJ) bitmap.o raster.o renderer.o model.o events.o psg.o music.o helper.o -o render~1.tos

$(RENDERERDRIVER_OBJ): $(RENDERERDRIVER_SRC) bitmap.h raster.h renderer.h model.h events.h defs.h psg.h music.h helper.h
	$(CC) $(CFLAGS) -c $(RENDERERDRIVER_SRC)

# Compile defender game
defend~1.tos: $(DEFENDERGAME_OBJ) bitmap.o raster.o renderer.o model.o events.o psg.o input.o music.o helper.o
	$(CC) $(CFLAGS) $(DEFENDERGAME_OBJ) bitmap.o raster.o renderer.o model.o events.o psg.o input.o music.o helper.o -o defend~1.tos

$(DEFENDERGAME_OBJ): $(DEFENDERGAME_SRC) bitmap.h raster.h renderer.h model.h events.h defs.h psg.h input.h music.h helper.h
	$(CC) $(CFLAGS) -c $(DEFENDERGAME_SRC)

# Compile soundDriver program
#soundd~1.tos: $(SOUNDDRIVER_OBJ) psg.o music.o effects.o helper.o
#	$(CC) $(CFLAGS) $(SOUNDDRIVER_OBJ) psg.o music.o effects.o helper.o -o soundd~1.tos

#$(SOUNDDRIVER_OBJ): $(SOUNDDRIVER_SRC) psg.h music.h effects.h helper.h
#	$(CC) $(CFLAGS) -c $(SOUNDDRIVER_SRC)

input.o: input.c input.h 
	$(CC) $(CFLAGS) -c input.c

helper.o: helper.c helper.h
	$(CC) $(CFLAGS) -c helper.c

# Other object files
bitmap.o: bitmap.c bitmap.h
	$(CC) $(CFLAGS) -c bitmap.c

raster.o: raster.c raster.h
	$(CC) $(CFLAGS) -c raster.c

renderer.o: renderer.c renderer.h
	$(CC) $(CFLAGS) -c renderer.c

model.o: model.c model.h
	$(CC) $(CFLAGS) -c model.c

events.o: events.c events.h
	$(CC) $(CFLAGS) -c events.c

psg.o: psg.c psg.h
	$(CC) $(CFLAGS) -c psg.c

effects.o: effects.c effects.h
	$(CC) $(CFLAGS) -c effects.c

music.o: music.c music.h
	$(CC) $(CFLAGS) -c music.c

# Clean target to remove built files
clean:
	-rm -f *.o *.tos
