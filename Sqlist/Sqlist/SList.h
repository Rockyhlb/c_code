#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef  int SLTDataType;
typedef struct SListNode
{
	SLTDataType data;
	struct SLIstNode *next;
}SLTNode;

SLTNode *CreateNode(SLTDataType);
void SListPrint(SLTNode *phead);
void SListPushBack(SLTNode **pphead, SLTDataType x);
void SListPushFront(SLTNode **pphead, SLTDataType x);

void SListPopBack(SLTNode **pphead);
void SListPopFrount(SLTNode **pphead);

SLTNode *SListFind(SLTNode **pphead, SLTDataType x);

void SListModify(SLTNode **pphead, SLTDataType x);
void SListInsert(SLTNode **pphead, SLTNode *pos, SLTDataType x);
void SListErase(SLTNode **pphead, SLTNode *pos);
