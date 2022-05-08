#include<iostream>
#include<stack>
#include<queue>
using namespace std;
struct Edge
{
	Edge* next;
	int adj;
	int wight;
};
struct Adv
{
	int in;
	char data;
	Edge* first;
};
struct AMGmap
{
	Adv* map;
	int advNum, arcNum;
};
bool Choose_data(AMGmap* map, int x);
bool toopSelete(AMGmap* T);
bool toopSelete(AMGmap* T);
void ImportantRoad(const AMGmap* map);
AMGmap * BuildAMGmap()
{
	cout << "你需要多少个顶点\n";
	int temp;
	cin >> temp;
	AMGmap* map = new AMGmap;
	map->advNum = temp;
	map->map = new Adv[temp];
	for (int i = 0; i < temp; i++)
	{
		cout << "请输入你的顶点\n";
		cin >> map->map[i].data;
		map->map[i].first = NULL;
		map->map[i].in = 0;
	}
	cout << "请输入你需要链接多少条边\n";
	int temp2 = 0; cin >> temp2;
	map->arcNum = temp2;
	for (int i = 0; i < temp2; i++)
	{
		for (int c = 0; c < map->advNum; c++)
		{
			cout << map->map[c].data << " ";
		}
		cout << "\n";
		cout << "请输入你想链接的两点(输入数字即可,左边的数字链接下一个顶点)\n";
		int x, y;
		cin >> x >> y;
		if (Choose_data(map, x) == false) {
			Edge* newNode = new Edge;
			newNode->adj = y;
			map->map[x].first = newNode;
			newNode->next = NULL;
			cout << "请输入其权值\t";
			cin >> newNode->wight;
			map->map[y].in++;
		}
		else {
			for (int t = 0; t < temp; t++)
			{
				Edge* T = map->map[t].first;
				while (T != NULL)
				{
					if (T->adj == x && T->next == NULL)
					{
						Edge* newNode = new Edge;
						T->next = newNode;
						cout << "请输入其权值\t";
						cin >> newNode->wight;
						newNode->next = NULL;
						newNode->adj = y;
						map->map[y].in++;
					}
					T = T->next;
				}
			}
		}
	}
	cout << "建立完成\n";
	system("cls");
	return map;
}
bool Choose_data(AMGmap* map, int x)
{
	if (map->map[x].first == NULL) { return false; }
	else {
		return true;
	}
}
int main()
{
	AMGmap* T = BuildAMGmap();
	for (int i = 0; i < T->advNum; i++)
	{
		cout << T->map[i].data << "-->";
		Edge* X = T->map[i].first;
		while (X != NULL)
		{
			cout << T->map[X->adj].data << "-->";
			X = X->next;
		}
		cout << "NULL";
		cout << "\n";
	}
	for (int c = 0; c < T->advNum; c++)
	{
		cout << T->map[c].in << " ";
	}
	cout << "\n";
	ImportantRoad(T);
}
//拓扑排序
bool toopSelete(const AMGmap* T)
{
	int sum=0;
	int count = 0;
	queue<int>S;
	for (int i = 0; i < T->advNum; i++)
	{
		if (T->map[i].in == 0) { S.push(i); }
	}
	while (!S.empty())
	{
		sum = S.front();
		cout << T->map[sum].data << " ";
		count++;
		for (auto e = T->map[sum].first; e != NULL; e = e->next)
		{
			auto k = e->adj;
			if (--T->map[k].in == 0) { S.push(k); }
		}
		S.pop();
	}
	if (count == T->advNum) { return true; }
	else {
		return false;
	}
}
void ImportantRoad(const AMGmap *map)//关键路径
{
	int* Path = new int[map->advNum];
	int top1 = 0;
	int count = 0;
	for (int i = 0; i < map->advNum; i++)
	{
		Path[i] = 0;
	}
	queue<int>T; queue<int>S;
	for (int i = 0; i < map->advNum; i++)
	{
		if (map->map[i].in == 0) { T.push(i); }
	}
	while (!T.empty())
	{
		top1 = T.front();
		count++;
		S.push(top1);
		for (auto e = map->map[top1].first; e != NULL; e = e->next)
		{
			int j = e->adj;
			if (map->map[j].in-- == 0) { T.push(j); }
			if (Path[top1] + e->wight > Path[j]) {
				Path[j] = Path[top1] + e->wight;
			}
		}
		T.pop();
	}
	while (!S.empty())
	{
		cout << S.front();
		S.pop();
	}
}

