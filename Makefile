LZ4INC = -Ilz4/lib
ROOTLIBS = $(shell root-config --libs)
CXXFLAGS = $(shell root-config --cflags) -Isrc/hipocpp $(LZ4INC)
LIBFLAG = -c $(shell root-config --auxcflags) $(LZ4INC) -D__LZ4__
DEBUG = -D__DEBUG__ -g
LIB = $(patsubst %.cpp,%.o,$(wildcard src/hipocpp/*.cpp))
CXX = g++
PROG = dst2root
LZ4 = src/lz4/lib/lz4.o

.PHONY: clean
all: $(PROG)

$(LIB): %.o: %.cpp
	$(CXX) $(LIBFLAG) -o $@ $<

$(LZ4):
	make lib -C src/lz4

$(PROG): $(LZ4) $(LIB)
	$(CXX) -O3 src/$@.cpp $(LIB) $(LZ4) $(CXXFLAGS) -o $@ $(ROOTLIBS)

clean:
	-rm -f $(PROG)
clean-all: clean
	-rm -f $(HIPOOBJ) $(LIB)
	make clean -C src/lz4
