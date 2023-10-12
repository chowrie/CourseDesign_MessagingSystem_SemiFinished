#define WIN32_LEAN_AND_MEAN //关键
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include<winsock.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")
#define num 1024
SOCKET clientSocket[num];
int coun;
void tongxin(int idx);

using namespace std;



int main() {

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//if (LOBYTE(wsaData.wVersion) != 2 ||
	//	HIBYTE(wsaData.wVersion) != 2) {
	//	cout << "wrong1!" << endl;
	//}

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serverSocket) {
		cout << "wrong2!" << endl;
		//清理协议版本信息	
		WSACleanup();
		system("pause");
		return -1;
	}
	//3.确定服务器协议地址簇
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//ip地址	
	addr.sin_port = htons(9527);//端口号
	//4.绑定
	int r = bind(serverSocket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r) {
		cout << "wrong3!" << endl;
		//清理协议版本信息	
		WSACleanup();
		system("pause");
		return -1;
	}
	//5.监听
	r = listen(serverSocket, 10);
	//if...
	//

	//6.接受客户端连接
	for (int i = 0; i < num; i++) {
		clientSocket[i] = accept(serverSocket,
			(sockaddr*)NULL, NULL);
		cout << "有客户端连接" << endl;
		coun++;
		CreateThread(NULL, NULL,
			(LPTHREAD_START_ROUTINE)tongxin,
			(LPVOID)i, NULL, NULL);

	}

	//8.关闭socket
	closesocket(serverSocket);
	//9.清理协议版本信息
	WSACleanup();

	return 0;
}

void tongxin(int idx) {
	//7.通信
	int r;
	char buff[4096];
	char temp[4096];
	while (1) {
		r = recv(clientSocket[idx], buff, 4096, NULL);
		if (r > 0) {

			buff[r] = 0;//添加结束符号
			printf(">>%s\n", buff);
			memset(temp, 0, 80);
			sprintf(temp, "%s", buff);
			//发送给连上服务器的所有客户端
			for (int i = 0; i < coun; i++) {
				send(clientSocket[i], temp, strlen(temp), NULL);
			}
		}
	}
}
