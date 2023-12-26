// week7work2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
struct word
{ // 存储输入的字符
    char c;
    double fre;
} *article; // 存储所有的字符（不重复存储）

int capacity = 0; // article的实际容量

int find(char ch)
{ // 找到字符
    for (int i = 0; i < capacity; i++)
    {
        if (article[i].c == ch)
            return i;
    }
    return capacity;
}

void input(string s)
{                                   // 输入文章
    article = new word[s.length()]; // 初始化
    for (int i = 0; i < s.length(); i++)
    {
        article[i].c = ' ';
        article[i].fre = 0;
    }
    for (int i = 0; i < s.length(); i++)
    {
        int mark = find(s[i]);
        if (article[mark].c != s[i])
        {                           // 如果该字符不存在
            article[mark].c = s[i]; // 存储字符
            capacity++;
        }
        article[mark].fre++; // 出现的次数+1
    }
    for (int i = 0; i < capacity; i++) // 计算频率
        article[i].fre /= s.length();
}

int compare(word w1, word w2)
{ // 定义struct如何比较大小（根据频率）
    return w1.fre < w2.fre;
}

class node
{ // 结点类
public:
    word data;
    node* next;
};

class BinaryTree;

class treeNode
{
    friend BinaryTree; // 声明友元
public:
    treeNode()
    {
        parent = leftchild = rightchild = NULL;
    }
    treeNode(const word& t)
    {
        data = t;
        parent = leftchild = rightchild = NULL;
    }
    treeNode(const word& t, treeNode* l, treeNode* r)
    {
        data = t;
        leftchild = l;
        rightchild = r;
        leftchild->parent = this;
        rightchild->parent = this;
    }
    word data;
    treeNode* parent; // 父节点
    treeNode* leftchild;
    treeNode* rightchild;
};

class wordList
{ // 存储字符的链表
public:
    bool isEmpty()
    {
        return head == NULL;
    }
    wordList& initialize(string s)
    {                                               // 初始化
        input(s);                                   // 输入所有的字符
        sort(article, article + capacity, compare); // 按照频率大小整理
        node* p = new node;
        p->data = article[capacity - 1]; // 获取频率最大的字符
        head = p;                        // 把它放在链表头节点
        head->next = NULL;
        for (int i = capacity - 2; i >= 0; i--)
        {
            // 按从大到小的顺序遍历article，好处是每次插入只需要更新头节点，不需要遍历整个链表
            // 全部插入后链表依然是从小到大的顺序
            node* q = new node;
            q->data = article[i];
            q->next = head;
            head = q;
        }
        // 按顺序输出存进链表后的字符及其频率
        cout << endl
            << "Word list:" << endl;
        p = head;
        while (p)
        {
            cout << p->data.c << " " << p->data.fre << endl;
            p = p->next;
        }
        cout << endl;
        return *this;
    }
    wordList& deleteHead()
    { // 删除头节点
        if (!isEmpty())
        {
            head = head->next;
        }
        return *this;
    }
    wordList& insert(node* w)
    {
        // 按照频率大小顺序，插入节点
        // 由于链表有序，可以推定每次搜索只需要搜索前几个就能找到应该插入的位置
        // 因此时间复杂度推定总是远小于n
        node* pre = new node;
        pre = w;
        pre->next = NULL;
        if (isEmpty())
        {
            head = pre;
            return *this;
        }
        node* p = head;
        while (p->next && p->next->data.fre < w->data.fre)
            p = p->next;
        pre->next = p->next;
        p->next = pre;
        return *this;
    }
    node* head;
};

class BinaryTree
{ // 二叉树
public:
    BinaryTree()
    {
        root = NULL;
        count = 0;
    }
    BinaryTree(treeNode* n)
    {
        root = n;
        count = 0;
    }
    bool isEmpty()
    {
        return ((root == NULL) ? true : false);
    }
    treeNode* getRoot()
    { // 返回根节点
        return root;
    }
    void combine(const word& t, BinaryTree& left, BinaryTree& right)
    { // 合并树
        root = new treeNode(t, left.root, right.root);
        left.root = right.root = NULL;
    }
    BinaryTree& huffmanTree(wordList w);
    treeNode* find(treeNode* t, word w)
    {                        // 根据字符找到叶节点
        queue<treeNode*> q; // 存储有左右子树的节点
        while (t)
        {
            if (t->data.c == w.c && t->data.fre == w.fre)
                return t;
            if (t->leftchild)
                q.push(t->leftchild); // 入队
            if (t->rightchild)
                q.push(t->rightchild);
            if (!q.empty())
            {
                t = q.front();
                q.pop(); // 出队
            }
            else // 队列为空时退出（仅限于完全二叉树）
                break;
        }
        return NULL;
    }
    void code()
    { // 根据哈夫曼树，输出哈夫曼编码
        for (int i = 0; i < capacity; i++)
        {                           // 遍历article的所有字符，输出它的编码
            int* hc = new int[100]; // 存储每个字符的编码
            int index = 0;
            treeNode* p = find(root, article[i]); // 找到该字符所在的叶节点
            while (p != root)
            {
                if (p->parent)
                { // 向上找父节点
                    if (p->parent->leftchild == p)
                        hc[index] = 0; // 左孩子编码为0
                    else
                        hc[index] = 1; // 右孩子编码为1
                    index++;
                    p = p->parent; // 继续向上，直到根节点
                }
            }
            cout << article[i].c << " : ";
            // 注意这里要倒序输出，因为存储是从叶节点开始存的
            for (int j = index - 1; j >= 0; j--)
                cout << hc[j];
            cout << endl;
        }
        cout << endl;
    }
    void decode(string key)
    {                           // 根据输入的编码，解码
        int* hc = new int[100]; // 把输入的字符串转为编码
        int index = 0;
        for (int i = 0; i < key.length(); i++)
        {
            if (key[index] == '0')
                hc[index] = 0;
            else if (key[index] == '1')
                hc[index] = 1;
            else
            {
                cout << "Wrong input!" << endl;
                return;
            }
            index++;
        }
        treeNode* p = root; // 从根节点开始
        for (int i = 0; i < index; i++)
        {
            if (hc[i] == 0) // 编码为0跳到左孩子
                p = p->leftchild;
            else // 编码为1跳到右孩子
                p = p->rightchild;
            if (!p)
            { // 如果结点为空则为错误输入
                cout << "Wrong input!" << endl;
                return;
            }
        }
        if (!p)
        { // 如果结点为空则为错误输入
            cout << "Wrong input!" << endl;
            return;
        }
        cout << "Decode: " << p->data.c << endl
            << endl; // 输出解码结果
    }
    treeNode* root; // 根节点
    int count;      // 森林里的树的个数
};

BinaryTree* bt = new BinaryTree[100];
// 森林，因为哈夫曼编码过程中可能出现多个二叉树

BinaryTree& BinaryTree::huffmanTree(wordList w)
{ // 构造哈夫曼树
    // 当字符链表有两个以上元素，即还没有把所有的字符串到一棵树上
    while (w.head->next)
    {
        word temp; // 把两个频率最低的字符串起来
        temp.c = ' ';
        temp.fre = w.head->data.fre + w.head->next->data.fre;
        treeNode* nl = new treeNode; // 左节点
        int i = 0;
        // 在森林里寻找是否有该字符，即频率最低的是多个字符的和还是单个字符
        for (; i < count; i++)
        {
            if (bt[i].root && bt[i].root->data.c == w.head->data.c && bt[i].root->data.fre == w.head->data.fre)
                break;
        }
        // 如果是单个字符
        if (i == count)
            nl->data = w.head->data;
        // 如果是多个字符的和
        else
        {
            nl = bt[i].root;
            bt[i].root = NULL; // 用过的树记得删除
        }
        treeNode* nr = new treeNode; // 右节点
        i = 0;
        for (; i < count; i++)
        {
            if (bt[i].root && bt[i].root->data.c == w.head->next->data.c && bt[i].root->data.fre == w.head->next->data.fre)
                break;
        }
        if (i == count)
            nr->data = w.head->next->data;
        else
        {
            nr = bt[i].root;
            bt[i].root = NULL;
        }
        BinaryTree tempLeft(nl);
        BinaryTree tempRight(nr);
        combine(temp, tempLeft, tempRight); // 合并树
        bt[count].root = root;              // 把新的树存到森林里
        count++;                            // 森林的树数目加一
        w.deleteHead();                     // 删除头节点
        w.deleteHead();
        node* tr = new node;
        tr->data = temp;
        w.insert(tr); // 把新的树的频率存进字符链表里，等待下一次运算
    }
    return *this;
}

int main()
{
    string s;
    cout << "Please input str:" << endl;
    cin >> s;
    wordList w;
    w.initialize(s);
    BinaryTree b;
    b.huffmanTree(w);
    cout << "Huffman code:" << endl;
    b.code();
    cout << "Please input huffman code: ";
    string key;
    for (int i = 0; i < 4; i++)
    {
        cin >> key;
        b.decode(key);
    }
    system("pause");
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
