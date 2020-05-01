#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_STRING   4
#define MAX_STR 100

/* Stack ����*/
typedef char element;

typedef struct _stack
{
	element data[MAX_STR];
	int top;
} Stack;

void init_stack(Stack* stack)
{
	stack->top = -1;

}

int is_full(Stack* stack)
{
	return stack->top == (MAX_STR - 1);
}

int is_empty(Stack* stack)
{
	return stack->top == -1;
}

void push(Stack* stack, element item)
{
	if (is_full(stack))
	{
		printf("������ ���� á���ϴ�.\n");
		return;
	}

	stack->data[++(stack->top)] = item;
}

element pop(Stack* stack)
{
	if (is_empty(stack))
	{
		printf("���ÿ� �����Ͱ� �����ϴ�.\n");
		exit(1);
	}

	return stack->data[(stack->top)--];
}

element peek(Stack* stack)
{
	if (is_empty(stack))
	{
		printf("���ÿ� �����Ͱ� �����ϴ�.\n");
		exit(1);
	}

	return stack->data[stack->top];
}

/*
stack�� �̿��Ͽ� ���ڿ��� �������� �����ϴ� �Լ�
@param    from : ���� ���ڿ��� ����� �迭�� ���� �ּ�
@param      to : ���� ���ڿ��� �������� ������ �迭�� ���� �ּ�
*/
void reverse(char from[], char to[])
{
	Stack tmp_stack;
	int cnt = 0;

	init_stack(&tmp_stack);

	for (int i = 0; i < strlen(from); i++)
		push(&tmp_stack, from[i]);

	while (tmp_stack.top >= 0)
	{
		to[cnt] = pop(&tmp_stack);
		cnt++;
	}
	to[cnt] = '\0';
}

/*
�Էµ� ���ڿ����� �����ڸ� ������ ��� ���ڴ� �����ϰ�, �빮�ڴ� �ҹ��ڷ� ��ȯ�ؼ� op�� �����ϴ� �Լ�
@param      ip : ��ȯ ����� �� �迭�� ���� �ּ�
@param      to : ��ȯ�� �Ϸ�� ���ڿ��� ����� �迭�� ���� �ּ�
*/
void convertString(char ip[], char op[]) {

	int cnt = 0;

	for (int i = 0; i < strlen(ip); i++)
	{
		if (isupper(ip[i]))
			op[cnt] = (char)((int)ip[i] + 32);
		else if (islower(ip[i]))
			op[cnt] = ip[i];
		else
			continue;
		
		cnt++;
	}

	op[cnt] = '\0';
}

/*
�Էµ� ���ڿ��� ȸ���̸� 1�� ��ȯ�ϰ�, �׷��� ������ 0�� ��ȯ�ϴ� �Լ�
@param     str : ȸ������ �ƴ��� �˻��� ���ڿ��� ����� �迭�� ���� �ּ�
*/
int checkPalindrom(char str[]) {
	char tmp[MAX_STR];

	reverse(str, tmp);

	if (strcmp(str, tmp)==0)
		return 1;
	else
		return 0;
}

int main(void) {
	char str[NUM_STRING][MAX_STR] = {
		"eye",
		"madam, I'm Adam",
		"madam, I am Adam",
		"race car"
	};
	char op[MAX_STR];
	int i;

	for (i = 0; i < NUM_STRING; i++) {
		convertString(str[i], op);
		printf("���ڿ�: %s ==> ", str[i]);
		if (checkPalindrom(op) == 1)
			printf("ȸ����\n");
		else
			printf("ȸ���� �ƴ�\n");
	}

	return 0;
}