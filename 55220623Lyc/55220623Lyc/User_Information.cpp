#define _CRT_SECURE_NO_WARNINGS
#include "User_Information.h"
#include "system.h"
#include"menu.h"
#include"tools.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<Windows.h>
using namespace std;

string Tencent_Lyc::return_ID()
{
	return ID;
}

string Tencent_Lyc::return_Passwd()
{
	return passwd;
}

string Tencent_Lyc::return_name()
{
	return name;
}

string Tencent_Lyc::return_birthday()
{
	return birthday;
}

string Tencent_Lyc::return_applyTime()
{
	return applyTime;
}

string Tencent_Lyc::return_sex()
{
	return sex;
}

string Tencent_Lyc::return_area()
{
	return area;
}

int Tencent_Lyc::return_friendsNum()
{
	return friendsNum;
}

int Tencent_Lyc::return_groupsNum()
{
	return groupsNum;
}

void Tencent_Lyc::change_passwd(string newpw)
{
	passwd = newpw;
}

void Tencent_Lyc::change_name(string newname)
{
	name = newname;
}

void Tencent_Lyc::change_bir(string newname)
{
	birthday = newname;
}

void Tencent_Lyc::change_sex(int n)
{
	if (n == 0)sex = man.SexFlag;
	else sex = man.SexFlag;
}

void Tencent_Lyc::change_area(string newarea)
{
	area = newarea;
}

void Tencent_Lyc::change_groupsNum(int num)
{
	groupsNum = num;
}

void Tencent_Lyc::change_friendsNum(int num)
{
	friendsNum = num;
}

int Tencent_Lyc::return_flag()
{
	return flag;
}

QQ_Lyc::QQ_Lyc(string id)//注册QQ
{
	//画面切换字符展示输入居中
	system("color 8b");
	f5(12);
	if (id == "-1") {
		int tempID = generate_ID();
		stringstream tempss{};
		tempss << tempID;
		tempss >> ID;
	}
	else {
		ID = id;
	}
	tttt(); cout << "现在进行QQ的注册\n";
	any_continue(5);
	int flagname = 1;
	while (flagname) {
		f5(13);
		tttt(); cout << "请输入您的昵称:\n";
		while (1) {
			tttt();
			if (cin.peek() == '\n') {
				clear_inputBuffer(stdin);
				cout << "\033[F";
			}
			else {
				cin >> name;
				clear_inputBuffer(stdin);
				break;
			}
		}
		f5(13);
		tttt(); cout << "您确定使用这个昵称吗：" << name << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		while (1) {
			tttt();
			if (cin.peek() == '\n') {
				clear_inputBuffer(stdin);
				cout << "\033[F";
			}
			else {
				cin >> opt;
				clear_inputBuffer(stdin);
				break;
			}
		}
		switch (opt) {
		case(1):flagname = 0; break;
		case(2):flagname = 1; break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
	f5(13);
	int flagpw = 1;
	while (flagpw) {
		f5(13);
		tttt(); cout << "请输入您的密码:\n";
		putt(passwd);
		f5(13);
		tttt(); cout << "请再次输入您的密码\n";
		string tmppw;
		putt(tmppw);
		if (passwd == tmppw) {
			f5(13);
			tttt(); cout << "您确定使用这个密码吗：" << passwd << "\n";
			tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
			int opt;
			putt(opt);
			switch (opt) {
			case(1):flagpw = 0; break;
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
	f5(13);
	int flagbir = 1;
	while (flagbir) {
		f5(13);
		birthday = bir_input();
		f5(13);
		tttt(); cout << "您确定是这个生日吗：" << birthday << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		putt(opt);
		switch (opt) {
		case(1):flagbir = 0; break;
		case(2):break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
		}
		}
	}
	f5(13);
	int flagsex = 1;
	while (flagsex) {
		f5(13);
		tttt(); cout << "请选择您的性别:\n";
		tttt(); cout << "0.男性 " << "1.女性\n";
		int ch = -1;
		putt(ch);
		switch (ch) {
		case 0:
			sex = man.SexFlag;
			break;
		case 1:
			sex = woman.SexFlag;
			break;
		default:
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入" << endl;
			any_continue(5);
			continue;
		}
		f5(13);
		tttt(); cout << "您确定是这个性别吗：" << sex << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		putt(opt);
		switch (opt) {
		case(1):flagsex = 0; break;
		case(2):break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
		}
		}
	}
	f5(13);
	int flagarea = 1;
	while (flagarea) {
		f5(13);
		tttt(); cout << "请输入您的地区:\n";
		putt(area);
		f5(13);
		tttt(); cout << "您确定是这个地区吗：" << area << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		putt(opt);
		switch (opt) {
		case(1):flagarea = 0; break;
		case(2):break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
		}
		}
	}
	time_t t;
	t = time(NULL);
	char* time;
	time = ctime(&t);
	applyTime = time;
	friendsNum = 0;
	groupsNum = 0;
	tempGNum = 0;
	flag = 0;
	f5(8);
	tttt(); cout << "QQ注册成功" << endl;
	tttt(); cout << "你的QQ号为:" << ID << endl;
	tttt(); cout << "你的QQ昵称为:" << name << endl;
	tttt(); cout << "你的QQ密码为:" << passwd << endl;
	tttt(); cout << "你的注册时间为:" << applyTime;
	tttt(); cout << "请妥善保存帐号和密码" << endl;
	string QQ = "QQ\\" + ID;
	CreateDirectory(QQ.c_str(), NULL);//每个QQ创建一个文件夹
	any_continue(5);
}

QQ_Lyc::QQ_Lyc(string qid, string qname, string qpw, string qbir, string qsex, string qarea, string qappTime) {
	ID = qid;
	passwd = qpw;
	name = qname;
	birthday = qbir;
	applyTime = qappTime;
	sex = qsex;
	area = qarea;
	friendsNum = 0;
	groupsNum = 0;
	tempGNum = 0;
	flag = 0;
}

QQ_Lyc::~QQ_Lyc()
{
	for (int i = 0; i < friends.size(); i++) {
		delete friends[i];
	}
	for (int i = 0; i < groups.size(); i++) {
		delete groups[i];
	}
}

//vector<Friend_Lyc*>& QQ_Lyc::return_friends()
//{
//	return friends;
//}

vector<QQ_Group_Lyc*>& QQ_Lyc::return_groups()
{
	return groups;
}
//
//vector<Temp_Group_Lyc*>& QQ_Lyc::return_tempGroups()
//{
//	return tempGroups;
//}

int QQ_Lyc::return_tempGNum()
{
	return tempGNum;
}

string QQ_Lyc::return_linkWeChat()
{
	return linkWeChat;
}

string QQ_Lyc::return_linkWeiBo()
{
	return linkWeiBo;
}

void QQ_Lyc::get_friends()
{
	ifstream file;
	string qq = ID;
	string filename = "QQ\\" + qq + "\\" + qq + "friends.txt";
	string filename1 = "QQs.txt";
	string nid;
	string nname;
	string nnote;
	string pw;
	string nbir;
	string nsex;
	string narea;
	string time;
	int nflag;

	// 清空当前的好友列表
	friends.clear();

	// 打开文件
	file.open(filename, ios::app);

	vector<string>tmpid;
	vector<string>tmpnote;
	vector<int>tmpflag;

	// 每次从文件中读取一个好友的信息，然后将其添加到列表中

	while (file >> nid >> nnote >> nflag) {
		tmpid.push_back(nid);
		tmpnote.push_back(nnote);
		tmpflag.push_back(nflag);
	}

	file.close();

	file.open(filename1, ios::app);
	while (file >> nid >> nname >> pw >> nbir >> nsex >> narea)
	{
		string empty;
		string time;
		getline(file, empty);
		getline(file, time);
		for (int i = 0; i < tmpid.size(); i++) {
			if (tmpid[i] == nid) {
				friends.push_back(new Friend_Lyc(tmpid[i], nname, tmpnote[i],
					nbir, nsex, narea, tmpflag[i]));
				//cout << friends.back()->return_flag() << endl;
				tmpid.erase(tmpid.begin() + i);
				tmpnote.erase(tmpnote.begin() + i);
				tmpflag.erase(tmpflag.begin() + i);
				break;
			}
		}
	}
	// 关闭文件
	file.close();

	// 更新好友数量
	friendsNum = friends.size();
}

void QQ_Lyc::get_groups()
{
	ifstream file;

	//对于每个用户，都有个群组文件，包含各群ID、群名称和加入信息

	string grouplist = "QQ\\" + ID + "\\" + ID + "groups.txt";
	file.open(grouplist, ios::app);
	string gID, gname;
	int gflag;
	groups.clear();
	groupsflag.clear();
	while (file >> gID >> gname >> gflag) {
		for (int i = 0; i < QQsystem.QQgroups.size(); i++) {
			if (QQsystem.QQgroups[i]->return_groupID() == gID) {
				groups.push_back(QQsystem.QQgroups[i]);
				groupsflag.push_back(gflag);
			}
		}
	}
	file.close();


	groupsNum = groups.size();
}

void QQ_Lyc::get_links()
{
	ifstream file;
	string tmp;
	string LWB = "";
	string LWC = "";
	string filename = "QQ\\" + ID + "\\" + ID + "links.txt";
	file.open(filename, ios::app);
	while (file >> tmp) {
		if (tmp == "WeiBo")file >> linkWeiBo;
		else if (tmp == "WeChat")file >> linkWeChat;
	}
	file.close();
}

WeChat_Lyc::WeChat_Lyc(string id)
{
	//画面切换字符展示输入居中
	system("color 8b");
	f5(12);
	if (id == "-1") {
		int tempID = generate_ID();
		stringstream tempss;
		tempss << tempID;
		tempss >> ID;
	}
	else {
		ID = id;
	}
	tttt(); cout << "现在进行微信的注册\n";
	any_continue(5);
	int flagname = 1;
	while (flagname) {
		f5(13);
		tttt(); cout << "请输入您的昵称:\n";
		tttt(); cin >> name;
		clear_inputBuffer(stdin);
		f5(13);
		tttt(); cout << "您确定使用这个昵称吗：" << name << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1):flagname = 0; break;
		case(2):flagname = 1; break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
	f5(13);
	int flagpw = 1;
	while (flagpw) {
		f5(13);
		tttt(); cout << "请输入您的密码:\n";
		tttt(); cin >> passwd;
		clear_inputBuffer(stdin);
		f5(13);
		tttt(); cout << "请再次输入您的密码\n";
		string tmppw;
		tttt(); cin >> tmppw;
		clear_inputBuffer(stdin);
		if (passwd == tmppw) {
			f5(13);
			tttt(); cout << "您确定使用这个密码吗：" << passwd << "\n";
			tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
			int opt;
			tttt(); cin >> opt;
			clear_inputBuffer(stdin);
			switch (opt) {
			case(1):flagpw = 0; break;
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
	f5(13);
	int flagbir = 1;
	while (flagbir) {
		f5(13);
		birthday = bir_input();
		f5(13);
		tttt(); cout << "您确定是这个生日吗：" << birthday << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1):flagbir = 0; break;
		case(2):break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
		}
		}
	}
	f5(13);
	int flagsex = 1;
	while (flagsex) {
		f5(13);
		tttt(); cout << "请选择您的性别:\n";
		tttt(); cout << "0.男性 " << "1.女性\n";
		int ch = -1;
		tttt(); cin >> ch;
		clear_inputBuffer(stdin);
		switch (ch) {
		case 0:
			sex = man.SexFlag;
			break;
		case 1:
			sex = woman.SexFlag;
			break;
		default:
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入" << endl;
			any_continue(5);
			continue;
		}
		f5(13);
		tttt(); cout << "您确定是这个性别吗：" << sex << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1):flagsex = 0; break;
		case(2):break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
		}
		}
	}
	f5(13);
	int flagarea = 1;
	while (flagarea) {
		f5(13);
		tttt(); cout << "请输入您的地区:\n";
		tttt(); cin >> area;
		clear_inputBuffer(stdin);
		f5(13);
		tttt(); cout << "您确定是这个地区吗：" << area << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1):flagarea = 0; break;
		case(2):break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
		}
		}
	}
	time_t t;
	t = time(NULL);
	char* time;
	time = ctime(&t);
	applyTime = time;
	friendsNum = 0;
	groupsNum = 0;
	flag = 0;
	f5(8);
	tttt(); cout << "微信注册成功" << endl;
	tttt(); cout << "你的微信为:" << ID << endl;
	tttt(); cout << "你的微信昵称为:" << name << endl;
	tttt(); cout << "你的微信密码为:" << passwd << endl;
	tttt(); cout << "你的注册时间为:" << applyTime;
	tttt(); cout << "请妥善保存帐号和密码" << endl;
	string WeChat = "WeChat\\" + ID;
	CreateDirectory(WeChat.c_str(), NULL);//每个QQ创建一个文件夹
	any_continue(5);
}

WeChat_Lyc::WeChat_Lyc(string wcid, string wcname, string wcpw, string wcbir, string wcsex, string wcarea, string wcappTime)
{
	ID = wcid;
	passwd = wcpw;
	name = wcname;
	birthday = wcbir;
	applyTime = wcappTime;
	sex = wcsex;
	area = wcarea;
	friendsNum = 0;
	groupsNum = 0;
	flag = 0;
}

WeChat_Lyc::~WeChat_Lyc()
{
	for (int i = 0; i < friends.size(); i++) {
		delete friends[i];
	}
	for (int i = 0; i < groups.size(); i++) {
		delete groups[i];
	}
}

vector<Friend_Lyc*>& WeChat_Lyc::return_friends()
{
	return friends;
}

vector<QQ_Group_Lyc*>& WeChat_Lyc::return_groups()
{
	return groups;
}

string WeChat_Lyc::return_linkQQ()
{
	return linkQQ;
}

string WeChat_Lyc::return_linkWeiBo()
{
	return linkWeiBo;
}

void WeChat_Lyc::get_friends()
{
	ifstream file;
	string WeChat = ID;
	string filename = "WeChat\\" + WeChat + "\\" + WeChat + "friends.txt";
	string filename1 = "WeChats.txt";
	string nid;
	string nname;
	string nnote;
	string pw;
	string nbir;
	string nsex;
	string narea;
	string time;
	int nflag;

	// 清空当前的好友列表
	friends.clear();

	// 打开文件
	file.open(filename, ios::app);

	vector<string>tmpid;
	vector<string>tmpnote;
	vector<int>tmpflag;

	// 每次从文件中读取一个好友的信息，然后将其添加到列表中

	while (file >> nid >> nnote >> nflag) {
		tmpid.push_back(nid);
		tmpnote.push_back(nnote);
		tmpflag.push_back(nflag);
	}

	file.close();

	file.open(filename1, ios::app);
	while (file >> nid >> nname >> pw >> nbir >> nsex >> narea)
	{
		string empty;
		string time;
		getline(file, empty);
		getline(file, time);
		for (int i = 0; i < tmpid.size(); i++) {
			if (tmpid[i] == nid) {
				friends.push_back(new Friend_Lyc(tmpid[i], nname, tmpnote[i],
					nbir, nsex, narea, tmpflag[i]));
				//cout << friends.back()->return_flag() << endl;
				tmpid.erase(tmpid.begin() + i);
				tmpnote.erase(tmpnote.begin() + i);
				tmpflag.erase(tmpflag.begin() + i);
				break;
			}
		}
	}
	// 关闭文件
	file.close();

	// 更新好友数量
	friendsNum = friends.size();
}

void WeChat_Lyc::get_groups()
{
	ifstream file;

	//对于每个用户，都有个群组文件，包含各群ID、群名称和加入信息

	string grouplist = "WeChat\\" + ID + "\\" + ID + "groups.txt";
	file.open(grouplist, ios::app);
	string gID, gname;
	int gflag;
	groups.clear();
	groupsflag.clear();
	while (file >> gID >> gname >> gflag) {
		for (int i = 0; i < WeChatsystem.WeChatgroups.size(); i++) {
			if (WeChatsystem.WeChatgroups[i]->return_groupID() == gID) {
				groups.push_back(WeChatsystem.WeChatgroups[i]);
				groupsflag.push_back(gflag);
			}
		}
	}
	file.close();


	groupsNum = groups.size();
}

void WeChat_Lyc::get_links()
{
	ifstream file;
	string tmp;
	string LQ = "";
	string LWB = "";
	string filename = "WeChat\\" + ID + "\\" + ID + "links.txt";
	file.open(filename, ios::app);
	while (file >> tmp) {
		if (tmp == "QQ")file >> linkQQ;
		else if (tmp == "WeiBo")file >> linkWeiBo;
	}
	file.close();
}

WeiBo_Lyc::WeiBo_Lyc(string id)
{
	//画面切换字符展示输入居中
	system("color 8b");
	f5(12);
	if (id == "-1") {
		int tempID = generate_ID();
		stringstream tempss;
		tempss << tempID;
		tempss >> ID;
	}
	else {
		ID = id;
	}
	tttt(); cout << "现在进行微博的注册\n";
	any_continue(5);
	int flagname = 1;
	while (flagname) {
		f5(13);
		tttt(); cout << "请输入您的昵称:\n";
		tttt(); cin >> name;
		clear_inputBuffer(stdin);
		f5(13);
		tttt(); cout << "您确定使用这个昵称吗：" << name << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1):flagname = 0; break;
		case(2):flagname = 1; break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
			break;
		}
		}
	}
	f5(13);
	int flagpw = 1;
	while (flagpw) {
		f5(13);
		tttt(); cout << "请输入您的密码:\n";
		tttt(); cin >> passwd;
		clear_inputBuffer(stdin);
		f5(13);
		tttt(); cout << "请再次输入您的密码\n";
		string tmppw;
		tttt(); cin >> tmppw;
		clear_inputBuffer(stdin);
		if (passwd == tmppw) {
			f5(13);
			tttt(); cout << "您确定使用这个密码吗：" << passwd << "\n";
			tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
			int opt;
			tttt(); cin >> opt;
			clear_inputBuffer(stdin);
			switch (opt) {
			case(1):flagpw = 0; break;
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
	f5(13);
	int flagbir = 1;
	while (flagbir) {
		f5(13);
		birthday = bir_input();
		f5(13);
		tttt(); cout << "您确定是这个生日吗：" << birthday << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1):flagbir = 0; break;
		case(2):break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
		}
		}
	}
	f5(13);
	int flagsex = 1;
	while (flagsex) {
		f5(13);
		tttt(); cout << "请选择您的性别:\n";
		tttt(); cout << "0.男性 " << "1.女性\n";
		int ch = -1;
		tttt(); cin >> ch;
		clear_inputBuffer(stdin);
		switch (ch) {
		case 0:
			sex = man.SexFlag;
			break;
		case 1:
			sex = woman.SexFlag;
			break;
		default:
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入" << endl;
			any_continue(5);
			continue;
		}
		f5(13);
		tttt(); cout << "您确定是这个性别吗：" << sex << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1):flagsex = 0; break;
		case(2):break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
		}
		}
	}
	f5(13);
	int flagarea = 1;
	while (flagarea) {
		f5(13);
		tttt(); cout << "请输入您的地区:\n";
		tttt(); cin >> area;
		clear_inputBuffer(stdin);
		f5(13);
		tttt(); cout << "您确定是这个地区吗：" << area << "\n";
		tttt(); cout << "1.确定 " << "2.重新输入" << "\n";
		int opt;
		tttt(); cin >> opt;
		clear_inputBuffer(stdin);
		switch (opt) {
		case(1):flagarea = 0; break;
		case(2):break;
		default: {
			f5(13);
			tttt(); cout << "因为无效的输入，默认为您需要重新输入\n";
			any_continue(5);
		}
		}
	}
	time_t t;
	t = time(NULL);
	char* time;
	time = ctime(&t);
	applyTime = time;
	friendsNum = 0;
	groupsNum = 0;
	tempGNum = 0;
	flag = 0;
	f5(8);
	tttt(); cout << "微博注册成功" << endl;
	tttt(); cout << "你的微博为:" << ID << endl;
	tttt(); cout << "你的微博昵称为:" << name << endl;
	tttt(); cout << "你的微博密码为:" << passwd << endl;
	tttt(); cout << "你的注册时间为:" << applyTime;
	tttt(); cout << "请妥善保存帐号和密码" << endl;
	string WeiBo = "WeiBo\\" + ID;
	CreateDirectory(WeiBo.c_str(), NULL);//每个QQ创建一个文件夹
	any_continue(5);
}

WeiBo_Lyc::WeiBo_Lyc(string wbid, string wbname, string wbpw, string wbbir, string wbsex, string wbarea, string wbappTime)
{
	ID = wbid;
	passwd = wbpw;
	name = wbname;
	birthday = wbbir;
	applyTime = wbappTime;
	sex = wbsex;
	area = wbarea;
	friendsNum = 0;
	groupsNum = 0;
	tempGNum = 0;
	flag = 0;
}

WeiBo_Lyc::~WeiBo_Lyc()
{

	for (int i = 0; i < friends.size(); i++) {
		delete friends[i];
	}
	for (int i = 0; i < groups.size(); i++) {
		delete groups[i];
	}
}

vector<Friend_Lyc*>& WeiBo_Lyc::return_friends()
{
	return friends;
}

vector<QQ_Group_Lyc*>& WeiBo_Lyc::return_groups()
{
	return groups;
}
//
//vector<Temp_Group_Lyc*>& WeiBo_Lyc::return_tempGroups()
//{
//	return tempGroups;
//}

int WeiBo_Lyc::return_tempGNum()
{
	return tempGNum;
}

string WeiBo_Lyc::return_linkQQ()
{
	return linkQQ;
}

string WeiBo_Lyc::return_linkWeChat()
{
	return linkWeChat;
}

void WeiBo_Lyc::get_friends()
{
	ifstream file;
	string WeiBo = ID;
	string filename = "WeiBo\\" + WeiBo + "\\" + WeiBo + "friends.txt";
	string filename1 = "WeiBos.txt";
	string nid;
	string nname;
	string nnote;
	string pw;
	string nbir;
	string nsex;
	string narea;
	string time;
	int nflag;

	// 清空当前的好友列表
	friends.clear();

	// 打开文件
	file.open(filename, ios::app);

	vector<string>tmpid;
	vector<string>tmpnote;
	vector<int>tmpflag;

	// 每次从文件中读取一个好友的信息，然后将其添加到列表中

	while (file >> nid >> nnote >> nflag) {
		tmpid.push_back(nid);
		tmpnote.push_back(nnote);
		tmpflag.push_back(nflag);
	}

	file.close();

	file.open(filename1, ios::app);
	while (file >> nid >> nname >> pw >> nbir >> nsex >> narea)
	{
		string empty;
		string time;
		getline(file, empty);
		getline(file, time);
		for (int i = 0; i < tmpid.size(); i++) {
			if (tmpid[i] == nid) {
				friends.push_back(new Friend_Lyc(tmpid[i], nname, tmpnote[i],
					nbir, nsex, narea, tmpflag[i]));
				//cout << friends.back()->return_flag() << endl;
				tmpid.erase(tmpid.begin() + i);
				tmpnote.erase(tmpnote.begin() + i);
				tmpflag.erase(tmpflag.begin() + i);
				break;
			}
		}
	}
	// 关闭文件
	file.close();

	// 更新好友数量
	friendsNum = friends.size();
}

void WeiBo_Lyc::get_groups()
{
	ifstream file;

	//对于每个用户，都有个群组文件，包含各群ID、群名称和加入信息

	string grouplist = "WeiBo\\" + ID + "\\" + ID + "groups.txt";
	file.open(grouplist, ios::app);
	string gID, gname;
	int gflag;
	groups.clear();
	groupsflag.clear();
	while (file >> gID >> gname >> gflag) {
		for (int i = 0; i < WeiBosystem.WeiBogroups.size(); i++) {
			if (WeiBosystem.WeiBogroups[i]->return_groupID() == gID) {
				groups.push_back(WeiBosystem.WeiBogroups[i]);
				groupsflag.push_back(gflag);
			}
		}
	}
	file.close();


	groupsNum = groups.size();
}

void WeiBo_Lyc::get_links()
{
	ifstream file;
	string tmp;
	string LQ = "";
	string LWC = "";
	string filename = "WeiBo\\" + ID + "\\" + ID + "links.txt";
	file.open(filename, ios::app);
	while (file >> tmp) {
		if (tmp == "QQ")file >> linkQQ;
		else if (tmp == "WeChat")file >> linkWeChat;
	}
	file.close();
}

Friend_Lyc::Friend_Lyc(string nid, string nname, string nnote, string nbir, string nsex, string narea, int nflag)
{
	ID = nid;
	name = nname;
	note = nnote;
	birthday = nbir;
	sex = nsex;
	area = narea;
	flag = nflag;
}


Friend_Lyc::Friend_Lyc(string nid, string nname, string nbir, string nsex, string narea, int nflag)
{
	ID = nid;
	name = nname;
	note = "未备注";
	birthday = nbir;
	sex = nsex;
	area = narea;
	flag = nflag;
}

string Friend_Lyc::return_ID()
{
	return ID;
}

string Friend_Lyc::return_name()
{
	return name;
}

string Friend_Lyc::return_note()
{
	return note;
}

string Friend_Lyc::return_birthday()
{
	return birthday;
}

string Friend_Lyc::return_sex()
{
	return sex;
}

string Friend_Lyc::return_area()
{
	return area;
}

int Friend_Lyc::return_flag()
{
	return flag;
}

void Friend_Lyc::change_flag(int n)
{
	flag = n;
}
//
Temp_Group_Lyc::Temp_Group_Lyc(string id, string tname)
{
	groupID = id;
	name = tname;
}

string Temp_Group_Lyc::return_groupID()
{
	return groupID;
}

string Temp_Group_Lyc::return_name()
{
	return name;
}

string Group_Lyc::return_groupID()
{
	return groupID;
}

string Group_Lyc::return_name()
{
	return name;
}

string Group_Lyc::return_masterID()
{
	return masterID;
}

vector<string>& Group_Lyc::retrun_members()
{
	return members;
}

QQ_Group_Lyc::QQ_Group_Lyc(string gid, string gname)
{
	groupID = gid;
	name = gname;
}

vector<string>& QQ_Group_Lyc::return_admins()
{
	return admins;
}
