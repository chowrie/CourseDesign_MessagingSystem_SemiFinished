#include <iostream>
#include"tools.h"
#include "menu.h"
#include<Windows.h>
using namespace std;
void Menu_Lyc::initial()
{
	SetConsoleTitle("腾*通信系统");
	system("color 8b");
	loading();
	system("CLS");
	string QQ = "QQ";
	string WeChat = "WeChat";
	string WeiBo = "WeiBo";
	CreateDirectory(QQ.c_str(), NULL);//创建文件夹
	CreateDirectory(WeChat.c_str(), NULL);//创建微信的文件夹
	CreateDirectory(WeiBo.c_str(), NULL);//创建微博的文件夹
	string QGroups = "QQ\\Groups";
	CreateDirectory(QGroups.c_str(), NULL);//创建QQ群组的文件夹
	string WCGroups = "WeChat\\Groups";
	CreateDirectory(WCGroups.c_str(), NULL);//创建微信群组的文件夹
	string WBGroups = "WeiBo\\Groups";
	CreateDirectory(WBGroups.c_str(), NULL);//创建微博群组的文件夹
	QQsystem.getinfor();
	WeChatsystem.getinfor();
	WeiBosystem.getinfor();
	mm.menu();
}

void Menu_Lyc::menu()
{
	while (1) {
		QQsystem.getinfor();
		WeChatsystem.getinfor();
		WeiBosystem.getinfor();
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*===========腾*通信系统===========*|" << endl;
		tttt(); cout << "|*             1.QQ                *|" << endl;
		tttt(); cout << "|*             2.微信              *|" << endl;
		tttt(); cout << "|*             3.微博              *|" << endl;
		tttt(); cout << "|*             0.退出系统          *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:";
		if (cin.peek() == '\n') {
			clear_inputBuffer(stdin);
			continue;
		}
		else {
			cin >> str;
		}
		clear_inputBuffer(stdin);
		select = judge_input_menu(str, 3);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			QQsystem.mainmenu();
			break;
		case 2:
			WeChatsystem.mainmenu();
			break;

		case 3:
			WeiBosystem.mainmenu();
			break;
		case 0:end(); return;
		}
		}
	}
}

void Menu_Lyc::loading()
{
	int i, j;
	f5(13);
	system("color 8b");
	for (i = 1; i <= 100; i++)
	{
		tttt(); cout << "欢迎使用腾*通讯系统|";
		for (j = 0; j < i / 10; j++)
			cout << "*";
		for (int k = 0; k < 10 - j; k++)
			cout << "-";
		printf("|'%d%%'\r", i);
		Sleep(10);
	}
}

void Menu_Lyc::end()
{
	int i;
	f5(13);
	system("color 8b");
	tttt(); cout << "欢迎您下次使用";
	for (i = 0; i < 10; i++)
	{
		printf(" .");
		Sleep(100);
	}
	cout << endl;
}

Menu_Lyc mm;

Core_QQ_Lyc QQsystem;

Core_WeChat_Lyc WeChatsystem;

Core_WeiBo_Lyc WeiBosystem;
