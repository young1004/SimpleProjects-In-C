#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LEN 244

//������ ������ ���� ����ü
typedef struct _NC {
	char nation[50];
	char capital[50];
}NC;

//������ ������ �Ǵ� ���Լ���
int asc_compare(const void *a, const void *b);
int nation_compare(const void *a, const void *b);
int capital_compare(const void *a, const void *b);

//������ �迭�� ���� ������ �˰��� �Լ���
int int_partition(int a[], int low, int high);
void qs_rec(int a[], int low, int high);
void quick_int_sort(int a[], int n);

//�迭�� �� ���� �ٲ��ִ� swap �Լ�
void swap(void *a, int i, int j, int size);
//�迭�� ���ĵǾ��ִ��� üũ�ϴ� �˻��Լ�
void check_sorted(const void *a, int n, int size, int(*cmp)(const void *a, const void *b));

//void*�� �̿��� ���� �ڷ����� �� ����
int partition(void *a, int low, int high, int size, int(*cmp)(const void *a, const void *b));
void qs_recur(void *a, int low, int high, int size, int(*cmp)(const void *a, const void *b));
void quick_sort(NC a[], int n, int size, int(*cmp)(const void *a, const void *b));


int main(void)
{
	int a[8] = { 123, 34, 189, 56, 150, 123, 9, 140 };
	FILE *capitals = fopen("capitals.txt", "r");
	NC nc[LEN];
	char cpy[50];
	int i;

	if (capitals == NULL)
		printf("\ncapitals.txt ������ �о���� ���Ͽ����ϴ�.\n");

	for (i = 0; i < LEN; i++) {

		fscanf(capitals, "%[^\t]	", cpy);
		strcpy(nc[i].nation, cpy);

		fscanf(capitals, "%[^\n]\n", cpy);
		strcpy(nc[i].capital, cpy);
	}

	quick_sort(nc, LEN, sizeof(NC), nation_compare);//LEN�� sizeof(nc)/sizeof(NC)�� ��ü ����

	printf("\n< ���������� ���� >\n");
	for (i = LEN - 5; i < LEN; i++)
		printf("%-25s%s\n", nc[i].nation, nc[i].capital);

	quick_sort(nc, LEN, sizeof(NC), capital_compare);//LEN�� sizeof(nc)/sizeof(NC)�� ��ü ����

	printf("\n< ���������� ���� >\n");
	for (i = LEN - 5; i < LEN; i++)
		printf("%-25s%s\n", nc[i].nation, nc[i].capital);

	if (capitals != NULL)
		fclose(capitals);

	return 0;
}

/*
�Էµ� �� ���� �ٲ��ִ� swap �Լ�
@param		a : �迭 ���� �ּ�
@param		i : �ٲ� ������ ù��° ��
@param		j : �ٲ� ������ �ι�° ��
@param	 size : �ڷ����� ũ��
*/
void swap(void *a, int i, int j, int size)
{
	void *tmp = malloc(size);
	memcpy(tmp, (char *)a + i * size, size);
	memcpy((char *)a + i * size, (char *)a + j * size, size);
	memcpy((char *)a + j * size, tmp, size);
	free(tmp);
}

//���� a�� b�� ���ϴ� ���Լ�
int asc_compare(const void *a, const void *b)
{
	int *x = (int *)a;
	int *y = (int *)b;

	if (*x < *y) return -1;
	if (*x > *y) return 1;

	return 0;

}

//������ �迭�� ���� �������� ���� �˰���
int int_partition(int a[], int low, int high)
{
	int i = low;
	int j = high + 1;
	int tmp;


	while (true) {
		while (a[++i] < a[low])
			if (i == high) break;
		while (a[low] < a[--j])
			if (j == low) break;
		if (i >= j) break;

		swap(a, i, j, sizeof(int));
	}

	swap(a, low, j, sizeof(int));

	return j;
}

//������ �迭 ������ ��� ����� �Լ�
void qs_rec(int a[], int low, int high)
{
	int pivot;

	if (low >= high) return;

	pivot = int_partition(a, low, high);

	qs_rec(a, low, pivot - 1);
	qs_rec(a, pivot + 1, high);
}

//ũ�Ⱑ n�� ������ �迭�� �������ϴ� ��� �Լ�
void quick_int_sort(int a[], int n)
{
	qs_rec(a, 0, n - 1);
}

//������ ���� �����ϴ� ���Լ�
int nation_compare(const void *a, const void *b)
{
	NC *p1 = (NC *)a;
	NC *p2 = (NC *)b;

	return strcmp(p1->nation, p2->nation);
}

//������ ���� �����ϴ� �� �Լ�
int capital_compare(const void *a, const void *b)
{
	NC *p1 = (NC *)a;
	NC *p2 = (NC *)b;

	return strcmp(p1->capital, p2->capital);
}

/*
pivot�� ��ȯ�ϴ� �������� partion �Լ�
@param		a : �迭 ���� �ּ�
@param	  low : ���� ���� ������ ��
@param	 high : ���� ���� ������ ��
@param	 size : �ڷ����� ũ��
@param	  cmp : ������ ������ �Ǵ� �Լ��� �ּ� ��
*/
int partition(void *a, int low, int high, int size, int(*cmp)(const void *a, const void *b))
{
	int i = low;
	int j = high + 1;
	void *tmp = malloc(size);


	while (true) {

		while (cmp((char*)a + ++i * size, (char*)a + low * size) < 0)
			if (i == high) break;

		while (cmp((char*)a + --j * size, (char*)a + low * size) > 0)
			if (j == low) break;
		if (i >= j) break;

		swap(a, i, j, size);
	}



	swap(a, low, j, size);

	free(tmp);

	return j;

}

/*
 quick_sort�� ��� ����� �Լ�
@param		a : �迭 ���� �ּ�
@param	  low : ���� ���� ������ ��
@param	 high : ���� ���� ������ ��
@param	 size : �ڷ����� ũ��
@param	  cmp : ������ ������ �Ǵ� �Լ��� �ּ� ��
*/
void qs_recur(void *a, int low, int high, int size, int(*cmp)(const void *a, const void *b))
{
	int pivot;

	if (low >= high) return;

	pivot = partition(a, low, high, size, cmp);

	qs_recur(a, low, pivot - 1, size, cmp);
	qs_recur(a, pivot + 1, high, size, cmp);
}

/*
quickSort �˰����� �̿��Ͽ� NC ����ü�� �����ϴ� ��� �Լ�
@param		a : �迭 ���� �ּ�
@param		n : �迭�� ũ��
@param	 size : �ڷ����� ũ��
@param	  cmp : ������ ������ �Ǵ� �Լ��� �ּ� ��
*/
void quick_sort(NC a[], int n, int size, int(*cmp)(const void *a, const void *b))
{
	qs_recur(a, 0, n - 1, size, cmp);
}


/*
�迭�� ���� ���¸� üũ�ϴ� �˻� �Լ�
@param		a : �迭 ���� �ּ�
@param		n : �迭�� ũ��
@param	 size : �ڷ����� ũ��
@param	  cmp : ������ ������ �Ǵ� �Լ��� �ּ� ��
*/
void check_sorted(const void *a, int n, int size, int(*cmp)(const void *a, const void *b)) {
	int i;

	for (i = 0; i < n - 1; i++)
	{
		if (cmp((char*)a + i * size, (char*)a + (i+1) * size) > 0)
		{
			printf("������ �Ǿ����� �ʽ��ϴ�.\n");
			return;
		}
	}

	printf("������ �Ǿ��ֽ��ϴ�.\n");
	return;
}