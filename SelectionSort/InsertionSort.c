#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//������ ������������ �����ϴ� ���Լ�
int asc_compare(const void *a, const void *b)
{
	int *x = (int *)a;
	int *y = (int *)b;

	if (*x < *y) return -1;
	if (*x > *y) return 1;

	return 0;

}

//������ ������������ �����ϴ� ���Լ�
int des_compare(const void *a, const void *b)
{
	return -asc_compare(a, b);
}

//���ڿ��� �����ϴ� ���Լ�
int str_compare(const void *a, const void *b)
{
	return strcmp((char *)a, (char *)b);

}

int main(void)
{
	int a[5] = { 5, 2, 7, 1, 3 };
	char animals[4][20] = { "dog", "cat", "lion", "bat" };
	int i;

	qsort(a, 5, sizeof(int), des_compare);

	for (i = 0; i < 5; i++)
		printf("%d", a[i]);

	printf("\n\n");

	qsort(animals, 4, 20, str_compare);

	for (i = 0; i < 4; i++)
		printf("%s ", animals[i]);
}

/*
int *a = (int *)x;
�迭�� ���� ��, const void *�� �Ķ���͸� ������ ���� ��Ȯ�� ���α׷����� �� ������.
*/