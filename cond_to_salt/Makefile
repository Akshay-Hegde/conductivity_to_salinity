CC      = gcc
CFLAGS  = -g
RM      = rm -f
BIN     = /bin
EXE     = cond_to_salt
SRC     = cond_to_salt_debug.c
 
default: all

all: $(EXE)

clean veryclean:
	@$(RM) $(EXE)
$(EXE) : 
	@$(CC) $(CFLAGS) -o $(EXE) $(SRC) -lm

install:$(EXE)
	@install $(EXE) $(BIN)
	@$(RM) $(EXE)
	@echo "Installation successfull"

