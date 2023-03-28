#pragma once

#include"stdio.h"
#include"conio.h"
#include"string.h"
#include"time.h"
#include"stdlib.h"

#define STR_LEN  30
#define MAX 50

//车辆信息 
typedef struct train 
{					
	char stationId[STR_LEN];		//列车号
	char from[STR_LEN]; //车票起点
	char to[STR_LEN];	//车票终点
	char stime[16];		//出发时间
	char rtime[16];		//到达时间
	int money;		//票价
	int ticket;		//票数
}Train;

//采用链表的方式定义列车节点
typedef struct node   
{
	Train data;
	struct node *next;
}Node, *link;

void menu();	  //总菜单显示
//录入模块  
void insert_Info(link l);				//文件信息录入 
void load(link l);				//文件数据载入
void except_id(Node *p, link l);//列车号录入查重

//查询模块  
void search(link l);		//列车信息查找菜单 
void search_t_to(link l);	//按终点站查询 
void search_t_from(link l);	//按发车站查询
void all_show(link l);		//查询全部信息 
void Info(Node *p);		//列车信息输出格式


// 修改模块 
void updateInfo(link l);//列车信息修改 
void except_update_id(Node *p);//修改列车号查重 
void save(link l);//文件保存

//删除模块
void deleteInfo(link l);