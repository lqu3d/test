#pragma once
#include<vector>
#include "XObject.h"

class CSceneMgr
{
public:
	friend class CAppRoot;

protected:
	CSceneMgr();
	virtual ~CSceneMgr();

	void OnAppInit();
	void OnAppQuit();

	void OnUpdate();

	CXObject* AddObj(int id);

	std::vector<CXObject*> _objs;
};

