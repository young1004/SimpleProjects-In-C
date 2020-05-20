//#include <stdio.h>
//#include <stdlib.h>
//#include "cqueue.h"
//
//int main(void)
//{
//	int minutes = 600;
//	int total_wait = 0;
//	int total_customers = 0;
//	int service_time = 0;
//	int service_customer;
//	int max_wait_time = 0;
//	CQueue queue;
//	init_queue(&queue);
//
//	for (int clock = 0; clock < minutes; clock++) {
//		if ((rand() % 10) < 3) {
//			element customer;
//			customer.id = total_customers++;
//			customer.arrival_time = clock;
//			customer.service_time = rand() % 3 + 1;
//			enqueue(&queue, customer);
//		}
//		if (service_time > 0) {
//			service_time--;
//		}
//		else {
//			if (!is_empty(&queue)) {
//				element customer = dequeue(&queue);
//				service_customer = customer.id;
//				service_time = customer.service_time;
//				total_wait += clock - customer.arrival_time;
//				if (max_wait_time <= clock - customer.arrival_time)
//					max_wait_time = clock - customer.arrival_time;
//			}
//		}
//	}
//	printf("�ùķ��̼� �ð� = %d\n", minutes);
//	printf("��ü �� �� = %d\n", total_customers);
//	printf("��� ��� �ð� = %0.1lf\n", (double)total_wait / (double)total_customers);
//	printf("�ִ� ��� �ð� = %d\n", max_wait_time);
//	return 0;
//}