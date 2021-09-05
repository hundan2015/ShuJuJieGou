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