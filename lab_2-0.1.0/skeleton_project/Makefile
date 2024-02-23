
EXECUTABLE  = elevator

COMPILER    = clang
CFLAGS      = -Wall -g -std=gnu11 -fsanitize=address
LDFLAGS     = -fsanitize=address
EXCLUDE     = '*test*'
CC := gcc
CFLAGSD += -std=gnu99

SOURCEDIR = source
OBJECTDIR = build

SOURCES := $(patsubst $(SOURCEDIR)/%, %, $(shell find $(SOURCEDIR) -name '*.c'  ! -name $(EXCLUDE)  ! -path $(EXCLUDE)))
OBJECTS = $(addprefix $(OBJECTDIR)/, $(SOURCES:.c=.o))

all: $(EXECUTABLE) 

rebuild: clean all
	
clean:
	rm -f $(EXECUTABLE)
	rm -rf $(OBJECTDIR)



## executable depends on object files: link them
$(EXECUTABLE): $(OBJECTS) 
	$(COMPILER) $^ -o $@ $(LDFLAGS)

## object files depend on source files: compile them
$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c
	@mkdir -p $(@D)
	$(COMPILER) -o $@ -c $(CFLAGS) $<

debug:
$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c
	@echo Compiling project with debug
	$(CC) $(CFLAFGSD) -ggdb -Og -g3 $(addprefix $(SOURCEDIR)/, $(SOURCES)) -o $(OBJECTDIR)/main.o


.PHONY: all rebuild clean

