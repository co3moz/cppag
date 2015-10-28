#ifndef mod_H
#define mod_H
extern "C" {
	int playmusic(char*);
	int setmusiconthread(char*);
	int playmusicthread();
}

const char* musicDir(char* b) {
	char path[MAX_PATH];
	string a = std::string( path, GetModuleFileName( NULL, path, MAX_PATH ) );
	a=a.substr(0,a.find_last_of("\\"));
	a.append("\\");
	a.append(b);
	return a.c_str();
}
#endif