#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LEN 244

//국가와 수도를 담을 구조체
typedef struct _NC {
	char nation[50];
	char capital[50];
}NC;

//정렬의 기준이 되는 비교함수들
int asc_compare(const void *a, const void *b);
int nation_compare(const void *a, const void *b);
int capital_compare(const void *a, const void *b);

//정수형 배열에 대한 퀵정렬 알고리즘 함수들
int int_partition(int a[], int low, int high);
void qs_rec(int a[], int low, int high);
void quick_int_sort(int a[], int n);

//배열의 두 값을 바꿔주는 swap 함수
void swap(void *a, int i, int j, int size);
//배열이 정렬되어있는지 체크하는 검사함수
void check_sorted(const void *a, int n, int size, int(*cmp)(const void *a, const void *b));

//void*를 이용해 많은 자료형을 비교 가능
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
		printf("\ncapitals.txt 파일을 읽어오지 못하였습니다.\n");

	for (i = 0; i < LEN; i++) {

		fscanf(capitals, "%[^\t]	", cpy);
		strcpy(nc[i].nation, cpy);

		fscanf(capitals, "%[^\n]\n", cpy);
		strcpy(nc[i].capital, cpy);
	}

	quick_sort(nc, LEN, sizeof(NC), nation_compare);//LEN은 sizeof(nc)/sizeof(NC)로 대체 가능

	printf("\n< 국가순으로 정렬 >\n");
	for (i = LEN - 5; i < LEN; i++)
		printf("%-25s%s\n", nc[i].nation, nc[i].capital);

	quick_sort(nc, LEN, sizeof(NC), capital_compare);//LEN은 sizeof(nc)/sizeof(NC)로 대체 가능

	printf("\n< 수도순으로 정렬 >\n");
	for (i = LEN - 5; i < LEN; i++)
		printf("%-25s%s\n", nc[i].nation, nc[i].capital);

	if (capitals != NULL)
		fclose(capitals);

	return 0;
}

/*
입력된 두 값을 바꿔주는 swap 함수
@param		a : 배열 시작 주소
@param		i : 바꿀 원소의 첫번째 값
@param		j : 바꿀 원소의 두번째 값
@param	 size : 자료형의 크기
*/
void swap(void *a, int i, int j, int size)
{
	void *tmp = malloc(size);
	memcpy(tmp, (char *)a + i * size, size);
	memcpy((char *)a + i * size, (char *)a + j * size, size);
	memcpy((char *)a + j * size, tmp, size);
	free(tmp);
}

//정수 a와 b를 비교하는 비교함수
int asc_compare(const void *a, const void *b)
{
	int *x = (int *)a;
	int *y = (int *)b;

	if (*x < *y) return -1;
	if (*x > *y) return 1;

	return 0;

}

//정수형 배열에 대한 퀵정렬의 분할 알고리즘
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

//정수형 배열 퀵정렬 재귀 도우미 함수
void qs_rec(int a[], int low, int high)
{
	int pivot;

	if (low >= high) return;

	pivot = int_partition(a, low, high);

	qs_rec(a, low, pivot - 1);
	qs_rec(a, pivot + 1, high);
}

//크기가 n인 정수형 배열을 퀵정렬하는 재귀 함수
void quick_int_sort(int a[], int n)
{
	qs_rec(a, 0, n - 1);
}

//국가에 대해 정렬하는 비교함수
int nation_compare(const void *a, const void *b)
{
	NC *p1 = (NC *)a;
	NC *p2 = (NC *)b;

	return strcmp(p1->nation, p2->nation);
}

//수도에 대해 정렬하는 비교 함수
int capital_compare(const void *a, const void *b)
{
	NC *p1 = (NC *)a;
	NC *p2 = (NC *)b;

	return strcmp(p1->capital, p2->capital);
}

/*
pivot을 반환하는 퀵정렬의 partion 함수
@param		a : 배열 시작 주소
@param	  low : 가장 낮은 원소의 값
@param	 high : 가장 높은 원소의 값
@param	 size : 자료형의 크기
@param	  cmp : 정렬할 기준이 되는 함수의 주소 값
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
 quick_sort의 재귀 도우미 함수
@param		a : 배열 시작 주소
@param	  low : 가장 낮은 원소의 값
@param	 high : 가장 높은 원소의 값
@param	 size : 자료형의 크기
@param	  cmp : 정렬할 기준이 되는 함수의 주소 값
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
quickSort 알고리즘을 이용하여 NC 구조체를 정렬하는 재귀 함수
@param		a : 배열 시작 주소
@param		n : 배열의 크기
@param	 size : 자료형의 크기
@param	  cmp : 정렬할 기준이 되는 함수의 주소 값
*/
void quick_sort(NC a[], int n, int size, int(*cmp)(const void *a, const void *b))
{
	qs_recur(a, 0, n - 1, size, cmp);
}


/*
배열의 정렬 상태를 체크하는 검사 함수
@param		a : 배열 시작 주소
@param		n : 배열의 크기
@param	 size : 자료형의 크기
@param	  cmp : 정렬할 기준이 되는 함수의 주소 값
*/
void check_sorted(const void *a, int n, int size, int(*cmp)(const void *a, const void *b)) {
	int i;

	for (i = 0; i < n - 1; i++)
	{
		if (cmp((char*)a + i * size, (char*)a + (i+1) * size) > 0)
		{
			printf("정렬이 되어있지 않습니다.\n");
			return;
		}
	}

	printf("정렬이 되어있습니다.\n");
	return;
}