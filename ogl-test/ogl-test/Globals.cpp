#include "stdafx.h"
#include <fstream>
#include <sstream>

const char* xGameName = "my-test";
const int xEngineVersion = 0;

void xMsg(const char* title, const char* s, UINT utype /* = MB_OK */){
	std::cout << s << std::endl;
	::MessageBoxA(NULL, s, title, utype);
}

void xsMsg(const std::string& title, const std::string& s,  UINT utype){
	std::cout << s << std::endl;
	::MessageBoxA(NULL, s.c_str(), title.c_str(), utype);
}

void xStrSplit(const char*s, std::vector<std::string>& strs) {

}

void xTextFromFile(const char * f, std::string & ret)
{
	using namespace std;

	std::ifstream fs(f, std::ios::in);
	if (!fs.is_open()) {
		xMsg(f, "Can't open file", MB_ICONERROR);
		return;
	}
	std::stringstream sstr;
	sstr << fs.rdbuf();
	fs.close();
	ret = sstr.str();
}
