CXX= g++
CXX_FLAGS= -levent

all:
	$(CXX) evhttp.cpp $(CXX_FLAGS)

debug:
	$(CXX) evhttp.cpp -g $(CXX_FLAGS)