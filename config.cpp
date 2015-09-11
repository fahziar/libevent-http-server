#include "config.h"
config getConfiguration(char* fileName){
	ifstream infile(fileName);
	string all;
	config conf;
	conf.host = "NULL";
	conf.port = "NULL";
	conf.root = "NULL";

	if(getline(infile,all,' ')){
		conf.host = all;
		//cout<<all<<endl;
		if(getline(infile,all,' ')){
			conf.port = all;
			//cout<<all<<endl;
			if(getline(infile,all,'\0')){
				conf.root = all;
				//cout<<all<<endl;
			}
		}
	}

	return conf;
}
