#pragma once
class CResMgr
{
public:
	friend class CAppRoot;


	GLint LoadShader(const char* vsfile, const char*psfile);
	GLuint LoadTextrue(const char* texFile, GLenum fmt = GL_RGB, GLuint ifmt = GL_RGB, GLuint level = 0, GLuint border = 0);
	GLuint loadDDS(const char * imagepath);
protected:
	CResMgr();
	virtual ~CResMgr();

	void OnAppInit();
	void OnAppQuit();
};

