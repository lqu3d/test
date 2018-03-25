#include "stdafx.h"

CGameManager::CGameManager()
{
	std::cout << "CGameManager-Constructed" << std::endl;
}
void CGameManager::OnAppInit(){

}

void CGameManager::OnAppQuit(){

}


CGameManager::~CGameManager()
{
}

void CGameManager::TestGM(){
	std::cout << "TestGM" << std::endl;
}
