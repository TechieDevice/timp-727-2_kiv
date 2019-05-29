#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 

void tree_sorting(int* arr, int root, int bottom)
{
	int maxChild;
	int done = 0;
	while ((root * 2 <= bottom) && (!done))
	{
		if (root * 2 == bottom)
		{
			maxChild = root * 2;
		}
		else if (arr[root * 2] > arr[root * 2 + 1])
		{
			maxChild = root * 2;
		}
		else
		{
			maxChild = root * 2 + 1;
		}
		if (arr[root] < arr[maxChild])
		{
			int temp = arr[root];
			arr[root] = arr[maxChild];
			arr[maxChild] = temp;
			root = maxChild;
		}
		else
		{
			done = 1;
		}
	}
}

void sorting_function(int* arr, int array_size)
{
	double tmp;
	tmp = (array_size / 2.0 + 0.5) - 1;

	for (int i = (int)tmp; i >= 0; i--)
	{
		tree_sorting(arr, i, array_size - 1);
	}
	for (int i = array_size - 1; i >= 1; i--)
	{
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		tree_sorting(arr, 0, i - 1);
	}
}

int main()
{
	int* a;
	int i, n;
	scanf("%d", &n);
	a = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	sorting_function(a, n);
	for (i = 0; i < n; i++)
	{
		if (i == (n - 1))
		{
			printf("%d\n", a[i]);
		}
		else
		{
			printf("%d ", a[i]);
		}
	}
	return 0;
}
