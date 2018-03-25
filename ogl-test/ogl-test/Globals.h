#pragma once
#include<vector>
#include<string>

extern const char* xGameName;
extern const int xEngineVersion;

void xMsg(const char* title, const char* s, UINT utype = MB_OK);

void xsMsg(const std::string& title, const std::string& s, UINT utype = MB_OK);

void xStrSplit(const char*s, std::vector<std::string>& strs);

void xTextFromFile(const char* f, std::string& ret);


