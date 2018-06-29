#include<stdio.h>
#define MAX_LEN 10

int main()
{
	unsigned a[MAX_LEN][MAX_LEN], dim, i, j, n = 1;
	printf("Dimension of the matrix: ");
	scanf("%d", &dim);
	if(dim > MAX_LEN)
	{
		printf("The number need less than %d\n", MAX_LEN);
		return 1;
	}

	for(i = 0; i < dim; i++)
	{
		for(j = 0; j < dim; j++)
		{
			a[i][j] = n++;
		}
	}

	for(n = 0; n < dim / 2; n++)
	{
		for(i = j = n; j < dim - n - 1; j++)printf("%d ", a[i][j]);
		for(j = dim - n - 1, i = n; i < dim - n - 1; i++)printf("%d ", a[i][j]);
		for(i = j = dim - n - 1; j > n; j--)printf("%d ", a[i][j]);
		for(i = dim - n - 1, j = n; i > n; i--)printf("%d ", a[i][j]);
	}
	if(dim % 2)printf("%d",a[n][n]);
	putchar('\n');

	return 0;
}
