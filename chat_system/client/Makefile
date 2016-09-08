ROOT_PATH=$(shell pwd)
CC=g++
SERVER=chat_client
COMMON=$(ROOT_PATH)/../common
WINDOW=$(ROOT_PATH)/../window
LIB=$(ROOT_PATH)/../lib

INCLUDE=-I$(COMMON) -I$(window) -I$(LIB)/jsoncpp/include -I$(LIB)/ncurse/include
LIB_PATH=-L$(LIB)/jsoncpp/lib -L$(LIB)/ncurse/lib

LDFLAGS=-ljsoncpp -lncurses -lpthread

SRC=$(shell ls *.cpp)
SRC+=$(shell cd $(COMMON);ls *.cpp)
SRC+=$(shell cd $(WINDOW);ls *.cpp)

OBJ=$(SRC:.cpp=.o)

$(SERVER):$(OBJ)
	$(CC) -o $@ $^ $(LIB_PATH) $(LDFLAGS)
%.o:%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(COMMON)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:%(WINDOW)/%.cpp
	$(CC) -c $< $(INCLUDE)

.PHONY:clean
clean:
	rm -f $(SERVER) *.o

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SRC)
	@echo $(OBJ)

