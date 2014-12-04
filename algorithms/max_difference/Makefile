CXX		= g++
LDFLAGS		= #-lpcap
SOURCES		= main.cpp
INCLUDES	= -I.
OBJECTS		= $(SOURCES:.cpp=.o)
TARGET		= my_program

all: $(SOURCES) $(TARGET)
debug:	CXX += -DDEBUG -g -std=c++0x
debug: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CXX) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
