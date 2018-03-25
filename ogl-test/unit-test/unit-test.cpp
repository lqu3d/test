// unit-test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<fstream>
#include <time.h>
#include <assert.h>

void TestArray(){

	//�������ǳ���ָ�룬
	//aָ�������׵�ַ��&aͬ��Ҳָ�������׵�ַ
	//��֮ͬ���ǣ�a + 1�� &a + 1�����岻ͬ
	//a+1 �����������ʼ��ַƫ����sizeof(int)�ֽ�
	//&a+1 �������������ʼ��ַƫ����sizeof(a)�ֽ�
	int a[] = { 1, 3, 2, 4 };
	cout << *a << *(a + 1) << *(a + 2) << *(a + 3) << endl; //1324
	

	cout << a << " " << &a << endl; //����ַ��ͬ
	cout << &a + 1 << "," << &a + 2 << endl; //0048FBB8,0048FBC8,�պò���16�ֽ�

	auto ta = a; //�����ʽ��Ȥ,ֻ�������ַ�ʽԭ��ʹ������
	cout << ta[0] << ta[1] << ta[2] << ta[3] << endl; //1324

	//����ȡַ����ȷ��ʽ
	int b = 10;
	int* p = &b;
	int** pp = &p; //
	int*** ppp = &pp;
	int**** pppp = &ppp;

	//����ȡַ������ʽ
	//int** ppt = &(&b); //&b�ǳ�����ַ��&(&b)�ǶԳ���ȡַ��������Ϊ��ֻ�б�����ȡַ
	
	
	//����һ��ָ�� int[4]���͵�ָ��pa��ע��,����Ԫ�ظ���������ȣ������� int(*pa)[2] = &a;
	int(*pa)[4] = &a;

	//ͬ�������ȶ���һ��int (*)[4]���ͣ��������������
	typedef int(*Arr4Ptr)[4]; //��������
	Arr4Ptr px = &a; //�������

	//�����ڴ�����������
	//�𰸣������һ��Ԫ�����ڴ��ж���������ŵ�,ʾ�����£�

	int iarr1[6]; //�ڴ�����
	int iarr2[6]; //�ڴ�����
	int iarr3[6]; //�ڴ�����
	float farr[3]; //�ڴ�����

	int* arrptrs[3];

	arrptrs[0] = iarr1;;
	arrptrs[1] = iarr2;
	arrptrs[2] = iarr3;

	//һ��Ԫ�ع�3����ÿ����������Ϊ int*��ָ�룬�������ڴ�����������ŵ�:
	//002CF994,002CF998,002CF99C
	cout << &(arrptrs[0]) << "," << &(arrptrs[1]) << "," << &(arrptrs[2]) << endl;

	//����Ԫ��iarr1,iarr2, iarr3�����ǲ�������ŵģ���Ϊ��������������ص���ͨ����
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

//�������ã�
//vs2015,vs2017
//intel(R)Core(TM)i7-6700HQ CPU@2.6GHZ 2.59GHZ
//16.0GB�ڴ� 64λ����ϵͳ
//���Խ����BUF_SIZEԽ��C++��C���ʱ��Խ���������£�
//BUF_SIZE= 1000: c++ƽ��90ms cƽ��80ms
//BUF_SIZE= 100000000: c++ƽ��70ms cƽ��30ms
//���Ƕ�ȡ���ԣ�����д���������������������BUF_SIZE= 100000000: c++ƽ��25�� cƽ��20��
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

