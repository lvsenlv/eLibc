TARGET_BASE_NAME    = a.out
CC                  = gcc
LD                  = ld
AR                  = ar
OBJCOPY             = objcopy
OBJDUMP             = objdump
CFLAGS              = -Wall -Wno-unused-function -Werror -O3
SRC_DIR             = ../src
INC_DIR             = ../inc
OBJ_DIR             = .
LIB_DIR             = ./lib
LIBS                = -L$(LIB_DIR)
OBJS                = crc.o crc_generate_table.o
DEF                 = -D__LINUX -D__CREATE_CRC_TABLE
INC                 = -I$(INC_DIR)
TARGET              = $(TARGET_BASE_NAME)

$(shell mkdir -p $(OBJ_DIR))

all : $(TARGET) 

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

%.o : $(SRC_DIR)/%.c
	$(CC) -c $<  -o $(OBJ_DIR)/$@ $(DEF) $(INC) $(CFLAGS) 

clean :
	rm -f $(TARGET) *.o

