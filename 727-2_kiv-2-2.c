#include <stdio.h>

int main()
{
	int n;
	int a;
	int S = 0;

	scanf("%d", &n);

	for (int i = 0; i < n; i++) 
	{
		scanf("%d", &a);
		S = ((i+1)%2)*a*a + S;

	}

	printf("%d", S);
}
