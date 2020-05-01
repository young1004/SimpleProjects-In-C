#include <stdio.h>
#include "cqueue.h"

/*
* 피보나치 수열을 계산해 출력하는 함수
* @param    q : 피보나치 수열을 계산할 데이터가 들어있는 원형 큐의 시작 주소
* @param  num : 계산할 피보나치 수열의 항
*/
int fib(CQueue* q, int num)
{
	int tmp;
	int fn;

	tmp = dequeue(q);
	fn = tmp + peek(q);
	enqueue(q, fn);
	return tmp;
}

int main(void)
{
	CQueue q;

	init_queue(&q);

	// 피보나치 수열 초기화
	enqueue(&q, 1);
	enqueue(&q, 1);

	for (int i = 1; i <= 20; i++)
		printf("%10d", fib(&q, i));

	return 0;
}