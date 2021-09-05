# 这是一个错题本，类似摘抄的东西
## 前情提要
这个是基于浙江大学mooc的PTA平台的题目。也不知道以后会不会有乱七八糟的题目加进来。

如果有的话也许会标记出处

目前写的都是c++  
**还有就是这个文档目前只支持最基础的markDown语法！**  
**那么就开始吧！**
## 01-复杂度2 Maximum Subsequence Sum
### 题目
>给定一个序列 到 整数{ N 1
​ , N 2, ..., N 到}. 一个连续的子序列被定义为{N 一世
​, N我+ 1, ..., N j} 在哪里 1≤一世≤j≤到. 最大子序列是其元素之和最大的连续子序列。例如，给定序列 { -2, 11, -4, 13, -5, -2 }，其最大子序列为 { 11, -4, 13 }，最大和为 20。

>现在你应该找到最大的和，以及最大子序列的第一个和最后一个数字。

>对于每个测试用例，在一行中输出最大的和，以及最大子序列的第一个和最后一个数字。数字必须由一个空格分隔，但行尾不得有多余空格。如果最大子序列不唯一，则输出索引最小的那个一世 和 j（如示例案例所示）。如果所有的到 numbers 为负，则其最大和定义为 0，您应该输出整个序列的第一个和最后一个数字。
### 解法
 #### 1. 暴力法

```c++
#include <iostream>
using namespace std;
//加法程序，将数组里的所有元素相加
int add(int a[], int start, int end)
{
    int res = 0;
    for (int i = start; i <= end; i++)
    {
        res += a[i];
    }
    return res;
}

int main()
{
    int count, *p;
    cin >> count;
    p = new int[count];//新建数组
    bool yep = false;
    for (int i = 0; i < count; i++)
    {
        cin >> p[i];
        if (p[i] >= 0)
        {
            yep = true;//用于判断输入是否全是负数
        }
    }
    int max = 0, start = 0, end = 0;
    for (int i = 0; i < count; i++)
    {
        for (int j = i; j < count; j++)
        {
            int temp = add(p, i, j);
            if (temp > max)
            {
                max = temp;
                start = p[i];//记录开始与结束的数
                end = p[j];
            }
        }
    }
    if (max == 0 && yep == false)//用于处理全是负数的情况
    {
        start = p[0];
        end = p[count - 1];
    }
    cout << max << " " << start << " " << end;
}
```


#### 2. 在线处理法
```c++
#include <iostream>
using namespace std;
int main()
{
    int a, max, temp, s, startT, start, end, endT;
    cin >> a;
    temp = max = start = 0;
    startT = 0;
    bool yep = false;
    bool IsStart=false;
    for (int i = 0; i < a; i++) //正常在线处理
    {
        cin >> s;
        if(IsStart){//更新开头StartTemp
            startT=s;
            IsStart=!IsStart;
        }
        if (s >= 0)
            yep = true;
        if (i == 0) //当第一次循环的时候，给StartTemp一个初始值
        {
            startT = s;
            start = s;
        }
        temp += s;
        if (temp < 0)//这里有一个逻辑问题，没有先判断子串和大小，直接给start赋值，应当利用好StartT
        {//已修复
            temp = 0;
            IsStart = true;
        }
        else if (temp > max)//对start和end进行更新
        {
            max = temp;
            end = s;
            start=startT;
        }
        if (i == a - 1 && yep == false)
        {
            end = s;
            //start = startT;
        }
    }
    if(max==0&&yep){//专门判断只有负数与0的情况
        start=end=0;
    }
    cout << max << " " << start << " " << end << endl;
}
```
>最后是只有在线处理能够全部通过，暴力法会超时。
最后能通过真的是太高兴了。

>+ 反思：
>> + 目前的水平还是太菜，很多算法的思想无法理解，逻辑也很混乱，希望在下一个任务中可以改善
>> + 都写得是什么破玩意啊我

## 07-树2List Leaves
### 题目
>给定一棵树，你应该按照从上到下、从左到右的顺序列出所有的叶子。

>对于每个测试用例，按照自上而下、从左到右的顺序在一行中打印所有叶子的索引。任何相邻数字之间必须正好有一个空格，行尾不能有多余的空格。

样本：
```
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
```
输出
```
4 1 5
```
>实现
```c++
#include <iostream>
#include <cstring>
#include <list>
using namespace std;
struct Node //定义节点
{
    int data;
    bool isNotRoot = false;
    int leftChild = -1;
    int rightChild = -1;
};
void bianli(int root, Node chain[])//实现节点层级遍历
{
    list<Node> Floor;
    Floor.push_back(chain[root]);
    int count = 1; //当前层级节点数
    list<int> dataList;//将叶节点的序号存在一个链表中
    while (!Floor.empty())
    {
        int countTemp = 0;
        for (int i = 0; i < count; i++)
        {
            /* 放入左右儿子 */
            if (Floor.front().leftChild != -1)
            {
                Floor.push_back(chain[Floor.front().leftChild]);
                countTemp++;
            }
            if (Floor.front().rightChild != -1)
            {
                Floor.push_back(chain[Floor.front().rightChild]);
                countTemp++;
            }
            if(Floor.front().rightChild == -1&&Floor.front().leftChild==-1){
                dataList.push_back(Floor.front().data);//这里可不可以直接输出呢？
                //答案是否，dataList的存在是为了单独控制叶节点输出时结尾没有空格
            }
            Floor.pop_front(); //弹出头，进入下一个
        }
        count=countTemp;//刷新计数
    }
    //在这里开始输出叶节点
    int datacount=dataList.size();
    for(int i=0; i < datacount; i++){
        cout<<dataList.front();
        dataList.pop_front();
        if(i!=datacount-1){
            cout<<" ";
        }
    }
}
int main()
{
    int count = 0, *p;
    cin >> count;
    Node *chain;
    chain = new Node[count];

    for (int i = 0; i < count; i++) //建立树
    {
        string temp;
        chain[i].data =i;
        cin >> temp;
        if (temp != "-")
        {
            chain[i].leftChild = atoi(temp.c_str());
            //这里使用了atoi函数对输入的字符进行强制转化，成为int；这个函数的具体用法还得再看
            chain[atoi(temp.c_str())].isNotRoot = true; //寻找树根
        }
        cin >> temp;
        if (temp != "-")
        {
            chain[i].rightChild = atoi(temp.c_str());
            chain[atoi(temp.c_str())].isNotRoot = true; //设定这个节点不是树根
        }
    }
    int root;
    /* 寻找树根 */
    for (int i = 0; i < count; i++)
    {
        if (chain[i].isNotRoot == false)
        {
            root = i;
            break;
        }
    }
    int pointer = 0; //定义所谓的指针；最后弃用
    //放弃的原因
    //因为这个不是先中后序，而是层级搜索，所以指针在这里意义不大
    //最终在函数中使用链表实现队列，进行层级搜索
    bianli(root,chain);
}
```
>总结：这个题思路还是很清晰的。很明显实现层级搜索就要用到队列。偷懒没有手撸链表实现队列结构，是使用的list库。也是一次AC，希望能再接再励。

### 08-树3 Tree Traversals Again
>题目
>可以使用堆栈以非递归方式实现中序二叉树遍历。例如，假设遍历一棵6节点的二叉树（键从1到6），栈操作为：push(1)；推（2）；推（3）；流行音乐（）; 流行音乐（）; 推（4）；流行音乐（）; 流行音乐（）; 推（5）；推（6）；流行音乐（）; 流行音乐（）。然后可以从这个操作序列生成一个唯一的二叉树（如图 1 所示）。你的任务是给出这棵树的后序遍历序列。

>解析
>>solution：如果对二叉树的遍历非递归实现有很好理解的话，那么这里理解起来就不是很大的难度，在输入格式中Push的过程就是二叉树前序遍历的结果，而Pop的过程及为二叉树的中序遍历的结果。如果理解了这两个操作，那么题目的意思就变成了已知二叉树的前序遍历和中序遍历求二叉树的后序遍历。由于前序遍历首先访问的是根节点，中序遍历首先访问的是左子树，而后序遍历最后才访问根节点。因此，前序遍历中第一个元素为后序遍历的最后一个元素，在中序遍历中根节点左边的为左子树的节点，右边为右子树的节点。所以需要递归的求解这个问题。

>代码
```c++
#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

// 给定前序遍历和中序遍历，求出二叉树的后序遍历
void getPostOrder(vector<int> preOrder, int preL, vector<int> inOrder, int inL,
                  vector<int> &postOrder, int postL, int n)
{
    if (n == 0) return ;
    if (n == 1) {
        postOrder[postL] = preOrder[preL];
        return ;
    }
    auto root = preOrder[preL];
    postOrder[postL + n - 1] = root;
    //在中序遍历数组上找出root的位置
    int i = 0;
    while (i < n) {
        if (inOrder[inL + i] == root) break;
        ++i;
    }
    // 计算出root节点左右子树节点的个数
    int L = i, R = n - i - 1;
    // 递归的进行求解
    getPostOrder(preOrder, preL + 1, inOrder, inL, postOrder, postL, L);
    getPostOrder(preOrder, preL + L + 1, inOrder, inL + L + 1, postOrder, postL + L, R);
}

vector<vector<int>> getOrder(int N)
{
    vector<int> preOrder(N, 0);
    vector<int> inOrder(N, 0);
    stack<int> st;
    int preL = 0, inL = 0;

    for (int i = 0; i < 2*N; ++i) {
        string str; int tmp;
        cin >> str;
        if (str == "Push") {
            cin >> tmp;
            preOrder[preL++] = tmp;
            st.push(tmp);
        } else if (str == "Pop") {
            inOrder[inL++] = st.top();
            st.pop();
        }
    }
    return {preOrder, inOrder};
}

int main()
{
    int N;
    cin >> N;
    auto res = getOrder(N);
    vector<int> postOrder(N, 0);
    getPostOrder(res[0], 0, res[1], 0, postOrder, 0, N);

    int i = 0;
    for (; i < N-1; ++i) {
        cout << postOrder[i] << " ";
    }
    cout << postOrder[i] << endl;
    return 0;
}
```
>我的实现：
>>原想法
>>如果有push则压入左边或右边，两个pop则当前节点是叶节点，没有儿子
>>这是个错误理解，原题目的意思是当末尾即出栈，访问上一个元素。这本质就像上面解析一样是研究先序和中序然后得到后序。代码放在下面简单纪念一下瞎写的成果。

```c++
#include <iostream>
#include <cstring>
/* 理解有误，不能AC */
/* 最后还是对了几个，就很奇怪 */
using namespace std;
struct Node
    {
        int data;
        int parent = -1;
        int leftChild = -1;
        int rightChild = -1;
    };
Node *chain;
int *finalData;
int dataCount=0;
void backward(int pos);
void printData(int count);
int main()
{
    int count = 0;
    cin >> count;
    chain=new Node[count];
    finalData=new int[count];
    
    string command;
    int item;
    int pos = -1, Position = -1; //表示当前实际节点位置，类似pointer；pos为数组所处位置
    int i = 0;
    cin >> command;
    if (command == "Push" && i == 0) //单独把第一次拉出来
    {
        cin >> item;
        pos++;
        Position++;
        chain[pos].data = item;
    }
    i++;
    while (i<count*2)//这一块全是创建树
    {
        if (chain[Position].leftChild>0 && chain[Position].rightChild>0&&chain[Position].parent!=-1)
        {
            Position = chain[Position].parent;
            continue;
        }
        cin>>command;
        if (command == "Push")
        {
            cin >> item;
            pos++; //指针指向下一个位置记录Node
            chain[pos].data = item;
            if (chain[Position].leftChild < 0)
            {
                chain[Position].leftChild = pos;
                chain[pos].parent = Position;
            }
            else if (chain[Position].rightChild < 0)
            {
                chain[Position].rightChild = pos;
                chain[pos].parent = Position;
            }
            Position = pos;
        }
        else if (command == "Pop")
        {
            if (chain[pos].leftChild == -1)
            {
                chain[pos].leftChild = -2;
            }
            else if (chain[pos].rightChild == -1)
            {
                chain[pos].rightChild = -2;
                Position = chain[pos].parent;
            }
        }
        i++;
    }
    //这一块是后序遍历树
    backward(0);
    printData(count);
}
void backward(int pos){
    if(chain[pos].leftChild>0||chain[pos].rightChild>0){
        if(chain[pos].leftChild>0) backward(chain[pos].leftChild);
        if(chain[pos].rightChild>0) backward(chain[pos].rightChild);
        finalData[dataCount] =chain[pos].data;
        dataCount++;
    }else{
        finalData[dataCount] =chain[pos].data;
        dataCount++;
    }
}
void printData(int count){
    for(int i=0;i<count;i++){
        cout<<finalData[i];
        if(i!=count-1){
            cout<<" ";
        }
    }
}
```

## 10-树4 是否同一棵二叉搜索树 
### 题目
>给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

>对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。

>输入：
```
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
```
>实现：
```c++
#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string data;
    Node *leftChild = NULL;
    Node *rightChild = NULL;
    Node *parent = NULL;
};
typedef Node *NodeP; //这里是将node的指针定义成NodeP，方便后续建立存放指针的数组
/* 不要太在意为什函数的位置是乱放的 */
void insertData(Node *p, Node *data);
/* 输入一个树 */
Node *inputTree(int count)
{
    Node *answer;
    answer = new Node;
    int data;
    Node *shit;
    shit = new Node; //定义一个新的节点
    cin >> data;     //这里单独将第一次拉出来，也就是说不考虑空树的情况
    answer->data = data;
    for (int i = 0; i < count - 1; i++)
    {
        cin >> data;
        shit->data = data;
        insertData(answer, shit);
        shit = new Node; //刷新节点，将shit指向一个新的节点地址
    }
    return answer;
}
/* 输出前序遍历结果，用string表示 */
string dataPre(Node *p)
{
    string data;
    data = p->data;
    if (p->leftChild != NULL)
    {
        data += dataPre(p->leftChild); //递归调用
    }
    if (p->rightChild != NULL)
    {
        data += dataPre(p->rightChild); //递归调用
    }
    return data;
}
/* 输出中序遍历结果，用string表示 */
string dataMid(Node *p)
{
    string data = "";

    if (p->leftChild != NULL)
    {
        data += dataPre(p->leftChild); //递归调用
    }
    data += p->data;
    if (p->rightChild != NULL)
    {
        data += dataPre(p->rightChild); //递归调用
    }
    return data;
}

int main()
{
    int count = 1;
    int chainCount;
    cin >> count;
    string message = ""; //新建消息队列
    while (count != 0)
    {
        cin >> chainCount;
        //NodeP p[10];
        NodeP *p;
        p = new NodeP[chainCount + 1]; //这里存储着这个所有的数，0储存的是原始树
        /* 对于每一组count和chainCount进行循环 */
        for (int i = 0; i < chainCount + 1; i++) //第一次输入的是原始树
        {
            p[i] = inputTree(count);
        }
        for (int i = 1; i < chainCount + 1; i++) //这个部分是判定树是否相同
        {
            /* 判定原理是前中后序中两种确定一个树 */
            /* 这里是用的前序遍历和中序遍历 */
            if (dataPre(p[0]) == dataPre(p[i]) && dataMid(p[i]) == dataMid(p[0]))
            {
                message += "Yes\n"; //将信息加入到消息队列
            }
            else
            {
                message += "No\n";
            }
        }
        cin >> count;
    }
    cout << message;
    //输入下一个count
}

/* 将节点插入树 */
void insertData(Node *p, Node *data)
{
    if (data->data > p->data)
    {
        if (p->rightChild != NULL)
        {
            insertData(p->rightChild, data);
        }
        else
        {
            p->rightChild = data;
        }
    }
    else if (data->data < p->data)
    {
        if (p->leftChild != NULL)
        {
            insertData(p->leftChild, data);
        }
        else
        {
            p->leftChild = data;
        }
    }
}
```
>感想:   
>   也是一次（差不多）AC，这个部分是考察如何建立一个树，以及如何判定两颗树相等。  
>希望再接再厉。

## 10-树5 Root of AVL Tree
>题目：  
给定一组序列，建立一个AVL（平衡树），返回该树的根
```
7
88 70 61 96 120 90 65
return 88
```
>解答：
```c++
#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *leftChild = NULL;
    Node *rightChild = NULL;
    int height = 1; //定义树高
};
int GetHeight(Node *p)//这里使用这个函数进行节点树高度的获取
{
    if (p != NULL)
        return p->height;
    else if (p == NULL)//这个部分非常关键，若对一个NULL指针取height是会SegmentationFault的
    {
        return 0;
    }
}
/* 旋转分为四种 */
//ll旋转
Node *leftRotation(Node *p)
{
    Node *root = p->leftChild;
    p->leftChild = root->rightChild;
    root->rightChild = p;
    //更新树高
    p->height = max(GetHeight(p->leftChild), GetHeight(p->rightChild)) + 1;//这里需要先更新子树高度
    root->height = max(GetHeight(root->leftChild), GetHeight(root->rightChild)) + 1;
    return root;
}
//rr旋转
Node *rightRotation(Node *p)
{
    Node *root = p->rightChild;
    p->rightChild = root->leftChild;
    root->leftChild = p;
    //更新树高
    p->height = max(GetHeight(p->leftChild), GetHeight(p->rightChild)) + 1;
    root->height = max(GetHeight(root->leftChild), GetHeight(root->rightChild)) + 1;
    return root;
}
//lr旋转
Node *lrRotation(Node *p)//像lr旋转这种问题一般十分的不好理解，所以说直接使用了暴力的方式进行挂载
{
    //这里课件提出是rr旋转和ll旋转的组合，暂且持保留意见
    Node *root = p->leftChild->rightChild;
    p->leftChild->rightChild = root->leftChild;
    root->leftChild = p->leftChild;
    p->leftChild = root->rightChild;
    root->rightChild = p;
    //更新树高
    root->leftChild->height = max(GetHeight(root->leftChild->leftChild), GetHeight(root->leftChild->rightChild)) + 1;
    root->rightChild->height = max(GetHeight(root->rightChild->leftChild), GetHeight(root->rightChild->rightChild)) + 1;
    root->height = max(GetHeight(root->leftChild), GetHeight(root->rightChild)) + 1;
    return root;
}
//rl旋转
Node *rlRotation(Node *p)
{
    //这里课件提出是rr旋转和ll旋转的组合，暂且持保留意见
    Node *root = p->rightChild->leftChild;
    p->rightChild->leftChild = root->rightChild;
    root->rightChild = p->rightChild;
    p->rightChild = root->leftChild;
    root->leftChild = p;
    //更新树高
    root->leftChild->height = max(GetHeight(root->leftChild->leftChild), GetHeight(root->leftChild->rightChild)) + 1;
    root->rightChild->height = max(GetHeight(root->rightChild->leftChild), GetHeight(root->rightChild->rightChild)) + 1;
    root->height = max(GetHeight(root->leftChild), GetHeight(root->rightChild)) + 1;
    return root;
}
Node *insertData(Node *p, Node *data) //返回当前节点插入后结果
{
    if (p == NULL)
    {
        return data;
    }
    //插入节点
    if (data->data > p->data) //右插入
    {
        p->rightChild = insertData(p->rightChild, data);
        //判定旋转
        if (GetHeight(p->rightChild) - GetHeight(p->leftChild) == 2)
        {
            //旋转
            if (data->data > p->rightChild->data)
            {
                //rr旋转
                p = rightRotation(p);
            }
            else
            {
                //rl旋转
                p = rlRotation(p);
            }
        }
    }
    else if (data->data < p->data) //左插入
    {
        p->leftChild = insertData(p->leftChild, data);
        if (GetHeight(p->rightChild) - GetHeight(p->leftChild) == -2)
        {
            //旋转
            if (data->data < p->leftChild->data)
            {
                //ll旋转
                p = leftRotation(p);
            }
            else
            {
                //lr旋转
                p = lrRotation(p);
            }
        }
    }
    //更新树高
    p->height = max(GetHeight(p->leftChild), GetHeight(p->rightChild)) + 1;
    return p;
}
int main()
{
    int data, count = 0;
    cin >> count;

    Node *p = NULL;
    for (int i = 0; i < count; i++)
    {
        cin >> data;
        Node *shit = new Node;
        shit->data = data;//不止没转，数据insert也有问题
        p = insertData(p, shit);
    }
    cout << p->data << endl;
}
```
>反思：
>>这个部分最初的想法是如果对一个叶节点进行插入操作的话就进行旋转。  
事实证明这个方法并不可行。例如给完全二叉树的叶节点插入，就不需要进行旋转。 
最后还是采用了原课件树高度的判定方式。  
用函数还原了四种旋转，但是在lr和rl旋转原课件好像有更深刻的思考方式。这个我暂时还没有理解。  
最后就是警告自己不要偷懒！远离人工智障！说的就是你（tabnine）  
正则表达式真的很好用！  
还是得多思考。

## 11-树6 Complete Binary Search Tree
>题目：  
>根据输入的数据建立一个完全二叉搜索树，并输出层序遍历的结果
>>细节：这个在数据结构的选择上选择了数组。  
因为层序遍历数组会更快，只需要顺序输出即可。  
而且在写入效率方面链表和数组没有太大区别，并且完全二叉树没有空间浪费  
所以说数组是更良好的选择。

>input
```
10
1 2 3 4 5 6 7 8 9 0
```
>output:
```
6 3 8 1 5 7 9 0 2 4
```
>代码：
```c++
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
int *res, *p;
int countG;
//int p[20], res[20];
void buildTree(int start, int endP, int position);
int main() //这个得细细考虑一下开始与结束的位置，以及对于元素位置的摆放
{
    int count;
    cin >> count;
    countG = count;
    p = new int[count];
    res = new int[count + 1];
    for (int i = 0; i < count; i++) //输入
    {
        cin >> p[i];
    }
    sort(p, p + count);                 //排序
    buildTree(0, count - 1, 1);         //建成树
    for (int i = 1; i < count + 1; i++) //输出队列
    {
        if (i != count)
        {
            cout << res[i] << " ";
        }
        else
        {
            cout << res[i];
        }
    }
}
void buildTree(int start, int endP, int position) //可以给这个函数指定一个放置位置，利用起position
{
    int count = endP - start + 1;
    int floor = 0, countTemp = 1;
    int startNext = start, endNext = endP;
    if (position > countG)
        return;                   //防止数据溢出，跳出栈
    while (countTemp - 1 < count) //计算当前层数
    {
        floor++;
        countTemp *= 2;
    }
    if (count == 1) //处理只有一个元素的情况
    {
        res[position] = p[start];
        return;
    }
    if (count <= (3 * pow(2, floor - 2) - 1))
    { //左树非满元素
        res[position] = p[endP - (int)pow(2, floor - 2) + 1];
        endNext = endP - (int)pow(2, floor - 2);
        startNext = endNext + 2;
    }
    else
    { //左树元素满
        res[position] = p[start + (int)pow(2, floor - 1) - 1];
        startNext = start + (int)pow(2, floor - 1);
        endNext = startNext - 2;
    }
    buildTree(start, endNext, position * 2); //向下一层建树
    buildTree(startNext, endP, position * 2 + 1);
}
```
>反思：  
>这次在一开始的思路并不明确，不过在看了课件开头便豁然开朗，也不知道是什么怪毛病。  
然后就是老问题，对整体的把控性太差。在编写程序的时候过于依赖通过迭代来修正问题，而不是站在一个全局的角度进行全方位思考然后在针对问题进行优化  
这样假如说参加竞赛的话会死吧（笑）
所以说下次要试着画一画，包括说是各个过程，整个流程图之类的东西。  
在写这种程序的时候除了核心也要思考细节。多去全面想！
