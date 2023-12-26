// week3work3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<iostream>
#include<algorithm>
#include<vector>
#include<fstream>
using namespace std;
const int Maxn = 1000;

class linkedmatrix {
public:
    vector<vector<int>>arr;
    void store(int i, int j, int a) 
    {
        vector<int>temp;
        temp[0] = i;
        temp[1] = j;
        temp[2] = a;
        vector<vector<int>>::iterator t = arr.begin();
        for (int k = 0; k < arr.size(); k++) 
        {
            if (i >= arr[k][0] && i <= arr[k + 1][0]) 
            {
                if ((i == arr[k][0] && j >= arr[k][1]) || i > arr[k][0])
                {
                    arr.insert(t, k, temp);//插入的方式
                }
            }
        }
        //    arr.push_back(temp);
    }
    int get(int i, int j) //已知行和列求值
    {
        for (int k = 0; k < arr.size(); k++) 
        {
            if (arr[k][0] == i && arr[k][1] == j)
                return arr[k][2];
        }
        return -1;
    }

    linkedmatrix add(linkedmatrix& b) //加法
    {
        linkedmatrix c;
        int x = 0, y = 0;
        for (int k = 0; k < arr.size() + b.arr.size(); k++) 
        {
            if (arr[k][0] > b.arr[k][0]) 
            {
                c.arr.push_back(arr[k]);
            }
            else if (arr[k][0] < b.arr[k][0])
            {
                c.arr.push_back(b.arr[k]);
            }
            else 
            {
                if (arr[k][1] > b.arr[k][1])
                {
                    c.arr.push_back(arr[k]);
                }
                else if (arr[k][1] < b.arr[k][1]) 
                {
                    c.arr.push_back(b.arr[k]);
                }
                else
                {
                    if (arr[k][2] + b.arr[k][2] != 0) 
                    {
                        vector<int>temp;
                        temp[0] = arr[k][0];
                        temp[1] = arr[k][1];
                        temp[2] = arr[k][2] + b.arr[k][2];
                        c.arr.push_back(temp);
                    }
                }
            }
        }
        return c;
    }
    linkedmatrix mina(linkedmatrix& b) //减法
    {
        linkedmatrix c;
        int x = 0, y = 0;
        for (int k = 0; k < arr.size() + b.arr.size(); k++)
        {
            if (arr[k][0] > b.arr[k][0]) 
            {
                c.arr.push_back(arr[k]);
            }
            else if (arr[k][0] < b.arr[k][0]) {
                c.arr.push_back(b.arr[k]);
            }
            else {
                if (arr[k][1] > b.arr[k][1])
                {
                    c.arr.push_back(arr[k]);
                }
                else if (arr[k][1] < b.arr[k][1]) {
                    c.arr.push_back(b.arr[k]);
                }
                else {
                    if (arr[k][2] + b.arr[k][2] != 0) {
                        vector<int>temp;
                        temp[0] = arr[k][0];
                        temp[1] = arr[k][1];
                        temp[2] = arr[k][2] - b.arr[k][2];
                        c.arr.push_back(temp);
                    }
                }
            }
        }
        return c;
    }
    linkedmatrix muti(linkedmatrix& b) //普通乘
    {
        linkedmatrix c;
        int x = 0, y = 0;
        for (int k = 0; k < arr.size() + b.arr.size(); k++) 
        {
            if (arr[k][0] > b.arr[k][0]) 
            {
                //  c.arr.push_back(arr[k]);
            }
            else if (arr[k][0] < b.arr[k][0]) {
                //c.arr.push_back(b.arr[k]);
            }
            else 
            {
                if (arr[k][1] > b.arr[k][1])
                {
                    // c.arr.push_back(arr[k]);
                }
                else if (arr[k][1] < b.arr[k][1]) 
                {
                    // c.arr.push_back(b.arr[k]);
                }
                else {
                    // if(arr[k][2]+b.arr[k][2]!=0){
                    vector<int>temp;
                    temp[0] = arr[k][0];
                    temp[1] = arr[k][1];
                    temp[2] = arr[k][2] * b.arr[k][2];
                    c.arr.push_back(temp);
                    //  }
                }
            }
        }
        return c;
    }
    friend ostream& operator >>(ostream& out, linkedmatrix a) //矩阵输出
    {
        for (int k = 0; k < a.arr.size(); k++)
        {
            cout << a.arr[k][2];//判断是否有值，并且找到位置按照格式输出
            if (a.arr[k][0] != a.arr[k + 1][0])
                cout << endl;
            else if (k < a.arr.size() - 1)
                cout << " ";
        }
        return out;
    }
    linkedmatrix reverse() //转置
    {
        linkedmatrix c;
        vector<int>arr1;
        for (int k = 0; k < arr.size(); k++) 
        {
            arr1[arr[k][1]]++;
        }
        vector<int>arr2;
        arr2[0] = 0;
        for (int k = 1; k < arr1.size(); k++)
        {
            arr2[k] = arr2[k - 1] + arr1[k];//求出转置矩阵当中的位置
        }
        vector<vector<int>>::iterator t = arr.begin();//赋初始节点的值
        for (int k = 0; k < arr.size(); k++) {
            vector<int>temp = arr[k];
            temp[0] = arr[k][1];
            temp[1] = arr[k][0];
            c.arr[arr2[k]] = temp;
            arr2[k]++;
        }
        return c;
    }
    linkedmatrix jumuti(linkedmatrix b)//矩阵乘法
    {
        linkedmatrix c;
        linkedmatrix bT = b.reverse();//令一个先转置，才方便进行乘
        int r0 = 0;//遍历到的行
        for (int k = 0; k < arr.size(); k++) {
            int q = 0;
            while (b.arr[q][0] != arr[k][1])q++;
            if (b.arr[q][0] > arr[k][1])continue;
            else //判断是否全为空，如果不是，可以进行乘法运算
            {
                while (b.arr[q][0] == arr[k][1]) 
                {
                    vector<int>temp;
                    temp[0] = arr[k][0];
                    temp[1] = arr[q][1];
                    temp[2] = arr[k][2] * arr[q][2];
                    c.arr.push_back(temp);
                }
            }
        }
        return c;
    }
};
int main()
{   
    
   linkedmatrix t;
    t.store(1, 1, 1);
    /*
    linkedmatrix t;
    vector<int>temp1;
    temp1[0] = 1;
    temp1[1] = 1;
    temp1[2] = 2;
    t.arr = vector<vector<int>>arr;
    arr.insert(t, 0, temp1);

    linkedmatrix s;
    vector<int>temp1;
    temp1[0] = s.arr[0][0];
    temp1[1] = s.arr[0][1];
    temp1[2] = s.arr[0][2];
        */
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
