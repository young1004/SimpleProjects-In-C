//#include <stdio.h>
//#include <stdlib.h>
//
//typedef int element;
//
//typedef struct ListNode {
//	element data;
//	struct ListNode* link;
//} ListNode;
//
//// ����Ʈ�� ������ ���
//void print_list(ListNode* head) {
//	for (ListNode* p = head; p != NULL; p = p->link) {
//		printf("%3d", p->data);
//	}
//	printf("\n");
//}
//
//// ����Ʈ�� �����͸� ������������ �߰�
//ListNode* ordered_add(ListNode* head, element data) {
//	ListNode* newNode = malloc(sizeof(ListNode));
//
//	newNode->data = data;
//	newNode->link = NULL;
//	// ����� �ٲ� ó��
//	if (head == NULL || head->data > data) {
//		newNode->link = head;
//		return newNode;
//	}
//		
//	for (ListNode* p = head; p != NULL; p = p->link) {
//		if (p->link == NULL || p->link->data >= data) {
//			newNode->link = p->link;
//			p->link = newNode;
//			return head;
//		}
//	}
//}
//
//int main(void) {
//	ListNode* head = NULL;
//	element data;
//
//	for (int i = 0; i < 15; i++) {
//		data = rand() % 10 + 1;
//		head = ordered_add(head, data);
//	}
//	print_list(head);
//
//	return 0;
//}