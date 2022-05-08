#include<iostream>
#include<Windows.h>
#include<queue>
#define MaxInt 0
#define MaxNum 20
#define Max 35125
using namespace std;
struct Amgmap
{
	char vers[MaxNum];//顶点表
	int arcs[MaxNum][MaxNum];//权值表
	int versNum, arcsNum;
	Amgmap(int vers, int arcs) :versNum(vers), arcsNum(arcs) {};
};
//创建对应的顶点网络
Amgmap BuildVerWeb(Amgmap Map)
{
	for (int i = 0; i < Map.versNum; i++)
	{
		cout << "请输入此点的名字\n";
		cin >> Map.vers[i];
	}
	cout << "创建完毕\n";
	return Map;
}
//初始化边的权值
Amgmap BuildArcsWeb_None(Amgmap Map)
{
	for (int i = 0; i < Map.versNum; i++)
	{
		for (int c = 0; c < Map.versNum; c++)
		{
			if (i == c) { Map.arcs[i][c] = 0; }
			else {
				Map.arcs[i][c] = Max;
			}
		}
	}
	Sleep(100);
	cout << "现在开始创建无向图\n";
	for (int i = 0; i < Map.arcsNum; i++)
	{
		cout << "请输入你需要链接的两点\t";
		int x, y,wight;
		cin >> x >> y;
		cout << "请输入你需要的权值\t";
		cin >> wight;
		Map.arcs[x][y] = wight;
		Map.arcs[y][x] = wight;
		cout << "创建成功\n";
	}
	cout << "全部创建完成\n";
	return Map;
}
bool* visiten;
void build( Amgmap map)
{
	visiten = new bool[map.versNum];
	for (int i = 0; i < map.versNum; i++)
	{
		visiten[i] = false;
	}
}
void DFS_Map(Amgmap Map,int v)
{
	cout << Map.vers[v]<<" "; visiten[v] = true;
	for ( int j = 0; j < Map.versNum; j++)
	{
		if (Map.arcs[v][j] != Max && visiten[j] != true) { DFS_Map(Map, j); }
	}
	cout << "\n";
}
bool* BFS_visit;
void buildBFS_visit(Amgmap map)
{
	BFS_visit = new bool[map.versNum];
	for (int i = 0; i < map.versNum; i++)
	{
		BFS_visit[i] = false;
	}
}
void look_BFS(Amgmap map, int v)
{
	queue<int>T;
	T.push(v);
	cout << "\n";
	while (!T.empty())
	{
		int temp = T.front();
		cout << map.vers[temp]<<" ";
		for (int c = 0; c < map.versNum; c++)
		{
			if (map.arcs[temp][c] != MaxInt && BFS_visit[c] != true) { T.push(c); }
		}
		BFS_visit[temp] = true;
		T.pop();
	}
}
void MinTree_Prim(Amgmap map)
{
	system("cls");
	int min, i, j, k;
	int sum = 0;
	int* adjvex = new int[map.versNum];
	int* lowcoat = new int[map.versNum];
	for (i = 0; i < map.versNum; i++)
	{
		lowcoat[i] = map.arcs[0][i];
		adjvex[i] = 0;
	}
	lowcoat[0] = 0;
	adjvex[0] = 0;
	for (i = 0; i < map.versNum-1; i++)
	{
		min = Max;
		j = 1; k = 0;
		while (j < map.versNum) {
			if (lowcoat[j] != 0 && lowcoat[j] < min)
			{
				min = lowcoat[j]; k = j;
			}
			j++;
		}
		cout<<"(" << adjvex[k]<<","<<k<<")"<<lowcoat[k]<<endl;
		sum = sum + lowcoat[k];
		lowcoat[k] = 0;
		for (j = 1; j < map.versNum; j++)
		{
			if (lowcoat[j] != 0 && map.arcs[k][j] < lowcoat[j])
			{
				lowcoat[j] = map.arcs[k][j];
				adjvex[j] = k;
			}
		}
	}
	cout << "总权值是" << sum << endl;
}
//克鲁斯卡尔算法
struct Edge
{
	int begin; int end;
	int weight;
};
Edge* buildEdge(Amgmap map)
{
	Edge* Dj = new Edge[map.arcsNum];
	int Z = 0;
	for (int i = 0; i < map.versNum; i++)
	{
		for (int y = i; y < map.versNum; y++)
		{
			if (map.arcs[i][y] != 0 && map.arcs[i][y] != Max)
			{
				Dj[Z].begin = i;
				Dj[Z].end = y;
				Dj[Z++].weight = map.arcs[i][y];
			}
		}
	}
	//排序
	for (int i = 0; i < map.arcsNum-1; i++)
	{
		int end = i;
		Edge Temp = Dj[end + 1];
		while (end >= 0)
		{
			if (Temp.weight < Dj[end].weight)
			{
				Dj[end + 1] = Dj[end];
				end--;
			}
			else { break; }
		}
		Dj[end + 1] = Temp;
	}
	return Dj;
}
int Find(int* parent, int v)
{
	while (parent[v] > 0)
	{
		v = parent[v];
	}
	return v;
}
void KerusiKaer(Amgmap map, Edge *T)
{
	int i, j, k;
	int* parent = new int[map.versNum];
	for (i = 0; i < map.versNum; i++)
	{
		parent[i] = 0;
	}
	for (i = 0; i < map.arcsNum; i++)
	{
		j = Find(parent, T[i].begin);
		k = Find(parent, T[i].end);
		if (j != k)
		{
			parent[j] = k;
			cout << "(" << T[i].begin << "," << T[i].end << ")" << T[i].weight << endl;
		}
	}
}
int main()
{
	cout << "请输入你需要的顶点数和边数\n";
	int vers, arcs;
	cin >> vers >> arcs;
	Amgmap Map(vers, arcs);
	Map=BuildVerWeb(Map);
	Map=BuildArcsWeb_None(Map);
	for (int i = 0; i < Map.versNum; i++)
	{
		cout << Map.vers[i] << " ";
	};
	cout << "\n";
	for (int i = 0; i < Map.versNum; i++)
	{
		for (int c = 0; c < Map.versNum; c++)
		{
			cout << Map.arcs[i][c] << " ";
		}
		cout << "\n";
	}
	build(Map);
	DFS_Map(Map, 0);
	buildBFS_visit(Map);
	look_BFS(Map, 0);
	MinTree_Prim(Map);
	Edge *T=buildEdge(Map);
	KerusiKaer(Map, T);
}
