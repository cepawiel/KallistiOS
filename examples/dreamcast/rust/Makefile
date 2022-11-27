#
# Basic KallistiOS skeleton / test program
# Copyright (C)2001-2004 Dan Potter
#   

# Put the filename of the output binary here
TARGET = rust.elf

# List all of your C files here, but change the extension to ".o"
# Include "romdisk.o" if you want a rom disk.
OBJS = main.o rust.o romdisk.o

# If you define this, the Makefile.rules will create a romdisk.o for you
# from the named dir.
KOS_ROMDISK_DIR = romdisk

# The rm-elf step is to remove the target before building, to force the
# re-creation of the rom disk.
all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	-rm -f $(TARGET) $(OBJS) romdisk.*

rm-elf:
	-rm -f $(TARGET) romdisk.*

$(TARGET): $(OBJS)
	kos-cc -o $(TARGET) $(OBJS) -Wl,-Map=hello.map

rust.o: rust.rs
	kos-cc -v $(CFLAGS) $(CXXFLAGS) -c rust.rs -o rust.o

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist:
	rm -f $(OBJS) romdisk.o romdisk.img
	$(KOS_STRIP) $(TARGET)
