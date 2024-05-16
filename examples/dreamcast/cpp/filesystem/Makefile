# KallistiOS ##version##
#
# # examples/dreamcast/cpp/filesystem/Makefile
# (c) 2023 Colton Pawielski
#

TARGET = filesystem.elf
OBJS = filesystem.o

KOS_CPPFLAGS += -std=c++20 -D_GLIBCXX_DEBUG

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean: rm-elf
	-rm -f $(OBJS)

rm-elf:
	-rm -f $(TARGET)

$(TARGET): $(OBJS)
	kos-c++ -o $(TARGET) $(OBJS)

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist: $(TARGET)
	-rm -f $(OBJS)
	$(KOS_STRIP) $(TARGET)
