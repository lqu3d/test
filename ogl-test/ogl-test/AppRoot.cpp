#include "stdafx.h"

CGameManager* gameMgr;
CRenderer* renderer;
CResMgr* resMgr;
CSceneMgr* sceneMgr;

//----------------------------------------------------------
//step0
//----------------------------------------------------------
CAppRoot::CAppRoot(){//不要在这里做任何事情
}

//----------------------------------------------------------
//step1
//----------------------------------------------------------
void CAppRoot::OnWndInit(){
	_wndWidth = 1280;
	_wndHeight = 720;
	_title = "ogl-test";
	_fullscr = false;
}

//----------------------------------------------------------
//step2
//----------------------------------------------------------
void CAppRoot::OnAppInit(){
	ImGui::StyleColorsLight();
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

	resMgr = new CResMgr();
	gameMgr = new CGameManager();
	sceneMgr = new CSceneMgr();
	renderer = new CRenderer();

	resMgr->OnAppInit();
	sceneMgr->OnAppInit();
	gameMgr->OnAppInit();
	renderer->OnAppInit();
}

//----------------------------------------------------------
//step3
//----------------------------------------------------------
void CAppRoot::OnFrameStart(){


	
}

//----------------------------------------------------------
//step4
//----------------------------------------------------------
void CAppRoot::OnFrameRender(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	sceneMgr->OnUpdate();
}

//----------------------------------------------------------
//step5
//----------------------------------------------------------
void CAppRoot::OnFrameEnd(){

}

//----------------------------------------------------------
//step6
//----------------------------------------------------------
void CAppRoot::OnAppQuit(){
	resMgr->OnAppQuit();
	renderer->OnAppQuit();
	sceneMgr->OnAppQuit();
	gameMgr->OnAppQuit();
}

//----------------------------------------------------------
//step7
//----------------------------------------------------------
CAppRoot::~CAppRoot()
{
	delete renderer;
	delete resMgr;
	delete sceneMgr;
	delete gameMgr;
}

void CAppRoot::GetMainWndStyle(int& width, int& height, char** title, bool& fullscreen){
	width = _wndWidth;
	height = _wndHeight;
	fullscreen = _fullscr;
	(*title) = _title;
}
