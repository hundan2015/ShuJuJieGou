#include <iostream>
#include <string>
using namespace std;
int position = 1;
//int p[20];
int *p;
void insert(int x)
{
    p[position] = x;
    int posTemp = position;
    while (p[posTemp / 2] > p[posTemp])
    {
        int Temp = p[posTemp / 2];
        p[posTemp / 2] = p[posTemp];
        p[posTemp] = Temp;
        posTemp /= 2;
    }
    position++;
}
string FindRoute(int pos)
{
    string res = "";
    while (pos != 1)
    {
        res += to_string(p[pos]) + " ";
        pos /= 2;
    }
    res += to_string(p[1]) + "\n";
    return res;
}
int main()
{
    int count, routeCount, data;
    cin >> count >> routeCount;
    p = new int[count + 1];
    p[0] = -99999;
    for (int i = 0; i < count; i++)
    {
        cin >> data;
        insert(data);
    }
    string res = "";
    for (int i = 0; i < routeCount; i++)
    {
        cin >> data;
        res += FindRoute(data);
    }
    cout << res;
}