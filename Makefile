CXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS)

all: bignum.exe
	

bignum.exe: main.cc cmdline.cc cmdline.h bignum.cc bignum.h lentrada.cc lentrada.h
	$(CXX) $(CXXFLAGS) -o bignum.exe bignum.cc cmdline.cc lentrada.cc lentrada.h main.cc

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err
