#define _CRT_SECURE_NO_WARNINGS
#include "SList.h"

SLTNode *CreateNode(SLTDataType x)  //申请结点
{
	SLTNode *newnode = (SLTNode*)malloc(sizeof(SLTNode));
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}

void SListPrint(SLTNode *phead)
{
	SLTNode *cur = phead;
	while (cur!=NULL)
	{
		printf("%d->",cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

void SListPushBack(SLTNode **pphead, SLTDataType x)
{
	SLTNode *newnode = CreateNode(x);
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		SLTNode *tail = *pphead;
		while (tail->next!=NULL)
		{
			tail = tail->data;
		}
		tail->next = newnode;
	}
}

void SListPushFront(SLTNode **pphead, SLTDataType x)
{
	SLTNode *newnode = CreateNode(x);

	newnode->next = *pphead;
	*pphead = newnode;
}

void SListPopBack(SLTNode **pphead)
{
	if (*pphead == NULL)
	{
		return;
	}
	else if ((*pphead)->next = NULL)
	{
		free(pphead);
		pphead = NULL;
	}
	else
	{
		SLTNode *tail = *pphead;
		SLTNode *prev = NULL;
		while (tail->next!=NULL)
		{
			prev = tail;
			tail = tail->next;
		}
		free(tail);
		tail = NULL;
		prev->next = NULL;
	}
}

void SListPopFrount(SLTNode **pphead)
{
	if (*pphead == NULL)
	{
		return;
	}
	else
	{
		SLTNode *p = (*pphead)->next;
		free(*pphead);
		*pphead = NULL;
		*pphead = p;
	}
}

SLTNode *SListFind(SLTNode **pphead, SLTDataType x)
{
	SLTNode *find = *pphead;
	while (find)
	{
		if (find->data == x)
		{
			return find;
		}
		find=find->next;
	}
}

void SListModify(SLTNode **pphead, SLTDataType x)
{
	SLTNode *findData = SListFind(pphead, x);
	if (findData == NULL)
	{
		printf("无此数据！");
	}
	else
	{
		int number = 0;
		printf("请你输入你修改的值：\n");
		scanf("%d", &number);

		findData->data = number;
	}
}

void SListInsert(SLTNode **pphead, SLTNode *pos, SLTDataType x)
{
	if (*pphead == pos)
	{
		SListPushBack(pphead, x);
	}
	else
	{
		SLTNode *newnode = CreateNode(x);
		SLTNode * prev = *pphead;
		while (prev->next!= pos)
		{
			prev = prev->next;
		}
		prev->next = newnode;
		newnode->next = pos;
	}
}

void SListErase(SLTNode **pphead, SLTNode *pos)
{
	if (*pphead == pos)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		SLTNode *prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;
		}
		prev->next = pos->next;
		free(pos);
	}
}