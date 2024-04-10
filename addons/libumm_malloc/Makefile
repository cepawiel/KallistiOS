# libumm_malloc Makefile
#

TARGET = libumm_malloc.a
OBJS = umm_info.o umm_integrity.o umm_poison.o umm_malloc.o

# Make sure everything compiles nice and cleanly (or not at all).
KOS_CFLAGS += -W -std=gnu99 -Werror -Wextra

# Uncomment the line below to enable all manner of debugging output.
KOS_CFLAGS += -I.
#-DUMM_INFO=1

include $(KOS_BASE)/addons/Makefile.prefab
