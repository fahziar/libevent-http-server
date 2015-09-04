CXX= g++
CXX_FLAGS= -levent

all:
	$(CXX) evhttp.cpp $(CXX_FLAGS) -o server

debug:
	$(CXX) evhttp.cpp -g $(CXX_FLAGS) -o server