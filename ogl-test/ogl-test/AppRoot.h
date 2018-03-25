#pragma once

#include "GameManager.h"
#include "Renderer.h"
#include "ResMgr.h"
#include "SceneMgr.h"

class CAppRoot
{
public:
	CAppRoot();
	~CAppRoot();

public:
	void OnWndInit();

	void OnAppInit();
	void OnAppQuit();

	void OnFrameStart();
	void OnFrameRender();
	void OnFrameEnd();

	void GetMainWndStyle(int& width, int& height, char** title, bool& fullscreen);
private:
	int _wndWidth = 1280;
	int _wndHeight = 720;
	char* _title; //使用SDL，自动赋值为 nullptr
	bool _fullscr; //使用SDL，自动赋值为 0
};

extern CGameManager* gameMgr;
extern CSceneMgr* sceneMgr;
extern CResMgr* resMgr;
extern CRenderer* renderer;
