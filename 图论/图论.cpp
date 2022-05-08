#include<iostream>
#include<vector>
#include"队列.h"
using namespace std;
struct node
{
	bool see;
	int data;
};
//邻接矩阵
struct List
{
	node gab[10][10];
	int ver;//节点数量;
	int line;//节点边数;
};

void init(List* list);
void show(List* list);
void Line(List* list);

//开始创建
void init(List* list)
{
	cout << "你需要多少个数值\n";
		int longLen;
		cin >> longLen;
		list->ver = longLen;
		for (int i = 0; i < longLen; i++) { 
			list->gab[i][0].data = i;
		}
		cout << "建立完成\n";
}
//清空bool值和赋值
void turnBool(List* list)
{
	for (int i = 0; i < list->ver; i++) {
		for (int c = 1; c < list->ver + 1; c++) {
			list->gab[i][c].see = false;
			list->gab[i][c].data = 0;
		}
	}
	cout << "初始化完成\n";
}
//连接线段
void Line(List* list) {
	for (int i = 0; i < list->ver; i++) {
		cout << "当前数值为" << list->gab[i]->data+1<<endl;
		cout << "有以下数据可使用\n";
		for (int c = 0; c < list->ver; c++) {cout << list->gab[c]->data+1<<"  " << "";}
		cout << "请选择你的连接点(299结束)\n";
		int num[10]; int x = 0;
		while (x!=10)
		{
			cin >> num[x];
			if (x == 10 || num[x] == 299) { break; }
			else {
				for (int y = 1; y < list->ver+1; y++) {
					if (num[x] == list->gab[y][0].data) { list->gab[i][y ] = list->gab[y][0]; }
				}
			}
			x++;
		}
		x = 0;
	}
}
//显示矩阵
void show(List* list)
{
	for (int i = 0; i < list->ver; i++) {
		for (int c = 1; c < list->ver+1 ; c++) {
			cout << list->gab[i][c].data<<"  ";
		}
		cout << "\n";
	}
}
//test
void showtest(List* list)
{
	for (int i = 0; i < list->ver; i++) { for (int c = 0; c < list->ver + 1; c++) { cout << list->gab[i][c].data << "  "; } }
}
//清空矩阵中的遍历
void changeBool(List* list)
{
	for (int i = 0; i < list->ver; i++) {
		for (int c = 0; c < list->ver + 1; c++) {
			list->gab[i][c].see = false;

		}
	}
}
//深度优先
void DeepLook(List* list)
{
	Stack* stack = NULL;
	init(stack);
	changeBool(list);
	cout << "你选择那个节点进行深度优先算法\n";
	int data=0; int num[10]; int temp;
	cin >> data;
	int y = 0;
	if (data > list->ver + 1 || data < 0) { cout << "抱歉无法实现\n"; return; }
	else {
		for (int k = 1; k < list->ver + 1; k++) {
			if (list->gab[data][k].data != 0) {
				pop(stack, list->gab[data][k].data);
			}
		FLAG:
			if (y == list->ver) { goto FLAG2; }
			temp=push(stack);
			if (temp == 0) { cout << "该点没有任何元素与其匹配\n"; return; }
			else {
				for (int i = 0; i < list->ver; i++) {
					if (list->gab[i][0].data == temp && list->gab[i][0].see != false) { num[y] = list->gab[i][0].data; list->gab[i][0].see = true; y++; }
					else { goto FLAG; }
				}
			}
		}
	}
	FLAG2:
	for (int i = 0; num[i] != 0; i++) { cout << num[i] << "->"; }
}
int main()
{
	List* list = new List;
	init(list);
	turnBool(list);
	Line(list);
	showtest(list);
	show(list);
	DeepLook(list);
}