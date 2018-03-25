#pragma once
class CXObject
{
public:
	CXObject();
	virtual ~CXObject();

	virtual void Init() {};
	virtual void OnUpdate() {};
	virtual void OnDestroy() {};
};

