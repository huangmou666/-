#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include<iostream>
using namespace std;
#include<stdlib.h>
#define MAX 0
#define MVNum 100
int visited1[MVNum];
int visited2[MVNum];

//�ڽӾ���
typedef struct
{
	char vexs[100];
	int arcs[100][100];
	int vexnum, arcnum;
}AMGraph;

//�ڽӱ�
typedef struct ArcNode {
	int adjvex;
	struct ArcNode* nextarc;
}ArcNode;
typedef struct VNode
{
	int data;
	ArcNode* firstarc;
}Vnode, AdjList[MVNum];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;

//�ڽӾ���
int LocateVexUDN(AMGraph G, int v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (v == G.vexs[i])
			return i;
}
int CreateUDN(AMGraph& G) {
	int i, j, k, w, v1, v2;
	printf("���붥�����ͱ���:");
	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	printf("���������Ϣ: ");
	for (i = 0; i < G.vexnum; i++)
		scanf_s("%d", &G.vexs[i]);
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = MAX;
	for (k = 0; k < G.arcnum; k++)
	{
		printf("�����(vi,vj)�ϵ��±�i,�±�j��Ȩw:");
		cin >> v1 >> v2 >> w;
		i = LocateVexUDN(G, v1);
		j = LocateVexUDN(G, v2);
		G.arcs[i][j] = w;
		G.arcs[j][i] = G.arcs[i][j];
	}
	return 1;
}
void ShowUND(AMGraph& G)
{
	int i, j;
	printf("\t");
	for (i = 0; i < G.vexnum; i++)
		printf("%d\t", G.vexs[i]);
	printf("\n");
	for (i = 0; i < G.vexnum; i++)
	{
		printf("%d\t", G.vexs[i]);
		for (j = 0; j < G.vexnum; j++)
			printf("%d\t", G.arcs[i][j]);
		printf("\n");
	}
}
void DFS(AMGraph G, int v)
{
	int w;
	printf("%d->", G.vexs[v]); visited1[v] = 1;
	for (w = 0; w < G.vexnum; w++)
	{
		if ((G.arcs[v][w] != 0) && (!visited1[w]))
			DFS(G, w);
	}
}
void DFSTraverse(AMGraph G) {
	printf("\n������ȱ���˳��Ϊ��");
	for (int v = 0; v < G.vexnum; ++v)
		visited1[v] = 0;
	for (int v = 0; v < G.vexnum; ++v)
	{
		if (!visited1[v])
			DFS(G, v);
	}
}
//�ڽӱ�
int CreateUDG(ALGraph& T) {
	int a, b, i;
	ArcNode* s, * s2;
	printf("�����붥��ͱ���:");
	scanf_s("%d%d", &T.vexnum, &T.arcnum);
	printf("��������");
	for (i = 1; i < T.vexnum + 1; i++)
	{
		scanf_s("%d", &T.vertices[i].data);
		T.vertices[i].firstarc = NULL;
	}
	for (i = 1; i < T.arcnum + 1; i++)
	{
		printf("�����������ӵĶ���:");
		scanf_s("%d%d", &a, &b);
		s = (ArcNode*)malloc(sizeof(ArcNode));
		s->adjvex = b;
		s->nextarc = T.vertices[a].firstarc;
		T.vertices[b].firstarc = s;
	}
	return 1;
}
void ShowUDG(ALGraph T)
{
	for (int i = 1; i < T.vexnum + 1; i++)
	{
		cout << "����" << i << "����ͨ�Ľ����: ";
		while (1)
		{
			if (T.vertices[i].firstarc == NULL)
			{
				cout << "^";
				break;
			}
			cout << T.vertices[i].firstarc->adjvex;
			T.vertices[i].firstarc = T.vertices[i].firstarc->nextarc;
		}
		cout << "\n";
	}
}
void BFS(ALGraph G, int v) {
	ArcNode* p;
	int j, que[MVNum], front = 0, rear = 0;
	printf("%d ", G.vertices[v].data);
	visited2[v] = true;
	rear = (rear + 1) % MVNum;
	que[rear] = v;
	while (front != rear)
	{
		front = (front + 1) % MVNum;
		j = que[front];
		p = G.vertices[j].firstarc;
		while (p != NULL)
		{
			if (visited2[p->adjvex] == 0)
			{
				printf("%d ", p->adjvex);
				visited2[p->adjvex] = 1;
				rear = (rear + 1) % MVNum;
				que[rear] = p->adjvex;
			}
			p = p->nextarc;
		}
	}
}
void BFSTravel(ALGraph G)
{
	int i;
	printf("\n������ȱ���˳��Ϊ��");
	for (i = 1; i < G.vexnum + 1; i++)
	{
		if (visited2[i] == 0)
			BFS(G, i);
	}
}
int main()
{
	ALGraph T;
	AMGraph G;
	printf("�ڽӾ�����Ϣ:\n");
	CreateUDN(G);        //�ڽӾ���
	ShowUND(G);
	printf("\n");
	DFSTraverse(G);
	printf("\n\n");
	printf("�ڽӱ���Ϣ:\n");
	CreateUDG(T);
	ShowUDG(T);
	printf("\n");
	BFSTravel(T);
}