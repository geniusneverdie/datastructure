// week1work2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<iostream>
#include<algorithm>
#include<string>
#include<stack>
#include<list>
#include<algorithm>
#include<unordered_map>
#include<fstream>
using  namespace  std;
using Iter = list<int>::iterator;
unordered_map<char, int>p;
#define ull unsigned long long
const int Maxn = 1010;
char arr[Maxn];
int exi = 0;
int t = 0;
int arr1[Maxn] = { 0 };
void f(int n)
{
    if (n == t)
    {
        int exii = 0;
        for (int i = 0; i < t; i++)
        {
            if (arr1[i] == 1)
            {
                if (exii == 0)
                {
                    cout << arr[i];
                    exii = 1;
                }
                else cout << " " << arr[i];
            }
        }
        cout << endl;
        return;
    }
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            arr1[n] = 1;
            f(n + 1);
        }
        else
        {
            arr1[n] = 0;
            f(n + 1);
        }
    }
}
int main()
{
    cin.getline(arr, Maxn);
   /* ifstream in("input.txt");*/
    /*if (!in.is_open())
    {
        cout << "can not open this file" << endl;
        return 0;
    }*/
    
    int n=0;
    /*in >> n;
    char* arr = new char[n+1];
    *(arr + n) = '/0';*/
    for (int i = 0; i < n; i++)
    {
        arr[i] = 'a' + i;
    }
    for (int i = 0; i < strlen(arr); i++)
    {
        if (p[arr[i]] > 0)
        {
            cout << "WRONG" << endl;
            return 1;
        }
        p[arr[i]] = 1;
    }
    t = strlen(arr);
    if (t == 0)
    {
        cout << endl;
        return 0;
    }
    f(0);
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
//#include<iostream>
//#include<fstream>
//using namespace std;
//void meiko(char a[], bool* b, int cur, int n)
//{
//    if (cur == n)
//    {
//        for (int i = 0; i < n; i++)
//        {
//            if (b[i])
//            {
//                cout << a[i] << " ";
//            }
//        }
//        cout << endl;
//    }
//    else
//    {
//        b[cur] = true;
//        meiko(a, b, cur + 1, n);
//        b[cur] = false;
//        meiko(a, b, cur + 1, n);
//    }
//}
//
//int  main() {
//    ifstream file("input.txt", ios::in);
//    int n;
//    file >> n;
//    file.close();
//    char a[26];
//    if (n > 0 && n <= 26) {
//        for (int i = 0; i < n; i++)
//        {
//            a[i] = 'a' + i;
//        }
//        bool* b = new bool(n);
//        meiko(a, b, 0, n);
//    }
//    else
//    {
//        cout << "WRONG" << endl;
//    }
//    return 0;
//}



