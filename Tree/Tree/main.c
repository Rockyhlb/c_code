#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"

void CreatBiTree(BiTree* T)
{
	char ch;
	ch = getchar();
	if (ch == '#')
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTree*)malloc(sizeof(BiTNode));
		if (!T)
		{
			exit(FALSE);
		}
		(*T)->data = ch;
		CreatBiTree(&(*T)->lchild);
		CreatBiTree(&(*T)->rchild);
	}
}

int NodeCount(BiTree T)
{
	if (T==NULL)
	{
		return 0;
	}
	else
	{
		return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
	}
}

int LeafCount(BiTree T)
{
	int count = 0;
	if (T == NULL)
	{
		return 0;
	}
	else
	{
		if (T->lchild==NULL && T->rchild==NULL)
		{
			count++;
		}
		else
		{
			count += LeafCount(T->lchild);
			count += LeafCount(T->rchild);
		}
	}
	return count;
}

void PreOrderTraverse(BiTree T)
{
	if (!T)
	{
		return;
	}
	else
	{
		printf("%c", T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse(BiTree T)
{
	if (!T)
	{
		return;
	}
	else
	{
		InOrderTraverse(T->lchild);
		printf("%c", T->data);
		InOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(BiTree T)
{
	if (!T)
	{
		return;
	}
	else
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c", T->data);
	}
}

int main()
{
	printf("请按照二叉树顺序进行输入,‘#’结束：");
	BiTree t;
	CreatBiTree(&t);
	printf("二叉树建立成功！\n\n");

	printf("前序遍历：");
	PreOrderTraverse(t);
	printf("\n");

	printf("中序遍历：");
	InOrderTraverse(t);
	printf("\n");

	printf("后序遍历：");
	PostOrderTraverse(t);
	printf("\n");

	printf("节点数为：%d\n", NodeCount(t));
	printf("叶子数为：%d", LeafCount(t));
	return 0;
}