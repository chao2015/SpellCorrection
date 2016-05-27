INC_DIR:= ./inc/server/ ./inc/server/net/ ./inc/server/threadpool/ ./inc/server/timer/
SRC_DIR:= ./src/server/ ./src/server/net/ ./src/server/threadpool/ ./src/server/timer/
SRCS:= $(wildcard ./src/server/*.cc) $(wildcard ./src/server/net/*.cc) $(wildcard ./src/server/threadpool/*.cc) $(wildcard ./src/server/timer/*.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
LIBS:= -lpthread

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) -Wno-deprecated

EXE:=./bin/server.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(SRCS) $(CXXFLAGS)
#$(SRC_DIR)/%.o:$(SRC_DIR)/%.cc
	#$(CXX)  -c $^ -o $@ $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
