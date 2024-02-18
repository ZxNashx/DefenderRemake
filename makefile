# Variables
CC=cc68x
CFLAGS=-g
GRAPHICSDRIVER_SRC=graphi~1.c
GRAPHICSDRIVER_OBJ=graphi~1.o
MODELDRIVER_SRC=modelt~1.c
MODELDRIVER_OBJ=modelt~1.o
RENDERERDRIVER_SRC=render~1.c
RENDERERDRIVER_OBJ=render~1.o

# All targets
all: graphi~1.tos modelt~1.tos render~1.tos

# Compile graphicsTestDriver program
graphi~1.tos: $(GRAPHICSDRIVER_OBJ) bitmap.o raster.o renderer.o model.o events.o
	$(CC) $(CFLAGS) $(GRAPHICSDRIVER_OBJ) bitmap.o raster.o renderer.o model.o events.o -o graphi~1.tos

$(GRAPHICSDRIVER_OBJ): $(GRAPHICSDRIVER_SRC) bitmap.h raster.h renderer.h model.h events.h defs.h
	$(CC) $(CFLAGS) -c $(GRAPHICSDRIVER_SRC)

# Compile modelTestDriver program
modelt~1.tos: $(MODELDRIVER_OBJ) bitmap.o raster.o renderer.o model.o events.o
	$(CC) $(CFLAGS) $(MODELDRIVER_OBJ) bitmap.o raster.o renderer.o model.o events.o -o modelt~1.tos

$(MODELDRIVER_OBJ): $(MODELDRIVER_SRC) bitmap.h raster.h renderer.h model.h events.h defs.h
	$(CC) $(CFLAGS) -c $(MODELDRIVER_SRC)

# Compile rendererTestDriver program
render~1.tos: $(RENDERERDRIVER_OBJ) bitmap.o raster.o renderer.o model.o events.o
	$(CC) $(CFLAGS) $(RENDERERDRIVER_OBJ) bitmap.o raster.o renderer.o model.o events.o -o rendert~1.tos

$(RENDERERDRIVER_OBJ): $(RENDERERDRIVER_SRC) bitmap.h raster.h renderer.h model.h events.h defs.h
	$(CC) $(CFLAGS) -c $(RENDERERDRIVER_SRC)

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

# Clean target to remove built files
clean:
	rm *.o *.tos
