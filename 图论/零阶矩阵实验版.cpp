#include<iostream>
#include<queue>
#include<winsock.h>
using namespace std;
#define MaxInt 10
#define Max 35525
struct Edge
{
	int right;
	int left;
	int weight;
};
class Amgmap
{
public:
	Amgmap();
	int VerNum;
	int ArcsNum;
	char Ver[MaxInt];
	int Arcs[MaxInt][MaxInt];
	void Pulim(int start);
	void KrirusiKaer();
	int Find_KrirusiKaer(int *parent,int v);
	void MyChoose();//自己创造的算法计算;
	void DjsiTela(int v0);
	void BuildPath();
	void FuluouiDe();//弗洛伊德
	Edge* T;
};

Amgmap::Amgmap()
{
	cout << "请输入你需要建立的点的数目\n";
	cin >> Amgmap::VerNum;
	cout << "请输入你需要建立的边的数目\n";
	cin >> Amgmap::ArcsNum;
	Amgmap::T = NULL;
	for (int i = 0; i < VerNum; i++)
	{
		cout << "请输入你需要的点\t";
		cin >> Ver[i];
	}
	for (int i = 0; i < VerNum; i++)
	{
		for (int c = 0; c < VerNum; c++)
		{
			if (i != c) { Amgmap::Arcs[i][c] = Max; }
			else { Amgmap::Arcs[i][c] = 0; }
		}
	}
	int x, y,weight;
	for (int i = 0; i < Amgmap::ArcsNum; i++)
	{
		cout << "请输入你需要的两个点\n";
		cin >> x >> y;
		cout << "请输入你需要的权值\n";
		cin >> weight;
		Amgmap::Arcs[x][y] = weight;
		Amgmap::Arcs[y][x] = weight;
	}
	cout << "建立完成\n";
	system("cls");
}
void Amgmap::Pulim(int start)
{
	int min, x, y;
	int* adjVer = new int[Amgmap::VerNum];
	int* Lowcost = new int[Amgmap::VerNum];
	for (int i = 0; i < VerNum; i++)
	{
		adjVer[i] = start;
		Lowcost[i] = Amgmap::Arcs[start][i];
	}
	Lowcost[start] = 0;
	for (int i = 0; i < VerNum - 1; i++)
	{
		min = Max;
		x = 0; y = 0;
		while (x < VerNum)
		{
			if (Lowcost[x] != 0 && Lowcost[x] < min)
			{
				min = Lowcost[x];
				y = x;
			}
			x++;
		}
		cout << "(" << adjVer[y] << "," << y << ")" << Lowcost[y] << endl;
		Lowcost[y] = 0;
		//添加进入新序列
		for (int i = 0; i < VerNum; i++)
		{
			if (Lowcost[i] != 0 && Amgmap::Arcs[y][i] < Lowcost[i])
			{
				Lowcost[i] = Amgmap::Arcs[y][i];
				adjVer[i] = y;
			}
		}
	}
}
void Amgmap::KrirusiKaer()
{
	int i, j, k;
	this->T = new Edge[ArcsNum];
	int* parent = new int[VerNum];
	int Z = 0;
	for (int i = 0; i < VerNum; i++)
	{
		for (int c = i; c < VerNum; c++)
		{
			if (Arcs[i][c] != 0 && Arcs[i][c] != Max)
			{
				T[Z].left = c;
				T[Z].right = i;
				T[Z++].weight = Arcs[i][c];
			}
		}
	}
	for (int i = 0; i < ArcsNum - 1; i++)
	{
		int end = i;
		Edge X = T[end + 1];
		while (end >= 0)
		{
			if (X.weight < T[end].weight)
			{
				T[end + 1] = T[end];
				end--;
			}
			else { break; }
		}
		T[end + 1] = X;
	}
	for (int i = 0; i < VerNum; i++)
	{
		parent[i] = 0;
	}
	for (int i = 0; i < VerNum-1; i++)
	{
		j = Find_KrirusiKaer(parent, T[i].left);
		k = Find_KrirusiKaer(parent, T[i].right);
		if (j != k)
		{
			parent[j] = k;
			cout << "(" << T[i].right << "," << T[i].left << ")" << T[i].weight;
		}
		cout << "\n";
	}
}
int Amgmap::Find_KrirusiKaer(int* parent, int v)
{
	while (parent[v] > 0)
	{
		v = parent[v];
	}
	return v;
}
void Amgmap::MyChoose()
{
	
}
int* MinPath;
int* Path;
void Amgmap::BuildPath()
{
	MinPath = new int[VerNum];
	Path = new int[VerNum];
	for (int i = 0; i < VerNum; i++)
	{
		MinPath[i] = Max;
		Path[i] = -1;
	}
}
void Amgmap::DjsiTela(int v)
{
	BuildPath();
	int min,longline=0;
	int* final = new int[VerNum];
	for (int i = 0; i < VerNum; i++)
	{
		final[i] = 0;
		MinPath[i] = Arcs[v][i];
	}
	for (int i = 0; i < VerNum; i++)
	{
		if (MinPath[i] < Max) { Path[i] = v; }
	}
	final[v] = 1;
	Path[v] = v;
	for (int i = 0; i < VerNum; i++)
	{
		min = Max;
		for (int y = 0; y < VerNum; y++)
		{
			if (final[y] != 1 && MinPath[y] < min)
			{
				min = MinPath[y];
				longline = y;
			}
		}
		final[longline] = 1;
		for (int c = 0; c < VerNum; c++)
		{
			if (final[c] != 1 && (min + Arcs[longline][c] < MinPath[c]))
			{
				MinPath[c] = min + Arcs[longline][c];
				Path[c] = longline;
			}
		}
	}
	for (int i = 0; i < VerNum; i++)
	{
		int z = i;
		do {
			cout << z << "<--";
			z = Path[z];
		} while (Path[z] != z);
			cout << v << " ";
			cout << "            \t" << MinPath[i] << "\n";
	}
	
}
void Amgmap::FuluouiDe()
{
	int MinPath_FuluoyiDe[10][10];
	int Path[10][10];
	for (int i = 0; i < Amgmap::VerNum; i++)
	{
		for (int c = 0; c < VerNum; c++)
		{
			MinPath_FuluoyiDe[i][c] = Arcs[i][c];
			Path[i][c] = c;
		}
	}
	for (int i = 0; i < VerNum; i++)
	{
		for (int w = 0; w < VerNum; w++)
		{
			for (int v = 0; v < VerNum; v++)
			{
				if (MinPath_FuluoyiDe[w][v] > MinPath_FuluoyiDe[i][v] + MinPath_FuluoyiDe[w][i])
					MinPath_FuluoyiDe[w][v] = MinPath_FuluoyiDe[i][v] + MinPath_FuluoyiDe[w][i];
					Path[w][v] = Path[w][i];
			}
		}
	}
	cout << "全图如下\n";
	for (int i = 0; i < VerNum; ++i)
	{
		for (int w = i + 1; w < VerNum; w++)
		{
			cout << i << " " << w << " " << MinPath_FuluoyiDe[i][w];
			int k = Path[i][w];
			cout << i << " ";
			while (k != w)
			{
				cout << "->" << k;
				k = Path[k][w];

			}
			cout << w ;
		}
		cout << "\n";
	}
}
int main()
{
	Amgmap T;
	T.KrirusiKaer();
	T.DjsiTela(1);
	T.FuluouiDe();
}
