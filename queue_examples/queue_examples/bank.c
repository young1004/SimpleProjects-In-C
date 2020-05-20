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
//	printf("시뮬레이션 시간 = %d\n", minutes);
//	printf("전체 고객 수 = %d\n", total_customers);
//	printf("평균 대기 시간 = %0.1lf\n", (double)total_wait / (double)total_customers);
//	printf("최대 대기 시간 = %d\n", max_wait_time);
//	return 0;
//}