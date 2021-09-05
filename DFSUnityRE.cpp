#include <iostream>
#include <array>
using namespace std;
int n, k,counter;
void printNum(array<bool,31> table, int pos, int count, string res)
//每个函数都有自己的table，如果用原生的数组就不能做到
//table是当前访问过的元素的表，pos表示当前元素数值，count是当前路径长度，res是最后输出的字符串
{
    table[pos] = true;//访问过了当前节点
    if (count < k)
    {
        for (int i = pos+1; i <= n; i++)//若i=0，就是Amn式的写法
        {
            if (table[i] == false)
            {
                printNum(table, i, count + 1, res + to_string(pos) + ",");
            }
        }
    }
    else
    {
        cout << res + to_string(pos)<<"],";
        counter++;
    }
}
int main()
{
    cin >> n >> k;
    array<bool,31> tb;//这是一个数据上限，题目规定n<=30
    string res="[";
    for (int i = 0; i <= n; i++)//初始化数组
    {
        tb[i] = false;
    }
    cout<<"[";
    for (int i = 1; i <= n; i++)
    {
        printNum(tb,i,1,res);
    }
    cout<<"]"<<counter;//最后有多少结果
}