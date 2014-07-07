RMDIR = rmdir /S /Q
MOVE  = move /Y

DIR_SRC = .
DIR_BIN = bin
DIR_LIB = lib
DIR_OBJ = obj
DIR_INSTALL = c:\users\ah957c\testing
TARGET = hasm.exe
TARGET_PATH = $(DIR_BIN)\$(TARGET)

CFLAGS = -c -nologo -EHsc
# CFLAGS += -DDEBUG
LFLAGS = /nologo /out:$(TARGET_PATH)

SRC_FILES = \
	code.cpp \
	parser.cpp \
	symbol.cpp \
	rj_funcs.cpp \
	main.cpp
	
OBJ_FILES = \
	$(DIR_OBJ)\code.obj \
	$(DIR_OBJ)\parser.obj \
	$(DIR_OBJ)\symbol.obj \
	$(DIR_OBJ)\rj_funcs.obj \
	$(DIR_OBJ)\main.obj
	
all : create_dirs $(TARGET_PATH)

{$(DIR_SRC)}.cpp{$(DIR_OBJ)}.obj ::
	@echo Compiling...
	cl $(CFLAGS) -Fo$(DIR_OBJ)\ $<

$(TARGET_PATH) : $(OBJ_FILES)
	@echo Linking $(TARGET)...
	link $(LFLAGS) $(OBJ_FILES)

create_dirs :
	@if not exist $(DIR_BIN) mkdir $(DIR_BIN)
	@if not exist $(DIR_OBJ) mkdir $(DIR_OBJ)

clean :
	@if exist $(DIR_BIN) $(RMDIR) $(DIR_BIN)
	@if exist $(DIR_OBJ) $(RMDIR) $(DIR_OBJ)

install :
	@echo '$@' target not yet implemented!
	
rebuild : clean create_dirs $(TARGET_PATH)
