#include <stdio.h>
#include <memory.h>

#define N 13
#define TEST 36
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int LIS_value(int* arr);
int least(int n);

int main(void)
{
	int arr[N] = { 1, 10, 5, 20, 15, 10, 30, 49, 25, 35, 66, 75, 44 };


	printf("LIS 길이 : %d\n", LIS_value(arr));
	printf("숫자 %d의 최소 연산 횟수 : %d\n", TEST, least(TEST));
	return 0;
}

/*LIS의 길이를 구하는 함수*/
int LIS_value(int* arr)
{
	int len = 0;
	int tmp[N] = { 0 };
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j <= len; j++)
		{
			if (tmp[j] > arr[i])
			{
				tmp[j] = arr[i];
				break;
			}
			if (j == len)
			{
				tmp[j] = arr[i];
				len++;
				break;
			}
		}
	}

	printf("과제[B] 배열의 값(LIS는 아님!) : ");
	for (i = 0; i < len; i++)
		printf("%d ", tmp[i]);
	printf("\n");

	return len;
}

/*구현 과제 아님! 확인용!*/
int least(int n)
{
	int* tmp;
	int i;
	int min = 0;

	tmp = calloc(n + 1, sizeof(int));


	tmp[1] = 0;
	for (i = 2; i <= n; i++)
	{
		if (i % 2 == 0 && i % 3 == 0)
			tmp[i] = MIN(tmp[i-1], MIN(tmp[i / 2], tmp[i / 3])) + 1;
		else if (i % 2 == 0)
			tmp[i] = MIN(tmp[i - 1], tmp[i / 2]) + 1;
		else if (i % 3 == 0)
			tmp[i] = MIN(tmp[i - 1], tmp[i / 3]) + 1;
		else
			tmp[i] = tmp[i - 1] + 1;
	}

	min = tmp[n];
	free(tmp);

	return min;
}