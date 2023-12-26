// week2work3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<iostream>
#include<algorithm>
#include<string>
#include<stack>
#include<list>
#include<algorithm>
#include<unordered_map>
using  namespace  std;
using Iter = list<int>::iterator;
const int Maxn = 1000;

class Node//定义一个节点，并且同时定义头指针和尾指针，并指向this
{
public:
    int data;
    Node* next;
    Node* back;
    Node(int x)
    {
        data = x;
        next = this;
        back = this;
    }
};
class extendedChain//定义类
{
public:
    Node* first;
    extendedChain()//把头节点赋初值
    {
        first = new Node(0);
    }
    void add(int x)//定义一个add函数用于把新的值赋给新节点
    {
        if (first == NULL)//节点为空，需要新开空间
        {
            first = new Node(x);
            return;
        }
        else
        {
            Node* temp = first;//把临时指针指向节点
            while (temp->next != first)temp = temp->next;//让指针指向下一个节点
            temp->next = new Node(x);//让这个节点的指针指向新赋值的单位
            temp->next->back = temp;//让这个节点指针的尾指针指向上一个节点
            temp->next->next = first;//让最后一个节点的尾指针指向头节点
        }
    }
   // friend extendedChain meld(extendedChain a, extendedChain b);
    friend extendedChain split(extendedChain c);
};
////extendedChain meld(extendedChain a, extendedChain b)
//{
//    extendedChain c;
//    Node* pa, * pb;
//    pa = a.first;
//    pb = b.first;
//    while (pa != NULL && pb != NULL)
//    {
//        c.add(pa->data);
//        pa = pa->next;
//        c.add(pb->data);
//        pb = pb->next;
//    }
//    while (pb != NULL)
//    {
//        c.add(pb->data);
//        pb = pb->next;
//
//    }
//    while (pa != NULL)
//    {
//        c.add(pa->data);
//        pa = pa->next;
//    }
//    return c;
//}
void  split(extendedChain c, extendedChain a, extendedChain b)//定义一个函数按照题目要求赋值
{
    Node* curr = c.first->next;
    for (int i = 0; curr != c.first; i++)
    {
        if (i % 2 == 0)
            a.add(curr->data);//索引为偶数给a赋值
        else
        {
            b.add(curr->data);//索引为奇数给b赋值
        }
        curr = curr->next;//向后遍历
    }
}
char arr[Maxn];
int arr1[Maxn] = { 0 };//初始化一个arr1
int main()
{
    int a = 0;
    extendedChain arr1;//将arr1的头四个节点赋值为1，2，3，4
    arr1.add(1);
    arr1.add(2);
    arr1.add(3);
    arr1.add(4);
        cout<<arr1.first->next->next->data<<endl;
        extendedChain arr2;
        extendedChain arr3;
    split(arr1, arr2, arr3);//定义arr2,arr3并且按照函数赋初值
    cout << arr2.first->next->data << endl;
    cout << arr3.first->next->data << endl;
    cout << arr2.first->next->next->data << endl;
    cout << arr3.first->next->next->data << endl;
    return  0;
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
