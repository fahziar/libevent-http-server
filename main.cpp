#include <sys/stat.h>

#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct config{
	string host;
	int port;
	string root;
};


//Variable global
config conf;

//HTTP Callback
void http_cb(struct evhttp_request *r, void *arg){
		//arahkan uri ke file
	const char * char_uri = evhttp_request_get_uri(r);
	string uri(char_uri);
	string path = conf.root + uri;

	//Cek apakah file ada
	bool file_exists = true;
	struct stat st;
	if (stat(path.c_str(), &st) == -1){
		file_exists = false;
	} else {
		if (S_ISDIR(st.st_mode)){
			path = path + "/index.html";
			if (stat(path.c_str(), &st) == -1){
				file_exists = false;
			}
		}
	}

	if (file_exists){
		//Buka file & tulis ke memory
		char *  html = (char *) malloc(st.st_size);

		if (st.st_size != 0){
			FILE * fp = fopen(path.c_str(), "r");
			fread(html, 1, st.st_size, fp);
			fclose(fp);
		}

		struct evbuffer * buffer = evbuffer_new();

		//set header
		char content_length[20];
		sprintf(content_length, "%d", (int)st.st_size);

		struct evkeyvalq * headers = evhttp_request_get_output_headers(r);
		evhttp_add_header(headers, "Content-Type", "text/html; charset=UTF-8");
		evhttp_add_header(headers, "Content-Length", content_length);

		//kirim file ke browser
		evbuffer_add(buffer, html, st.st_size);
		evhttp_send_reply(r, HTTP_OK, "OK", buffer);

		evbuffer_free(buffer);
		free(html);
	} else {
		//Kirim error
		evhttp_send_error(r, HTTP_NOTFOUND, "NOT FOUND");
	}
}

config getConfiguration(string fileName){
	ifstream infile(fileName);
	string all;
	config conf;
	conf.host = "NULL";
	conf.port = 0;
	conf.root = "NULL";

	if(getline(infile,all,' ')){
		conf.host = all;
		//cout<<all<<endl;
		if(getline(infile,all,' ')){
			conf.port = stoi(all);
			//cout<<all<<endl;
			if(getline(infile,all,'\0')){
				conf.root = all;
				//cout<<all<<endl;
			}
		}
	}

	return conf;
}


int main(){
	conf = getConfiguration("config.txt");
	cout<<conf.host<<endl;
	cout<<conf.port<<endl;
	cout<<conf.root<<endl;

	struct event_base * ev_base = event_base_new();
	struct evhttp * ev_http = evhttp_new(ev_base);

	evhttp_bind_socket(ev_http, conf.host.c_str(), conf.port);
	evhttp_set_gencb(ev_http, http_cb, NULL);

	event_base_dispatch(ev_base);

	return 0;
}