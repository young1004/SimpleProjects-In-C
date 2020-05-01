#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_STRING   4
#define MAX_STR 100

/* Stack 구현*/
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
		printf("스택이 가득 찼습니다.\n");
		return;
	}

	stack->data[++(stack->top)] = item;
}

element pop(Stack* stack)
{
	if (is_empty(stack))
	{
		printf("스택에 데이터가 없습니다.\n");
		exit(1);
	}

	return stack->data[(stack->top)--];
}

element peek(Stack* stack)
{
	if (is_empty(stack))
	{
		printf("스택에 데이터가 없습니다.\n");
		exit(1);
	}

	return stack->data[stack->top];
}

/*
stack을 이용하여 문자열을 역순으로 저장하는 함수
@param    from : 원본 문자열이 저장된 배열의 시작 주소
@param      to : 원본 문자열을 역순으로 저장할 배열의 시작 주소
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
입력된 문자열에서 영문자를 제외한 모든 문자는 제거하고, 대문자는 소문자로 변환해서 op에 저장하는 함수
@param      ip : 변환 대상이 될 배열의 시작 주소
@param      to : 변환이 완료된 문자열이 저장될 배열의 시작 주소
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
입력된 문자열이 회문이면 1을 반환하고, 그렇지 않으면 0을 반환하는 함수
@param     str : 회문인지 아닌지 검사할 문자열이 저장된 배열의 시작 주소
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
		printf("문자열: %s ==> ", str[i]);
		if (checkPalindrom(op) == 1)
			printf("회문임\n");
		else
			printf("회문이 아님\n");
	}

	return 0;
}