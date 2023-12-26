#pragma once
#include<iostream>
#include"Exception.h"
#include"LinkedQueue.h"
#include<iomanip>
using namespace std;

//�������ڵ���
template<class T>
class BinaryTreeNode {

public:
	//һ���޲ι��죬���ǹ���������ǹ��������������
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
	//��������������һ���ǵ�ǰ�ڵ�����ݣ�����������ָ�����ҽڵ��ָ��
	T data;
	int color;
	BinaryTreeNode<T>* LeftChild, * RightChild, * father;
};

//��������
template<class T>
class BinaryTree {

public:
	//���캯���������յĶ�����
	BinaryTree()
	{
		root = 0;
	}

	//��������
	~BinaryTree() {};

	//�ж϶������Ƿ�Ϊ��
	bool IsEmpty()const
	{
		return ((root) ? false : true);
	}

	//ȡ�����ڵ��ֵ����x�У�����ʧ���򷵻�false
	bool Root(T& x)const;

	//����һ����������elementΪ���ڵ㣬leftΪ��������rightΪ������
	void MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right);

	//��ֶ�������ɾ�����������������������������
	void BreakTree(T& element, BinaryTree<T>& left, BinaryTree<T>& right);

	//�������
	void PreOrder(void(*Visit)(BinaryTreeNode<T>* u))
	{
		PreOrder(Visit, root);
	}

	//�������
	void InOrder(void(*Visit)(BinaryTreeNode<T>* u))
	{
		InOrder(Visit, root);
	}

	//�������
	void PostOrder(void(*Visit)(BinaryTreeNode<T>* u))
	{
		PostOrder(Visit, root);
	}

	//������
	void LevelOrder(void(*Visit)(BinaryTreeNode<T>* u));

	//����������������
	void Exchange(BinaryTreeNode<T>* t);

	//����������
	int GetWid();

	//�����ȫ���Ż�����׺���ʽ
	void Infix(BinaryTreeNode<T>* t);

	//ɾ���������ĵ����ڵ�����нڵ�
	static void Free(BinaryTreeNode<T>* t)
	{
		delete t;
	}
	void Delete()
	{
		PostOrder(Free, root);
		root = 0;
	}

	//��������
	int Height()const
	{
		return Height(root);
	}
	int Height(BinaryTreeNode<T>* t)const;

	//ͳ��Ҷ�ڵ���Ŀ
	int LeafCount(BinaryTreeNode<T>* t);

	//ͳ�ƽڵ���Ŀ
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

	//����һ��ͳ�ƽڵ���Ŀ�ĵݹ鷽��
	int Size(BinaryTreeNode<T>* t)const;

public:

	BinaryTreeNode<T>* root;
	//��������������������������Ľӿں���
	void PreOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t);
	void InOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t);
	void PostOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T>* t);

	//ͨ���������򡢺��򡢲�����ֱ����������������
	void PreOrderOutput();
	void InOrderOutput();
	void PostOrderOutput();
	void LevelOrderOutput();
};

//ȡ�����ڵ��ֵ����x�У�����ʧ���򷵻�false
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

//����һ����������elementΪ���ڵ㣬leftΪ��������rightΪ������
template<class T>
void BinaryTree<T>::MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	root = new BinaryTreeNode<T>(element, left.root, right.root);
	//���������ˣ��Ѻ�֮ǰ�ĸ��Ĺ�ϵ�ϵ�
	left.root = right.root = 0;
}

//��ֶ�����,ɾ�����������������������������
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

//��������һ�����������������滻�����⺯��
template <class T>
void Visit(BinaryTreeNode<T>* x)
{
	// visit node *x, just output element field.
	cout << x->data << ' ';
}

//�������
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

//�������
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

//�������
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

//����������
template<class T>
void BinaryTree<T>::PreOrderOutput()
{
	PreOrder(Visit);
	cout << endl;
}

//����������
template<class T>
void BinaryTree<T>::InOrderOutput()
{
	InOrder(Visit);
	cout << endl;
}

//����������
template<class T>
void BinaryTree<T>::PostOrderOutput()
{
	PostOrder(Visit);
	cout << endl;
}

//��α������
template<class T>
void BinaryTree<T>::LevelOrderOutput()
{
	LevelOrder(Visit);
	cout << endl;
}

//�����ȫ���Ż�����׺���ʽ
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

//��α���
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

//����������������
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

//�����������п��
template<class T>
int BinaryTree<T>::GetWid()
{
	if (root == NULL)
	{
		return 0;
	}
	//max��ʾĿǰΪֹ�����п�ȣ�last��ʾ��һ�еĿ��
	int max = 1, last = 1;
	BinaryTreeNode<T>* t = root;
	LinkedQueue < BinaryTreeNode<T>*> Q;
	Q.Add(t);
	while (!Q.IsEmpty())
	{
		int i = last;
		//ɾ������һ���ȫ���ڵ�
		//���ѵ�ǰ���ȫ���ڵ���ӵ����е���
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
		//forѭ�������󣬶�����ʣ�µ��ǵ�ǰ�������еĽڵ�
		if (Q.QueueSize() > max)
		{
			max = Q.QueueSize();
		}
		last = Q.QueueSize();
	}
	return max;
}

//��������߶�
template<class T>
int BinaryTree<T>::Height(BinaryTreeNode<T>* t)const
{
	if (!t)
		return 0;
	//�����������ֱ�ȥ�ݹ���߶ȣ���󷵻ظߵĴ�������ĸ߶�
	int hl = Height(t->LeftChild);
	int hr = Height(t->RightChild);
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}

//ͳ��Ҷ�ڵ���Ŀ
template<class T>
int BinaryTree<T>::LeafCount(BinaryTreeNode<T>* t)
{
	int count = 0;
	//�ݹ�����ı�־�����Һ��Ӿ�Ϊ�գ����������Ľڵ㷵��1�������е�1��Ӽ�����Ҷ�ڵ���Ŀ
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

//ͳ�ƶ������ڵ���Ŀ
template<class T>
int BinaryTree<T>::Size(BinaryTreeNode<T>* t)const
{
	if (!t)
		return 0;
	else
		//�ڵ���ĿΪ�������ڵ���Ŀ+�������ڵ���Ŀ+1
		//�˵ݹ���ÿ�ݹ�һ�μ�һ���ڵ㣬�����нڵ�ݹ���������սڵ���
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