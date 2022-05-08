#include<iostream>
#include<map>
#include<queue>
using namespace std;
struct Node
{
	int weight;
	int parent, left, right;
};
struct NodeList
{
	int Code;
	Node List;
};
void selete(Node* list, int n);
void BuildCode(NodeList* List);
void HaffmanTreeBuild(Node*&list, int n)
{
	if (n < 1) { return; }
	int m = 2 * n - 1;
	list = new Node[m+1];
	for (int i = 1; i <= m; i++)
	{
		list[i].left = 0;
		list[i].right = 0;
		list[i].parent = 0;
		list[i].weight = NULL;
	}
	for (int i = 1; i <= n; i++)
	{
		cout << "请输入你需要的第" << i << "个节点的值      ";
		cin >> list[i].weight;
		cout << "\n";
	}
	for (int i = n+1; i <= m; i++)
	{
		selete(list, i - 1);
	}
}
void selete(Node* list, int n)
{
	int min1 = 65525;
	int min2 = min1;
	int x1 = 0, x2 = 0;
	for (int i = 1; i <= n; i++)
	{
		if (list[i].parent == 0 && list[i].weight < min1)
		{
			min2 = min1;
			min1 = list[i].weight;
			x2 = x1;
			x1 = i;
		}
		else if (list[i].weight < min2 && list[i].parent == 0)
		{
			min2 = list[i].weight;
			x2 = i;
		}
	}
	list[x1].parent = n + 1;
	list[x2].parent = n + 1;
	list[n + 1].weight = min1 + min2;
	list[n + 1].right = x1;
	list[n + 1].left = x2;
}
void BuildHaffmanCode(Node* list, NodeList* Tlist,int n)
{
	int m = 2 * n - 1;
	Tlist = new NodeList[m+1];
	for (int i = 1; i <= m; i++)
	{
		Tlist[i].Code = 1;
		Tlist[i].List = list[i];
	}
	Tlist[0].Code = 1;
	Tlist[0].List.left = m;
	Tlist[0].List.right = m-1;
	BuildCode(Tlist);

	cout << "节点         节点值           左孩子        右孩子          父母          编码\n";
	for (int i = 1; i <= m; i++)
	{
		cout << "第" << i << "个元素\t" <<Tlist[i].List.weight<<"              "<< Tlist[i].List.left << "            " << Tlist[i].List.right << "               " << Tlist[i].List.parent << "              " << Tlist[i].Code<<"\n";
	}

}
void BuildCode(NodeList* List)
{
	queue<NodeList>q;
	q.push(List[0]);
	while (!q.empty())
	{
		NodeList Temp = q.front();
		if (Temp.List.left != 0) { List[Temp.List.left].Code=Temp.Code*10+1; q.push(List[Temp.List.left]); }
		if (Temp.List.right != 0) { List[Temp.List.right].Code = Temp.Code * 10 ; q.push(List[Temp.List.right]); }
		q.pop();
	}
}
int main()
{
	int n = 10;
	Node* list = NULL;
	NodeList* Tlist = NULL;
	HaffmanTreeBuild(list, n);
	BuildHaffmanCode(list, Tlist, n);
}