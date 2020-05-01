#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BROKEN -1
#define INF 5000

void dijkstra(int** arr, int from, int to, int nc);

int main(void)
{
	int nc; // 파일에서 입력받을 노드(정점)의 수
	int** arr; // 노드의 연결 정보를 저장할 변수
	int i, j; // 반복문을 위한 변수
	int from, to; // 시작 라우터와 도착 라우터를 입력받을 변수
	int tmp;

	FILE* init;

	init = fopen("init.txt", "r");

	if (init == NULL) {
		printf("\n파일을 읽어오지 못하였습니다.\n");
		return 1;
	}

	fscanf(init, "%d\n", &nc); //노드의 수에 따라 배열을 생성하기 위해 입력받음

	/*2차원 배열 동적 할당(LSDB 테이블을 저장할 배열)*/
	arr = (int**)malloc(sizeof(int*) * (nc + 1));
	for (i = 0; i <= nc; i++)
		arr[i] = (int*)calloc(nc + 1, sizeof(int));

	for (i = 1; i <= nc; i++) {
		for (j = 1; j <= nc; j++) {
			fscanf(init, "%d,", &tmp);

			if (tmp == BROKEN)
				arr[i][j] = INF;
			else
				arr[i][j] = tmp;
		}
		fscanf(init, "\n");
	}

	printf("출발 라우터, 도착 라우터 입력 (범위 : 1~%d 의 정수) : ", nc);
	scanf("%d %d", &from, &to);

	dijkstra(arr, from, to, nc);

	/*메모리 해제*/
	for (i = 0; i <= nc; i++)
		free(arr[i]);
	free(arr);

	//파일 닫기
	fclose(init);

	return 0;
}

/*다익스트라 알고리즘으로 최단 경로를 구하는 함수*/
void dijkstra(int** arr, int from, int to, int nc)
{
	int** dist; // 거리를 저장할 변수
	int** tmp;
	int* next; //다음 라우터를 저장할 변수
	int* path; //경로를 저장할 변수
	bool** visit; // 각 경로에 대해 방문 여부를 표시할 boolean 변수
	int i, j, k; //반복문을 위한 변수
	int min = 0; // 최소 거리를 저장할 변수
	int vertex = 0; //방문중인 정점을 저장할 변수

	/*방문 여부, 거리, 경로를 표시할 배열 동적 할당, 0으로 초기화*/
	tmp = (int**)malloc(sizeof(int*) * (nc + 1));
	for (i = 0; i <= nc; i++)
		tmp[i] = (int*)calloc(nc + 1, sizeof(int));
	dist = (int**)malloc(sizeof(int*) * (nc + 1));
	for (i = 0; i <= nc; i++)
		dist[i] = (int*)calloc(nc + 1, sizeof(int));
	visit = (bool**)malloc(sizeof(bool*) * (nc + 1));
	for (i = 0; i <= nc; i++)
		visit[i] = (bool*)calloc(nc + 1, sizeof(bool));
	path = (int*)calloc(nc + 1, sizeof(int));
	next = (int*)calloc(nc + 1, sizeof(int));

	for (i = 1; i <= nc; i++)
		for (j = 1; j <= nc; j++)
			dist[i][j] = INF;

	for (i = 1; i <= nc; i++)
		dist[i][i] = 0;

	/*다익스트라 알고리즘*/
	for (i = 1; i <= nc; i++) {
		for (j = 1; j <= nc; j++) {
			min = INF;
			for (k = 1; k <= nc; k++) {
				if (dist[i][k] < min && visit[i][k] == false) {
					min = dist[i][k];
					vertex = k;
				}
			}

			visit[i][vertex] = true;
			for (k = 1; k <= nc; k++) {
				if (dist[i][vertex] + arr[vertex][k] < dist[i][k]) {
					dist[i][k] = dist[i][vertex] + arr[vertex][k]; //거리 갱신
					tmp[i][k] = vertex; //최소거리로 오기위해 거쳐야 할 전 노드를 저장
				}
			}
		}
	}

	//경로를 역추적하여 반대로 저장
	vertex = to;
	path[0] = to;
	while (tmp[from][vertex] != 0)
	{
		for (i = nc - 1; i > 0; i--)
			path[i] = path[i - 1];
		path[0] = tmp[from][vertex];
		vertex = tmp[from][vertex];
	}

	printf("Path : ");
	for (i = 0; i < nc; i++) {
		if (path[i + 1] == 0) {
			printf("%d", path[i]);
			break;
		}
		else
			printf("%d-", path[i]);
	}

	printf(" / Cost : %d\n", dist[from][to]);

	for (i = 1; i <= nc; i++) {
		next[i] = i;
		for (j = 1; j <= nc; j++) {
			vertex = j;
			while (tmp[i][vertex] != 0) {
				next[j] = vertex;
				vertex = tmp[i][vertex];
			}
		}

		printf("[라우터 %d의 라우팅 테이블]\n", i);
		printf("Node\tCost\tNextHop\n");
		for (k = 1; k <= nc; k++) {
			if (next[k] == i)
				printf("%d\t%d\t-\n", k, dist[i][k]);
			else if (k == next[k])
				printf("%d\t%d\tdirectly\n", k, dist[i][k]);
			else
				printf("%d\t%d\t%d\n", k, dist[i][k], next[k]);
		}
	}

	/*메모리 해제*/
	for (i = 0; i <= nc; i++)
		free(tmp[i]);
	free(tmp);
	for (i = 0; i <= nc; i++)
		free(dist[i]);
	free(dist);
	for (i = 0; i <= nc; i++)
		free(visit[i]);
	free(visit);
	free(path);
}