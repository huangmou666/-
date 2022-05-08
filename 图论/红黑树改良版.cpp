#include<iostream>
#include<queue>
#include<time.h>
#define Black 1
#define Red 0
using namespace std;
struct node
{
	int data;
	int color;
	node* left;
	node* right;
	node* parent;
	node(int data): left(NULL), right(NULL), parent(NULL), data(data), color(Red) {};
};
class BRTree
{
public:
	BRTree() :root(NULL), SumNode(0) {};
	int get_color(node* Node);
	void Insert(int key);
	void MidLook(node* Root);
	void Delete(int key);
	node* root;
private:
	int SumNode;
	void LeftTurn(node* parent);
	void RightTurn(node* parent);
	void Fix_InsertTree(node* insert);
	void Fix_DeleteNode(node* insert);
	node* ReplaceNode(node* Node, node* replace);
};
int BRTree::get_color(node* Node)
{
	if (Node == NULL) {
		return Black;
	}
	else {
		return Node->color;
	}
}
void BRTree::MidLook(node* Root)
{
	if (Root == NULL) { return; }
	else {
		MidLook(Root->left);
		cout << Root->data << " ";
		MidLook(Root->right);
	}
}
void BRTree::LeftTurn(node* parent)
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
void BRTree::RightTurn(node* parent)
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
void BRTree::Insert(int key)
{
	if (root == NULL) {
		root = new node(key);
		root->color = Black;
	}
	else {
		node* parent = NULL;
		node* insert = root;
		while (insert != NULL) {
			if (insert->data > key) { parent = insert; insert = insert->left; }
			else if (insert->data < key) { parent = insert; insert = insert->right; }
			else if (insert->data == key) { cout << "此树中已存在相应节点\n"; return; }
		}
		SumNode++;
		insert = new node(key);
		if (parent->data > key) {
			parent->left = insert; insert->parent = parent;
			if (parent->color == Red) { Fix_InsertTree(insert); }
		}
		if (parent->data < key) {
			parent->right = insert; insert->parent = parent;
			if (parent->color == Red) { Fix_InsertTree(insert); }
		}
	}
}
void BRTree::Fix_InsertTree(node* insert)
{
	while (get_color(insert->parent) == Red && insert->parent != NULL)
	{
		node* parent = insert->parent;
		node* grandfa = insert->parent->parent;
		if (grandfa == NULL) { break; }
			//父亲是红色说明祖父不是根节点;
			if (grandfa->left == parent)
			{
				node* Uncle = grandfa->right;
				if (get_color(Uncle) == Red)
				{
					parent->color = Black;
					Uncle->color = Black;
					grandfa->color = Red;
					insert = grandfa;
				}
				else {
					if (insert == parent->right) {
						insert = parent;
						LeftTurn(insert);
					}
					parent->color = Black;
					grandfa->color = Red;
					RightTurn(grandfa);
				}
			}
			else {
				node* Uncle = grandfa->left;
				if (get_color(Uncle) == Red) {
					Uncle->color = Black;
					parent->color = Black;
					grandfa->color = Red;
					insert = grandfa;
				}
				else {
					if (insert == parent->left) {
						insert = parent;
						RightTurn(insert);
					}
					parent->color = Black;
					grandfa->color = Red;
					LeftTurn(grandfa);
				}
			}
		}
	
	root->color = Black;
}
node* BRTree::ReplaceNode(node* Node, node* replace)
{
	if (Node->parent == NULL) { root = replace; }
	else {
		if (Node->parent->left == Node) { Node->parent->left = replace; }
		else { Node->parent->right = replace; }
	}
	if (replace != NULL) { replace->parent = Node->parent; }
	return replace;
}
void BRTree::Delete(int key)
{
	node* child = root;
	int Find = false;
	while (child)
	{
		if (child->data > key) { child = child->left; }
		else if (child->data < key) { child = child->right; }
		else if (child->data == key) { Find = true; break; }
	}
	if (Find == false) { cout << "此树中未能找到相关节点\n"; return; }
	else {
		node* nextnode = NULL; node* temp = NULL;
		if (child->left != NULL && child->right != NULL) 
		{
			temp = child-> right;
			while (temp->left != NULL) 
			{
				nextnode = temp; temp = temp->left;
			}
			child->data = temp->data;
			child = temp;
		}
		if (child->left != NULL) 
		{
			temp = child->left;
			child->data = temp->data;
			child->left = NULL;
			delete temp;
		}
		else if (child->right != NULL) 
		{
			temp = child->right;
			child->data = temp->data;
			child->right = NULL;
			delete temp;
		}
		else 
		{
			Fix_DeleteNode(child);
			if (child == root) { root = NULL; }
			else if (child->parent->left == child) {
				child->parent->left = NULL;
			}
			else if (child->parent->right == child) {
				child->parent->right = NULL;
			}
			delete child;
		}
	}
}
void BRTree::Fix_DeleteNode(node* Delete)
{
	while (Delete->parent!=NULL && Delete->color == Black) 
	{
		if (Delete == Delete->parent->left) {
			node* Uncle = Delete->parent->right;
			if (get_color(Uncle) == Red) {
				Uncle->color = Black;
				Delete->parent->color = Red;
				LeftTurn(Delete->parent);
				Uncle = Delete->parent->right;
			}
			if (Uncle != NULL ) {
				if (get_color(Uncle->left) == Black && get_color(Uncle->right) == Black)
				{
					Uncle->color = Red;
					Delete = Delete->parent;
				}
				else {
					if (get_color(Uncle->right) == Black) {
						if (Uncle->left != NULL) { Uncle->left->color = Black; }
						Uncle->color = Red;
						RightTurn(Uncle);
						Uncle = Delete->parent->right;
					}
					Uncle->color = Delete->color;
					Delete->parent->color = Black;
					if (Uncle->right != NULL) { Uncle->right->color = Black; }
					LeftTurn(Delete->parent);
					Delete = root;
				}
			}
			else { break; }
		}
		else {
			node* Uncle = Delete->parent->left;
			if (get_color(Uncle) == Red) {
				Uncle->color = Black;
				Delete->parent->color = Red;
				RightTurn(Delete->parent);
				Uncle = Delete->parent->left;
			}
			if (Uncle != NULL) {
				if (get_color(Uncle->left) == Black && get_color(Uncle->right) == Black)
				{
					Uncle->color = Red;
					Delete = Delete->parent;
				}
				else {
					if (get_color(Uncle->left) == Black) {
						if (Uncle->right != NULL) { Uncle->right->color = Black; }
						Uncle->color = Red;
						LeftTurn(Uncle);
						Uncle = Delete->parent->left;
					}
					Uncle->color = Delete->color;
					Delete->parent->color = Black;
					if (Uncle->left != NULL) { Uncle->left->color = Black; }
					RightTurn(Delete->parent);
					Delete = root;
				}
			}
			else {break;}
		}
	}
	Delete->color = Black;
}
int main()
{
	BRTree Tree;
	srand(unsigned(time));
	for (int i = 1; i <11; i++) {
		Tree.Insert(i);
	}
	Tree.Delete(6);
	Tree.MidLook(Tree.root);
}
