#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <winsock.h>
#include <iostream>
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<graphics.h>
#include<conio.h>


#include"User_Information.h"
class Core_Base_Lyc;
class Core_QQ_Lyc;
class Core_WeChat_Lyc;
class Core_WeiBo_Lyc;
using namespace std;

class Core_Base_Lyc {
public:
	virtual void mainmenu() = 0;//主菜单，登录前

	virtual void submenu() = 0;//次菜单，登陆后

	virtual void login() = 0;//登录

	virtual void enroll(string id = "-1") = 0;//注册

	virtual void savebase() = 0;//保存QQ信息

	virtual void getinfor() = 0;//从文件读信息

	virtual void informenu() = 0;//用户基本信息管理菜单

	virtual void friendmenu() = 0;//好友管理菜单

	virtual void groupmenu() = 0;//群管理菜单

	virtual void openmenu() = 0;//开通管理菜单

	virtual void loginmenu() = 0;//登陆管理菜单

	virtual void savechange() = 0;

	virtual void showinfor() = 0;

	virtual void changename() = 0;

	virtual void changepw() = 0;

	virtual void changebir() = 0;

	virtual void changesex() = 0;

	virtual void changearea() = 0;
};

class Core_QQ_Lyc :public Core_Base_Lyc {
public:
	friend DWORD WINAPI threadFuncRecv_QQ(LPVOID pram);
	friend int vchat(string gid, Core_QQ_Lyc& c);

	friend class Core_WeChat_Lyc;
	friend class Core_WeiBo_Lyc;
	friend class Friend_Lyc;
	friend class Temp_Group_Lyc;
	friend class WeChat_Lyc;
	friend class QQ_Lyc;
	friend class WeiBo_Lyc;
	friend class QQ_Group_Lyc;

	virtual void mainmenu();

	virtual void submenu();

	virtual void login();

	virtual void enroll(string id = "-1");

	virtual void savebase();

	virtual void getinfor();

	virtual void informenu();

	virtual void friendmenu();

	virtual void groupmenu();//群管理菜单

	virtual void openmenu();//开通管理菜单

	virtual void loginmenu();//登陆管理菜单

	void savechange();

	virtual void showinfor();

	void changename();

	void changepw();

	void changebir();

	void changesex();

	void changearea();

	void addfriends();

	void friendrequest();

	void deletefriends();

	void showfriends();

	void changefriendsnote();

	void findfriends();

	void findmutualfriends();

	void Qgroupmenu();

	void Wgroupmenu();

	void viewgroups();

	void groupssave();

	void creategroups();

	void quitgroups();

	void rungroups();

	void joingroups();

	void invitefriends();

	void solveinvitation();

	void rungroups1();

	void quitgroups1();

	void groupchat();

	QQ_Lyc* getself(string id);
	//其他功能
protected:
	vector<QQ_Lyc*>QQs;
	vector<QQ_Group_Lyc*>QQgroups;
	QQ_Lyc* client;
	string QQNumber; //登陆的QQ号
};

class Core_WeiBo_Lyc :public Core_Base_Lyc {
public:

	friend DWORD WINAPI threadFuncRecv_WeiBo(LPVOID pram);
	friend int vchat(string gid, Core_WeiBo_Lyc& c);

	friend class Core_QQ_Lyc;
	friend class Core_WeChat_Lyc;
	friend class Friend_Lyc;
	friend class Temp_Group_Lyc;
	friend class WeChat_Lyc;
	friend class QQ_Lyc;
	friend class WeiBo_Lyc;

	//vector<WeiBo_Lyc*> return_WeiBos();

	virtual void mainmenu();

	virtual void submenu();

	virtual void login();

	virtual void enroll(string id = "-1");

	virtual void savebase();

	virtual void getinfor();

	virtual void informenu();

	virtual void friendmenu();

	virtual void groupmenu();//群管理菜单

	virtual void openmenu();//开通管理菜单

	virtual void loginmenu();//登陆管理菜单

	void savechange();

	virtual void showinfor();

	void changename();

	void changepw();

	void changebir();

	void changesex();

	void changearea();

	void addfriends();

	void friendrequest();

	void deletefriends();

	void showfriends();

	void changefriendsnote();

	void findfriends();

	void findmutualfriends();

	void Qgroupmenu();

	void Wgroupmenu();

	void viewgroups();

	void groupssave();

	void creategroups();

	void quitgroups();

	void rungroups();

	void joingroups();

	void invitefriends();

	void solveinvitation();

	void rungroups1();

	void quitgroups1();

	void groupchat();

	WeiBo_Lyc* getself(string id);
protected:
	vector<WeiBo_Lyc*>WeiBos;
	vector<QQ_Group_Lyc*>WeiBogroups;
	WeiBo_Lyc* client;
	string WBNumber;
};

class Core_WeChat_Lyc :public Core_Base_Lyc {
public:
	friend DWORD WINAPI threadFuncRecv_WeChat(LPVOID pram);
	friend int vchat(string gid, Core_WeChat_Lyc& c);

	friend class Core_QQ_Lyc;
	friend class Core_WeiBo_Lyc;
	friend class Friend_Lyc;
	friend class Temp_Group_Lyc;
	friend class WeChat_Lyc;
	friend class QQ_Lyc;
	friend class WeiBo_Lyc;


	virtual void mainmenu();

	virtual void submenu();

	virtual void login();

	virtual void enroll(string id = "-1");

	virtual void savebase();

	virtual void getinfor();

	virtual void informenu();

	virtual void friendmenu();

	virtual void groupmenu();//群管理菜单

	virtual void openmenu();//开通管理菜单

	virtual void loginmenu();//登陆管理菜单

	void savechange();

	virtual void showinfor();

	void changename();

	void changepw();

	void changebir();

	void changesex();

	void changearea();

	void addfriends();

	void friendrequest();

	void deletefriends();

	void showfriends();

	void changefriendsnote();

	void findfriends();

	void findmutualfriends();

	void Qgroupmenu();

	void Wgroupmenu();

	void viewgroups();

	void groupssave();

	void creategroups();

	void quitgroups();

	void rungroups();

	void joingroups();

	void invitefriends();

	void solveinvitation();

	void rungroups1();

	void quitgroups1();

	void groupchat();

	WeChat_Lyc* getself(string id);
protected:
	vector<WeChat_Lyc*>WeChats;
	vector<QQ_Group_Lyc*>WeChatgroups;
	WeChat_Lyc* client;
	string WCNumber;
};
