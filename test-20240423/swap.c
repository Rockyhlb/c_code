#include <stdio.h>

void swap(char **p,char **q)
{
	// 解引用
	char *tmp = *p;
	*p = *q;
	*q = tmp;
}

int main()
{
	char *p = "aaaaa";
	char *q = "bbbbb";

	printf("%s%s\n", p, q);

	swap(&p,&q);

	printf("%s%s\n", p, q);
}
