#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

#define IP4 4 //IPv4
#define BIT 8 //IPv4의 비트 개수
#define HOST 10 //host의 개수


int des_compare(const void *a, const void *b)
{
	int *x = (int *)a;
	int *y = (int *)b;

	if (*x < *y) return 1;
	if (*x > *y) return -1;

	return 0;

}

//밑이 x, 진수가 Y인 로그함수 사용하기
double logxY(double y, double x)
{
	return log(y) / log(x);
}

/*
@param	i: 2차원 배열의 첫번째 인덱스
@param	a: 연산을 위해 가져올 2차원 배열의 시작 주소
*/
int change_to_decimal(int i, int a[][BIT])
{
	int j;
	int dec = 0;

	for (j = 7; j >= 0; j--)
		if (a[i][7 - j] != 0)
			dec += pow(2, j);

	return (int)dec;
}

int main(void)
{
	int net_ID[IP4] = { 0 };//네트워크 ID 저장을 위한 변수 선언, 초기화
	int sub_mask = 0;//서브넷 마스크 변수 선언, 초기화
	int sub_num = 0;// 서브넷 개수, 초기화
	int host[HOST] = { 0 };//호스트 당 네트워크 수를 저장할 변수, 초기화 : 데이터 - { 100, 55, 30, 12 };

	char net_work[20] = {0};//네트워크 ID를 입력받을 변수
	char *is_int; //문자열을 체크, 저장하기 위한 변수
	int i, j, k; //반복문을 위한 변수
	int q, r; //q는 몫, r은 나머지를 저장할 변수
	bool flag = true; //입력받은 값에 대해 검사하는 bool 변수
	int cmp[IP4] = { 0 }; //서브넷 마스크와 네트워크 ID를 and 연산하기 위한 배열 선언, 초기화
	int sum = 0; //서브넷을 구성하는데 필요한 네트워크의 수를 저장할 변수
	int check = 0; //사용 가능한 네트워크의 개수를 저장할 변수
	int bit[IP4][BIT] = { 0 }; //bit연산을 위한 배열
	int sub_net[HOST][IP4] = { 0 }; // 서브넷팅 값을 저장할 배열(첫번째 인자: 서브넷 개수, 두번째 인자: IP4)

	printf("[서브넷 계산기] - Subnet IP Zero 기준이 적용되어 있습니다.\n");
	printf("계산에 필요한 값을 입력해 주세요.\n");

	while (true) {//네트워크 ID를 받는 반복문(예외 처리 포함)
		i = 0;
		flag = true;
		printf("네트워크 ID(x.y.z.w)(0~255의 수를 입력) : ");
		scanf(" %[^\n]", net_work);

		is_int = strtok(net_work, ".");//맨 앞의 IP 분리

		while (is_int != NULL) 
		{
			j = 0;
			while (true)//정수값인지 검사
			{
				if (is_int[j] == ' ')
				{
					printf("IP에 문자열이 포함되어 있습니다. 정수만 입력해 주세요\n");
					flag = false;
					break;
				}

				if (is_int[j] == NULL)
					break;

				if (isdigit(is_int[j]) == 0)
				{
					printf("IP에 문자열이 포함되어 있습니다. 정수만 입력해 주세요\n");
					flag = false;
					break;
				}
				j++;
			}
			if (flag == false)//정수가 아닌 값이 입력되면
				break;//빠져나감

			net_ID[i] = atoi(is_int); //받은 IP를 정수로 변환

			if (net_ID < 0 || 255 < net_ID[i])// 네트워크 ID가 0~255 사이가 아니면 다시 입력 받아야함
			{
				printf("네트워크 ID는 0~255 사이의 수여야 합니다. 다시 입력해 주세요.\n");
				flag = false;
				break;
			}

			is_int = strtok(NULL, ".");//계속해서 다음 IP 분리
			i++;
		}
		if (flag == false)//이미 틀린 값이 들어왔으므로 아래 구문 실행 X
			continue;

		if (i != 4)//네트워크 ID가 잘못 입력되면
			printf("정확한 네트워크 ID를 입력해 주세요. 4개의 IP를 괄호 안의 형식으로 입력해야 합니다.\n");
		else if (i == 4)
			break;
	}

	while (true)//서브넷 마스크 입력 구간(예외 처리 포함)
	{
		j = 0;
		flag = true;
		is_int = malloc(sizeof(char) * 20); //변수 재사용을 위해 할당

		printf("서브넷 마스크(0~32) : ");
		scanf(" %[^\n]", is_int);

		while (true)//정수값인지 검사
		{
			if (is_int[j] == ' ')
			{
				printf("서브넷 마스크에 문자열이 포함되어 있습니다. 정수만 입력해 주세요\n");
				flag = false;
				free(is_int);
				break;
			}

			if (is_int[j] == NULL)
				break;

			if (isdigit(is_int[j]) == 0)
			{
				printf("서브넷 마스크에 문자열이 포함되어 있습니다. 정수만 입력해 주세요\n");
				flag = false;
				free(is_int);
				break;
			}
			j++;
		}
		if (flag == false)//이미 틀린 값이 들어왔으므로 아래 구문 실행 X
			continue;

		sub_mask = atoi(is_int); //받은 IP를 정수로 변환
		if (0 <= sub_mask && sub_mask <= 32)
			break;
		else
			printf("잘못된 값입니다. 0~32의 정수를 입력해주세요.\n");

		free(is_int);
	}

	for (i = 0; i < 32 - sub_mask; i++)
		check += (int)pow(2, (32 - sub_mask - 1 - i));

	while (true)//서브넷 개수 입력 구간(예외 처리 포함)
	{
		j = 0;
		flag = true;
		is_int = malloc(sizeof(char) * 20); //변수 재사용을 위해 할당

		printf("서브넷 개수(1~%d) : ", HOST);
		scanf(" %[^\n]", is_int);

		while (true)//정수값인지 검사
		{
			if (is_int[j] == ' ')
			{
				printf("서브넷 개수로 정수만 입력해 주세요\n");
				flag = false;
				free(is_int);
				break;
			}

			if (is_int[j] == NULL)
				break;

			if (isdigit(is_int[j]) == 0)
			{
				printf("서브넷 개수로 정수만 입력해 주세요\n");
				flag = false;
				free(is_int);
				break;
			}
			j++;
		}
		if (flag == false)//이미 틀린 값이 들어왔으므로 아래 구문 실행 X
			continue;

		sub_num = atoi(is_int); //받은 IP를 정수로 변환
		if (1 <= sub_num && sub_num <= 10)
			break;
		else
			printf("잘못된 값입니다. 1~10의 정수를 입력해주세요.\n");

		free(is_int);
	}

	for (i = 0; i < sub_num; i++)//서브넷의 크기를 입력받는 반복문
	{
		j = 0;
		flag = true;
		is_int = malloc(sizeof(char) * 20); //변수 재사용을 위해 할당

		printf("%d번째 호스트의 수를 입력하세요 : ", i + 1);
		scanf(" %[^\n]", is_int);

		while (true)//정수값인지 검사
		{
			if (is_int[j] == ' ')
			{
				printf("호스트 수로 정수만 입력해 주세요\n");
				flag = false;
				free(is_int);
				i--;
				break;
			}

			if (is_int[j] == NULL)
				break;

			if (isdigit(is_int[j]) == 0)
			{
				printf("호스트 수로 정수만 입력해 주세요\n");
				flag = false;
				free(is_int);
				i--;
				break;
			}
			j++;
		}
		if (flag == false)//이미 틀린 값이 들어왔으므로 아래 구문 실행 X
			continue;

		host[i] = atoi(is_int); //받은 IP를 정수로 변환

		sum += (int)pow(2, ceil(logxY((host[i] + 2), 2)));

		if (sum > check)
		{
			printf("서브넷을 할당할 수 없습니다.\n");
			printf("할당 가능한 네트워크 크기: %d\n", check);
			printf("주어진 서브넷을 할당하는 데 필요한 크기: %d\n", sum);
			sum = 0;
			i = -1;
		}

		free(is_int);
	}

	qsort(host, HOST, sizeof(int), des_compare);

	q = sub_mask / 8; //서브넷팅에 필요한 수를 계산하는 과정
	r = sub_mask % 8;

	for (i = 0; i < q; i++) //서브넷 마스크 만큼 비트를 1로 채우기(1)
		for (j = 0; j < BIT; j++)
			bit[i][j] = 1;

	for (j = 0; j < r; j++) //서브넷 마스크 만큼 비트를 1로 채우기(2)
		bit[q][j] = 1;

	for (i = 0; i < IP4; i++)//연산을 위한 값을 구해줌
		cmp[i] = change_to_decimal(i, bit);

	for (i = 0; i < sub_num; i++)
		for (j = 0; j < IP4; j++)
			sub_net[i][j] = cmp[j] & net_ID[j];//서브넷팅전 서브넷 값 셋팅

	for (i = 0; i < IP4; i++)//변수 재사용을 위해 초기화
		for (j = 0; j < BIT; j++)
			bit[i][j] = 0;

	for (i = 0; i < IP4; i++)//변수 재사용을 위해 초기화
		cmp[i] = 0;

	for (i = 0; i < sub_num; i++)
	{
		if (host[i] == 0)//호스트 수가 0이면 할당할 필요 없음
			break;

		sub_mask = 32 - (int)ceil(logxY((host[i] + 2), 2));//서브넷팅할때 최대한 작은 조각을 준다.+예외 처리(ex:15대는 못쓰는 ip 2개 때문에 더 큰 조각을 할당해야함)

		q = sub_mask / 8; //서브넷팅에 필요한 수를 계산하는 과정
		r = sub_mask % 8;

		for (k = q; k < IP4; k++)//서브넷팅 범위의 최소값 연산
			for (j = r; j < BIT; j++)
				bit[k][j] = 0;

		bit[3][7] = 1; //마지막 비트를 1로 바꿔줌 (전부 0인 네트웤은 쓸수 x)

		for (k = 0; k < IP4; k++)//연산을 위한 값을 구해줌
			cmp[k] = change_to_decimal(k, bit);

		printf("Subnet %d : ", i + 1);
		for (j = 0; j < IP4; j++)//최소값 출력
		{
			if (j == IP4 - 1)
				printf("%d", sub_net[i][j] + cmp[j]);
			else
				printf("%d.", sub_net[i][j] + cmp[j]);
		}

		printf(" ~ ");

		for (k = q; k < IP4; k++)//서브넷팅 범위의 최대값 연산
			for (j = r; j < BIT; j++)
				bit[k][j] = 1;

		bit[3][7] = 0;//마지막 비트를 0으로 바꿔줌 (전부 1인 네트웤은 쓸수 x)  

		for (k = 0; k < IP4; k++)//연산을 위한 값을 구해줌
			cmp[k] = change_to_decimal(k, bit);

		for (j = 0; j < IP4; j++)//최대값 출력
		{
			if(j == IP4 - 1)
				printf("%d", sub_net[i][j] + cmp[j]);
			else
				printf("%d.", sub_net[i][j] + cmp[j]);
		}
			
		for (k = q; k < IP4; k++)//변수 재사용을 위해 초기화
			for (j = r; j < BIT; j++)
				bit[k][j] = 0;

		printf("(/%d)\n", sub_mask);//서브넷 마스크 출력


		while (true)
		{
			sub_mask--;

			q = sub_mask / 8; //서브넷팅에 필요한 수를 계산하는 과정
			r = sub_mask % 8;

			if (bit[q][r] == 0)//네트워크 ID 서브넷팅
			{
				bit[q][r] = 1;
				break;
			}
			else if (bit[q][r] == 1)
				bit[q][r] = 0;

		}

	}

	return 0;
}