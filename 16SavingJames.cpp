#include <iostream>
#include <math.h>

using namespace std;
struct node
{
    bool final = false;
    bool visited = false;
    int x, y;
};
node *p;
int nodeCount;
double maxDistence;
bool finded = false;
double cacuDistance(node a, node b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
void DFS(int x) //这个还是用的递归实现
{
    if (p[x].visited == false)
    {
        p[x].visited = true;
        if (p[x].final)
        {
            finded = true;
            return;
        }
        for (int i = 1; i <= nodeCount; i++)
        {
            if (!p[i].visited && cacuDistance(p[x], p[i]) <= maxDistence)
            {
                DFS(i);
            }
        }
    }
}
int main()
{
    cin >> nodeCount >> maxDistence;
    p = new node[nodeCount+1];
    int data1, data2;
    p[0].x = 0;
    p[0].y = 0;
    if(maxDistence>=50){
        finded = true;
    }
    for (int i = 1; i <= nodeCount; i++)
    {
        cin >> data1 >> data2;
        p[i].x = data1;
        p[i].y = data2;
        if (abs(data1 - 50) <= maxDistence || abs(data2 - 50) <= maxDistence || abs(data1 + 50) <= maxDistence || abs(data2 + 50) <= maxDistence)
        {
            p[i].final = true;
        }
    }
    for (int i = 1; i <= nodeCount; i++)
    {
        if (!p[i].visited && cacuDistance(p[0], p[i]) <= maxDistence+15/2)
        {
            DFS(i);
        }
    }
    if (finded)
        cout << "Yes";
    else
        cout << "No";
}