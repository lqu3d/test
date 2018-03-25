#include "stdafx.h"
#include "exc1/TestObj.h"

CSceneMgr::CSceneMgr()
{
	_objs.reserve(100);
}
void CSceneMgr::OnAppInit(){
	AddObj(10);

	for (auto obj : _objs) {
		obj->Init();
	}
}

void CSceneMgr::OnUpdate() {
	for (auto obj : _objs) {
		obj->OnUpdate();
	}
}

CXObject* CSceneMgr::AddObj(int id) {
	CXObject* obj = new CTestObj();
	_objs.push_back(obj);

	return obj;
}
void CSceneMgr::OnAppQuit(){

}
CSceneMgr::~CSceneMgr()
{

}
