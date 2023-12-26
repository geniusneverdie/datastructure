// week5work12.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//同一个尾节点的有序列表

#include<iostream>
#include<limits.h>
using namespace std;
class node {//初始化列表
public:
	int data;
	node* next;
	node(int x) {
		data = x; next = NULL;
	}
	node() { data = 0; next = NULL; }
};
class hashChainsWithTail //定义需要的散列列表
{
public:
	node** hcf;
	node* tail;//不同的头节点，相同的尾节点
	int divisor;
	hashChainsWithTail(int x) {
		divisor = x;
		hcf = new node * [x];
		tail = new node(INT_MAX);//头尾节点初始化
		for (int i = 0; i < divisor; i++) {
			hcf[i] = new node;
			hcf[i]->next = tail;
		}
	}
	bool search(int k) {//列表当中实现查找操作
		int i = k % divisor;//找到在哪条子链表
		node* p = hcf[i];
		for (p = p->next; p->data <= k; p = p->next);//向后遍历直到找到
		if (p->data == k) return true;
		return false;
	}
	void insert(int k) {//列表当中实现插入操作
		int i = k % divisor;
		node* newnode = new node(k);
		node* p = hcf[i];//找到需要插入的子链表
		if (p->next == tail) {//节点在尾节点前面的节点
			p->next = newnode;
			newnode->next = tail;
		}
		else {//不在尾节点前面
			for (; p->next != tail && p->next->data <= k; p = p->next);
			newnode->next = p->next;
			p->next = newnode;
		}
	}
	void remove(int k) {//定义删除操作，因为不会删除尾节点所以不用判断
		int i = k % divisor;
		node* p = hcf[i];
		for (; p->next->data != k; p = p->next);
		node* q = p->next;
		p->next = q->next;
		delete q;
	}
	void print() {//对链表进行输出
		for (int i = 0; i < divisor; i++) {
			node* p = hcf[i];
			for (p = p->next; p != tail; p = p->next) cout << p->data << ' ';
			cout << endl;
		}
		cout << "输出完毕" << endl;
	}
};
int main() {
	hashChainsWithTail h(11);
	int n;
	for (int i = 0; i < 11; i++) {
		cin >> n;
		h.insert(n);
	}
	h.print();
	h.remove(16);
	h.print();
	h.remove(29);
	h.print();
	h.remove(27);
	h.print();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
//测试数据：5 16 6 29 33 14 27 20 48 32 7