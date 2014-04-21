
PRO = rtnorm

CXX = g++
CXXFLAG = -W -Wall -g
LIB = -lm -lgsl -lgslcblas

SRC1 = src/rtnorm.cpp 
OBJ1 = tmp/rtnorm.o

SRC2 = src/main.cpp
OBJ2 = tmp/main.o

HDRS = src/rtnorm.hpp

all : $(PRO)

$(PRO): $(OBJ1) $(OBJ2)
	$(CXX) -o $(PRO) $(OBJ1) $(OBJ2)  $(LIB)

$(OBJ1) : $(SRC1) $(HDRS)
	$(CXX) -o $(OBJ1) -c $(SRC1) $(CXXFLAG)

$(OBJ2) : $(SRC2) $(HDRS)
	$(CXX) -o $(OBJ2) -c $(SRC2) $(CXXFLAG)

clean : 
	rm -rf $(PRO) ./tmp/*.o
