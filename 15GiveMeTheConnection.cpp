#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
vector<int> *p;
bool *table;
list<int> que;
void DFS(int position)//这个还是用的递归实现
{
    if (table[position] == false)
    {
        cout << position << " ";
        table[position] = true;
        int size = p[position].size();
        for (int i = 0; i < size; i++)
        {
            DFS(p[position][i]);
        }
    }
}
void BFS(int position)
{
    que.push_back(position);
    while (que.empty() == false)
    {
        int v = que.front();
        table[v] = true;
        cout << v << " ";
        que.pop_front();
        for (int i = 0; i < p[v].size(); i++)
        {
            if (!table[p[v][i]])
            {
                table[p[v][i]] = true; //重要！首先要标记这个已经被主节点访问过！
                //不然在较小子节点与较大子节点之间有边，较小子节点会访问较大子节点！
                que.push_back(p[v][i]);
            }
        }
    }
}
int main()
{
    int countNode, countSide;
    int data1, data2;
    cin >> countNode >> countSide;
    p = new vector<int>[countNode];
    table = new bool[countNode];
    for (int i = 0; i < countNode; i++)
    {
        table[i] = false;
    }

    for (int i = 0; i < countSide; i++)
    {
        cin >> data1 >> data2;
        p[data1].push_back(data2);
        p[data2].push_back(data1);
        sort(p[data1].begin(), p[data1].end());//为了顺序访问节点
        sort(p[data2].begin(), p[data2].end());
    }
    for (int i = 0; i < countNode; i++)
    {

        if (table[i] != false)
            continue;
        cout << "{ ";
        DFS(i);
        cout << "}" << endl;
    }
    for (int i = 0; i < countNode; i++)
    {
        table[i] = false;
    }
    for (int i = 0; i < countNode; i++)
    {

        if (table[i] != false)
            continue;
        cout << "{ ";
        BFS(i);
        cout << "}" << endl;
    }
}