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