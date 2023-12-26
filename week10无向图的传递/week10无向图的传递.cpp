// week10无向图的传递.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
using namespace std;

const int N = 100;
int n, m, label;
int vi[N], fl[N];
vector<int> g[N];
void dfs(int x, int reach[], int label)
{// 深度优先搜索. reach[i] 用来标记所有邻接于顶点v的可到达的顶点
	reach[x] = 1;
	fl[x] = label;
	for (int i = 0; i < g[x].size(); i++)//对于每个未到达的节点进行搜索
	{
		int y = g[x][i];
		if (reach[y] == 0)// y 是一个没有到达的顶点
		{
			// 深度优先搜索递归方法
			dfs(y, reach, label);
		}
	}
}
int lablecomponents(int c[])
{// 给无向图的构件做标记
	// 返回构件的个数
	// 令 c[i] 是顶点 i 的构件号
	fill(c, c + n + 1, 0);
	label = 0;
	for (int i = 1; i <= n; i++)
	{
		if (c[i] == 0)// 顶点 i 未到达
		{// 顶点 i 是一个新构件
			dfs(i, c, label); // 给新构件做标记 
			label++;
		}
	}
	return label;
}
int main() {
	cout << "请输入节点数和边数" << endl;
	cin >> n >> m;
	cout << "请输入每条边两边的节点编号" << endl;
	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}//输入并进行图的初始化存储
	lablecomponents(vi);
	cout << endl;
	for (int i = 1; i <= n; i++) 
	{
		for (int j = 1; j <= n; j++) 
		{
			if (fl[i] == fl[j] && i != j)
				cout << "1 ";
			else
				cout << "0 ";
		}
		//判断每个点的距离是否相等
		cout << endl;
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
