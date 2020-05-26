// UseUtils.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "../../../Src/Log/Logger.h"

#include <stdio.h> 
#include <windows.h> 
#include <iostream> 
using namespace std;

#if 0
int main(void) { 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | FOREGROUND_GREEN); 
	cout<<"zhangzhe"<<endl; 
	printf("TestA"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN); 
	printf("TestB"); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	printf("TestC");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("TestqqqC");
	printf("TestqqqC");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("TestqqqC");
	CONSOLE_SCREEN_BUFFER_INFO bInfo; // 存储窗口信息
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&bInfo);
	
	getchar();

	return 0; 
}
#else
int main()
{
	Logger log("mylog", EnumLogLevel::LogLevelAll);
	log.TraceKeyInfo("KeyInfo");
	log.TraceWarning("warninginfo");
	log.TraceError("errorinfo");
	log.TraceInfo("normalinfo\ndajojoajo");
	std::cout << "Hello World!\n";
}
#endif
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
