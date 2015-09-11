#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct config{
	string host;
	string port;
	string root;
};

config getConfiguration(char* fileName);
	



