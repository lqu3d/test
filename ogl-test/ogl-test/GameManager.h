#pragma once
class CGameManager
{
public:

	void TestGM();
	friend class CAppRoot;

protected:
	CGameManager();
	~CGameManager();

	void OnAppInit();
	void OnAppQuit();
public:

};
