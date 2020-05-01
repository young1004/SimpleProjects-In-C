#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void selection_sort(double a[], int n);
void check_sorted(double a[], int n);

int main(void) 
{
	double score[100000];
	int i;
	clock_t start, end;
	double elapsed = 0;

	srand(time(NULL));

	for (i = 0; i < 100000; i++)
		score[i] = rand() / (double)RAND_MAX;


	start = clock();
	selection_sort(score, 100000);
	end = clock();

	elapsed = (end - start) / (double)CLOCKS_PER_SEC;

	printf("\n경과 시간3 : %0.3lf \n\n", elapsed);

	for (i = 0; i < 100000; i++)
		printf("%lf\n", score[i]);

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
	int i, j;

	for (i = 0; i < n-2; i++) {
		for (j = i+1; j < n; j++) {
			if (a[i] > a[j]) {
				printf("오름차순이 아닙니다.");
				return;
			}
		}

	}

	printf("오름차순입니다.");
	return;
}

