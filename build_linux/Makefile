TARGET_BASE_NAME    = eLibc
CC                  = gcc
LD                  = ld
AR                  = ar
OBJCOPY             = objcopy
OBJDUMP             = objdump
CFLAGS              = -Wall -Wno-unused-function -Werror -O3
SRC_DIR             = ../src
INC_DIR             = ../inc
OBJ_DIR             = .
LIB_DIR             = ../lib
LIBS                = -L$(LIB_DIR)
OBJS                = crc.o file.o hash.o parser.o log.o queue.o
DEF                 = -D__LINUX
INC                 = -I$(INC_DIR) -I$(COMMON)
TARGET              = $(TARGET_BASE_NAME)

ifeq ($(COMMON),)
    COMMON          = $(INC_DIR)
endif

ifeq ($(TAR_DIR),)
    TAR_DIR         = .
endif

all : $(TARGET) 

$(TARGET) : $(OBJS)
	$(AR) rcs $(TAR_DIR)/lib$@.a $(OBJS)

%.o : $(SRC_DIR)/%.c
	$(CC) -c $< -o $(OBJ_DIR)/$@ $(DEF) $(INC) $(CFLAGS) 

clean :
	rm -f $(OBJS) $(TAR_DIR)/lib$(TARGET).a
