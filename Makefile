CC=gcc
CFLAGS=-Wall -I. -lMLV
HEADERS = cellules.h particule.h quadtree.h graphique.h zone.h
OBJ = segmentation.o cellules.o particule.o quadtree.o graphique.o zone.o
EXEC = segmentation

default: $(EXEC)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test: $(EXEC)
	./$(EXEC)

clean:
	-rm -f *.o
	-rm -f $(EXEC)
