
THRIFT_INSTALL=/export/yuzhitao/install/thrift/
BOOST_INSTALL=/export/yuzhitao/open_source/boost_1_67_0/

CPP = $(CXX)
BUILDEXE = $(CPP) $(BFLAGS) -o $@ $^ $(LINKS) 
CPPCOMPILE = $(CPP) $(CFLAGS) -Wno-deprecated $< $(FLAGS) $(INCLS) -o $@


########## options ##########
BFLAGS= -g -ggdb
CFLAGS = -g -ggdb $(INCLS) -fPIC -DLINUX -pipe -c -fno-inline -std=c++11 -DHAVE_CONFIG_H
CFLAGS += -g -ggdb -fno-strict-aliasing -Wall -export-dynamic -Wall -pipe  -D_GNU_SOURCE -D_REENTRANT -fPIC -Wno-deprecated -m64

LINKS += -L$(THRIFT_INSTALL)/lib/ -lthrift
INCLS += -I$(THRIFT_INSTALL)/include/ -I$(BOOST_INSTALL)/

########## options ##########

#GEN_SRCS  = $(wildcard ../gen-cpp/*.cpp)
THRIFT_SRCS  = Calculator.cpp shared_constants.cpp SharedService.cpp shared_types.cpp tutorial_constants.cpp tutorial_types.cpp
GEN_SRCS  = $(patsubst %.cpp,../gen-cpp/%.cpp,$(THRIFT_SRCS))
GEN_OBJS  = $(patsubst %.cpp,%.o,$(GEN_SRCS))

PROGS = CppServer CppClient

all:$(PROGS)

CppServer:CppServer.o $(GEN_OBJS)
	$(BUILDEXE) 
CppClient:CppClient.o $(GEN_OBJS)
	$(BUILDEXE) 


CLEAN = rm -f *.o 
clean:
	$(CLEAN) *.o $(PROGS)

.cpp.o:
	$(CPPCOMPILE)
