CC		= g++
CFLAGS		= -g -c -Wall -D_GNU_SOURCE
LDFLAGS		= -g
SOURCES		= main.cpp
INCLUDES	= -I.
OBJECTS		= $(SOURCES:.cpp=.o)
TARGET		= my_program

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf -i $(OBJECTS) $(TARGET)
