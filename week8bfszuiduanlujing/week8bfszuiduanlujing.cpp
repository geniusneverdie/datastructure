// week8bfszuiduanlujing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MaxN = 100;
vector<int> g[MaxN];
int start, End;
int re[MaxN], vi[MaxN];
int m, n;
int len;


bool bfs(int v, int label)
{// 进行广度优先搜索， reach[i] 用来标记从顶点v可到达的所有顶点
	len = 1;
	queue<int>q;
	re[v] = label;
	q.push(v);
	while (!q.empty())
	{
		// 从队列中删除一个标记过的顶点
		int w = q.front();
		q.pop();
		if (w == End)
			break;
		// 标记所有没有到达的邻接于顶点w的顶点
		int u;
		for (int i = 0; i < g[w].size(); i++)
		{
			u = g[w][i];
			if (!vi[u])
			{
				len++;
				re[u] = w;
				vi[u] = 1;
				q.push(u);
			}//对于每一个新接入点
		}
	}
	if (len == 1)
		return false;
	return true;
}
//使用bfs编写findpath函数
bool findpath_bfs(int S, int E) {
	re[1] = S;
	len = 1;
	End = E;
	fill(vi, vi + n, 0);
	if (S == E || bfs(S, 1)) {
		re[0] = 0;
		return true;
	}
	return false;
}
//输出路径上的节点号
void show_bfs(int x) {
	if (x == start) {
		cout << x << " ";
		return;
	}
	show_bfs(re[x]);
	cout << x << " ";
	re[0]++;
}
int main() {
	cout << "请输入节点数和边数" << endl;
	cin >> n >> m;
	int u, v;
	cout << "请输入每条边两个节点编号" << endl;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	cout << "请输入起始节点和终止节点" << endl;
	cin >> start >> End;
	if (findpath_bfs(start,End))//进行bfs路径和其最小长度的输出
	{
		cout << "bfs路径:";
		show_bfs(End);
		cout << endl;
		cout << "bfs路径长度:" << re[0] << endl;
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
