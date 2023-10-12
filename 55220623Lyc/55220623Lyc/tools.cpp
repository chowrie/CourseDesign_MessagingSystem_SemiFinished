#pragma warning(suppress : 4996)
#define EXAMPLE_MACRO_NAME
#define _CRT_SECURE_NO_WARNINGS
#include"tools.h"
#include<time.h>
#include<ctime>
#include<iostream>
#include <random>
#include <chrono>
#include<Windows.h>
#include <conio.h>
using namespace std;
int generate_ID() {
	int lower = 100000;
	int upper = 999999;

	// 使用高精度时钟作为种子
	unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();

	// 创建一个随机数生成器
	mt19937 generator(seed);

	// 创建一个在lower和upper之间均匀分布的分布器
	uniform_int_distribution<int> distribution(lower, upper);

	// 生成一个在lower和upper之间的随机数，并返回
	return distribution(generator);
}

void clear_inputBuffer(FILE* fp)
{
	do {} while (fgetc(fp) != '\n' && !feof(fp));
}

void any_continue()
{
	f5(13);
	tttt(6); cout << "按回车键继续";
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
	//getchar();
	//clear_inputBuffer(stdin);
}

void any_continue(int n)
{
	tttt(n); cout << "按回车键继续";
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
	//getchar();
	//clear_inputBuffer(stdin);
}

string bir_input()
{
	f5(13);
	tttt(); cout << "请输入您的生日，格式为：20041213:\n";
	int a[2][12] = { 31,28,31,30,31,30,31,31,30,31,30,31,31,29,31,30,31,30,31,31,30,31,30,31 };
	string temp;
	putt(temp);
	int flag = 0;
	int len = temp.size();
	while (1) {
		flag = 0;
		while (len != 8)
		{
			f5(13);
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
				f5(13);
				tttt(); cout << "请输入正确的日期形式：格式为：20041213:" << endl;
				flag = 1;
				putt(temp);
			}
		}
		else
		{
			if ((year > 9999 || year < 0) || (month > 12 || month < 1) || (day > a[0][month - 1] || day < 1))
			{
				f5(13);
				tttt(); cout << "请输入正确的日期形式：格式为：20041213:" << endl;
				flag = 1;
				putt(temp);
			}
		}
		if (!flag)
		{
			break;
		}
	}
	return temp;
}

int judge_input_menu(string str, int n)
{
	int select = 0;
	int flag;
	int len = str.size();
	if (len != 1 && len != 2)
	{
		f5(13);
		tttt(); cout << "您输入的格式有误\n";
		any_continue(5);
		return -1;
	}
	if (len == 1)
	{
		select = str[0] - '0';
		if (select<0 || select>n)
		{
			f5(13);
			tttt(); cout << "您输入的范围有误\n";
			any_continue(5);
			return -1;
		}
	}
	else if (len == 2)
	{
		select = 10 * (str[0] - '0') + str[1] - '0';
		if (select != 10 && select != 11)
		{
			f5(13);
			tttt(); cout << "您输入的范围有误\n";
			any_continue(5);
			return -1;
		}
	}
	return select;
}

void tttt()
{
	cout << "\t\t\t\t\t";
}

void tttt(int n)
{
	while (n--) {
		cout << "\t";
	}
}

void f5(int n)
{
	system("CLS");
	for (int i = 0; i < n; i++)cout << "\n";
}

void putt(string& s)
{
	while (1) {
		tttt();
		if (cin.peek() == '\n') {
			clear_inputBuffer(stdin);
			cout << "\033[F";
		}
		else {
			cin >> s;
			clear_inputBuffer(stdin);
			break;
		}
	}
}

void putt(int& s)
{
	while (1) {
		tttt();
		if (cin.peek() == '\n') {
			clear_inputBuffer(stdin);
			cout << "\033[F";
		}
		else {
			cin >> s;
			clear_inputBuffer(stdin);
			break;
		}
	}
}
