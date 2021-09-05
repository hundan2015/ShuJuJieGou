#include <iostream>
using namespace std;
int add(int a[], int start, int end)
{
    int res = 0;
    for (int i = start; i <= end; i++)
    {
        res += a[i];
    }
    return res;
}
int main()
{
    int count, *p;
    cin >> count;
    p = new int[count];
    bool yep = false;
    for (int i = 0; i < count; i++)
    {
        cin >> p[i];
        if (p[i] >= 0)
        {
            yep = true;
        }
    }
    int max = 0, start = 0, end = 0;
    for (int i = 0; i < count; i++)
    {
        for (int j = i; j < count; j++)
        {
            int temp = add(p, i, j);
            if (temp > max)
            {
                max = temp;

                start = p[i];
                end = p[j];
            }
        }
    }
    if (max == 0 && yep == false)
    {
        start = p[0];
        end = p[count - 1];
    }
    cout << max << " " << start << " " << end;
}