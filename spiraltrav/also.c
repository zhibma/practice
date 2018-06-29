#define IS_DEBUG 0 //1 means yes, 0 means no.
#define MAX_LEN 10
#include <stdio.h>

int a[MAX_LEN][MAX_LEN], m, n;

void init(int h)
{
	int i, j, k = 1;
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < h; j++)
		{
			a[i][j] = k++;
		}
	}
	m = n = h;
}

void printm()
{
	int i, j;
	putchar('\n');
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("%2d ", a[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
}

void change()
{
	int t = m -1;
	m = n;
	n = t;

	int i, j, b[m][n];
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			b[i][j] = a[j + 1][m -1 - i];
		}
	}

	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			a[i][j]=b[i][j];
		}
	}
}

int main()
{
	int iNum;
	printf("Input a number to initialize the matrix: ");
	scanf("%d", &iNum);
	if(iNum > MAX_LEN)
	{
		printf("The number need less than %d\n", MAX_LEN);
		return 1;
	}
	init(iNum);
	int i, j;
	for(i = 0; i < m;)
	{
		#if IS_DEBUG
		printm();
		#endif
		for(j = 0; j < n; j++)printf("%d ", a[0][j]);
		change();
	}
	putchar('\n');
	return 0;
}
