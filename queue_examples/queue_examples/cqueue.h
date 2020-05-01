#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 3

typedef int element;

typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} CQueue;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(CQueue* q)
{
	q->front = q->rear = 0;
}

bool is_empty(CQueue* q)
{
	return (q->front == q->rear);
}

bool is_full(CQueue* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(CQueue* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element peek(CQueue* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

element dequeue(CQueue* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}