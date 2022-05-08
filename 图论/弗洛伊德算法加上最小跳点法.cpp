#include<iostream>
#include<Windows.h>
#include<queue>
#define Max 10
#define MaxDec 65525
#define Point 65524
using namespace std;
struct AMGmap
{
	int ver;
	int arc;
	char *mapVer;
	int map[Max][Max];
};
pair<bool, vector<int>>Back(AMGmap map, int begin);
AMGmap buildAMGMap(AMGmap map)
{
	std::cout << "����������Ҫ�����Ľ�����\n";
	cin >> map.ver;
	map.mapVer = new char[map.ver];
	std::cout << "����������Ҫ�����ı�����\n";
	cin >> map.arc; int x, y;
	for (int i = 0; i < map.ver; i++)
	{
		for (int v = 0; v < map.ver; v++)
		{
			map.map[i][v] = MaxDec;
		}
	}
	for (int i = 0; i < map.ver; i++)
	{
		map.map[i][i] = 0;
	}
	for (int i = 0; i < map.ver; i++)
	{
		std::cout << "�����붥��\n";
		cin >> map.mapVer[i];
	}
	std::cout << "�����ɹ�\n";
	int wight;
	for (int i = 0; i < map.arc; i++)
	{
		std::cout << "���ڻ���" << map.arc - i << "����δ����\n";
		std::cout << "����������Ҫ������������\n";
		cin >> x >> y;
		std::cout << "������ߵ�Ȩֵ\n";
		cin >> wight;
		map.map[x][y] = map.map[y][x] = wight;
	}
	std::cout << "�������\n";
	return map;
}
int Path[Max][Max];
int PathRoot[Max][Max];
void FuluoYiDe(AMGmap map, int Path[Max][Max], int PathRoot[Max][Max])
{
	for (int i = 0; i < map.ver; i++)
	{
		for (int y = 0; y < map.ver; y++)
		{
			Path[i][y] = map.map[i][y];
			PathRoot[y][i] = i;
		}
	}
	for (int i = 0; i < map.ver; i++)
	{
		for (int j = 0; j < map.ver; j++)
		{
			for (int k = 0; k < map.ver; k++)
			{
				if (Path[j][k] > Path[j][i] + Path[i][k])
				{
					Path[j][k] = Path[j][i] + Path[i][k];
					PathRoot[j][k] = PathRoot[j][i];
				}
			}
		}
	}
	std::cout << "����������·������\n";
	int k = 0;
	for (int i = 0; i < map.ver; ++i)
	{
		for (int d = i+ 1; d < map.ver; d++)
		{
			std::cout << i << "--" << d << " weight: " << Path[i][d]<<" ";
			k = PathRoot[i][d];
			std::cout <<"Path:"<< i;
			while (k != d)
			{
				std::cout <<"-->"<< k << "";
				k = PathRoot[k][d];
			}
			std::cout <<"-->"<< d<<"\n";
		}
		std::cout << "\n";
	}
	int x, y;
	while (true)
	{
		FLAG:
		std::cout << "��������Ҫ�ض����ҵĶ�Ӧ����\n";
		cin >> x >> y;
		std::cout << "��������\n"; Sleep(300);
		if (Path[x][y] == Max) { std::cout << "��������ֱ������\n"; break; }
		else {
			std::cout << "�������Ȩֵ��("<<Path[x][y]<<")\n";
		}
		std::cout << x << "-->";
		while (x != y)
		{
			std::cout << PathRoot[x][y] << "-->";
			x = PathRoot[x][y];
		}
		std::cout << "�������Ƿ���Ҫ���²�ѯ(1/0)\n";
		bool ch = false;
		cin >> ch;
		if (ch == 1) { goto FLAG; }
		else { break; }
	}
}
void ShortPathNode(AMGmap map)
{

	int JumpTemp[Max][Max];
	for (int i = 0; i < map.ver; i++)
	{
		for (int j = 0; j < map.ver; j++)
		{
			JumpTemp[i][j] = MaxDec;
		}
	}
	for (int i = 0; i < map.ver; i++)
	{
		JumpTemp[i][i] = 0;
	}
	int begin;
	std::cout << "����������Ҫ�����\n";
	cin >> begin;
	queue<pair<int, pair<int, int>>>Q; int T = begin;
	int ImportCen = 1;
	JumpTemp[begin][begin] = 0;
	for (int i = 0; i < map.ver; i++)
	{
		if (map.map[T][i] != 0 && map.map[T][i] != MaxDec)
		{
			JumpTemp[T][i] = 1;
			Q.push({ ImportCen, {T, i} });
		}
	}
	//����Ҫ��ѭ��............��JumpTemp����ά��
	while (!Q.empty())
	{
		auto Tec = Q.front();
		JumpTemp[Tec.second.second][Tec.second.first] = Tec.first;
		for (int i = 0; i < map.ver; i++)
		{
			if (map.map[Tec.second.second][i] != 0 && map.map[Tec.second.second][i] != Max && i != Tec.second.first)
			{
				if (JumpTemp[Tec.second.second][i] > Tec.first + 1) {
					JumpTemp[Tec.second.second][i] = Tec.first + 1;
					Q.push({ Tec.first + 1, { Tec.second.second ,i } });
				}
			}
		}
		Q.pop();
	}
	//��JumpTemp���н���
	for (int i = 0; i < map.ver; i++)
	{
		for (int d = 0; d < map.ver; d++)
		{
			std::cout << JumpTemp[i][d] << " ";
		}
		std::cout << "\n";
	}

	//����������ͨͼ������
	auto AllMapTong = Back(map, begin);
	vector<int>Look;
	if (AllMapTong.first == false) {
		Look = AllMapTong.second;
	}
	class Great
	{
	public:
		bool operator()(pair<int, pair<int, int>>T1, pair<int, pair<int, int>>T2)
		{
			if (T1.second.first > T2.second.first)
			{
				return true;
			}
			else if (T1.second.first < T2.second.first)
			{
				return false;
			}
			else if (T1.second.first == T2.second.first)
			{
				if (T1.second.second > T2.second.second)
				{
					return true;
				}
				else {
					return false;
				}
			}
		}
	};
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, Great>QE;
	for (int i = 0; i < map.ver; i++)
	{
		if (i == begin) { continue; }
	else{
		std::cout << "��" << i << "-->";
		int sum = 0;
		for (int d = 0; d < map.ver; d++){if (map.map[i][d]!=MaxDec){QE.push({ d,{JumpTemp[i][d],map.map[i][d]} });}}
		QE.pop();
		auto Fine = find(Look.begin(), Look.end(), i);
		if (QE.size() != 0&&Fine==Look.end())
		{ 
		auto Temp = QE.top();
			sum += Temp.second.second;
			std::cout << Temp.first << "-->";
			while (!QE.empty()) { QE.pop(); }
			while (Temp.first != begin)
			{
				for (int k = 0; k < map.ver; k++) {
					if(map.map[Temp.first][k] != MaxDec)
					QE.push({ k,{JumpTemp[Temp.first][k],map.map[Temp.first][k]} });
				}
				QE.pop();
				if (QE.size() != 0) {
					Temp = QE.top();
					sum += Temp.second.second;
					std::cout << Temp.first<<"-->";
					while (!QE.empty()) { QE.pop(); }
				}
				else {
					break;
				}
			}
			std::cout << "\t\tȨֵ��    " << sum << endl;
		}
		else{
				std::cout << "�˵���ֱ��" << begin << "����ͨ·\n";
				continue;
		}
	};
	}
}
pair<bool, vector<int>>Back(AMGmap map, int begin)
{
	bool* Selete = new bool[map.ver];
	bool TEC = true;
	for (int i = 0; i < map.ver; i++)
	{
		Selete[i] = false;
	}
	queue<int>Q;
	Q.push(begin);
	while (!Q.empty())
	{
		auto n = Q.front();
		Selete[n] = true;
		for (int i = 0; i < map.ver; i++)
		{
			if (map.map[n][i] != MaxDec && Selete[i] != true) { Q.push(i); }
		}
		Q.pop();
	}
	vector<int>ASS;
	for (int i = 0; i < map.ver; i++)
	{
		if (Selete[i] == false) { ASS.push_back(i); TEC = false; }
	}
	if (TEC == false) { return { false,ASS }; }
	else { return { true,ASS }; }
}
int main()
{
	AMGmap map = {0};
	map = buildAMGMap(map);
	ShortPathNode(map);
	/*FuluoYiDe(map, Path, PathRoot);*/

}