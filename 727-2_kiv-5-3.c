#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


struct node
{
	int value;
	struct node* left;
	struct node* right;
	struct node* parent;
};

struct tree
{
	int number;
	struct node* base;
};

void init(struct tree* t)
{
	t->base = NULL;
	t->number = 0;
}

int insert(struct tree* t, int v)
{
	int cycle = 1;
	struct node* newNode;
	struct node* presentNode;

	if (malloc(sizeof(struct node)) == NULL)
	{
		return 2;
	}

	newNode = (struct node*)malloc(sizeof(struct node));

	newNode->value = v;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	if (t->base == NULL)
	{
		t->base = newNode;
		t->number = 1;
		return 0;
	}

	presentNode = t->base;
	while (cycle == 1)
	{
		if (newNode->value == presentNode->value)
		{
			return 1;
		}
		if (newNode->value < presentNode->value)
		{
			if (presentNode->left != NULL)
			{
				presentNode = presentNode->left;
			}
			else
			{
				newNode->parent = presentNode;
				presentNode->left = newNode;
				return 0;
			}
		}
		else
		{
			if (presentNode->right != NULL)
			{
				presentNode = presentNode->right;
			}
			else
			{
				newNode->parent = presentNode;
				presentNode->right = newNode;
				return 0;
			}
		}
	}
	return 0;
}

void printTree(struct node* b)
{
	if (b->left != NULL)
	{
		printTree(b->left);
	}
	if (b->right != NULL)
	{
		printTree(b->right);
	}
	if (b->parent != NULL)
	{
		printf("%d ", b->value);
	}
	else
	{
		printf("%d\n", b->value);
	}
}


int main()
{
	struct tree x;
	int v;

	init(&x);

	for (int i = 0; i < 7; i++)
	{
		scanf("%d", &v);
		insert(&x, v);
	}

	printTree(x.base);

	return 0;
}
