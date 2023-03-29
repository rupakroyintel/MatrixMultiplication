# execute the following command before building this solution:
# source /opt/intel/oneapi/setvars.sh

# Usage options:
#   make
#     build all with Intel oneAPI tools and libraries

ONE_API_DIR=/opt/intel/oneapi
COMP_VER=2022.1.0
ICX_VER=2022.2.0
ICC=$(ONE_API_DIR)/compiler/$(COMP_VER)/linux/bin/intel64/icc
ICPC=$(ONE_API_DIR)/compiler/$(COMP_VER)/linux/bin/intel64/icpc
ICPX=$(ONE_API_DIR)/compiler/$(ICX_VER)/linux/bin/icpx
ICX=$(ONE_API_DIR)/compiler/$(ICX_VER)/linux/bin/icx

CC = gcc
CFLAGS = -O2 -g -std=c99
CPP = g++
CPPFLAGS = -g -O2 -std=c++11
LDFLAGS = -lm

all: MatrixMultiplication_gcc MatrixMultiplication_icc \
	MatrixMultiplication_icx MatrixMultiplicationOpt_gcc \
	MatrixMultiplicationOpt_icc MatrixMultiplicationOpt_icx

MatrixMultiplication_gcc: MatrixMultiplication.c
	$(CC) -o $@ $^ $(CFLAGS) -shared-libgcc

MatrixMultiplication_icc: MatrixMultiplication.c
	$(ICC) -o $@ $^ $(CFLAGS) -shared-intel

MatrixMultiplication_icx: MatrixMultiplication.c
	$(ICX) -o $@ $^ $(CFLAGS) -shared-intel

MatrixMultiplicationOpt_gcc: MatrixMultiplication.c
	$(CC) -o $@ $^ $(CFLAGS) -DOPT -shared-libgcc

MatrixMultiplicationOpt_icc: MatrixMultiplication.c
	$(ICC) -o $@ $^ $(CFLAGS) -DOPT -shared-intel

MatrixMultiplicationOpt_icx: MatrixMultiplication.c
	$(ICX) -o $@ $^ $(CFLAGS) -DOPT -shared-intel

clean:
	rm -f MatrixMultiplication_* MatrixMultiplicationOpt_*

