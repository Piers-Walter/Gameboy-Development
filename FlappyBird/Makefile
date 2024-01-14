CC = /Users/piers/Documents/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j
BINS = main.gb

# Source files in the Background folder
SRC_FILES := $(wildcard Background/*.c)

# Corresponding object files
OBJ_FILES := $(patsubst %.c, %.o, $(SRC_FILES))

BINS	= main.gb

all: $(BINS)

# Compile and link single file in one pass
%.gb: %.c $(OBJ_FILES)
	$(CC) -o $@ $^

# Compile individual source files to object files
%.o: %.c
	$(CC) -o $@ -c $<

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm *.noi
	rm -f Background/*.o Background/*.lst Background/*.map Background/*~ Background/*.rel Background/*.cdb Background/*.ihx Background/*.lnk Background/*.sym Background/*.asm Background/*.noi