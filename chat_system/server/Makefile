ROOT_PATH=$(shell pwd)
CC=g++
SERVER=chat_server
DATA_POOL=$(ROOT_PATH)/../data_pool
COMMON=$(ROOT_PATH)/../common
LIB=$(ROOT_PATH)/../lib

INCLUDE=-I$(COMMON) -I$(DATA_POOL) -I$(LIB)/jsoncpp/include
LIB_PATH=-L$(LIB)/jsoncpp/lib

LDFLAGS=-ljsoncpp -lpthread

SRC=$(shell ls *.cpp)
SRC+=$(shell cd $(COMMON);ls *.cpp)
SRC+=$(shell cd $(DATA_POOL);ls *.cpp)
OBJ=$(SRC:.cpp=.o)

$(SERVER):$(OBJ)
	$(CC) -o $@ $^ $(LIB_PATH) $(LDFLAGS)
%.o:%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(COMMON)/%.cpp
	$(CC) -c $< $(INCLUDE)
%.o:$(DATA_POOL)/%.cpp
	$(CC) -c $< $(INCLUDE)

.PHONY:clean
clean:
	rm -f $(SERVER) *.o

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SRC)
	@echo $(OBJ)

