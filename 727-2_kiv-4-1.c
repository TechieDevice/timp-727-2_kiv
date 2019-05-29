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
			printf("%d\n", l->tail->value);
		}
		else
		{
			printf("_\n");
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
	newNode = (struct node*)malloc(sizeof(struct node));
	if (newNode == NULL)
	{
		return 2;
	}

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
				t->number = t->number + 1;
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
				t->number = t->number + 1;
				return 0;
			}
		}
	}
	return 0;
}

int removeNode(struct tree* t, int v)
{
	int cycle = 1;
	struct node* presentNode;
	struct node* replaceNode;
	struct node* rightReplaseNode;

	presentNode = t->base;
	while (cycle == 1)
	{
		if (v == presentNode->value)
		{
			if ((presentNode->right == NULL) & (presentNode->left == NULL))
			{
				if (presentNode->parent != NULL)
				{
					if (presentNode->parent->right != NULL)
					{
						if (presentNode->parent->right->value == v)
						{
							presentNode->parent->right = NULL;
						}
					}
					if (presentNode->parent->left != NULL)
					{
						if (presentNode->parent->left->value == v)
						{
							presentNode->parent->left = NULL;
						}
					}
				}
				t->number = t->number - 1;
				free(presentNode);
				return 0;
			}

			if (presentNode->right == NULL)
			{
				if (presentNode->parent != NULL)
				{
					replaceNode = presentNode->left;
					replaceNode->parent = presentNode->parent;
					if (presentNode->parent->value < v)
					{
						presentNode->parent->right = replaceNode;
					}
					else
					{
						presentNode->parent->left = replaceNode;
					}
				}
				else
				{
					replaceNode = presentNode->left;
					replaceNode->parent = NULL;
					t->base = replaceNode;
				}
				t->number = t->number - 1;
				free(presentNode);
				return 0;
			}
			
			replaceNode = presentNode->right;
			while (cycle == 1)
			{
				if (replaceNode->left == NULL)
				{
					if (replaceNode->right != NULL)
					{
						if (presentNode->parent != NULL)
						{
							rightReplaseNode = replaceNode->right;
							rightReplaseNode->parent = replaceNode->parent;
							if (presentNode->parent->right->value == v)
							{
								replaceNode->parent->right = rightReplaseNode;
							}
							if (presentNode->parent->left->value == v)
							{
								replaceNode->parent->left = rightReplaseNode;
							}
						}
					}
					else
					{
						if (presentNode->parent != NULL)
						{
							if (presentNode->parent->right != NULL)
							{
								if (presentNode->parent->right->value == v)
								{
									presentNode->parent->right = NULL;
								}
							}
							if (presentNode->parent->left != NULL)
							{
								if (presentNode->parent->left->value == v)
								{
									presentNode->parent->left = NULL;
								}
							}
						}
					}
					if (presentNode->parent != NULL)
					{
						replaceNode->parent = presentNode->parent;
						if (presentNode->parent->value < v)
						{
							replaceNode->parent->right = replaceNode;
							if ((presentNode->left != NULL) & (presentNode->left != replaceNode))
							{
								presentNode->left->parent = replaceNode;
								replaceNode->left = presentNode->left;
							}
							if ((presentNode->right != NULL) & (presentNode->right != replaceNode))
							{
								presentNode->right->parent = replaceNode;
								replaceNode->right = presentNode->right;
							}
							t->number = t->number - 1;
							free(presentNode);
						}
						else
						{
							replaceNode->parent->left = replaceNode;
							if ((presentNode->left != NULL) & (presentNode->left != replaceNode))
							{
								presentNode->left->parent = replaceNode;
								replaceNode->left = presentNode->left;
							}
							if ((presentNode->right != NULL) & (presentNode->right != replaceNode))
							{
								presentNode->right->parent = replaceNode;
								replaceNode->right = presentNode->right;
							}
							t->number = t->number - 1;
							free(presentNode);
						}
					}
					else
					{
						replaceNode->parent = NULL;
						if ((presentNode->left != NULL) & (presentNode->left != replaceNode))
						{
							presentNode->left->parent = replaceNode;
							replaceNode->left = presentNode->left;
						}
						if ((presentNode->right != NULL) & (presentNode->right != replaceNode))
						{
							presentNode->right->parent = replaceNode;
							replaceNode->right = presentNode->right;
						}
						t->number = t->number - 1;
						t->base = replaceNode;
						free(presentNode);
					}
					return 0;
				}
				replaceNode = replaceNode->left;
			}
		}
		if (v < presentNode->value)
		{
			if (presentNode->left != NULL)
			{
				presentNode = presentNode->left;
			}
			else
			{
				return 1;
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
				return 1;
			}
		}
	}
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
			else
			{
				return NULL;
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
				return NULL;
			}
		}
	}
	return NULL;
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


int find(struct tree* t, int v, struct node** n)
{
	int cycle = 1;
	struct node* presentNode;

	presentNode = t->base;
	while (cycle == 1)
	{
		if (v == presentNode->value)
		{
			*n = presentNode;
			return 0;
		}
		if (v < presentNode->value)
		{
			if (presentNode->left != NULL)
			{
				presentNode = presentNode->left;
			}
			else
			{
				return 1;
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
				return 1;
			}
		}
	}
	return -1;
}

void printTree(struct tree* t)
{
	int cycle = 1;
	int n = 1;
	struct list a;
	initList(&a);
	struct list b;
	initList(&b);
	struct link* presentLink;


	if (t->base != NULL)
	{
		push_back(&a, t->base->value);
		printList(&a);
	}
	else
	{
		printf("-\n");
		return;
	}

	presentLink = a.head;
	while (cycle == 1)
	{
		for (int i = 1; i < (n + 1); i++)
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
					/*printf("push_back(b,%d)_sucsess\n", (liteFind(t, presentLink->value)->right->value));*/
				}
				else
				{
					push_back(&b, -1);
				}
			}
			else
			{
				push_back(&b, -1);
				push_back(&b, -1);
			}
			if (presentLink->next != NULL)
			{
				presentLink = presentLink->next;
			}
		}
		if (emptyList(&b) == 1)
		{
			return;
		}
		printList(&b);
		presentLink = b.head;
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
			}
			else
			{
				push_back(&a, -1);
				push_back(&a, -1);
			}
			if (presentLink->next != NULL)
			{
				presentLink = presentLink->next;
			}
		}
		if (emptyList(&a) == 1)
		{
			return;
		}
		printList(&a);
		presentLink = a.head;
		clearList(&b);
		n = n * 2;
	}
}

void clearTree(struct tree* t)
{
	struct node* presentNode;
	struct node* presentNodeParent;
	presentNode = t->base;
	while (t->base != NULL)
	{
		if (presentNode->left == NULL)
		{
			if (presentNode->right == NULL)
			{
				if (presentNode->parent != NULL)
				{
					presentNodeParent = presentNode->parent;
					if (presentNodeParent->right != NULL)
					{
						if (presentNodeParent->right == presentNode)
						{
							presentNode->parent->right = NULL;
							free(presentNode);
							presentNode = presentNodeParent;
						}
					}
					if (presentNodeParent->left != NULL)
					{
						if (presentNode != NULL)
						{
							if (presentNodeParent->left == presentNode)
							{
								presentNode->parent->left = NULL;
								free(presentNode);
								presentNode = presentNodeParent;
							}
						}
					}
				}
				else
				{
					free(presentNode);
					t->base = NULL;
				}
			}
			else
			{
				presentNode = presentNode->right;
			}
			
		}
		else
		{
			presentNode = presentNode->left;
		}
	}
	init(t);
}

int rotateLeft(struct node *n, struct tree *t)
{
	struct node *presentNode;
	if (n->right == NULL) return 1;
	if (n->parent == NULL)
	{
		t->base = n->right;
		n->right->parent = NULL;
	}
	else
	{
		if (n->parent->left == n) n->parent->left = n->right;
		else n->parent->right = n->right;
		n->right->parent = n->parent;
	}
	n->parent = n->right;
	presentNode = n->parent->left;
	n->parent->left = n;
	n->right = presentNode;
	return 0;
}

int rotateRight(struct node *n, struct tree *t)
{
	struct node *presentNode;
	if (n->left == NULL) return 1;
	if (n->parent == NULL)
	{
		t->base = n->left;
		n->left->parent = NULL;
	}
	else
	{
		if (n->parent->left == n) n->parent->left = n->left;
		else n->parent->right = n->left;
		n->left->parent = n->parent;
	}
	n->parent = n->left;
	presentNode = n->parent->right;
	n->parent->right = n;
	n->left = presentNode;
	return 0;
}

int main()
{
	struct tree x;
	int v;
	int k=0;
	struct node* f;
	f = NULL;

	//1
	init(&x);
	for (int i = 0; i < 4; i++)
	{
		scanf("%d", &v);
		insert(&x, v);
	}
	//2
	printTree(&x);
	//3
	for (int i = 0; i < 3; i++)
	{
		scanf("%d", &v);
		insert(&x, v);
	}
	//4
	printTree(&x);
	//5
	scanf("%d", &v);
	f = liteFind(&x, v);
	if (f->parent != NULL)
	{
		printf("%d ", f->parent->value);
	}
	else
	{
		printf("_ ");
	}
	if (f->left != NULL)
	{
		printf("%d ", f->left->value);
	}
	else
	{
		printf("_ ");
	}
	if (f->right != NULL)
	{
		printf("%d\n", f->right->value);
	}
	else
	{
		printf("_\n");
	}
	//6
	scanf("%d", &v);
	f = liteFind(&x, v);
	if (f != NULL)
	{
		if (f->parent != NULL)
		{
			printf("%d ", f->parent->value);
		}
		else
		{
			printf("_ ");
		}
		if (f->left != NULL)
		{
			printf("%d ", f->left->value);
		}
		else
		{
			printf("_ ");
		}
		if (f->right != NULL)
		{
			printf("%d\n", f->right->value);
		}
		else
		{
			printf("_\n");
		}
	}
	else
	{
		printf("-\n");
	}
	//7
	scanf("%d", &v);
	removeNode(&x, v);
	//8
	printTree(&x);
	//9
	while (k == 0)
	{
		k = rotateLeft(x.base, &x);
	}
	k = 0;
	//10
	printTree(&x);
	//11
	while (k == 0)
	{
		k = rotateRight(x.base, &x);
	}
	//12
	printTree(&x);
	//13
	printf("%d\n", x.number);
	//14
	clearTree(&x);
	//15
	printTree(&x);
	return 0;
}
