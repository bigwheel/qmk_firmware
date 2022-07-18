SRC += \
	   util_km.c \
	   features.c \
	   auto_disable_ime_timer.c \
	   auto_disable_ime.c

ifeq ($(MAC_KEYMAP),1)
SRC += disable_ime_mac.c
else
SRC += disable_ime_pc.c
endif
