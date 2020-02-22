# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/BlackSTM32F4VET6/board.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/BlackSTM32F4VET6

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)


