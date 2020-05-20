#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode { // ���� ���� ����Ʈ Ÿ��
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

// ���� ���� ����Ʈ�� �ʱ�ȭ
void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

// ���� ���� ����Ʈ�� ��带 �ͷ�
void print_dlist(DListNode* phead) {
	DListNode* p;

	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}

// ���ο� �����͸� ��� ��� �����ʿ� �����Ѵ�.
void add_first(DListNode* phead, element data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;
	newnode->llink = phead;
	newnode->rlink = phead->rlink;
	phead->rlink->llink = newnode;
	phead->rlink = newnode;
}

// ������ data�� ���� ��带 ã�Ƽ� ������ 1, ������ 0�� ��ȯ�Ѵ�.
int search(DListNode* phead, element data) {
	DListNode* p;

	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (p->data == data)
			return 1;
	}
	return 0;
}

// ������ data�� ���� ��带 �����Ѵ�.
void del_node(DListNode* phead, element data) {
	DListNode* p;

	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (p->data == data) {
			p->llink->rlink = p->rlink;
			p->rlink->llink = p->llink;
		}
	}

}

int main(void) {
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);

	add_first(head, 3);
	add_first(head, 8);
	add_first(head, 9);
	add_first(head, 7);
	add_first(head, 4);
	print_dlist(head);

	if (search(head, 9) == 1) {
		printf("9�� ���� ���� ����Ʈ�� �ֽ��ϴ�.\n\n");
	}
	else {
		printf("9�� ���� ���� ����Ʈ�� �����ϴ�.\n");
	}
	printf("7�� �����մϴ�.\n");
	del_node(head, 7);
	print_dlist(head);

	return 0;
}