CXX			= g++
LDFLAGS		+= -pthread
SOURCES		= main.cpp
INCLUDES	= -I.
OBJECTS		= $(SOURCES:.cpp=.o)
TARGET		= executable

all: $(SOURCES) release

debug:	CXXFLAGS += -DDEBUG -g3 -O0 -Wall -D_GNU_SOURCE -std=c++11 -pthread 
debug:	$(SOURCES) $(TARGET)

release:	CXXFLAGS += -O3 -Wall -D_GNU_SOURCE -std=c++11 -pthread 
release:	$(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<

.PHONY:
clean:
	rm -rf $(OBJECTS) $(TARGET)
