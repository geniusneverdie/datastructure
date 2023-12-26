#pragma once
#include<iostream>
#include"Exception.h"
#include"LinkedQueue.h"
#include<iomanip>
using namespace std;

//二叉树节点类
template<class T>
class BinaryTreeNode {

public:
	//一是无参构造，二是构造根，三是构造根和左右子树
	BinaryTreeNode()
	{
		LeftChild = RightChild = father = 0;
		color = 0;
	}
	BinaryTreeNode(const T& e)
	{
		data = e; LeftChild = RightChild = father = 0;
		color = 0;
	}
	BinaryTreeNode(const T& e, BinaryTreeNode* l, BinaryTreeNode* r)
	{
		data = e;
		LeftChild = l;
		RightChild = r;
		father = 0;
		color = 0;
	}

public:
	//数据域有三个，一个是当前节点的数据，另外两个是指向左右节点的指针
	T data;
	int color;
	BinaryTreeNode<T>* LeftChild, * RightChild, * father;
};

//二叉树类
template<class T>
class BinaryTree {

public:
	//构造函数，创建空的二叉树
	BinaryTree()
	{
		root = 0;
	}

	//析构函数
	~BinaryTree() {};

	//判断二叉树是否为空
	bool IsEmpty()const
	{
		return ((root) ? false : true);
	}

	//取出根节点的值放在x中，操作失败则返回false
	bool Root(T& x)const;

	//创建一个二叉树，element为根节点，left为左子树，right为右子树
	void MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right);

	//拆分二叉树，删除根，将左子树和右子树分离出来
	void BreakTree(T& element, BinaryTree<T>& left, BinaryTree<T>& right);

	//先序遍历
	void PreOrder(void(*Visit)(BinaryTreeNode<T>* u))
	{
		PreOrder(Visit, root);
	}

	//中序遍历
	void InOrder(void(*Visit)(BinaryTreeNode<T>* u))
	{
		InOrder(Visit, root);
	}

	//后序遍历
	void PostOrder(void(*Visit)(BinaryTreeNode<T>* u))
	{
		PostOrder(Visit, root);
	}

	//逐层遍历
	void LevelOrder(void(*Visit)(BinaryTreeNode<T>* u));

	//交换所有左右子树
	void Exchange(BinaryTreeNode<T>* t);

	//求二叉树宽度
	int GetWid();

	//输出完全括号化的中缀表达式
	void Infix(BinaryTreeNode<T>* t);

	//删除二叉树的单个节点和所有节点
	static void Free(BinaryTreeNode<T>* t)
	{
		delete t;
	}
	void Delete()
	{
		PostOrder(Free, root);
		root = 0;
	}

	//计算树高
	int Height()const
	{
		return Height(root);
	}
	int Height(BinaryTreeNode<T>* t)const;

	//统计叶节点数目
	int LeafCount(BinaryTreeNode<T>* t);

	//统计节点数目
	static int _count;

	static void Add1(BinaryTreeNode<T>* t)
	{
		_count++;
	}

	int size()
	{
		_count = 0;
		PreOrder(Add1, root);
		return _count;
	}

	//另外一种统计节点数目的递归方法
	int Size(BinaryTreeNode<T>* t)const;

public:

	BinaryTreeNode<T>* root;
	//先序遍历，中序遍历，后序遍历的接口函数
	void PreOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t);
	void InOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t);
	void PostOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t);

	//通过先序、中序、后序、层次四种遍历方法输出二叉树
	void PreOrderOutput();
	void InOrderOutput();
	void PostOrderOutput();
	void LevelOrderOutput();
};

//取出根节点的值放在x中，操作失败则返回false
template<class T>
bool BinaryTree<T>::Root(T& x)const
{
	if (root)
	{
		x = root->data;
		return true;
	}
	else
		return false;
}

//创建一个二叉树，element为根节点，left为左子树，right为右子树
template<class T>
void BinaryTree<T>::MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	root = new BinaryTreeNode<T>(element, left.root, right.root);
	//新树建好了，把和之前的根的关系断掉
	left.root = right.root = 0;
}

//拆分二叉树,删除根，将左子树和右子树分离出来
template<class T>
void BinaryTree<T>::BreakTree(T& element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	if (!root)
		throw BadInput();
	element = root->data;
	left.root = root->LeftChild;
	right.root = root->RightChild;
	delete root;
	root = 0;
}

//传进来的一个函数参数，可以替换成任意函数
template <class T>
void Visit(BinaryTreeNode<T>* x)
{
	// visit node *x, just output element field.
	cout << x->data << ' ';
}

//先序遍历
template<class T>
void BinaryTree<T>::PreOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t)
{
	if (t)
	{
		Visit(t);
		PreOrder(Visit, t->LeftChild);
		PreOrder(Visit, t->RightChild);
	}
}

//中序遍历
template<class T>
void BinaryTree<T>::InOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t)
{
	if (t)
	{
		InOrder(Visit, t->LeftChild);
		Visit(t);
		InOrder(Visit, t->RightChild);
	}
}

//后序遍历
template<class T>
void BinaryTree<T>::PostOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t)
{
	if (t)
	{
		PostOrder(Visit, t->LeftChild);
		PostOrder(Visit, t->RightChild);
		Visit(t);
	}
}

//先序遍历输出
template<class T>
void BinaryTree<T>::PreOrderOutput()
{
	PreOrder(Visit);
	cout << endl;
}

//中序遍历输出
template<class T>
void BinaryTree<T>::InOrderOutput()
{
	InOrder(Visit);
	cout << endl;
}

//后序遍历输出
template<class T>
void BinaryTree<T>::PostOrderOutput()
{
	PostOrder(Visit);
	cout << endl;
}

//层次遍历输出
template<class T>
void BinaryTree<T>::LevelOrderOutput()
{
	LevelOrder(Visit);
	cout << endl;
}

//输出完全括号化的中缀表达式
template<class T>
void BinaryTree<T>::Infix(BinaryTreeNode<T>* t)
{
	if (t)
	{
		cout << "(";
		Infix(t->LeftChild);
		cout << t->data;
		Infix(t->RightChild);
		cout << ")";
	}
}

//层次遍历
template<class T>
void BinaryTree<T>::LevelOrder(void(*Visit)(BinaryTreeNode<T>* u))
{
	LinkedQueue < BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T>* t = root;
	while (t)
	{
		Visit(t);
		if (t->LeftChild)
			Q.Add(t->LeftChild);
		if (t->RightChild)
			Q.Add(t->RightChild);
		try
		{
			Q.Delete(t);
		}
		catch (OutOfBounds)
		{
			return;
		}
	}
}

//交换所有左右子树
template<class T>
void BinaryTree<T>::Exchange(BinaryTreeNode<T>* t)
{
	if (t != 0)
	{
		BinaryTreeNode<T>* temp = t->LeftChild;
		t->LeftChild = t->RightChild;
		t->RightChild = temp;
		Exchange(t->LeftChild);
		Exchange(t->RightChild);
	}
}

//求二叉树最大行宽度
template<class T>
int BinaryTree<T>::GetWid()
{
	if (root == NULL)
	{
		return 0;
	}
	//max表示目前为止最大的行宽度，last表示上一行的宽度
	int max = 1, last = 1;
	BinaryTreeNode<T>* t = root;
	LinkedQueue < BinaryTreeNode<T>*> Q;
	Q.Add(t);
	while (!Q.IsEmpty())
	{
		int i = last;
		//删除掉上一层的全部节点
		//并把当前层的全部节点添加到队列当中
		for (i; i > 0; i--)
		{
			t = Q.front();
			if (t->LeftChild)
				Q.Add(t->LeftChild);
			if (t->RightChild)
				Q.Add(t->RightChild);
			try
			{
				Q.Delete(t);
			}
			catch (OutOfBounds)
			{
				return;
			}
		}
		//for循环结束后，队列中剩下的是当前层中所有的节点
		if (Q.QueueSize() > max)
		{
			max = Q.QueueSize();
		}
		last = Q.QueueSize();
	}
	return max;
}

//求二叉树高度
template<class T>
int BinaryTree<T>::Height(BinaryTreeNode<T>* t)const
{
	if (!t)
		return 0;
	//给左右子树分别去递归求高度，最后返回高的大的子树的高度
	int hl = Height(t->LeftChild);
	int hr = Height(t->RightChild);
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}

//统计叶节点数目
template<class T>
int BinaryTree<T>::LeafCount(BinaryTreeNode<T>* t)
{
	int count = 0;
	//递归结束的标志是左右孩子均为空，碰到这样的节点返回1，把所有的1相加即得总叶节点数目
	if (t->LeftChild == NULL && t->RightChild == NULL)
	{
		return 1;
	}
	else
	{
		count = LeafCount(t->LeftChild) + LeafCount(t->RightChild);
	}
	return count;
}

//统计二叉树节点数目
template<class T>
int BinaryTree<T>::Size(BinaryTreeNode<T>* t)const
{
	if (!t)
		return 0;
	else
		//节点数目为左子树节点数目+右子树节点数目+1
		//此递归是每递归一次加一个节点，把所有节点递归完求得最终节点数
		return Size(t->LeftChild) + Size(t->RightChild) + 1;
}
template<class T>
void show(BinaryTreeNode<T>* x, int d)
{

	if (x != NULL) {

		show(x->RightChild, d + 1);

		cout.setf(ios::right);

		cout << setw(3 * d) << " ";

		cout << x->data << endl;

		show(x->LeftChild, d + 1);

	}
}