# MIT License
# 
# Copyright (c) 2018 André L. Maravilha
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


# Compilers
CPP = g++

# Discorde TSP headers path
INC = ../discorde/include/

# Discorde TSP library for C
DISCORDE_CPPLIB = -L../discorde/lib/ -ldiscorde_cpp -ldiscorde

# Concorde TSP library
CONCORDE_LIB = -L/opt/concorde -lconcorde

# CPLEX libraries
CPLEX_LIB = -L/opt/ibm/ILOG/CPLEX_Studio1271/cplex/lib/x86-64_linux/static_pic \
            -L/opt/ibm/ILOG/CPLEX_Studio1271/concert/lib/x86-64_linux/static_pic \
            -lconcert -lilocplex -lcplex

all: cpp_example
    
run: cpp_example
	./cpp_example

cpp_example: ./src/main.cpp
	$(CPP) -o $@ $< -O2 -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0 -I$(INC) $(DISCORDE_CPPLIB) $(CONCORDE_LIB) $(CPLEX_LIB) -lm -lpthread

clean:
	rm -rf c_example *.o

