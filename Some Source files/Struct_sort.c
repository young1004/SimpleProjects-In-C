#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10

//���� �ڵ尡 ����־� ���� �߻�����!

/*
���Լ��� ���� �������� �Լ�(���̺귯�� �Լ� qsort ���� �ϱ�)
@param		a : �迭 ���� �ּ�
@param		n : �迭�� ������ ��
@param	 size : �� ������ ����Ʈ ��
@param cmpare : ���Ŀ� ����� ���Լ� ������
*/
void insertion_sort(void *a, int n, int size, int(*cmp)(const void *a, const void *b))
{
	int i, j;
	void *key = malloc(size);

	for (i = 0; i < n; i++)
	{

		memcpy(key, (char *)a + i * size, size);//key = a[i];

		j = i - 1;
		while (j >= 0 && cmp((char *)a + j * size, key) > 0)
		{
			memcpy((char *)a + (j + 1) * size, (char *)a + j * size, size);//a[i + 1] = a[i];
			j--;

		}
		memcpy((char *)a + (j + 1) * size, key, size);//a[j + 1] = key;
	}

	free(key);

}

//animal ����ü ����
typedef struct
{
	char name[20];//�̸�
	double weight;//������
}animal;

//name�� ���Ͽ� ������(��������)���� �����ϴ� ���Լ�
int name_compare(const void *a, const void *b)
{
	animal *p1 = (animal *)a;
	animal *p2 = (animal *)b;

	return strcmp(p1->name, p2->name);
}

//weight�� ���Ͽ� ������������ �����ϴ� ���Լ�
int weight_compare(const void *a, const void *b)
{
	animal *p1 = (animal *)a;
	animal *p2 = (animal *)b;

	if (p1->weight < p2->weight) return -1;
	if (p2->weight < p1->weight) return 1;

	return 0;
}

//���� weight�� ���� ������������ �����ϰ�, weight�� �����ϸ� name���� �����ϴ� ���Լ�
int multi_compare(const void *a, const void *b)
{
	animal *p1 = (animal *)a;
	animal *p2 = (animal *)b;

	if (weight_compare(p1, p2) == 0)
		return strcmp(p1->name, p2->name);
	
	return -weight_compare(p1, p2);
}

//������ �����ϴ� ���Լ�
int asc_compare(const void *a, const void *b)
{
	int *x = (int *)a;
	int *y = (int *)b;

	if (*x < *y) return -1;
	if (*x > *y) return 1;

	return 0;

}
int des_compare(const void *a, const void *b)
{
	return -asc_compare(a, b);
}

//���ڿ��� �����ϴ� ���Լ�
int str_asc_compare(const void *a, const void *b)
{
	return strcmp((char *)a, (char *)b);
}
int str_des_compare(const void *a, const void *b)
{
	return -strcmp((char *)a, (char *)b);
}

int main(void)
{
	int i;
	animal list[N] = { {"human_adult", 1350}, {"chimpanzee", 400}, {"cat", 30}, {"dog", 30}, {"human_baby", 400}, {"alligator", 8.4}, {"turtle", 0.3}, {"lizard", 0.08}, {"dolphin", 1500}, {"elephant", 6000} };


	printf("<name�� ���Ͽ� ���������� ����>\n");
	insertion_sort(list, sizeof(list) / sizeof(animal), sizeof(animal), name_compare);
	for (i = 0; i < N; i++)
		printf("%15s%10.1f\n", list[i].name, list[i].weight);

	printf("<weight�� ���Ͽ� ���������� ����>\n");
	insertion_sort(list, sizeof(list) / sizeof(animal), sizeof(animal), weight_compare);
	for (i = 0; i < N; i++)
		printf("%15s%10.1f\n", list[i].name, list[i].weight);

	printf("<weight�� ���Ͽ� �������� => weight�� �����ϸ� name���� ����>\n");
	insertion_sort(list, sizeof(list) / sizeof(animal), sizeof(animal), multi_compare);
	for (i = 0; i < N; i++)
		printf("%15s%10.1f\n", list[i].name, list[i].weight);

}