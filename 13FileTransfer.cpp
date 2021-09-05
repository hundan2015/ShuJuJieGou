/* #include <iostream>
using namespace std;
/* 这道题题意理解有误，最后是因为超时没有办法AC，有的时候是答案错误 */
/* 总之直接用数组会好太多。 */
/* struct Node
{
    int parent = -1;
    int count = 1;
};
Node *p;
//Node p[20];
int findParent(int x)
{
    while (p[x].parent != -1)
    {
        x = p[x].parent;
    }
    return x;
}
void Connect(int data1, int data2)
{
    if (findParent(data1) != findParent(data2))
    {
        p[findParent(data2)].parent = findParent(data1);
    }
}
int main()
{
    int count;
    cin >> count;
    int data1, data2;
    p = new Node[count+1];
    string command;
    cin>>command;
    int ans=0;
    while (command != "S")
    {
        cin >> data1 >> data2;
        if (command == "C")
        {
            if (findParent(data1)==findParent(data2)){
                cout<<"yes";       
            }else{
                cout<<"no";
            }
        }
        else if (command == "I")
        {
            Connect(data1, data2);
        }
        cin >> command;
    }
    for(int i=0;i<count;i++){
        if(p[i].parent==-1) ans++;
    }
    if(ans==1){
        cout<<"The network is connected.";
    }else{
        cout<<"There are "<<ans<<" components.";
    }
    
}  */
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>
#include <string.h>
using namespace std;
#define N 10010

int Fa[N];

void Init()
{
    for (int i = 0; i < N; i++)
        Fa[i] = i; //将所有节点的父亲设为节点本身
}
int Find(int x)
{
    int r = x;
    while (r != Fa[r])
        r = Fa[r];
    int i = x, j;
    while (i != r) //把路径上所有节点的父亲设置成根节点
    {
        j = Fa[i];
        Fa[i] = r;
        i = j;
    }
    return r;
}
int main()
{

    Init();
    int n, a, b, fa, fb;
    char c;
    scanf("%d", &n);
    while (scanf("%c", &c))
    {
        if (c == 'C')
        {
            scanf("%d%d", &a, &b);
            fa = Find(a);
            fb = Find(b);
            if (fa != fb)
                printf("no\n");
            else
                printf("yes\n");
        }
        if (c == 'I')
        {
            scanf("%d%d", &a, &b);
            fa = Find(a);
            fb = Find(b);
            if (fa != fb)
                Fa[fb] = fa;
        }
        if (c == 'S')
        {
            int ans = 0;
            for (int i = 1; i <= n; i++)
            {
                if (Fa[i] == i)
                    ans++;
            }

            if (ans == 1)
                printf("The network is connected."); //只有一个子网络
            else
                printf("There are %d components.", ans); //这个题想问你这个有几个子网络
            return 0;
        }
    }
    return 0;
}
