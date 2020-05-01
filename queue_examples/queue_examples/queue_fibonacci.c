#include <stdio.h>
#include "cqueue.h"

/*
* �Ǻ���ġ ������ ����� ����ϴ� �Լ�
* @param    q : �Ǻ���ġ ������ ����� �����Ͱ� ����ִ� ���� ť�� ���� �ּ�
* @param  num : ����� �Ǻ���ġ ������ ��
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

	// �Ǻ���ġ ���� �ʱ�ȭ
	enqueue(&q, 1);
	enqueue(&q, 1);

	for (int i = 1; i <= 20; i++)
		printf("%10d", fib(&q, i));

	return 0;
}