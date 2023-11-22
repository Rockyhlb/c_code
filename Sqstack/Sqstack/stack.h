#pragma once
#include<stdio.h>
#include<stdlib.h>
#define STACK_SIZE 100
#define TRUE 1
#define ERROR 0

typedef char SElemType;
typedef int Status;

typedef struct
{
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;

Status InitStack(SqStack* S);
Status Push(SqStack* S, SElemType e);
Status Pop(SqStack* S, SElemType* e);
Status Pop(SqStack* S, SElemType* e);