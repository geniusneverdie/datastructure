#pragma once

#include<iostream>
#include"Exception.h"
#include"BinaryTree.h"
using namespace std;


template<class T>
class BSTree :public BinaryTree<T> {
public:
	bool Search(const T& t)const;//�������������ؼ�ֵΪk��Ԫ�ط��ص�t�У��������ʧ���򷵻�false�����򷵻�true
	BSTree<T>& Insert(const T& t);//���뺯������Ԫ��t���뵽��������
	BSTree<T>& Delete(const T& t);//ɾ��������ɾ���ؼ�ֵΪk��Ԫ�ز��ҽ��䷵�ص�t��
	void Ascend() { BSTree<T>::InOrderOutput(); }//���ؼ����������������������
};

//�������������ؼ�ֵΪk��Ԫ�ط��ص�t�У��������ʧ���򷵻�false�����򷵻�true
template<class T>
bool BSTree<T>::Search(const T& t)const
{
	//����ʹpָ����ڵ�
	BinaryTreeNode<T>* p = BSTree<T>::root;
	while (p)
	{
		//����if-else����ѡһ��kС�ڸ��ڵ�ʱָ����������k���ڸ��ڵ�ʱָ�������������ڸ��ڵ�ʱ����true
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
	//û���ҵ��ؼ�ֵΪk��Ԫ�أ���ʱpΪ�գ�ֱ�ӷ���false
	return false;
}

//���뺯������Ԫ��t���뵽��������
template<class T>
BSTree<T>& BSTree<T>::Insert(const T& t)
{
	//pָ����ڵ㣬ppָ����ڵ�ĸ��ڵ㣨�ǳ�ʼʱ��
	BinaryTreeNode<T>* p = BSTree<T>::root, * pp = 0;
	while (p)
	{
		//ppָ����һ��whileѭ��������p�ڵ��λ��
		pp = p;
		//����if-else����ѡһ��kС�ڸ��ڵ�ʱָ����������
		//k���ڸ��ڵ�ʱָ�������������ڸ��ڵ�ʱ˵���Ѿ�����e���Ԫ�أ��޷�����
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
	//�����Ѿ��ҵ��˺��ʵĲ���λ��
	BinaryTreeNode<T>* r = new BinaryTreeNode<T>(t);
	//�����ڵ����ʱ���жϲ��������������ǲ�����������
	if (BSTree<T>::root)
	{
		if (t < pp->data)
			pp->LeftChild = r;
		else
			pp->RightChild = r;
	}
	//���ڵ㲻������e���Ǹ��ڵ�
	else
		BSTree<T>::root = r;
	return *this;
}

//ɾ��������ɾ���ؼ�ֵΪk��Ԫ�ز��ҽ��䷵�ص�t��
template<class T>
BSTree<T>& BSTree<T>::Delete(const T& t)
{
	//pָ����ڵ㣬ppָ����ڵ�ĸ��ڵ㣨�ǳ�ʼʱ��
	BinaryTreeNode<T>* p = BSTree<T>::root, * pp = 0;
	while (p && p->data != t)
	{
		pp = p;
		if (t < p->data)
			p = p->LeftChild;
		else
			p = p->RightChild;
	}
	//��p�����ڵ�ʱ��˵���ؼ�ֵΪk��Ԫ�ز����ڣ��׳��쳣����
	if (!p)
		throw BadInput();
	//�ҵ�Ҫɾ����Ԫ���ˣ�t������������ֵ
	t = p->data;
	//Ҫɾ���ڵ�����ҽڵ㶼���ڵ������
	if (p->LeftChild && p->RightChild)
	{
		//ʹsָ��p�����ӣ�psָ��p
		BinaryTreeNode<T>* s = p->LeftChild, * ps = p;
		//�ҵ�������һ���������һ���Һ�����s����ʾ��ps��ʾs�ĸ��ڵ�
		while (s->RightChild)
		{
			ps = s;
			s = s->RightChild;
		}
		//s�����������Ҫɾ���Ľڵ㣬���ˣ��������������ڵ�����´������
		p->data = s->data;

		//���s����ڵ㣬��Ҫ��sɾ������ڵ����������ƶ�p��ppλ��Ϊ����Ĵ����̵�
		//pΪ������һ���������һ���Һ���s
		p = s;
		//ppΪs�ĸ��ڵ�
		pp = ps;
	}

	BinaryTreeNode<T>* c;
	//��p��������ʱ(��������һ��ifѭ��)����p������������������һ��ʱ��û�����ϸ�ifѭ����
	if (p->LeftChild)
		c = p->LeftChild;
	else
		c = p->RightChild;
	//���p�Ǹ��ڵ�ֱ�Ӱ�c��ֵ�����ڵ�
	if (p == BSTree<T>::root)
		BSTree<T>::root = c;
	//p���Ǹ��ڵ�Ļ�����pp��p�Ĺ�ϵ���Ӷ�����pp��c�Ĺ�ϵ
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