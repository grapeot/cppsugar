all: demo
demo: demo.cpp Util.hpp
	g++ demo.cpp --std=c++11 -o demo
