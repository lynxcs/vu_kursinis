CFLAGS:= -O3 -Wall -std=c++23 -march=native
GCC:=g++
CLANG:=clang++-19
# COMPILER:=clang++-19

# run_bench: benchmark
# 	python3

all: benchmark_gcc benchmark_clang

benchmark_gcc: functions_gcc.o benchmark_gcc.o
	$(GCC) $(CFLAGS) -o benchmark_gcc benchmark_gcc.o functions_gcc.o

benchmark_clang: functions_clang.o benchmark_clang.o
	$(CLANG) $(CFLAGS) -o benchmark_clang benchmark_clang.o functions_clang.o 

functions_gcc.o: functions.cpp functions.hpp
	$(GCC) $(CFLAGS) -c functions.cpp -o functions_gcc.o

benchmark_gcc.o: benchmark.cpp criterion/criterion.hpp
	$(GCC) $(CFLAGS) -c benchmark.cpp -o benchmark_gcc.o -DCOMPILER_NAME="\"gcc\""

functions_clang.o: functions.cpp functions.hpp
	$(CLANG) $(CFLAGS) -c functions.cpp -o functions_clang.o

benchmark_clang.o: benchmark.cpp criterion/criterion.hpp
	$(CLANG) $(CFLAGS) -c benchmark.cpp -o benchmark_clang.o -DCOMPILER_NAME="\"clang\""