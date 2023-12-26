// week6work3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<iostream>
#include<stack>
#include<queue>
#include<cstring>
#include <iomanip>
using namespace std;
class node {//初始化二叉树
public:
	char data;
	node* left;
	node* right;
	node(char x) {
		data = x;
		left = right = NULL;
	}
};
//中缀表达式转后缀表达式
string zztohz(string s) //运用栈的方法进行对字符和操作符输入输出
{
	int l = s.length();
	string target;
	string a;
	stack<char>sk;//定义需要的栈
	for (int i = 0; i < l; i++) {
		char temp = (char)s[i];
		switch (temp)//判断左右括号左入栈右出栈
		{
		case'(':
			sk.push(temp);
			break;
		case')':	
			while (sk.top() != '(') //当栈顶不是左括号的时候
			{
				a = sk.top();
				target.append(a);
				sk.pop();//定义新的a占栈顶的位置方便出栈
			}
			sk.pop();
			break;
		case'+':
		case'-'://加减法的优先级低，只需要考虑有没有括号
			if (sk.empty() || sk.top() == '(')//栈顶只有一个左括号，直接压栈输出
				sk.push(temp);
			else {
				while (!sk.empty() && sk.top() != '(') //栈非空且栈顶不是左括号
				{
					a = sk.top();
					target.append(a);
					sk.pop();//a在栈顶的情况需要一起出栈
				}
				sk.push(temp);
			}
			break;
		case'*':
		case'/'://乘除法优先级最大
			if (sk.empty() || (sk.top() != '/' && sk.top() != '*'))sk.push(temp);//栈顶不是乘除法，则此操作符就是要出栈的
			else {
				a = sk.top();
				target.append(a);
				sk.pop();
				sk.push(temp);
			}
			break;
		default://输入的全都不是
			a = temp;
			target.append(a);
			break;
		}
	}
	while (!sk.empty())//栈不是空的需要有占位元素
	{
		a = sk.top();
		target.append(a);
		sk.pop();
	}
	return target;
}
class binarytree {//定义输出的后序二叉树
public:
	node* root = NULL;
	binarytree(string st) {//构造函数将字符串转成二叉树
		string s = zztohz(st);
		int l = s.length();
		stack<node*>sk;
		for (int i = 0; i < l; i++) 
		{
			char t = (char)s[i];
			if (t != '+' && t != '-' && t != '*' && t != '/')//当输入的不是操作符即为数字或字母
			{
				root = new node(t);
				sk.push(root);//入栈操作
			}
			else {
				root = new node(t);//否则定义新节点之后进行出栈操作
				if (!sk.empty()) {
					root->right = sk.top();//栈在非空的时候头节点出栈的同时需要左右孩子入栈
					sk.pop();
				}
				if (!sk.empty()) {
					root->left = sk.top();
					sk.pop();
				}
				sk.push(root);
			}
		}
	}
	int depth(node* p) {//递归计算树高
		if (p == NULL)return 0;
		int i = depth(p->left);
		int j = depth(p->right);
		return i > j ? i + 1 : j + 1;
	}
	void output(node* root, int depth1) {//定义输出树高的操作
		if (root != NULL)
		{
			output(root->right, depth1 + 1);
			cout << setw(4 * (depth1 - 1)) << " ";
			cout << root->data << endl;
			output(root->left, depth1 + 1);
		}
	}
	int leafnum(node* p) {//求叶子节点的数目
		if (p->left == NULL && p->right == NULL) return 1;
		int i = leafnum(p->left);
		int j = leafnum(p->right);
		return i + j;
	}
	void changelr(node* p) //定义创建中序树的操作
	{
		if (p != NULL) {
			node* t = p->left;
			p->left = p->right;
			p->right = t;
			changelr(p->left);
			changelr(p->right);
		}
	}
	void bianli() {//定义对书的遍历操作用队列的方式进行遍历
		queue<node*>qe;
		qe.push(root);//定义新队列，先把根节点进入队列
		while (!qe.empty()) {
			node* p = qe.front();
			cout << p->data << " ";
			qe.pop();
			if (p->left)qe.push(p->left);
			if (p->right)qe.push(p->right);//根节点出栈的同时，判断有无孩子节点，如果有孩子节点，则孩子节点入栈
		}
		cout << endl;
	}
	int width() {//求最大宽度的函数
		int width = 0;
		queue<node*>qe;
		qe.push(root);
		while (1) {
			if (qe.empty())break;
			else {
				int l = qe.size();//每进行一步操作，时刻定义此时的队列宽度
				for (int i = 0; i < l; i++) {//l记录上一层有多少个结点，然后把每个结点的左右节点分别插入到队列里后，弹出该节点。
					node* p = qe.front();//同时比较现在的队列大小（下一层节点数量）和width大小，进行更新。
					if (p->left)qe.push(p->left);
					if (p->right)qe.push(p->right);
					qe.pop();
				}
				width = width > qe.size() ? width : qe.size();//时刻判断宽度是否是比上一层大，如果大就改变width
			}
		}
		return width;
	}
};
int main() {
	string s;
	cin >> s;
	string s1 = zztohz(s);
	binarytree b(s);//每进行一步输入都需要构造列表和二叉树

	b.output(b.root, 1);
	cout << endl;
	cout << b.depth(b.root) << endl;
	b.changelr(b.root);
	b.output(b.root, 1);
	b.bianli();
	cout << b.leafnum(b.root) << endl;
	cout << b.width();
}


//实现思路：对于前两问，用递归很容易实现。第三问需要层次遍历，显然不能用递归。
// 对于每个节点，访问时是先进先出的，所以应该利用队列。每个节点输出之后，
// 就要接着判断他的两个孩子节点是否可以入队，
// 这样的话就实现了从上到下，从左到右的入队顺序，即输出顺序。
// 第四问和第三问的思路很类似，需要利用的就是每次上一层节点全输出完毕之后，
//队列里留下的就是他们的所有孩子的节点，也就是下一层的节点数量。不断对比进行更新width就可以了。6
/*1 a
2 1 b
3 1 c
4 2 d
5 2 e
6 3 f
7 3 g
*/


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
