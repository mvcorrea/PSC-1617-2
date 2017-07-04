TARGET = prog
LIBS = -lm
CC = gcc
CFLAGS = -g3 -Wall -std=c99
#CFLAGS = -ggdb -Wall -std=c99

BUILDDIR = build
#OBJECTS = $(addprefix $(BUILDDIR)/,$(patsubst %.c, %.o, $(wildcard *.c)))
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

.PHONY: default all clean

default: $(TARGET)
all: default
	@echo "" "" 

run: all
	@printf "> running: "
	./$(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
#	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)/$@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) -I$(BUILDDIR) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f build/*.o
	-rm -f *.o
	-rm -f $(TARGET)