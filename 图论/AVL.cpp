#pragma warning (disable:4996)
#include<iostream>
#include<time.h>
#include<queue>

using namespace std;
template<class A,class B>
struct node
{
	A key;
	B data;
	node<A,B>* parent;
	node<A,B>* left, * right;
	int bf;
	node<A, B>(A key, B data) :key(key), data(data), parent(NULL), left(NULL), right(NULL), bf(0) {};
	node<A, B>():key(NULL), data(NULL), parent(NULL), left(NULL), right(NULL), bf(0) {};
};
template<class A,class B>
class AVLNodeTree
{
public:
	bool Insert(const A& key, const B& data);
	bool DeleteNode_KEY(const A& key);
	bool ChangeNode(const A& key);
	node<A,B>* FindNode(A key);
	bool clear();  //清除树
	bool isBanlance(node<A,B> *&root);
	int getHeight(node<A,B>* Node);
protected:
	int NodeSum;
	int MaxNode;
	int MinNode;
	void LeftTurn(node<A,B>*& Gnode);
	void RightTurn(node<A,B>*& Gnode);
	void LeftAndRightTurn(node<A,B>*& Gnode);
	void RightAndLeftTurn(node<A,B>*& Gnode);
public:
	node<A, B> root; 
	AVLNodeTree()
	{
		this->MaxNode = this->MinNode = this->NodeSum = 0;
		this->root();
	}
	int GetDeep(node<A, B>* Node)
	{
		if (Node == NULL) { return 0; }
		else {
			int left = GetDeep(Node->left);
			int right = GetDeep(Node->right);
			return max(left, right) + 1;
		}
	}
	int GetMaxNode() { return this->MaxNode; }
	int GetMinNode(){return this->MinNode;}
	int GetNodeSum(){return this->NodeSum;}
	void CenLook() {
		queue<node<A,B>*>Q;
		Q.push(this.root);
		while (!Q.empty())
		{
			auto T = Q.front();
			cout << T->key << " ";
			if (T->left != NULL) { Q.push(T->left); }
			if (T->right != NULL) { Q.push(T->right); }
			Q.pop();
		}
	}
};
template<class A,class B>
void AVLNodeTree<A, B>::LeftTurn(node<A,B>*& Gnode)
{
	node<A,B>* R = Gnode->right;
	node<A,B>* RL = R->left;
	RL->parent = Gnode;
	Gnode->right = RL;
	Gnode->parent = R;
	if (Gnode->parent == NULL)
	{
		root = R;
		R->parent = NULL;
	}
	else {
		if (Gnode->parent->left == Gnode) {
			Gnode->parent->left = R;
			R->parent = Gnode->parent;
		}
		if (Gnode->parent->right == Gnode) {
			Gnode->parent->right = R;
			R->parent = Gnode->parent;
		}
	}
	R->bf = Gnode->bf = 0;
}
template<class A, class B>
void AVLNodeTree<A, B>::RightTurn(node<A, B>*& Gnode)
{
	node<A,B>* L = Gnode->left;
	node<A,B>* LR = L->right;
	LR->parent = Gnode;
	Gnode->left = LR;
	Gnode->parent = L;
	if (Gnode->parent == NULL)
	{
		root = L;
		L->parent = NULL;
	}
	else {
		if (Gnode->parent->left == Gnode) {
			Gnode->parent->left = L;
		}
		else {
			Gnode->parent->right = L;
		}
		L->parent = Gnode->parent;
	}
	L->bf = Gnode->bf = 0;
}
template<class A, class B>
void AVLNodeTree<A, B>::LeftAndRightTurn(node<A, B>*& Gnode)
{

	node<A,B>* L = Gnode->left;
	node<A,B>* LR = L->right;
	int bf = LR->bf;
	LeftTurn(L);
	RightTurn(Gnode);
	if (bf == 1) {
		L->bf = -1; Gnode->bf = 0;
	}
	if (bf == 0) { L->bf = Gnode->bf = 0; }
	if (bf == -1) { L->bf = 0; Gnode->bf = 1; }
}
template<class A, class B>
void AVLNodeTree<A, B>::RightAndLeftTurn(node<A, B>*& Gnode)
{
	node<A,B>* R = Gnode->right;
	node<A,B>* RL = R->left;
	int bf = RL->bf;
	RightTurn(R);
	LeftTurn(Gnode);
	if (bf == 0) { Gnode->bf = R->bf = 0; }
	if (bf == 1) { Gnode->bf = -1; R->bf = 0; }
	if (bf == -1) { Gnode->bf = 0; R->bf = 1; }
}
template<class A, class B>
bool AVLNodeTree<A, B>::Insert(const A& key, const B& data)
{
	if (root == NULL)
	{
		root = new node<A,B>(key,data);
		return true;
	}
	node<A,B>* parent = NULL;
	node<A,B>* cur = root;
	while (cur!=NULL)
	{
		if (key > cur->key) { parent = cur; cur = cur->right; }
		if (key < cur->key) { parent = cur; cur = cur->left; }
		if (key == cur->key) { cout << "已在树中找到相同权值的节点\n"; return false; }
	}
	cur = new node<A,B>(key, data);
	if (key > parent->key) { parent->right = cur; cur->parent = parent; }
	else { parent->left = cur; cur->parent = parent; }
	while (parent)
	{
		if (parent->left == cur) { parent->bf--; }else { parent->bf++; }
		if (parent->bf == 0) { break; }
		else if (parent->bf == -1 || parent->bf == 1)
		{
			cur = parent;
			parent = parent->parent;
		}
		else {
			if (parent->bf == 2) {
				if (cur->bf == 1) { RightTurn(parent); }
				else { RightAndLeftTurn(parent); }
			}
			if (parent->bf == -2)
			{
				if (cur->bf == -1) { LeftTurn(parent); }
				else { LeftAndRightTurn(parent); }
			}
			break;
		}
	}
	return true;
}
template<class A, class B>
node<A,B>* AVLNodeTree<A, B>::FindNode(A key)
{
	node* T = root;
	if (T == NULL) { cout << "此树无根节点\n"; return NULL; }
	while (T)
	{
		if (T->key > key) { T = T->left; }
		if (T->key < key) { T = T->right; }
		if (T->key == key) { return T; }
	}
	return NULL;
}
template<class A, class B>
bool AVLNodeTree<A, B>::ChangeNode(const A& key)
{
	auto E=this->FindNode(key);
	if (E == NULL) { cout << "在树中未找到此权值\n"; return false; }
	cout << "请输入你需要修改的内容值\n";
	cin >> E->data;
	return true;
}
template<class A, class B>
bool AVLNodeTree<A, B>::clear()
{
	cout << "是否要清除此树中的所有节点(y/n)\n";
	char choose;
	cin >> choose;
	if (choose == 'y') {
		node* T = root;
		queue<node<A, B>*>Q;
		Q.push(T);
		while (!Q.empty())
		{
			auto E = Q.front();
			if (E->left != NULL) { Q.push(E->left); }
			if (E->right != NULL) { Q.push(E->right); }
			delete E;
			Q.pop();
		}
	}
	if (choose == 'n') { return false; }
}
template<class A, class B>
bool AVLNodeTree<A, B>::isBanlance(node<A,B>*& root)
{
	if (root == NULL) { return true; }
	else {
		int bf = getHeight(root->left) - getHeight(root->right);
		if (abs(bf) > 1 || bf != root->bf) { cout << "平衡因子有问题" << root->bf << endl; return false; }
		return isBanlance(root->left) && isBanlance(root->right);
	}
}
template<class A, class B>
int AVLNodeTree<A, B>::getHeight(node<A,B>* Node)
{
	if (Node == NULL) { return 0; }
	else {
		int left = getHeight(Node->left);
		int right = getHeight(Node->right);
		return max(left, right) + 1;
	}
}
template<class A, class B>
bool AVLNodeTree<A, B>::DeleteNode_KEY(const A& key)
{
	return false;
}
int main()
{
	AVLNodeTree<int, int>Tree;
	srand(unsigned(time));
	for (int i = 0; i < 4000; i++)
	{
		Tree.Insert(rand() % 400000, i);
	}
}