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
OBJS                = crc.o file.o hash.o parser.o
DEF                 = -D__WINDOWS
INC                 = -I$(INC_DIR) -I$(COMMON)
#TARGET             = $(TARGET_BASE_NAME)

ifeq ($(COMMON),)
    COMMON          = $(INC_DIR)
endif

ifeq ($(TAR_DIR),)
    TAR_DIR         = .
endif

ifeq ($(DLL),Y)
	LIB_EXE         = $(CC)
	LIB_FLAGS       = -O3 -shared -o
	TARGET          = lib$(TARGET_BASE_NAME).dll
else
	LIB_EXE         = $(AR)
ifeq ($(PREFIX),)
	LIB_FLAGS       = rcs
else
	LIB_FLAGS       = rv
endif
	TARGET          = lib$(TARGET_BASE_NAME).a
endif

all : $(TARGET) 

$(TARGET) : $(OBJS)
	$(LIB_EXE) $(LIB_FLAGS) $(TAR_DIR)/$@ $(OBJS)
	
%.o : $(SRC_DIR)/%.c
	$(CC) -c $< -o $(OBJ_DIR)/$@ $(DEF) $(INC) $(CFLAGS) 

.PHONY : clean

clean :
	-clean.bat
