#include<iostream>
#include<Windows.h>
#include<queue>
#define None NULL
#define MaxVers 20
using namespace std;
struct ArcNode
{
	int adjVers;
	ArcNode* next;
	int weight;//Ȩ��
};
struct Ver
{
	char VerName;
	ArcNode* firstarc;
};
struct AMGMap
{
	Ver* MapTree;
	int versNum, arcsNum;
};
int LocalVar(AMGMap& Map, char v);
void CreatAMGMap(AMGMap& Map)
{
	cout << "����������Ҫ�Ķ���\n";
	int temp;
	cin >> temp;
	Map.versNum = temp;
	Map.MapTree = new Ver[temp];
	cout << "����������Ҫ�ı�\n";
	cin >> temp;
	Map.arcsNum = temp;
	cout << "����������ǵ�����\n";
	for (int i = 0; i < Map.versNum; i++)
	{
		cout << "������\n";
		cin >> Map.MapTree[i].VerName;
		Map.MapTree[i].firstarc = new ArcNode;
		Map.MapTree[i].firstarc->next = NULL;
		Map.MapTree[i].firstarc->adjVers = i;
		Map.MapTree[i].firstarc->weight = 0;
	}
	cout << "����ɹ�\n";
	Sleep(300); system("cls");
	for (int i = 0; i < Map.arcsNum; i++)
	{
		cout << "��Ӧ�ĽǱ�����\n";
		for (int c = 0; c < Map.versNum; c++)
		{
			cout << Map.MapTree[c].VerName<<" ";
		}
		cout << "\n";
		cout << "�������Ӧ�ıߣ������������ּ��ɣ�\n";
		char v, y;
		cin >> v >> y;
		int v1 = LocalVar(Map, v); int v2 = LocalVar(Map, y);
		cout << "�����������Ȩֵ\n";
		int weight;
		cin >> weight;
		ArcNode* NewNode1 = new ArcNode;
		NewNode1->adjVers = v2;
		NewNode1->weight = weight;
		NewNode1->next = Map.MapTree[v1].firstarc;
		Map.MapTree[v1].firstarc = NewNode1;
		ArcNode* NewNode2 = new ArcNode;
		NewNode2->adjVers = v1;
		NewNode2->weight = weight;
		NewNode2->next = Map.MapTree[v2].firstarc;
		Map.MapTree[v2].firstarc = NewNode2;
		Sleep(400);
		system("cls");
	}
}
//��λ���ڱ��е�λ��
int LocalVar(AMGMap& Map, char v)
{
	bool T = false; int c = 0;
	for (int i = 0; i < Map.versNum; i++)
	{
		if (v == Map.MapTree[i].VerName) { return i; }
	}
	return -1;
}
bool* LOOK;
void buildLook(AMGMap map)
{
	LOOK = new bool[map.versNum];
	for (int i = 0; i < map.versNum; i++)
	{
		LOOK[i] = false;
	}
}
void DFS_AL(AMGMap map, int v)
{
	cout << map.MapTree[v].VerName;
	LOOK[v] = true;
	auto T = map.MapTree[v].firstarc;
	while (T != NULL)
	{
		auto w = T->adjVers;
		if (LOOK[w] != true) { DFS_AL(map, w);  }
		T = T->next;
	}
}
bool* BFS_visit;
void build_BFS(AMGMap map)
{
	BFS_visit = new bool[map.versNum];
	for (int i = 0; i < map.versNum; i++)
	{
		BFS_visit[i] = false;
	}
}
void BFS_LOOK(AMGMap map, int v)
{
	queue<ArcNode*>T;
	T.push(map.MapTree[v].firstarc);
	while (!T.empty())
	{
		auto Temp = T.front();
		cout << map.MapTree[Temp->adjVers].VerName;
		while (Temp != NULL) {
			if (BFS_visit[Temp->adjVers] != true) { T.push(map.MapTree[Temp->adjVers].firstarc); }
			Temp = Temp->next;
		}
		BFS_visit[Temp->adjVers] = true;
		T.pop();
	}
}
//����ķ�㷨

int main()
{
	AMGMap Map;
	CreatAMGMap(Map);
	for (int i = 0; i < Map.versNum; i++)
	{
		cout << Map.MapTree[i].VerName<<" ";
	}
	cout << endl;
	for (int i = 0; i < Map.versNum; i++)
	{
		ArcNode *Temp = Map.MapTree[i].firstarc;
		while (Temp != NULL)
		{
			cout << Map.MapTree[Temp->adjVers].VerName << "__" << Temp->weight << "__--->" << " ";
			Temp = Temp->next;
		}
		cout << "\n";
	}
	buildLook(Map);
	DFS_AL(Map, 0);
}