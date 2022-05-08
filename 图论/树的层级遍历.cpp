#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct Node
{
	int val;
	Node* left;
	Node* right;
};
struct NodeRead
{
	bool see;
	Node *Tree;
};
void BuildNode(Node*& root)
{
	int temp;
	cout << "输入数值 255结束       ";
	cin >> temp;
	if (temp == 255) { return; }
	else {
		root = new Node;
		root->val = temp;
		root->left = NULL;
		root->right = NULL;
		BuildNode(root->left);
		BuildNode(root->right);
	}
}
int sumNode(Node* root)
{
	if (root == NULL) { return 0; }
	else {
		return  sumNode(root->left)+sumNode(root->right)+ 1;
	}
}
void Read(Node* root, queue<Node*>List)
{
	if (root == NULL) { return; }
	else {
		while (List.size() != 0)
		{
			Node* Temp = List.front();
			cout << Temp->val;
			if (Temp->left != NULL) { List.push(Temp->left); }
			if (Temp->right != NULL) { List.push(Temp->right); }
			List.pop();
		}
	}
}
int main()
{
	Node* root = new Node;
	BuildNode(root);
	queue<Node*>List;
	List.push(root);
	Read(root, List);
}