#include <stdio.h>
#include <stdlib.h>
#include "Deque.h"

void DequeInit(Deque* pdeq)
{
	pdeq->head = NULL;
	pdeq->tail = NULL;
}

int DQIsEmpty(Deque* pdeq)
{
	if (pdeq->head->next == pdeq->tail)
		return TRUE;
	else
		return FALSE;
}

void DQAddFirst(Deque* pdeq, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = pdeq->head;

	if (DQIsEmpty(pdeq))
		pdeq->tail = newNode;
	else
		pdeq->head->prev = newNode;

	newNode->prev = NULL;
	pdeq->head = newNode;
}

void DQAddLast(Deque* pdeq, Data data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->prev = pdeq->tail;

	if (DQIsEmpty(pdeq))
		pdeq->head = newNode;
	else
		pdeq->tail->next = newNode;

	newNode->next = NULL;
	pdeq->tail = newNode;
}

Data DQRemoveFirst(Deque* pdeq)
{
	Node* rnode = pdeq->head->next;
	Data rdata = pdeq->head->next->data;

	if (DQIsEmpty(pdeq))
	{
		printf("Deque Memory Error!");
		exit(-1);
	}

	pdeq->head->next = pdeq->head->next->next;
	free(rnode);

	if (DQIsEmpty(pdeq))
		pdeq->tail->prev = pdeq->head;

	return rdata;
}

Data DQRemoveLast(Deque* pdeq)
{
	Node* rnode = pdeq->tail;
	Data rdata = pdeq->tail->data;

	if (DQIsEmpty(pdeq))
	{
		printf("Deque Memory Error!");
		exit(-1);
	}

	pdeq->tail = pdeq->tail->prev;
	free(rnode);

	if (pdeq->tail == NULL)
		pdeq->head = NULL;
	else
		pdeq->tail->next = NULL;

	return rdata;
}

Data DQGetFirst(Deque* pdeq)
{
	if (DQIsEmpty(pdeq))
	{
		printf("Deque Memory Error!");
		exit(-1);
	}

	return pdeq->head->next->data;
}

Data DQGetLast(Deque* pdeq)
{
	if (DQIsEmpty(pdeq))
	{
		printf("Deque Memory Error!");
		exit(-1);
	}

	return pdeq->tail->prev->data;
}
