// week4work3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<math.h>
using namespace std;
int main()
{
    int n=0, m=0;
    int a[20], b[20];
    int k = 0;
    int s = 0;
    cin >> n>>m;
    for (int i = 2; i < sqrt(n); i++)
    {
        if (n % i == 0)
        {
            a[k] = i;
            k++;
        }
    }
    for (int i = 2; i < sqrt(m); i++)
    {
        if (m % i == 0)
        {
            b[s] = i;
            s++;
        }
    }
    for (int i = 0; i < 20; i++)
    {
        for (int k = 0; k < 20; k++)
        {
            if (a[i] == b[k]&&a[i]>0&&a[i]<sqrt(n))
            {
                cout << "ERROR";
                system("pause");
                i = k = 20;
            }

        }
        if (i == 19)
        {
            int l = 0;
            int d[20];
            for (int e = 0; e < n; e++)
            {
                d[e] = e;
            }
            for (int e = 0; e < n; e++)
            {
                l += m;
                
                if (l > n)
                {
                    l -= n;
                  
                }
                if (l <= n)
                {
                    cout << d[l];
                    for (int r = l; r < 20; r++)
                    {
                        d[r-1] = d[r];
                    }
                }
            }
            
        }
    }
    return 0;
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
