#include <stdio.h>

void swap(int **p,int **q)
{
	// 解引用
	int *tmp = *p;
	*p = *q;
	*q = tmp;
}

int main()
{
	int *p = "aaaaa";
	int *q = "bbbbb";

	printf("%s%s\n", p, q);

	swap(&p,&q);

	printf("%s%s\n", p, q);
}
