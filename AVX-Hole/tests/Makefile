# C++ compiler, compiler flags, and include statements

CXX	     := g++-11
CXXFLAGS := -Wall -Wpedantic -Wextra -std=c++20 -mavx2 -mavx512f -mfma
CXXTESTS := -I $(HOME)/projects/AVX-Hole/tests
CXXINCLD := -I $(HOME)/projects/AVX-Hole/include
CXXOBJTS := test_main.o test_avx2_float.o test_avx2_double.o test_avx512_float.o test_avx512_double.o

all: test.exe

test.exe: $(CXXOBJTS)
	$(CXX) $(CXXFLAGS) $(CXXTESTS) $(CXXINCLD) -o test.exe $(CXXOBJTS)

test_main.o: test_main.cxx
	$(CXX) $(CXXFLAGS) $(CXXTESTS) $(CXXINCLD) -c test_main.cxx

test_avx2_float.o: test_avx2_float.cxx
	$(CXX) $(CXXFLAGS) $(CXXTESTS) $(CXXINCLD) -c test_avx2_float.cxx

test_avx2_double.o: test_avx2_double.cxx
	$(CXX) $(CXXFLAGS) $(CXXTESTS) $(CXXINCLD) -c test_avx2_double.cxx

test_avx512_float.o: test_avx512_float.cxx
	$(CXX) $(CXXFLAGS) $(CXXTESTS) $(CXXINCLD) -c test_avx512_float.cxx

test_avx512_double.o: test_avx512_double.cxx
	$(CXX) $(CXXFLAGS) $(CXXTESTS) $(CXXINCLD) -c test_avx512_double.cxx

run: test.exe
	./test.exe

clean:
	rm *.exe *.o
	clear