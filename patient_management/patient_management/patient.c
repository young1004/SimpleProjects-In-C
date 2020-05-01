#include <stdio.h>
#include <string.h>
#include "DBDLinkedList.h"
#include "Deque.h"

int main(void)
{
	List emergency; //응급 환자
	List reserve; //예약 환자
	List normal; //일반 환자

	Deque patient;//환자 전체

	int select;//번호 선택
	int grade;// 환자 등급
	int pnum = 0;//환자 번호
	char name;//환자 이름

	ListInit(&emergency);
	ListInit(&reserve);
	ListInit(&normal);

	DequeInit(&patient);

	printf("--------------------------------------------\n");
	printf("            환자 관리 프로그램 \n");
	printf("--------------------------------------------\n");
	printf("1. 환자 추가 \n");
	printf("2. 환자 진료 완료 \n");
	printf("3. 대기환자 수 출력 \n");
	printf("4. 환자 대기번호 출력 \n");
	printf("5. 환자 진료 취소 \n");
	printf("6. 대기환자 목록 출력 \n");
	printf("7. 마지막 대기 환자 출력 \n");
	printf("8. 다음 진료 환자 출력 \n");
	printf("9. 등급별 환자 출력 \n");
	printf("10. 프로그램 종료 \n");
	printf("--------------------------------------------\n");


	while (1)
	{
		printf("숫자를 입력하세요: ");

		scanf("%d", &select);
		getchar();

		if (select == 10) //프로그램 종료
		{
			printf("프로그램 종료. \n");
			break;
		}


		if (select == 1) //환자 추가
		{

			while (1)
			{
				printf("환자의 상태를 입력하세요(1.응급, 2.예약, 3.일반): ");
				scanf("%d", &grade);
				getchar(); //버퍼 비우기

				if (grade >= 1 && grade <= 3)
					break;
				else
					printf("값이 올바르지 않습니다. 1~3사이의 수를 입력해주세요. \n\n");
			}

			while (1)
			{
				printf("환자의 이름을 입력하세요(알파벳 대문자): ");
				scanf("%c", &name);
				getchar(); //버퍼 비우기

				if (name >= 65 && name <= 90)
					break;
				else
					printf("값이 올바르지 않습니다. 알파벳 대문자를 입력해주세요. \n\n");
			}

			if (grade == 1)
				LInsert(&emergency, name);
			else if (grade == 2)
				LInsert(&reserve, name);
			else if (grade == 3)
				LInsert(&normal, name);

		}

		if (LFirst(&reserve, &name))//예약환자가 있으면
		{
			emergency.tail->prev->next = reserve.head->next;//예약환자와 연결

			if (LFirst(&normal, &name))//일반환자도있으면
				reserve.tail->prev->next = normal.head->next;//일반환자와 연걸
			else
				reserve.tail->prev->next = normal.tail;//없으면 꼬리에 연결
		}
		else if (LFirst(&normal, &name)) //예약환자가 없고 일반환자는 있으면
			emergency.tail->prev->next = normal.head->next;
		else //둘다 없으면
			emergency.tail->prev->next = normal.tail; //꼬리노드와 연결


		patient.head = emergency.head;
		patient.tail = normal.tail; //큐에 리스트를 저장한다.



		if (select == 2) //진료 완료
		{
			if (DQIsEmpty(&patient))
				printf("대기 환자가 없습니다. \n");
			else
			{
				printf("%c 환자의 진료가 완료되었습니다. \n", DQRemoveFirst(&patient));

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

		if (select == 3) //대기환자 수 출력
			printf("대기 환자 수: %d \n", LCount(&emergency) + LCount(&reserve) + LCount(&normal));

		if (select == 4) //환자의 대기번호 출력
		{
			pnum = 0;
			if (DQIsEmpty(&patient))
				printf("대기중인 환자가 없습니다. \n");
			else
			{
				while (1)
				{
					printf("환자의 이름을 입력해주세요(알파벳 대문자): ");
					scanf("%c", &name);
					getchar(); //버퍼 비우기

					if (name >= 65 && name <= 90)
						break;
					else
						printf("값이 올바르지 않습니다. 알파벳 대문자를 입력해주세요. \n\n");
				}

				while (1)
				{
					patient.head = patient.head->next; //헤드를 이동하며 탐색
					pnum++; //대기번호 증가
					if (patient.head->data == name)
					{
						printf("%c 환자의 대기번호는 %d입니다. \n", name, pnum);
						pnum = 0; //대기번호 초기화
						patient.head = emergency.head;
						break;
					}

					if (patient.head == patient.tail) // 데이터가 없으면
					{
						printf("%c 환자가 등록되어있지 않습니다. \n", name);
						pnum = 0;
						patient.head = emergency.head;
						break;
					}

				}
			}

		}

		if (select == 5) // 환자 진료 취소
		{
			if (DQIsEmpty(&patient))
				printf("대기중인 환자가 없습니다. \n");
			else
			{
				while (1)
				{
					printf("환자의 이름을 입력해주세요(알파벳 대문자): ");
					scanf("%c", &name);
					getchar(); //버퍼 비우기

					if (name >= 65 && name <= 90)
						break;
					else
						printf("값이 올바르지 않습니다. 알파벳 대문자를 입력해주세요. \n\n");
				}

				while (1)
				{
					if (patient.head->next->data == name)
					{
						patient.head->next->prev->next = patient.head->next->next;
						printf("%c 환자의 진료가 취소되었습니다. \n", DQRemoveFirst(&patient));

						if (emergency.numOfData != 0)
							(emergency.numOfData)--;
						else if (reserve.numOfData != 0)
							(reserve.numOfData)--;
						else if (normal.numOfData != 0)
							(normal.numOfData)--;

						patient.head = emergency.head;
						break;
					}

					patient.head = patient.head->next; //헤드를 이동하며 탐색

					if (patient.head == patient.tail) // 데이터가 없으면
					{
						printf("%c 환자가 등록되어있지 않습니다. \n", name);
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
				printf("대기중인 환자가 없습니다! \n");
				break;
			}
			else
			{
				while (1)
				{

					printf("%c ", DQGetFirst(&patient));

					patient.head = patient.head->next; //헤드를 이동하며 탐색

					if (patient.head->next == patient.tail) // 데이터가 없으면
					{
						printf("\n[탐색 종료] \n");
						patient.head = emergency.head;
						break;
					}
				}
			}
		}


		if (select == 7)
		{
			if (DQIsEmpty(&patient))
				printf("대기환자가 없습니다! \n");
			else
				printf("마지막 대기환자는 %c입니다. \n", DQGetLast(&patient));
		}

		if (select == 8)
		{
			if (DQIsEmpty(&patient))
				printf("대기환자가 없습니다! \n");
			else
			{

				while (1)
				{
					printf("환자의 이름을 입력해주세요(알파벳 대문자): ");
					scanf("%c", &name);
					getchar(); //버퍼 비우기

					if (name >= 65 && name <= 90)
						break;
					else
						printf("값이 올바르지 않습니다. 알파벳 대문자를 입력해주세요. \n\n");
				}

				while (1)
				{
					if (patient.head->next->data == name) //다음 대기환자가 입력된 환자면
					{
						if (patient.head->prev == NULL) //환자가 가장 첫번째 대기환자일 경우
							printf("%c 환자가 첫번째 대기환자입니다. \n", DQGetFirst(&patient));
						else
							printf("%c 환자 앞 대기환자는 %c 환자입니다. \n", name, patient.head->data);

						break;
					}

					patient.head = patient.head->next; //헤드를 이동하며 탐색

					if (patient.head->next == patient.tail) // 데이터가 없으면
					{
						printf("환자가 등록되어있지 않습니다. \n");
						patient.head = emergency.head;
						break;
					}
				}
			}
		}

		if (select == 9)
		{
			if (DQIsEmpty(&patient))
				printf("대기환자가 없습니다! \n");
			else
			{
				while (1)
				{
					printf("환자의 등급을 입력하세요(1. 응급 환자 2. 예약 환자 3. 일반 환자):");
					scanf("%d", &grade);
					getchar();

					if (grade >= 1 && grade <= 3)
						break;
					else
						printf("1 ~ 3 사이의 수를 입력해주세요. \n");
				}
				if (grade == 1)
				{
					printf("응급 환자 목록: ");
					while (1)
					{
						if (ListIsEmpty(&emergency))
						{
							printf("없음 \n");
							break;
						}

						printf("%c ", DQGetFirst(&patient));

						patient.head = patient.head->next; //헤드를 이동하며 탐색

						if (patient.head == emergency.tail->prev) // 데이터가 없으면
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
					printf("예약 환자 목록: ");
					while (1)
					{
						if (ListIsEmpty(&reserve))
						{
							printf("없음 \n");
							break;
						}

						printf("%c ", DQGetFirst(&patient));

						patient.head = patient.head->next; //헤드를 이동하며 탐색

						if (patient.head == reserve.tail->prev) // 데이터가 없으면
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
					printf("일반 환자 목록: ");
					while (1)
					{
						if (ListIsEmpty(&normal))
						{
							printf("없음 \n");
							break;
						}


						printf("%c ", DQGetFirst(&patient));

						patient.head = patient.head->next; //헤드를 이동하며 탐색

						if (patient.head == normal.tail->prev) // 데이터가 없으면
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
