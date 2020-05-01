#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

#define IP4 4 //IPv4
#define BIT 8 //IPv4�� ��Ʈ ����
#define HOST 10 //host�� ����


int des_compare(const void *a, const void *b)
{
	int *x = (int *)a;
	int *y = (int *)b;

	if (*x < *y) return 1;
	if (*x > *y) return -1;

	return 0;

}

//���� x, ������ Y�� �α��Լ� ����ϱ�
double logxY(double y, double x)
{
	return log(y) / log(x);
}

/*
@param	i: 2���� �迭�� ù��° �ε���
@param	a: ������ ���� ������ 2���� �迭�� ���� �ּ�
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
	int net_ID[IP4] = { 0 };//��Ʈ��ũ ID ������ ���� ���� ����, �ʱ�ȭ
	int sub_mask = 0;//����� ����ũ ���� ����, �ʱ�ȭ
	int sub_num = 0;// ����� ����, �ʱ�ȭ
	int host[HOST] = { 0 };//ȣ��Ʈ �� ��Ʈ��ũ ���� ������ ����, �ʱ�ȭ : ������ - { 100, 55, 30, 12 };

	char net_work[20] = {0};//��Ʈ��ũ ID�� �Է¹��� ����
	char *is_int; //���ڿ��� üũ, �����ϱ� ���� ����
	int i, j, k; //�ݺ����� ���� ����
	int q, r; //q�� ��, r�� �������� ������ ����
	bool flag = true; //�Է¹��� ���� ���� �˻��ϴ� bool ����
	int cmp[IP4] = { 0 }; //����� ����ũ�� ��Ʈ��ũ ID�� and �����ϱ� ���� �迭 ����, �ʱ�ȭ
	int sum = 0; //������� �����ϴµ� �ʿ��� ��Ʈ��ũ�� ���� ������ ����
	int check = 0; //��� ������ ��Ʈ��ũ�� ������ ������ ����
	int bit[IP4][BIT] = { 0 }; //bit������ ���� �迭
	int sub_net[HOST][IP4] = { 0 }; // ������� ���� ������ �迭(ù��° ����: ����� ����, �ι�° ����: IP4)

	printf("[����� ����] - Subnet IP Zero ������ ����Ǿ� �ֽ��ϴ�.\n");
	printf("��꿡 �ʿ��� ���� �Է��� �ּ���.\n");

	while (true) {//��Ʈ��ũ ID�� �޴� �ݺ���(���� ó�� ����)
		i = 0;
		flag = true;
		printf("��Ʈ��ũ ID(x.y.z.w)(0~255�� ���� �Է�) : ");
		scanf(" %[^\n]", net_work);

		is_int = strtok(net_work, ".");//�� ���� IP �и�

		while (is_int != NULL) 
		{
			j = 0;
			while (true)//���������� �˻�
			{
				if (is_int[j] == ' ')
				{
					printf("IP�� ���ڿ��� ���ԵǾ� �ֽ��ϴ�. ������ �Է��� �ּ���\n");
					flag = false;
					break;
				}

				if (is_int[j] == NULL)
					break;

				if (isdigit(is_int[j]) == 0)
				{
					printf("IP�� ���ڿ��� ���ԵǾ� �ֽ��ϴ�. ������ �Է��� �ּ���\n");
					flag = false;
					break;
				}
				j++;
			}
			if (flag == false)//������ �ƴ� ���� �ԷµǸ�
				break;//��������

			net_ID[i] = atoi(is_int); //���� IP�� ������ ��ȯ

			if (net_ID < 0 || 255 < net_ID[i])// ��Ʈ��ũ ID�� 0~255 ���̰� �ƴϸ� �ٽ� �Է� �޾ƾ���
			{
				printf("��Ʈ��ũ ID�� 0~255 ������ ������ �մϴ�. �ٽ� �Է��� �ּ���.\n");
				flag = false;
				break;
			}

			is_int = strtok(NULL, ".");//����ؼ� ���� IP �и�
			i++;
		}
		if (flag == false)//�̹� Ʋ�� ���� �������Ƿ� �Ʒ� ���� ���� X
			continue;

		if (i != 4)//��Ʈ��ũ ID�� �߸� �ԷµǸ�
			printf("��Ȯ�� ��Ʈ��ũ ID�� �Է��� �ּ���. 4���� IP�� ��ȣ ���� �������� �Է��ؾ� �մϴ�.\n");
		else if (i == 4)
			break;
	}

	while (true)//����� ����ũ �Է� ����(���� ó�� ����)
	{
		j = 0;
		flag = true;
		is_int = malloc(sizeof(char) * 20); //���� ������ ���� �Ҵ�

		printf("����� ����ũ(0~32) : ");
		scanf(" %[^\n]", is_int);

		while (true)//���������� �˻�
		{
			if (is_int[j] == ' ')
			{
				printf("����� ����ũ�� ���ڿ��� ���ԵǾ� �ֽ��ϴ�. ������ �Է��� �ּ���\n");
				flag = false;
				free(is_int);
				break;
			}

			if (is_int[j] == NULL)
				break;

			if (isdigit(is_int[j]) == 0)
			{
				printf("����� ����ũ�� ���ڿ��� ���ԵǾ� �ֽ��ϴ�. ������ �Է��� �ּ���\n");
				flag = false;
				free(is_int);
				break;
			}
			j++;
		}
		if (flag == false)//�̹� Ʋ�� ���� �������Ƿ� �Ʒ� ���� ���� X
			continue;

		sub_mask = atoi(is_int); //���� IP�� ������ ��ȯ
		if (0 <= sub_mask && sub_mask <= 32)
			break;
		else
			printf("�߸��� ���Դϴ�. 0~32�� ������ �Է����ּ���.\n");

		free(is_int);
	}

	for (i = 0; i < 32 - sub_mask; i++)
		check += (int)pow(2, (32 - sub_mask - 1 - i));

	while (true)//����� ���� �Է� ����(���� ó�� ����)
	{
		j = 0;
		flag = true;
		is_int = malloc(sizeof(char) * 20); //���� ������ ���� �Ҵ�

		printf("����� ����(1~%d) : ", HOST);
		scanf(" %[^\n]", is_int);

		while (true)//���������� �˻�
		{
			if (is_int[j] == ' ')
			{
				printf("����� ������ ������ �Է��� �ּ���\n");
				flag = false;
				free(is_int);
				break;
			}

			if (is_int[j] == NULL)
				break;

			if (isdigit(is_int[j]) == 0)
			{
				printf("����� ������ ������ �Է��� �ּ���\n");
				flag = false;
				free(is_int);
				break;
			}
			j++;
		}
		if (flag == false)//�̹� Ʋ�� ���� �������Ƿ� �Ʒ� ���� ���� X
			continue;

		sub_num = atoi(is_int); //���� IP�� ������ ��ȯ
		if (1 <= sub_num && sub_num <= 10)
			break;
		else
			printf("�߸��� ���Դϴ�. 1~10�� ������ �Է����ּ���.\n");

		free(is_int);
	}

	for (i = 0; i < sub_num; i++)//������� ũ�⸦ �Է¹޴� �ݺ���
	{
		j = 0;
		flag = true;
		is_int = malloc(sizeof(char) * 20); //���� ������ ���� �Ҵ�

		printf("%d��° ȣ��Ʈ�� ���� �Է��ϼ��� : ", i + 1);
		scanf(" %[^\n]", is_int);

		while (true)//���������� �˻�
		{
			if (is_int[j] == ' ')
			{
				printf("ȣ��Ʈ ���� ������ �Է��� �ּ���\n");
				flag = false;
				free(is_int);
				i--;
				break;
			}

			if (is_int[j] == NULL)
				break;

			if (isdigit(is_int[j]) == 0)
			{
				printf("ȣ��Ʈ ���� ������ �Է��� �ּ���\n");
				flag = false;
				free(is_int);
				i--;
				break;
			}
			j++;
		}
		if (flag == false)//�̹� Ʋ�� ���� �������Ƿ� �Ʒ� ���� ���� X
			continue;

		host[i] = atoi(is_int); //���� IP�� ������ ��ȯ

		sum += (int)pow(2, ceil(logxY((host[i] + 2), 2)));

		if (sum > check)
		{
			printf("������� �Ҵ��� �� �����ϴ�.\n");
			printf("�Ҵ� ������ ��Ʈ��ũ ũ��: %d\n", check);
			printf("�־��� ������� �Ҵ��ϴ� �� �ʿ��� ũ��: %d\n", sum);
			sum = 0;
			i = -1;
		}

		free(is_int);
	}

	qsort(host, HOST, sizeof(int), des_compare);

	q = sub_mask / 8; //������ÿ� �ʿ��� ���� ����ϴ� ����
	r = sub_mask % 8;

	for (i = 0; i < q; i++) //����� ����ũ ��ŭ ��Ʈ�� 1�� ä���(1)
		for (j = 0; j < BIT; j++)
			bit[i][j] = 1;

	for (j = 0; j < r; j++) //����� ����ũ ��ŭ ��Ʈ�� 1�� ä���(2)
		bit[q][j] = 1;

	for (i = 0; i < IP4; i++)//������ ���� ���� ������
		cmp[i] = change_to_decimal(i, bit);

	for (i = 0; i < sub_num; i++)
		for (j = 0; j < IP4; j++)
			sub_net[i][j] = cmp[j] & net_ID[j];//��������� ����� �� ����

	for (i = 0; i < IP4; i++)//���� ������ ���� �ʱ�ȭ
		for (j = 0; j < BIT; j++)
			bit[i][j] = 0;

	for (i = 0; i < IP4; i++)//���� ������ ���� �ʱ�ȭ
		cmp[i] = 0;

	for (i = 0; i < sub_num; i++)
	{
		if (host[i] == 0)//ȣ��Ʈ ���� 0�̸� �Ҵ��� �ʿ� ����
			break;

		sub_mask = 32 - (int)ceil(logxY((host[i] + 2), 2));//��������Ҷ� �ִ��� ���� ������ �ش�.+���� ó��(ex:15��� ������ ip 2�� ������ �� ū ������ �Ҵ��ؾ���)

		q = sub_mask / 8; //������ÿ� �ʿ��� ���� ����ϴ� ����
		r = sub_mask % 8;

		for (k = q; k < IP4; k++)//������� ������ �ּҰ� ����
			for (j = r; j < BIT; j++)
				bit[k][j] = 0;

		bit[3][7] = 1; //������ ��Ʈ�� 1�� �ٲ��� (���� 0�� ��Ʈ�p�� ���� x)

		for (k = 0; k < IP4; k++)//������ ���� ���� ������
			cmp[k] = change_to_decimal(k, bit);

		printf("Subnet %d : ", i + 1);
		for (j = 0; j < IP4; j++)//�ּҰ� ���
		{
			if (j == IP4 - 1)
				printf("%d", sub_net[i][j] + cmp[j]);
			else
				printf("%d.", sub_net[i][j] + cmp[j]);
		}

		printf(" ~ ");

		for (k = q; k < IP4; k++)//������� ������ �ִ밪 ����
			for (j = r; j < BIT; j++)
				bit[k][j] = 1;

		bit[3][7] = 0;//������ ��Ʈ�� 0���� �ٲ��� (���� 1�� ��Ʈ�p�� ���� x)  

		for (k = 0; k < IP4; k++)//������ ���� ���� ������
			cmp[k] = change_to_decimal(k, bit);

		for (j = 0; j < IP4; j++)//�ִ밪 ���
		{
			if(j == IP4 - 1)
				printf("%d", sub_net[i][j] + cmp[j]);
			else
				printf("%d.", sub_net[i][j] + cmp[j]);
		}
			
		for (k = q; k < IP4; k++)//���� ������ ���� �ʱ�ȭ
			for (j = r; j < BIT; j++)
				bit[k][j] = 0;

		printf("(/%d)\n", sub_mask);//����� ����ũ ���


		while (true)
		{
			sub_mask--;

			q = sub_mask / 8; //������ÿ� �ʿ��� ���� ����ϴ� ����
			r = sub_mask % 8;

			if (bit[q][r] == 0)//��Ʈ��ũ ID �������
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