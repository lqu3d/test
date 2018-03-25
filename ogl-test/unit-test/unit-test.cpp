// unit-test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<fstream>
#include <time.h>
#include <assert.h>

void TestArray(){

	//数组名是常量指针，
	//a指向数组首地址，&a同样也指向数组首地址
	//不同之处是，a + 1与 &a + 1的意义不同
	//a+1 是相对数组起始地址偏移了sizeof(int)字节
	//&a+1 是相对于数组起始地址偏移了sizeof(a)字节
	int a[] = { 1, 3, 2, 4 };
	cout << *a << *(a + 1) << *(a + 2) << *(a + 3) << endl; //1324
	

	cout << a << " " << &a << endl; //两地址相同
	cout << &a + 1 << "," << &a + 2 << endl; //0048FBB8,0048FBC8,刚好差了16字节

	auto ta = a; //这个方式有趣,只能用这种方式原样使用数组
	cout << ta[0] << ta[1] << ta[2] << ta[3] << endl; //1324

	//向上取址，正确方式
	int b = 10;
	int* p = &b;
	int** pp = &p; //
	int*** ppp = &pp;
	int**** pppp = &ppp;

	//向上取址，错误方式
	//int** ppt = &(&b); //&b是常量地址，&(&b)是对常量取址，错误行为，只有变量能取址
	
	
	//定义一个指向 int[4]类型的指针pa，注意,数组元素个数必须相等，不能是 int(*pa)[2] = &a;
	int(*pa)[4] = &a;

	//同理，可以先定义一个int (*)[4]类型，再用它定义变量
	typedef int(*Arr4Ptr)[4]; //声明类型
	Arr4Ptr px = &a; //定义变量

	//数组内存是连续的吗？
	//答案：数组的一级元素在内存中都是连续存放的,示例如下：

	int iarr1[6]; //内存连续
	int iarr2[6]; //内存连续
	int iarr3[6]; //内存连续
	float farr[3]; //内存连续

	int* arrptrs[3];

	arrptrs[0] = iarr1;;
	arrptrs[1] = iarr2;
	arrptrs[2] = iarr3;

	//一级元素共3个，每个都是类型为 int*的指针，它们在内存中是连续存放的:
	//002CF994,002CF998,002CF99C
	cout << &(arrptrs[0]) << "," << &(arrptrs[1]) << "," << &(arrptrs[2]) << endl;

	//二级元素iarr1,iarr2, iarr3明显是不连续存放的，因为它们是三个不相关的普通变量
	cout << iarr1 << "," << iarr2 << "," << iarr3 << endl;

}

void test_write()
{
	const int TEST_SIZE = 100000000;
	const char* c_plus_write_file = "H://c_plus_write_file.txt";
	const char* c_write_file = "g://c_write_file.txt";

	cout << "Test size :" << TEST_SIZE << endl;
	//c++ style writing file  
	ofstream of(c_plus_write_file);
	//assert(of);
	time_t start, end;
	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
	{
		char tmp[1];
		tmp[0] = char(i);
		of.write(tmp, 1);
	}
	end = clock();
	of.close();
	cout << "C++ style: " << end - start << " ms" << endl;
	//c style writing file  
	FILE* fp;
	fopen_s(&fp, c_write_file, "w");
	start = clock();
	for (int i = 0; i < TEST_SIZE; ++i)
	{
		char tmp[1];
		tmp[0] = char(i);
		fwrite(tmp, 1, 1, fp);
	}
	end = clock();
	fclose(fp);
	cout << "C style: " << end - start << " ms" << endl;
	cin.get();
}

//机器配置：
//vs2015,vs2017
//intel(R)Core(TM)i7-6700HQ CPU@2.6GHZ 2.59GHZ
//16.0GB内存 64位操作系统
//测试结果：BUF_SIZE越大，C++与C风格时间越大，数据如下：
//BUF_SIZE= 1000: c++平均90ms c平均80ms
//BUF_SIZE= 100000000: c++平均70ms c平均30ms
//这是读取测试，对于写入操作二者相关则更显著：BUF_SIZE= 100000000: c++平均25秒 c平均20秒
void test_read()
{
	const char* read_file = "g://c_write_file.txt";
	const int BUF_SIZE = 100000000;
	//char buf[BUF_SIZE];
	char* buf = new char[BUF_SIZE];
	time_t start, end;

	//c style writing file  
	FILE* fp = fopen(read_file, "rb");
	assert(fp);
	start = clock();
	int len = 0;
	do
	{
		len = fread(buf, 1, BUF_SIZE, fp);
		//cout<<len<<endl;  
	} while (len != 0);
	end = clock();
	fclose(fp);
	cout << "C style: " << end - start << " ms" << endl;

	//c++ style writing file  
	ifstream ifs(read_file, ios::binary);
	assert(ifs);
	start = clock();
	while (!ifs.eof())
	{
		ifs.read(buf, BUF_SIZE);
	}
	end = clock();
	ifs.close();
	cout << "C++ style: " << end - start << " ms" << endl;
	
	delete[] buf;
	cin.get();
}

int _tmain(int argc, _TCHAR* argv[])
{
	//TestArray();
	//test_write();
test_read();
	
	return 0;
}

