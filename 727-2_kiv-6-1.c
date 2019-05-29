#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int sorting_function(int* arr, int arr_len)
{
	int n = 0; 
	double fakt = 1.2473309; 
	double step = arr_len - 1;
	int intstep = step;
	int tmp;

	while (step >= 1)
	{
		for (int i = 0; i + intstep < arr_len; ++i)
		{
			if (arr[i] > arr[i + intstep])
			{
				tmp = arr[i];
				arr[i] = arr[i + intstep];
				arr[i + intstep] = tmp;
				n++;
			}
		}
		step /= fakt;
		intstep = (int)(step + 0.5);
	}
	return 0;
}


int main()
{
	int n;
	int a;
	int* arr = &a;
	scanf("%d", &n);
	arr = (int*)malloc(n * sizeof(int));
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	sorting_function(arr, n);

	for (int i = 0; i < n; i++)
	{
		if (i == (n - 1))
		{
			printf("%d\n", arr[i]);
		}
		else
		{
			printf("%d ", arr[i]);
		}
	}	

	return 0;
}
