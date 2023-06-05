#define _CRT_SECURE_NO_WARNINGS 1

#include <windows.h>
#include <time.h>
#include <string>
#include <iostream>
#include <assert.h>
using namespace std;
bool tools[5];		 //全局变量，用餐工具
CRITICAL_SECTION cs; //信号量, 在线程中使用，临界区

class Philosopher
{
private:
	int number;
	int status; // 标记当前哲学家的状态  --  0 表示正在等待(即处于饥饿状态),1 表示得到两支筷子正在吃饭,2 表示正在思考
public:
	Philosopher(int num = 0) : status(2), number(num) { }
	const int find()
	{
		return number;
	}
	const int getinfo()
	{
		return status;
	}
	void Change(); //状态改变函数
	void dead_lock();
};

void Philosopher::dead_lock()
{
	EnterCriticalSection(&cs); //进入临界区
	string s;
	if (status == 1)
	{
		tools[number % 5] = true;
		status = 2;
	}
	else if (status == 2)
	{
		status = 0;
	}
	else if (status == 0)
	{
		tools[number % 5] = false;
		tools[(number - 1) % 5] = false;
		status = 1;
	}
	LeaveCriticalSection(&cs);
}

void Philosopher::Change()
{
	EnterCriticalSection(&cs);	//进入临界区
	if (status == 1)			//正在进餐
	{
		tools[number % 5] = true; //放下左手工具
		tools[(number - 1) % 5] = true; //放下右手工具
		status = 2;						//改变状态为思考
	}
	else if (status == 2)		 //思考中
	{
		status = 0;				//改变状态为等待
	}
	else if (status == 0)		//等待中
	{
		if (tools[number % 5] && tools[(number - 1) % 5]) //左右手两边工具均为空闲状态
		{
		tools[number % 5] = false; //拿起左手工具
		tools[(number - 1) % 5] = false; //拿起右手工具
		status = 1;
		}
	}
	LeaveCriticalSection(&cs);
}
string print(Philosopher *pA)
{
	//pA->Change();
	int i = pA->getinfo();
	string str;
	if (i == 0)
		str = "等待 ";
	else if (i == 1)
		str = "就餐 ";
	else str = "思考 ";
	return str;
}
string toolstatus(bool a)
{
	string state;
	if (a == true)
		state = "闲 ";
	if (a == false)
		state = "用 ";
	return state;
}
int main()
{
	char con = 'y'; //判断是否继续
   // con = 'n';
	for (int i = 0; i < 5; i++)
		tools[i] = true; //筷子都未使用，初始化
	Philosopher P1(1), P2(2), P3(3), P4(4), P5(5);
	InitializeCriticalSection(&cs); //初始化初始化临界区
	cout << "-----------------------状态说明示意图：	---------------------- - "<<endl;
	cout << "" << "哲学家 1 号的状态" << " " << endl;
	cout << " 筷子 0 的状态" << " " << "筷子 1 的状态" << endl;
	cout << " \n哲学家 5 号的状态" << " " << "哲学家 2 号的状态" << endl;
	cout << " 筷子 4 的状态" << " " << "筷子 2 的状态" << endl;
	cout << " \n哲学家 4 号的状态" << " " << "哲学家 3 号的状态" << endl;
	cout << " " << "筷子 3 的状态" << endl;
	//cout<<" "<<"哲学家 3 号的状态"<<" "<<endl
	cout << "筷子的状态，用表示使用中，闲表示空闲中。" << endl;
	cout << "--------------------------------------------------------------"
		<< endl;
	//cout<<"哲学家们开始生活："<<endl;
	//cout<<"当前状态：";
	cout << endl;
	//cin>>con;
	while (con == 'y')
	{
		P1.Change(); P2.Change(); P3.Change(); P4.Change();
		P5.Change();
		cout << "当前状态为：" << endl;
		cout << " 哲学家" << P1.find() << print(&P1) << " " << endl;
		cout << " " << toolstatus(tools[0]) << ""<<toolstatus(tools[1])<<endl;
			cout << " 哲学家" << P5.find() << print(&P5) << " 哲学家"<<P2.find()<<print(&P2)<<endl;
			cout << " " << toolstatus(tools[4]) << ""<<toolstatus(tools[2])<<endl;
			cout << " 哲学家" << P4.find() << print(&P4) << " 哲学家"<<P3.find()<<print(&P3)<<endl;
			cout << " " << toolstatus(tools[3]) << endl;
		cout << "--------------------------" << endl;
		cout << "若要继续下一状态，输入 y；输入 n 进入死锁；输入其他，结束程序：";
			cin >> con;
		Sleep(20);
	}
	while (con == 'n')
	{
		P1.dead_lock();
		P2.dead_lock(); P3.dead_lock(); P4.dead_lock(); P5.dead_lock();
		cout << "死锁情况" << endl;
		cout << " " << P1.find() << print(&P1) << " " << endl;
		cout << " " << toolstatus(tools[0]) << ""<<toolstatus(tools[1])<<endl;
			cout << " " << P5.find() << print(&P5) << ""<<P2.find()<<print(&P2)<<endl;
			cout << " " << toolstatus(tools[4]) << ""<<toolstatus(tools[2])<<endl;
			cout << " " << P4.find() << print(&P4) << ""<<P3.find()<<print(&P3)<<endl;
			cout << " " << toolstatus(tools[3]) << endl;
		cout << "--------------------------" << endl;
		cout << "输入 n 继续；输入其他，结束程序：";
		cin >> con;
		Sleep(20);
	}
	DeleteCriticalSection(&cs); //退出资源区
	return 0;
}