#include "User_Information.h"
#include"system.h"
#include "tools.h"
#include "menu.h"
#include<Windows.h>
#include <iostream>
#include<fstream>
#include<sstream>
#include<unordered_map>
#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<winsock.h>
#include<conio.h>

using namespace std;

//vector<QQ_Lyc*> Core_QQ_Lyc::QQs
//{
//	return QQs;
//}
void Core_QQ_Lyc::mainmenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*===============QQ================*|" << endl;
		tttt(); cout << "|*             1.登录              *|" << endl;
		tttt(); cout << "|*             2.注册              *|" << endl;
		tttt(); cout << "|*             0.返回主菜单        *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:";
		if (cin.peek() == '\n') {
			clear_inputBuffer(stdin);
			continue;
		}
		else {
			cin >> str;
			clear_inputBuffer(stdin);
		}
		select = judge_input_menu(str, 2);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			login();
			break;
		case 2:
			enroll();
			break;
		case 0:return;
		}
		}
	}
}

void Core_QQ_Lyc::submenu()
{
	client->flag = 1;
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*============欢迎使用QQ==========*|" << endl;
		tttt(); cout << "|*            1.个人信息          *|" << endl;
		tttt(); cout << "|*            2.好友管理          *|" << endl;
		tttt(); cout << "|*            3.群管理            *|" << endl;
		tttt(); cout << "|*            4.开通管理          *|" << endl;
		tttt(); cout << "|*            5.登录管理          *|" << endl;
		tttt(); cout << "|*            0.返回主菜单        *|" << endl;
		tttt(); cout << "|*================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 5);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			informenu();
			break;
		}
		case 2:
		{
			friendmenu();
			break;
		}
		case 3:
		{
			groupmenu();
			break;
		}
		case 4:
		{
			openmenu();
			break;
		}
		case 5:
		{
			loginmenu();
			break;
		case 0:return;
		}
		}
	}
}

void Core_QQ_Lyc::login()
{
qqlogintag:
	system("CLS");
	string ID;
	bool flag = false;
	string Passwd;
	int target;
	f5(11);
	tttt(); cout << "请输入账号：\n";
	putt(ID);
	for (int i = 0; i < QQs.size(); i++) {
		if (QQs[i]->return_ID() == ID) {
			flag = true;
			target = i;
			break;
		}
	}
	if (!flag) {
		f5(11);
		tttt(); cout << "不存在该账号，将返回菜单\n";
		any_continue(5);
		return;
	}
	else if (QQs[target]->return_flag() == 0) {
		while (1) {
			system("CLS");
			f5(10);
			tttt(4); cout << "  账号：" << ID << endl << endl;
			tttt(); cout << "请输入密码：\n";
			putt(Passwd);
			if (Passwd != QQs[target]->return_Passwd()) {
				f5(11);
				tttt(); cout << "密码输入错误，请重新输入\n";
				any_continue(5);
			}
			else break;
		}
	}

	client = QQs[target];

	client->get_friends();
	client->get_groups();
	client->get_links();
	client->flag = 1;
	system("CLS");
	f5(11);
	tttt(); cout << "登录成功\n";
	any_continue(5);
	submenu();
}

void Core_QQ_Lyc::enroll(string id)
{
	system("CLS");
	QQs.push_back(new QQ_Lyc(id));
	savebase();//保存信息到文件，并初始化一些信息
}

void Core_QQ_Lyc::savebase()
{
	ofstream file;
	string filename = "QQs.txt";
	file.open(filename, ios::app);
	if (QQs.empty())return;
	QQ_Lyc* target = QQs.back();
	if (QQs.empty()) return;
	file << target->return_ID() << endl << target->return_name() << endl << target->return_Passwd() << endl
		<< target->return_birthday() << endl << target->return_sex() << endl << target->return_area() << endl
		<< target->return_applyTime() << endl;
	file.close();
	target->get_friends();
	target->get_groups();
	string filename0 = "QQ\\" + target->return_ID() + "\\" + target->return_ID() + "links.txt";
	file.open(filename0, ios::app);
	file << "WeChat 0\nWeiBo 0";
}

void Core_QQ_Lyc::getinfor()
{
	string s;
	QQs.clear();
	QQs.shrink_to_fit();
	string id, name, pw, bir, sex, area, time;
	ifstream file;
	file.open("QQs.txt", ios::in);
	while (getline(file, id) && getline(file, name) && getline(file, pw) && getline(file, bir) && getline(file, sex) && getline(file, area) && getline(file, time))
	{
		string empty;
		getline(file, empty);
		QQs.push_back(new QQ_Lyc(id, name, pw, bir, sex, area, time));
		QQs.back()->flag = 0;
		QQs.back()->get_friends();
		QQs.back()->get_links();
	}
	for (int i = 0; i < QQs.size(); i++) {
		if (client != nullptr) {
			if (client->return_ID() == QQs[i]->return_ID()) {
				client = QQs[i];
			}
		}
	}
	file.close();


	QQgroups.clear();
	QQgroups.shrink_to_fit();
	string filename0 = "QQ\\Groups\\groupslist.txt";
	file.open(filename0, ios::in);
	while (file >> id >> name)
	{
		string empty;
		getline(file, empty);
		QQgroups.push_back(new QQ_Group_Lyc(id, name));

		string groupname = QQgroups.back()->return_groupID();
		string filename0 = "QQ\\Groups\\" + groupname + "\\" + groupname;
		string filename1 = filename0 + ".txt";
		string id;
		ifstream file1;
		file1.open(filename1, ios::in);
		while (file1 >> id) {
			QQgroups.back()->members.push_back(id);
		}
		file1.close();

		string filename2 = filename0 + "admins.txt";
		file1.open(filename2, ios::app);
		file1 >> id;
		QQgroups.back()->masterID = id;
		while (file1 >> id) {
			QQgroups.back()->admins.push_back(id);
		}
		file1.close();

		string filename5 = filename0 + "tempmem.txt";
		file1.open(filename5, ios::app);
		while (file1 >> id) {
			QQgroups.back()->tempmem.push_back(id);
		}
		file1.close();

		string filename3 = filename0 + "songroups\\";
		string filename4 = filename3 + "list.txt";
		string tgid, tgname;
		file1.open(filename4, ios::app);
		while (file1 >> tgid >> tgname) {
			QQgroups.back()->tempGroups.push_back(new Temp_Group_Lyc(tgid, tgname));
		}
		file1.close();
		for (int j = 0; j < QQgroups.back()->tempGroups.size(); j++) {
			string filename5 = filename3 + QQgroups.back()->tempGroups[j]->return_groupID() + ".txt";
			file1.open(filename5, ios::app);
			string tgmid;
			while (file1 >> tgmid) {
				QQgroups.back()->tempGroups[j]->member.push_back(tgmid);
			}
			file1.close();
			QQgroups.back()->tempGroups[j]->dad = QQgroups.back();
		}

	}
	for (int i = 0; i < QQs.size(); i++) {
		QQs[i]->get_groups();
	}
	file.close();
}

void Core_QQ_Lyc::informenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*============个人信息=============*|" << endl;
		tttt(); cout << "|*             1.查看个人信息      *|" << endl;
		tttt(); cout << "|*             2.修改昵称          *|" << endl;
		tttt(); cout << "|*             3.修改密码          *|" << endl;
		tttt(); cout << "|*             4.修改生日          *|" << endl;
		tttt(); cout << "|*             5.修改性别          *|" << endl;
		tttt(); cout << "|*             6.修改地区          *|" << endl;
		tttt(); cout << "|*             0.返回主菜单        *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 6);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			showinfor();
			break;
		}
		case 2:
		{
			changename();
			break;
		}case 3:
		{
			changepw();
			break;
		}
		case 4:
		{
			changebir();
			break;
		}case 5:
		{
			changesex();
			break;
		}
		case 6:
		{
			changearea();
			break;
		}
		case 0:return;
		}
	}
}

void Core_QQ_Lyc::friendmenu()
{
	while (1) {
		system("CLS");
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*============好友管理=============*|" << endl;
		tttt(); cout << "|*          1.所有好友展示         *|" << endl;//
		tttt(); cout << "|*          2.修改好友备注         *|" << endl;//
		tttt(); cout << "|*          3.查询好友             *|" << endl;//
		tttt(); cout << "|*          4.查询共同好友         *|" << endl;//
		tttt(); cout << "|*          5.添加好友             *|" << endl;//
		tttt(); cout << "|*          6.删除好友             *|" << endl;//
		tttt(); cout << "|*          7.查看好友申请         *|" << endl;//
		//tttt(); cout << "|*          8.好友通讯功能      *|" << endl;
		tttt(); cout << "|*          0.返回主菜单           *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 7);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			showfriends();
			break;
		}
		case 2:
		{
			changefriendsnote();
			break;
		}case 3:
		{
			findfriends();
			break;
		}
		case 4:
		{
			findmutualfriends();
			break;
		}case 5:
		{
			addfriends();
			break;
		}
		case 6:
		{
			deletefriends();
			break;
		}
		case 7:
		{
			friendrequest();
			break;
		}
		//case 8:
		//{
		//	//friendchat();
		//	break;
		//}
		case 0:return;
		}
	}
}

void Core_QQ_Lyc::groupmenu()
{
	while (1) {
		system("CLS");
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*========请选择群管理特色=========*|" << endl;
		tttt(); cout << "|*          1.QQ                   *|" << endl;
		tttt(); cout << "|*          2.微信                 *|" << endl;
		//		tttt(); cout << "|*          7.群通讯功能               *|" << endl;//
		tttt(); cout << "|*          0.返回主菜单           *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 5);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			Qgroupmenu();
			break;
		}
		case 2:
		{
			Wgroupmenu();
			break;
		}
		case 0:return;
		}
	}
}

void Core_QQ_Lyc::openmenu()
{

	ofstream file;
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*=============开通管理============*|" << endl;
		tttt(); cout << "|*             1.绑定微信          *|" << endl;
		tttt(); cout << "|*             2.开通微博          *|" << endl;
		tttt(); cout << "|*             0.返回主菜单        *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 2);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1://QQ绑定微信
		{
			if (client->return_linkWeChat() != "0") {
				f5(11);
				tttt(); cout << "已绑定微信" << endl;
				tttt(); cout << "微信ID为：" << client->return_linkWeChat() << endl;
				tttt(); cout << "如需开启自动登录，请移步登录管理" << endl;
				any_continue(5);
				break;
			}
			else {
				f5(11);
				tttt(); cout << "请输入您要绑定的微信号：\n";
				string twcid; putt(twcid);
				int num = WeChatsystem.WeChats.size();
				int flag = 0;
				for (int i = 0; i < num; i++) {
					WeChat_Lyc* tWC = WeChatsystem.WeChats[i];
					if (tWC->return_ID() == twcid) {
						flag = 1;
						string ps;
						tttt(); cout << "请输入微信密码：\n";
						putt(ps);
						if (ps == tWC->return_Passwd()) {
							//1.微信已绑定QQ
							//2.微信已开通其他微x服务，QQ也开通对于微x服务，但是两者账号不同
							if (tWC->return_linkQQ() != "0" || tWC->return_linkWeiBo() != "0") {
								cout << tWC->return_linkQQ() << endl;
								tttt(); cout << "绑定失败\n";
								tttt(); cout << "该微信已被绑定\n";
								any_continue(5);
								break;
							}
							else {
								string filename0 = "QQ\\" + client->return_ID() + "\\" + client->return_ID() + "links.txt";
								file.open(filename0, ios::out);
								file << "WeChat " << tWC->return_ID() <<
									"\nWeiBo " << client->return_linkWeiBo();
								file.close();
								client->get_links();

								string filename1 = "WeChat\\" + tWC->return_ID() + "\\" +
									tWC->return_ID() + "links.txt";
								file.open(filename1, ios::out);
								file << "QQ " << client->return_ID() << "\nWeiBo " << client->return_linkWeiBo();
								file.close();
								tWC->get_links();

								if (client->linkWeiBo != "0") {
									//微博绑定
									string filename2 = "WeiBo\\" + client->return_ID() + "\\" +
										client->return_ID() + "links.txt";
									file.open(filename2, ios::out);
									file << "QQ " << client->return_ID() << "\nWeChat " << tWC->return_ID();
									file.close();
									WeiBo_Lyc* temp = WeiBosystem.getself(client->return_ID());
									temp->get_links();
								}

								tttt(); cout << "微信绑定成功\n";
								tttt(); cout << "微信ID为：" << client->return_linkWeChat() << endl;
								tttt(); cout << "同时微信将自动绑定与QQ共享的微博（若存在）\n";
								tttt(); cout << "如需开启自动登录，请移步登录管理\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "密码错误\n";
							any_continue(5);
							break;
						}
					}
				}
				if (!flag) {
					tttt(); cout << "未找到该微信号\n";
					any_continue(5);
				}
			}
			break;
		}
		case 2://QQ开通微博
		{
			if (client->return_linkWeiBo() != "0") {
				f5(11);
				tttt(); cout << "微博服务已开通" << endl;
				tttt(); cout << "微博ID为：" << client->return_linkWeiBo() << endl;
				tttt(); cout << "如需开启自动登录，请移步登录管理" << endl;
				any_continue(5);
				break;
			}
			else {
				f5(12);
				tttt(); cout << "微博即将开始注册\n";
				any_continue(5);
				WeiBosystem.enroll(client->return_ID());

				string filename0 = "QQ\\" + client->return_ID() + "\\" + client->return_ID() + "links.txt";
				file.open(filename0, ios::out);
				file << "WeiBo " << WeiBosystem.WeiBos.back()->return_ID() << "\nWeChat " << client->return_linkWeChat();
				file.close();
				client->get_links();

				string filename1 = "WeiBo\\" + WeiBosystem.WeiBos.back()->return_ID() + "\\" +
					WeiBosystem.WeiBos.back()->return_ID() + "links.txt";
				file.open(filename1, ios::out);
				file << "QQ " << client->return_ID() << "\nWeChat " << client->return_linkWeChat();
				file.close();
				WeiBosystem.WeiBos.back()->get_links();

				if (client->linkWeChat != "0") {
					//微信绑定
					string filename2 = "WeChat\\" + client->linkWeChat + "\\" +
						client->linkWeChat + "links.txt";
					file.open(filename2, ios::out);
					file << "QQ " << client->return_ID() << "\nWeiBo " << client->return_ID();
					file.close();
					WeChat_Lyc* temp = WeChatsystem.getself(client->linkWeChat);
					temp->get_links();
				}

				f5(11);
				tttt(); cout << "微博开通成功\n";
				tttt(); cout << "微博ID为：" << client->return_linkWeiBo() << endl;
				tttt(); cout << "同时微博将自动绑定与QQ共享的微信（若存在）\n";
				tttt(); cout << "如需开启自动登录，请移步登录管理\n";
				any_continue(5);
			}
			break;
		}
		case 0:return;
		}
	}
}

void Core_QQ_Lyc::loginmenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*============登录管理=============*|" << endl;
		tttt(); cout << "|*             1.登录微信          *|" << endl;
		tttt(); cout << "|*             2.登录微博          *|" << endl;
		tttt(); cout << "|*             0.返回主菜单        *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 2);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			if (client->return_linkWeChat() == "0") {
				f5(11);
				tttt(); cout << "您暂未开通微信\n";
				tttt(); cout << "如需开通微信，请移步开通管理\n";
				any_continue(5);
			}
			else {
				int num = WeChatsystem.WeChats.size();
				for (int i = 0; i < num; i++) {
					WeChat_Lyc* target = WeChatsystem.WeChats[i];
					if (target->return_ID() == client->return_linkWeChat())target->flag = 1;
				}
				f5(11);
				tttt(); cout << "自动登录成功\n";
				tttt(); cout << "现在您可以返回主界面登录微信\n";
				any_continue(5);
			}
			break;
		}
		case 2:
		{
			if (client->return_linkWeiBo() == "0") {
				f5(11);
				tttt(); cout << "您暂未开通微博\n";
				tttt(); cout << "如需开通微博，请移步开通管理\n";
				any_continue(5);
			}
			else {
				int num = WeiBosystem.WeiBos.size();
				for (int i = 0; i < num; i++) {
					WeiBo_Lyc* target = WeiBosystem.WeiBos[i];
					if (target->return_ID() == client->return_linkWeiBo())target->flag = 1;
				}
				f5(11);
				tttt(); cout << "自动登录成功\n";
				tttt(); cout << "现在您可以返回主界面登录微博\n";
				any_continue(5);
			}
		}
		break;
		case 0:return;
		}
	}
}

void Core_QQ_Lyc::savechange()
{
	ofstream file;
	string filename = "QQs.txt";
	file.open(filename, ios::trunc | ios::out);
	if (QQs.empty())return;
	int num = QQs.size();
	for (int i = 0; i < num; i++) {
		QQ_Lyc* target = QQs[i];


		file << target->return_ID() << endl << target->return_name() << endl << target->return_Passwd() << endl
			<< target->return_birthday() << endl << target->return_sex() << endl << target->return_area() << endl
			<< target->return_applyTime() << endl << endl;


		ofstream file1;
		string filename1 = "QQ\\" + target->return_ID() + "\\" + target->return_ID() + "friends.txt";
		file1.open(filename1, ios::trunc | ios::out);
		for (int j = 0; j < target->friends.size(); j++) {
			Friend_Lyc* temp = target->friends[j];
			file1 << temp->return_ID() << endl << temp->return_note() << endl << temp->return_flag() << endl << endl;
		}
		file1.close();

		ofstream file2;
		string filename2 = "QQ\\" + target->return_ID() + "\\" + target->return_ID() + "groups.txt";
		file2.open(filename2, ios::trunc | ios::out);
		for (int j = 0; j < target->groups.size(); j++) {
			QQ_Group_Lyc* temp = target->groups[j];
			file2 << temp->return_groupID() << endl << temp->return_name() << endl;
			file2 << target->groupsflag[j] << endl << endl;
		}
		file2.close();
	}
	file.close();
	getinfor();
}

void Core_QQ_Lyc::showinfor()
{
	while (1) {
		f5(8);
		getinfor();
		tttt(); cout << "|=============个人信息============|" << endl;
		tttt(); cout << "ID：" << client->return_ID() << endl;
		tttt(); cout << "昵称：" << client->return_name() << endl;
		tttt(); cout << "密码：" << client->return_Passwd() << endl;
		tttt(); cout << "生日：" << client->return_birthday() << endl;
		tttt(); cout << "性别：" << client->return_sex() << endl;
		tttt(); cout << "地区：" << client->return_area() << endl;
		tttt(); cout << "注册时间：" << client->return_applyTime() << endl;
		tttt(); cout << "绑定微信ID：";
		if (client->return_linkWeChat() != "0") {
			cout << client->return_linkWeChat() << endl;
		}
		else {
			cout << "未绑定\n";
		}
		tttt(); cout << "绑定微博ID：";
		if (client->return_linkWeiBo() != "0") {
			cout << client->return_linkWeiBo() << endl;
		}
		else {
			cout << "未绑定\n";
		}
		any_continue(5);
		break;
	}
}

void Core_QQ_Lyc::changename()
{
	int flag = 1;
	while (flag) {
		getinfor();
		f5(8);
		tttt(); cout << "|=============修改昵称============|" << endl;
		tttt(); cout << "当前昵称：" << client->return_name() << endl << endl;
		tttt(); cout << "请输入新昵称：\n";
		string name; putt(name);
		tttt(); cout << "您确定使用这个昵称吗：" << name << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt; putt(opt);
		switch (opt) {
		case(1): {
			flag = 0;
			client->change_name(name);
			tttt(); cout << "修改成功\n";
			savechange();
			any_continue(5);
			break;
		}
		case(2): break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
}

void Core_QQ_Lyc::changepw()
{
	int flag = 1;
	while (flag) {
		getinfor();
		f5(8);
		tttt(); cout << "|=============修改密码============|" << endl;
		tttt(); cout << "当前密码：" << client->return_Passwd() << endl << endl;
		tttt(); cout << "请输入新密码：\n";
		string pw; putt(pw);
		tttt(); cout << "请再次输入新密码：\n";
		tttt(); string tmppw; cin >> tmppw;
		clear_inputBuffer(stdin);
		if (pw == tmppw) {
			f5(13);
			tttt(); cout << "您确定使用这个密码吗：" << pw << "\n";
			tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
			int opt; putt(opt);
			switch (opt) {
			case(1): {
				flag = 0;
				client->change_passwd(pw);
				tttt(); cout << "修改成功\n";
				savechange();
				any_continue(5);
				break;
			}
			case(2):break;
			default: {
				f5(13);
				tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
				any_continue(5);
			}
			}
		}
		else {
			f5(13);
			tttt(); cout << "您输入的两次密码不相符，请重新输入!\n";
			any_continue(5);
		}
	}
}

void Core_QQ_Lyc::changebir()
{

	int a[2][12] = { 31,28,31,30,31,30,31,31,30,31,30,31,31,29,31,30,31,30,31,31,30,31,30,31 };
	int flag = 1;
	string temp;
	while (flag) {
		getinfor();
		f5(8);
		tttt(); cout << "|=============修改生日============|" << endl;
		tttt(); cout << "当前生日：" << client->return_birthday() << endl << endl;
		tttt(); cout << "请输入您的生日，格式为：20041213:\n";
		putt(temp);
		int len = temp.size();
		while (1) {
			int flag1 = 0;
			while (len != 8)
			{
				f5(8);
				tttt(); cout << "|=============修改生日============|" << endl;
				tttt(); cout << "当前生日：" << client->return_birthday() << endl << endl;
				tttt(); cout << "请输入正确的日期形式：格式为：20041213:" << endl;
				putt(temp);
				len = temp.size();
			}
			int  year = 1000 * (temp[0] - '0') + 100 * (temp[1] - '0') + 10 * (temp[2] - '0') + temp[3] - '0';
			int  month = (temp[4] - '0') * 10 + temp[5] - '0';
			int day = (temp[6] - '0') * 10 + temp[7] - '0';
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			{
				if ((year > 9999 || year < 0) || (month > 12 || month < 1) || (day > a[1][month - 1] || day < 1))
				{
					f5(8);
					tttt(); cout << "|=============修改生日============|" << endl;
					tttt(); cout << "请输入正确的日期形式：格式为：20041213:" << endl;
					flag1 = 1;
					putt(temp);
				}
			}
			else
			{
				if ((year > 9999 || year < 0) || (month > 12 || month < 1) || (day > a[0][month - 1] || day < 1))
				{
					f5(8);
					tttt(); cout << "|=============修改生日============|" << endl;
					tttt(); cout << "请输入正确的日期形式：格式为：20041213:" << endl;
					flag1 = 1;
					putt(temp);
				}
			}
			if (!flag1)
			{
				break;
			}
		}
		f5(8);
		tttt(); cout << "|=============修改生日============|" << endl;
		tttt(); cout << "您确定使用这个生日吗：" << temp << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		putt(opt);
		switch (opt) {
		case(1): {
			flag = 0;
			client->change_bir(temp);
			tttt(); cout << "修改成功\n";
			savechange();
			any_continue(5);
			break;
		}
		case(2): break;
		default: {
			f5(8);
			tttt(); cout << "|=============修改生日============|" << endl;
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
}

void Core_QQ_Lyc::changesex()
{
	int flag = 1;
	while (flag) {
		getinfor();
		f5(8);
		tttt(); cout << "|=============修改性别============|" << endl;
		tttt(); cout << "当前性别：" << client->return_sex() << endl << endl;
		tttt(); cout << "请输入新性别：\n";
		tttt(); cout << "0.男性 1.女性\n";
		int name; putt(name);
		if (!(name == 0 || name == 1)) {

			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入" << endl;
			any_continue(5);
			continue;
		}
		string t;
		if (name == 0)t = "男";
		else t = "女";
		tttt(); cout << "您确定是这个性别吗：" << t << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt; putt(opt);
		switch (opt) {
		case(1): {
			flag = 0;
			switch (name) {
			case 0:
				client->change_sex(0);
				break;
			case 1:
				client->change_sex(1);
				break;
			}
			tttt(); cout << "修改成功\n";
			savechange();
			any_continue(5);
			break;
		}
		case(2): break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
}

void Core_QQ_Lyc::changearea()
{
	int flag = 1;
	while (flag) {
		getinfor();
		f5(8);
		tttt(); cout << "|=============修改地区============|" << endl;
		tttt(); cout << "当前地区：" << client->return_area() << endl << endl;
		tttt(); cout << "请输入新地区：\n";
		string name; putt(name);
		tttt(); cout << "您确定使用这个地区吗：" << name << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt; putt(opt);
		switch (opt) {
		case(1): {
			flag = 0;
			client->change_area(name);
			tttt(); cout << "修改成功\n";
			savechange();
			any_continue(5);
			break;
		}
		case(2): break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
}

void Core_QQ_Lyc::addfriends()
{
	while (1) {
		getinfor();
		//推荐好友部分
		system("CLS");
		f5(5);
		tttt(); cout << "推荐好友：\n\n\n";
		struct qlinkfriend {
			string wid;
			string wname;
			string qid;
			string qname;
		};
		vector<qlinkfriend>wc;
		vector<qlinkfriend>wb;
		WeChat_Lyc* linkwc{};
		WeiBo_Lyc* linkwb{};
		int wcflag, wbflag;
		if (client->return_linkWeChat() != "0") {//当前QQ账户有绑定的微信账户
			linkwc = WeChatsystem.getself(client->return_linkWeChat());
			for (int i = 0; i < linkwc->friends.size(); i++) {//遍历绑定的微信账户的所有好友
				WeChat_Lyc* tmpwcfriend = WeChatsystem.getself(linkwc->friends[i]->return_ID());
				wcflag = 1;
				if (tmpwcfriend->return_linkQQ() != "0") {//微信好友是否有绑定的QQ账户
					QQ_Lyc* tmpqqfriend = QQsystem.getself(tmpwcfriend->return_linkQQ());
					for (int j = 0; j < tmpqqfriend->friends.size(); j++) {//判断微信好友的QQ账户好友有无自己
						if (tmpqqfriend->friends[j]->return_ID() == client->return_ID()) {
							wcflag = 0; break;
						}
					}
					if (wcflag) {
						wc.push_back({ tmpwcfriend->return_ID(),tmpwcfriend->return_name(),
							tmpqqfriend->return_ID(),tmpqqfriend->return_name() });
					}
				}
			}
		}
		if (client->return_linkWeiBo() != "0") {//当前QQ账户有绑定的微信账户
			linkwb = WeiBosystem.getself(client->return_linkWeiBo());
			for (int i = 0; i < linkwb->friends.size(); i++) {//遍历绑定的微信账户的所有好友
				WeiBo_Lyc* tmpwbfriend = WeiBosystem.getself(linkwb->friends[i]->return_ID());
				wbflag = 1;
				if (tmpwbfriend->return_linkQQ() != "0") {//微信好友是否有绑定的QQ账户
					QQ_Lyc* tmpqqfriend = QQsystem.getself(tmpwbfriend->return_linkQQ());
					for (int j = 0; j < tmpqqfriend->friends.size(); j++) {//判断微信好友的QQ账户好友有无自己
						if (tmpqqfriend->friends[j]->return_ID() == client->return_ID()) {
							wbflag = 0; break;
						}
					}
					if (wbflag) {
						wb.push_back({ tmpwbfriend->return_ID(),tmpwbfriend->return_name(),
							tmpqqfriend->return_ID(),tmpqqfriend->return_name() });
					}
				}
			}
		}
		tttt(); cout << "来自微信的推荐好友：\n\n";
		if (wc.empty()) {
			tttt(); cout << "无\n\n";
		}
		else {
			for (int i = 0; i < wc.size(); i++) {
				tttt(); cout << "您的微信好友：" <<
					"ID:" << wc[i].wid << " 名字： " << wc[i].wname << endl;
				tttt(); cout << "其QQID：" << wc[i].qid << " 名字： " << wc[i].qid << endl << endl;
			}
			wc.clear();
		}
		cout << endl;
		tttt(); cout << "来自微博的推荐好友：\n\n";
		if (wb.empty()) {
			tttt(); cout << "无\n\n";
		}
		else {
			for (int i = 0; i < wb.size(); i++) {
				tttt(); cout << "您的微博好友：" <<
					"ID:" << wb[i].wid << " 名字： " << wb[i].wname << endl;
				tttt(); cout << "其QQID：" << wb[i].qid << " 名字： " << wb[i].qid << endl << endl;
			}
			wb.clear();
		}
		//添加部分

		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|===========添加好友==========|\n";
		tttt(); cout << "请输入您要添加的好友的ID：（输入-1返回菜单）\n";
		string id; putt(id);
		if (id == "-1") {
			return;
		}
		else if (id == client->return_ID()) {
			tttt(); cout << "您不能添加自己为好友\n";
			any_continue(5);
			continue;
		}
		else {
			int flag1 = 0;
			QQ_Lyc* target{};
			for (int i = 0; i < QQs.size(); i++) {
				if (QQs[i]->return_ID() == id) {
					flag1 = 1;
					target = QQs[i];
					break;
				}
			}
			if (!flag1) {
				tttt(); cout << "未找到该用户\n";
				any_continue(5);
				continue;
			}
			for (int i = 0; i < client->friends.size(); i++) {
				if (target->return_ID() == client->friends[i]->return_ID()) {
					if (client->friends[i]->return_flag() == 1) {
						tttt(); cout << "您已添加该好友\n";
						any_continue(5);
						return;
					}
					else if (client->friends[i]->return_flag() == 0) {
						//确认信息
						tttt(); cout << "发送好友成功，请等待对方确认\n";
						any_continue(5);
						return;
					}
					else if (client->friends[i]->return_flag() == -1) {
						tttt(); cout << "对方在此前已向您发出好友请求\n";
						tttt(); cout << "添加好友成功\n";
						any_continue(5);
						client->friends[i]->change_flag(1);
						savechange();
						return;
					}
				}
			}
			//具体操作
			target->friends.push_back(new Friend_Lyc(client->return_ID(), client->return_name(),
				client->return_birthday(), client->return_sex(), client->return_area(), -1));
			client->friends.push_back(new Friend_Lyc(target->return_ID(), target->return_name(),
				target->return_birthday(), target->return_sex(), target->return_area(), 0));

			savechange();
			tttt(); cout << "发送好友成功，请等待对方确认\n";
			any_continue(5);
			continue;
		}
	}
}

void Core_QQ_Lyc::friendrequest()
{
	while (1) {
		getinfor();
		//展示好友申请列表
		f5(5);
		vector<Friend_Lyc*>tmp;
		for (int i = 0; i < client->friends.size(); i++) {
			Friend_Lyc* target = client->friends[i];
			if (target->return_flag() == -1) {
				tmp.push_back(target);
			}
		}
		if (tmp.empty()) {
			tttt(); cout << "目前没有好友申请\n";
		}
		else {
			for (int i = 0; i < tmp.size(); i++) {
				tttt(); cout << "第" << i + 1 << "个\n";
				tttt(); cout << "ID：" << tmp[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << tmp[i]->return_name() << endl;
				tttt(); cout << "备注：" << tmp[i]->return_note() << endl;
				tttt(); cout << "生日：" << tmp[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << tmp[i]->return_sex() << endl;
				tttt(); cout << "地区：" << tmp[i]->return_area() << endl;
				cout << endl;
			}
		}
		//输入框
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|=========查看好友申请========|\n";
		tttt(); cout << "请输入您要处理的好友申请：\n";
		tttt(); cout << "（输入对应序号表示处理对应序号好友申请，输入-1返回菜单）\n";
		int sub; putt(sub);
		if (sub == -1) {
			return;
		}
		else if (sub >= 1 && sub <= tmp.size()) {
			cout << endl;
			tttt(); cout << "第" << sub << "个\n";
			tttt(); cout << "ID：" << tmp[sub - 1]->return_ID() << endl;
			tttt(); cout << "昵称：" << tmp[sub - 1]->return_name() << endl;
			tttt(); cout << "备注：" << tmp[sub - 1]->return_note() << endl;
			tttt(); cout << "生日：" << tmp[sub - 1]->return_birthday() << endl;
			tttt(); cout << "性别：" << tmp[sub - 1]->return_sex() << endl;
			tttt(); cout << "地区：" << tmp[sub - 1]->return_area() << endl;
			tttt(); cout << "您要同意该用户的好友申请吗？\n";
			tttt(); cout << "1.同意 2.拒绝\n";
			int opt; putt(opt);
			switch (opt) {
			case 1: {
				for (int i = 0; i < client->friends.size(); i++) {
					if (client->friends[i]->return_ID() == tmp[sub - 1]->return_ID())
					{
						client->friends[i]->change_flag(1);
						break;
					}
				}
				QQ_Lyc* target = getself(tmp[sub - 1]->return_ID());
				for (int i = 0; i < target->friends.size(); i++) {
					if (target->friends[i]->return_ID() == client->return_ID())
					{
						target->friends[i]->change_flag(1);
						break;
					}
				}
				savechange();
				tttt(); cout << "操作成功\n";
				any_continue(5);
				break;
			}
			case 2: {
				for (int i = 0; i < client->friends.size(); i++) {
					if (client->friends[i]->return_ID() == tmp[sub - 1]->return_ID())
					{
						client->friends.erase(client->friends.begin() + i);
						break;
					}
				}
				QQ_Lyc* target = getself(tmp[sub - 1]->return_ID());
				for (int i = 0; i < target->friends.size(); i++) {
					if (target->friends[i]->return_ID() == client->return_ID())
					{
						target->friends.erase(target->friends.begin() + i);
						break;
					}
				}
				//cout << client->friends.size();
				//while (1);
				savechange();
				tttt(); cout << "操作成功\n";
				any_continue(5);
				break;
			}
			default: {
				tttt(); cout << "由于检测到不合法输出\n";
				tttt(); cout << "默认您要重新输入要处理的好友请求\n";
				any_continue(5);
				continue;
			}
			}
		}
		else {
			tttt(); cout << "您的输入范围有误\n";
			any_continue(5);
		}
	}
}

void Core_QQ_Lyc::deletefriends()
{
	while (1) {
		getinfor();
		f5(5);
		vector<Friend_Lyc*>tmp;
		for (int i = 0; i < client->friends.size(); i++) {
			Friend_Lyc* target = client->friends[i];
			if (target->return_flag() == 1) {
				tmp.push_back(target);
			}
		}
		if (tmp.empty()) {
			tttt(); cout << "目前没有好友\n";
		}
		else {
			for (int i = 0; i < tmp.size(); i++) {
				tttt(); cout << "ID：" << tmp[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << tmp[i]->return_name() << endl;
				tttt(); cout << "备注：" << tmp[i]->return_note() << endl;
				tttt(); cout << "生日：" << tmp[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << tmp[i]->return_sex() << endl;
				tttt(); cout << "地区：" << tmp[i]->return_area() << endl;
				cout << endl;
			}
		}

		//输入框
		cout << "\033[1;1H";
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|===========删除好友==========|\n";
		tttt(); cout << "请输入您要删除的好友ID：\n";
		tttt(); cout << "（输入-1返回菜单）\n";
		string id; putt(id);
		if (id == "-1") {
			return;
		}
		else {
			Friend_Lyc* target = nullptr;
			int sub;
			for (int i = 0; i < client->friends.size(); i++) {
				if (client->friends[i]->return_ID() == id) {
					target = client->friends[i];
					sub = i;
					break;
				}
			}
			if (target == nullptr) {
				tttt(); cout << "您暂未添加该用户为好友\n";
				any_continue(5);
				continue;
			}
			else {
				cout << endl;
				tttt(); cout << "ID：" << target->return_ID() << endl;
				tttt(); cout << "昵称：" << target->return_name() << endl;
				tttt(); cout << "备注：" << target->return_note() << endl;
				tttt(); cout << "生日：" << target->return_birthday() << endl;
				tttt(); cout << "性别：" << target->return_sex() << endl;
				tttt(); cout << "地区：" << target->return_area() << endl;
				tttt(); cout << "您要删除该好友吗？\n";
				tttt(); cout << "1.确认 2.取消\n";
				int opt; putt(opt);
				switch (opt)
				{
				case 1: {
					QQ_Lyc* ttarget = getself(target->return_ID());
					client->friends.erase(client->friends.begin() + sub);
					for (int i = 0; i < ttarget->friends.size(); i++) {
						if (ttarget->friends[i]->return_ID() == client->return_ID()) {
							ttarget->friends.erase(ttarget->friends.begin() + sub);
							break;
						}
					}
					savechange();
					break;
				}
				case 2: {
					tttt(); cout << "操作成功\n";
					any_continue(5);
					break;
				}
				default: {
					tttt(); cout << "由于检测到不合法输出\n";
					tttt(); cout << "默认您要重新输入要删除的好友\n";
					any_continue(5);
					break;
				}
				}
			}
		}
	}
}

void Core_QQ_Lyc::showfriends()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->friends.empty()) {
			tttt(); cout << "目前没有好友\n";
		}
		else {
			for (int i = 0; i < client->friends.size(); i++) {
				tttt(); cout << "第" << i + 1 << "位" << endl;
				tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
				tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
				tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
				tttt(); cout << "地区：" << client->friends[i]->return_area() << endl;
				cout << endl;
			}
		}

		//输入框
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|=========所有好友展示========|\n";
		tttt(); cout << "按回车键返回菜单\n";
		tttt(); string s;
		if (cin.peek()) {
			clear_inputBuffer(stdin);
			return;
		}
	}
}

void Core_QQ_Lyc::changefriendsnote()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->friends.empty()) {
			tttt(); cout << "目前没有好友\n";
		}
		else {
			for (int i = 0; i < client->friends.size(); i++) {
				tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
				tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
				tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
				tttt(); cout << "地区：" << client->friends[i]->return_area() << endl;
				cout << endl;
			}
		}

		//输入框
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|=========修改好友备注========|\n";
		tttt(); cout << "请输入您要修改备注的好友ID：\n";
		tttt(); cout << "（输入-1返回菜单）\n";
		string id; putt(id);
		if (id == "-1") {
			return;
		}
		else {
			Friend_Lyc* target = nullptr;
			int sub;
			for (int i = 0; i < client->friends.size(); i++) {
				if (client->friends[i]->return_ID() == id) {
					target = client->friends[i];
					sub = i;
					break;
				}
			}
			if (target == nullptr) {
				tttt(); cout << "您暂未添加该用户为好友\n";
				any_continue(5);
				continue;
			}
			else {
				tttt(); cout << "请输入新备注：\n";
				string note; putt(note);
				target->note = note;
				savechange();
				tttt(); cout << "操作成功\n";
				any_continue(5);
				continue;
			}
		}
	}
}

void Core_QQ_Lyc::findfriends()
{
	while (1) {
		getinfor();
		//输入框
		system("CLS");
		f5(3);
		int opt;
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|==============查找好友============|\n";
		tttt(); cout << "|*            1.ID                *|" << endl;
		tttt(); cout << "|*            2.昵称              *|" << endl;
		tttt(); cout << "|*            3.备注              *|" << endl;
		tttt(); cout << "|*            4.生日              *|" << endl;
		tttt(); cout << "|*            5.性别              *|" << endl;
		tttt(); cout << "|*            6.地区              *|" << endl;
		tttt(); cout << "|*            0.返回菜单          *|" << endl;
		tttt(); cout << "|*================================*|" << endl;
		tttt(); cout << "请选择您要查找的方式：\n";
		putt(opt);
		switch (opt) {
		case 1: {
			string id;
			tttt(); cout << "请输入要查找的ID：\n";
			putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_ID()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
					break;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
		}
		case 2: {
			string id;
			tttt(); cout << "请输入要查找的昵称：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_name()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
		}
		case 3: {
			string id;
			tttt(); cout << "请输入要查找的备注：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_note()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
		}
		case 4: {
			string id;
			tttt(); cout << "请输入要查找的生日：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_birthday()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
		}
		case 5: {
			string id;
			tttt(); cout << "请输入要查找的性别：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_sex()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
			break;
		}
		case 6: {
			string id;
			tttt(); cout << "请输入要查找的地区：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_area()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
			break;
		}
		case 0: {
			return;
		}
		}
	}
}


void Core_QQ_Lyc::Wgroupmenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*=============群管理==============*|" << endl;
		tttt(); cout << "|*          1.创建群               *|" << endl;
		tttt(); cout << "|*          2.退出群               *|" << endl;
		tttt(); cout << "|*          3.管理群               *|" << endl;
		tttt(); cout << "|*          4.查看群信息           *|" << endl;
		tttt(); cout << "|*          5.推荐好友入群         *|" << endl;
		tttt(); cout << "|*          6.应答接受入群         *|" << endl;
		tttt(); cout << "|*          7.群通讯功能               *|" << endl;//
		tttt(); cout << "|*          0.返回主菜单           *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 7);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			creategroups();
			break;
		}
		case 2:
		{
			quitgroups1();
			break;
		}
		case 3:
		{
			rungroups1();
			break;
		}
		case 4:
		{
			viewgroups();
			break;
		}
		case 5: {
			invitefriends();
			break;
		}
		case 6: {
			solveinvitation();
			break;
		}
		case 7:
		{
			groupchat();
			break;
		}
		case 0:return;
		}
	}
}


void Core_QQ_Lyc::viewgroups()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				if (client->groups[i]->tempGroups.empty()) {
					tttt(); cout << "无子群:\n";
				}
				else {
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						tttt(); cout << "群ID：" << client->groups[i]->tempGroups[j]->return_groupID() << endl;
						tttt(); cout << "群昵称：" << client->groups[i]->tempGroups[j]->return_name() << endl << endl;
					}
				}
				cout << endl;
			}
		}
		int select;
		string str;
		//cout << "\033[1;1H";
		for (int i = 0; i < 5; i++)cout << endl;
		tttt(); cout << "|*===========查看群信息============*|" << endl;
		tttt(); cout << "请输入您要查看的群的ID:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						if (client->groups[i]->tempGroups[j]->return_groupID() == str) {
							for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
								if (client->groups[i]->tempGroups[j]->member[k] == client->return_ID()) {
									flag = 2;
									sub = i;
									tsub = j;
									target = client->groups[i];
									ttarget = client->groups[i]->tempGroups[j];
									break;
								}
							}
						}
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				if (flag == 1) {
					f5(7);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					QQ_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;


					tttt(); cout << "管理员：\n";
					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					cout << endl;
					tttt(); cout << "普通成员：\n";
					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
				}
				else if (flag == 2) {
					f5(7);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << ttarget->return_groupID() << endl;
					tttt(); cout << "群昵称：" << ttarget->return_name() << endl;
					tttt(); cout << "父群ID：" << ttarget->dad->return_groupID() << endl;
					tttt(); cout << "父群昵称：" << ttarget->dad->return_name() << endl;

					cout << endl;

					tttt(); cout << "成员：\n";
					for (int i = 0; i < ttarget->member.size(); i++) {
						QQ_Lyc* tgmname = getself(ttarget->member[i]);
						tttt(); cout << "ID：" << tgmname->return_ID() <<
							" 昵称：" << tgmname->return_name() << endl << endl;
					}
				}

				cout << "\033[1;1H";
				for (int i = 0; i < 5; i++)cout << endl;
				tttt(); cout << "按回车键返回菜单\n";
				tttt(); getchar();
				return;
			}
		}
	}
}

void Core_QQ_Lyc::groupssave()
{
	for (int i = 0; i < client->groups.size(); i++) {
		ofstream file0;
		string filename0 = "QQ\\Groups\\" + client->groups[i]->return_groupID() + "\\" + client->groups[i]->return_groupID() + ".txt";
		file0.open(filename0, ios::out | ios::trunc);
		for (int j = 0; j < client->groups[i]->members.size(); j++) {
			file0 << client->groups[i]->members[j] << endl;
		}
		file0.close();

		string filename1 = "QQ\\Groups\\" + client->groups[i]->return_groupID() + "\\" + client->groups[i]->return_groupID() + "admins.txt";
		file0.open(filename1, ios::out | ios::trunc);
		file0 << client->groups[i]->return_masterID() << endl;
		for (int j = 0; j < client->groups[i]->admins.size(); j++) {
			file0 << client->groups[i]->admins[j] << endl;
		}
		file0.close();

		string filename2 = "QQ\\Groups\\" + client->groups[i]->return_groupID() + "\\" + client->groups[i]->return_groupID() + "tempmem.txt";
		file0.open(filename2, ios::out | ios::trunc);
		for (int j = 0; j < client->groups[i]->tempmem.size(); j++) {
			file0 << client->groups[i]->tempmem[j] << endl;
		}
		file0.close();

		for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
			string filename2 = "QQ\\Groups\\" + client->groups[i]->return_groupID() + "\\" + client->groups[i]->return_groupID() + "songroups\\" +
				client->groups[i]->tempGroups[j]->return_groupID() + ".txt";
			file0.open(filename2, ios::out | ios::trunc);
			for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
				file0 << client->groups[i]->tempGroups[j]->member[k] << endl;
			}
		}
	}
}

void Core_QQ_Lyc::creategroups()
{
	while (1) {
		getinfor();
		f5(10);
		tttt(); cout << "|============创建群===========|\n";
		tttt(); cout << "请输入您要创建的群的昵称：\n";
		tttt(); cout << "按回车键取消创建\n";
		string name;
		tttt();
		if (cin.peek() == '\n') {
			tttt(); cout << "取消创建成功\n";
			clear_inputBuffer(stdin);
		}
		else {
			cin >> name;
			clear_inputBuffer(stdin);

			tttt(); cout << "您确定要使用这个昵称吗:" << name << endl;
			tttt(); cout << "1.确认2.取消\n";
			int opt; putt(opt);
			switch (opt) {
			case 1: {

				int tempid = generate_ID();
				stringstream tempss;
				tempss << tempid;
				string id;
				tempss >> id;
				ofstream file;

				//向QQ\\Groups\\groupslist.txt添加群信息
				string filename0 = "QQ\\Groups\\groupslist.txt";
				file.open(filename0, ios::app);
				file << id << endl << name << endl << endl;
				file.close();

				string filename1 = "QQ\\Groups\\" + id;
				CreateDirectory(filename1.c_str(), NULL);//创建文件夹
				string filename44 = filename1 + "\\" + id + "songroups";
				CreateDirectory(filename44.c_str(), NULL);//创建文件夹
				string filename45 = filename44 + "\\list.txt";
				file.open(filename45, ios::app);
				file.close();

				string filename2 = filename1 + "\\" + id + ".txt";
				file.open(filename2, ios::app);
				file.close();

				string filename3 = filename1 + "\\" + id + "admins.txt";
				file.open(filename3, ios::app);
				file << client->return_ID() << endl;
				file.close();


				string filename4 = filename1 + "\\" + id + "tempmem.txt";
				file.open(filename4, ios::app);
				file.close();

				QQgroups.push_back(new QQ_Group_Lyc(id, name));
				client->groups.push_back(QQgroups.back());
				client->groupsflag.push_back(0);
				client->groups.back()->masterID = client->return_ID();
				//client->groups.back()->admins.push_back(client->return_ID());
				tttt(); cout << "群创建成功" << endl;
				tttt(); cout << "群ID为:" << id << endl;
				tttt(); cout << "群昵称为:" << name << endl;
				savechange();
				groupssave();
				break;
			}
			case 2: {
				continue;
			}
			default: {
				tttt(); cout << "由于检测到无效的输出\n";
				tttt(); cout << "默认您要重新输入昵称\n";
				//continue;
			}
			}
		}
		tttt(); cout << "按回车键返回菜单\n";
		tttt(); getchar();
		return;
	}
}

void Core_QQ_Lyc::quitgroups()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				if (client->groups[i]->tempGroups.empty()) {
					tttt(); cout << "无子群:\n";
				}
				else {
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						tttt(); cout << "群ID：" << client->groups[i]->tempGroups[j]->return_groupID() << endl;
						tttt(); cout << "群昵称：" << client->groups[i]->tempGroups[j]->return_name() << endl << endl;
					}
				}
				cout << endl;
			}
		}
		int select;
		string str;
		for (int i = 0; i < 5; i++)cout << endl;
		tttt(); cout << "|*==========退出/解散群==========*|" << endl;
		tttt(); cout << "请输入您要退出/解散的群的ID:\n";
		tttt(); cout << "子群仅可解散:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						if (client->groups[i]->tempGroups[j]->return_groupID() == str) {
							for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
								if (client->groups[i]->tempGroups[j]->member[k] == client->return_ID()) {
									flag = 2;
									sub = i;
									tsub = j;
									target = client->groups[i];
									ttarget = client->groups[i]->tempGroups[j];
									break;
								}
							}
						}
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				f5(15);
				if (flag == 1) {
					int memflag = 0;
					int memsub;

					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					QQ_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;


					tttt(); cout << "管理员：\n";
					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						if (ttarget->return_ID() == client->return_ID()) {
							memflag = 1;
							memsub = i;
						}
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					cout << endl;
					tttt(); cout << "普通成员：\n";
					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						if (ttarget->return_ID() == client->return_ID()) {
							memflag = 0;
							memsub = i;
						}
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
					cout << "\033[1;1H";
					for (int i = 0; i < 5; i++)cout << endl;

					int opt;
					if (target->return_masterID() == client->return_ID()) {//判断操作用户是否是群主
						memflag = 2;
						tttt(); cout << "您是当前群群主，若执行退群操作，则将视为解散群\n";
						tttt(); cout << "若想在保留该群的情况下退出，则请先移步管理群功能转让群主\n";
						tttt(); cout << "您要解散该群吗\n";
						tttt(); cout << "1.是 2.否\n";
						putt(opt);
					}
					else {
						tttt(); cout << "您要退出该群吗\n";
						tttt(); cout << "1.是 2.否\n";
						putt(opt);
					}

					switch (opt)
					{
					case 1: {
						if (memflag == 1) {
							target->admins.erase(target->admins.begin() + memsub);
							groupssave();
							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);
						}
						else if (memflag == 0) {
							target->members.erase(target->members.begin() + memsub);
							groupssave();
							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);
						}
						else if (memflag == 2) {
							//管理员退群
							for (int i = 0; i < target->admins.size(); i++) {
								QQ_Lyc* tttarget = getself(target->admins[i]);
								for (int j = 0; j < tttarget->return_groups().size(); j++) {
									if (tttarget->groups[j]->return_groupID() == target->return_groupID()) {
										tttarget->groups.erase(tttarget->groups.begin() + i);
										break;
									}
								}
							}
							//普通成员退群
							for (int i = 0; i < target->members.size(); i++) {
								QQ_Lyc* tttarget = getself(target->members[i]);
								for (int j = 0; j < tttarget->return_groups().size(); j++) {
									if (tttarget->groups[j]->return_groupID() == target->return_groupID()) {
										tttarget->groups.erase(tttarget->groups.begin() + i);
										break;
									}
								}
							}

							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);

							//删除总群文件内的该群信息
							ofstream file1;
							ifstream file2;
							string filename0 = "QQ\\Groups\\groupslist.txt";
							vector<string>tempid, tempname;
							string tid, tname;
							file2.open(filename0, ios::in);
							while (file2 >> tid >> tname) {
								if (tid != target->return_groupID()) {
									tempid.push_back(tid);
									tempname.push_back(tname);
								}
							}
							file2.close();
							file1.open(filename0, ios::out);
							while (!tempid.empty()) {
								file1 << *tempid.begin() << endl << *tempname.begin()
									<< endl << endl;
								tempid.erase(tempid.begin());
								tempname.erase(tempname.begin());

							}

							string filename = "QQ\\Groups\\" + target->return_groupID();
							string filename1 = filename + "\\" + target->return_groupID() + ".txt";
							string filename2 = filename + "\\" + target->return_groupID() + "admins.txt";
							string filename5 = filename + "\\" + target->return_groupID() + "tempmem.txt";
							DeleteFile(filename1.c_str());
							DeleteFile(filename2.c_str());
							DeleteFile(filename5.c_str());

							//删除子群信息
							string filename3 = filename + "\\" + target->return_groupID() + "songroups";
							for (int i = 0; i < target->tempGroups.size(); i++) {
								string tgid = target->tempGroups[i]->return_groupID();
								string filename4 = filename3 + "\\" + tgid + ".txt";
								DeleteFile(filename4.c_str());

							}
							string filename4 = filename3 + "\\list.txt";
							DeleteFile(filename4.c_str());

							RemoveDirectory(filename3.c_str());
							RemoveDirectory(filename.c_str());

							delete target;
						}
						break;
					}case 2: {
						break;
					}
					default: {
						tttt(); cout << "由于检测到不合法的输出，默认您要重新输入要退出/解散的群ID\n";
						any_continue(5);
						continue;
					}
					}
				}
				else if (flag == 2) {

					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << ttarget->return_groupID() << endl;
					tttt(); cout << "群昵称：" << ttarget->return_name() << endl;
					tttt(); cout << "父群ID：" << target->return_groupID() << endl;
					tttt(); cout << "父群昵称：" << target->return_name() << endl;

					cout << endl;

					tttt(); cout << "成员：\n";
					for (int i = 0; i < ttarget->member.size(); i++) {
						QQ_Lyc* tgmname = getself(ttarget->member[i]);
						tttt(); cout << "ID：" << tgmname->return_ID() <<
							" 昵称：" << tgmname->return_name() << endl << endl;
					}

					cout << "\033[1;1H";
					for (int i = 0; i < 5; i++)cout << endl;
					tttt(); cout << "您要退出/解散该子群吗\n";
					tttt(); cout << "1.退出 2.解散 3.取消\n";
					int opt1; putt(opt1);
					switch (opt1) {
					case 1: {
						for (int i = 0; i < client->groups[sub]->tempGroups[tsub]->member.size(); i++) {
							if (client->groups[sub]->tempGroups[tsub]->member[i] == client->return_ID()) {
								client->groups[sub]->tempGroups[tsub]->member.erase(client->groups[sub]->tempGroups[tsub]->member.begin() + i);
								groupssave();
							}
						}
						/*client->groups[sub]->tempGroups.erase(client->groups[sub]->tempGroups.begin() + tsub);*/
						break;
					}
					case 2: {
						string filename0 = "QQ\\Groups\\" + client->groups[sub]->groupID + "\\" + client->groups[sub]->groupID + "songroups";
						string filename1 = filename0 + "\\list.txt";
						vector<string> tgvid, tgvname;
						string tgid, tgname;
						ifstream file;
						ofstream file1;
						file.open(filename1, ios::app);
						while (file >> tgid >> tgname) {
							if (tgid != client->groups[sub]->tempGroups[tsub]->return_groupID()) {
								tgvid.push_back(tgid);
								tgvname.push_back(tgname);
							}
						}
						file.close();
						file1.open(filename1, ios::trunc | ios::out);
						while (!tgvid.empty()) {
							file1 << *tgvid.begin() << endl << *tgvname.begin() << endl << endl;
						}
						string filename2 = filename0 + "\\" + ttarget->return_groupID() + ".txt";
						DeleteFile(filename2.c_str());

						client->groups[sub]->tempGroups.erase(client->groups[sub]->tempGroups.begin() + tsub);

						break;
					}
					case 3: {
						break;
					}default: {
						tttt(); cout << "由于不合法的输入，默认您要重新输入要退出/解散的群ID\n";
						any_continue(5);
						continue;
					}
					}

				}
				groupssave();
				savechange();
				cout << endl;
				tttt(); cout << "操作成功\n";
				tttt(); cout << "按回车键返回菜单\n";
				tttt(); getchar();
				return;
			}
		}
	}
}

void Core_QQ_Lyc::rungroups()
{
	while (1) {
		getinfor();
		string QWflag = "Q";
		string conflag;
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				if (client->groups[i]->tempGroups.empty()) {
					tttt(); cout << "无子群:\n";
				}
				else {
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						tttt(); cout << "群ID：" << client->groups[i]->tempGroups[j]->return_groupID() << endl;
						tttt(); cout << "群昵称：" << client->groups[i]->tempGroups[j]->return_name() << endl << endl;
					}
				}
				cout << endl;
			}
		}
		int select;
		string str;
		for (int i = 0; i < 5; i++)cout << endl;
		//1.解散/退出群
		//2.T人 
		//3/转让群主 群主专用
		//4.加入群请求处理 QQ专用
		//5.设置临时讨论组 QQ专用
		//6.设置/取消管理员 群主专用 QQ专用
		tttt(); cout << "|*=============管理群==============*|" << endl;
		tttt(); cout << "|*          1.T人                  *|" << endl;
		tttt(); cout << "|*          2.转让群主             *|" << endl;
		tttt(); cout << "|*          3.加入群请求处理       *|" << endl;
		tttt(); cout << "|*          4.设置子群             *|" << endl;
		tttt(); cout << "|*          5.设置/取消管理员      *|" << endl;
		tttt(); cout << "请输入您要管理的群的ID:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						if (client->groups[i]->tempGroups[j]->return_groupID() == str) {
							for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
								if (client->groups[i]->tempGroups[j]->member[k] == client->return_ID()) {
									flag = 2;
									sub = i;
									tsub = j;
									target = client->groups[i];
									ttarget = client->groups[i]->tempGroups[j];
									break;
								}
							}
						}
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				int memflag;
				if (flag == 1) {
					f5(5);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					QQ_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;
					if (ttarget->return_ID() == client->return_ID())memflag = 2;


					tttt(); cout << "管理员：\n";
					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						if (ttarget->return_ID() == client->return_ID())memflag = 1;
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					cout << endl;
					tttt(); cout << "普通成员：\n";
					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						if (ttarget->return_ID() == client->return_ID())memflag = 0;
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
				}
				else if (flag == 2) {
					f5(5);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << ttarget->return_groupID() << endl;
					tttt(); cout << "群昵称：" << ttarget->return_name() << endl;
					tttt(); cout << "父群ID：" << ttarget->dad->return_groupID() << endl;
					tttt(); cout << "父群昵称：" << ttarget->dad->return_name() << endl;

					cout << endl;

					tttt(); cout << "成员：\n";
					for (int i = 0; i < ttarget->member.size(); i++) {
						QQ_Lyc* tgmname = getself(ttarget->member[i]);
						tttt(); cout << "ID：" << tgmname->return_ID() <<
							" 昵称：" << tgmname->return_name() << endl << endl;
					}
				}
				//cout << "\033[1;1H"; 
				//cout << "\033[100A";
				//for (int i = 0; i < 5; i++)cout << endl;
				//1.解散/退出群
				//2.T人 
				//3/转让群主 群主专用
				//4.加入群请求处理 QQ专用
				//5.设置临时讨论组 QQ专用
				//6.设置/取消管理员 群主专用 QQ专用
				tttt(); cout << "|*=============管理群==============*|" << endl;
				tttt(); cout << "|*          1.T人                  *|" << endl;//
				tttt(); cout << "|*          2.转让群主             *|" << endl;//
				tttt(); cout << "|*          3.加入群请求处理       *|" << endl;
				tttt(); cout << "|*          4.创建子群             *|" << endl;
				tttt(); cout << "|*          5.设置/取消管理员      *|" << endl;//
				tttt(); cout << "请输入您要使用的群功能:\n";
				tttt(); cout << "（输入-1返回菜单)\n";
				putt(str);
				if (str == "-1")return;
				else {
					int select = judge_input_menu(str, 6);
					switch (select) {
					case 1: {
						//tmem();
						if (flag == 2) {
							tttt(); cout << "子群无法执行T人操作\n";
							any_continue(5);
						}
						else {
							tttt(); cout << "请输入您要T的群员的ID：\n";
							string Tedid; putt(Tedid); int Tsub;
							if (memflag == 0) {
								tttt(); cout << "您无此执行功能的权限\n";
								any_continue(5);
							}
							else if (memflag == 1) {
								int Tedflag = 0;
								QQ_Lyc* Ted = nullptr;
								for (int i = 0; i < target->members.size(); i++) {
									if (target->members[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								if (!Tedflag) {
									tttt(); cout << "该群不存在此用户或您没有对该用户执行T人的权限\n";
									any_continue(5);
								}
								else {
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "确定T该用户吗\n";
									tttt(); cout << "1.是2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->members.size(); i++) {
											if (target->members[i] == Ted->return_ID()) {
												target->members.erase(target->members.begin() + i);
											}
										}
										groupssave();
										Ted->groups.erase(Ted->groups.begin() + Tsub);
										Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
							}
							else if (memflag == 2) {
								int Tedflag = 0, Tedstu;
								QQ_Lyc* Ted = nullptr;
								for (int i = 0; i < target->members.size(); i++) {
									if (target->members[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tedstu = 0;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								for (int i = 0; i < target->admins.size(); i++) {
									if (target->admins[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tedstu = 1;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								if (Tedid == client->return_ID()) {
									tttt(); cout << "您没有对该用户执行T人的权限\n";
									any_continue(5);
								}
								else if (!Tedflag) {
									tttt(); cout << "该群不存在此用户\n";
									any_continue(5);
								}
								else {
									if (Tedstu == 0) {
										tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
										tttt(); cout << "确定T该用户吗\n";
										tttt(); cout << "1.是2.否\n";
										int Topt; putt(Topt);
										switch (Topt) {
										case 1: {
											for (int i = 0; i < target->members.size(); i++) {
												if (target->members[i] == Ted->return_ID()) {
													target->members.erase(target->members.begin() + i);
												}
											}
											groupssave();
											Ted->groups.erase(Ted->groups.begin() + Tsub);
											Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
											break;
										}
										case 2: {
											break;
										}
										default: {
											tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
											any_continue(5);
											continue;
										}
										}
									}
									else if (Tedstu == 1) {
										tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
										tttt(); cout << "确定T该用户吗\n";
										tttt(); cout << "1.是 2.否\n";
										int Topt; putt(Topt);
										switch (Topt) {
										case 1: {
											for (int i = 0; i < target->admins.size(); i++) {
												if (target->admins[i] == Ted->return_ID()) {
													target->admins.erase(target->admins.begin() + i);
												}
											}
											groupssave();
											Ted->groups.erase(Ted->groups.begin() + Tsub);
											Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
											break;
										}
										case 2: {
											break;
										}
										default: {
											tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
											any_continue(5);
											continue;
										}
										}
									}
									tttt(); cout << "操作成功\n";
									any_continue(5);
									break;
								}
							}
						}
						break;
					}
					case 2: {
						if (target->return_masterID() == client->return_ID()) {
							int Tedflag = 0, Tedstu;
							tttt(); cout << "请输入您转让的群员的ID：\n";
							tttt(); cout << "（在转让后，您将成为普通群员）\n";
							string Tedid; putt(Tedid); int Tsub;
							QQ_Lyc* Ted = nullptr;
							for (int i = 0; i < target->members.size(); i++) {
								if (target->members[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 0;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							for (int i = 0; i < target->admins.size(); i++) {
								if (target->admins[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 1;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							if (target->return_masterID() == Tedid) {
								tttt(); cout << "您不能对自己进行此操作\n";
								any_continue(5);
							}
							else if (!Tedflag) {
								tttt(); cout << "该群不存在此用户\n";
								any_continue(5);
							}
							else {
								if (Tedstu == 0) {
									QQ_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "您确定转让给该用户吗\n";
									tttt(); cout << "1.是2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->members.size(); i++) {
											if (target->members[i] == Ted->return_ID()) {
												target->members.erase(target->members.begin() + i);
											}
										}
										target->masterID = Ted->return_ID();
										groupssave();
										target->members.push_back(client->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								else if (Tedstu == 1) {
									QQ_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "您确定转让给该用户吗\n";
									tttt(); cout << "1.是 2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->admins.size(); i++) {
											if (target->admins[i] == Ted->return_ID()) {
												target->admins.erase(target->admins.begin() + i);
											}
										}
										target->masterID = Ted->return_ID();
										groupssave();
										target->members.push_back(client->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								tttt(); cout << "操作成功\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "您没有转让群主的权限\n";
							any_continue(5);
						}
						break;
					}
					case 3: {
						f5(5);
						tttt(); cout << "申请人：\n\n";
						int num = 1;
						for (int i = 0; i < target->tempmem.size(); i++) {
							QQ_Lyc* tmtarget = getself(target->tempmem[i]);
							for (int j = 0; j < tmtarget->groups.size(); j++) {
								if (tmtarget->groups[j] == target) {
									if (tmtarget->groupsflag[j] == -1 || tmtarget->groupsflag[j] == -3) {
										tttt(); cout << "第" << num << "位\n";
										tttt(); cout << "ID：" << tmtarget->return_ID() << " 昵称："
											<< tmtarget->return_name() << endl << endl;
										num++;
									}
								}
							}
						}
						if (target->tempmem.empty()) {
							tttt(); cout << "暂无请求\n";
							any_continue(5);
						}
						else {
							tttt(); cout << "请输入你要处理的请求：（位）\n";
							int sub; putt(sub);
							if (sub<1 || sub>target->tempmem.size()) {
								tttt(); cout << "输入范围有误\n";
							}
							else {
								tttt(); cout << "您要同意该用户的申请吗\n";
								tttt(); cout << "1.同意 2.拒绝\n";
								int opt; putt(opt);
								switch (opt) {
								case 1: {
									QQ_Lyc* tmtarget = getself(target->tempmem[sub - 1]);
									for (int i = 0; i < tmtarget->groups.size(); i++) {
										if (tmtarget->groups[i]->return_groupID() == target->return_groupID()) {
											target->tempmem.erase(target->tempmem.begin() + sub - 1);
											target->members.push_back(tmtarget->return_ID());
											tmtarget->groupsflag[i] = 0;
										}
									}

									tttt(); cout << "处理成功\n";
									any_continue(5);
									break;
								}
								case 2: {
									QQ_Lyc* tmtarget = getself(target->tempmem[sub - 1]);
									for (int i = 0; i < tmtarget->groups.size(); i++) {
										if (tmtarget->groups[i]->return_groupID() == target->return_groupID()) {
											target->tempmem.erase(target->tempmem.begin() + sub - 1);
											tmtarget->groupsflag.erase(tmtarget->groupsflag.begin() + i);
											tmtarget->groups.erase(tmtarget->groups.begin() + i);
										}
									}
									tttt(); cout << "处理成功\n";
									any_continue(5);
									break;
								}
								default: {
									tttt(); cout << "由于不合法的输入，将回到菜单\n";
									any_continue(5);
								}
								}
							}
						}
						break;
					}
					case 4: {
						tttt(); cout << "子群是QQ类型群的特有功能\n";
						tttt(); cout << "子群没有群主或管理员，不可新增成员\n";
						tttt(); cout << "子群的成员均可解散子群\n";
						tttt(); cout << "请输入你要创建的子群昵称：\n";
						string name; putt(name);
						int tid = generate_ID(); string id;
						stringstream temp;
						temp << tid;
						temp >> id;
						target->tempGroups.push_back(new Temp_Group_Lyc(id, name));
						target->tempGroups.back()->member.push_back(client->return_ID());
						tttt(); cout << "请依次输入你要从父群拉群到子群的群友ID：\n";
						tttt(); cout << "(输入-1结束)\n";
						while (1) {
							string gfriend;
							putt(gfriend);
							if (gfriend == "-1")break;
							else {
								QQ_Lyc* Gfriend = nullptr;
								Gfriend = getself(gfriend);
								if (Gfriend) {
									target->tempGroups.back()->member.push_back(gfriend);
								}
							}
						}
						tttt(); cout << "创建成功\n";
						tttt(); cout << "群ID：" << target->tempGroups.back()->return_groupID() <<
							" 群名：" << target->tempGroups.back()->return_name() << endl;

						ofstream file;
						string filename = "QQ\\Groups\\" + target->return_groupID() + "\\" +
							target->return_groupID() + "songroups\\list.txt";
						file.open(filename, ios::app);
						file << id << endl << name << endl;
						file.close();
						groupssave();
						savechange();
						any_continue(5);
						break;
					}
					case 5: {
						if (target->return_masterID() == client->return_ID()) {
							int Tedflag = 0, Tedstu;
							QQ_Lyc* Ted = nullptr;
							tttt(); cout << "请输入您处理的群员的ID：\n";
							string Tedid; putt(Tedid); int Tsub;
							for (int i = 0; i < target->members.size(); i++) {
								if (target->members[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 0;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							for (int i = 0; i < target->admins.size(); i++) {
								if (target->admins[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 1;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							if (target->return_masterID() == Tedid) {
								tttt(); cout << "您不能对自己进行此操作\n";
								any_continue(5);
							}
							else if (!Tedflag) {
								tttt(); cout << "该群不存在此用户\n";
								any_continue(5);
							}
							else {
								if (Tedstu == 0) {
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "该用户是普通成员，确定将其升级为管理员吗\n";
									tttt(); cout << "1.是2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->members.size(); i++) {
											if (target->members[i] == Ted->return_ID()) {
												target->members.erase(target->members.begin() + i);
											}
										}
										groupssave();
										target->admins.push_back(Ted->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								else if (Tedstu == 1) {
									QQ_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "该用户是管理员，确定将其降级为普通用户吗\n";
									tttt(); cout << "1.是 2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->admins.size(); i++) {
											if (target->admins[i] == Ted->return_ID()) {
												target->admins.erase(target->admins.begin() + i);
											}
										}
										groupssave();
										target->members.push_back(Ted->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								tttt(); cout << "操作成功\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "您没有设置/取消管理员权限\n";
							any_continue(5);
						}
					}
					default: {
						continue;
					}
					}
					groupssave();
					savechange();
				}
			}
		}
	}
}

void Core_QQ_Lyc::joingroups()
{
	while (1) {
		getinfor();
		f5(7);
		tttt(); cout << "请输入你要加入的群ID：\n";
		string tid; putt(tid);
		ifstream file;
		string filename = "QQ\\Groups\\groupslist.txt";
		string tgid, tgname;
		file.open(filename, ios::in);
		int flag = 0;
		while (file >> tgid >> tgname) {
			if (tgid == tid) {
				flag = 1;
				break;
			}
		}
		if (!flag) {
			tttt(); cout << "未找到该群\n";
			any_continue(5);
			return;
		}
		else {
			int gflag = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (tgid == client->groups[i]->return_groupID()) {
					if (client->groupsflag[i] == 0) {
						tttt(); cout << "您已加入此群\n";
					}
					else if (client->groupsflag[i] == -2) {
						client->groupsflag[i] = -3;
						tttt(); cout << "入群申请已发送\n";
					}
					else {
						tttt(); cout << "入群申请已发送\n";
					}
					gflag = 1;
					break;
				}
			}
			if (!gflag) {
				for (int i = 0; i < QQgroups.size(); i++) {
					if (tgid == QQgroups[i]->return_groupID()) {
						client->groups.push_back(QQgroups[i]);
						client->groupsflag.push_back(-1);
						client->groups.back()->tempmem.push_back(client->return_ID());
					}

				}
				tttt(); cout << "入群申请已发送\n";
			}
			groupssave();
			savechange();
			any_continue(5);
			return;
		}
	}
}

void Core_QQ_Lyc::invitefriends()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				cout << endl;
			}
		}
		int select;
		string str;
		//cout << "\033[1;1H";
		//for (int i = 0; i < 5; i++)cout << endl;
		tttt(); cout << "|*==========推荐好友入群===========*|" << endl;
		tttt(); cout << "请输入您要推荐的群的ID:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				f5(7);
				tttt(); cout << "该群信息如下所示\n\n";
				tttt(); cout << "群ID：" << target->return_groupID() << endl;
				tttt(); cout << "群昵称：" << target->return_name() << endl;
				QQ_Lyc* ttarget = getself(target->return_masterID());
				tttt(); cout << "群主：" << endl;
				tttt(); cout << "ID：" << ttarget->return_ID() <<
					" 昵称：" << ttarget->return_name() << endl << endl << endl;


				tttt(); cout << "管理员：\n";
				for (int i = 0; i < target->admins.size(); i++) {
					ttarget = getself(target->admins[i]);
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl;
				}

				cout << endl;
				tttt(); cout << "普通成员：\n";
				for (int i = 0; i < target->members.size(); i++) {
					ttarget = getself(target->members[i]);
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl;
				}
				tttt(); cout << "请输入你要推荐的好友的ID:\n";
				string fid; putt(fid);
				int fflag = 0;
				QQ_Lyc* fri = nullptr;
				for (int i = 0; i < client->friends.size(); i++) {
					if (fid == client->friends[i]->return_ID()) {
						fflag = 1;
						fri = getself(fid);
					}
				}
				if (!fflag) {
					tttt(); cout << "未查询到该好友\n";
					any_continue(5);
				}
				else {
					int thflag = 0;
					for (int i = 0; i < fri->groups.size(); i++) {
						if (fri->groups[i] == target) {
							thflag = 1;
							if (fri->groupsflag[i] == -3 || fri->groupsflag[i] == -1) {
								fri->groupsflag[i] = -3;
								tttt(); cout << "邀请已发送\n";
							}
							else if (fri->groupsflag[i] == -2) {
								fri->groupsflag[i] = -2;
								tttt(); cout << "邀请已发送\n";
							}
							else if (fri->groupsflag[i] == 0) {
								tttt(); cout << "该用户已加入\n";
							}
							break;
						}
					}
					if (!thflag) {
						fri->groups.push_back(target);
						fri->groupsflag.push_back(-2);
						target->tempmem.push_back(fri->return_ID());
						tttt(); cout << "邀请已发送\n";
					}
					groupssave();
					savechange();
					any_continue(5);
				}
				return;
			}
		}
	}
}

void Core_QQ_Lyc::findmutualfriends()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->friends.empty()) {
			tttt(); cout << "目前没有好友\n";
		}
		else {
			for (int i = 0; i < client->friends.size(); i++) {
				tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
				tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
				tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
				tttt(); cout << "地区：" << client->friends[i]->return_area() << endl;
				cout << endl;
			}
		}

		//输入框
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|=========查找共同好友========|\n";
		tttt(); cout << "请输入要查找的好友ID：\n";
		tttt(); cout << "（输入-1返回菜单）\n";
		string id;
		putt(id);
		if (id == "-1") {
			return;
		}
		QQ_Lyc* target = nullptr;
		for (int i = 0; i < client->friends.size(); i++) {
			if (id == client->friends[i]->return_ID()) {
				target = getself(id);
				break;
			}
		}
		if (target == nullptr) {
			tttt(); cout << "未查找到相关用户\n";
		}
		else {
			f5(5);
			cout << endl; tttt();
			if (target->return_linkWeChat() == "0") {
				cout << "该用户暂未绑定微信\n";
			}
			else {
				cout << "该用户的绑定微信ID信息如下：" << endl;
				WeChat_Lyc* ttarget = WeChatsystem.getself(target->return_linkWeChat());
				tttt(); cout << "ID：" << ttarget->return_ID() << endl;
				tttt(); cout << "昵称：" << ttarget->return_name() << endl;
				tttt(); cout << "生日：" << ttarget->return_birthday() << endl;
				tttt(); cout << "性别：" << ttarget->return_sex() << endl;
				tttt(); cout << "地区：" << ttarget->return_area() << endl;

			}

			cout << endl; tttt();
			if (target->return_linkWeiBo() == "0") {
				cout << "该用户暂未绑定微博\n";
			}
			else {
				cout << "该用户的绑定微博ID信息如下：" << endl;
				WeiBo_Lyc* ttarget = WeiBosystem.getself(target->return_linkWeiBo());
				tttt(); cout << "ID：" << ttarget->return_ID() << endl;
				tttt(); cout << "昵称：" << ttarget->return_name() << endl;
				tttt(); cout << "生日：" << ttarget->return_birthday() << endl;
				tttt(); cout << "性别：" << ttarget->return_sex() << endl;
				tttt(); cout << "地区：" << ttarget->return_area() << endl;
			}
		}
		cout << endl; any_continue(5);
	}
}

void Core_QQ_Lyc::Qgroupmenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*=============群管理==============*|" << endl;
		tttt(); cout << "|*          1.创建群               *|" << endl;//
		tttt(); cout << "|*          2.加入群               *|" << endl;//
		tttt(); cout << "|*          3.管理群               *|" << endl;
		tttt(); cout << "|*          4.查看群信息           *|" << endl;//
		tttt(); cout << "|*          5.退出/解散群          *|" << endl;//
		tttt(); cout << "|*          6.群通讯功能               *|" << endl;//
		tttt(); cout << "|*          0.返回主菜单           *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 6);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			creategroups();
			break;
		}
		case 2:
		{
			joingroups();
			break;
		}
		case 3:
		{
			rungroups();
			break;
		}
		case 4:
		{
			viewgroups();
			break;
		}
		case 5: {
			quitgroups();
			break;
		}
		case 6:
		{
			groupchat();
			break;
		}
		case 0:return;
		}
	}
}

void Core_QQ_Lyc::solveinvitation()
{
	while (1) {
		getinfor();
		f5(5);
		vector<int>gsub;
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == -2 || client->groupsflag[i] == -3) {
				gsub.push_back(i);
			}
		}
		for (int i = 0; i < gsub.size(); i++) {
			tttt(); cout << "第" << i + 1 << "位\n";
			tttt(); cout << "群ID：" << client->groups[gsub[i]]->return_groupID() <<
				"群名：" << client->groups[gsub[i]]->return_name() << endl << endl;
		}
		if (gsub.empty()) {
			tttt(); cout << "暂无可应答的入群\n";
			any_continue(5);
			return;
		}
		else {
			tttt(); cout << "请输入你要应答的推荐入群的位数：\n";
			tttt(); cout << "(如果您选择暂不加入，该推荐入群仍然会留在您的账户中)\n";
			tttt(); cout << "(输入-1返回菜单)\n";
			int sub; putt(sub);
			if (sub == -1)return;
			if (sub<1 || sub>gsub.size()) {
				tttt(); cout << "由于超出范围，默认您要重新输入\n";
				continue;
			}
			else {
				tttt(); cout << "群ID：" << client->groups[gsub[sub - 1]]->return_groupID() <<
					"群名：" << client->groups[gsub[sub - 1]]->return_name() << endl << endl;
				tttt(); cout << "您要加入吗？\n";
				tttt(); cout << "1.加入 2.暂不加入\n";
				int opt; putt(opt);
				switch (opt)
				{
				case 1: {
					client->groupsflag[gsub[sub - 1]] = 0;
					for (int i = 0; i < client->groups[gsub[sub - 1]]->tempmem.size(); i++) {
						if (client->groups[gsub[sub - 1]]->tempmem[i] == client->return_ID()) {
							client->groups[gsub[sub - 1]]->tempmem.erase(client->groups[gsub[sub - 1]]->tempmem.begin() + i);
							client->groups[gsub[sub - 1]]->members.push_back(client->return_ID());
							groupssave();
							savechange();
						}
					}
					tttt(); cout << "操作成功\n";
					break;
				}
				case 2: {
					tttt(); cout << "操作成功\n";
					break;
				}
				default:
					tttt(); cout << "由于不合法的输出，默认您要重新输入\n";
					continue;
				}
			}
		}
		any_continue(5);
	}
}

void Core_QQ_Lyc::rungroups1()
{
	while (1) {
		getinfor();
		string QWflag = "Q";
		string conflag;
		f5(5); if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				if (client->groups[i]->tempGroups.empty()) {
					tttt(); cout << "无子群:\n";
				}
				else {
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						tttt(); cout << "群ID：" << client->groups[i]->tempGroups[j]->return_groupID() << endl;
						tttt(); cout << "群昵称：" << client->groups[i]->tempGroups[j]->return_name() << endl << endl;
					}
				}
				cout << endl;
			}
		}
		int select;
		string str;
		for (int i = 0; i < 5; i++)cout << endl;
		//1.解散/退出群
		//2.T人 
		//3/转让群主 群主专用
		//4.加入群请求处理 QQ专用
		//5.设置临时讨论组 QQ专用
		//6.设置/取消管理员 群主专用 QQ专用
		tttt(); cout << "|*=============管理群==============*|" << endl;
		tttt(); cout << "|*          1.T人                  *|" << endl;
		tttt(); cout << "|*          2.转让群主             *|" << endl;
		tttt(); cout << "请输入您要管理的群的ID:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						if (client->groups[i]->tempGroups[j]->return_groupID() == str) {
							for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
								if (client->groups[i]->tempGroups[j]->member[k] == client->return_ID()) {
									flag = 2;
									sub = i;
									tsub = j;
									target = client->groups[i];
									ttarget = client->groups[i]->tempGroups[j];
									break;
								}
							}
						}
					}
				}
			}
			if (!flag || flag == 2) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				int memflag;
				if (flag == 1) {
					f5(5);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					QQ_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;
					if (ttarget->return_ID() == client->return_ID())memflag = 2;



					tttt(); cout << "成员：\n";


					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						if (ttarget->return_ID() == client->return_ID())memflag = 1;
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						if (ttarget->return_ID() == client->return_ID())memflag = 0;
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
				}
				//cout << "\033[1;1H"; 
				//cout << "\033[100A";
				//for (int i = 0; i < 5; i++)cout << endl;
				//1.解散/退出群
				//2.T人 
				//3/转让群主 群主专用
				//4.加入群请求处理 QQ专用
				//5.设置临时讨论组 QQ专用
				//6.设置/取消管理员 群主专用 QQ专用
				tttt(); cout << "|*=============管理群==============*|" << endl;
				tttt(); cout << "|*          1.T人                  *|" << endl;//
				tttt(); cout << "|*          2.转让群主             *|" << endl;//
				tttt(); cout << "请输入您要使用的群功能:\n";
				tttt(); cout << "（输入-1返回菜单)\n";
				putt(str);
				if (str == "-1")return;
				else {
					int select = judge_input_menu(str, 6);
					switch (select) {
					case 1: {
						//tmem();
						if (flag == 2) {
							tttt(); cout << "子群无法执行T人操作\n";
							any_continue(5);
						}
						else {
							tttt(); cout << "请输入您要T的群员的ID：\n";
							string Tedid; putt(Tedid); int Tsub;
							if (memflag == 0 || memflag == 1) {
								tttt(); cout << "您无此执行功能的权限\n";
								any_continue(5);
							}
							else if (memflag == 2) {
								int Tedflag = 0, Tedstu;
								QQ_Lyc* Ted = nullptr;
								for (int i = 0; i < target->members.size(); i++) {
									if (target->members[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tedstu = 0;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								for (int i = 0; i < target->admins.size(); i++) {
									if (target->admins[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tedstu = 1;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								if (Tedid == client->return_ID()) {
									tttt(); cout << "您没有对该用户执行T人的权限\n";
									any_continue(5);
								}
								else if (!Tedflag) {
									tttt(); cout << "该群不存在此用户\n";
									any_continue(5);
								}
								else {
									if (Tedstu == 0) {
										tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
										tttt(); cout << "确定T该用户吗\n";
										tttt(); cout << "1.是2.否\n";
										int Topt; putt(Topt);
										switch (Topt) {
										case 1: {
											for (int i = 0; i < target->members.size(); i++) {
												if (target->members[i] == Ted->return_ID()) {
													target->members.erase(target->members.begin() + i);
												}
											}
											groupssave();
											Ted->groups.erase(Ted->groups.begin() + Tsub);
											Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
											break;
										}
										case 2: {
											break;
										}
										default: {
											tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
											any_continue(5);
											continue;
										}
										}
									}
									else if (Tedstu == 1) {
										tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
										tttt(); cout << "确定T该用户吗\n";
										tttt(); cout << "1.是 2.否\n";
										int Topt; putt(Topt);
										switch (Topt) {
										case 1: {
											for (int i = 0; i < target->admins.size(); i++) {
												if (target->admins[i] == Ted->return_ID()) {
													target->admins.erase(target->admins.begin() + i);
												}
											}
											groupssave();
											Ted->groups.erase(Ted->groups.begin() + Tsub);
											Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
											break;
										}
										case 2: {
											break;
										}
										default: {
											tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
											any_continue(5);
											continue;
										}
										}
									}
									tttt(); cout << "操作成功\n";
									any_continue(5);
									break;
								}
							}
						}
						break;
					}
					case 2: {
						if (target->return_masterID() == client->return_ID()) {
							int Tedflag = 0, Tedstu;
							tttt(); cout << "请输入您转让的群员的ID：\n";
							tttt(); cout << "（在转让后，您将成为普通群员）\n";
							string Tedid; putt(Tedid); int Tsub;
							QQ_Lyc* Ted = nullptr;
							for (int i = 0; i < target->members.size(); i++) {
								if (target->members[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 0;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							for (int i = 0; i < target->admins.size(); i++) {
								if (target->admins[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 1;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							if (target->return_masterID() == Tedid) {
								tttt(); cout << "您不能对自己进行此操作\n";
								any_continue(5);
							}
							else if (!Tedflag) {
								tttt(); cout << "该群不存在此用户\n";
								any_continue(5);
							}
							else {
								if (Tedstu == 0) {
									QQ_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "您确定转让给该用户吗\n";
									tttt(); cout << "1.是2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->members.size(); i++) {
											if (target->members[i] == Ted->return_ID()) {
												target->members.erase(target->members.begin() + i);
											}
										}
										target->masterID = Ted->return_ID();
										groupssave();
										target->members.push_back(client->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								else if (Tedstu == 1) {
									QQ_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "您确定转让给该用户吗\n";
									tttt(); cout << "1.是 2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->admins.size(); i++) {
											if (target->admins[i] == Ted->return_ID()) {
												target->admins.erase(target->admins.begin() + i);
											}
										}
										target->masterID = Ted->return_ID();
										groupssave();
										target->members.push_back(client->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								tttt(); cout << "操作成功\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "您没有转让群主的权限\n";
							any_continue(5);
						}
						break;
					}
					}
					groupssave();
					savechange();
				}
			}
		}
	}
}

void Core_QQ_Lyc::quitgroups1()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				cout << endl;
			}
		}
		int select;
		string str;
		for (int i = 0; i < 5; i++)cout << endl;
		tttt(); cout << "|*==========退出/解散群==========*|" << endl;
		tttt(); cout << "请输入您要退出/解散的群的ID:\n";
		tttt(); cout << "子群仅可解散:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				f5(15);
				if (flag == 1) {
					int memflag = 0;
					int memsub;

					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					QQ_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;


					tttt(); cout << "管理员：\n";
					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						if (ttarget->return_ID() == client->return_ID()) {
							memflag = 1;
							memsub = i;
						}
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					cout << endl;
					tttt(); cout << "普通成员：\n";
					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						if (ttarget->return_ID() == client->return_ID()) {
							memflag = 0;
							memsub = i;
						}
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
					cout << "\033[1;1H";
					for (int i = 0; i < 5; i++)cout << endl;

					int opt;
					if (target->return_masterID() == client->return_ID()) {//判断操作用户是否是群主
						memflag = 2;
						tttt(); cout << "您是当前群群主，若执行退群操作，则将视为解散群\n";
						tttt(); cout << "若想在保留该群的情况下退出，则请先移步管理群功能转让群主\n";
						tttt(); cout << "您要解散该群吗\n";
						tttt(); cout << "1.是 2.否\n";
						putt(opt);
					}
					else {
						tttt(); cout << "您要退出该群吗\n";
						tttt(); cout << "1.是 2.否\n";
						putt(opt);
					}

					switch (opt)
					{
					case 1: {
						if (memflag == 1) {
							target->admins.erase(target->admins.begin() + memsub);
							groupssave();
							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);
						}
						else if (memflag == 0) {
							target->members.erase(target->members.begin() + memsub);
							groupssave();
							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);
						}
						else if (memflag == 2) {
							//管理员退群
							for (int i = 0; i < target->admins.size(); i++) {
								QQ_Lyc* tttarget = getself(target->admins[i]);
								for (int j = 0; j < tttarget->return_groups().size(); j++) {
									if (tttarget->groups[j]->return_groupID() == target->return_groupID()) {
										tttarget->groups.erase(tttarget->groups.begin() + i);
										break;
									}
								}
							}
							//普通成员退群
							for (int i = 0; i < target->members.size(); i++) {
								QQ_Lyc* tttarget = getself(target->members[i]);
								for (int j = 0; j < tttarget->return_groups().size(); j++) {
									if (tttarget->groups[j]->return_groupID() == target->return_groupID()) {
										tttarget->groups.erase(tttarget->groups.begin() + i);
										break;
									}
								}
							}

							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);

							//删除总群文件内的该群信息
							ofstream file1;
							ifstream file2;
							string filename0 = "QQ\\Groups\\groupslist.txt";
							vector<string>tempid, tempname;
							string tid, tname;
							file2.open(filename0, ios::in);
							while (file2 >> tid >> tname) {
								if (tid != target->return_groupID()) {
									tempid.push_back(tid);
									tempname.push_back(tname);
								}
							}
							file2.close();
							file1.open(filename0, ios::out);
							while (!tempid.empty()) {
								file1 << *tempid.begin() << endl << *tempname.begin()
									<< endl << endl;
								tempid.erase(tempid.begin());
								tempname.erase(tempname.begin());

							}

							string filename = "QQ\\Groups\\" + target->return_groupID();
							string filename1 = filename + "\\" + target->return_groupID() + ".txt";
							string filename2 = filename + "\\" + target->return_groupID() + "admins.txt";
							string filename5 = filename + "\\" + target->return_groupID() + "tempmem.txt";
							DeleteFile(filename1.c_str());
							DeleteFile(filename2.c_str());
							DeleteFile(filename5.c_str());

							//删除子群信息
							string filename3 = filename + "\\" + target->return_groupID() + "songroups";
							for (int i = 0; i < target->tempGroups.size(); i++) {
								string tgid = target->tempGroups[i]->return_groupID();
								string filename4 = filename3 + "\\" + tgid + ".txt";
								DeleteFile(filename4.c_str());

							}
							string filename4 = filename3 + "\\list.txt";
							DeleteFile(filename4.c_str());

							RemoveDirectory(filename3.c_str());
							RemoveDirectory(filename.c_str());

							delete target;
						}
						break;
					}case 2: {
						break;
					}
					default: {
						tttt(); cout << "由于检测到不合法的输出，默认您要重新输入要退出/解散的群ID\n";
						any_continue(5);
						continue;
					}
					}
				}
				groupssave();
				savechange();
				cout << endl;
				tttt(); cout << "操作成功\n";
				tttt(); cout << "按回车键返回菜单\n";
				tttt(); getchar();
				return;
			}
		}
	}
}

void Core_QQ_Lyc::groupchat()
{
	while (1) {
		f5(5);
		tttt(); cout << "请输入您要进行通讯的群的ID:\n";
		tttt(); cout << "(输入-1返回)\n";
		string gid; putt(gid);
		if (gid == "-1")return;
		int flag = 0;
		for (int i = 0; i < client->groups.size(); i++) {
			if (gid == client->groups[i]->groupID) {
				if (client->groupsflag[i] == 0) {
					flag = 1;
					break;
				}
			}
		}
		if (!flag) {
			tttt(); cout << "未找到该群\n";
			any_continue(5);
		}
		else {
			vchat(gid, QQsystem);
		}
	}
}






QQ_Lyc* Core_QQ_Lyc::getself(string id)
{
	for (int i = 0; i < QQs.size(); i++) {
		if (QQs[i]->return_ID() == id) {
			return QQs[i];
		}
	}

	return nullptr;
}

//vector<WeChat_Lyc*> Core_WeChat_Lyc::return_WeChats()
//{
//	return WeChats;
//}

void Core_WeChat_Lyc::mainmenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*==============微信===============*|" << endl;
		tttt(); cout << "|*             1.登录              *|" << endl;
		tttt(); cout << "|*             2.注册              *|" << endl;
		tttt(); cout << "|*             0.返回主菜单        *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:"; cin >> str;
		clear_inputBuffer(stdin);
		select = judge_input_menu(str, 2);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			login();
			break;
		case 2:
			enroll();
			break;
		case 0:return;
		}
		}
	}
}

void Core_WeChat_Lyc::submenu()
{
	client->flag = 1;
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*===========欢迎使用微信=========*|" << endl;
		tttt(); cout << "|*            1.个人信息          *|" << endl;
		tttt(); cout << "|*            2.好友管理          *|" << endl;
		tttt(); cout << "|*            3.群管理            *|" << endl;
		tttt(); cout << "|*            4.开通管理          *|" << endl;
		tttt(); cout << "|*            5.登录管理          *|" << endl;
		tttt(); cout << "|*            0.返回主菜单        *|" << endl;
		tttt(); cout << "|*================================*|" << endl;
		tttt(); cout << "请输入您的选择:"; cin >> str;
		clear_inputBuffer(stdin);
		select = judge_input_menu(str, 5);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			informenu();
			break;
		}
		case 2:
		{
			friendmenu();
			break;
		}
		case 3:
		{
			groupmenu();
			break;
		}
		case 4:
		{
			openmenu();
			break;
		}
		case 5:
		{
			loginmenu();
			break;
		case 0:return;
		}
		}
	}
}

void Core_WeChat_Lyc::login()
{
	system("CLS");
	string ID;
	bool flag = false;
	string Passwd;
	int target;
	f5(11);

	tttt(); cout << "请输入账号：\n";
	tttt(); cin >> ID;
	clear_inputBuffer(stdin);
	for (int i = 0; i < WeChats.size(); i++) {
		cout << WeChats[i]->return_ID() << endl;
		if (WeChats[i]->return_ID() == ID) {
			flag = true;
			target = i;
			break;
		}
	}
	if (!flag) {
		f5(11);
		tttt(); cout << "不存在该账号，将返回菜单\n";
		any_continue(5);
		return;
	}
	else if (WeChats[target]->return_flag() == 0) {
		while (1) {
			system("CLS");
			f5(10);
			tttt(4); cout << "  账号：" << ID << endl << endl;
			tttt(); cout << "请输入密码：\n";
			tttt(); cin >> Passwd;
			clear_inputBuffer(stdin);
			if (Passwd != WeChats[target]->return_Passwd()) {
				f5(11);
				tttt(); cout << "密码输入错误，请重新输入\n";
				any_continue(5);
			}
			else break;
		}
	}
	client = WeChats[target];
	client->get_friends();
	client->get_groups();
	client->get_links();
	client->flag = 1;
	system("CLS");
	f5(11);
	tttt(); cout << "登录成功\n";
	any_continue(5);
	submenu();
}

void Core_WeChat_Lyc::enroll(string id)
{
	system("CLS");
	WeChats.push_back(new WeChat_Lyc(id));
	savebase();
}

void Core_WeChat_Lyc::savebase()
{
	ofstream file;
	string filename = "WeChats.txt";
	file.open(filename, ios::app);
	if (WeChats.empty())return;
	WeChat_Lyc* target = WeChats.back();
	file << target->return_ID() << endl << target->return_name() << endl << target->return_Passwd() << endl
		<< target->return_birthday() << endl << target->return_sex() << endl << target->return_area() << endl
		<< target->return_applyTime() << endl;
	file.close();
	target->get_friends();
	target->get_groups();
	string filename0 = "WeChat\\" + target->return_ID() + "\\" + target->return_ID() + "links.txt";
	file.open(filename0, ios::app);
	file << "QQ 0\nWeiBo 0";
}

//void Core_WeChat_Lyc::getinfor()
//{
//	WeChats.clear();
//	WeChats.shrink_to_fit();
//	string id, name, pw, bir, sex, area, time;
//	ifstream file;
//	string filename = "WeChats.txt";
//	file.open("WeChats.txt", ios::in);
//	while (file >> id >> name >> pw >> bir >> sex >> area)
//	{
//		getline(file, time);
//		cout << time;
//		WeChats.push_back(new WeChat_Lyc(id, name, pw, bir, sex, area, time));
//		cout << id << name << pw << bir << sex << area << time << endl;
//		while (1);
//		WeChats.back()->flag = 0;
//	}
//	file.close();
//}

void Core_WeChat_Lyc::getinfor()
{
	string s;
	WeChats.clear();
	WeChats.shrink_to_fit();
	string id, name, pw, bir, sex, area, time;
	ifstream file;
	file.open("WeChats.txt", ios::in);
	while (getline(file, id) && getline(file, name) && getline(file, pw) && getline(file, bir) && getline(file, sex) && getline(file, area) && getline(file, time))
	{
		string empty;
		getline(file, empty);
		WeChats.push_back(new WeChat_Lyc(id, name, pw, bir, sex, area, time));
		WeChats.back()->flag = 0;
		WeChats.back()->get_friends();
		WeChats.back()->get_links();
	}
	for (int i = 0; i < WeChats.size(); i++) {
		if (client != nullptr) {
			if (client->return_ID() == WeChats[i]->return_ID()) {
				client = WeChats[i];
			}
		}
	}
	file.close();


	WeChatgroups.clear();
	WeChatgroups.shrink_to_fit();
	string filename0 = "WeChat\\Groups\\groupslist.txt";
	file.open(filename0, ios::in);
	while (file >> id >> name)
	{
		string empty;
		getline(file, empty);
		WeChatgroups.push_back(new QQ_Group_Lyc(id, name));

		string groupname = WeChatgroups.back()->return_groupID();
		string filename0 = "WeChat\\Groups\\" + groupname + "\\" + groupname;
		string filename1 = filename0 + ".txt";
		string id;
		ifstream file1;
		file1.open(filename1, ios::in);
		while (file1 >> id) {
			WeChatgroups.back()->members.push_back(id);
		}
		file1.close();

		string filename2 = filename0 + "admins.txt";
		file1.open(filename2, ios::app);
		file1 >> id;
		WeChatgroups.back()->masterID = id;
		while (file1 >> id) {
			WeChatgroups.back()->admins.push_back(id);
		}
		file1.close();

		string filename5 = filename0 + "tempmem.txt";
		file1.open(filename5, ios::app);
		while (file1 >> id) {
			WeChatgroups.back()->tempmem.push_back(id);
		}
		file1.close();

		string filename3 = filename0 + "songroups\\";
		string filename4 = filename3 + "list.txt";
		string tgid, tgname;
		file1.open(filename4, ios::app);
		while (file1 >> tgid >> tgname) {
			WeChatgroups.back()->tempGroups.push_back(new Temp_Group_Lyc(tgid, tgname));
		}
		file1.close();
		for (int j = 0; j < WeChatgroups.back()->tempGroups.size(); j++) {
			string filename5 = filename3 + WeChatgroups.back()->tempGroups[j]->return_groupID() + ".txt";
			file1.open(filename5, ios::app);
			string tgmid;
			while (file1 >> tgmid) {
				WeChatgroups.back()->tempGroups[j]->member.push_back(tgmid);
			}
			file1.close();
			WeChatgroups.back()->tempGroups[j]->dad = WeChatgroups.back();
		}

	}
	for (int i = 0; i < WeChats.size(); i++) {
		WeChats[i]->get_groups();
	}
	file.close();
}


void Core_WeChat_Lyc::informenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*============个人信息=============*|" << endl;
		tttt(); cout << "|*             1.查看个人信息      *|" << endl;
		tttt(); cout << "|*             2.修改昵称          *|" << endl;
		tttt(); cout << "|*             3.修改密码          *|" << endl;
		tttt(); cout << "|*             4.修改生日          *|" << endl;
		tttt(); cout << "|*             5.修改性别          *|" << endl;
		tttt(); cout << "|*             6.修改地区          *|" << endl;
		tttt(); cout << "|*             0.返回主菜单        *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 6);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			showinfor();
			break;
		}
		case 2:
		{
			changename();
			break;
		}case 3:
		{
			changepw();
			break;
		}
		case 4:
		{
			changebir();
			break;
		}case 5:
		{
			changesex();
			break;
		}
		case 6:
		{
			changearea();
			break;
		}
		case 0:return;
		}
	}
}

void Core_WeChat_Lyc::friendmenu()
{
	while (1) {
		system("CLS");
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*============好友管理=============*|" << endl;
		tttt(); cout << "|*          1.所有好友展示         *|" << endl;//
		tttt(); cout << "|*          2.修改好友备注         *|" << endl;//
		tttt(); cout << "|*          3.查询好友             *|" << endl;//
		tttt(); cout << "|*          4.查询共同好友         *|" << endl;//
		tttt(); cout << "|*          5.添加好友             *|" << endl;//
		tttt(); cout << "|*          6.删除好友             *|" << endl;//
		tttt(); cout << "|*          7.查看好友申请         *|" << endl;//
		//tttt(); cout << "|*          8.好友通讯功能      *|" << endl;
		tttt(); cout << "|*          0.返回主菜单           *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 7);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			showfriends();
			break;
		}
		case 2:
		{
			changefriendsnote();
			break;
		}case 3:
		{
			findfriends();
			break;
		}
		case 4:
		{
			findmutualfriends();
			break;
		}case 5:
		{
			addfriends();
			break;
		}
		case 6:
		{
			deletefriends();
			break;
		}
		case 7:
		{
			friendrequest();
			break;
		}
		//case 8:
		//{
		//	//friendchat();
		//	break;
		//}
		case 0:return;
		}
	}
}

void Core_WeChat_Lyc::groupmenu()
{
	while (1) {
		system("CLS");
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*========请选择群管理特色=========*|" << endl;
		tttt(); cout << "|*          1.QQ                   *|" << endl;
		tttt(); cout << "|*          2.微信                 *|" << endl;
		//		tttt(); cout << "|*          7.群通讯功能               *|" << endl;//
		tttt(); cout << "|*          0.返回主菜单           *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 5);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			Qgroupmenu();
			break;
		}
		case 2:
		{
			Wgroupmenu();
			break;
		}
		case 0:return;
		}
	}
}

void Core_WeChat_Lyc::openmenu()
{
	ofstream file;
	while (1) {
		getinfor();
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*=============开通管理============*|" << endl;
		tttt(); cout << "|*             1.绑定QQ            *|" << endl;
		tttt(); cout << "|*             2.绑定微博          *|" << endl;
		tttt(); cout << "|*             0.返回主菜单        *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:"; cin >> str;
		clear_inputBuffer(stdin);
		select = judge_input_menu(str, 2);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			if (client->return_linkQQ() != "0") {
				f5(11);
				tttt(); cout << "已绑定QQ" << endl;
				tttt(); cout << "QQID为：" << client->return_linkQQ() << endl;
				tttt(); cout << "如需开启自动登录，请移步登录管理" << endl;
				any_continue(5);
				break;
			}
			else if (client->return_linkWeiBo() != "0") {
				f5(11);
				tttt(); cout << "已绑定微博，但未绑定QQ" << endl;
				tttt(); cout << "您可以从绑定的微博开通QQ以快捷绑定QQ" << endl;
				any_continue(5);
				break;
			}
			else {
				f5(11);
				tttt(); cout << "请输入您要绑定的QQ号：\n";
				string twcid;
				tttt(); cin >> twcid;
				clear_inputBuffer(stdin);
				int num = QQsystem.QQs.size();
				int flag = 0;
				for (int i = 0; i < num; i++) {
					QQ_Lyc* tWC = QQsystem.QQs[i];
					if (tWC->return_ID() == twcid) {
						flag = 1;
						string ps;
						tttt(); cout << "请输入QQ密码：\n";
						tttt(); cin >> ps;
						clear_inputBuffer(stdin);
						if (ps == tWC->return_Passwd()) {
							//1.微信已绑定微博
							//2.微信已开通其他微x服务，QQ也开通对于微x服务，但是两者账号不同
							if (tWC->return_linkWeChat() != "0") {
								tttt(); cout << tWC->return_linkWeiBo() << endl;
								tttt(); cout << "绑定失败\n";
								tttt(); cout << "该QQ已被绑定\n";
								any_continue(5);
								break;
							}
							else {
								string filename1 = "WeChat\\" + client->return_ID() + "\\" +
									client->return_ID() + "links.txt";
								file.open(filename1, ios::out);
								file << "QQ " << tWC->return_ID() << "\nWeiBo " << tWC->return_linkWeiBo();
								file.close();
								client->get_links();

								string filename0 = "QQ\\" + tWC->return_ID() + "\\" + tWC->return_ID() + "links.txt";
								file.open(filename0, ios::out);
								file << "WeChat " << client->return_ID() <<
									"\nWeiBo " << tWC->return_linkWeiBo();
								file.close();
								tWC->get_links();

								if (tWC->linkWeiBo != "0") {
									//微博绑定
									string filename2 = "WeiBo\\" + tWC->return_ID() + "\\" +
										tWC->return_ID() + "links.txt";
									file.open(filename2, ios::out);
									file << "QQ " << tWC->return_ID() << "\nWeChat " << client->return_ID();
									file.close();
									WeiBo_Lyc* temp = WeiBosystem.getself(tWC->return_ID());
									temp->get_links();
								}

								tttt(); cout << "QQ绑定成功\n";
								tttt(); cout << "QQID为：" << client->return_linkQQ() << endl;
								tttt(); cout << "同时微信将自动绑定与QQ共享的微博（若存在）\n";
								tttt(); cout << "如需开启自动登录，请移步登录管理\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "密码错误\n";
							any_continue(5);
							break;
						}
					}
				}
				if (!flag) {
					tttt(); cout << "未找到该QQ号\n";
					any_continue(5);
				}
			}
			break;
		}
		case 2:
		{
			if (client->return_linkWeiBo() != "0") {
				f5(11);
				tttt(); cout << "已绑定微博" << endl;
				tttt(); cout << "微博ID为：" << client->return_linkQQ() << endl;
				tttt(); cout << "如需开启自动登录，请移步登录管理" << endl;
				any_continue(5);
				break;
			}
			else if (client->return_linkQQ() != "0") {
				f5(11);
				tttt(); cout << "已绑定QQ，但未绑定微博" << endl;
				tttt(); cout << "您可以从绑定的QQ开通微博以快捷绑定微博" << endl;
				any_continue(5);
				break;
			}
			else {
				f5(11);
				tttt(); cout << "请输入您要绑定的微博号：\n";
				string twcid;
				tttt(); cin >> twcid;
				clear_inputBuffer(stdin);
				int num = WeiBosystem.WeiBos.size();
				int flag = 0;
				for (int i = 0; i < num; i++) {
					WeiBo_Lyc* tWC = WeiBosystem.WeiBos[i];
					if (tWC->return_ID() == twcid) {
						flag = 1;
						string ps;
						tttt(); cout << "请输入微博密码：\n";
						tttt(); cin >> ps;
						clear_inputBuffer(stdin);
						if (ps == tWC->return_Passwd()) {
							//1.微信已绑定微博
							//2.微信已开通其他微x服务，QQ也开通对于微x服务，但是两者账号不同
							if (tWC->return_linkWeChat() != "0") {
								tttt(); cout << "绑定失败\n";
								tttt(); cout << "该微博已被绑定\n";
								any_continue(5);
								break;
							}
							else {
								string filename1 = "WeChat\\" + client->return_ID() + "\\" +
									client->return_ID() + "links.txt";
								file.open(filename1, ios::out);
								file << "QQ " << tWC->return_linkQQ() << "\nWeiBo " << tWC->return_ID();
								file.close();
								client->get_links();

								string filename0 = "WeiBo\\" + tWC->return_ID() + "\\" + tWC->return_ID() + "links.txt";
								file.open(filename0, ios::out);
								file << "WeChat " << client->return_ID() <<
									"\nQQ " << tWC->return_linkQQ();
								file.close();
								tWC->get_links();

								if (tWC->linkQQ != "0") {
									//QQ绑定
									string filename2 = "QQ\\" + tWC->return_ID() + "\\" +
										tWC->return_ID() + "links.txt";
									file.open(filename2, ios::out);
									file << "WeiBo " << tWC->return_ID() << "\nWeChat " << client->return_ID();
									file.close();
									QQ_Lyc* temp = QQsystem.getself(tWC->return_ID());
									temp->get_links();
								}

								tttt(); cout << "微博绑定成功\n";
								tttt(); cout << "微博ID为：" << client->return_linkWeiBo() << endl;
								tttt(); cout << "同时微信将自动绑定与微博共享的QQ（若存在）\n";
								tttt(); cout << "如需开启自动登录，请移步登录管理\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "密码错误\n";
							any_continue(5);
							break;
						}
					}
				}
				if (!flag) {
					tttt(); cout << "未找到该微博\n";
					any_continue(5);
				}
			}
			break;
		}
		case 0:return;
		}
	}
}

void Core_WeChat_Lyc::loginmenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*============登录管理=============*|" << endl;
		tttt(); cout << "|*             1.登录QQ            *|" << endl;
		tttt(); cout << "|*             2.登录微博          *|" << endl;
		tttt(); cout << "|*             0.返回主菜单        *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:"; cin >> str;
		clear_inputBuffer(stdin);
		select = judge_input_menu(str, 2);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			if (client->return_linkQQ() == "0") {
				f5(11);
				tttt(); cout << "您暂未开通QQ\n";
				tttt(); cout << "如需开通QQ，请移步开通管理\n";
				any_continue();
			}
			else {
				int num = QQsystem.QQs.size();
				for (int i = 0; i < num; i++) {
					QQ_Lyc* target = QQsystem.QQs[i];
					if (target->return_ID() == client->return_linkQQ())target->flag = 1;
				}
				f5(11);
				tttt(); cout << "自动登录成功\n";
				tttt(); cout << "现在您可以返回主界面登录QQ\n";
				any_continue(5);
			}
			break;
		}
		case 2:
		{
			if (client->return_linkWeiBo() == "0") {
				f5(11);
				tttt(); cout << "您暂未开通微博\n";
				tttt(); cout << "如需开通微博，请移步开通管理\n";
				any_continue();
			}
			else {
				int num = WeiBosystem.WeiBos.size();
				for (int i = 0; i < num; i++) {
					WeiBo_Lyc* target = WeiBosystem.WeiBos[i];
					if (target->return_ID() == client->return_linkWeiBo())target->flag = 1;
				}
				f5(11);
				tttt(); cout << "自动登录成功\n";
				tttt(); cout << "现在您可以返回主界面登录微博\n";
				any_continue(5);
			}
		}
		break;
		case 0:return;
		}
	}
}

void Core_WeChat_Lyc::savechange()
{
	ofstream file;
	string filename = "WeChats.txt";
	file.open(filename, ios::trunc | ios::out);
	if (WeChats.empty())return;
	int num = WeChats.size();
	for (int i = 0; i < num; i++) {
		WeChat_Lyc* target = WeChats[i];


		file << target->return_ID() << endl << target->return_name() << endl << target->return_Passwd() << endl
			<< target->return_birthday() << endl << target->return_sex() << endl << target->return_area() << endl
			<< target->return_applyTime() << endl << endl;


		ofstream file1;
		string filename1 = "WeChat\\" + target->return_ID() + "\\" + target->return_ID() + "friends.txt";
		file1.open(filename1, ios::trunc | ios::out);
		for (int j = 0; j < target->friends.size(); j++) {
			Friend_Lyc* temp = target->friends[j];
			file1 << temp->return_ID() << endl << temp->return_note() << endl << temp->return_flag() << endl << endl;
		}
		file1.close();

		ofstream file2;
		string filename2 = "WeChat\\" + target->return_ID() + "\\" + target->return_ID() + "groups.txt";
		file2.open(filename2, ios::trunc | ios::out);
		for (int j = 0; j < target->groups.size(); j++) {
			QQ_Group_Lyc* temp = target->groups[j];
			file2 << temp->return_groupID() << endl << temp->return_name() << endl;
			file2 << target->groupsflag[j] << endl << endl;
		}
		file2.close();
	}
	file.close();
	getinfor();
}

void Core_WeChat_Lyc::showinfor()
{
	while (1) {
		f5(8);
		tttt(); cout << "个人信息" << endl;
		tttt(); cout << "ID：" << client->return_ID() << endl;
		tttt(); cout << "密码：" << client->return_Passwd() << endl;
		tttt(); cout << "昵称：" << client->return_name() << endl;
		tttt(); cout << "生日：" << client->return_birthday() << endl;
		tttt(); cout << "性别：" << client->return_sex() << endl;
		tttt(); cout << "地区：" << client->return_area() << endl;
		tttt(); cout << "注册时间：" << client->return_applyTime() << endl;
		tttt(); cout << "绑定QQID：";
		if (client->return_linkQQ() != "0") {
			cout << client->return_linkQQ() << endl;
		}
		else {
			cout << "未绑定\n";
		}
		tttt(); cout << "绑定微博ID：";
		if (client->return_linkWeiBo() != "0") {
			cout << client->return_linkWeiBo() << endl;
		}
		else {
			cout << "未绑定\n";
		}
		any_continue(5);
		break;
	}
}

void Core_WeChat_Lyc::changename()
{
	int flag = 1;
	while (flag) {
		f5(8);
		tttt(); cout << "|=============修改昵称============|" << endl;
		tttt(); cout << "当前昵称：" << client->return_name() << endl << endl;
		tttt(); cout << "请输入新昵称：\n";
		tttt(); string name; cin >> name;
		clear_inputBuffer(stdin);
		tttt(); cout << "您确定使用这个昵称吗：" << name << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1): {
			flag = 0;
			client->change_name(name);
			tttt(); cout << "修改成功\n";
			savechange();
			any_continue(5);
			break;
		}
		case(2): break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
}

void Core_WeChat_Lyc::changepw()
{
	int flag = 1;
	while (flag) {
		f5(8);
		tttt(); cout << "|=============修改密码============|" << endl;
		tttt(); cout << "当前密码：" << client->return_Passwd() << endl << endl;
		tttt(); cout << "请输入新密码：\n";
		tttt(); string pw; cin >> pw;
		clear_inputBuffer(stdin);
		tttt(); cout << "请再次输入新密码：\n";
		tttt(); string tmppw; cin >> tmppw;
		clear_inputBuffer(stdin);
		if (pw == tmppw) {
			f5(13);
			tttt(); cout << "您确定使用这个密码吗：" << pw << "\n";
			tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
			int opt;
			tttt(); cin >> opt;
			clear_inputBuffer(stdin);
			switch (opt) {
			case(1): {
				flag = 0;
				client->change_passwd(pw);
				tttt(); cout << "修改成功\n";
				savechange();
				any_continue(5);
				break;
			}
			case(2):break;
			default: {
				f5(13);
				tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
				any_continue(5);
			}
			}
		}
		else {
			f5(13);
			tttt(); cout << "您输入的两次密码不相符，请重新输入!\n";
			any_continue(5);
		}
	}
}

void Core_WeChat_Lyc::changebir()
{
	int a[2][12] = { 31,28,31,30,31,30,31,31,30,31,30,31,31,29,31,30,31,30,31,31,30,31,30,31 };
	int flag = 1;
	string temp;
	while (flag) {
		f5(8);
		tttt(); cout << "|=============修改生日============|" << endl;
		tttt(); cout << "当前生日：" << client->return_birthday() << endl << endl;
		tttt(); cout << "请输入您的生日，格式为：20041213:\n";
		tttt(); cin >> temp;
		int len = temp.size();
		while (1) {
			int flag1 = 0;
			while (len != 8)
			{
				f5(8);
				tttt(); cout << "|=============修改生日============|" << endl;
				tttt(); cout << "请输入正确的日期形式：格式为：20041213:" << endl;
				tttt(); cin >> temp;
				clear_inputBuffer(stdin);
				len = temp.size();
			}
			int  year = 1000 * (temp[0] - '0') + 100 * (temp[1] - '0') + 10 * (temp[2] - '0') + temp[3] - '0';
			int  month = (temp[4] - '0') * 10 + temp[5] - '0';
			int day = (temp[6] - '0') * 10 + temp[7] - '0';
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			{
				if ((year > 9999 || year < 0) || (month > 12 || month < 1) || (day > a[1][month - 1] || day < 1))
				{
					f5(8);
					tttt(); cout << "|=============修改生日============|" << endl;
					tttt(); cout << "请输入正确的日期形式：格式为：20041213:" << endl;
					flag1 = 1;
					tttt(); cin >> temp;
					clear_inputBuffer(stdin);
				}
			}
			else
			{
				if ((year > 9999 || year < 0) || (month > 12 || month < 1) || (day > a[0][month - 1] || day < 1))
				{
					f5(8);
					tttt(); cout << "|=============修改生日============|" << endl;
					tttt(); cout << "请输入正确的日期形式：格式为：20041213:" << endl;
					flag1 = 1;
					tttt(); cin >> temp;
					clear_inputBuffer(stdin);
				}
			}
			if (!flag1)
			{
				break;
			}
		}
		f5(8);
		tttt(); cout << "|=============修改生日============|" << endl;
		tttt(); cout << "您确定使用这个生日吗：" << temp << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1): {
			flag = 0;
			client->change_bir(temp);
			tttt(); cout << "修改成功\n";
			savechange();
			any_continue(5);
			break;
		}
		case(2): break;
		default: {
			f5(8);
			tttt(); cout << "|=============修改生日============|" << endl;
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
}

void Core_WeChat_Lyc::changesex()
{
	int flag = 1;
	while (flag) {
		f5(8);
		tttt(); cout << "|=============修改性别============|" << endl;
		tttt(); cout << "当前性别：" << client->return_sex() << endl << endl;
		tttt(); cout << "请输入新性别：\n";
		tttt(); cout << "0,男性 1.女性\n";
		tttt(); int name; cin >> name;
		clear_inputBuffer(stdin);
		if (!(name == 0 || name == 1)) {

			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入" << endl;
			any_continue(5);
			continue;
		}
		string t;
		if (name == 0)t = "男";
		else t = "女";
		tttt(); cout << "您确定是这个性别吗：" << t << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1): {
			flag = 0;
			switch (name) {
			case 0:
				client->change_sex(0);
				break;
			case 1:
				client->change_sex(1);
				break;
			}
			tttt(); cout << "修改成功\n";
			savechange();
			any_continue(5);
			break;
		}
		case(2): break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
}

void Core_WeChat_Lyc::changearea()
{
	int flag = 1;
	while (flag) {
		f5(8);
		tttt(); cout << "|=============修改地区============|" << endl;
		tttt(); cout << "当前地区：" << client->return_area() << endl << endl;
		tttt(); cout << "请输入新地区：\n";
		tttt(); string name; cin >> name;
		clear_inputBuffer(stdin);
		tttt(); cout << "您确定使用这个地区吗：" << name << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1): {
			flag = 0;
			client->change_area(name);
			tttt(); cout << "修改成功\n";
			savechange();
			any_continue(5);
			break;
		}
		case(2): break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
}

void Core_WeChat_Lyc::addfriends()
{
	while (1) {
		getinfor();
		//推荐好友部分
		system("CLS");
		f5(5);
		tttt(); cout << "推荐好友：\n\n\n";
		struct qlinkfriend {
			string wid;
			string wname;
			string qid;
			string qname;
		};
		vector<qlinkfriend>wc;
		vector<qlinkfriend>wb;
		QQ_Lyc* linkwc{};
		WeiBo_Lyc* linkwb{};
		int wcflag, wbflag;
		if (client->return_linkQQ() != "0") {//当前微信账户有绑定的QQ账户
			linkwc = QQsystem.getself(client->return_linkQQ());
			for (int i = 0; i < linkwc->friends.size(); i++) {//遍历绑定的QQ账户的所有好友
				QQ_Lyc* tmpwcfriend = QQsystem.getself(linkwc->friends[i]->return_ID());
				wcflag = 1;
				if (tmpwcfriend->return_linkWeChat() != "0") {//QQ好友是否有绑定的QQ账户
					WeChat_Lyc* tmpqqfriend = WeChatsystem.getself(tmpwcfriend->return_linkWeChat());
					for (int j = 0; j < tmpqqfriend->friends.size(); j++) {//判断QQ好友的微信账户好友有无自己
						if (tmpqqfriend->friends[j]->return_ID() == client->return_ID()) {
							wcflag = 0; break;
						}
					}
					if (wcflag) {
						wc.push_back({ tmpwcfriend->return_ID(),tmpwcfriend->return_name(),
							tmpqqfriend->return_ID(),tmpqqfriend->return_name() });
					}
				}
			}
		}
		if (client->return_linkWeiBo() != "0") {//当前微信账户有绑定的微博账户
			linkwb = WeiBosystem.getself(client->return_linkWeiBo());
			for (int i = 0; i < linkwb->friends.size(); i++) {//遍历绑定的微博账户的所有好友
				WeiBo_Lyc* tmpwbfriend = WeiBosystem.getself(linkwb->friends[i]->return_ID());
				wbflag = 1;
				if (tmpwbfriend->return_linkWeChat() != "0") {//微博好友是否有绑定的微信账户
					WeChat_Lyc* tmpqqfriend = getself(tmpwbfriend->return_linkWeChat());
					for (int j = 0; j < tmpqqfriend->friends.size(); j++) {//判断微博好友的微信账户好友有无自己
						if (tmpqqfriend->friends[j]->return_ID() == client->return_ID()) {
							wbflag = 0; break;
						}
					}
					if (wbflag) {
						wb.push_back({ tmpwbfriend->return_ID(),tmpwbfriend->return_name(),
							tmpqqfriend->return_ID(),tmpqqfriend->return_name() });
					}
				}
			}
		}
		tttt(); cout << "来自QQ的推荐好友：\n\n";
		if (wc.empty()) {
			tttt(); cout << "无\n\n";
		}
		else {
			for (int i = 0; i < wc.size(); i++) {
				tttt(); cout << "您的QQ好友：" <<
					"ID:" << wc[i].wid << " 名字： " << wc[i].wname << endl;
				tttt(); cout << "其微信ID：" << wc[i].qid << " 名字： " << wc[i].qid << endl << endl;
			}
			wc.clear();
		}
		cout << endl;
		tttt(); cout << "来自微博的推荐好友：\n\n";
		if (wb.empty()) {
			tttt(); cout << "无\n\n";
		}
		else {
			for (int i = 0; i < wb.size(); i++) {
				tttt(); cout << "您的微博好友：" <<
					"ID:" << wb[i].wid << " 名字： " << wb[i].wname << endl;
				tttt(); cout << "其微信ID：" << wb[i].qid << " 名字： " << wb[i].qid << endl << endl;
			}
			wb.clear();
		}
		//添加部分

		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|===========添加好友==========|\n";
		tttt(); cout << "请输入您要添加的好友的ID：（输入-1返回菜单）\n";
		string id; putt(id);
		if (id == "-1") {
			return;
		}
		else if (id == client->return_ID()) {
			tttt(); cout << "您不能添加自己为好友\n";
			any_continue(5);
			continue;
		}
		else {
			int flag1 = 0;
			WeChat_Lyc* target{};
			for (int i = 0; i < WeChats.size(); i++) {
				if (WeChats[i]->return_ID() == id) {
					flag1 = 1;
					target = WeChats[i];
					break;
				}
			}
			if (!flag1) {
				tttt(); cout << "未找到该用户\n";
				any_continue(5);
				continue;
			}
			for (int i = 0; i < client->friends.size(); i++) {
				if (target->return_ID() == client->friends[i]->return_ID()) {
					if (client->friends[i]->return_flag() == 1) {
						tttt(); cout << "您已添加该好友\n";
						any_continue(5);
						return;
					}
					else if (client->friends[i]->return_flag() == 0) {
						//确认信息
						tttt(); cout << "发送好友成功，请等待对方确认\n";
						any_continue(5);
						return;
					}
					else if (client->friends[i]->return_flag() == -1) {
						tttt(); cout << "对方在此前已向您发出好友请求\n";
						tttt(); cout << "添加好友成功\n";
						any_continue(5);
						client->friends[i]->change_flag(1);
						savechange();
						return;
					}
				}
			}
			//具体操作
			target->friends.push_back(new Friend_Lyc(client->return_ID(), client->return_name(),
				client->return_birthday(), client->return_sex(), client->return_area(), -1));
			client->friends.push_back(new Friend_Lyc(target->return_ID(), target->return_name(),
				target->return_birthday(), target->return_sex(), target->return_area(), 0));

			savechange();
			tttt(); cout << "发送好友成功，请等待对方确认\n";
			any_continue(5);
			continue;
		}
	}
}

void Core_WeChat_Lyc::friendrequest()
{
	while (1) {
		getinfor();
		//展示好友申请列表
		f5(5);
		vector<Friend_Lyc*>tmp;
		for (int i = 0; i < client->friends.size(); i++) {
			Friend_Lyc* target = client->friends[i];
			if (target->return_flag() == -1) {
				tmp.push_back(target);
			}
		}
		if (tmp.empty()) {
			tttt(); cout << "目前没有好友申请\n";
		}
		else {
			for (int i = 0; i < tmp.size(); i++) {
				tttt(); cout << "第" << i + 1 << "个\n";
				tttt(); cout << "ID：" << tmp[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << tmp[i]->return_name() << endl;
				tttt(); cout << "备注：" << tmp[i]->return_note() << endl;
				tttt(); cout << "生日：" << tmp[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << tmp[i]->return_sex() << endl;
				tttt(); cout << "地区：" << tmp[i]->return_area() << endl;
				cout << endl;
			}
		}
		//输入框
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|=========查看好友申请========|\n";
		tttt(); cout << "请输入您要处理的好友申请：\n";
		tttt(); cout << "（输入对应序号表示处理对应序号好友申请，输入-1返回菜单）\n";
		int sub; putt(sub);
		if (sub == -1) {
			return;
		}
		else if (sub >= 1 && sub <= tmp.size()) {
			cout << endl;
			tttt(); cout << "第" << sub << "个\n";
			tttt(); cout << "ID：" << tmp[sub - 1]->return_ID() << endl;
			tttt(); cout << "昵称：" << tmp[sub - 1]->return_name() << endl;
			tttt(); cout << "备注：" << tmp[sub - 1]->return_note() << endl;
			tttt(); cout << "生日：" << tmp[sub - 1]->return_birthday() << endl;
			tttt(); cout << "性别：" << tmp[sub - 1]->return_sex() << endl;
			tttt(); cout << "地区：" << tmp[sub - 1]->return_area() << endl;
			tttt(); cout << "您要同意该用户的好友申请吗？\n";
			tttt(); cout << "1.同意 2.拒绝\n";
			int opt; putt(opt);
			switch (opt) {
			case 1: {
				for (int i = 0; i < client->friends.size(); i++) {
					if (client->friends[i]->return_ID() == tmp[sub - 1]->return_ID())
					{
						client->friends[i]->change_flag(1);
						break;
					}
				}
				WeChat_Lyc* target = getself(tmp[sub - 1]->return_ID());
				for (int i = 0; i < target->friends.size(); i++) {
					if (target->friends[i]->return_ID() == client->return_ID())
					{
						target->friends[i]->change_flag(1);
						break;
					}
				}
				savechange();
				tttt(); cout << "操作成功\n";
				any_continue(5);
				break;
			}
			case 2: {
				for (int i = 0; i < client->friends.size(); i++) {
					if (client->friends[i]->return_ID() == tmp[sub - 1]->return_ID())
					{
						client->friends.erase(client->friends.begin() + i);
						break;
					}
				}
				WeChat_Lyc* target = getself(tmp[sub - 1]->return_ID());
				for (int i = 0; i < target->friends.size(); i++) {
					if (target->friends[i]->return_ID() == client->return_ID())
					{
						target->friends.erase(target->friends.begin() + i);
						break;
					}
				}
				//cout << client->friends.size();
				//while (1);
				savechange();
				tttt(); cout << "操作成功\n";
				any_continue(5);
				break;
			}
			default: {
				tttt(); cout << "由于检测到不合法输出\n";
				tttt(); cout << "默认您要重新输入要处理的好友请求\n";
				any_continue(5);
				continue;
			}
			}
		}
		else {
			tttt(); cout << "您的输入范围有误\n";
			any_continue(5);
		}
	}
}

void Core_WeChat_Lyc::deletefriends()
{
	while (1) {
		getinfor();
		f5(5);
		vector<Friend_Lyc*>tmp;
		for (int i = 0; i < client->friends.size(); i++) {
			Friend_Lyc* target = client->friends[i];
			if (target->return_flag() == 1) {
				tmp.push_back(target);
			}
		}
		if (tmp.empty()) {
			tttt(); cout << "目前没有好友\n";
		}
		else {
			for (int i = 0; i < tmp.size(); i++) {
				tttt(); cout << "ID：" << tmp[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << tmp[i]->return_name() << endl;
				tttt(); cout << "备注：" << tmp[i]->return_note() << endl;
				tttt(); cout << "生日：" << tmp[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << tmp[i]->return_sex() << endl;
				tttt(); cout << "地区：" << tmp[i]->return_area() << endl;
				cout << endl;
			}
		}

		//输入框
		cout << "\033[1;1H";
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|===========删除好友==========|\n";
		tttt(); cout << "请输入您要删除的好友ID：\n";
		tttt(); cout << "（输入-1返回菜单）\n";
		string id; putt(id);
		if (id == "-1") {
			return;
		}
		else {
			Friend_Lyc* target = nullptr;
			int sub;
			for (int i = 0; i < client->friends.size(); i++) {
				if (client->friends[i]->return_ID() == id) {
					target = client->friends[i];
					sub = i;
					break;
				}
			}
			if (target == nullptr) {
				tttt(); cout << "您暂未添加该用户为好友\n";
				any_continue(5);
				continue;
			}
			else {
				cout << endl;
				tttt(); cout << "ID：" << target->return_ID() << endl;
				tttt(); cout << "昵称：" << target->return_name() << endl;
				tttt(); cout << "备注：" << target->return_note() << endl;
				tttt(); cout << "生日：" << target->return_birthday() << endl;
				tttt(); cout << "性别：" << target->return_sex() << endl;
				tttt(); cout << "地区：" << target->return_area() << endl;
				tttt(); cout << "您要删除该好友吗？\n";
				tttt(); cout << "1.确认 2.取消\n";
				int opt; putt(opt);
				switch (opt)
				{
				case 1: {
					WeChat_Lyc* ttarget = getself(target->return_ID());
					client->friends.erase(client->friends.begin() + sub);
					for (int i = 0; i < ttarget->friends.size(); i++) {
						if (ttarget->friends[i]->return_ID() == client->return_ID()) {
							ttarget->friends.erase(ttarget->friends.begin() + sub);
							break;
						}
					}
					savechange();
					break;
				}
				case 2: {
					tttt(); cout << "操作成功\n";
					any_continue(5);
					break;
				}
				default: {
					tttt(); cout << "由于检测到不合法输出\n";
					tttt(); cout << "默认您要重新输入要删除的好友\n";
					any_continue(5);
					break;
				}
				}
			}
		}
	}
}

void Core_WeChat_Lyc::showfriends()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->friends.empty()) {
			tttt(); cout << "目前没有好友\n";
		}
		else {
			for (int i = 0; i < client->friends.size(); i++) {
				tttt(); cout << "第" << i + 1 << "位" << endl;
				tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
				tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
				tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
				tttt(); cout << "地区：" << client->friends[i]->return_area() << endl;
				cout << endl;
			}
		}

		//输入框
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|=========所有好友展示========|\n";
		tttt(); cout << "按回车键返回菜单\n";
		tttt(); string s;
		if (cin.peek()) {
			clear_inputBuffer(stdin);
			return;
		}
	}
}

void Core_WeChat_Lyc::changefriendsnote()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->friends.empty()) {
			tttt(); cout << "目前没有好友\n";
		}
		else {
			for (int i = 0; i < client->friends.size(); i++) {
				tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
				tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
				tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
				tttt(); cout << "地区：" << client->friends[i]->return_area() << endl;
				cout << endl;
			}
		}

		//输入框
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|=========修改好友备注========|\n";
		tttt(); cout << "请输入您要修改备注的好友ID：\n";
		tttt(); cout << "（输入-1返回菜单）\n";
		string id; putt(id);
		if (id == "-1") {
			return;
		}
		else {
			Friend_Lyc* target = nullptr;
			int sub;
			for (int i = 0; i < client->friends.size(); i++) {
				if (client->friends[i]->return_ID() == id) {
					target = client->friends[i];
					sub = i;
					break;
				}
			}
			if (target == nullptr) {
				tttt(); cout << "您暂未添加该用户为好友\n";
				any_continue(5);
				continue;
			}
			else {
				tttt(); cout << "请输入新备注：\n";
				string note; putt(note);
				target->note = note;
				savechange();
				tttt(); cout << "操作成功\n";
				any_continue(5);
				continue;
			}
		}
	}
}

void Core_WeChat_Lyc::findfriends()
{
	while (1) {
		getinfor();
		//输入框
		system("CLS");
		f5(3);
		int opt;
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|==============查找好友============|\n";
		tttt(); cout << "|*            1.ID                *|" << endl;
		tttt(); cout << "|*            2.昵称              *|" << endl;
		tttt(); cout << "|*            3.备注              *|" << endl;
		tttt(); cout << "|*            4.生日              *|" << endl;
		tttt(); cout << "|*            5.性别              *|" << endl;
		tttt(); cout << "|*            6.地区              *|" << endl;
		tttt(); cout << "|*            0.返回菜单          *|" << endl;
		tttt(); cout << "|*================================*|" << endl;
		tttt(); cout << "请选择您要查找的方式：\n";
		putt(opt);
		switch (opt) {
		case 1: {
			string id;
			tttt(); cout << "请输入要查找的ID：\n";
			putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_ID()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
					break;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
		}
		case 2: {
			string id;
			tttt(); cout << "请输入要查找的昵称：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_name()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
		}
		case 3: {
			string id;
			tttt(); cout << "请输入要查找的备注：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_note()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
		}
		case 4: {
			string id;
			tttt(); cout << "请输入要查找的生日：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_birthday()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
		}
		case 5: {
			string id;
			tttt(); cout << "请输入要查找的性别：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_sex()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
			break;
		}
		case 6: {
			string id;
			tttt(); cout << "请输入要查找的地区：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_area()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
			break;
		}
		case 0: {
			return;
		}
		}
	}
}

void Core_WeChat_Lyc::findmutualfriends()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->friends.empty()) {
			tttt(); cout << "目前没有好友\n";
		}
		else {
			for (int i = 0; i < client->friends.size(); i++) {
				tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
				tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
				tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
				tttt(); cout << "地区：" << client->friends[i]->return_area() << endl;
				cout << endl;
			}
		}

		//输入框
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|=========查找共同好友========|\n";
		tttt(); cout << "请输入要查找的好友ID：\n";
		tttt(); cout << "（输入-1返回菜单）\n";
		string id;
		putt(id);
		if (id == "-1") {
			return;
		}
		WeChat_Lyc* target = nullptr;
		for (int i = 0; i < client->friends.size(); i++) {
			if (id == client->friends[i]->return_ID()) {
				target = getself(id);
				break;
			}
		}
		if (target == nullptr) {
			tttt(); cout << "未查找到相关用户\n";
		}
		else {
			f5(5);
			cout << endl; tttt();
			if (target->return_linkQQ() == "0") {
				cout << "该用户暂未绑定QQ\n";
			}
			else {
				cout << "该用户的绑定QQID信息如下：" << endl;
				QQ_Lyc* ttarget = QQsystem.getself(target->return_linkQQ());
				tttt(); cout << "ID：" << ttarget->return_ID() << endl;
				tttt(); cout << "昵称：" << ttarget->return_name() << endl;
				tttt(); cout << "生日：" << ttarget->return_birthday() << endl;
				tttt(); cout << "性别：" << ttarget->return_sex() << endl;
				tttt(); cout << "地区：" << ttarget->return_area() << endl;

			}

			cout << endl; tttt();
			if (target->return_linkWeiBo() == "0") {
				cout << "该用户暂未绑定微博\n";
			}
			else {
				cout << "该用户的绑定微博ID信息如下：" << endl;
				WeiBo_Lyc* ttarget = WeiBosystem.getself(target->return_linkWeiBo());
				tttt(); cout << "ID：" << ttarget->return_ID() << endl;
				tttt(); cout << "昵称：" << ttarget->return_name() << endl;
				tttt(); cout << "生日：" << ttarget->return_birthday() << endl;
				tttt(); cout << "性别：" << ttarget->return_sex() << endl;
				tttt(); cout << "地区：" << ttarget->return_area() << endl;
			}
		}
		cout << endl; any_continue(5);
	}
}

void Core_WeChat_Lyc::Qgroupmenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*=============群管理==============*|" << endl;
		tttt(); cout << "|*          1.创建群               *|" << endl;//
		tttt(); cout << "|*          2.加入群               *|" << endl;//
		tttt(); cout << "|*          3.管理群               *|" << endl;
		tttt(); cout << "|*          4.查看群信息           *|" << endl;//
		tttt(); cout << "|*          5.退出/解散群          *|" << endl;//
		tttt(); cout << "|*          6.群通讯功能           *|" << endl;//
		tttt(); cout << "|*          0.返回主菜单           *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 6);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			creategroups();
			break;
		}
		case 2:
		{
			joingroups();
			break;
		}
		case 3:
		{
			rungroups();
			break;
		}
		case 4:
		{
			viewgroups();
			break;
		}
		case 5: {
			quitgroups();
			break;
		}
		case 6:
		{
			groupchat();
			break;
		}
		case 0:return;
		}
	}
}

void Core_WeChat_Lyc::Wgroupmenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*=============群管理==============*|" << endl;
		tttt(); cout << "|*          1.创建群               *|" << endl;
		tttt(); cout << "|*          2.退出群               *|" << endl;
		tttt(); cout << "|*          3.管理群               *|" << endl;
		tttt(); cout << "|*          4.查看群信息           *|" << endl;
		tttt(); cout << "|*          5.推荐好友入群         *|" << endl;
		tttt(); cout << "|*          6.应答接受入群         *|" << endl;
		tttt(); cout << "|*          7.群通讯功能           *|" << endl;
		tttt(); cout << "|*          0.返回主菜单           *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 7);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			creategroups();
			break;
		}
		case 2:
		{
			quitgroups1();
			break;
		}
		case 3:
		{
			rungroups1();
			break;
		}
		case 4:
		{
			viewgroups();
			break;
		}
		case 5: {
			invitefriends();
			break;
		}
		case 6: {
			solveinvitation();
			break;
		}
		case 7:
		{
			groupchat();
			break;
		}
		case 0:return;
		}
	}
}

void Core_WeChat_Lyc::viewgroups()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				if (client->groups[i]->tempGroups.empty()) {
					tttt(); cout << "无子群:\n";
				}
				else {
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						tttt(); cout << "群ID：" << client->groups[i]->tempGroups[j]->return_groupID() << endl;
						tttt(); cout << "群昵称：" << client->groups[i]->tempGroups[j]->return_name() << endl << endl;
					}
				}
				cout << endl;
			}
		}
		int select;
		string str;
		//cout << "\033[1;1H";
		for (int i = 0; i < 5; i++)cout << endl;
		tttt(); cout << "|*===========查看群信息============*|" << endl;
		tttt(); cout << "请输入您要查看的群的ID:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						if (client->groups[i]->tempGroups[j]->return_groupID() == str) {
							for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
								if (client->groups[i]->tempGroups[j]->member[k] == client->return_ID()) {
									flag = 2;
									sub = i;
									tsub = j;
									target = client->groups[i];
									ttarget = client->groups[i]->tempGroups[j];
									break;
								}
							}
						}
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				if (flag == 1) {
					f5(7);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					WeChat_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;


					tttt(); cout << "管理员：\n";
					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					cout << endl;
					tttt(); cout << "普通成员：\n";
					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
				}
				else if (flag == 2) {
					f5(7);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << ttarget->return_groupID() << endl;
					tttt(); cout << "群昵称：" << ttarget->return_name() << endl;
					tttt(); cout << "父群ID：" << ttarget->dad->return_groupID() << endl;
					tttt(); cout << "父群昵称：" << ttarget->dad->return_name() << endl;

					cout << endl;

					tttt(); cout << "成员：\n";
					for (int i = 0; i < ttarget->member.size(); i++) {
						WeChat_Lyc* tgmname = getself(ttarget->member[i]);
						tttt(); cout << "ID：" << tgmname->return_ID() <<
							" 昵称：" << tgmname->return_name() << endl << endl;
					}
				}

				cout << "\033[1;1H";
				for (int i = 0; i < 5; i++)cout << endl;
				tttt(); cout << "按回车键返回菜单\n";
				tttt(); getchar();
				return;
			}
		}
	}
}

void Core_WeChat_Lyc::groupssave()
{
	for (int i = 0; i < client->groups.size(); i++) {
		ofstream file0;
		string filename0 = "WeChat\\Groups\\" + client->groups[i]->return_groupID() + "\\" + client->groups[i]->return_groupID() + ".txt";
		file0.open(filename0, ios::out | ios::trunc);
		for (int j = 0; j < client->groups[i]->members.size(); j++) {
			file0 << client->groups[i]->members[j] << endl;
		}
		file0.close();

		string filename1 = "WeChat\\Groups\\" + client->groups[i]->return_groupID() + "\\" + client->groups[i]->return_groupID() + "admins.txt";
		file0.open(filename1, ios::out | ios::trunc);
		file0 << client->groups[i]->return_masterID() << endl;
		for (int j = 0; j < client->groups[i]->admins.size(); j++) {
			file0 << client->groups[i]->admins[j] << endl;
		}
		file0.close();

		string filename2 = "WeChat\\Groups\\" + client->groups[i]->return_groupID() + "\\" + client->groups[i]->return_groupID() + "tempmem.txt";
		file0.open(filename2, ios::out | ios::trunc);
		for (int j = 0; j < client->groups[i]->tempmem.size(); j++) {
			file0 << client->groups[i]->tempmem[j] << endl;
		}
		file0.close();

		for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
			string filename2 = "WeChat\\Groups\\" + client->groups[i]->return_groupID() + "\\" + client->groups[i]->return_groupID() + "songroups\\" +
				client->groups[i]->tempGroups[j]->return_groupID() + ".txt";
			file0.open(filename2, ios::out | ios::trunc);
			for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
				file0 << client->groups[i]->tempGroups[j]->member[k] << endl;
			}
		}
	}
}

void Core_WeChat_Lyc::creategroups()
{
	while (1) {
		getinfor();
		f5(10);
		tttt(); cout << "|============创建群===========|\n";
		tttt(); cout << "请输入您要创建的群的昵称：\n";
		tttt(); cout << "按回车键取消创建\n";
		string name;
		tttt();
		if (cin.peek() == '\n') {
			tttt(); cout << "取消创建成功\n";
			clear_inputBuffer(stdin);
		}
		else {
			cin >> name;
			clear_inputBuffer(stdin);

			tttt(); cout << "您确定要使用这个昵称吗:" << name << endl;
			tttt(); cout << "1.确认2.取消\n";
			int opt; putt(opt);
			switch (opt) {
			case 1: {

				int tempid = generate_ID();
				stringstream tempss;
				tempss << tempid;
				string id;
				tempss >> id;
				ofstream file;

				//向WeChat\\Groups\\groupslist.txt添加群信息
				string filename0 = "WeChat\\Groups\\groupslist.txt";
				file.open(filename0, ios::app);
				file << id << endl << name << endl << endl;
				file.close();

				string filename1 = "WeChat\\Groups\\" + id;
				CreateDirectory(filename1.c_str(), NULL);//创建文件夹
				string filename44 = filename1 + "\\" + id + "songroups";
				CreateDirectory(filename44.c_str(), NULL);//创建文件夹
				string filename45 = filename44 + "\\list.txt";
				file.open(filename45, ios::app);
				file.close();

				string filename2 = filename1 + "\\" + id + ".txt";
				file.open(filename2, ios::app);
				file.close();

				string filename3 = filename1 + "\\" + id + "admins.txt";
				file.open(filename3, ios::app);
				file << client->return_ID() << endl;
				file.close();


				string filename4 = filename1 + "\\" + id + "tempmem.txt";
				file.open(filename4, ios::app);
				file.close();

				WeChatgroups.push_back(new QQ_Group_Lyc(id, name));
				client->groups.push_back(WeChatgroups.back());
				client->groupsflag.push_back(0);
				client->groups.back()->masterID = client->return_ID();
				//client->groups.back()->admins.push_back(client->return_ID());
				tttt(); cout << "群创建成功" << endl;
				tttt(); cout << "群ID为:" << id << endl;
				tttt(); cout << "群昵称为:" << name << endl;
				savechange();
				groupssave();
				break;
			}
			case 2: {
				continue;
			}
			default: {
				tttt(); cout << "由于检测到无效的输出\n";
				tttt(); cout << "默认您要重新输入昵称\n";
				//continue;
			}
			}
		}
		tttt(); cout << "按回车键返回菜单\n";
		tttt(); getchar();
		return;
	}
}

void Core_WeChat_Lyc::quitgroups()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				if (client->groups[i]->tempGroups.empty()) {
					tttt(); cout << "无子群:\n";
				}
				else {
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						tttt(); cout << "群ID：" << client->groups[i]->tempGroups[j]->return_groupID() << endl;
						tttt(); cout << "群昵称：" << client->groups[i]->tempGroups[j]->return_name() << endl << endl;
					}
				}
				cout << endl;
			}
		}
		int select;
		string str;
		for (int i = 0; i < 5; i++)cout << endl;
		tttt(); cout << "|*==========退出/解散群==========*|" << endl;
		tttt(); cout << "请输入您要退出/解散的群的ID:\n";
		tttt(); cout << "子群仅可解散:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						if (client->groups[i]->tempGroups[j]->return_groupID() == str) {
							for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
								if (client->groups[i]->tempGroups[j]->member[k] == client->return_ID()) {
									flag = 2;
									sub = i;
									tsub = j;
									target = client->groups[i];
									ttarget = client->groups[i]->tempGroups[j];
									break;
								}
							}
						}
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				f5(15);
				if (flag == 1) {
					int memflag = 0;
					int memsub;

					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					WeChat_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;


					tttt(); cout << "管理员：\n";
					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						if (ttarget->return_ID() == client->return_ID()) {
							memflag = 1;
							memsub = i;
						}
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					cout << endl;
					tttt(); cout << "普通成员：\n";
					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						if (ttarget->return_ID() == client->return_ID()) {
							memflag = 0;
							memsub = i;
						}
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
					cout << "\033[1;1H";
					for (int i = 0; i < 5; i++)cout << endl;

					int opt;
					if (target->return_masterID() == client->return_ID()) {//判断操作用户是否是群主
						memflag = 2;
						tttt(); cout << "您是当前群群主，若执行退群操作，则将视为解散群\n";
						tttt(); cout << "若想在保留该群的情况下退出，则请先移步管理群功能转让群主\n";
						tttt(); cout << "您要解散该群吗\n";
						tttt(); cout << "1.是 2.否\n";
						putt(opt);
					}
					else {
						tttt(); cout << "您要退出该群吗\n";
						tttt(); cout << "1.是 2.否\n";
						putt(opt);
					}

					switch (opt)
					{
					case 1: {
						if (memflag == 1) {
							target->admins.erase(target->admins.begin() + memsub);
							groupssave();
							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);
						}
						else if (memflag == 0) {
							target->members.erase(target->members.begin() + memsub);
							groupssave();
							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);
						}
						else if (memflag == 2) {
							//管理员退群
							for (int i = 0; i < target->admins.size(); i++) {
								WeChat_Lyc* tttarget = getself(target->admins[i]);
								for (int j = 0; j < tttarget->return_groups().size(); j++) {
									if (tttarget->groups[j]->return_groupID() == target->return_groupID()) {
										tttarget->groups.erase(tttarget->groups.begin() + i);
										break;
									}
								}
							}
							//普通成员退群
							for (int i = 0; i < target->members.size(); i++) {
								WeChat_Lyc* tttarget = getself(target->members[i]);
								for (int j = 0; j < tttarget->return_groups().size(); j++) {
									if (tttarget->groups[j]->return_groupID() == target->return_groupID()) {
										tttarget->groups.erase(tttarget->groups.begin() + i);
										break;
									}
								}
							}

							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);

							//删除总群文件内的该群信息
							ofstream file1;
							ifstream file2;
							string filename0 = "WeChat\\Groups\\groupslist.txt";
							vector<string>tempid, tempname;
							string tid, tname;
							file2.open(filename0, ios::in);
							while (file2 >> tid >> tname) {
								if (tid != target->return_groupID()) {
									tempid.push_back(tid);
									tempname.push_back(tname);
								}
							}
							file2.close();
							file1.open(filename0, ios::out);
							while (!tempid.empty()) {
								file1 << *tempid.begin() << endl << *tempname.begin()
									<< endl << endl;
								tempid.erase(tempid.begin());
								tempname.erase(tempname.begin());

							}

							string filename = "WeChat\\Groups\\" + target->return_groupID();
							string filename1 = filename + "\\" + target->return_groupID() + ".txt";
							string filename2 = filename + "\\" + target->return_groupID() + "admins.txt";
							string filename5 = filename + "\\" + target->return_groupID() + "tempmem.txt";
							DeleteFile(filename1.c_str());
							DeleteFile(filename2.c_str());
							DeleteFile(filename5.c_str());

							//删除子群信息
							string filename3 = filename + "\\" + target->return_groupID() + "songroups";
							for (int i = 0; i < target->tempGroups.size(); i++) {
								string tgid = target->tempGroups[i]->return_groupID();
								string filename4 = filename3 + "\\" + tgid + ".txt";
								DeleteFile(filename4.c_str());

							}
							string filename4 = filename3 + "\\list.txt";
							DeleteFile(filename4.c_str());

							RemoveDirectory(filename3.c_str());
							RemoveDirectory(filename.c_str());

							delete target;
						}
						break;
					}case 2: {
						break;
					}
					default: {
						tttt(); cout << "由于检测到不合法的输出，默认您要重新输入要退出/解散的群ID\n";
						any_continue(5);
						continue;
					}
					}
				}
				else if (flag == 2) {

					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << ttarget->return_groupID() << endl;
					tttt(); cout << "群昵称：" << ttarget->return_name() << endl;
					tttt(); cout << "父群ID：" << target->return_groupID() << endl;
					tttt(); cout << "父群昵称：" << target->return_name() << endl;

					cout << endl;

					tttt(); cout << "成员：\n";
					for (int i = 0; i < ttarget->member.size(); i++) {
						WeChat_Lyc* tgmname = getself(ttarget->member[i]);
						tttt(); cout << "ID：" << tgmname->return_ID() <<
							" 昵称：" << tgmname->return_name() << endl << endl;
					}

					cout << "\033[1;1H";
					for (int i = 0; i < 5; i++)cout << endl;
					tttt(); cout << "您要退出/解散该子群吗\n";
					tttt(); cout << "1.退出 2.解散 3.取消\n";
					int opt1; putt(opt1);
					switch (opt1) {
					case 1: {
						for (int i = 0; i < client->groups[sub]->tempGroups[tsub]->member.size(); i++) {
							if (client->groups[sub]->tempGroups[tsub]->member[i] == client->return_ID()) {
								client->groups[sub]->tempGroups[tsub]->member.erase(client->groups[sub]->tempGroups[tsub]->member.begin() + i);
								groupssave();
							}
						}
						/*client->groups[sub]->tempGroups.erase(client->groups[sub]->tempGroups.begin() + tsub);*/
						break;
					}
					case 2: {
						string filename0 = "WeChat\\Groups\\" + client->groups[sub]->groupID + "\\" + client->groups[sub]->groupID + "songroups";
						string filename1 = filename0 + "\\list.txt";
						vector<string> tgvid, tgvname;
						string tgid, tgname;
						ifstream file;
						ofstream file1;
						file.open(filename1, ios::app);
						while (file >> tgid >> tgname) {
							if (tgid != client->groups[sub]->tempGroups[tsub]->return_groupID()) {
								tgvid.push_back(tgid);
								tgvname.push_back(tgname);
							}
						}
						file.close();
						file1.open(filename1, ios::trunc | ios::out);
						while (!tgvid.empty()) {
							file1 << *tgvid.begin() << endl << *tgvname.begin() << endl << endl;
						}
						string filename2 = filename0 + "\\" + ttarget->return_groupID() + ".txt";
						DeleteFile(filename2.c_str());

						client->groups[sub]->tempGroups.erase(client->groups[sub]->tempGroups.begin() + tsub);

						break;
					}
					case 3: {
						break;
					}default: {
						tttt(); cout << "由于不合法的输入，默认您要重新输入要退出/解散的群ID\n";
						any_continue(5);
						continue;
					}
					}

				}
				groupssave();
				savechange();
				cout << endl;
				tttt(); cout << "操作成功\n";
				tttt(); cout << "按回车键返回菜单\n";
				tttt(); getchar();
				return;
			}
		}
	}
}

void Core_WeChat_Lyc::rungroups()
{
	while (1) {
		getinfor();
		string QWflag = "Q";
		string conflag;
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				if (client->groups[i]->tempGroups.empty()) {
					tttt(); cout << "无子群:\n";
				}
				else {
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						tttt(); cout << "群ID：" << client->groups[i]->tempGroups[j]->return_groupID() << endl;
						tttt(); cout << "群昵称：" << client->groups[i]->tempGroups[j]->return_name() << endl << endl;
					}
				}
				cout << endl;
			}
		}
		int select;
		string str;
		for (int i = 0; i < 5; i++)cout << endl;
		//1.解散/退出群
		//2.T人 
		//3/转让群主 群主专用
		//4.加入群请求处理 WeChat专用
		//5.设置临时讨论组 WeChat专用
		//6.设置/取消管理员 群主专用 WeChat专用
		tttt(); cout << "|*=============管理群==============*|" << endl;
		tttt(); cout << "|*          1.T人                  *|" << endl;
		tttt(); cout << "|*          2.转让群主             *|" << endl;
		tttt(); cout << "|*          3.加入群请求处理       *|" << endl;
		tttt(); cout << "|*          4.设置子群             *|" << endl;
		tttt(); cout << "|*          5.设置/取消管理员      *|" << endl;
		tttt(); cout << "请输入您要管理的群的ID:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						if (client->groups[i]->tempGroups[j]->return_groupID() == str) {
							for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
								if (client->groups[i]->tempGroups[j]->member[k] == client->return_ID()) {
									flag = 2;
									sub = i;
									tsub = j;
									target = client->groups[i];
									ttarget = client->groups[i]->tempGroups[j];
									break;
								}
							}
						}
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				int memflag;
				if (flag == 1) {
					f5(5);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					WeChat_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;
					if (ttarget->return_ID() == client->return_ID())memflag = 2;


					tttt(); cout << "管理员：\n";
					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						if (ttarget->return_ID() == client->return_ID())memflag = 1;
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					cout << endl;
					tttt(); cout << "普通成员：\n";
					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						if (ttarget->return_ID() == client->return_ID())memflag = 0;
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
				}
				else if (flag == 2) {
					f5(5);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << ttarget->return_groupID() << endl;
					tttt(); cout << "群昵称：" << ttarget->return_name() << endl;
					tttt(); cout << "父群ID：" << ttarget->dad->return_groupID() << endl;
					tttt(); cout << "父群昵称：" << ttarget->dad->return_name() << endl;

					cout << endl;

					tttt(); cout << "成员：\n";
					for (int i = 0; i < ttarget->member.size(); i++) {
						WeChat_Lyc* tgmname = getself(ttarget->member[i]);
						tttt(); cout << "ID：" << tgmname->return_ID() <<
							" 昵称：" << tgmname->return_name() << endl << endl;
					}
				}
				//cout << "\033[1;1H"; 
				//cout << "\033[100A";
				//for (int i = 0; i < 5; i++)cout << endl;
				//1.解散/退出群
				//2.T人 
				//3/转让群主 群主专用
				//4.加入群请求处理 WeChat专用
				//5.设置临时讨论组 WeChat专用
				//6.设置/取消管理员 群主专用 WeChat专用
				tttt(); cout << "|*=============管理群==============*|" << endl;
				tttt(); cout << "|*          1.T人                  *|" << endl;//
				tttt(); cout << "|*          2.转让群主             *|" << endl;//
				tttt(); cout << "|*          3.加入群请求处理       *|" << endl;
				tttt(); cout << "|*          4.创建子群             *|" << endl;
				tttt(); cout << "|*          5.设置/取消管理员      *|" << endl;//
				tttt(); cout << "请输入您要使用的群功能:\n";
				tttt(); cout << "（输入-1返回菜单)\n";
				putt(str);
				if (str == "-1")return;
				else {
					int select = judge_input_menu(str, 6);
					switch (select) {
					case 1: {
						//tmem();
						if (flag == 2) {
							tttt(); cout << "子群无法执行T人操作\n";
							any_continue(5);
						}
						else {
							tttt(); cout << "请输入您要T的群员的ID：\n";
							string Tedid; putt(Tedid); int Tsub;
							if (memflag == 0) {
								tttt(); cout << "您无此执行功能的权限\n";
								any_continue(5);
							}
							else if (memflag == 1) {
								int Tedflag = 0;
								WeChat_Lyc* Ted = nullptr;
								for (int i = 0; i < target->members.size(); i++) {
									if (target->members[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								if (!Tedflag) {
									tttt(); cout << "该群不存在此用户或您没有对该用户执行T人的权限\n";
									any_continue(5);
								}
								else {
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "确定T该用户吗\n";
									tttt(); cout << "1.是2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->members.size(); i++) {
											if (target->members[i] == Ted->return_ID()) {
												target->members.erase(target->members.begin() + i);
											}
										}
										groupssave();
										Ted->groups.erase(Ted->groups.begin() + Tsub);
										Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
							}
							else if (memflag == 2) {
								int Tedflag = 0, Tedstu;
								WeChat_Lyc* Ted = nullptr;
								for (int i = 0; i < target->members.size(); i++) {
									if (target->members[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tedstu = 0;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								for (int i = 0; i < target->admins.size(); i++) {
									if (target->admins[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tedstu = 1;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								if (Tedid == client->return_ID()) {
									tttt(); cout << "您没有对该用户执行T人的权限\n";
									any_continue(5);
								}
								else if (!Tedflag) {
									tttt(); cout << "该群不存在此用户\n";
									any_continue(5);
								}
								else {
									if (Tedstu == 0) {
										tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
										tttt(); cout << "确定T该用户吗\n";
										tttt(); cout << "1.是2.否\n";
										int Topt; putt(Topt);
										switch (Topt) {
										case 1: {
											for (int i = 0; i < target->members.size(); i++) {
												if (target->members[i] == Ted->return_ID()) {
													target->members.erase(target->members.begin() + i);
												}
											}
											groupssave();
											Ted->groups.erase(Ted->groups.begin() + Tsub);
											Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
											break;
										}
										case 2: {
											break;
										}
										default: {
											tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
											any_continue(5);
											continue;
										}
										}
									}
									else if (Tedstu == 1) {
										tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
										tttt(); cout << "确定T该用户吗\n";
										tttt(); cout << "1.是 2.否\n";
										int Topt; putt(Topt);
										switch (Topt) {
										case 1: {
											for (int i = 0; i < target->admins.size(); i++) {
												if (target->admins[i] == Ted->return_ID()) {
													target->admins.erase(target->admins.begin() + i);
												}
											}
											groupssave();
											Ted->groups.erase(Ted->groups.begin() + Tsub);
											Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
											break;
										}
										case 2: {
											break;
										}
										default: {
											tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
											any_continue(5);
											continue;
										}
										}
									}
									tttt(); cout << "操作成功\n";
									any_continue(5);
									break;
								}
							}
						}
						break;
					}
					case 2: {
						if (target->return_masterID() == client->return_ID()) {
							int Tedflag = 0, Tedstu;
							tttt(); cout << "请输入您转让的群员的ID：\n";
							tttt(); cout << "（在转让后，您将成为普通群员）\n";
							string Tedid; putt(Tedid); int Tsub;
							WeChat_Lyc* Ted = nullptr;
							for (int i = 0; i < target->members.size(); i++) {
								if (target->members[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 0;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							for (int i = 0; i < target->admins.size(); i++) {
								if (target->admins[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 1;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							if (target->return_masterID() == Tedid) {
								tttt(); cout << "您不能对自己进行此操作\n";
								any_continue(5);
							}
							else if (!Tedflag) {
								tttt(); cout << "该群不存在此用户\n";
								any_continue(5);
							}
							else {
								if (Tedstu == 0) {
									WeChat_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "您确定转让给该用户吗\n";
									tttt(); cout << "1.是2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->members.size(); i++) {
											if (target->members[i] == Ted->return_ID()) {
												target->members.erase(target->members.begin() + i);
											}
										}
										target->masterID = Ted->return_ID();
										groupssave();
										target->members.push_back(client->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								else if (Tedstu == 1) {
									WeChat_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "您确定转让给该用户吗\n";
									tttt(); cout << "1.是 2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->admins.size(); i++) {
											if (target->admins[i] == Ted->return_ID()) {
												target->admins.erase(target->admins.begin() + i);
											}
										}
										target->masterID = Ted->return_ID();
										groupssave();
										target->members.push_back(client->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								tttt(); cout << "操作成功\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "您没有转让群主的权限\n";
							any_continue(5);
						}
						break;
					}
					case 3: {
						f5(5);
						tttt(); cout << "申请人：\n\n";
						int num = 1;
						for (int i = 0; i < target->tempmem.size(); i++) {
							WeChat_Lyc* tmtarget = getself(target->tempmem[i]);
							for (int j = 0; j < tmtarget->groups.size(); j++) {
								if (tmtarget->groups[j] == target) {
									if (tmtarget->groupsflag[j] == -1 || tmtarget->groupsflag[j] == -3) {
										tttt(); cout << "第" << num << "位\n";
										tttt(); cout << "ID：" << tmtarget->return_ID() << " 昵称："
											<< tmtarget->return_name() << endl << endl;
										num++;
									}
								}
							}
						}
						if (target->tempmem.empty()) {
							tttt(); cout << "暂无请求\n";
							any_continue(5);
						}
						else {
							tttt(); cout << "请输入你要处理的请求：（位）\n";
							int sub; putt(sub);
							if (sub<1 || sub>target->tempmem.size()) {
								tttt(); cout << "输入范围有误\n";
							}
							else {
								tttt(); cout << "您要同意该用户的申请吗\n";
								tttt(); cout << "1.同意 2.拒绝\n";
								int opt; putt(opt);
								switch (opt) {
								case 1: {
									WeChat_Lyc* tmtarget = getself(target->tempmem[sub - 1]);
									for (int i = 0; i < tmtarget->groups.size(); i++) {
										if (tmtarget->groups[i]->return_groupID() == target->return_groupID()) {
											target->tempmem.erase(target->tempmem.begin() + sub - 1);
											target->members.push_back(tmtarget->return_ID());
											tmtarget->groupsflag[i] = 0;
										}
									}

									tttt(); cout << "处理成功\n";
									any_continue(5);
									break;
								}
								case 2: {
									WeChat_Lyc* tmtarget = getself(target->tempmem[sub - 1]);
									for (int i = 0; i < tmtarget->groups.size(); i++) {
										if (tmtarget->groups[i]->return_groupID() == target->return_groupID()) {
											target->tempmem.erase(target->tempmem.begin() + sub - 1);
											tmtarget->groupsflag.erase(tmtarget->groupsflag.begin() + i);
											tmtarget->groups.erase(tmtarget->groups.begin() + i);
										}
									}
									tttt(); cout << "处理成功\n";
									any_continue(5);
									break;
								}
								default: {
									tttt(); cout << "由于不合法的输入，将回到菜单\n";
									any_continue(5);
								}
								}
							}
						}
						break;
					}
					case 4: {
						tttt(); cout << "子群是WeChat类型群的特有功能\n";
						tttt(); cout << "子群没有群主或管理员，不可新增成员\n";
						tttt(); cout << "子群的成员均可解散子群\n";
						tttt(); cout << "请输入你要创建的子群昵称：\n";
						string name; putt(name);
						int tid = generate_ID(); string id;
						stringstream temp;
						temp << tid;
						temp >> id;
						target->tempGroups.push_back(new Temp_Group_Lyc(id, name));
						target->tempGroups.back()->member.push_back(client->return_ID());
						tttt(); cout << "请依次输入你要从父群拉群到子群的群友ID：\n";
						tttt(); cout << "(输入-1结束)\n";
						while (1) {
							string gfriend;
							putt(gfriend);
							if (gfriend == "-1")break;
							else {
								WeChat_Lyc* Gfriend = nullptr;
								Gfriend = getself(gfriend);
								if (Gfriend) {
									target->tempGroups.back()->member.push_back(gfriend);
								}
							}
						}
						tttt(); cout << "创建成功\n";
						tttt(); cout << "群ID：" << target->tempGroups.back()->return_groupID() <<
							" 群名：" << target->tempGroups.back()->return_name() << endl;

						ofstream file;
						string filename = "WeChat\\Groups\\" + target->return_groupID() + "\\" +
							target->return_groupID() + "songroups\\list.txt";
						file.open(filename, ios::app);
						file << id << endl << name << endl;
						file.close();
						groupssave();
						savechange();
						any_continue(5);
						break;
					}
					case 5: {
						if (target->return_masterID() == client->return_ID()) {
							int Tedflag = 0, Tedstu;
							WeChat_Lyc* Ted = nullptr;
							tttt(); cout << "请输入您处理的群员的ID：\n";
							string Tedid; putt(Tedid); int Tsub;
							for (int i = 0; i < target->members.size(); i++) {
								if (target->members[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 0;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							for (int i = 0; i < target->admins.size(); i++) {
								if (target->admins[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 1;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							if (target->return_masterID() == Tedid) {
								tttt(); cout << "您不能对自己进行此操作\n";
								any_continue(5);
							}
							else if (!Tedflag) {
								tttt(); cout << "该群不存在此用户\n";
								any_continue(5);
							}
							else {
								if (Tedstu == 0) {
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "该用户是普通成员，确定将其升级为管理员吗\n";
									tttt(); cout << "1.是2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->members.size(); i++) {
											if (target->members[i] == Ted->return_ID()) {
												target->members.erase(target->members.begin() + i);
											}
										}
										groupssave();
										target->admins.push_back(Ted->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								else if (Tedstu == 1) {
									WeChat_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "该用户是管理员，确定将其降级为普通用户吗\n";
									tttt(); cout << "1.是 2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->admins.size(); i++) {
											if (target->admins[i] == Ted->return_ID()) {
												target->admins.erase(target->admins.begin() + i);
											}
										}
										groupssave();
										target->members.push_back(Ted->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								tttt(); cout << "操作成功\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "您没有设置/取消管理员权限\n";
							any_continue(5);
						}
					}
					default: {
						continue;
					}
					}
					groupssave();
					savechange();
				}
			}
		}
	}
}

void Core_WeChat_Lyc::joingroups()
{
	while (1) {
		getinfor();
		f5(7);
		tttt(); cout << "请输入你要加入的群ID：\n";
		string tid; putt(tid);
		ifstream file;
		string filename = "WeChat\\Groups\\groupslist.txt";
		string tgid, tgname;
		file.open(filename, ios::in);
		int flag = 0;
		while (file >> tgid >> tgname) {
			if (tgid == tid) {
				flag = 1;
				break;
			}
		}
		if (!flag) {
			tttt(); cout << "未找到该群\n";
			any_continue(5);
			return;
		}
		else {
			int gflag = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (tgid == client->groups[i]->return_groupID()) {
					if (client->groupsflag[i] == 0) {
						tttt(); cout << "您已加入此群\n";
					}
					else if (client->groupsflag[i] == -2) {
						client->groupsflag[i] = -3;
						tttt(); cout << "入群申请已发送\n";
					}
					else {
						tttt(); cout << "入群申请已发送\n";
					}
					gflag = 1;
					break;
				}
			}
			if (!gflag) {
				for (int i = 0; i < WeChatgroups.size(); i++) {
					if (tgid == WeChatgroups[i]->return_groupID()) {
						client->groups.push_back(WeChatgroups[i]);
						client->groupsflag.push_back(-1);
						client->groups.back()->tempmem.push_back(client->return_ID());
					}

				}
				tttt(); cout << "入群申请已发送\n";
			}
			groupssave();
			savechange();
			any_continue(5);
			return;
		}
	}
}

void Core_WeChat_Lyc::invitefriends()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				cout << endl;
			}
		}
		int select;
		string str;
		//cout << "\033[1;1H";
		//for (int i = 0; i < 5; i++)cout << endl;
		tttt(); cout << "|*==========推荐好友入群===========*|" << endl;
		tttt(); cout << "请输入您要推荐的群的ID:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				f5(7);
				tttt(); cout << "该群信息如下所示\n\n";
				tttt(); cout << "群ID：" << target->return_groupID() << endl;
				tttt(); cout << "群昵称：" << target->return_name() << endl;
				WeChat_Lyc* ttarget = getself(target->return_masterID());
				tttt(); cout << "群主：" << endl;
				tttt(); cout << "ID：" << ttarget->return_ID() <<
					" 昵称：" << ttarget->return_name() << endl << endl << endl;


				tttt(); cout << "管理员：\n";
				for (int i = 0; i < target->admins.size(); i++) {
					ttarget = getself(target->admins[i]);
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl;
				}

				cout << endl;
				tttt(); cout << "普通成员：\n";
				for (int i = 0; i < target->members.size(); i++) {
					ttarget = getself(target->members[i]);
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl;
				}
				tttt(); cout << "请输入你要推荐的好友的ID:\n";
				string fid; putt(fid);
				int fflag = 0;
				WeChat_Lyc* fri = nullptr;
				for (int i = 0; i < client->friends.size(); i++) {
					if (fid == client->friends[i]->return_ID()) {
						fflag = 1;
						fri = getself(fid);
					}
				}
				if (!fflag) {
					tttt(); cout << "未查询到该好友\n";
					any_continue(5);
				}
				else {
					int thflag = 0;
					for (int i = 0; i < fri->groups.size(); i++) {
						if (fri->groups[i] == target) {
							thflag = 1;
							if (fri->groupsflag[i] == -3 || fri->groupsflag[i] == -1) {
								fri->groupsflag[i] = -3;
								tttt(); cout << "邀请已发送\n";
							}
							else if (fri->groupsflag[i] == -2) {
								fri->groupsflag[i] = -2;
								tttt(); cout << "邀请已发送\n";
							}
							else if (fri->groupsflag[i] == 0) {
								tttt(); cout << "该用户已加入\n";
							}
							break;
						}
					}
					if (!thflag) {
						fri->groups.push_back(target);
						fri->groupsflag.push_back(-2);
						target->tempmem.push_back(fri->return_ID());
						tttt(); cout << "邀请已发送\n";
					}
					groupssave();
					savechange();
					any_continue(5);
				}
				return;
			}
		}
	}
}

void Core_WeChat_Lyc::solveinvitation()
{
	while (1) {
		getinfor();
		f5(5);
		vector<int>gsub;
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == -2 || client->groupsflag[i] == -3) {
				gsub.push_back(i);
			}
		}
		for (int i = 0; i < gsub.size(); i++) {
			tttt(); cout << "第" << i + 1 << "位\n";
			tttt(); cout << "群ID：" << client->groups[gsub[i]]->return_groupID() <<
				"群名：" << client->groups[gsub[i]]->return_name() << endl << endl;
		}
		if (gsub.empty()) {
			tttt(); cout << "暂无可应答的入群\n";
			any_continue(5);
			return;
		}
		else {
			tttt(); cout << "请输入你要应答的推荐入群的位数：\n";
			tttt(); cout << "(如果您选择暂不加入，该推荐入群仍然会留在您的账户中)\n";
			tttt(); cout << "(输入-1返回菜单)\n";
			int sub; putt(sub);
			if (sub == -1)return;
			if (sub<1 || sub>gsub.size()) {
				tttt(); cout << "由于超出范围，默认您要重新输入\n";
				continue;
			}
			else {
				tttt(); cout << "群ID：" << client->groups[gsub[sub - 1]]->return_groupID() <<
					"群名：" << client->groups[gsub[sub - 1]]->return_name() << endl << endl;
				tttt(); cout << "您要加入吗？\n";
				tttt(); cout << "1.加入 2.暂不加入\n";
				int opt; putt(opt);
				switch (opt)
				{
				case 1: {
					client->groupsflag[gsub[sub - 1]] = 0;
					for (int i = 0; i < client->groups[gsub[sub - 1]]->tempmem.size(); i++) {
						if (client->groups[gsub[sub - 1]]->tempmem[i] == client->return_ID()) {
							client->groups[gsub[sub - 1]]->tempmem.erase(client->groups[gsub[sub - 1]]->tempmem.begin() + i);
							client->groups[gsub[sub - 1]]->members.push_back(client->return_ID());
							groupssave();
							savechange();
						}
					}
					tttt(); cout << "操作成功\n";
					break;
				}
				case 2: {
					tttt(); cout << "操作成功\n";
					break;
				}
				default:
					tttt(); cout << "由于不合法的输出，默认您要重新输入\n";
					continue;
				}
			}
		}
		any_continue(5);
	}
}

void Core_WeChat_Lyc::rungroups1()
{
	while (1) {
		getinfor();
		string QWflag = "Q";
		string conflag;
		f5(5); if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				if (client->groups[i]->tempGroups.empty()) {
					tttt(); cout << "无子群:\n";
				}
				else {
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						tttt(); cout << "群ID：" << client->groups[i]->tempGroups[j]->return_groupID() << endl;
						tttt(); cout << "群昵称：" << client->groups[i]->tempGroups[j]->return_name() << endl << endl;
					}
				}
				cout << endl;
			}
		}
		int select;
		string str;
		for (int i = 0; i < 5; i++)cout << endl;
		//1.解散/退出群
		//2.T人 
		//3/转让群主 群主专用
		//4.加入群请求处理 WeChat专用
		//5.设置临时讨论组 WeChat专用
		//6.设置/取消管理员 群主专用 WeChat专用
		tttt(); cout << "|*=============管理群==============*|" << endl;
		tttt(); cout << "|*          1.T人                  *|" << endl;
		tttt(); cout << "|*          2.转让群主             *|" << endl;
		tttt(); cout << "请输入您要管理的群的ID:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						if (client->groups[i]->tempGroups[j]->return_groupID() == str) {
							for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
								if (client->groups[i]->tempGroups[j]->member[k] == client->return_ID()) {
									flag = 2;
									sub = i;
									tsub = j;
									target = client->groups[i];
									ttarget = client->groups[i]->tempGroups[j];
									break;
								}
							}
						}
					}
				}
			}
			if (!flag || flag == 2) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				int memflag;
				if (flag == 1) {
					f5(5);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					WeChat_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;
					if (ttarget->return_ID() == client->return_ID())memflag = 2;



					tttt(); cout << "成员：\n";


					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						if (ttarget->return_ID() == client->return_ID())memflag = 1;
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						if (ttarget->return_ID() == client->return_ID())memflag = 0;
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
				}
				//cout << "\033[1;1H"; 
				//cout << "\033[100A";
				//for (int i = 0; i < 5; i++)cout << endl;
				//1.解散/退出群
				//2.T人 
				//3/转让群主 群主专用
				//4.加入群请求处理 WeChat专用
				//5.设置临时讨论组 WeChat专用
				//6.设置/取消管理员 群主专用 WeChat专用
				tttt(); cout << "|*=============管理群==============*|" << endl;
				tttt(); cout << "|*          1.T人                  *|" << endl;//
				tttt(); cout << "|*          2.转让群主             *|" << endl;//
				tttt(); cout << "请输入您要使用的群功能:\n";
				tttt(); cout << "（输入-1返回菜单)\n";
				putt(str);
				if (str == "-1")return;
				else {
					int select = judge_input_menu(str, 6);
					switch (select) {
					case 1: {
						//tmem();
						if (flag == 2) {
							tttt(); cout << "子群无法执行T人操作\n";
							any_continue(5);
						}
						else {
							tttt(); cout << "请输入您要T的群员的ID：\n";
							string Tedid; putt(Tedid); int Tsub;
							if (memflag == 0 || memflag == 1) {
								tttt(); cout << "您无此执行功能的权限\n";
								any_continue(5);
							}
							else if (memflag == 2) {
								int Tedflag = 0, Tedstu;
								WeChat_Lyc* Ted = nullptr;
								for (int i = 0; i < target->members.size(); i++) {
									if (target->members[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tedstu = 0;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								for (int i = 0; i < target->admins.size(); i++) {
									if (target->admins[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tedstu = 1;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								if (Tedid == client->return_ID()) {
									tttt(); cout << "您没有对该用户执行T人的权限\n";
									any_continue(5);
								}
								else if (!Tedflag) {
									tttt(); cout << "该群不存在此用户\n";
									any_continue(5);
								}
								else {
									if (Tedstu == 0) {
										tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
										tttt(); cout << "确定T该用户吗\n";
										tttt(); cout << "1.是2.否\n";
										int Topt; putt(Topt);
										switch (Topt) {
										case 1: {
											for (int i = 0; i < target->members.size(); i++) {
												if (target->members[i] == Ted->return_ID()) {
													target->members.erase(target->members.begin() + i);
												}
											}
											groupssave();
											Ted->groups.erase(Ted->groups.begin() + Tsub);
											Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
											break;
										}
										case 2: {
											break;
										}
										default: {
											tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
											any_continue(5);
											continue;
										}
										}
									}
									else if (Tedstu == 1) {
										tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
										tttt(); cout << "确定T该用户吗\n";
										tttt(); cout << "1.是 2.否\n";
										int Topt; putt(Topt);
										switch (Topt) {
										case 1: {
											for (int i = 0; i < target->admins.size(); i++) {
												if (target->admins[i] == Ted->return_ID()) {
													target->admins.erase(target->admins.begin() + i);
												}
											}
											groupssave();
											Ted->groups.erase(Ted->groups.begin() + Tsub);
											Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
											break;
										}
										case 2: {
											break;
										}
										default: {
											tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
											any_continue(5);
											continue;
										}
										}
									}
									tttt(); cout << "操作成功\n";
									any_continue(5);
									break;
								}
							}
						}
						break;
					}
					case 2: {
						if (target->return_masterID() == client->return_ID()) {
							int Tedflag = 0, Tedstu;
							tttt(); cout << "请输入您转让的群员的ID：\n";
							tttt(); cout << "（在转让后，您将成为普通群员）\n";
							string Tedid; putt(Tedid); int Tsub;
							WeChat_Lyc* Ted = nullptr;
							for (int i = 0; i < target->members.size(); i++) {
								if (target->members[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 0;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							for (int i = 0; i < target->admins.size(); i++) {
								if (target->admins[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 1;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							if (target->return_masterID() == Tedid) {
								tttt(); cout << "您不能对自己进行此操作\n";
								any_continue(5);
							}
							else if (!Tedflag) {
								tttt(); cout << "该群不存在此用户\n";
								any_continue(5);
							}
							else {
								if (Tedstu == 0) {
									WeChat_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "您确定转让给该用户吗\n";
									tttt(); cout << "1.是2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->members.size(); i++) {
											if (target->members[i] == Ted->return_ID()) {
												target->members.erase(target->members.begin() + i);
											}
										}
										target->masterID = Ted->return_ID();
										groupssave();
										target->members.push_back(client->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								else if (Tedstu == 1) {
									WeChat_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "您确定转让给该用户吗\n";
									tttt(); cout << "1.是 2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->admins.size(); i++) {
											if (target->admins[i] == Ted->return_ID()) {
												target->admins.erase(target->admins.begin() + i);
											}
										}
										target->masterID = Ted->return_ID();
										groupssave();
										target->members.push_back(client->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								tttt(); cout << "操作成功\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "您没有转让群主的权限\n";
							any_continue(5);
						}
						break;
					}
					}
					groupssave();
					savechange();
				}
			}
		}
	}
}

void Core_WeChat_Lyc::quitgroups1()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				cout << endl;
			}
		}
		int select;
		string str;
		for (int i = 0; i < 5; i++)cout << endl;
		tttt(); cout << "|*==========退出/解散群==========*|" << endl;
		tttt(); cout << "请输入您要退出/解散的群的ID:\n";
		tttt(); cout << "子群仅可解散:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				f5(15);
				if (flag == 1) {
					int memflag = 0;
					int memsub;

					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					WeChat_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;


					tttt(); cout << "管理员：\n";
					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						if (ttarget->return_ID() == client->return_ID()) {
							memflag = 1;
							memsub = i;
						}
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					cout << endl;
					tttt(); cout << "普通成员：\n";
					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						if (ttarget->return_ID() == client->return_ID()) {
							memflag = 0;
							memsub = i;
						}
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
					cout << "\033[1;1H";
					for (int i = 0; i < 5; i++)cout << endl;

					int opt;
					if (target->return_masterID() == client->return_ID()) {//判断操作用户是否是群主
						memflag = 2;
						tttt(); cout << "您是当前群群主，若执行退群操作，则将视为解散群\n";
						tttt(); cout << "若想在保留该群的情况下退出，则请先移步管理群功能转让群主\n";
						tttt(); cout << "您要解散该群吗\n";
						tttt(); cout << "1.是 2.否\n";
						putt(opt);
					}
					else {
						tttt(); cout << "您要退出该群吗\n";
						tttt(); cout << "1.是 2.否\n";
						putt(opt);
					}

					switch (opt)
					{
					case 1: {
						if (memflag == 1) {
							target->admins.erase(target->admins.begin() + memsub);
							groupssave();
							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);
						}
						else if (memflag == 0) {
							target->members.erase(target->members.begin() + memsub);
							groupssave();
							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);
						}
						else if (memflag == 2) {
							//管理员退群
							for (int i = 0; i < target->admins.size(); i++) {
								WeChat_Lyc* tttarget = getself(target->admins[i]);
								for (int j = 0; j < tttarget->return_groups().size(); j++) {
									if (tttarget->groups[j]->return_groupID() == target->return_groupID()) {
										tttarget->groups.erase(tttarget->groups.begin() + i);
										break;
									}
								}
							}
							//普通成员退群
							for (int i = 0; i < target->members.size(); i++) {
								WeChat_Lyc* tttarget = getself(target->members[i]);
								for (int j = 0; j < tttarget->return_groups().size(); j++) {
									if (tttarget->groups[j]->return_groupID() == target->return_groupID()) {
										tttarget->groups.erase(tttarget->groups.begin() + i);
										break;
									}
								}
							}

							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);

							//删除总群文件内的该群信息
							ofstream file1;
							ifstream file2;
							string filename0 = "WeChat\\Groups\\groupslist.txt";
							vector<string>tempid, tempname;
							string tid, tname;
							file2.open(filename0, ios::in);
							while (file2 >> tid >> tname) {
								if (tid != target->return_groupID()) {
									tempid.push_back(tid);
									tempname.push_back(tname);
								}
							}
							file2.close();
							file1.open(filename0, ios::out);
							while (!tempid.empty()) {
								file1 << *tempid.begin() << endl << *tempname.begin()
									<< endl << endl;
								tempid.erase(tempid.begin());
								tempname.erase(tempname.begin());

							}

							string filename = "WeChat\\Groups\\" + target->return_groupID();
							string filename1 = filename + "\\" + target->return_groupID() + ".txt";
							string filename2 = filename + "\\" + target->return_groupID() + "admins.txt";
							string filename5 = filename + "\\" + target->return_groupID() + "tempmem.txt";
							DeleteFile(filename1.c_str());
							DeleteFile(filename2.c_str());
							DeleteFile(filename5.c_str());

							//删除子群信息
							string filename3 = filename + "\\" + target->return_groupID() + "songroups";
							for (int i = 0; i < target->tempGroups.size(); i++) {
								string tgid = target->tempGroups[i]->return_groupID();
								string filename4 = filename3 + "\\" + tgid + ".txt";
								DeleteFile(filename4.c_str());

							}
							string filename4 = filename3 + "\\list.txt";
							DeleteFile(filename4.c_str());

							RemoveDirectory(filename3.c_str());
							RemoveDirectory(filename.c_str());

							delete target;
						}
						break;
					}case 2: {
						break;
					}
					default: {
						tttt(); cout << "由于检测到不合法的输出，默认您要重新输入要退出/解散的群ID\n";
						any_continue(5);
						continue;
					}
					}
				}
				groupssave();
				savechange();
				cout << endl;
				tttt(); cout << "操作成功\n";
				tttt(); cout << "按回车键返回菜单\n";
				tttt(); getchar();
				return;
			}
		}
	}
}

void Core_WeChat_Lyc::groupchat()
{
	while (1) {
		f5(5);
		tttt(); cout << "请输入您要进行通讯的群的ID:\n";
		tttt(); cout << "(输入-1返回)\n";
		string gid; putt(gid);
		if (gid == "-1")return;
		int flag = 0;
		for (int i = 0; i < client->groups.size(); i++) {
			if (gid == client->groups[i]->groupID) {
				if (client->groupsflag[i] == 0) {
					flag = 1;
					break;
				}
			}
		}
		if (!flag) {
			tttt(); cout << "未找到该群\n";
			any_continue(5);
		}
		else {
			vchat(gid, WeChatsystem);
		}
	}
}

WeChat_Lyc* Core_WeChat_Lyc::getself(string id)
{
	for (int i = 0; i < WeChats.size(); i++) {
		if (WeChats[i]->return_ID() == id) {
			return WeChats[i];
		}
	}
	return nullptr;
}
//
//vector<WeiBo_Lyc*> Core_WeiBo_Lyc::return_WeiBos()
//{
//	return WeiBos;
//}

void Core_WeiBo_Lyc::mainmenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*==============微博===============*|" << endl;
		tttt(); cout << "|*             1.登录              *|" << endl;
		tttt(); cout << "|*             2.注册              *|" << endl;
		tttt(); cout << "|*             0.返回主菜单        *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:"; cin >> str;
		clear_inputBuffer(stdin);
		select = judge_input_menu(str, 2);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			login();
			break;
		case 2:
			enroll();
			break;
		case 0:return;
		}
		}
	}
}

void Core_WeiBo_Lyc::submenu()
{
	client->flag = 1;
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*===========欢迎使用微博=========*|" << endl;
		tttt(); cout << "|*            1.个人信息          *|" << endl;
		tttt(); cout << "|*            2.好友管理          *|" << endl;
		tttt(); cout << "|*            3.群管理            *|" << endl;
		tttt(); cout << "|*            4.开通管理          *|" << endl;
		tttt(); cout << "|*            5.登录管理          *|" << endl;
		tttt(); cout << "|*            0.返回主菜单        *|" << endl;
		tttt(); cout << "|*================================*|" << endl;
		tttt(); cout << "请输入您的选择:"; cin >> str;
		clear_inputBuffer(stdin);
		select = judge_input_menu(str, 5);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			informenu();
			break;
		}
		case 2:
		{
			friendmenu();
			break;
		}
		case 3:
		{
			groupmenu();
			break;
		}
		case 4:
		{
			openmenu();
			break;
		}
		case 5:
		{
			loginmenu();
			break;
		case 0:return;
		}
		}
	}
}

void Core_WeiBo_Lyc::login()
{
	system("CLS");
	string ID;
	bool flag = false;
	string Passwd;
	int target;
	f5(11);
	tttt(); cout << "请输入账号：\n";
	tttt(); cin >> ID;
	clear_inputBuffer(stdin);
	for (int i = 0; i < WeiBos.size(); i++) {
		if (WeiBos[i]->return_ID() == ID) {
			flag = true;
			target = i;
			break;
		}
	}
	if (!flag) {
		f5(11);
		tttt(); cout << "不存在该账号，将返回菜单\n";
		any_continue(5);
		return;
	}
	else if (WeiBos[target]->return_flag() == 0) {
		while (1) {
			system("CLS");
			f5(10);
			tttt(4); cout << "  账号：" << ID << endl << endl;
			tttt(); cout << "请输入密码：\n";
			tttt(); cin >> Passwd;
			clear_inputBuffer(stdin);
			if (Passwd != WeiBos[target]->return_Passwd()) {
				f5(11);
				tttt(); cout << "密码输入错误，请重新输入\n";
				any_continue(5);
			}
			else break;
		}
	}
	client = WeiBos[target];
	client->get_friends();
	client->get_groups();
	client->get_links();
	client->flag = 1;
	system("CLS");
	f5(11);
	tttt(); cout << "登录成功\n";
	any_continue(5);
	submenu();
}

void Core_WeiBo_Lyc::enroll(string id)
{
	system("CLS");
	WeiBos.push_back(new WeiBo_Lyc(id));
	savebase();
}

void Core_WeiBo_Lyc::savebase()
{
	ofstream file;
	string filename = "WeiBos.txt";
	file.open(filename, ios::app);
	if (WeiBos.empty())return;
	WeiBo_Lyc* target = WeiBos.back();
	file << target->return_ID() << endl << target->return_name() << endl << target->return_Passwd() << endl
		<< target->return_birthday() << endl << target->return_sex() << endl << target->return_area() << endl
		<< target->return_applyTime() << endl;
	file.close();
	target->get_friends();
	target->get_groups();
	string filename0 = "WeiBo\\" + target->return_ID() + "\\" + target->return_ID() + "links.txt";
	file.open(filename0, ios::app);
	file << "QQ 0\nWeChat 0";
}

void Core_WeiBo_Lyc::getinfor()
{
	string s;
	WeiBos.clear();
	WeiBos.shrink_to_fit();
	string id, name, pw, bir, sex, area, time;
	ifstream file;
	file.open("WeiBos.txt", ios::in);
	while (getline(file, id) && getline(file, name) && getline(file, pw) && getline(file, bir) && getline(file, sex) && getline(file, area) && getline(file, time))
	{
		string empty;
		getline(file, empty);
		WeiBos.push_back(new WeiBo_Lyc(id, name, pw, bir, sex, area, time));
		WeiBos.back()->flag = 0;
		WeiBos.back()->get_friends();
		WeiBos.back()->get_links();
	}
	for (int i = 0; i < WeiBos.size(); i++) {
		if (client != nullptr) {
			if (client->return_ID() == WeiBos[i]->return_ID()) {
				client = WeiBos[i];
			}
		}
	}
	file.close();


	WeiBogroups.clear();
	WeiBogroups.shrink_to_fit();
	string filename0 = "WeiBo\\Groups\\groupslist.txt";
	file.open(filename0, ios::in);
	while (file >> id >> name)
	{
		string empty;
		getline(file, empty);
		WeiBogroups.push_back(new QQ_Group_Lyc(id, name));

		string groupname = WeiBogroups.back()->return_groupID();
		string filename0 = "WeiBo\\Groups\\" + groupname + "\\" + groupname;
		string filename1 = filename0 + ".txt";
		string id;
		ifstream file1;
		file1.open(filename1, ios::in);
		while (file1 >> id) {
			WeiBogroups.back()->members.push_back(id);
		}
		file1.close();

		string filename2 = filename0 + "admins.txt";
		file1.open(filename2, ios::app);
		file1 >> id;
		WeiBogroups.back()->masterID = id;
		while (file1 >> id) {
			WeiBogroups.back()->admins.push_back(id);
		}
		file1.close();

		string filename5 = filename0 + "tempmem.txt";
		file1.open(filename5, ios::app);
		while (file1 >> id) {
			WeiBogroups.back()->tempmem.push_back(id);
		}
		file1.close();

		string filename3 = filename0 + "songroups\\";
		string filename4 = filename3 + "list.txt";
		string tgid, tgname;
		file1.open(filename4, ios::app);
		while (file1 >> tgid >> tgname) {
			WeiBogroups.back()->tempGroups.push_back(new Temp_Group_Lyc(tgid, tgname));
		}
		file1.close();
		for (int j = 0; j < WeiBogroups.back()->tempGroups.size(); j++) {
			string filename5 = filename3 + WeiBogroups.back()->tempGroups[j]->return_groupID() + ".txt";
			file1.open(filename5, ios::app);
			string tgmid;
			while (file1 >> tgmid) {
				WeiBogroups.back()->tempGroups[j]->member.push_back(tgmid);
			}
			file1.close();
			WeiBogroups.back()->tempGroups[j]->dad = WeiBogroups.back();
		}

	}
	for (int i = 0; i < WeiBos.size(); i++) {
		WeiBos[i]->get_groups();
	}
	file.close();
}

void Core_WeiBo_Lyc::informenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*============个人信息=============*|" << endl;
		tttt(); cout << "|*             1.查看个人信息      *|" << endl;
		tttt(); cout << "|*             2.修改昵称          *|" << endl;
		tttt(); cout << "|*             3.修改密码          *|" << endl;
		tttt(); cout << "|*             4.修改生日          *|" << endl;
		tttt(); cout << "|*             5.修改性别          *|" << endl;
		tttt(); cout << "|*             6.修改地区          *|" << endl;
		tttt(); cout << "|*             0.返回主菜单        *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 6);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			showinfor();
			break;
		}
		case 2:
		{
			changename();
			break;
		}case 3:
		{
			changepw();
			break;
		}
		case 4:
		{
			changebir();
			break;
		}case 5:
		{
			changesex();
			break;
		}
		case 6:
		{
			changearea();
			break;
		}
		case 0:return;
		}
	}
}

void Core_WeiBo_Lyc::friendmenu()
{
	while (1) {
		system("CLS");
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*============好友管理=============*|" << endl;
		tttt(); cout << "|*          1.所有好友展示         *|" << endl;//
		tttt(); cout << "|*          2.修改好友备注         *|" << endl;//
		tttt(); cout << "|*          3.查询好友             *|" << endl;//
		tttt(); cout << "|*          4.查询共同好友         *|" << endl;//
		tttt(); cout << "|*          5.添加好友             *|" << endl;//
		tttt(); cout << "|*          6.删除好友             *|" << endl;//
		tttt(); cout << "|*          7.查看好友申请         *|" << endl;//
		//tttt(); cout << "|*          8.好友通讯功能      *|" << endl;
		tttt(); cout << "|*          0.返回主菜单           *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 7);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			showfriends();
			break;
		}
		case 2:
		{
			changefriendsnote();
			break;
		}case 3:
		{
			findfriends();
			break;
		}
		case 4:
		{
			findmutualfriends();
			break;
		}case 5:
		{
			addfriends();
			break;
		}
		case 6:
		{
			deletefriends();
			break;
		}
		case 7:
		{
			friendrequest();
			break;
		}
		//case 8:
		//{
		//	//friendchat();
		//	break;
		//}
		case 0:return;
		}
	}
}

void Core_WeiBo_Lyc::groupmenu()
{
	while (1) {
		system("CLS");
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*========请选择群管理特色=========*|" << endl;
		tttt(); cout << "|*          1.QQ                   *|" << endl;
		tttt(); cout << "|*          2.微信                 *|" << endl;
		//		tttt(); cout << "|*          7.群通讯功能               *|" << endl;//
		tttt(); cout << "|*          0.返回主菜单           *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 5);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			Qgroupmenu();
			break;
		}
		case 2:
		{
			Wgroupmenu();
			break;
		}
		case 0:return;
		}
	}
}

void Core_WeiBo_Lyc::openmenu()
{
	ofstream file;
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*=============开通管理============*|" << endl;
		tttt(); cout << "|*             1.开通QQ            *|" << endl;
		tttt(); cout << "|*             2.绑定微信          *|" << endl;
		tttt(); cout << "|*             0.返回主菜单        *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:"; cin >> str;
		clear_inputBuffer(stdin);
		select = judge_input_menu(str, 2);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:

		{
			if (client->return_linkQQ() != "0") {
				f5(11);
				tttt(); cout << "QQ服务已开通" << endl;
				tttt(); cout << "QQID为：" << client->return_linkQQ() << endl;
				tttt(); cout << "如需开启自动登录，请移步登录管理" << endl;
				any_continue(5);
				break;
			}
			else {
				f5(12);
				tttt(); cout << "QQ即将开始注册\n";
				any_continue(5);
				QQsystem.enroll(client->return_ID());

				QQ_Lyc* tQQ = QQsystem.QQs.back();

				string filename0 = "WeiBo\\" + client->return_ID() + "\\" + client->return_ID() + "links.txt";
				file.open(filename0, ios::out);
				file << "QQ " << tQQ->return_ID() <<
					"\nWeChat " << client->return_linkWeChat();
				file.close();
				client->get_links();

				string filename1 = "QQ\\" + tQQ->return_ID() + "\\" +
					tQQ->return_ID() + "links.txt";
				file.open(filename1, ios::out);
				file << "WeChat " << client->return_linkWeChat() << "\nWeiBo " << client->return_ID();
				file.close();
				tQQ->get_links();


				if (client->linkWeChat != "0") {
					//微信绑定
					string filename2 = "WeChat\\" + client->linkWeChat + "\\" +
						client->linkWeChat + "links.txt";
					file.open(filename2, ios::out);
					file << "QQ " << client->return_ID() << "\nWeiBo " << client->return_ID();
					file.close();
					WeChat_Lyc* temp = WeChatsystem.getself(client->linkWeChat);
					temp->get_links();
				}

				f5(11);
				tttt(); cout << "QQ开通成功\n";
				tttt(); cout << "QQID为：" << client->return_linkQQ() << endl;
				tttt(); cout << "同时QQ将自动绑定与微博共享的微信（若存在）\n";
				tttt(); cout << "如需开启自动登录，请移步登录管理\n";
				any_continue(5);
			}
			break;
		}
		case 2:
		{
			if (client->return_linkWeChat() != "0") {
				f5(11);
				tttt(); cout << "已绑定微信" << endl;
				tttt(); cout << "微信ID为：" << client->return_linkWeChat() << endl;
				tttt(); cout << "如需开启自动登录，请移步登录管理" << endl;
				any_continue(5);
				break;
			}
			else {
				f5(11);
				tttt(); cout << "请输入您要绑定的微信号：\n";
				string twcid;
				tttt(); cin >> twcid;
				clear_inputBuffer(stdin);
				int num = WeChatsystem.WeChats.size();
				int flag = 0;
				for (int i = 0; i < num; i++) {
					WeChat_Lyc* tWC = WeChatsystem.WeChats[i];
					if (tWC->return_ID() == twcid) {
						flag = 1;
						string ps;
						tttt(); cout << "请输入微信密码：\n";
						tttt(); cin >> ps;
						clear_inputBuffer(stdin);
						if (ps == tWC->return_Passwd()) {
							//1.微信已绑定微博
							//2.微信已开通其他微x服务，QQ也开通对于微x服务，但是两者账号不同
							if (tWC->return_linkWeiBo() != "0") {
								tttt(); cout << "绑定失败\n";
								tttt(); cout << "该微信已被绑定\n";
								any_continue(5);
								break;
							}
							else {
								string filename0 = "WeiBo\\" + client->return_ID() + "\\" + client->return_ID() + "links.txt";
								file.open(filename0, ios::out);
								file << "WeChat " << tWC->return_ID() <<
									"\nQQ " << client->return_linkQQ();
								file.close();
								client->get_links();

								string filename1 = "WeChat\\" + tWC->return_ID() + "\\" +
									tWC->return_ID() + "links.txt";
								file.open(filename1, ios::out);
								file << "QQ " << client->return_linkQQ() << "\nWeiBo " << client->return_ID();
								file.close();
								tWC->get_links();

								if (client->linkQQ != "0") {
									//微博绑定
									string filename2 = "QQ\\" + client->return_ID() + "\\" +
										client->return_ID() + "links.txt";
									file.open(filename2, ios::out);
									file << "WeiBo " << client->return_ID() << "\nWeChat " << tWC->return_ID();
									file.close();
									QQ_Lyc* temp = QQsystem.getself(client->return_ID());
									temp->get_links();
								}


								tttt(); cout << "微信绑定成功\n";
								tttt(); cout << "微信ID为：" << client->return_linkWeChat() << endl;
								tttt(); cout << "同时微信将自动绑定与微博共享的QQ（若存在）\n";
								tttt(); cout << "如需开启自动登录，请移步登录管理\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "密码错误\n";
							any_continue(5);
							break;
						}
					}
				}
				if (!flag) {
					tttt(); cout << "未找到该微信\n";
					any_continue(5);
				}
			}
			break;
		}
		case 0:return;
		}
	}

}

void Core_WeiBo_Lyc::loginmenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*============登录管理=============*|" << endl;
		tttt(); cout << "|*             1.登录QQ            *|" << endl;
		tttt(); cout << "|*             2.登录微信          *|" << endl;
		tttt(); cout << "|*             0.返回主菜单        *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:"; cin >> str;
		clear_inputBuffer(stdin);
		select = judge_input_menu(str, 2);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			if (client->return_linkQQ() == "0") {
				f5(11);
				tttt(); cout << "您暂未开通QQ\n";
				tttt(); cout << "如需开通QQ，请移步开通管理\n";
				any_continue(5);
			}
			else {
				int num = QQsystem.QQs.size();
				for (int i = 0; i < num; i++) {
					QQ_Lyc* target = QQsystem.QQs[i];
					if (target->return_ID() == client->return_linkQQ())target->flag = 1;
				}
				f5(11);
				tttt(); cout << "自动登录成功\n";
				tttt(); cout << "现在您可以返回主界面登录QQ\n";
				any_continue(5);
			}
			break;
		}
		case 2:
		{
			if (client->return_linkWeChat() == "0") {
				f5(11);
				tttt(); cout << "您暂未开通微信\n";
				tttt(); cout << "如需开通微信，请移步开通管理\n";
				any_continue(5);
			}
			else {
				int num = WeChatsystem.WeChats.size();
				for (int i = 0; i < num; i++) {
					WeChat_Lyc* target = WeChatsystem.WeChats[i];
					if (target->return_ID() == client->return_linkWeChat())target->flag = 1;
				}
				f5(11);
				tttt(); cout << "自动登录成功\n";
				tttt(); cout << "现在您可以返回主界面登录微信\n";
				any_continue(5);
			}
		}
		break;
		case 0:return;
		}
	}
}

void Core_WeiBo_Lyc::savechange()
{
	ofstream file;
	string filename = "WeiBos.txt";
	file.open(filename, ios::trunc | ios::out);
	if (WeiBos.empty())return;
	int num = WeiBos.size();
	for (int i = 0; i < num; i++) {
		WeiBo_Lyc* target = WeiBos[i];


		file << target->return_ID() << endl << target->return_name() << endl << target->return_Passwd() << endl
			<< target->return_birthday() << endl << target->return_sex() << endl << target->return_area() << endl
			<< target->return_applyTime() << endl << endl;


		ofstream file1;
		string filename1 = "WeiBo\\" + target->return_ID() + "\\" + target->return_ID() + "friends.txt";
		file1.open(filename1, ios::trunc | ios::out);
		for (int j = 0; j < target->friends.size(); j++) {
			Friend_Lyc* temp = target->friends[j];
			file1 << temp->return_ID() << endl << temp->return_note() << endl << temp->return_flag() << endl << endl;
		}
		file1.close();

		ofstream file2;
		string filename2 = "WeiBo\\" + target->return_ID() + "\\" + target->return_ID() + "groups.txt";
		file2.open(filename2, ios::trunc | ios::out);
		for (int j = 0; j < target->groups.size(); j++) {
			QQ_Group_Lyc* temp = target->groups[j];
			file2 << temp->return_groupID() << endl << temp->return_name() << endl;
			file2 << target->groupsflag[j] << endl << endl;
		}
		file2.close();
	}
	file.close();
	getinfor();
}

void Core_WeiBo_Lyc::showinfor()
{
	while (1) {
		f5(8);
		getinfor();
		tttt(); cout << "个人信息" << endl;
		tttt(); cout << "ID：" << client->return_ID() << endl;
		tttt(); cout << "密码：" << client->return_Passwd() << endl;
		tttt(); cout << "昵称：" << client->return_name() << endl;
		tttt(); cout << "生日：" << client->return_birthday() << endl;
		tttt(); cout << "性别：" << client->return_sex() << endl;
		tttt(); cout << "地区：" << client->return_area() << endl;
		tttt(); cout << "注册时间：" << client->return_applyTime() << endl;
		tttt(); cout << "绑定微信ID：";
		if (client->return_linkWeChat() != "0") {
			cout << client->return_linkWeChat() << endl;
		}
		else {
			cout << "未绑定\n";
		}
		tttt(); cout << "绑定QQID：";
		if (client->return_linkQQ() != "0") {
			cout << client->return_linkQQ() << endl;
		}
		else {
			cout << "未绑定\n";
		}
		any_continue(5);
		break;
	}
}

void Core_WeiBo_Lyc::changename()
{
	int flag = 1;
	while (flag) {
		getinfor();
		f5(8);
		tttt(); cout << "|=============修改昵称============|" << endl;
		tttt(); cout << "当前昵称：" << client->return_name() << endl << endl;
		tttt(); cout << "请输入新昵称：\n";
		string name; putt(name);
		tttt(); cout << "您确定使用这个昵称吗：" << name << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt; putt(opt);
		switch (opt) {
		case(1): {
			flag = 0;
			client->change_name(name);
			tttt(); cout << "修改成功\n";
			savechange();
			any_continue(5);
			break;
		}
		case(2): break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
}

void Core_WeiBo_Lyc::changepw()
{
	int flag = 1;
	while (flag) {
		f5(8);
		getinfor();
		tttt(); cout << "|=============修改密码============|" << endl;
		tttt(); cout << "当前密码：" << client->return_Passwd() << endl << endl;
		tttt(); cout << "请输入新密码：\n";
		tttt(); string pw; cin >> pw;
		clear_inputBuffer(stdin);
		tttt(); cout << "请再次输入新密码：\n";
		tttt(); string tmppw; cin >> tmppw;
		clear_inputBuffer(stdin);
		if (pw == tmppw) {
			f5(13);
			tttt(); cout << "您确定使用这个密码吗：" << pw << "\n";
			tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
			int opt;
			tttt(); cin >> opt;
			clear_inputBuffer(stdin);
			switch (opt) {
			case(1): {
				flag = 0;
				client->change_passwd(pw);
				tttt(); cout << "修改成功\n";
				savechange();
				any_continue(5);
				break;
			}
			case(2):break;
			default: {
				f5(13);
				tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
				any_continue(5);
			}
			}
		}
		else {
			f5(13);
			tttt(); cout << "您输入的两次密码不相符，请重新输入!\n";
			any_continue(5);
		}
	}
}

void Core_WeiBo_Lyc::changebir()
{
	int a[2][12] = { 31,28,31,30,31,30,31,31,30,31,30,31,31,29,31,30,31,30,31,31,30,31,30,31 };
	int flag = 1;
	string temp;
	while (flag) {
		getinfor();
		f5(8);
		tttt(); cout << "|=============修改生日============|" << endl;
		tttt(); cout << "当前生日：" << client->return_birthday() << endl << endl;
		tttt(); cout << "请输入您的生日，格式为：20041213:\n";
		tttt(); cin >> temp;
		int len = temp.size();
		while (1) {
			int flag1 = 0;
			while (len != 8)
			{
				f5(8);
				tttt(); cout << "|=============修改生日============|" << endl;
				tttt(); cout << "请输入正确的日期形式：格式为：20041213:" << endl;
				tttt(); cin >> temp;
				clear_inputBuffer(stdin);
				len = temp.size();
			}
			int  year = 1000 * (temp[0] - '0') + 100 * (temp[1] - '0') + 10 * (temp[2] - '0') + temp[3] - '0';
			int  month = (temp[4] - '0') * 10 + temp[5] - '0';
			int day = (temp[6] - '0') * 10 + temp[7] - '0';
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			{
				if ((year > 9999 || year < 0) || (month > 12 || month < 1) || (day > a[1][month - 1] || day < 1))
				{
					f5(8);
					tttt(); cout << "|=============修改生日============|" << endl;
					tttt(); cout << "请输入正确的日期形式：格式为：20041213:" << endl;
					flag1 = 1;
					tttt(); cin >> temp;
					clear_inputBuffer(stdin);
				}
			}
			else
			{
				if ((year > 9999 || year < 0) || (month > 12 || month < 1) || (day > a[0][month - 1] || day < 1))
				{
					f5(8);
					tttt(); cout << "|=============修改生日============|" << endl;
					tttt(); cout << "请输入正确的日期形式：格式为：20041213:" << endl;
					flag1 = 1;
					tttt(); cin >> temp;
					clear_inputBuffer(stdin);
				}
			}
			if (!flag1)
			{
				break;
			}
		}
		f5(8);
		tttt(); cout << "|=============修改生日============|" << endl;
		tttt(); cout << "您确定使用这个生日吗：" << temp << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1): {
			flag = 0;
			client->change_bir(temp);
			tttt(); cout << "修改成功\n";
			savechange();
			any_continue(5);
			break;
		}
		case(2): break;
		default: {
			f5(8);
			tttt(); cout << "|=============修改生日============|" << endl;
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
}

void Core_WeiBo_Lyc::changesex()
{
	int flag = 1;
	while (flag) {
		getinfor();
		f5(8);
		tttt(); cout << "|=============修改性别============|" << endl;
		tttt(); cout << "当前性别：" << client->return_sex() << endl << endl;
		tttt(); cout << "请输入新性别：\n";
		tttt(); cout << "0,男性 1.女性\n";
		tttt(); int name; cin >> name;
		clear_inputBuffer(stdin);
		if (!(name == 0 || name == 1)) {

			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入" << endl;
			any_continue(5);
			continue;
		}
		string t;
		if (name == 0)t = "男";
		else t = "女";
		tttt(); cout << "您确定是这个性别吗：" << t << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1): {
			flag = 0;
			switch (name) {
			case 0:
				client->change_sex(0);
				break;
			case 1:
				client->change_sex(1);
				break;
			}
			tttt(); cout << "修改成功\n";
			savechange();
			any_continue(5);
			break;
		}
		case(2): break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
}

void Core_WeiBo_Lyc::changearea()
{
	int flag = 1;
	while (flag) {
		getinfor();
		f5(8);
		tttt(); cout << "|=============修改地区============|" << endl;
		tttt(); cout << "当前地区：" << client->return_area() << endl << endl;
		tttt(); cout << "请输入新地区：\n";
		tttt(); string name; cin >> name;
		clear_inputBuffer(stdin);
		tttt(); cout << "您确定使用这个地区吗：" << name << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1): {
			flag = 0;
			client->change_area(name);
			tttt(); cout << "修改成功\n";
			savechange();
			any_continue(5);
			break;
		}
		case(2): break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
}

void Core_WeiBo_Lyc::addfriends()
{
	while (1) {
		getinfor();
		//推荐好友部分
		system("CLS");
		f5(5);
		tttt(); cout << "推荐好友：\n\n\n";
		struct qlinkfriend {
			string wid;
			string wname;
			string qid;
			string qname;
		};
		vector<qlinkfriend>wc;
		vector<qlinkfriend>wb;
		WeChat_Lyc* linkwc{};
		QQ_Lyc* linkwb{};
		int wcflag, wbflag;
		if (client->return_linkWeChat() != "0") {//当前微博账户有绑定的微信账户
			linkwc = WeChatsystem.getself(client->return_linkWeChat());
			for (int i = 0; i < linkwc->friends.size(); i++) {//遍历绑定的微信账户的所有好友
				WeChat_Lyc* tmpwcfriend = WeChatsystem.getself(linkwc->friends[i]->return_ID());
				wcflag = 1;
				if (tmpwcfriend->return_linkWeiBo() != "0") {//微信好友是否有绑定的微博账户
					WeiBo_Lyc* tmpqqfriend = WeiBosystem.getself(tmpwcfriend->return_linkWeiBo());
					for (int j = 0; j < tmpqqfriend->friends.size(); j++) {//判断微信好友的微博账户好友有无自己
						if (tmpqqfriend->friends[j]->return_ID() == client->return_ID()) {
							wcflag = 0; break;
						}
					}
					if (wcflag) {
						wc.push_back({ tmpwcfriend->return_ID(),tmpwcfriend->return_name(),
							tmpqqfriend->return_ID(),tmpqqfriend->return_name() });
					}
				}
			}
		}
		if (client->return_linkQQ() != "0") {//当前微博账户有绑定的QQ账户
			linkwb = QQsystem.getself(client->return_linkQQ());
			for (int i = 0; i < linkwb->friends.size(); i++) {//遍历绑定的QQ账户的所有好友
				QQ_Lyc* tmpwbfriend = QQsystem.getself(linkwb->friends[i]->return_ID());
				wbflag = 1;
				if (tmpwbfriend->return_linkWeiBo() != "0") {//QQ好友是否有绑定的微博账户
					WeiBo_Lyc* tmpqqfriend = WeiBosystem.getself(tmpwbfriend->return_linkWeiBo());
					for (int j = 0; j < tmpqqfriend->friends.size(); j++) {//判断QQ好友的微博账户好友有无自己
						if (tmpqqfriend->friends[j]->return_ID() == client->return_ID()) {
							wbflag = 0; break;
						}
					}
					if (wbflag) {
						wb.push_back({ tmpwbfriend->return_ID(),tmpwbfriend->return_name(),
							tmpqqfriend->return_ID(),tmpqqfriend->return_name() });
					}
				}
			}
		}
		tttt(); cout << "来自微信的推荐好友：\n\n";
		if (wc.empty()) {
			tttt(); cout << "无\n\n";
		}
		else {
			for (int i = 0; i < wc.size(); i++) {
				tttt(); cout << "您的微信好友：" <<
					"ID:" << wc[i].wid << " 名字： " << wc[i].wname << endl;
				tttt(); cout << "其微博ID：" << wc[i].qid << " 名字： " << wc[i].qid << endl << endl;
			}
			wc.clear();
		}
		cout << endl;
		tttt(); cout << "来自QQ的推荐好友：\n\n";
		if (wb.empty()) {
			tttt(); cout << "无\n\n";
		}
		else {
			for (int i = 0; i < wb.size(); i++) {
				tttt(); cout << "您的QQ好友：" <<
					"ID:" << wb[i].wid << " 名字： " << wb[i].wname << endl;
				tttt(); cout << "其微博ID：" << wb[i].qid << " 名字： " << wb[i].qid << endl << endl;
			}
			wb.clear();
		}
		//添加部分

		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|===========添加好友==========|\n";
		tttt(); cout << "请输入您要添加的好友的ID：（输入-1返回菜单）\n";
		string id; putt(id);
		if (id == "-1") {
			return;
		}
		else if (id == client->return_ID()) {
			tttt(); cout << "您不能添加自己为好友\n";
			any_continue(5);
			continue;
		}
		else {
			int flag1 = 0;
			WeiBo_Lyc* target{};
			for (int i = 0; i < WeiBos.size(); i++) {
				if (WeiBos[i]->return_ID() == id) {
					flag1 = 1;
					target = WeiBos[i];
					break;
				}
			}
			if (!flag1) {
				tttt(); cout << "未找到该用户\n";
				any_continue(5);
				continue;
			}
			for (int i = 0; i < client->friends.size(); i++) {
				if (target->return_ID() == client->friends[i]->return_ID()) {
					if (client->friends[i]->return_flag() == 1) {
						tttt(); cout << "您已添加该好友\n";
						any_continue(5);
						return;
					}
					else if (client->friends[i]->return_flag() == 0) {
						//确认信息
						tttt(); cout << "发送好友成功，请等待对方确认\n";
						any_continue(5);
						return;
					}
					else if (client->friends[i]->return_flag() == -1) {
						tttt(); cout << "对方在此前已向您发出好友请求\n";
						tttt(); cout << "添加好友成功\n";
						any_continue(5);
						client->friends[i]->change_flag(1);
						savechange();
						return;
					}
				}
			}
			//具体操作
			target->friends.push_back(new Friend_Lyc(client->return_ID(), client->return_name(),
				client->return_birthday(), client->return_sex(), client->return_area(), -1));
			client->friends.push_back(new Friend_Lyc(target->return_ID(), target->return_name(),
				target->return_birthday(), target->return_sex(), target->return_area(), 0));

			savechange();
			tttt(); cout << "发送好友成功，请等待对方确认\n";
			any_continue(5);
			continue;
		}
	}
}

void Core_WeiBo_Lyc::friendrequest()
{
	while (1) {
		getinfor();
		//展示好友申请列表
		f5(5);
		vector<Friend_Lyc*>tmp;
		for (int i = 0; i < client->friends.size(); i++) {
			Friend_Lyc* target = client->friends[i];
			if (target->return_flag() == -1) {
				tmp.push_back(target);
			}
		}
		if (tmp.empty()) {
			tttt(); cout << "目前没有好友申请\n";
		}
		else {
			for (int i = 0; i < tmp.size(); i++) {
				tttt(); cout << "第" << i + 1 << "个\n";
				tttt(); cout << "ID：" << tmp[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << tmp[i]->return_name() << endl;
				tttt(); cout << "备注：" << tmp[i]->return_note() << endl;
				tttt(); cout << "生日：" << tmp[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << tmp[i]->return_sex() << endl;
				tttt(); cout << "地区：" << tmp[i]->return_area() << endl;
				cout << endl;
			}
		}
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|=========查看好友申请========|\n";
		tttt(); cout << "请输入您要处理的好友申请：\n";
		tttt(); cout << "（输入对应序号表示处理对应序号好友申请，输入-1返回菜单）\n";
		int sub; putt(sub);
		if (sub == -1) {
			return;
		}
		else if (sub >= 1 && sub <= tmp.size()) {
			cout << endl;
			tttt(); cout << "第" << sub << "个\n";
			tttt(); cout << "ID：" << tmp[sub - 1]->return_ID() << endl;
			tttt(); cout << "昵称：" << tmp[sub - 1]->return_name() << endl;
			tttt(); cout << "备注：" << tmp[sub - 1]->return_note() << endl;
			tttt(); cout << "生日：" << tmp[sub - 1]->return_birthday() << endl;
			tttt(); cout << "性别：" << tmp[sub - 1]->return_sex() << endl;
			tttt(); cout << "地区：" << tmp[sub - 1]->return_area() << endl;
			tttt(); cout << "您要同意该用户的好友申请吗？\n";
			tttt(); cout << "1.同意 2.拒绝\n";
			int opt; putt(opt);
			switch (opt) {
			case 1: {
				for (int i = 0; i < client->friends.size(); i++) {
					if (client->friends[i]->return_ID() == tmp[sub - 1]->return_ID())
					{
						client->friends[i]->change_flag(1);
						break;
					}
				}
				WeiBo_Lyc* target = getself(tmp[sub - 1]->return_ID());
				for (int i = 0; i < target->friends.size(); i++) {
					if (target->friends[i]->return_ID() == client->return_ID())
					{
						target->friends[i]->change_flag(1);
						break;
					}
				}
				savechange();
				tttt(); cout << "操作成功\n";
				any_continue(5);
				break;
			}
			case 2: {
				for (int i = 0; i < client->friends.size(); i++) {
					if (client->friends[i]->return_ID() == tmp[sub - 1]->return_ID())
					{
						client->friends.erase(client->friends.begin() + i);
						break;
					}
				}
				WeiBo_Lyc* target = getself(tmp[sub - 1]->return_ID());
				for (int i = 0; i < target->friends.size(); i++) {
					if (target->friends[i]->return_ID() == client->return_ID())
					{
						target->friends.erase(target->friends.begin() + i);
						break;
					}
				}
				//cout << client->friends.size();
				//while (1);
				savechange();
				tttt(); cout << "操作成功\n";
				any_continue(5);
				break;
			}
			default: {
				tttt(); cout << "由于检测到不合法输出\n";
				tttt(); cout << "默认您要重新输入要处理的好友请求\n";
				any_continue(5);
				continue;
			}
			}
		}
		else {
			tttt(); cout << "您的输入范围有误\n";
			any_continue(5);
		}
	}
}

void Core_WeiBo_Lyc::deletefriends()
{

	while (1) {
		getinfor();
		f5(5);
		vector<Friend_Lyc*>tmp;
		for (int i = 0; i < client->friends.size(); i++) {
			Friend_Lyc* target = client->friends[i];
			if (target->return_flag() == 1) {
				tmp.push_back(target);
			}
		}
		if (tmp.empty()) {
			tttt(); cout << "目前没有好友\n";
		}
		else {
			for (int i = 0; i < tmp.size(); i++) {
				tttt(); cout << "ID：" << tmp[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << tmp[i]->return_name() << endl;
				tttt(); cout << "备注：" << tmp[i]->return_note() << endl;
				tttt(); cout << "生日：" << tmp[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << tmp[i]->return_sex() << endl;
				tttt(); cout << "地区：" << tmp[i]->return_area() << endl;
				cout << endl;
			}
		}

		//输入框
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|===========删除好友==========|\n";
		tttt(); cout << "请输入您要删除的好友ID：\n";
		tttt(); cout << "（输入-1返回菜单）\n";
		string id; putt(id);
		if (id == "-1") {
			return;
		}
		else {
			Friend_Lyc* target = nullptr;
			int sub;
			for (int i = 0; i < client->friends.size(); i++) {
				if (client->friends[i]->return_ID() == id) {
					target = client->friends[i];
					sub = i;
					break;
				}
			}
			if (target == nullptr) {
				tttt(); cout << "您暂未添加该用户为好友\n";
				any_continue(5);
				continue;
			}
			else {
				cout << endl;
				tttt(); cout << "ID：" << target->return_ID() << endl;
				tttt(); cout << "昵称：" << target->return_name() << endl;
				tttt(); cout << "备注：" << target->return_note() << endl;
				tttt(); cout << "生日：" << target->return_birthday() << endl;
				tttt(); cout << "性别：" << target->return_sex() << endl;
				tttt(); cout << "地区：" << target->return_area() << endl;
				tttt(); cout << "您要删除该好友吗？\n";
				tttt(); cout << "1.确认 2.取消\n";
				int opt; putt(opt);
				switch (opt)
				{
				case 1: {
					WeiBo_Lyc* ttarget = getself(target->return_ID());
					client->friends.erase(client->friends.begin() + sub);
					for (int i = 0; i < ttarget->friends.size(); i++) {
						if (ttarget->friends[i]->return_ID() == client->return_ID()) {
							ttarget->friends.erase(ttarget->friends.begin() + sub);
							break;
						}
					}
					savechange();
					break;
				}
				case 2: {
					tttt(); cout << "操作成功\n";
					any_continue(5);
					break;
				}
				default: {
					tttt(); cout << "由于检测到不合法输出\n";
					tttt(); cout << "默认您要重新输入要删除的好友\n";
					any_continue(5);
					break;
				}
				}
			}
		}
	}
}

void Core_WeiBo_Lyc::showfriends()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->friends.empty()) {
			tttt(); cout << "目前没有好友\n";
		}
		else {
			for (int i = 0; i < client->friends.size(); i++) {
				tttt(); cout << "第" << i + 1 << "位" << endl;
				tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
				tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
				tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
				tttt(); cout << "地区：" << client->friends[i]->return_area() << endl;
				cout << endl;
			}
		}

		//输入框
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|=========所有好友展示========|\n";
		tttt(); cout << "按回车键返回菜单\n";
		tttt(); string s;
		if (cin.peek()) {
			clear_inputBuffer(stdin);
			return;
		}
	}
}

void Core_WeiBo_Lyc::changefriendsnote()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->friends.empty()) {
			tttt(); cout << "目前没有好友\n";
		}
		else {
			for (int i = 0; i < client->friends.size(); i++) {
				tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
				tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
				tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
				tttt(); cout << "地区：" << client->friends[i]->return_area() << endl;
				cout << endl;
			}
		}

		//输入框
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|=========修改好友备注========|\n";
		tttt(); cout << "请输入您要修改备注的好友ID：\n";
		tttt(); cout << "（输入-1返回菜单）\n";
		string id; putt(id);
		if (id == "-1") {
			return;
		}
		else {
			Friend_Lyc* target = nullptr;
			int sub;
			for (int i = 0; i < client->friends.size(); i++) {
				if (client->friends[i]->return_ID() == id) {
					target = client->friends[i];
					sub = i;
					break;
				}
			}
			if (target == nullptr) {
				tttt(); cout << "您暂未添加该用户为好友\n";
				any_continue(5);
				continue;
			}
			else {
				tttt(); cout << "请输入新备注：\n";
				string note; putt(note);
				target->note = note;
				savechange();
				tttt(); cout << "操作成功\n";
				any_continue(5);
				continue;
			}
		}
	}

}

void Core_WeiBo_Lyc::findfriends()
{
	while (1) {
		getinfor();
		//输入框
		system("CLS");
		f5(3);
		int opt;
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|==============查找好友============|\n";
		tttt(); cout << "|*            1.ID                *|" << endl;
		tttt(); cout << "|*            2.昵称              *|" << endl;
		tttt(); cout << "|*            3.备注              *|" << endl;
		tttt(); cout << "|*            4.生日              *|" << endl;
		tttt(); cout << "|*            5.性别              *|" << endl;
		tttt(); cout << "|*            6.地区              *|" << endl;
		tttt(); cout << "|*            0.返回菜单          *|" << endl;
		tttt(); cout << "|*================================*|" << endl;
		tttt(); cout << "请选择您要查找的方式：\n";
		putt(opt);
		switch (opt) {
		case 1: {
			string id;
			tttt(); cout << "请输入要查找的ID：\n";
			putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_ID()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
					break;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
		}
		case 2: {
			string id;
			tttt(); cout << "请输入要查找的昵称：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_name()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
		}
		case 3: {
			string id;
			tttt(); cout << "请输入要查找的备注：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_note()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
		}
		case 4: {
			string id;
			tttt(); cout << "请输入要查找的生日：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_birthday()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
		}
		case 5: {
			string id;
			tttt(); cout << "请输入要查找的性别：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_sex()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
			break;
		}
		case 6: {
			string id;
			tttt(); cout << "请输入要查找的地区：\n"; putt(id);
			int flag = 0;
			for (int i = 0; i < client->friends.size(); i++) {
				if (id == client->friends[i]->return_area()) {
					flag++;
					if (flag == 1) {
						cout << endl; tttt(); cout << "查询成功\n\n";
					}
					tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
					tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
					tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
					tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
					tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
					tttt(); cout << "地区：" << client->friends[i]->return_area() << endl << endl;
				}
			}
			if (!flag) {
				cout << endl; tttt(); cout << "未查询到相关用户\n";
			}
			any_continue(5);
			break;
			break;
		}
		case 0: {
			return;
		}
		}
	}
}

void Core_WeiBo_Lyc::findmutualfriends()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->friends.empty()) {
			tttt(); cout << "目前没有好友\n";
		}
		else {
			for (int i = 0; i < client->friends.size(); i++) {
				tttt(); cout << "ID：" << client->friends[i]->return_ID() << endl;
				tttt(); cout << "昵称：" << client->friends[i]->return_name() << endl;
				tttt(); cout << "备注：" << client->friends[i]->return_note() << endl;
				tttt(); cout << "生日：" << client->friends[i]->return_birthday() << endl;
				tttt(); cout << "性别：" << client->friends[i]->return_sex() << endl;
				tttt(); cout << "地区：" << client->friends[i]->return_area() << endl;
				cout << endl;
			}
		}

		//输入框
		for (int i = 0; i < 2; i++)tttt(); cout << endl;
		tttt(); cout << "|=========查找共同好友========|\n";
		tttt(); cout << "请输入要查找的好友ID：\n";
		tttt(); cout << "（输入-1返回菜单）\n";
		string id;
		putt(id);
		if (id == "-1") {
			return;
		}
		WeiBo_Lyc* target = nullptr;
		for (int i = 0; i < client->friends.size(); i++) {
			if (id == client->friends[i]->return_ID()) {
				target = getself(id);
				break;
			}
		}
		if (target == nullptr) {
			tttt(); cout << "未查找到相关用户\n";
		}
		else {
			f5(5);
			cout << endl; tttt();
			if (target->return_linkWeChat() == "0") {
				cout << "该用户暂未绑定微信\n";
			}
			else {
				cout << "该用户的绑定微信ID信息如下：" << endl;
				WeChat_Lyc* ttarget = WeChatsystem.getself(target->return_linkWeChat());
				tttt(); cout << "ID：" << ttarget->return_ID() << endl;
				tttt(); cout << "昵称：" << ttarget->return_name() << endl;
				tttt(); cout << "生日：" << ttarget->return_birthday() << endl;
				tttt(); cout << "性别：" << ttarget->return_sex() << endl;
				tttt(); cout << "地区：" << ttarget->return_area() << endl;

			}

			cout << endl; tttt();
			if (target->return_linkQQ() == "0") {
				cout << "该用户暂未绑定QQ\n";
			}
			else {
				cout << "该用户的绑定QQID信息如下：" << endl;
				QQ_Lyc* ttarget = QQsystem.getself(target->return_linkQQ());
				tttt(); cout << "ID：" << ttarget->return_ID() << endl;
				tttt(); cout << "昵称：" << ttarget->return_name() << endl;
				tttt(); cout << "生日：" << ttarget->return_birthday() << endl;
				tttt(); cout << "性别：" << ttarget->return_sex() << endl;
				tttt(); cout << "地区：" << ttarget->return_area() << endl;
			}
		}
		cout << endl; any_continue(5);
	}
}

void Core_WeiBo_Lyc::Qgroupmenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*=============群管理==============*|" << endl;
		tttt(); cout << "|*          1.创建群               *|" << endl;//
		tttt(); cout << "|*          2.加入群               *|" << endl;//
		tttt(); cout << "|*          3.管理群               *|" << endl;
		tttt(); cout << "|*          4.查看群信息           *|" << endl;//
		tttt(); cout << "|*          5.退出/解散群          *|" << endl;//
		tttt(); cout << "|*          6.群通讯功能           *|" << endl;//
		tttt(); cout << "|*          0.返回主菜单           *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 6);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			creategroups();
			break;
		}
		case 2:
		{
			joingroups();
			break;
		}
		case 3:
		{
			rungroups();
			break;
		}
		case 4:
		{
			viewgroups();
			break;
		}
		case 5: {
			quitgroups();
			break;
		}
		case 6:
		{
			groupchat();
			break;
		}
		case 0:return;
		}
	}
}

void Core_WeiBo_Lyc::Wgroupmenu()
{
	while (1) {
		int select;
		string str;
		f5(8);
		tttt(); cout << "|*=============群管理==============*|" << endl;
		tttt(); cout << "|*          1.创建群               *|" << endl;
		tttt(); cout << "|*          2.退出群               *|" << endl;
		tttt(); cout << "|*          3.管理群               *|" << endl;
		tttt(); cout << "|*          4.查看群信息           *|" << endl;
		tttt(); cout << "|*          5.推荐好友入群         *|" << endl;
		tttt(); cout << "|*          6.应答接受入群         *|" << endl;
		tttt(); cout << "|*          7.群通讯功能               *|" << endl;//
		tttt(); cout << "|*          0.返回主菜单           *|" << endl;
		tttt(); cout << "|*=================================*|" << endl;
		tttt(); cout << "请输入您的选择:\n";
		putt(str);
		select = judge_input_menu(str, 7);
		switch (select)//不同的功能对应不同的菜单体现多态思想
		{
		case 1:
		{
			creategroups();
			break;
		}
		case 2:
		{
			quitgroups1();
			break;
		}
		case 3:
		{
			rungroups1();
			break;
		}
		case 4:
		{
			viewgroups();
			break;
		}
		case 5: {
			invitefriends();
			break;
		}
		case 6: {
			solveinvitation();
			break;
		}
		case 7:
		{
			groupchat();
			break;
		}
		case 0:return;
		}
	}
}

void Core_WeiBo_Lyc::viewgroups()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				if (client->groups[i]->tempGroups.empty()) {
					tttt(); cout << "无子群:\n";
				}
				else {
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						tttt(); cout << "群ID：" << client->groups[i]->tempGroups[j]->return_groupID() << endl;
						tttt(); cout << "群昵称：" << client->groups[i]->tempGroups[j]->return_name() << endl << endl;
					}
				}
				cout << endl;
			}
		}
		int select;
		string str;
		//cout << "\033[1;1H";
		for (int i = 0; i < 5; i++)cout << endl;
		tttt(); cout << "|*===========查看群信息============*|" << endl;
		tttt(); cout << "请输入您要查看的群的ID:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						if (client->groups[i]->tempGroups[j]->return_groupID() == str) {
							for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
								if (client->groups[i]->tempGroups[j]->member[k] == client->return_ID()) {
									flag = 2;
									sub = i;
									tsub = j;
									target = client->groups[i];
									ttarget = client->groups[i]->tempGroups[j];
									break;
								}
							}
						}
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				if (flag == 1) {
					f5(7);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					WeiBo_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;


					tttt(); cout << "管理员：\n";
					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					cout << endl;
					tttt(); cout << "普通成员：\n";
					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
				}
				else if (flag == 2) {
					f5(7);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << ttarget->return_groupID() << endl;
					tttt(); cout << "群昵称：" << ttarget->return_name() << endl;
					tttt(); cout << "父群ID：" << ttarget->dad->return_groupID() << endl;
					tttt(); cout << "父群昵称：" << ttarget->dad->return_name() << endl;

					cout << endl;

					tttt(); cout << "成员：\n";
					for (int i = 0; i < ttarget->member.size(); i++) {
						WeiBo_Lyc* tgmname = getself(ttarget->member[i]);
						tttt(); cout << "ID：" << tgmname->return_ID() <<
							" 昵称：" << tgmname->return_name() << endl << endl;
					}
				}

				cout << "\033[1;1H";
				for (int i = 0; i < 5; i++)cout << endl;
				tttt(); cout << "按回车键返回菜单\n";
				tttt(); getchar();
				return;
			}
		}
	}
}

void Core_WeiBo_Lyc::groupssave()
{
	for (int i = 0; i < client->groups.size(); i++) {
		ofstream file0;
		string filename0 = "WeiBo\\Groups\\" + client->groups[i]->return_groupID() + "\\" + client->groups[i]->return_groupID() + ".txt";
		file0.open(filename0, ios::out | ios::trunc);
		for (int j = 0; j < client->groups[i]->members.size(); j++) {
			file0 << client->groups[i]->members[j] << endl;
		}
		file0.close();

		string filename1 = "WeiBo\\Groups\\" + client->groups[i]->return_groupID() + "\\" + client->groups[i]->return_groupID() + "admins.txt";
		file0.open(filename1, ios::out | ios::trunc);
		file0 << client->groups[i]->return_masterID() << endl;
		for (int j = 0; j < client->groups[i]->admins.size(); j++) {
			file0 << client->groups[i]->admins[j] << endl;
		}
		file0.close();

		string filename2 = "WeiBo\\Groups\\" + client->groups[i]->return_groupID() + "\\" + client->groups[i]->return_groupID() + "tempmem.txt";
		file0.open(filename2, ios::out | ios::trunc);
		for (int j = 0; j < client->groups[i]->tempmem.size(); j++) {
			file0 << client->groups[i]->tempmem[j] << endl;
		}
		file0.close();

		for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
			string filename2 = "WeiBo\\Groups\\" + client->groups[i]->return_groupID() + "\\" + client->groups[i]->return_groupID() + "songroups\\" +
				client->groups[i]->tempGroups[j]->return_groupID() + ".txt";
			file0.open(filename2, ios::out | ios::trunc);
			for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
				file0 << client->groups[i]->tempGroups[j]->member[k] << endl;
			}
		}
	}
}

void Core_WeiBo_Lyc::creategroups()
{
	while (1) {
		getinfor();
		f5(10);
		tttt(); cout << "|============创建群===========|\n";
		tttt(); cout << "请输入您要创建的群的昵称：\n";
		tttt(); cout << "按回车键取消创建\n";
		string name;
		tttt();
		if (cin.peek() == '\n') {
			tttt(); cout << "取消创建成功\n";
			clear_inputBuffer(stdin);
		}
		else {
			cin >> name;
			clear_inputBuffer(stdin);

			tttt(); cout << "您确定要使用这个昵称吗:" << name << endl;
			tttt(); cout << "1.确认2.取消\n";
			int opt; putt(opt);
			switch (opt) {
			case 1: {

				int tempid = generate_ID();
				stringstream tempss;
				tempss << tempid;
				string id;
				tempss >> id;
				ofstream file;

				//向WeiBo\\Groups\\groupslist.txt添加群信息
				string filename0 = "WeiBo\\Groups\\groupslist.txt";
				file.open(filename0, ios::app);
				file << id << endl << name << endl << endl;
				file.close();

				string filename1 = "WeiBo\\Groups\\" + id;
				CreateDirectory(filename1.c_str(), NULL);//创建文件夹
				string filename44 = filename1 + "\\" + id + "songroups";
				CreateDirectory(filename44.c_str(), NULL);//创建文件夹
				string filename45 = filename44 + "\\list.txt";
				file.open(filename45, ios::app);
				file.close();

				string filename2 = filename1 + "\\" + id + ".txt";
				file.open(filename2, ios::app);
				file.close();

				string filename3 = filename1 + "\\" + id + "admins.txt";
				file.open(filename3, ios::app);
				file << client->return_ID() << endl;
				file.close();


				string filename4 = filename1 + "\\" + id + "tempmem.txt";
				file.open(filename4, ios::app);
				file.close();

				WeiBogroups.push_back(new QQ_Group_Lyc(id, name));
				client->groups.push_back(WeiBogroups.back());
				client->groupsflag.push_back(0);
				client->groups.back()->masterID = client->return_ID();
				//client->groups.back()->admins.push_back(client->return_ID());
				tttt(); cout << "群创建成功" << endl;
				tttt(); cout << "群ID为:" << id << endl;
				tttt(); cout << "群昵称为:" << name << endl;
				savechange();
				groupssave();
				break;
			}
			case 2: {
				continue;
			}
			default: {
				tttt(); cout << "由于检测到无效的输出\n";
				tttt(); cout << "默认您要重新输入昵称\n";
				//continue;
			}
			}
		}
		tttt(); cout << "按回车键返回菜单\n";
		tttt(); getchar();
		return;
	}
}

void Core_WeiBo_Lyc::quitgroups()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				if (client->groups[i]->tempGroups.empty()) {
					tttt(); cout << "无子群:\n";
				}
				else {
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						tttt(); cout << "群ID：" << client->groups[i]->tempGroups[j]->return_groupID() << endl;
						tttt(); cout << "群昵称：" << client->groups[i]->tempGroups[j]->return_name() << endl << endl;
					}
				}
				cout << endl;
			}
		}
		int select;
		string str;
		for (int i = 0; i < 5; i++)cout << endl;
		tttt(); cout << "|*==========退出/解散群==========*|" << endl;
		tttt(); cout << "请输入您要退出/解散的群的ID:\n";
		tttt(); cout << "子群仅可解散:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						if (client->groups[i]->tempGroups[j]->return_groupID() == str) {
							for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
								if (client->groups[i]->tempGroups[j]->member[k] == client->return_ID()) {
									flag = 2;
									sub = i;
									tsub = j;
									target = client->groups[i];
									ttarget = client->groups[i]->tempGroups[j];
									break;
								}
							}
						}
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				f5(15);
				if (flag == 1) {
					int memflag = 0;
					int memsub;

					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					WeiBo_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;


					tttt(); cout << "管理员：\n";
					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						if (ttarget->return_ID() == client->return_ID()) {
							memflag = 1;
							memsub = i;
						}
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					cout << endl;
					tttt(); cout << "普通成员：\n";
					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						if (ttarget->return_ID() == client->return_ID()) {
							memflag = 0;
							memsub = i;
						}
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
					cout << "\033[1;1H";
					for (int i = 0; i < 5; i++)cout << endl;

					int opt;
					if (target->return_masterID() == client->return_ID()) {//判断操作用户是否是群主
						memflag = 2;
						tttt(); cout << "您是当前群群主，若执行退群操作，则将视为解散群\n";
						tttt(); cout << "若想在保留该群的情况下退出，则请先移步管理群功能转让群主\n";
						tttt(); cout << "您要解散该群吗\n";
						tttt(); cout << "1.是 2.否\n";
						putt(opt);
					}
					else {
						tttt(); cout << "您要退出该群吗\n";
						tttt(); cout << "1.是 2.否\n";
						putt(opt);
					}

					switch (opt)
					{
					case 1: {
						if (memflag == 1) {
							target->admins.erase(target->admins.begin() + memsub);
							groupssave();
							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);
						}
						else if (memflag == 0) {
							target->members.erase(target->members.begin() + memsub);
							groupssave();
							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);
						}
						else if (memflag == 2) {
							//管理员退群
							for (int i = 0; i < target->admins.size(); i++) {
								WeiBo_Lyc* tttarget = getself(target->admins[i]);
								for (int j = 0; j < tttarget->return_groups().size(); j++) {
									if (tttarget->groups[j]->return_groupID() == target->return_groupID()) {
										tttarget->groups.erase(tttarget->groups.begin() + i);
										break;
									}
								}
							}
							//普通成员退群
							for (int i = 0; i < target->members.size(); i++) {
								WeiBo_Lyc* tttarget = getself(target->members[i]);
								for (int j = 0; j < tttarget->return_groups().size(); j++) {
									if (tttarget->groups[j]->return_groupID() == target->return_groupID()) {
										tttarget->groups.erase(tttarget->groups.begin() + i);
										break;
									}
								}
							}

							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);

							//删除总群文件内的该群信息
							ofstream file1;
							ifstream file2;
							string filename0 = "WeiBo\\Groups\\groupslist.txt";
							vector<string>tempid, tempname;
							string tid, tname;
							file2.open(filename0, ios::in);
							while (file2 >> tid >> tname) {
								if (tid != target->return_groupID()) {
									tempid.push_back(tid);
									tempname.push_back(tname);
								}
							}
							file2.close();
							file1.open(filename0, ios::out);
							while (!tempid.empty()) {
								file1 << *tempid.begin() << endl << *tempname.begin()
									<< endl << endl;
								tempid.erase(tempid.begin());
								tempname.erase(tempname.begin());

							}

							string filename = "WeiBo\\Groups\\" + target->return_groupID();
							string filename1 = filename + "\\" + target->return_groupID() + ".txt";
							string filename2 = filename + "\\" + target->return_groupID() + "admins.txt";
							string filename5 = filename + "\\" + target->return_groupID() + "tempmem.txt";
							DeleteFile(filename1.c_str());
							DeleteFile(filename2.c_str());
							DeleteFile(filename5.c_str());

							//删除子群信息
							string filename3 = filename + "\\" + target->return_groupID() + "songroups";
							for (int i = 0; i < target->tempGroups.size(); i++) {
								string tgid = target->tempGroups[i]->return_groupID();
								string filename4 = filename3 + "\\" + tgid + ".txt";
								DeleteFile(filename4.c_str());

							}
							string filename4 = filename3 + "\\list.txt";
							DeleteFile(filename4.c_str());

							RemoveDirectory(filename3.c_str());
							RemoveDirectory(filename.c_str());

							delete target;
						}
						break;
					}case 2: {
						break;
					}
					default: {
						tttt(); cout << "由于检测到不合法的输出，默认您要重新输入要退出/解散的群ID\n";
						any_continue(5);
						continue;
					}
					}
				}
				else if (flag == 2) {

					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << ttarget->return_groupID() << endl;
					tttt(); cout << "群昵称：" << ttarget->return_name() << endl;
					tttt(); cout << "父群ID：" << target->return_groupID() << endl;
					tttt(); cout << "父群昵称：" << target->return_name() << endl;

					cout << endl;

					tttt(); cout << "成员：\n";
					for (int i = 0; i < ttarget->member.size(); i++) {
						WeiBo_Lyc* tgmname = getself(ttarget->member[i]);
						tttt(); cout << "ID：" << tgmname->return_ID() <<
							" 昵称：" << tgmname->return_name() << endl << endl;
					}

					cout << "\033[1;1H";
					for (int i = 0; i < 5; i++)cout << endl;
					tttt(); cout << "您要退出/解散该子群吗\n";
					tttt(); cout << "1.退出 2.解散 3.取消\n";
					int opt1; putt(opt1);
					switch (opt1) {
					case 1: {
						for (int i = 0; i < client->groups[sub]->tempGroups[tsub]->member.size(); i++) {
							if (client->groups[sub]->tempGroups[tsub]->member[i] == client->return_ID()) {
								client->groups[sub]->tempGroups[tsub]->member.erase(client->groups[sub]->tempGroups[tsub]->member.begin() + i);
								groupssave();
							}
						}
						/*client->groups[sub]->tempGroups.erase(client->groups[sub]->tempGroups.begin() + tsub);*/
						break;
					}
					case 2: {
						string filename0 = "WeiBo\\Groups\\" + client->groups[sub]->groupID + "\\" + client->groups[sub]->groupID + "songroups";
						string filename1 = filename0 + "\\list.txt";
						vector<string> tgvid, tgvname;
						string tgid, tgname;
						ifstream file;
						ofstream file1;
						file.open(filename1, ios::app);
						while (file >> tgid >> tgname) {
							if (tgid != client->groups[sub]->tempGroups[tsub]->return_groupID()) {
								tgvid.push_back(tgid);
								tgvname.push_back(tgname);
							}
						}
						file.close();
						file1.open(filename1, ios::trunc | ios::out);
						while (!tgvid.empty()) {
							file1 << *tgvid.begin() << endl << *tgvname.begin() << endl << endl;
						}
						string filename2 = filename0 + "\\" + ttarget->return_groupID() + ".txt";
						DeleteFile(filename2.c_str());

						client->groups[sub]->tempGroups.erase(client->groups[sub]->tempGroups.begin() + tsub);

						break;
					}
					case 3: {
						break;
					}default: {
						tttt(); cout << "由于不合法的输入，默认您要重新输入要退出/解散的群ID\n";
						any_continue(5);
						continue;
					}
					}

				}
				groupssave();
				savechange();
				cout << endl;
				tttt(); cout << "操作成功\n";
				tttt(); cout << "按回车键返回菜单\n";
				tttt(); getchar();
				return;
			}
		}
	}
}

void Core_WeiBo_Lyc::rungroups()
{
	while (1) {
		getinfor();
		string QWflag = "Q";
		string conflag;
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				if (client->groups[i]->tempGroups.empty()) {
					tttt(); cout << "无子群:\n";
				}
				else {
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						tttt(); cout << "群ID：" << client->groups[i]->tempGroups[j]->return_groupID() << endl;
						tttt(); cout << "群昵称：" << client->groups[i]->tempGroups[j]->return_name() << endl << endl;
					}
				}
				cout << endl;
			}
		}
		int select;
		string str;
		for (int i = 0; i < 5; i++)cout << endl;
		//1.解散/退出群
		//2.T人 
		//3/转让群主 群主专用
		//4.加入群请求处理 WeiBo专用
		//5.设置临时讨论组 WeiBo专用
		//6.设置/取消管理员 群主专用 WeiBo专用
		tttt(); cout << "|*=============管理群==============*|" << endl;
		tttt(); cout << "|*          1.T人                  *|" << endl;
		tttt(); cout << "|*          2.转让群主             *|" << endl;
		tttt(); cout << "|*          3.加入群请求处理       *|" << endl;
		tttt(); cout << "|*          4.设置子群             *|" << endl;
		tttt(); cout << "|*          5.设置/取消管理员      *|" << endl;
		tttt(); cout << "请输入您要管理的群的ID:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						if (client->groups[i]->tempGroups[j]->return_groupID() == str) {
							for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
								if (client->groups[i]->tempGroups[j]->member[k] == client->return_ID()) {
									flag = 2;
									sub = i;
									tsub = j;
									target = client->groups[i];
									ttarget = client->groups[i]->tempGroups[j];
									break;
								}
							}
						}
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				int memflag;
				if (flag == 1) {
					f5(5);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					WeiBo_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;
					if (ttarget->return_ID() == client->return_ID())memflag = 2;


					tttt(); cout << "管理员：\n";
					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						if (ttarget->return_ID() == client->return_ID())memflag = 1;
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					cout << endl;
					tttt(); cout << "普通成员：\n";
					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						if (ttarget->return_ID() == client->return_ID())memflag = 0;
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
				}
				else if (flag == 2) {
					f5(5);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << ttarget->return_groupID() << endl;
					tttt(); cout << "群昵称：" << ttarget->return_name() << endl;
					tttt(); cout << "父群ID：" << ttarget->dad->return_groupID() << endl;
					tttt(); cout << "父群昵称：" << ttarget->dad->return_name() << endl;

					cout << endl;

					tttt(); cout << "成员：\n";
					for (int i = 0; i < ttarget->member.size(); i++) {
						WeiBo_Lyc* tgmname = getself(ttarget->member[i]);
						tttt(); cout << "ID：" << tgmname->return_ID() <<
							" 昵称：" << tgmname->return_name() << endl << endl;
					}
				}
				//cout << "\033[1;1H"; 
				//cout << "\033[100A";
				//for (int i = 0; i < 5; i++)cout << endl;
				//1.解散/退出群
				//2.T人 
				//3/转让群主 群主专用
				//4.加入群请求处理 WeiBo专用
				//5.设置临时讨论组 WeiBo专用
				//6.设置/取消管理员 群主专用 WeiBo专用
				tttt(); cout << "|*=============管理群==============*|" << endl;
				tttt(); cout << "|*          1.T人                  *|" << endl;//
				tttt(); cout << "|*          2.转让群主             *|" << endl;//
				tttt(); cout << "|*          3.加入群请求处理       *|" << endl;
				tttt(); cout << "|*          4.创建子群             *|" << endl;
				tttt(); cout << "|*          5.设置/取消管理员      *|" << endl;//
				tttt(); cout << "请输入您要使用的群功能:\n";
				tttt(); cout << "（输入-1返回菜单)\n";
				putt(str);
				if (str == "-1")return;
				else {
					int select = judge_input_menu(str, 6);
					switch (select) {
					case 1: {
						//tmem();
						if (flag == 2) {
							tttt(); cout << "子群无法执行T人操作\n";
							any_continue(5);
						}
						else {
							tttt(); cout << "请输入您要T的群员的ID：\n";
							string Tedid; putt(Tedid); int Tsub;
							if (memflag == 0) {
								tttt(); cout << "您无此执行功能的权限\n";
								any_continue(5);
							}
							else if (memflag == 1) {
								int Tedflag = 0;
								WeiBo_Lyc* Ted = nullptr;
								for (int i = 0; i < target->members.size(); i++) {
									if (target->members[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								if (!Tedflag) {
									tttt(); cout << "该群不存在此用户或您没有对该用户执行T人的权限\n";
									any_continue(5);
								}
								else {
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "确定T该用户吗\n";
									tttt(); cout << "1.是2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->members.size(); i++) {
											if (target->members[i] == Ted->return_ID()) {
												target->members.erase(target->members.begin() + i);
											}
										}
										groupssave();
										Ted->groups.erase(Ted->groups.begin() + Tsub);
										Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
							}
							else if (memflag == 2) {
								int Tedflag = 0, Tedstu;
								WeiBo_Lyc* Ted = nullptr;
								for (int i = 0; i < target->members.size(); i++) {
									if (target->members[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tedstu = 0;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								for (int i = 0; i < target->admins.size(); i++) {
									if (target->admins[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tedstu = 1;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								if (Tedid == client->return_ID()) {
									tttt(); cout << "您没有对该用户执行T人的权限\n";
									any_continue(5);
								}
								else if (!Tedflag) {
									tttt(); cout << "该群不存在此用户\n";
									any_continue(5);
								}
								else {
									if (Tedstu == 0) {
										tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
										tttt(); cout << "确定T该用户吗\n";
										tttt(); cout << "1.是2.否\n";
										int Topt; putt(Topt);
										switch (Topt) {
										case 1: {
											for (int i = 0; i < target->members.size(); i++) {
												if (target->members[i] == Ted->return_ID()) {
													target->members.erase(target->members.begin() + i);
												}
											}
											groupssave();
											Ted->groups.erase(Ted->groups.begin() + Tsub);
											Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
											break;
										}
										case 2: {
											break;
										}
										default: {
											tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
											any_continue(5);
											continue;
										}
										}
									}
									else if (Tedstu == 1) {
										tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
										tttt(); cout << "确定T该用户吗\n";
										tttt(); cout << "1.是 2.否\n";
										int Topt; putt(Topt);
										switch (Topt) {
										case 1: {
											for (int i = 0; i < target->admins.size(); i++) {
												if (target->admins[i] == Ted->return_ID()) {
													target->admins.erase(target->admins.begin() + i);
												}
											}
											groupssave();
											Ted->groups.erase(Ted->groups.begin() + Tsub);
											Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
											break;
										}
										case 2: {
											break;
										}
										default: {
											tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
											any_continue(5);
											continue;
										}
										}
									}
									tttt(); cout << "操作成功\n";
									any_continue(5);
									break;
								}
							}
						}
						break;
					}
					case 2: {
						if (target->return_masterID() == client->return_ID()) {
							int Tedflag = 0, Tedstu;
							tttt(); cout << "请输入您转让的群员的ID：\n";
							tttt(); cout << "（在转让后，您将成为普通群员）\n";
							string Tedid; putt(Tedid); int Tsub;
							WeiBo_Lyc* Ted = nullptr;
							for (int i = 0; i < target->members.size(); i++) {
								if (target->members[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 0;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							for (int i = 0; i < target->admins.size(); i++) {
								if (target->admins[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 1;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							if (target->return_masterID() == Tedid) {
								tttt(); cout << "您不能对自己进行此操作\n";
								any_continue(5);
							}
							else if (!Tedflag) {
								tttt(); cout << "该群不存在此用户\n";
								any_continue(5);
							}
							else {
								if (Tedstu == 0) {
									WeiBo_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "您确定转让给该用户吗\n";
									tttt(); cout << "1.是2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->members.size(); i++) {
											if (target->members[i] == Ted->return_ID()) {
												target->members.erase(target->members.begin() + i);
											}
										}
										target->masterID = Ted->return_ID();
										groupssave();
										target->members.push_back(client->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								else if (Tedstu == 1) {
									WeiBo_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "您确定转让给该用户吗\n";
									tttt(); cout << "1.是 2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->admins.size(); i++) {
											if (target->admins[i] == Ted->return_ID()) {
												target->admins.erase(target->admins.begin() + i);
											}
										}
										target->masterID = Ted->return_ID();
										groupssave();
										target->members.push_back(client->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								tttt(); cout << "操作成功\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "您没有转让群主的权限\n";
							any_continue(5);
						}
						break;
					}
					case 3: {
						f5(5);
						tttt(); cout << "申请人：\n\n";
						int num = 1;
						for (int i = 0; i < target->tempmem.size(); i++) {
							WeiBo_Lyc* tmtarget = getself(target->tempmem[i]);
							for (int j = 0; j < tmtarget->groups.size(); j++) {
								if (tmtarget->groups[j] == target) {
									if (tmtarget->groupsflag[j] == -1 || tmtarget->groupsflag[j] == -3) {
										tttt(); cout << "第" << num << "位\n";
										tttt(); cout << "ID：" << tmtarget->return_ID() << " 昵称："
											<< tmtarget->return_name() << endl << endl;
										num++;
									}
								}
							}
						}
						if (target->tempmem.empty()) {
							tttt(); cout << "暂无请求\n";
							any_continue(5);
						}
						else {
							tttt(); cout << "请输入你要处理的请求：（位）\n";
							int sub; putt(sub);
							if (sub<1 || sub>target->tempmem.size()) {
								tttt(); cout << "输入范围有误\n";
							}
							else {
								tttt(); cout << "您要同意该用户的申请吗\n";
								tttt(); cout << "1.同意 2.拒绝\n";
								int opt; putt(opt);
								switch (opt) {
								case 1: {
									WeiBo_Lyc* tmtarget = getself(target->tempmem[sub - 1]);
									for (int i = 0; i < tmtarget->groups.size(); i++) {
										if (tmtarget->groups[i]->return_groupID() == target->return_groupID()) {
											target->tempmem.erase(target->tempmem.begin() + sub - 1);
											target->members.push_back(tmtarget->return_ID());
											tmtarget->groupsflag[i] = 0;
										}
									}

									tttt(); cout << "处理成功\n";
									any_continue(5);
									break;
								}
								case 2: {
									WeiBo_Lyc* tmtarget = getself(target->tempmem[sub - 1]);
									for (int i = 0; i < tmtarget->groups.size(); i++) {
										if (tmtarget->groups[i]->return_groupID() == target->return_groupID()) {
											target->tempmem.erase(target->tempmem.begin() + sub - 1);
											tmtarget->groupsflag.erase(tmtarget->groupsflag.begin() + i);
											tmtarget->groups.erase(tmtarget->groups.begin() + i);
										}
									}
									tttt(); cout << "处理成功\n";
									any_continue(5);
									break;
								}
								default: {
									tttt(); cout << "由于不合法的输入，将回到菜单\n";
									any_continue(5);
								}
								}
							}
						}
						break;
					}
					case 4: {
						tttt(); cout << "子群是WeiBo类型群的特有功能\n";
						tttt(); cout << "子群没有群主或管理员，不可新增成员\n";
						tttt(); cout << "子群的成员均可解散子群\n";
						tttt(); cout << "请输入你要创建的子群昵称：\n";
						string name; putt(name);
						int tid = generate_ID(); string id;
						stringstream temp;
						temp << tid;
						temp >> id;
						target->tempGroups.push_back(new Temp_Group_Lyc(id, name));
						target->tempGroups.back()->member.push_back(client->return_ID());
						tttt(); cout << "请依次输入你要从父群拉群到子群的群友ID：\n";
						tttt(); cout << "(输入-1结束)\n";
						while (1) {
							string gfriend;
							putt(gfriend);
							if (gfriend == "-1")break;
							else {
								WeiBo_Lyc* Gfriend = nullptr;
								Gfriend = getself(gfriend);
								if (Gfriend) {
									target->tempGroups.back()->member.push_back(gfriend);
								}
							}
						}
						tttt(); cout << "创建成功\n";
						tttt(); cout << "群ID：" << target->tempGroups.back()->return_groupID() <<
							" 群名：" << target->tempGroups.back()->return_name() << endl;

						ofstream file;
						string filename = "WeiBo\\Groups\\" + target->return_groupID() + "\\" +
							target->return_groupID() + "songroups\\list.txt";
						file.open(filename, ios::app);
						file << id << endl << name << endl;
						file.close();
						groupssave();
						savechange();
						any_continue(5);
						break;
					}
					case 5: {
						if (target->return_masterID() == client->return_ID()) {
							int Tedflag = 0, Tedstu;
							WeiBo_Lyc* Ted = nullptr;
							tttt(); cout << "请输入您处理的群员的ID：\n";
							string Tedid; putt(Tedid); int Tsub;
							for (int i = 0; i < target->members.size(); i++) {
								if (target->members[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 0;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							for (int i = 0; i < target->admins.size(); i++) {
								if (target->admins[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 1;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							if (target->return_masterID() == Tedid) {
								tttt(); cout << "您不能对自己进行此操作\n";
								any_continue(5);
							}
							else if (!Tedflag) {
								tttt(); cout << "该群不存在此用户\n";
								any_continue(5);
							}
							else {
								if (Tedstu == 0) {
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "该用户是普通成员，确定将其升级为管理员吗\n";
									tttt(); cout << "1.是2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->members.size(); i++) {
											if (target->members[i] == Ted->return_ID()) {
												target->members.erase(target->members.begin() + i);
											}
										}
										groupssave();
										target->admins.push_back(Ted->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								else if (Tedstu == 1) {
									WeiBo_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "该用户是管理员，确定将其降级为普通用户吗\n";
									tttt(); cout << "1.是 2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->admins.size(); i++) {
											if (target->admins[i] == Ted->return_ID()) {
												target->admins.erase(target->admins.begin() + i);
											}
										}
										groupssave();
										target->members.push_back(Ted->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								tttt(); cout << "操作成功\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "您没有设置/取消管理员权限\n";
							any_continue(5);
						}
					}
					default: {
						continue;
					}
					}
					groupssave();
					savechange();
				}
			}
		}
	}
}

void Core_WeiBo_Lyc::joingroups()
{
	while (1) {
		getinfor();
		f5(7);
		tttt(); cout << "请输入你要加入的群ID：\n";
		string tid; putt(tid);
		ifstream file;
		string filename = "WeiBo\\Groups\\groupslist.txt";
		string tgid, tgname;
		file.open(filename, ios::in);
		int flag = 0;
		while (file >> tgid >> tgname) {
			if (tgid == tid) {
				flag = 1;
				break;
			}
		}
		if (!flag) {
			tttt(); cout << "未找到该群\n";
			any_continue(5);
			return;
		}
		else {
			int gflag = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (tgid == client->groups[i]->return_groupID()) {
					if (client->groupsflag[i] == 0) {
						tttt(); cout << "您已加入此群\n";
					}
					else if (client->groupsflag[i] == -2) {
						client->groupsflag[i] = -3;
						tttt(); cout << "入群申请已发送\n";
					}
					else {
						tttt(); cout << "入群申请已发送\n";
					}
					gflag = 1;
					break;
				}
			}
			if (!gflag) {
				for (int i = 0; i < WeiBogroups.size(); i++) {
					if (tgid == WeiBogroups[i]->return_groupID()) {
						client->groups.push_back(WeiBogroups[i]);
						client->groupsflag.push_back(-1);
						client->groups.back()->tempmem.push_back(client->return_ID());
					}

				}
				tttt(); cout << "入群申请已发送\n";
			}
			groupssave();
			savechange();
			any_continue(5);
			return;
		}
	}
}

void Core_WeiBo_Lyc::invitefriends()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				cout << endl;
			}
		}
		int select;
		string str;
		//cout << "\033[1;1H";
		//for (int i = 0; i < 5; i++)cout << endl;
		tttt(); cout << "|*==========推荐好友入群===========*|" << endl;
		tttt(); cout << "请输入您要推荐的群的ID:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				f5(7);
				tttt(); cout << "该群信息如下所示\n\n";
				tttt(); cout << "群ID：" << target->return_groupID() << endl;
				tttt(); cout << "群昵称：" << target->return_name() << endl;
				WeiBo_Lyc* ttarget = getself(target->return_masterID());
				tttt(); cout << "群主：" << endl;
				tttt(); cout << "ID：" << ttarget->return_ID() <<
					" 昵称：" << ttarget->return_name() << endl << endl << endl;


				tttt(); cout << "管理员：\n";
				for (int i = 0; i < target->admins.size(); i++) {
					ttarget = getself(target->admins[i]);
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl;
				}

				cout << endl;
				tttt(); cout << "普通成员：\n";
				for (int i = 0; i < target->members.size(); i++) {
					ttarget = getself(target->members[i]);
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl;
				}
				tttt(); cout << "请输入你要推荐的好友的ID:\n";
				string fid; putt(fid);
				int fflag = 0;
				WeiBo_Lyc* fri = nullptr;
				for (int i = 0; i < client->friends.size(); i++) {
					if (fid == client->friends[i]->return_ID()) {
						fflag = 1;
						fri = getself(fid);
					}
				}
				if (!fflag) {
					tttt(); cout << "未查询到该好友\n";
					any_continue(5);
				}
				else {
					int thflag = 0;
					for (int i = 0; i < fri->groups.size(); i++) {
						if (fri->groups[i] == target) {
							thflag = 1;
							if (fri->groupsflag[i] == -3 || fri->groupsflag[i] == -1) {
								fri->groupsflag[i] = -3;
								tttt(); cout << "邀请已发送\n";
							}
							else if (fri->groupsflag[i] == -2) {
								fri->groupsflag[i] = -2;
								tttt(); cout << "邀请已发送\n";
							}
							else if (fri->groupsflag[i] == 0) {
								tttt(); cout << "该用户已加入\n";
							}
							break;
						}
					}
					if (!thflag) {
						fri->groups.push_back(target);
						fri->groupsflag.push_back(-2);
						target->tempmem.push_back(fri->return_ID());
						tttt(); cout << "邀请已发送\n";
					}
					groupssave();
					savechange();
					any_continue(5);
				}
				return;
			}
		}
	}
}

void Core_WeiBo_Lyc::solveinvitation()
{
	while (1) {
		getinfor();
		f5(5);
		vector<int>gsub;
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == -2 || client->groupsflag[i] == -3) {
				gsub.push_back(i);
			}
		}
		for (int i = 0; i < gsub.size(); i++) {
			tttt(); cout << "第" << i + 1 << "位\n";
			tttt(); cout << "群ID：" << client->groups[gsub[i]]->return_groupID() <<
				"群名：" << client->groups[gsub[i]]->return_name() << endl << endl;
		}
		if (gsub.empty()) {
			tttt(); cout << "暂无可应答的入群\n";
			any_continue(5);
			return;
		}
		else {
			tttt(); cout << "请输入你要应答的推荐入群的位数：\n";
			tttt(); cout << "(如果您选择暂不加入，该推荐入群仍然会留在您的账户中)\n";
			tttt(); cout << "(输入-1返回菜单)\n";
			int sub; putt(sub);
			if (sub == -1)return;
			if (sub<1 || sub>gsub.size()) {
				tttt(); cout << "由于超出范围，默认您要重新输入\n";
				continue;
			}
			else {
				tttt(); cout << "群ID：" << client->groups[gsub[sub - 1]]->return_groupID() <<
					"群名：" << client->groups[gsub[sub - 1]]->return_name() << endl << endl;
				tttt(); cout << "您要加入吗？\n";
				tttt(); cout << "1.加入 2.暂不加入\n";
				int opt; putt(opt);
				switch (opt)
				{
				case 1: {
					client->groupsflag[gsub[sub - 1]] = 0;
					for (int i = 0; i < client->groups[gsub[sub - 1]]->tempmem.size(); i++) {
						if (client->groups[gsub[sub - 1]]->tempmem[i] == client->return_ID()) {
							client->groups[gsub[sub - 1]]->tempmem.erase(client->groups[gsub[sub - 1]]->tempmem.begin() + i);
							client->groups[gsub[sub - 1]]->members.push_back(client->return_ID());
							groupssave();
							savechange();
						}
					}
					tttt(); cout << "操作成功\n";
					break;
				}
				case 2: {
					tttt(); cout << "操作成功\n";
					break;
				}
				default:
					tttt(); cout << "由于不合法的输出，默认您要重新输入\n";
					continue;
				}
			}
		}
		any_continue(5);
	}
}

void Core_WeiBo_Lyc::rungroups1()
{
	while (1) {
		getinfor();
		string QWflag = "Q";
		string conflag;
		f5(5); if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				tttt(); cout << "该群子群:\n";
				if (client->groups[i]->tempGroups.empty()) {
					tttt(); cout << "无子群:\n";
				}
				else {
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						tttt(); cout << "群ID：" << client->groups[i]->tempGroups[j]->return_groupID() << endl;
						tttt(); cout << "群昵称：" << client->groups[i]->tempGroups[j]->return_name() << endl << endl;
					}
				}
				cout << endl;
			}
		}
		int select;
		string str;
		for (int i = 0; i < 5; i++)cout << endl;
		//1.解散/退出群
		//2.T人 
		//3/转让群主 群主专用
		//4.加入群请求处理 WeiBo专用
		//5.设置临时讨论组 WeiBo专用
		//6.设置/取消管理员 群主专用 WeiBo专用
		tttt(); cout << "|*=============管理群==============*|" << endl;
		tttt(); cout << "|*          1.T人                  *|" << endl;
		tttt(); cout << "|*          2.转让群主             *|" << endl;
		tttt(); cout << "请输入您要管理的群的ID:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
					for (int j = 0; j < client->groups[i]->tempGroups.size(); j++) {
						if (client->groups[i]->tempGroups[j]->return_groupID() == str) {
							for (int k = 0; k < client->groups[i]->tempGroups[j]->member.size(); k++) {
								if (client->groups[i]->tempGroups[j]->member[k] == client->return_ID()) {
									flag = 2;
									sub = i;
									tsub = j;
									target = client->groups[i];
									ttarget = client->groups[i]->tempGroups[j];
									break;
								}
							}
						}
					}
				}
			}
			if (!flag || flag == 2) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				int memflag;
				if (flag == 1) {
					f5(5);
					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					WeiBo_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;
					if (ttarget->return_ID() == client->return_ID())memflag = 2;



					tttt(); cout << "成员：\n";


					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						if (ttarget->return_ID() == client->return_ID())memflag = 1;
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						if (ttarget->return_ID() == client->return_ID())memflag = 0;
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
				}
				//cout << "\033[1;1H"; 
				//cout << "\033[100A";
				//for (int i = 0; i < 5; i++)cout << endl;
				//1.解散/退出群
				//2.T人 
				//3/转让群主 群主专用
				//4.加入群请求处理 WeiBo专用
				//5.设置临时讨论组 WeiBo专用
				//6.设置/取消管理员 群主专用 WeiBo专用
				tttt(); cout << "|*=============管理群==============*|" << endl;
				tttt(); cout << "|*          1.T人                  *|" << endl;//
				tttt(); cout << "|*          2.转让群主             *|" << endl;//
				tttt(); cout << "请输入您要使用的群功能:\n";
				tttt(); cout << "（输入-1返回菜单)\n";
				putt(str);
				if (str == "-1")return;
				else {
					int select = judge_input_menu(str, 6);
					switch (select) {
					case 1: {
						//tmem();
						if (flag == 2) {
							tttt(); cout << "子群无法执行T人操作\n";
							any_continue(5);
						}
						else {
							tttt(); cout << "请输入您要T的群员的ID：\n";
							string Tedid; putt(Tedid); int Tsub;
							if (memflag == 0 || memflag == 1) {
								tttt(); cout << "您无此执行功能的权限\n";
								any_continue(5);
							}
							else if (memflag == 2) {
								int Tedflag = 0, Tedstu;
								WeiBo_Lyc* Ted = nullptr;
								for (int i = 0; i < target->members.size(); i++) {
									if (target->members[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tedstu = 0;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								for (int i = 0; i < target->admins.size(); i++) {
									if (target->admins[i] == Tedid) {
										Ted = getself(Tedid);
										for (int j = 0; j < Ted->groups.size(); j++) {
											if (Ted->groups[j]->groupID == target->groupID) {
												if (Ted->groupsflag[j] == 0) {
													Tedflag = 1;
													Tedstu = 1;
													Tsub = i;

												}
												break;
											}
										}
									}
								}
								if (Tedid == client->return_ID()) {
									tttt(); cout << "您没有对该用户执行T人的权限\n";
									any_continue(5);
								}
								else if (!Tedflag) {
									tttt(); cout << "该群不存在此用户\n";
									any_continue(5);
								}
								else {
									if (Tedstu == 0) {
										tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
										tttt(); cout << "确定T该用户吗\n";
										tttt(); cout << "1.是2.否\n";
										int Topt; putt(Topt);
										switch (Topt) {
										case 1: {
											for (int i = 0; i < target->members.size(); i++) {
												if (target->members[i] == Ted->return_ID()) {
													target->members.erase(target->members.begin() + i);
												}
											}
											groupssave();
											Ted->groups.erase(Ted->groups.begin() + Tsub);
											Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
											break;
										}
										case 2: {
											break;
										}
										default: {
											tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
											any_continue(5);
											continue;
										}
										}
									}
									else if (Tedstu == 1) {
										tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
										tttt(); cout << "确定T该用户吗\n";
										tttt(); cout << "1.是 2.否\n";
										int Topt; putt(Topt);
										switch (Topt) {
										case 1: {
											for (int i = 0; i < target->admins.size(); i++) {
												if (target->admins[i] == Ted->return_ID()) {
													target->admins.erase(target->admins.begin() + i);
												}
											}
											groupssave();
											Ted->groups.erase(Ted->groups.begin() + Tsub);
											Ted->groupsflag.erase(Ted->groupsflag.begin() + Tsub);
											break;
										}
										case 2: {
											break;
										}
										default: {
											tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
											any_continue(5);
											continue;
										}
										}
									}
									tttt(); cout << "操作成功\n";
									any_continue(5);
									break;
								}
							}
						}
						break;
					}
					case 2: {
						if (target->return_masterID() == client->return_ID()) {
							int Tedflag = 0, Tedstu;
							tttt(); cout << "请输入您转让的群员的ID：\n";
							tttt(); cout << "（在转让后，您将成为普通群员）\n";
							string Tedid; putt(Tedid); int Tsub;
							WeiBo_Lyc* Ted = nullptr;
							for (int i = 0; i < target->members.size(); i++) {
								if (target->members[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 0;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							for (int i = 0; i < target->admins.size(); i++) {
								if (target->admins[i] == Tedid) {
									Ted = getself(Tedid);
									for (int j = 0; j < Ted->groups.size(); j++) {
										if (Ted->groups[j]->groupID == target->groupID) {
											if (Ted->groupsflag[j] == 0) {
												Tedflag = 1;
												Tedstu = 1;
												Tsub = i;

											}
											break;
										}
									}
								}
							}
							if (target->return_masterID() == Tedid) {
								tttt(); cout << "您不能对自己进行此操作\n";
								any_continue(5);
							}
							else if (!Tedflag) {
								tttt(); cout << "该群不存在此用户\n";
								any_continue(5);
							}
							else {
								if (Tedstu == 0) {
									WeiBo_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "您确定转让给该用户吗\n";
									tttt(); cout << "1.是2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->members.size(); i++) {
											if (target->members[i] == Ted->return_ID()) {
												target->members.erase(target->members.begin() + i);
											}
										}
										target->masterID = Ted->return_ID();
										groupssave();
										target->members.push_back(client->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								else if (Tedstu == 1) {
									WeiBo_Lyc* Ted = getself(Tedid);
									tttt(); cout << "ID：" << Ted->return_ID() << " 昵称：" << Ted->return_name() << endl;
									tttt(); cout << "您确定转让给该用户吗\n";
									tttt(); cout << "1.是 2.否\n";
									int Topt; putt(Topt);
									switch (Topt) {
									case 1: {
										for (int i = 0; i < target->admins.size(); i++) {
											if (target->admins[i] == Ted->return_ID()) {
												target->admins.erase(target->admins.begin() + i);
											}
										}
										target->masterID = Ted->return_ID();
										groupssave();
										target->members.push_back(client->return_ID());
										groupssave();
										break;
									}
									case 2: {
										break;
									}
									default: {
										tttt(); cout << "由于检测到不合法的输入，将回到菜单\n";
										any_continue(5);
										continue;
									}
									}
								}
								tttt(); cout << "操作成功\n";
								any_continue(5);
								break;
							}
						}
						else {
							tttt(); cout << "您没有转让群主的权限\n";
							any_continue(5);
						}
						break;
					}
					}
					groupssave();
					savechange();
				}
			}
		}
	}
}

void Core_WeiBo_Lyc::quitgroups1()
{
	while (1) {
		getinfor();
		f5(5);
		if (client->groups.empty()) {
			tttt(); cout << "暂未加入任何群\n";
		}
		else {
			int num = 0;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] != 0)num++;
			}
			if (num == client->groups.size()) {
				tttt(); cout << "暂未加入任何群\n";
			}
		}
		for (int i = 0; i < client->groups.size(); i++) {
			if (client->groupsflag[i] == 0) {
				tttt(); cout << "群ID：" << client->groups[i]->return_groupID() << endl;
				tttt(); cout << "群昵称：" << client->groups[i]->return_name() << endl << endl;
				cout << endl;
			}
		}
		int select;
		string str;
		for (int i = 0; i < 5; i++)cout << endl;
		tttt(); cout << "|*==========退出/解散群==========*|" << endl;
		tttt(); cout << "请输入您要退出/解散的群的ID:\n";
		tttt(); cout << "子群仅可解散:\n";
		tttt(); cout << "（输入-1返回菜单)\n";
		putt(str);
		if (str == "-1")return;
		else {
			int flag = 0;
			QQ_Group_Lyc* target = nullptr;
			Temp_Group_Lyc* ttarget = nullptr;
			int sub, tsub;
			for (int i = 0; i < client->groups.size(); i++) {
				if (client->groupsflag[i] == 0) {
					if (client->groups[i]->return_groupID() == str) {
						flag = 1;
						sub = i;
						target = client->groups[i];
						break;
					}
				}
			}
			if (!flag) {
				tttt(); cout << "未查找到该群\n";
				any_continue(5);
			}
			else {
				f5(15);
				if (flag == 1) {
					int memflag = 0;
					int memsub;

					tttt(); cout << "该群信息如下所示\n\n";
					tttt(); cout << "群ID：" << target->return_groupID() << endl;
					tttt(); cout << "群昵称：" << target->return_name() << endl;
					WeiBo_Lyc* ttarget = getself(target->return_masterID());
					tttt(); cout << "群主：" << endl;
					tttt(); cout << "ID：" << ttarget->return_ID() <<
						" 昵称：" << ttarget->return_name() << endl << endl << endl;


					tttt(); cout << "管理员：\n";
					for (int i = 0; i < target->admins.size(); i++) {
						ttarget = getself(target->admins[i]);
						if (ttarget->return_ID() == client->return_ID()) {
							memflag = 1;
							memsub = i;
						}
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}

					cout << endl;
					tttt(); cout << "普通成员：\n";
					for (int i = 0; i < target->members.size(); i++) {
						ttarget = getself(target->members[i]);
						if (ttarget->return_ID() == client->return_ID()) {
							memflag = 0;
							memsub = i;
						}
						tttt(); cout << "ID：" << ttarget->return_ID() <<
							" 昵称：" << ttarget->return_name() << endl << endl;
					}
					cout << "\033[1;1H";
					for (int i = 0; i < 5; i++)cout << endl;

					int opt;
					if (target->return_masterID() == client->return_ID()) {//判断操作用户是否是群主
						memflag = 2;
						tttt(); cout << "您是当前群群主，若执行退群操作，则将视为解散群\n";
						tttt(); cout << "若想在保留该群的情况下退出，则请先移步管理群功能转让群主\n";
						tttt(); cout << "您要解散该群吗\n";
						tttt(); cout << "1.是 2.否\n";
						putt(opt);
					}
					else {
						tttt(); cout << "您要退出该群吗\n";
						tttt(); cout << "1.是 2.否\n";
						putt(opt);
					}

					switch (opt)
					{
					case 1: {
						if (memflag == 1) {
							target->admins.erase(target->admins.begin() + memsub);
							groupssave();
							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);
						}
						else if (memflag == 0) {
							target->members.erase(target->members.begin() + memsub);
							groupssave();
							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);
						}
						else if (memflag == 2) {
							//管理员退群
							for (int i = 0; i < target->admins.size(); i++) {
								WeiBo_Lyc* tttarget = getself(target->admins[i]);
								for (int j = 0; j < tttarget->return_groups().size(); j++) {
									if (tttarget->groups[j]->return_groupID() == target->return_groupID()) {
										tttarget->groups.erase(tttarget->groups.begin() + i);
										break;
									}
								}
							}
							//普通成员退群
							for (int i = 0; i < target->members.size(); i++) {
								WeiBo_Lyc* tttarget = getself(target->members[i]);
								for (int j = 0; j < tttarget->return_groups().size(); j++) {
									if (tttarget->groups[j]->return_groupID() == target->return_groupID()) {
										tttarget->groups.erase(tttarget->groups.begin() + i);
										break;
									}
								}
							}

							client->groups.erase(client->groups.begin() + sub);
							client->groupsflag.erase(client->groupsflag.begin() + sub);

							//删除总群文件内的该群信息
							ofstream file1;
							ifstream file2;
							string filename0 = "WeiBo\\Groups\\groupslist.txt";
							vector<string>tempid, tempname;
							string tid, tname;
							file2.open(filename0, ios::in);
							while (file2 >> tid >> tname) {
								if (tid != target->return_groupID()) {
									tempid.push_back(tid);
									tempname.push_back(tname);
								}
							}
							file2.close();
							file1.open(filename0, ios::out);
							while (!tempid.empty()) {
								file1 << *tempid.begin() << endl << *tempname.begin()
									<< endl << endl;
								tempid.erase(tempid.begin());
								tempname.erase(tempname.begin());

							}

							string filename = "WeiBo\\Groups\\" + target->return_groupID();
							string filename1 = filename + "\\" + target->return_groupID() + ".txt";
							string filename2 = filename + "\\" + target->return_groupID() + "admins.txt";
							string filename5 = filename + "\\" + target->return_groupID() + "tempmem.txt";
							DeleteFile(filename1.c_str());
							DeleteFile(filename2.c_str());
							DeleteFile(filename5.c_str());

							//删除子群信息
							string filename3 = filename + "\\" + target->return_groupID() + "songroups";
							for (int i = 0; i < target->tempGroups.size(); i++) {
								string tgid = target->tempGroups[i]->return_groupID();
								string filename4 = filename3 + "\\" + tgid + ".txt";
								DeleteFile(filename4.c_str());

							}
							string filename4 = filename3 + "\\list.txt";
							DeleteFile(filename4.c_str());

							RemoveDirectory(filename3.c_str());
							RemoveDirectory(filename.c_str());

							delete target;
						}
						break;
					}case 2: {
						break;
					}
					default: {
						tttt(); cout << "由于检测到不合法的输出，默认您要重新输入要退出/解散的群ID\n";
						any_continue(5);
						continue;
					}
					}
				}
				groupssave();
				savechange();
				cout << endl;
				tttt(); cout << "操作成功\n";
				tttt(); cout << "按回车键返回菜单\n";
				tttt(); getchar();
				return;
			}
		}
	}
}

void Core_WeiBo_Lyc::groupchat()
{

	while (1) {
		f5(5);
		tttt(); cout << "请输入您要进行通讯的群的ID:\n";
		tttt(); cout << "(输入-1返回)\n";
		string gid; putt(gid);
		if (gid == "-1")return;
		int flag = 0;
		for (int i = 0; i < client->groups.size(); i++) {
			if (gid == client->groups[i]->groupID) {
				if (client->groupsflag[i] == 0) {
					flag = 1;
					break;
				}
			}
		}
		if (!flag) {
			tttt(); cout << "未找到该群\n";
			any_continue(5);
		}
		else {
			vchat(gid, WeiBosystem);
		}
	}
}

WeiBo_Lyc* Core_WeiBo_Lyc::getself(string id)
{
	for (int i = 0; i < WeiBos.size(); i++) {
		if (WeiBos[i]->return_ID() == id) {
			return WeiBos[i];
		}
	}
	return nullptr;
}
