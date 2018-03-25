// ogl-test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//-------------------------------------------------------------------------------
	//step1: init window
	//-------------------------------------------------------------------------------
	if (!glfwInit())
		return 1;
	glfwWindowHint(GLFW_DEPTH_BITS, 24);//24位深度缓存
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	bool fullscr;
	char* ptitle;
	int wndw, wndh, moniCnt;
	CAppRoot* appRoot = new CAppRoot();

	appRoot->OnWndInit();
	appRoot->GetMainWndStyle(wndw, wndh, &ptitle, fullscr);
	GLFWmonitor* pMonitor = fullscr == true ? glfwGetMonitors(&moniCnt)[0] : NULL;

	GLFWwindow* window = glfwCreateWindow(wndw, wndh, ptitle, pMonitor, NULL);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	//-------------------------------------------------------------------------------
	//step2: init openGL
	//-------------------------------------------------------------------------------
	if (gl3wInit() !=0)
	{
		return 1;
	}

	//-------------------------------------------------------------------------------
	//step3: init imgui
	//-------------------------------------------------------------------------------
	ImGui_ImplGlfwGL3_Init(window, true);

	//-------------------------------------------------------------------------------
	//step4: start game
	//-------------------------------------------------------------------------------
	appRoot->OnAppInit();

	//-------------------------------------------------------------------------------
	//step5: loop game
	//-------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS){
		appRoot->OnFrameStart();
		{//render frame
			appRoot->OnFrameRender();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		appRoot->OnFrameEnd();
	}

	//-------------------------------------------------------------------------------
	//step6: shutdown
	//-------------------------------------------------------------------------------
	glfwTerminate();
	ImGui_ImplGlfwGL3_Shutdown();

	if (appRoot){
		appRoot->OnAppQuit();

		delete appRoot;
		appRoot = NULL;
	}
	return 0;
}

