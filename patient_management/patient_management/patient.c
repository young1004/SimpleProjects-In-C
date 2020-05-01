#include <stdio.h>
#include <string.h>
#include "DBDLinkedList.h"
#include "Deque.h"

int main(void)
{
	List emergency; //���� ȯ��
	List reserve; //���� ȯ��
	List normal; //�Ϲ� ȯ��

	Deque patient;//ȯ�� ��ü

	int select;//��ȣ ����
	int grade;// ȯ�� ���
	int pnum = 0;//ȯ�� ��ȣ
	char name;//ȯ�� �̸�

	ListInit(&emergency);
	ListInit(&reserve);
	ListInit(&normal);

	DequeInit(&patient);

	printf("--------------------------------------------\n");
	printf("            ȯ�� ���� ���α׷� \n");
	printf("--------------------------------------------\n");
	printf("1. ȯ�� �߰� \n");
	printf("2. ȯ�� ���� �Ϸ� \n");
	printf("3. ���ȯ�� �� ��� \n");
	printf("4. ȯ�� ����ȣ ��� \n");
	printf("5. ȯ�� ���� ��� \n");
	printf("6. ���ȯ�� ��� ��� \n");
	printf("7. ������ ��� ȯ�� ��� \n");
	printf("8. ���� ���� ȯ�� ��� \n");
	printf("9. ��޺� ȯ�� ��� \n");
	printf("10. ���α׷� ���� \n");
	printf("--------------------------------------------\n");


	while (1)
	{
		printf("���ڸ� �Է��ϼ���: ");

		scanf("%d", &select);
		getchar();

		if (select == 10) //���α׷� ����
		{
			printf("���α׷� ����. \n");
			break;
		}


		if (select == 1) //ȯ�� �߰�
		{

			while (1)
			{
				printf("ȯ���� ���¸� �Է��ϼ���(1.����, 2.����, 3.�Ϲ�): ");
				scanf("%d", &grade);
				getchar(); //���� ����

				if (grade >= 1 && grade <= 3)
					break;
				else
					printf("���� �ùٸ��� �ʽ��ϴ�. 1~3������ ���� �Է����ּ���. \n\n");
			}

			while (1)
			{
				printf("ȯ���� �̸��� �Է��ϼ���(���ĺ� �빮��): ");
				scanf("%c", &name);
				getchar(); //���� ����

				if (name >= 65 && name <= 90)
					break;
				else
					printf("���� �ùٸ��� �ʽ��ϴ�. ���ĺ� �빮�ڸ� �Է����ּ���. \n\n");
			}

			if (grade == 1)
				LInsert(&emergency, name);
			else if (grade == 2)
				LInsert(&reserve, name);
			else if (grade == 3)
				LInsert(&normal, name);

		}

		if (LFirst(&reserve, &name))//����ȯ�ڰ� ������
		{
			emergency.tail->prev->next = reserve.head->next;//����ȯ�ڿ� ����

			if (LFirst(&normal, &name))//�Ϲ�ȯ�ڵ�������
				reserve.tail->prev->next = normal.head->next;//�Ϲ�ȯ�ڿ� ����
			else
				reserve.tail->prev->next = normal.tail;//������ ������ ����
		}
		else if (LFirst(&normal, &name)) //����ȯ�ڰ� ���� �Ϲ�ȯ�ڴ� ������
			emergency.tail->prev->next = normal.head->next;
		else //�Ѵ� ������
			emergency.tail->prev->next = normal.tail; //�������� ����


		patient.head = emergency.head;
		patient.tail = normal.tail; //ť�� ����Ʈ�� �����Ѵ�.



		if (select == 2) //���� �Ϸ�
		{
			if (DQIsEmpty(&patient))
				printf("��� ȯ�ڰ� �����ϴ�. \n");
			else
			{
				printf("%c ȯ���� ���ᰡ �Ϸ�Ǿ����ϴ�. \n", DQRemoveFirst(&patient));

				if (emergency.numOfData != 0)
					(emergency.numOfData)--;
				else if (reserve.numOfData != 0)
					(reserve.numOfData)--;
				else if (normal.numOfData != 0)
					(normal.numOfData)--;

				if (emergency.numOfData == 0)
					emergency.tail->prev = emergency.head;

				if (reserve.numOfData == 0)
					reserve.tail->prev = reserve.head;

				if (normal.numOfData == 0)
					normal.tail->prev = normal.head;

			}
		}

		if (select == 3) //���ȯ�� �� ���
			printf("��� ȯ�� ��: %d \n", LCount(&emergency) + LCount(&reserve) + LCount(&normal));

		if (select == 4) //ȯ���� ����ȣ ���
		{
			pnum = 0;
			if (DQIsEmpty(&patient))
				printf("������� ȯ�ڰ� �����ϴ�. \n");
			else
			{
				while (1)
				{
					printf("ȯ���� �̸��� �Է����ּ���(���ĺ� �빮��): ");
					scanf("%c", &name);
					getchar(); //���� ����

					if (name >= 65 && name <= 90)
						break;
					else
						printf("���� �ùٸ��� �ʽ��ϴ�. ���ĺ� �빮�ڸ� �Է����ּ���. \n\n");
				}

				while (1)
				{
					patient.head = patient.head->next; //��带 �̵��ϸ� Ž��
					pnum++; //����ȣ ����
					if (patient.head->data == name)
					{
						printf("%c ȯ���� ����ȣ�� %d�Դϴ�. \n", name, pnum);
						pnum = 0; //����ȣ �ʱ�ȭ
						patient.head = emergency.head;
						break;
					}

					if (patient.head == patient.tail) // �����Ͱ� ������
					{
						printf("%c ȯ�ڰ� ��ϵǾ����� �ʽ��ϴ�. \n", name);
						pnum = 0;
						patient.head = emergency.head;
						break;
					}

				}
			}

		}

		if (select == 5) // ȯ�� ���� ���
		{
			if (DQIsEmpty(&patient))
				printf("������� ȯ�ڰ� �����ϴ�. \n");
			else
			{
				while (1)
				{
					printf("ȯ���� �̸��� �Է����ּ���(���ĺ� �빮��): ");
					scanf("%c", &name);
					getchar(); //���� ����

					if (name >= 65 && name <= 90)
						break;
					else
						printf("���� �ùٸ��� �ʽ��ϴ�. ���ĺ� �빮�ڸ� �Է����ּ���. \n\n");
				}

				while (1)
				{
					if (patient.head->next->data == name)
					{
						patient.head->next->prev->next = patient.head->next->next;
						printf("%c ȯ���� ���ᰡ ��ҵǾ����ϴ�. \n", DQRemoveFirst(&patient));

						if (emergency.numOfData != 0)
							(emergency.numOfData)--;
						else if (reserve.numOfData != 0)
							(reserve.numOfData)--;
						else if (normal.numOfData != 0)
							(normal.numOfData)--;

						patient.head = emergency.head;
						break;
					}

					patient.head = patient.head->next; //��带 �̵��ϸ� Ž��

					if (patient.head == patient.tail) // �����Ͱ� ������
					{
						printf("%c ȯ�ڰ� ��ϵǾ����� �ʽ��ϴ�. \n", name);
						patient.head = emergency.head;
						break;
					}

				}

			}
		}

		if (select == 6)
		{
			if (DQIsEmpty(&patient))
			{
				printf("������� ȯ�ڰ� �����ϴ�! \n");
				break;
			}
			else
			{
				while (1)
				{

					printf("%c ", DQGetFirst(&patient));

					patient.head = patient.head->next; //��带 �̵��ϸ� Ž��

					if (patient.head->next == patient.tail) // �����Ͱ� ������
					{
						printf("\n[Ž�� ����] \n");
						patient.head = emergency.head;
						break;
					}
				}
			}
		}


		if (select == 7)
		{
			if (DQIsEmpty(&patient))
				printf("���ȯ�ڰ� �����ϴ�! \n");
			else
				printf("������ ���ȯ�ڴ� %c�Դϴ�. \n", DQGetLast(&patient));
		}

		if (select == 8)
		{
			if (DQIsEmpty(&patient))
				printf("���ȯ�ڰ� �����ϴ�! \n");
			else
			{

				while (1)
				{
					printf("ȯ���� �̸��� �Է����ּ���(���ĺ� �빮��): ");
					scanf("%c", &name);
					getchar(); //���� ����

					if (name >= 65 && name <= 90)
						break;
					else
						printf("���� �ùٸ��� �ʽ��ϴ�. ���ĺ� �빮�ڸ� �Է����ּ���. \n\n");
				}

				while (1)
				{
					if (patient.head->next->data == name) //���� ���ȯ�ڰ� �Էµ� ȯ�ڸ�
					{
						if (patient.head->prev == NULL) //ȯ�ڰ� ���� ù��° ���ȯ���� ���
							printf("%c ȯ�ڰ� ù��° ���ȯ���Դϴ�. \n", DQGetFirst(&patient));
						else
							printf("%c ȯ�� �� ���ȯ�ڴ� %c ȯ���Դϴ�. \n", name, patient.head->data);

						break;
					}

					patient.head = patient.head->next; //��带 �̵��ϸ� Ž��

					if (patient.head->next == patient.tail) // �����Ͱ� ������
					{
						printf("ȯ�ڰ� ��ϵǾ����� �ʽ��ϴ�. \n");
						patient.head = emergency.head;
						break;
					}
				}
			}
		}

		if (select == 9)
		{
			if (DQIsEmpty(&patient))
				printf("���ȯ�ڰ� �����ϴ�! \n");
			else
			{
				while (1)
				{
					printf("ȯ���� ����� �Է��ϼ���(1. ���� ȯ�� 2. ���� ȯ�� 3. �Ϲ� ȯ��):");
					scanf("%d", &grade);
					getchar();

					if (grade >= 1 && grade <= 3)
						break;
					else
						printf("1 ~ 3 ������ ���� �Է����ּ���. \n");
				}
				if (grade == 1)
				{
					printf("���� ȯ�� ���: ");
					while (1)
					{
						if (ListIsEmpty(&emergency))
						{
							printf("���� \n");
							break;
						}

						printf("%c ", DQGetFirst(&patient));

						patient.head = patient.head->next; //��带 �̵��ϸ� Ž��

						if (patient.head == emergency.tail->prev) // �����Ͱ� ������
						{
							printf("\n");
							patient.head = emergency.head;
							break;
						}
					}

				}
				else if (grade == 2)
				{
					patient.head = reserve.head;
					printf("���� ȯ�� ���: ");
					while (1)
					{
						if (ListIsEmpty(&reserve))
						{
							printf("���� \n");
							break;
						}

						printf("%c ", DQGetFirst(&patient));

						patient.head = patient.head->next; //��带 �̵��ϸ� Ž��

						if (patient.head == reserve.tail->prev) // �����Ͱ� ������
						{
							printf("\n");
							patient.head = emergency.head;
							break;
						}
					}
				}
				else if (grade == 3)
				{
					patient.head = normal.head;
					printf("�Ϲ� ȯ�� ���: ");
					while (1)
					{
						if (ListIsEmpty(&normal))
						{
							printf("���� \n");
							break;
						}


						printf("%c ", DQGetFirst(&patient));

						patient.head = patient.head->next; //��带 �̵��ϸ� Ž��

						if (patient.head == normal.tail->prev) // �����Ͱ� ������
						{
							printf("\n");
							patient.head = emergency.head;
							break;
						}
					}
				}
			}

		}

	}


	return 0;
}
