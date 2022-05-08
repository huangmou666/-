#include<iostream>
#include<queue>
#include<time.h>
#include<math.h>
#define Red 0
#define Black 1
using namespace std;
struct node
{
	node* left;
	node* right;
	int data;
	bool color;
	node* parent;
	node(int key) :left(NULL), right(NULL), data(key), color(0), parent(NULL) {};
};
class RedAndBlackTree
{
public:
	node* root;
	RedAndBlackTree() :SumNode(0), MaxSum(0), MinSum(0), root(NULL) {};
	bool InsertNode(int key);
	void MidLook(node* Look);
	void DeleteNode(int key);
	void CenLook();
	int SumNode;
	int MaxSum;
	int MinSum;
private:
	void LeftTurn(node* parent);
	void RightTurn(node* parent);
	void Fix_Tree(node* insert);
	void ease_Node(node* Delete);
	void Fix_TreeDelete(node* Node);
};
void RedAndBlackTree::LeftTurn(node* parent)
{
	node* R = parent->right;
	node* RL = R->left;
	parent->right = RL;
	if (RL != NULL) { RL->parent = parent; }
	if (parent->parent == NULL) {
		root = R; R->parent = NULL;
	}
	else {
		if (parent->parent->left == parent) { parent->parent->left = R; R->parent = parent->parent; }
		else { parent->parent->right = R; R->parent = parent->parent; }
	}
	R->left = parent; parent->parent = R;
}
void RedAndBlackTree::RightTurn(node* parent)
{
	node* L = parent->left;
	node* LR = L->right;
	parent->left = LR;
	if (LR != NULL) { LR->parent = parent; }
	if (parent->parent == NULL) { root = L; L->parent = NULL; }
	else if (parent->parent != NULL) {
		if (parent->parent->left == parent) { parent->parent->left = L; L->parent = parent->parent; }
		else { parent->parent->right = L; L->parent = parent->parent; }
	}
	L->right = parent;
	parent->parent = L;
}
void RedAndBlackTree::ease_Node(node* Delete)
{
	if (Delete->parent != NULL) {
		if (Delete->parent->left == Delete) { Delete->parent->left = NULL; }
		else { Delete->parent->right = NULL; }
		Delete->parent = NULL;
	}
	Delete->data = NULL; Delete->left = NULL;
	Delete->right = NULL; Delete->color = Red;
	delete Delete;
}
void RedAndBlackTree::CenLook()
{
	node* Temp = root;
	int thiscen = 0; int jump = 0;
	int Cha = 0;
	queue<node*>Q;
	Q.push(Temp);
	while (!Q.empty()) {
		auto E = Q.front();
		if (E->left != NULL) { Q.push(E->left); }
		if (E->right != NULL) { Q.push(E->right); }
		cout << E->data << " ";
		Q.pop();
		jump++;
		if (jump == pow(2, thiscen)) { cout << "\n";
		Cha = pow(2, thiscen) - pow(2, jump - 1);
		jump = 0; jump = Cha;
		thiscen++;
		}
	}
}
void RedAndBlackTree::Fix_Tree(node* insert)
{
	node* parent = insert->parent;
	node* Uncle = NULL;
	while (true) {
		if (parent == NULL) { break; }
		if (parent->color == Black) { break; }
		node* grandfa = parent->parent;
		if (grandfa != NULL) {//祖父健在
			if (parent == grandfa->left) {//父亲是祖父的左儿子
				Uncle = grandfa->right;
				if (Uncle) 
				{//叔叔健在
					if (Uncle->color == Red) {
						Uncle->color = Black;
						parent->color = Black;
						grandfa->color = Red;
						insert = grandfa;
					}
					else if (insert == parent->right) {//叔叔是黑色，父亲是红色，是父亲的右节点
						insert = parent;
						LeftTurn(insert);
					}
					else {//是父亲的左节点
						parent->color = Black; grandfa->color = Red;
						RightTurn(grandfa);
					}
				}
				else {//没有叔叔
					if (insert == parent->right) {
						insert = parent;
						LeftTurn(insert);
					}
					else {
						parent->color = Black;
						grandfa->color = Red;
						RightTurn(grandfa);
					}
				}
			}
			else {//父亲是右边的孩子
				Uncle = grandfa->left;
				if (Uncle) {
					if (Uncle->color == Red) {
						Uncle->color = Black;
						parent->color = Black;
						grandfa->color = Red;
						insert = grandfa;
					}
					else if (insert == parent->left) {
						insert = parent;
						RightTurn(insert);
					}
					else {
						parent->color = Black;
						grandfa->color = Red;
						LeftTurn(grandfa);
					}
				}
				else {//没有叔叔
					if (insert == parent->left) {
						insert = parent;
						RightTurn(insert);
					}
					else {
						parent->color = Black; 
						grandfa->color = Red;
						LeftTurn(grandfa);
					}
				}
			}
		}
	}
	root->color = Black;
}
bool RedAndBlackTree::InsertNode(int key)
{
	if (root == NULL) {
		root = new node(key);
		root->color = Black;
		return true;
	}
	else {
		node* parent = NULL;
		node* insert = root;
		while (insert != NULL) {
			if (insert->data > key) { parent = insert; insert = insert->left; }
			else if (insert->data < key) { parent = insert; insert = insert->right; }
			else if (insert->data == key) { cout << "此树中已存在相应节点\n"; return false; }
		}
		SumNode++;
		if (key > MaxSum) { MaxSum = key; }
		if (key < MinSum) { MinSum = key; }
		insert = new node(key);
		if (parent->data > key){
			parent->left = insert; insert->parent = parent;
		    if (parent->color == Red) { Fix_Tree(insert); }
		}
		if (parent->data < key) { 
			parent->right = insert; insert->parent = parent;
			if (parent->color == Red) { Fix_Tree(insert); }
		}
	}
}
void RedAndBlackTree::MidLook(node* Look)
{
	if (Look == NULL) { return; }
	else {
		MidLook(Look->left);
		cout << Look->data << " ";
		MidLook(Look->right);
	}
}
void RedAndBlackTree::DeleteNode(int key)
{
	node* child = root;
	node* parent = NULL;
	while (child->data != key)
	{
		if (child->data > key) { parent = child; child = child->left; }
		else { parent = child; child = child->right; }
	}
	int Acolor = child->color;
	if (child->left==NULL&&child->right==NULL) {
		if (child->parent == NULL) {
			if (Acolor == Red) { root = NULL; delete child; return; }
			else { Fix_TreeDelete(child); }
		}
		else {
			if (Acolor == Red) { delete child; return; }
			else { Fix_TreeDelete(child);}
		}
	}
	if (child->left != NULL && child->right == NULL) {
		
	}
}
void RedAndBlackTree::Fix_TreeDelete(node* child)
{
	while (child != root && child->color==Black)
	{

	}
}
int main()
{
	srand(unsigned(time));
	RedAndBlackTree Tree;
	for (int i = 0; i < 4000; i++)
	{
		Tree.InsertNode(rand() % 5000000);
	}
	Tree.CenLook();
}