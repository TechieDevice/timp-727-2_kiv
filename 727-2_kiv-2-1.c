#include<stdio.h>

int main()
{
	int n;
	float a;
	float S = 0;

	scanf("%d", &n);

	for (int i = 0; i < n; i++) 
	{
		scanf("%f", &a);
		S = S + a;
	}

	a = S / n;
	printf("%f", a);
}

