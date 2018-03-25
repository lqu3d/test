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
	char* _title; //ʹ��SDL���Զ���ֵΪ nullptr
	bool _fullscr; //ʹ��SDL���Զ���ֵΪ 0
};

extern CGameManager* gameMgr;
extern CSceneMgr* sceneMgr;
extern CResMgr* resMgr;
extern CRenderer* renderer;
