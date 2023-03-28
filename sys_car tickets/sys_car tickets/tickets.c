#define _CRT_SECURE_NO_WARNINGS 1

#include "tickets.h"

//售票信息录入
void insert_Info(link l) 
{
	Node *p, *q;
	while (1)
	{
		q = l;
		while (q->next != NULL)
		{
			q = q->next;
		}
		p = (Node *)malloc(sizeof(Node));
		printf("\n\t---------------------------------列车信息录入---------------------------------\n");
		if (!p)//p=NULL
		{
			printf("录入出错！");
			exit(0); //退出函数 
		}
		printf("\n\t1.请输入列车号：");
		scanf("%s", &p->data.stationId);
		except_id(p, l);
		printf("\t2.请输入起点站名称：");
		scanf("%s", &p->data.from);
		printf("\t3.请输入终点站名称：");
		scanf("%s", &p->data.to);
		printf("\t4.请输入列车出发时间(时分格式为00:00)：");
		scanf("%s", &p->data.stime);
		printf("\t5.请输入列车到达时间(时分格式为00:00)：");
		scanf("%s", &p->data.rtime);
		printf("\t6.请输入票价：");
		scanf("%d", &p->data.money);
		printf("\t7.请输入票数：");
		scanf("%d", &p->data.ticket);
		p->next = NULL;
		q->next = p;
		q = p;
		printf("\t录入成功！\t");
		break;
	}
}

//录入列车号查重
void except_id(Node *p, link l) 
{
	Node *q;
	q = l;
	while (q != NULL)
	{
		if (strcmp(p->data.stationId,q->data.stationId) == 0)
		{
			printf("\t当前列车班次已存在,请重新输入：");
			scanf("%s", &p->data.stationId);
			except_id(p, l);
		}
		else
		{
			q = q->next;
		}
	}
}

//文件数据导入
void load(link l)
{
	Node *p, *r;
	FILE *fp;
	l->next = NULL;
	r = l;
	if ((fp = fopen("train", "rb")) == NULL)
	{
		printf("\n\t********文件打开失败！*********");
	}
	else
	{
		printf("\n\t========文件数据导入成功！=========");
		while (!feof(fp))
		{
			p = (Node *)malloc(sizeof(Node));
			if (fread(p, sizeof(Node), 1, fp) != 1)
				break;
			else
			{
				p->next = NULL;
				r->next = p;
				r = p;
			}
		}
	}
}
//查询 
//按终点站查询 
void search_t_to(link l)
{
	Node *p;
	char preach[STR_LEN];
	p = l->next;
	int count = 0;
	printf("请输入您需要查找的列车信息的终点站：");
	scanf("%s", &preach);
	printf("\n\t\t\t\t******-----查询结果-----******\n");
	printf("\t列车号\t发车站\t到达站\t发车时间\t到达时间\t票价(元)\t票数（张）\n");
	while (p)
	{
		if (strcmp(p->data.to, preach) == 0)
		{
			Info(p);
			count++;
		}
		if (p->next == NULL)
			break;
		else
			p = p->next;
	}
	if (!p || count == 0)
	{
		printf("\t\t\t.......未找到该列车信息!");
	}
}

//按发车站查询
void search_t_from(link l) 
{
	Node *p;
	char pstart[STR_LEN];
	p = l;
	int count = 0;
	printf("请输入您需要查找的列车信息的始发站：");
	scanf("%s", &pstart);
	printf("\n\t\t\t\t******-----查询结果-----******\n");
	printf("\t列车号\t发车站\t到达站\t发车时间\t到达时间\t票价(元)\t票数（张）\n");
	while (p)
	{
		if (strcmp(p->data.from, pstart) == 0)
		{
			Info(p);
			count++;
			if (p->next == NULL)
				break;
			else
				p = p->next;
		}
		if (p->next != NULL)
			p = p->next;
		else
			break;
	}
	if (p == NULL || count == 0)
	{
		printf("\t\t\t.......未找到该列车信息!");
	}
}

//列车信息查找
void search(link l) 
{
	int num_cf;
	printf("\n\t---------------------------------列车信息查询---------------------------------\n");
	printf("\t1.按始发站查询\n\t2.按终点站查询\n\t3.查询所有列车信息\n\n");
	printf("\t请输入您的查询方式：");
	scanf("%d", &num_cf);
	printf("\n\t---------------------------------————————-----------------------------\n");
	
	if (num_cf == 1)
		search_t_from(l);
	else if (num_cf == 2)
		search_t_to(l);
	else if (num_cf == 3)
		all_show(l);
	else
		printf("\t\t输入错误！！");
}

//查询全部售票信息
void all_show(link l)
{
	Node *p;
	p = l->next;
	printf("\n\t\t\t\t******-----查询结果-----******\n");
	printf("\t列车号\t发车站\t到达站\t发车时间\t到达时间\t票价(元)\t票数（张）\n");
	if (p == NULL)
	{
		printf("\t\t\t.......未查询到任何列车信息！");
	}
	while (p != NULL)
	{
		Info(p);
		p = p->next;
	}
}

//列车信息输出格式 
void Info(Node *p)
{
	printf("\t%5s", p->data.stationId);
	printf("%8s", p->data.from);
	printf("%8s", p->data.to);
	printf("%10s", p->data.stime);
	printf("%15s", p->data.rtime);
	printf("%15d", p->data.money);
	printf("%15d\n", p->data.ticket);
}

//列车信息修改 
void updateInfo(link l)
{
	char num[STR_LEN];
	int n;
	Node *p;
	p = l;
	if (p == NULL)
	{
		printf("\t**暂时没有可以修改的列车信息**\n");

	}
	else
	{
		printf("请输入需要修改列车信息的列车号：");
		scanf("%s", &num);
		while (strcmp(p->data.stationId , num) != 0)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("找不到该列车信息");
				break;
			}
		}
		if (p != NULL)
		{
			printf("\n\t---------------------------------列车信息修改---------------------------------\n");
			printf("\t1.列车号\n\t2.起始站\n\t3.终点站\n\t4.出发时间\n\t5.到达时间\n\t6.票价\n\t7.票数\n");
			printf("\t---------------------------------——————---------------------------------\n");
			printf("\t请输入您要修改的信息编号：");
			scanf("%d", &n);
			switch (n)
			{
			case 1:
				printf("\t请输入变更后的列车号:");
				scanf("%s", &p->data.stationId);
				except_update_id(p);
				break;
			case 2:
				printf("\t请输入变更后的起始站:");
				scanf("%s", &p->data.from);
				break;
			case 3:
				printf("\t请输入变更后的终点站:");
				scanf("%s", &p->data.to);
				break;
			case 4:
				printf("\t请输入变更后的出发时间(时分格式为00:00)：");
				scanf("%s", &p->data.stime);
				break;
			case 5:
				printf("\t请输入变更后的到达时间(时分格式为00:00)：");
				scanf("%s", &p->data.rtime);
				break;
			case 6:
				printf("\t请输入变更后的票价：");
				scanf("%d", &p->data.money);
				break;
			case 7:
				printf("\t请输入变更后的票数：");
				scanf("%d", &p->data.ticket);
				break;
			default:
				printf("\t输入错误！");
				system("pause");
			}
			if (n >= 1 && n <= 7)
			{
				printf("\t**修改成功**");
			}
		}
	}
}

//修改列车号查重
void except_update_id(Node *p)
{
	Node *q, *m;
	q = p->next;
	while (q != NULL)
	{
		if (strcmp(p->data.stationId,q->data.stationId) == 0)
		{
			printf("\t当前列车班次已存在,请重新输入：");
			scanf("%s", &p->data.stationId);
			except_update_id(p);
		}
		else
			q = q->next;
	}
}

//文件保存 
void save(link l)
{
	Node *p;
	FILE *fp;
	p = l->next;
	if ((fp = fopen("train", "wb")) == NULL)
	{
		printf("\t********文件打开失败！*********");
		exit(0);
	}
	else
		printf("\t========文件保存成功！=========");
	while (p)
	{
		fwrite(p, sizeof(Node), 1, fp);
		p = p->next;
	}
	fclose(fp);
}

void deleteInfo(link l)
{
	char stationId[STR_LEN];
	Node *p = l->next;
	Node *q = l;
	char choice[10];
	printf("\n\t\t\t\t******-----下面为可删除的车票-----******\n");
	printf("\t列车号\t发车站\t到达站\t发车时间\t到达时间\t票价(元)\t票数（张）\n");
	while (p != NULL)
	{
		Info(p);
		p = p->next;
	}

	printf("\t.....请选择要删除的列车号：");
	scanf("%s", &stationId);

	p = l->next;
	while (p != NULL)
	{
		if (strcmp(stationId, p->data.stationId) == 0)//查找要删除的节点
		{
			Info(p);
			printf("是否删除？（Y or F）：");
			scanf("%s", &choice);
			if (strcmp(choice ,"Y") == 0)
			{
				q->next = p->next;//将q的下一个节点和上一个节点连接起来
				free(p);//释放p
				break;
			}
			else if(strcmp(choice,"F") == 0)
			{
				printf("取消成功！\n");
				break;
			}
		}
		else
		{
			q = p;
			p = p->next;
		}
	}
	if (p == NULL)
	{
		printf("没有可删除的列车信息！\n");
	}
}