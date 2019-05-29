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

struct link
{
	int value;
	struct link *next;
};

struct list
{
	struct link *head;
	struct link *tail;
};

void initList(struct list* l)
{
	l->head = NULL;
	l->tail = NULL;
}

void clearList(struct list* l)
{
	struct link* l1;
	struct link* l2;
	l1 = l->head;
	while (l1->next != NULL)
	{
		l2 = l1;
		l1 = l1->next;
		free(l2);
	}
	free(l1);
	initList(l);
}

int push_back(struct list* l, int val)
{
	struct link* newLink;
	newLink = (struct link*)malloc(sizeof(struct link));
	newLink->value = val;
	newLink->next = NULL;
	if (l->head == NULL)
	{
		l->head = newLink;
	}
	else
	{
		if (l->head->next == NULL)
		{
			l->head->next = newLink;
		}
		else
		{
			l->tail->next = newLink;
		}
	}
	l->tail = newLink;
	return 0;
}

int isEmpty(struct list* l)
{
	if (l->head == NULL) return 0;
	else return 1;
}

void printList(struct list* l)
{
	if (isEmpty(l) == 1)
	{
		struct link* tmp;
		tmp = l->head;
		while (tmp->next != NULL)
		{
			if (tmp->value != -1)
			{
				printf("%d ", tmp->value);
			}
			else
			{
				printf("_ ");
			}
			tmp = tmp->next;
		}
		if (tmp->value != -1)
		{
			printf("%d", l->tail->value);
		}
		else
		{
			printf("_");
		}
	}
}

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



struct node* liteFind(struct tree* t, int v)
{
	int cycle = 1;
	struct node* presentNode;

	presentNode = t->base;
	while (cycle == 1)
	{
		if (v == presentNode->value)
		{
			return presentNode;
		}
		if (v < presentNode->value)
		{
			if (presentNode->left != NULL)
			{
				presentNode = presentNode->left;
			}
		}
		else
		{
			if (presentNode->right != NULL)
			{
				presentNode = presentNode->right;
			}
		}
	}
}

int emptyList(struct list* l)
{
	struct link* a;
	a = l->head;
	if (a->value != -1)
	{
		return 0;
	}
	while (a->next != NULL)
	{
		if (a->next->value != -1)
		{
			return 0;
		}
		a = a->next;
	}
	return 1;
}


void printTree(struct tree* t)
{
	int cycle = 1;
	int n = 1;
	struct list a;
	initList(&a);
	struct list b;
	initList(&b);
	struct list* l;
	struct link* presentLink;
	
	
	if (t->base != NULL)
	{
		push_back(&a, t->base->value);
		printList(&a);
	}
	else
	{
		printf("-\n");
		return ;
	}

	l = &a;
	presentLink = l->head;
	while (cycle == 1)
	{
		for (int i=1; i < (n + 1); i++)
		{
			if (presentLink->value != -1)
			{
				if (liteFind(t, presentLink->value)->left != NULL)
				{
					push_back(&b, liteFind(t, presentLink->value)->left->value);
				}
				else
				{
					push_back(&b, -1);
				}
				if (liteFind(t, presentLink->value)->right != NULL)
				{
					push_back(&b, liteFind(t, presentLink->value)->right->value);
				}
				else
				{
					push_back(&b, -1);
				}
				if (presentLink->next != NULL)
				{
					presentLink = presentLink->next;
				}
			}
			else
			{
				push_back(&b, -1);
				push_back(&b, -1);
			}
		}
		if (emptyList(&b) == 1)
		{
			printf("\n");
			return ;
		}
		printf(" ");
		printList(&b);
		l = &b;
		presentLink = l->head;
		clearList(&a);
		n = n * 2;

		for (int i = 1; i < (n + 1); i++)
		{
			if (presentLink->value != -1)
			{
				if (liteFind(t, presentLink->value)->left != NULL)
				{
					push_back(&a, liteFind(t, presentLink->value)->left->value);
				}
				else
				{
					push_back(&a, -1);
				}
				if (liteFind(t, presentLink->value)->right != NULL)
				{
					push_back(&a, liteFind(t, presentLink->value)->right->value);
				}
				else
				{
					push_back(&a, -1);
				}
				if (presentLink->next != NULL)
				{
					presentLink = presentLink->next;
				}
			}
			else
			{
				push_back(&a, -1);
				push_back(&a, -1);
			}
		}
		if (emptyList(&a) == 1)
		{
			printf("\n");
			return ;
		}
		printf(" ");
		printList(&a);
		l = &a;
		presentLink = l->head;
		clearList(&b);
		n = n * 2;
	}
}


int main()
{
	struct tree x;
	int v;

	init(&x);

	for (int i=0; i < 7; i++)
	{
		scanf("%d", &v);
		insert(&x, v);
	}

	printTree(&x);
	
	return 0;
}
