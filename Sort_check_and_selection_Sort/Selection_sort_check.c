#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LEN 100000

void selection_sort(double a[], int n);
void check_sorted(double a[], int n);

int main(void)
{
	double score[LEN];
	int i;
	clock_t start, end;
	double elapsed = 0;

	srand(time(NULL));

	for (i = 0; i < LEN; i++)
		score[i] = rand() / (double)RAND_MAX;

	printf("정렬 전: ");
	for (i = 0; i < LEN; i++)
		printf("%0.1lf ", score[i]);

	printf("\n");
	check_sorted(score, LEN);

	start = clock();
	selection_sort(score, LEN);
	end = clock();

	printf("정렬 후: ");
	for (i = 0; i < LEN; i++)
		printf("%0.1lf ", score[i]);

	printf("\n");
	check_sorted(score, LEN);

	elapsed = (end - start) / (double)CLOCKS_PER_SEC;
	printf("\n");
	printf("\n경과 시간3 : %0.3lf \n\n", elapsed);


	return 0;
}

//선택 정렬 함수
void selection_sort(double a[], int n)
{
	int i, j, least;
	double key;

	for (i = 0; i < n - 1; i++)
	{
		key = a[i];
		least = i;

		for (j = i + 1; j < n; j++)
			if (a[j] < a[least])
				least = j;


		a[i] = a[least];
		a[least] = key;
	}

}

void check_sorted(double a[], int n) {
	int i;

	for (i = 0; i < n-1; i++)
	{
		if (a[i] > a[i + 1])
		{
			printf("정렬이 되어있지 않습니다.\n");
			return;
		}
	}

	printf("정렬이 되어있습니다.");
	return;
}

