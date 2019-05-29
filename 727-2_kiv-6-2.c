#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


void sorting_function(int* arr, int arr_len)
{
	int i, j, k;
	int t;
	for (k = arr_len / 2; k > 0; k /= 2)
	{
		for (i = k; i < arr_len; i++)
		{
			t = arr[i];
			for (j = i; j >= k; j -= k)
			{
				if (t < arr[j - k])
				{
					arr[j] = arr[j - k];
				}
				else
				{
					break;
				}
			}
			arr[j] = t;
		}
	}
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
