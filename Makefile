CXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)

all: bignum.exe
	

bignum.exe: main.cc cmdline.cc cmdline.h bignum.cc bignum.h
	$(CXX) $(CXXFLAGS) -o bignum.exe bignum.cc cmdline.cc main.cc

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err
