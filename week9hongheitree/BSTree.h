#pragma once

#include<iostream>
#include"Exception.h"
#include"BinaryTree.h"
using namespace std;


template<class T>
class BSTree :public BinaryTree<T> {
public:
	bool Search(const T& t)const;//搜索函数，将关键值为k的元素返回到t中；如果操作失败则返回false，否则返回true
	BSTree<T>& Insert(const T& t);//插入函数，将元素t插入到搜索树中
	BSTree<T>& Delete(const T& t);//删除函数，删除关键值为k的元素并且将其返回到t中
	void Ascend() { BSTree<T>::InOrderOutput(); }//按关键词升序即中序输出所有数对
};

//搜索函数，将关键值为k的元素返回到t中；如果操作失败则返回false，否则返回true
template<class T>
bool BSTree<T>::Search(const T& t)const
{
	//首先使p指向跟节点
	BinaryTreeNode<T>* p = BSTree<T>::root;
	while (p)
	{
		//两层if-else，三选一，k小于根节点时指向左子树，k大于根节点时指向右子树，等于根节点时返回true
		if (t < p->data)
			p = p->LeftChild;
		else
		{
			if (t > p->data)
				p = p->RightChild;
			else
			{
				t = p->data;
				return true;
			}
		}
	}
	//没有找到关键值为k的元素，此时p为空，直接返回false
	return false;
}

//插入函数，将元素t插入到搜索树中
template<class T>
BSTree<T>& BSTree<T>::Insert(const T& t)
{
	//p指向根节点，pp指向根节点的根节点（非初始时）
	BinaryTreeNode<T>* p = BSTree<T>::root, * pp = 0;
	while (p)
	{
		//pp指向上一个while循环结束的p节点的位置
		pp = p;
		//两层if-else，三选一，k小于根节点时指向左子树，
		//k大于根节点时指向右子树，等于根节点时说明已经含有e这个元素，无法插入
		if (t < p->data)
			p = p->LeftChild;
		else
		{
			if (t > p->data)
				p = p->RightChild;
			else
				throw BadInput();
		}
	}
	//现在已经找到了合适的插入位置
	BinaryTreeNode<T>* r = new BinaryTreeNode<T>(t);
	//当根节点存在时，判断插入其左子树还是插入其右子树
	if (BSTree<T>::root)
	{
		if (t < pp->data)
			pp->LeftChild = r;
		else
			pp->RightChild = r;
	}
	//根节点不存在是e就是根节点
	else
		BSTree<T>::root = r;
	return *this;
}

//删除函数，删除关键值为k的元素并且将其返回到t中
template<class T>
BSTree<T>& BSTree<T>::Delete(const T& t)
{
	//p指向根节点，pp指向根节点的根节点（非初始时）
	BinaryTreeNode<T>* p = BSTree<T>::root, * pp = 0;
	while (p && p->data != t)
	{
		pp = p;
		if (t < p->data)
			p = p->LeftChild;
		else
			p = p->RightChild;
	}
	//当p不存在的时候说明关键值为k的元素不存在，抛出异常即可
	if (!p)
		throw BadInput();
	//找到要删除的元素了，t来保存其数据值
	t = p->data;
	//要删除节点的左右节点都存在的情况下
	if (p->LeftChild && p->RightChild)
	{
		//使s指向p的左孩子，ps指向p
		BinaryTreeNode<T>* s = p->LeftChild, * ps = p;
		//找到左孩子这一条线上最后一个右孩子用s来表示，ps表示s的父节点
		while (s->RightChild)
		{
			ps = s;
			s = s->RightChild;
		}
		//s的数据来替代要删除的节点，至此，左右子树都存在的情况下大体完成
		p->data = s->data;

		//如果s有左节点，还要将s删除后左节点移上来，移动p和pp位置为下面的代码铺垫
		//p为左孩子这一条线上最后一个右孩子s
		p = s;
		//pp为s的父节点
		pp = ps;
	}

	BinaryTreeNode<T>* c;
	//当p有左子树时(进入了上一个if循环)，或p有左子树或右子树的一棵时（没进入上个if循环）
	if (p->LeftChild)
		c = p->LeftChild;
	else
		c = p->RightChild;
	//如果p是根节点直接把c赋值给根节点
	if (p == BSTree<T>::root)
		BSTree<T>::root = c;
	//p不是根节点的话回找pp与p的关系，从而建立pp和c的关系
	else
	{
		if (p == pp->LeftChild)
			pp->LeftChild = c;
		else
			pp->RightChild = c;
	}
	delete p;
	return *this;
}