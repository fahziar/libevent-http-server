CXX= g++
CXX_FLAGS= -levent

all:
	$(CXX) -std=c++0x main.cpp $(CXX_FLAGS) -o server

debug:
	$(CXX) -std=c++0x main.cpp -g $(CXX_FLAGS) -o server
