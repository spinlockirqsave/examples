CC		= g++
CFLAGS		= -c -g -Wall -D_GNU_SOURCE
LDFLAGS		= -g
SOURCES		= main.cc
INCLUDES	= -I.
OBJECTS		= $(SOURCES:.cc=.o)
TARGET		= my_program

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
