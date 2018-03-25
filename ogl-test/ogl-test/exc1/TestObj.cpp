#include "TestObj.h"
#include "../stdafx.h"
void _implgui() {
	using namespace std;

	static float f = 0;
	static bool show_another_window = true;
	static bool chk1 = false;
	static bool chk2 = true;
	ImGui_ImplGlfwGL3_NewFrame();


	ImGui::Text("hello,world");
	ImGui::SliderFloat("float", &f, 0, 1);

	if (show_another_window) {
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;

		if (ImGui::TreeNode("root")) {
			if (ImGui::TreeNode("subRoot1")) {
				if (ImGui::Checkbox("check1", &chk1)) {
					if (chk1)
						cout << "chk1" << endl;
				}
				if (ImGui::Checkbox("check2", &chk2)) {
					if (chk2)
						cout << "chk2" << endl;

				}
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("subRoot2")) {

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
		ImGui::End();
	}

	ImGui::Render();
}

GLuint vao_tris;
GLuint vao_tris2;
GLuint programId1;
GLuint programId2;
void _initTris() {
	glGenVertexArrays(1, &vao_tris);
	glBindVertexArray(vao_tris);

	float verts[] = {
		-1, 1, 0.2,
		0, 1, 0.2,
		0, -1, 0.2,
	};

	GLuint buf_vert;
	glGenBuffers(1, &buf_vert);
	glBindBuffer(GL_ARRAY_BUFFER, buf_vert);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	programId1 = resMgr->LoadShader("exc1/vs.vs", "exc1/ps.ps");
}

GLuint texSam;
GLuint texSam2;
GLuint texId;
GLuint texId2;
glm::mat4 mvp;
GLuint mvpId;
struct Vert {
	float x, y, z;
	float r, g, b;
	float u, v;
};

void _initTris2() {



	//--------------------------------------------------------------------------------
	//开启VAO: 顶点相关的操作结果都将存入其中，在切换顶点数据时，只需要切换VAO
	//受影响的操作有：
	//1,顶点缓存操作：顶点位置，颜色，UV数据
	//2,索引缓存操作：
	//3,属性开关操作：glEnableVertexAttribArray(0)(1)(2)等
	glGenVertexArrays(1, &vao_tris2);
	glBindVertexArray(vao_tris2);
	//--------------------------------------------------------------------------------
	//VAO作用开始
	//--------------------------------------------------------------------------------

	//pos, color, uv
	float verts[] = {
		-0.5, 0.5, 1, 1, 0, 0, 0, 1,
		0.5, 0.5, 1, 1, 1, 0, 1, 1,
		-0.5, -0.5, 1, 0, 0, 1, 0, 0,
		0.5, -0.5, 1, 0, 1, 0, 1, 0,
	};

	GLushort idxs[] = {	0, 1, 2, 1, 2, 3 };

	GLuint buf_vert;
	glGenBuffers(1, &buf_vert);
	glBindBuffer(GL_ARRAY_BUFFER, buf_vert);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	int szfloat = sizeof(float);
	float stride = 8 * szfloat;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * szfloat));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(6 *szfloat));

	GLuint idx_buf;
	glGenBuffers(1, &idx_buf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idxs), idxs, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//-----------------------------------------------------------------------------------
	//VAO影响范围结束，后面的操作都不会影响VAO了
	//-----------------------------------------------------------------------------------


	// Step2 设定wrap参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Step3 设定filter参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // 为MipMap设定filter方法

	programId2 = resMgr->LoadShader("exc1/tex.vs", "exc1/tex.ps");

	//texId = resMgr->loadDDS("media/uvmap.DDS");
	texId = resMgr->LoadTextrue("media/sbox.jpg", GL_BGR); //注意不是GL_RGB!!!!!!!!!!
	texId2 = resMgr->LoadTextrue("media/bbox.jpg", GL_BGR); //注意不是GL_RGB!!!!!!!!!!

	texSam = glGetUniformLocation(programId2, "myTextureSampler");
	texSam2 = glGetUniformLocation(programId2, "myTextureSampler2");
	
	auto modelMat = glm::mat4(1);
	auto viewMat = glm::lookAt(glm::vec3(0, 1, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	//注意，znear一定不能用 <=0的值，否则什么都绘制不出来
	auto projMat = glm::perspective(glm::radians(45.0f), 1280 / 720.0f, 0.1f, 1000.0f);

	mvp = projMat*viewMat*modelMat;
	mvpId = glGetUniformLocation(programId2, "MVP");

}


void _impltris1() {
	glBindVertexArray(vao_tris);
	glUseProgram(programId1);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void _impltris2() {
	glBindVertexArray(vao_tris2);
	glUseProgram(programId2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texId);
	glUniform1i(texSam, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texId2);
	glUniform1i(texSam2, 1);
	glUniformMatrix4fv(mvpId, 1, GL_FALSE, &mvp[0][0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}
CTestObj::CTestObj()
{
}

void CTestObj::Init() {
	//glEnable(GL_CULL_FACE);
	_initTris();
	_initTris2();

	//开启深度测试必须使用glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearDepth(1); //默认值就是1

}

void CTestObj::OnUpdate(){
	_impltris1();
	_impltris2();


	//imgui test
	_implgui();
	
}
CTestObj::~CTestObj()
{
}
