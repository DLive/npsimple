# npsimple makefile

CC = gcc
CXX = g++

INCLUDES = -I. 
#		   -I./include -I./include/pkcs11 -I./include/PCSC \

CFLAGS = -w -g -fPIC $(iNCLUDES)
CFLAGS += -DXP_UNIX -Dlinux
CFLAGS += -D_DEBUG

CXXFLAGS = $(CFLAGS)

LDFLAGS = -L.
LIBS = $(LDFLAGS) 

PLUGIN = libnpsimple.so

PROG = \
       $(PLUGIN)

all: $(PROG)

np_entry.o: np_entry.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

npp_entry.o: npp_gate.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

npn_entry.o: npn_gate.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

plugin.o: plugin.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

npsobj.o: npsobj.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

npsobjbase.o: npsobjbase.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

global.o: global.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

$(PLUGIN): np_entry.o npp_entry.o npn_entry.o plugin.o npsobj.o npsobjbase.o global.o
	$(CXX) -shared $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o $(PROG) *.a *.so *.dylib
