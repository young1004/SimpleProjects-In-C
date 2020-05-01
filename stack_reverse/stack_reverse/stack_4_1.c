//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define MAX_STR 100
//
///* Stack ����*/
//typedef char element;
//
//typedef struct _stack
//{
//	element data[MAX_STR];
//	int top;
//} Stack;
//
//void init_stack(Stack * stack)
//{
//	stack->top = -1;
//
//}
//
//int is_full(Stack* stack)
//{
//	return stack->top == (MAX_STR - 1);
//}
//
//int is_empty(Stack* stack)
//{
//	return stack->top == -1;
//}
//
//void push(Stack* stack, element item)
//{
//	if (is_full(stack)) 
//	{
//		printf("������ ���� á���ϴ�.\n");
//		return;
//	}
//
//	stack->data[++(stack->top)] = item;
//}
//
//element pop(Stack* stack)
//{
//	if (is_empty(stack)) 
//	{
//		printf("���ÿ� �����Ͱ� �����ϴ�.\n");
//		exit(1);
//	}
//
//	return stack->data[(stack->top)--];
//}
//
//element peek(Stack* stack)
//{
//	if (is_empty(stack))
//	{
//		printf("���ÿ� �����Ͱ� �����ϴ�.\n");
//		exit(1);
//	}
//
//	return stack->data[stack->top];
//}
//
//
///* 
//stack�� �̿��Ͽ� ���ڿ��� �������� �����ϴ� �Լ�
//@param    from : ���� ���ڿ��� ����� �迭�� ���� �ּ�
//@param      to : ���� ���ڿ��� �������� ������ �迭�� ���� �ּ�
//*/
//void reverse(char from[], char to[])
//{
//	Stack tmp_stack;
//	int cnt = 0;
//
//	init_stack(&tmp_stack);
//
//	for (int i = 0; i < strlen(from); i++)
//		push(&tmp_stack, from[i]);
//
//	while (tmp_stack.top>=0)
//	{
//		to[cnt] = pop(&tmp_stack);
//		cnt++;
//	}
//	to[cnt] = '\0';
//}
//
//int main(void)
//{
//	char str1[MAX_STR], str2[MAX_STR];
//
//	printf("���ڿ� �Է�: ");
//	fgets(str1, MAX_STR, stdin);
//	str1[strlen(str1) - 1] = '\0';
//	reverse(str1, str2);
//	printf("\n�Է� ���ڿ�: %s\n", str1);
//	printf("\n���� ���ڿ�: %s\n", str2);
//
//	return 0;
//}