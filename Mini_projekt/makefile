all = all
CC = gcc
CFLAGS = -std=c99 -lncurses
LDIR = lib
ODIR = obj
SDIR = src
EDIR = bin
MK = mkdir

_DEPS = defines.h memory_handling.h r_w_func.h inter_mode.h game.h
DEPS = $(patsubst %, $(LDIR)/%,$(_DEPS))

_OBJ = main.o memory_handling.o r_w_func.o inter_mode.o game.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS) | $(ODIR)
	$(CC) $< $(CFLAGS) -c -o $@

$(ODIR):
	$(MK) $@

$(all): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(EDIR)/Mini_projekt


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o Mini_projekt
