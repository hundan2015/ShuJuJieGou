#include <iostream>
#include <cstring>
#include <list>
using namespace std;
struct Node
{
    int data;
    bool isNotRoot = false;
    int leftChild = -1;
    int rightChild = -1;
};
void bianli(int root, Node chain[])
{
    list<Node> Floor;
    Floor.push_back(chain[root]);
    int count = 1; //当前层级节点数
    list<int> dataList;
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
                dataList.push_back(Floor.front().data);
            }
            Floor.pop_front(); //弹出头，进入下一个
        }
        count=countTemp;//刷新计数
    }
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
    int pointer = 0; //定义所谓的指针
    bianli(root,chain);
}