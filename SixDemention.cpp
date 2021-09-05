#include <iostream>
#include <array>
#include <list>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
vector<int> *p;
list<int> que;
double counter = 0;
array<bool, 1001> table;//这个地方有坑，在最大nodeCount的时候访问最后一位是table[1000]，而只有table[999]造成溢出
void refreshTable(int count)
{
    for (int i = 0; i <= count; i++)
    {
        table[i] = false;
    }
}
// 看了看网上的解释，用dfs在限定遍历深度的情况下有时候可能会打断本来存在的连接，从而使有的节点访问不到，比如说，在一个2度空间问题中，有两个路径
// 1->2->3
// 1->3->4
// 按照dfs先走第一条路径，2，3都被访问了，走第二条路径的时候，因为3已经被访问了，所以就没法跳到4了
// 所以还是用bfs吧

/* void DFS(int position, int count) //这个还是用的递归实现
{
    if (table[position] == false && count <= 6)
    {
        count++;
        table[position] = true;
        counter++;
        int size = p[position].size();
        for (int i = 0; i < size; i++)
        {
            DFS(p[position][i], count);
        }
    }
} */
void BFS(int position)
{
    table[position] = true;
    int last = position;
    que.push_back(position);
    int level = 0;
    while (que.empty() == false)
    {
        int v = que.front();
        que.pop_front();
        counter++;
        for (int i = 0; i < p[v].size(); i++)
        {
            if (!table[p[v][i]])
            {
                table[p[v][i]] = true; 
                que.push_back(p[v][i]);
            }
        }
        if(v==last){
            last = que.back();
            level++;
        }
        if(level==7){
            break;
        }
    }
}
int main()
{
    int nodeCount, sideCount;
    cin >> nodeCount >> sideCount;
    p = new vector<int>[nodeCount + 1];
    refreshTable(nodeCount);
    for (int i = 1; i <= sideCount; i++)
    {
        int data1, data2;
        cin >> data1 >> data2;
        p[data1].push_back(data2);
        p[data2].push_back(data1);
    }
    for (int i = 1; i <= nodeCount; i++)
    {
        BFS(i);
        double percentage = (counter / nodeCount) * 100;
        cout << i << ": " << setiosflags(ios::fixed) << setprecision(2) << percentage << "%" << endl;
        counter = 0;
        que.clear();
        refreshTable(nodeCount);
    }
}