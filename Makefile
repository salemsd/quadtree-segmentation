# Projet
.PHONY: all dist docs clean

# flags
CC = gcc
CFLAGS += -g -Wall -Iinclude -lMLV -lm

# executable
BIN_DIR = bin
TARGET = $(BIN_DIR)/segmentation

# chemins
vpath %.c src/
vpath %.h include/

# .o
OBJ_DIR = obj/
OBJ = $(OBJ_DIR)segmentation.o $(OBJ_DIR)cellules.o $(OBJ_DIR)particule.o $(OBJ_DIR)quadtree.o $(OBJ_DIR)graphique.o $(OBJ_DIR)zone.o $(OBJ_DIR)menu.o

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^ $(CFLAGS)
	@echo "\nUsage: make test"
$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)
$(OBJ_DIR):
	mkdir -p $@	
	
dist:
	mkdir -p $@
	zip -r dist/SAOUDI_OUKACI_DM2.zip rapport.pdf Makefile src/ include/

test: $(TARGET)
	./$(TARGET)

clean:
	$(RM) -r dist/ $(OBJ_DIR) $(BIN_DIR)/