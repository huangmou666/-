#include<iostream>
#include<queue>
#include<vector>
#include<iterator>
using namespace std;
struct Node
{
	int x;
	int y;
	int v;
};
class ET
{
	public:
	bool operator()(Node T1, Node T2)
	{
		if (T1.x > T2.x)
		{
			return true;
		}
		else if (T1.x < T2.x)
		{
			return false;
		}
		else if (T1.x == T2.x && T1.y > T2.y)
		{
			return true;
		}
		else if (T1.x == T2.x && T1.y < T2.y)
		{
			return false;
		}
		else if (T1.x == T2.x && T1.y == T2.y && T1.v > T2.v)
		{
			return true;
		}
		else if (T1.x == T2.x && T1.y == T2.y && T1.v < T2.v)
		{
			return false;
		}
	}
};
int main()
{
	priority_queue<Node, vector<Node>, ET>Q;
	Q.push({ 1,8,11 });
	Q.push({ 2,9,7 });
	Q.push({ 3,1,8 });
	Q.push({ 2,8,4 });
	Q.push({ 3,3,9 });
	Q.push({ 5,2,9 });
	Q.push({ 4,7,7 });
	Q.push({ 2,2,2, });
	while (!Q.empty())
	{
		auto C = Q.top();
		
		cout << C.x << " " << C.y << " " << C.v << endl;
		Q.pop();
	}
}