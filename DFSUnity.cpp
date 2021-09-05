#include <iostream>
#include <array>
using namespace std;
int n, k,counter;
void printNum(array<bool,31> table, int pos, int count, string res)
{
    table[pos] = true;
    if (count < k)
    {
        for (int i = 1; i <= n; i++)
        {
            if (table[i] == false)
            {
                printNum(table, i, count + 1, res + to_string(pos) + ",");
            }
        }
    }
    else
    {
        cout << res + to_string(pos)<<endl;
        counter++;
    }
}
int main()
{
    cin >> n >> k;
    array<bool,31> tb;
    string res="";
    for (int i = 0; i <= n; i++)
    {
        tb[i] = false;
    }
    for (int i = 1; i <= n; i++)
    {
        printNum(tb,i,1,res);
    }
    cout<<counter;
}