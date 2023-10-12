#define WIN32_LEAN_AND_MEAN //关键
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<graphics.h>
#include<winsock.h>
#include<conio.h>
#include"system.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define SERVER_IP "127.0.0.1"
#define QUN_LIAO_PORT 9527
char nickName[32];//昵称
char line1[111];//一行分割线
char line2[111];//一行空白字符串

SOCKET serverSocket;//网络套接字
sockaddr_in sockAddr;//网络地址
HANDLE hMutex;//互斥锁


void GBKToUTF8(string& strGBK) {
	int len = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	wchar_t* wszUtf8 = new wchar_t[len];
	memset(wszUtf8, 0, len);
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, wszUtf8, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char* szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL, NULL);
	strGBK = szUtf8;
	delete[]szUtf8;
	delete[]wszUtf8;
}

string UTF8ToGBK(const char* strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}

bool init() {
	//1.网络服务初始化
	WSADATA data;
	int ret = WSAStartup(MAKEWORD(2, 2), &data);
	if (ret != 0) {
		return false;
	}

	//2.网络套接字
	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//3.物理地址
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	sockAddr.sin_port = htons(QUN_LIAO_PORT);

	//4.创建锁
	hMutex = CreateMutex(0, 0, "console");

	return true;

}

void login() {
	system("mode con lines=5 cols=30\n");
	cout << "  欢迎进入聊天室\n\n";
	cout << "      昵称：";
	cin >> nickName;

	while (getchar() != '\n');//清空输入缓冲区

	string name = nickName;
	GBKToUTF8(name);
	//send(serverSocket, nickName, strlen(nickName) + 1, NULL);
	send(serverSocket, name.c_str(), strlen(name.c_str()) + 1, NULL);

}

void gotoxy(int x, int y) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}

void uiInit() {
	system("mode con lines=36 cols=110");
	system("cls");
	gotoxy(0, 33);

	for (int i = 0; i < 110; i++) {
		line1[i] = '-';
		line2[i] = ' ';
	}
	line1[110] = '\0';
	line2[110] = '\0';

	cout << line1 << endl;

}

void printMsg(const char* msg) {
	//申请互斥锁
	//INFINITE，表示如果没有申请到资源，就一直等待，直到等到为止
	WaitForSingleObject(hMutex, INFINITE);

	static POINT  pos = { 0,0 };
	gotoxy(pos.x, pos.y);
	cout << msg << endl;

	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &info);
	pos.x = info.dwCursorPosition.X;
	pos.y = info.dwCursorPosition.Y;

	// 已经到聊天区域的底部
	if (pos.y >= 33) {
		printf("%s\n", line2); // 清除底部的编辑区
		printf("\n\n"); // 强迫屏幕向上滚动两行
		// 重新绘制分割线
		gotoxy(0, 33);
		printf("%s\n", line1);
		pos.y -= 1; //调整输出位置
	}

	gotoxy(1, 34);

	//释放锁
	ReleaseMutex(hMutex);
}

void editPrint(int col, char ch) {
	WaitForSingleObject(hMutex, INFINITE);

	gotoxy(col, 34);
	cout << ch;

	ReleaseMutex(hMutex);
}

void editPrint(int col, const char* ch) {
	WaitForSingleObject(hMutex, INFINITE);

	gotoxy(col, 34);
	cout << ch;

	ReleaseMutex(hMutex);
}

DWORD WINAPI threadFuncRecv_WeChat(LPVOID pram) {
	char buff[4096];
	while (1) {
		Core_WeChat_Lyc* pc = static_cast<Core_WeChat_Lyc*>(pram);
		int ret = recv(serverSocket, buff, sizeof(buff) - 1, 0);
		if (ret <= 0) {
			//cout << ret << "服务器关闭或故障\n" << endl;
			break;
		}
		else {
			int separator_pos = 0;
			char part1[4096];
			char part2[4096];
			for (int i = 0; i < ret; i++) {
				if (buff[i] == '\n') {
					separator_pos = i;
					break;
				}
			}
			// 分割字符串
			if (separator_pos > 0) {
				strncpy(part1, buff, separator_pos);
				part1[separator_pos] = 0;  // 添加字符串结束符
				strcpy(part2, buff + separator_pos + 1);
				part2[6] = 0;
			}
			string ppart2 = part2;
			for (int i = 0; i < pc->client->return_groups().size(); i++) {
				if (pc->client->return_groups()[i]->return_groupID() == ppart2) {
					if (pc->client->groupsflag[i] == 0) {
						printMsg(part1);
					}
				}
			}
			//printMsg(UTF8ToGBK(buff).c_str());
		}
		//打印接收到的信息
	}
	return NULL;

}

DWORD WINAPI threadFuncRecv_QQ(LPVOID pram) {
	char buff[4096];
	while (1) {
		Core_QQ_Lyc* pc = static_cast<Core_QQ_Lyc*>(pram);
		int ret = recv(serverSocket, buff, sizeof(buff) - 1, 0);
		if (ret <= 0) {
			//cout << ret << "服务器关闭或故障\n" << endl;
			break;
		}
		else {
			int separator_pos = 0;
			char part1[4096];
			char part2[4096];
			for (int i = 0; i < ret; i++) {
				if (buff[i] == '\n') {
					separator_pos = i;
					break;
				}
			}
			// 分割字符串
			if (separator_pos > 0) {
				strncpy(part1, buff, separator_pos);
				part1[separator_pos] = 0;  // 添加字符串结束符
				strcpy(part2, buff + separator_pos + 1);
				part2[6] = 0;
			}
			string ppart2 = part2;
			for (int i = 0; i < pc->client->return_groups().size(); i++) {
				if (pc->client->return_groups()[i]->return_groupID() == ppart2) {
					if (pc->client->groupsflag[i] == 0) {
						printMsg(part1);
					}
				}
			}
			//printMsg(UTF8ToGBK(buff).c_str());
		}
		//打印接收到的信息
	}
	return NULL;

}

DWORD WINAPI threadFuncRecv_WeiBo(LPVOID pram) {
	char buff[4096];
	while (1) {
		Core_WeiBo_Lyc* pc = static_cast<Core_WeiBo_Lyc*>(pram);
		int ret = recv(serverSocket, buff, sizeof(buff) - 1, 0);
		if (ret <= 0) {
			//cout << ret << "服务器关闭或故障\n" << endl;
			break;
		}
		else {
			int separator_pos = 0;
			char part1[4096];
			char part2[4096];
			for (int i = 0; i < ret; i++) {
				if (buff[i] == '\n') {
					separator_pos = i;
					break;
				}
			}
			// 分割字符串
			if (separator_pos > 0) {
				strncpy(part1, buff, separator_pos);
				part1[separator_pos] = 0;  // 添加字符串结束符
				strcpy(part2, buff + separator_pos + 1);
				part2[6] = 0;
			}
			string ppart2 = part2;
			for (int i = 0; i < pc->client->return_groups().size(); i++) {
				if (pc->client->return_groups()[i]->return_groupID() == ppart2) {
					if (pc->client->groupsflag[i] == 0) {
						printMsg(part1);
					}
				}
			}
			//printMsg(UTF8ToGBK(buff).c_str());
		}
		//打印接收到的信息
	}
	return NULL;

}

bool isHZ(char str[], int dex) {
	//一个汉字两个字节 第一个字节<0 第二个字节<0.>0
	//一个英文字符，只有一个字节，>0
	int i = 0;
	while (i < dex) {
		if (str[i] > 0) {
			i++;
		}
		else {
			i += 2;
		}
	}
	if (i == dex) {
		return false;
	}
	else {
		return true;
	}
}

int vchat(string gid, Core_WeChat_Lyc& c) {
	if (!init()) {
		cout << "初始化失败";
		return -1;
	}

	int r = connect(serverSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr));
	if (r == -1) {
		cout << "连接失败";
		return -2;
	}


	uiInit();//初始化 聊天室界面

	HANDLE hThread = CreateThread(0, 0, threadFuncRecv_WeChat, &c, 0, 0);

	CloseHandle(hThread);

	//编辑信息
	while (1) {
		char buff[1024];
		memset(buff, 0, sizeof(buff));


		editPrint(0, '>');
		int len = 0;
		while (1) {
			if (_kbhit()) {
				char c = getch();
				if (c == '\r') {
					break;
				}
				if (c == 16 || c == 32) {
					continue;
				}
				else if (c == 8) {//删除
					if (len == 0) {
						continue;
					}

					editPrint(len + 1, "\b\b \b\b");

					if (isHZ(buff, len - 1)) {
						cout << "\b\b \b\b";
						editPrint(len + 2, "\b\b  \b\b");
						buff[len - 1] = 0;
						buff[len - 2] = 0;
						len -= 2;
					}
					else {
						editPrint(len + 1, "\b \b");
						buff[len - 1] = 0;
						len -= 1;
					}

					continue;
				}
				else if (c == 27)return 0;
				editPrint(len + 1, c);
				buff[len++] = c;
			}
		}
		if (len == 0) {
			continue;
		}
		//清除编辑区信息
		char buff2[1024];

		sprintf_s(buff2, sizeof(buff2), "%s\n", line2);
		editPrint(0, buff2);

		//发送信息

		char tempBuff[1024]; // 使用足够大的缓冲区
		sprintf_s(tempBuff, sizeof(tempBuff), "%s:%s\n%s", c.client->return_name().c_str(), buff, gid.c_str());
		strcpy_s(buff, sizeof(buff), tempBuff); // 将结果复制到 buff

		send(serverSocket, buff, strlen(buff) + 1, 0);
	}
}


int vchat(string gid, Core_QQ_Lyc& c) {
	if (!init()) {
		cout << "初始化失败";
		return -1;
	}

	int r = connect(serverSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr));
	if (r == -1) {
		cout << "连接失败";
		return -2;
	}


	uiInit();//初始化 聊天室界面

	HANDLE hThread = CreateThread(0, 0, threadFuncRecv_QQ, &c, 0, 0);

	CloseHandle(hThread);

	//编辑信息
	while (1) {
		char buff[1024];
		memset(buff, 0, sizeof(buff));


		editPrint(0, '>');
		int len = 0;
		while (1) {
			if (_kbhit()) {
				char c = getch();
				if (c == '\r') {
					break;
				}
				if (c == 16 || c == 32) {
					continue;
				}
				else if (c == 8) {//删除
					if (len == 0) {
						continue;
					}

					editPrint(len + 1, "\b\b \b\b");

					if (isHZ(buff, len - 1)) {
						cout << "\b\b \b\b";
						editPrint(len + 2, "\b\b  \b\b");
						buff[len - 1] = 0;
						buff[len - 2] = 0;
						len -= 2;
					}
					else {
						editPrint(len + 1, "\b \b");
						buff[len - 1] = 0;
						len -= 1;
					}

					continue;
				}
				else if (c == 27)return 0;
				editPrint(len + 1, c);
				buff[len++] = c;
			}
		}
		if (len == 0) {
			continue;
		}
		//清除编辑区信息
		char buff2[1024];

		sprintf_s(buff2, sizeof(buff2), "%s\n", line2);
		editPrint(0, buff2);

		//发送信息

		char tempBuff[1024]; // 使用足够大的缓冲区
		sprintf_s(tempBuff, sizeof(tempBuff), "%s:%s\n%s", c.client->return_name().c_str(), buff, gid.c_str());
		strcpy_s(buff, sizeof(buff), tempBuff); // 将结果复制到 buff

		send(serverSocket, buff, strlen(buff) + 1, 0);
	}
}


int vchat(string gid, Core_WeiBo_Lyc& c) {
	if (!init()) {
		cout << "初始化失败";
		return -1;
	}

	int r = connect(serverSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr));
	if (r == -1) {
		cout << "连接失败";
		return -2;
	}


	uiInit();//初始化 聊天室界面

	HANDLE hThread = CreateThread(0, 0, threadFuncRecv_WeiBo, &c, 0, 0);

	CloseHandle(hThread);

	//编辑信息
	while (1) {
		char buff[1024];
		memset(buff, 0, sizeof(buff));


		editPrint(0, '>');
		int len = 0;
		while (1) {
			if (_kbhit()) {
				char c = getch();
				if (c == '\r') {
					break;
				}
				if (c == 16 || c == 32) {
					continue;
				}
				else if (c == 8) {//删除
					if (len == 0) {
						continue;
					}

					editPrint(len + 1, "\b\b \b\b");

					if (isHZ(buff, len - 1)) {
						cout << "\b\b \b\b";
						editPrint(len + 2, "\b\b  \b\b");
						buff[len - 1] = 0;
						buff[len - 2] = 0;
						len -= 2;
					}
					else {
						editPrint(len + 1, "\b \b");
						buff[len - 1] = 0;
						len -= 1;
					}

					continue;
				}
				else if (c == 27)return 0;
				editPrint(len + 1, c);
				buff[len++] = c;
			}
		}
		if (len == 0) {
			continue;
		}
		//清除编辑区信息
		char buff2[1024];

		sprintf_s(buff2, sizeof(buff2), "%s\n", line2);
		editPrint(0, buff2);

		//发送信息

		char tempBuff[1024]; // 使用足够大的缓冲区
		sprintf_s(tempBuff, sizeof(tempBuff), "%s:%s\n%s", c.client->return_name().c_str(), buff, gid.c_str());
		strcpy_s(buff, sizeof(buff), tempBuff); // 将结果复制到 buff

		send(serverSocket, buff, strlen(buff) + 1, 0);
	}
}
