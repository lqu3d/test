#pragma once
class CRenderer
{
public:
	friend class CAppRoot;

protected:
	CRenderer();
	virtual ~CRenderer();

	void OnAppInit();
	void OnAppQuit();

};

