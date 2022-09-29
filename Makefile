CC=g++
WFLAGS=-std=c++17 
SOURCES=s21_matrix_oop.cpp
OBJECTS=$(SOURCES:.cpp=.o)
GCOVFLAGS=--coverage
HTML_CREATE=lcov --no-external -t a.out -o rep.info -c -d .; genhtml -o report rep.info
OS=$(shell uname)
ifeq ($(OS), Linux)
	TESTFLAGS= -lgtest -pthread -std=c++17
else
	TESTFLAGS= -lgtest -lstdc++ -std=c++17
endif

all: test
clean:
	rm -rf *.o *.g* *.out report *.a *.info

test: clean s21_matrix_oop.a
	$(CC) test.cpp s21_matrix_oop.cpp $(TESTFLAGS) -L. -ls21_matrix_oop
	./a.out

s21_matrix_oop.a: s21_matrix_oop.o
	ar rcs libs21_matrix_oop.a s21_matrix_oop.o
	ranlib libs21_matrix_oop.a
	cp libs21_matrix_oop.a s21_matrix_oop.a
	cp libs21_matrix_oop.a ls21_matrix_oop.a

s21_matrix_oop.o:
	$(CC) $(WFLAGS) -c s21_matrix_oop.cpp

leaks: test
	leaks --atExit -- ./a.out

gcov_report: clean s21_matrix_oop.a
	$(CC) test.cpp $(SOURCES) $(CHECK_FLAGS) $(TESTFLAGS) $(GCOVFLAGS) -L. -ls21_matrix_oop
	./a.out
	$(HTML_CREATE)
