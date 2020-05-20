#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode { // 이중 연결 리스트 타입
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

// 이중 연결 리스트를 초기화
void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

// 이중 연결 리스트의 노드를 촐력
void print_dlist(DListNode* phead) {
	DListNode* p;

	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}

// 새로운 데이터를 헤드 노드 오른쪽에 삽입한다.
void add_first(DListNode* phead, element data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;
	newnode->llink = phead;
	newnode->rlink = phead->rlink;
	phead->rlink->llink = newnode;
	phead->rlink = newnode;
}

// 데이터 data를 가진 노드를 찾아서 있으면 1, 없으면 0을 반환한다.
int search(DListNode* phead, element data) {
	DListNode* p;

	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (p->data == data)
			return 1;
	}
	return 0;
}

// 데이터 data를 가진 노드를 삭제한다.
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
		printf("9는 이중 연결 리스트에 있습니다.\n\n");
	}
	else {
		printf("9는 이중 연결 리스트에 없습니다.\n");
	}
	printf("7을 제거합니다.\n");
	del_node(head, 7);
	print_dlist(head);

	return 0;
}