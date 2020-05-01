#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10

//개인 코드가 들어있어 오류 발생가능!

/*
비교함수를 갖는 삽입정렬 함수(라이브러리 함수 qsort 따라 하기)
@param		a : 배열 시작 주소
@param		n : 배열의 원소의 수
@param	 size : 각 원소의 바이트 수
@param cmpare : 정렬에 사용할 비교함수 포인터
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

//animal 구조체 정의
typedef struct
{
	char name[20];//이름
	double weight;//몸무게
}animal;

//name에 대하여 사전순(오름차순)으로 정렬하는 비교함수
int name_compare(const void *a, const void *b)
{
	animal *p1 = (animal *)a;
	animal *p2 = (animal *)b;

	return strcmp(p1->name, p2->name);
}

//weight에 대하여 오름차순으로 정렬하는 비교함수
int weight_compare(const void *a, const void *b)
{
	animal *p1 = (animal *)a;
	animal *p2 = (animal *)b;

	if (p1->weight < p2->weight) return -1;
	if (p2->weight < p1->weight) return 1;

	return 0;
}

//먼저 weight에 대해 내림차순으로 정렬하고, weight가 동일하면 name으로 정렬하는 비교함수
int multi_compare(const void *a, const void *b)
{
	animal *p1 = (animal *)a;
	animal *p2 = (animal *)b;

	if (weight_compare(p1, p2) == 0)
		return strcmp(p1->name, p2->name);
	
	return -weight_compare(p1, p2);
}

//정수를 정렬하는 비교함수
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

//문자열을 정렬하는 비교함수
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


	printf("<name에 대하여 사전순으로 정렬>\n");
	insertion_sort(list, sizeof(list) / sizeof(animal), sizeof(animal), name_compare);
	for (i = 0; i < N; i++)
		printf("%15s%10.1f\n", list[i].name, list[i].weight);

	printf("<weight에 대하여 사전순으로 정렬>\n");
	insertion_sort(list, sizeof(list) / sizeof(animal), sizeof(animal), weight_compare);
	for (i = 0; i < N; i++)
		printf("%15s%10.1f\n", list[i].name, list[i].weight);

	printf("<weight에 대하여 내림차순 => weight가 동일하면 name으로 정렬>\n");
	insertion_sort(list, sizeof(list) / sizeof(animal), sizeof(animal), multi_compare);
	for (i = 0; i < N; i++)
		printf("%15s%10.1f\n", list[i].name, list[i].weight);

}