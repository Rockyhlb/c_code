#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define null 0
#define len sizeof(struct page)
struct page
{
	int num;
	int tag;
	struct page* next;
};

struct page* create(int n)
{
	int count = 1;
	struct page* p1, *p2, *head;
	head = p2 = p1 = (struct page*)malloc(len);
	p1->tag = -1;
	p1->num = -1;
	while (count < n)
	{
		count++;
		p1 = (struct page*)malloc(len);
		p1->tag = -1;
		p1->num = -1;
		p2->next = p1;
		p2 = p1;
	}
	p2->next = null;
	return(head);
}
void FIFO(int* array, int n)
{
	int* p;

	struct page* cp, *dp, *head, *New;
	int count = 0;
	head = create(n);
	p = array;

	while (*p != -1)
	{
		cp = dp = head;
		for (; cp->num != *p && cp->next != null;)
			cp = cp->next;
		if (cp->num == *p)
			printf("! ");

		else
		{
			count++;
			cp = head;
			for (; cp->tag != -1 && cp->next != null;) cp = cp->next;
			if (cp->tag == -1)
			{
				cp->num = *p;
				cp->tag = 0;
				printf(" *");
			}
			else
			{
				New = (struct page*)malloc(len);
				New->num = *p;
				New->tag = 0;
				New->next = null;
				cp->next = New;
				head = head->next;
				printf("%d", dp->num);
				free(dp);
			}
		}
		p++;
	}
	printf("\nQueye Zongshu : %d\n", count);
}
int main()
{
	FILE* fp;
	char pt;
	char str[10];
	int i, j = 0;
	int page[50], space = 0;
	for (i = 0; i < 50; i++)
		page[i] = -1;
	fp = fopen("page.txt", "r+");
	if (fp == NULL)
	{
		printf("Can't open the file\n");
		exit(0);
	}
	i = 0;
	while ((pt = fgetc(fp)) != EOF)
	{
		if (pt >= '0' && pt <= '9')
		{
			str[i] = pt;
			i++;
			space = 0;
		}
		else
		{
			if (pt == ' ' || pt == '\n')
			{
				if (space == 1)
					break;
				else
				{
					str[i] = '\0';
					page[j] = atoi(str);
					if (pt == '\n')
						break;
					else
					{
						space = 1;
						j++;
						i = 0;
					}
				}
			}
		}
	}
	if (pt == EOF)
	{
		str[i] = '\0';
		page[j] = atoi(str);
	}
	i = 0;
	while (page[i] != -1)
	{
		printf(" %d", page[i]);
		i++;
	}
	fclose(fp);
	printf("\n");

	printf("! : mean no moved \n * : mean have free space \n\n");
	printf("FIFO");
	FIFO(page, 3);
}