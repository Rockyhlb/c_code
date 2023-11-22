#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100

typedef float Num;
typedef struct
{
	Num data[MAX];
	int top;
}StackNum;//������ջ

typedef struct
{
	char data[MAX];
	int top;
}StackChar;//�����ջ 

void InitNum(StackNum *p);//������ջ��ʼ��
void PushNum(StackNum *p, Num e);//������ѹջ
void PopNum(StackNum *p, Num *e);//��������ջ
Num GetNum(StackNum p);//ȡջ��Ԫ��

void InitChar(StackChar *p);//�����ջ��ʼ��
void PushChar(StackChar *p, char e);//�����ѹջ 
void PopChar(StackChar *p, char *e);//�������ջ 

void Fun(StackNum *p, char e);

void main()
{
	int i;
	Num temp;
	char str[MAX], ch;
	
	StackNum n1;
	StackChar c1;
	InitNum(&n1);
	InitChar(&c1);
	
	for (;;)
	{
		printf("��������׺���ʽ��");
		gets(str);
		
		for (i = 0; str[i] != '\0'; i++)
		{
			if (str[i] >= '0'&&str[i] <= '9')
			{
				temp = str[i] - '0';

				while (str[i + 1] != '\0')
				{
					if (str[i + 1] >= '0'&&str[i + 1] <= '9')
					{
						temp = temp * 10 + str[i + 1] - '0';
						i++;
					}
					else
						break;
				}
				PushNum(&n1, temp); 
			}
			else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')')
			{
				switch (str[i])
				{
				case '+':
					if (c1.data[c1.top - 1] != '+'&&c1.data[c1.top - 1] != '-'&&c1.data[c1.top - 1] != '*'&&c1.data[c1.top - 1] != '/')
					{
						PushChar(&c1, '+');
					}
					else
					{
						while (c1.top > 0 && c1.data[c1.top - 1] != '(')
						{
							PopChar(&c1, &ch);
							Fun(&n1, ch);
						}
						PushChar(&c1, '+');
					}
					; break;
				case '-':
					if (c1.data[c1.top - 1] != '+'&&c1.data[c1.top - 1] != '-'&&c1.data[c1.top - 1] != '*'&&c1.data[c1.top - 1] != '/')
					{
						PushChar(&c1, '-');
					}
					else
					{
						while (c1.top > 0 && c1.data[c1.top - 1] != '(')
						{
							PopChar(&c1, &ch);
							Fun(&n1, ch);

						}
						PushChar(&c1, '-');
					}
					; break;
				case '*':
					if (c1.data[c1.top - 1] != '*'&&c1.data[c1.top - 1] != '/')
					{
						PushChar(&c1, '*');
					}
					else
					{
						while (c1.top > 0 && c1.data[c1.top - 1] != '(')
						{
							PopChar(&c1, &ch);
							Fun(&n1, ch);

						}
						PushChar(&c1, '*');
					}
					; break;
				case '/':
					if (c1.data[c1.top - 1] != '*'&&c1.data[c1.top - 1] != '/')
					{
						PushChar(&c1, '/');
					}
					else
					{
						while (c1.top > 0 && c1.data[c1.top - 1] != '(')
						{
							PopChar(&c1, &ch);
							Fun(&n1, ch);

						}
						PushChar(&c1, '/');
					}
					; break;
				case '(':

					PushChar(&c1, '(');

					; break;
				case ')':
					while (c1.data[c1.top - 1] != '(')
					{
						PopChar(&c1, &ch);
						Fun(&n1, ch);
					}
					PopChar(&c1, &ch);
					; break;
				}
			}
		}
		while (c1.top > 0)
		{
			PopChar(&c1, &ch);
			Fun(&n1, ch);
		}
		printf("%s=%.2f", str, GetNum(n1));
		printf("\n");
		system("pause");
	}

}
void InitNum(StackNum *p)
{
	p->top = 0;
}
void InitChar(StackChar *p)
{
	p->top = 0;
}
void PushNum(StackNum *p, Num e)
{
	if (p->top == MAX)
		printf("������ջ����\n");
	else
	{
		p->data[p->top] = e;
		p->top++;
	}
}
void PushChar(StackChar *p, char e)
{
	if (p->top == MAX)
		printf("�����ջ����\n");
	else
	{
		p->data[p->top] = e;
		p->top++;
	}
}
void PopNum(StackNum *p, Num *e)
{
	if (p->top == 0)
		printf("������ջ�գ�\n");
	else
	{
		p->top--;
		*e = p->data[p->top];
	}
}
void PopChar(StackChar *p, char *e)
{
	if (p->top == 0)
		printf("�����ջ�գ�\n");
	else
	{
		p->top--;
		*e = p->data[p->top];
	}
}
void Fun(StackNum *p, char e)
{
	Num temp1, temp2;
	PopNum(p, &temp2);
	PopNum(p, &temp1);
	switch (e)
	{
	case '+':
		PushNum(p, temp1 + temp2); 
		break;
	case '-':
		PushNum(p, temp1 - temp2); 
		break;
	case '*':
		PushNum(p, temp1*temp2); 
		break;
	case '/':
		PushNum(p, temp1 / temp2); 
		break;
	}
}
Num GetNum(StackNum p)
{
	return p.data[p.top - 1];
}
