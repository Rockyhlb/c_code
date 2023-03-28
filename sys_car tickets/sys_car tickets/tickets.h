#pragma once

#include"stdio.h"
#include"conio.h"
#include"string.h"
#include"time.h"
#include"stdlib.h"

#define STR_LEN  30
#define MAX 50

//������Ϣ 
typedef struct train 
{					
	char stationId[STR_LEN];		//�г���
	char from[STR_LEN]; //��Ʊ���
	char to[STR_LEN];	//��Ʊ�յ�
	char stime[16];		//����ʱ��
	char rtime[16];		//����ʱ��
	int money;		//Ʊ��
	int ticket;		//Ʊ��
}Train;

//��������ķ�ʽ�����г��ڵ�
typedef struct node   
{
	Train data;
	struct node *next;
}Node, *link;

void menu();	  //�ܲ˵���ʾ
//¼��ģ��  
void insert_Info(link l);				//�ļ���Ϣ¼�� 
void load(link l);				//�ļ���������
void except_id(Node *p, link l);//�г���¼�����

//��ѯģ��  
void search(link l);		//�г���Ϣ���Ҳ˵� 
void search_t_to(link l);	//���յ�վ��ѯ 
void search_t_from(link l);	//������վ��ѯ
void all_show(link l);		//��ѯȫ����Ϣ 
void Info(Node *p);		//�г���Ϣ�����ʽ


// �޸�ģ�� 
void updateInfo(link l);//�г���Ϣ�޸� 
void except_update_id(Node *p);//�޸��г��Ų��� 
void save(link l);//�ļ�����

//ɾ��ģ��
void deleteInfo(link l);