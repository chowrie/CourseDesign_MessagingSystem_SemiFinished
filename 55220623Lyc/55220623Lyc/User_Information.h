#pragma once
#include <string>
#include <vector>
#include"system.h"
using namespace std;



class Friend_Lyc;
class Group_Lyc;
class QQ_Group_Lyc;
class Temp_Group_Lyc;

//对于每个平台，都有一个群组文件夹和群组列表，文件内容是是每个群一个的文件夹，包含各群详细信息和临时讨论组
// 群成员、管理员、ID、昵称
//这里假定群组文件夹都已存在
//QQ\\grouplist.txt 含群ID
//QQ\\"groupID"\\member.txt 含所有群成员
//QQ\\"groupID"\\admin.txt 含所有管理员
//QQ\\"groupID"\\tempgroup.txt 含所有临时讨论组
//QQ\\"groupID"\\"tempgroupID"\\member.txt


class Group_Lyc {
protected:
	string groupID;
	string name;
	string masterID;
	vector<string>members;
public:
	virtual string return_groupID();
	virtual string return_name();
	virtual string return_masterID();
	virtual vector<string>& retrun_members();
};

class QQ_Group_Lyc :public Group_Lyc {
protected:
	vector<string>admins;
	vector<Temp_Group_Lyc*>tempGroups;
	vector<string>tempmem;
public:
	friend class QQ_Lyc;
	friend class Core_QQ_Lyc;
	friend class WeChat_Lyc;
	friend class Core_WeChat_Lyc;
	friend class WeiBo_Lyc;
	friend class Core_WeiBo_Lyc;
	friend class Temp_Group_Lyc;
	QQ_Group_Lyc(string gid, string gname);
	friend class QQ_Lyc;
	vector<string>& return_admins();
};


class Temp_Group_Lyc {
protected:
	string groupID;
	string name;
	vector<string>member;
	QQ_Group_Lyc* dad;
public:
	friend class QQ_Group_Lyc;
	friend class Core_QQ_Lyc;
	friend class QQ_Lyc;
	friend class Core_WeChat_Lyc;
	friend class WeChat_Lyc;
	friend class Core_WeiBo_Lyc;
	friend class WeiBo_Lyc;
	Temp_Group_Lyc(string id, string tname);
	virtual string return_groupID();
	virtual string return_name();
};

class Tencent_Lyc {
protected:
	string ID;
	string passwd;
	string name;
	string birthday;
	string applyTime;
	string sex;
	string area;
	int friendsNum;
	int groupsNum;
	struct sexType {
		string SexFlag;
	}man{ "男" }, woman{ "女" };
public:
	int flag;
	virtual string return_ID();
	virtual string return_Passwd();
	virtual string return_name();
	virtual string return_birthday();
	virtual string return_applyTime();
	virtual string return_sex();
	virtual string return_area();
	virtual int return_friendsNum();
	virtual int return_groupsNum();
	virtual void change_passwd(string newpw);
	virtual void change_name(string newname);
	virtual void change_bir(string newname);
	virtual void change_sex(int n);
	virtual void change_area(string newarea);
	virtual void change_groupsNum(int num);
	virtual void change_friendsNum(int num);
	virtual int return_flag();
	virtual void get_friends() = 0;
	virtual void get_groups() = 0;
	virtual void get_links() = 0;
};

class QQ_Lyc :public Tencent_Lyc {
protected:
	string linkWeChat;
	string linkWeiBo;
	int tempGNum;
	vector<Friend_Lyc*>friends;
	vector<QQ_Group_Lyc*>groups;
	//vector<QQ_Group_Lyc*>tempGroups;
	vector<int>groupsflag;//-1：申请中；0：已申请；-2：推荐入群；-3：-1+（-2）
	vector<int>tempgroupsflag;
public:
	friend DWORD WINAPI threadFuncRecv_QQ(LPVOID pram);

	//vector<Friend_Lyc*>friends;
	//vector<QQ_Group_Lyc*>groups;
	//vector<Temp_Group_Lyc*>tempGroups;
	friend class Friend_Lyc;
	friend class QQ_Group_Lyc;
	friend class WeChat_Lyc;
	friend class WeiBo_Lyc;
	friend class Temp_Group_Lyc;
	friend class Core_WeChat_Lyc;
	friend class Core_QQ_Lyc;
	friend class Core_WeiBo_Lyc;
	QQ_Lyc(string id = "-1");
	QQ_Lyc(string qid, string qname, string qpw, string qbir, string qsex, string qarea, string qappTime);
	~QQ_Lyc();
	vector<QQ_Group_Lyc*>& return_groups();
	int return_tempGNum();
	string return_linkWeChat();
	string return_linkWeiBo();
	void get_friends();
	void get_groups();
	void get_links();
};

class WeiBo_Lyc :public Tencent_Lyc {
protected:
	int tempGNum;
	string linkWeChat;
	string linkQQ;
	vector<Friend_Lyc*>friends;
	vector<QQ_Group_Lyc*>groups;
	//vector<QQ_Group_Lyc*>tempGroups;
	vector<int>groupsflag;
	vector<int>tempgroupsflag;
public:
	friend DWORD WINAPI threadFuncRecv_WeiBo(LPVOID pram);

	friend class Friend_Lyc;
	friend class QQ_Group_Lyc;
	friend class Temp_Group_Lyc;
	friend class WeChat_Lyc;
	friend class QQ_Lyc;
	friend class Core_WeChat_Lyc;
	friend class Core_QQ_Lyc;
	friend class Core_WeiBo_Lyc;
	WeiBo_Lyc(string id = "-1");
	WeiBo_Lyc(string wbid, string wbname, string wbpw, string wbbir, string wbsex, string wbarea, string wbappTime);
	~WeiBo_Lyc();
	vector<Friend_Lyc*>& return_friends();
	vector<QQ_Group_Lyc*>& return_groups();
	//vector<QQ_Group_Lyc*>& return_tempGroups();
	int return_tempGNum();
	string return_linkQQ();
	string return_linkWeChat();
	void get_friends();
	void get_groups();
	void get_links();
};

class WeChat_Lyc :public Tencent_Lyc {
protected:
	string linkWeiBo;
	string linkQQ;
	vector<Friend_Lyc*>friends;
	vector<QQ_Group_Lyc*>groups;
	vector<int>groupsflag;
public:
	friend DWORD WINAPI threadFuncRecv_WeChat(LPVOID pram);

	friend class Friend_Lyc;
	friend class QQ_Group_Lyc;
	friend class Temp_Group_Lyc;
	friend class Core_WeChat_Lyc;
	friend class QQ_Lyc;
	friend class WeiBo_Lyc;
	friend class Core_QQ_Lyc;
	friend class Core_WeChat_Lyc;
	friend class Core_WeiBo_Lyc;
	WeChat_Lyc(string id = "-1");
	WeChat_Lyc(string wcid, string wcname, string wcpw, string wcbir, string wcsex, string wcarea, string wcappTime);
	~WeChat_Lyc();
	vector<Friend_Lyc*>& return_friends();
	vector<QQ_Group_Lyc*>& return_groups();
	string return_linkQQ();
	string return_linkWeiBo();
	void get_friends();
	void get_groups();
	void get_links();
};

class Friend_Lyc {
protected:
	string ID;
	string name;
	string note;
	string birthday;
	string sex;
	string area;
	struct sexType {
		string SexFlag;
	}man{ "男" }, woman{ "女" };
	int flag;
public:
	friend class Wechat_Lyc;
	friend class QQt_Lyc;
	friend class WeiBo_Lyc;
	friend class Core_WeChat_Lyc;
	friend class Core_WeiBo_Lyc;
	friend class Core_QQ_Lyc;
	Friend_Lyc(string nid, string nname, string nnote,
		string nbir, string nsex, string narea, int nflag);
	Friend_Lyc(string nid, string nname,
		string nbir, string nsex, string narea, int nflag);
	string return_ID();
	string return_name();
	string return_note();
	string return_birthday();
	string return_sex();
	string return_area();
	int return_flag();//-1被申请中，0申请中，1好友
	void change_flag(int n);
	friend class QQ_Lyc;
	friend class WeChat_Lyc;
	friend class WeiBo_Lyc;
};
