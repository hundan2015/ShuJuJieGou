#include <iostream>
using namespace std;
void qSort(int start, int end);
void pickOne(int start, int end);
void printP(int count);
int count;
int p[20];
int main()
{
    //int *p;
    cin >> count;
    //p = new int[count];
    //input array
    for (int i = 0; i < count; i++)
    {
        cin >> p[i];
    }
    //sort
    qSort(0, count - 1);
    //output array
    printP(count);
}
void printP(int count)
{
    for (int i = 0; i < count; i++)
    {
        if (i != count - 1)
        {
            cout << p[i] << " ";
        }
        else
        {
            cout << p[i];
        }
    }
}
void qSort(int start, int end)
{
    /* if (start >= end)
        return;
    if (end - start == 1)
    {
        if (p[end] < p[start])
        {
            swap(p[end], p[start]);
        }
        return;
    } */
    pickOne(start, end);
    int mid = p[end];
    int tempj = end - 1;
    /* for (int i = start; i < tempj; i++)
    {
        if (p[i] > mid)
        {
            for (int j = tempj; j > i; j--)
            {
                if (p[j] < mid)
                {
                    swap(p[i], p[j]);
                    tempj = j;
                    break;
                }
                if (j == i + 1)
                    tempj = i;
            }
        }
    } */
    while(1){
        
    }
    swap(p[end], p[tempj]);
    qSort(start, tempj - 1);
    qSort(tempj + 1, end);
}

void pickOne(int start, int end)
{
    int mid = (start + end) / 2;
    int maxNum = max(p[end], max(p[start], p[mid]));
    int minNum = min(p[end], min(p[start], p[mid]));
    if (p[end] != maxNum && p[end] != minNum)
    {
    }
    else if (p[mid] != maxNum && p[mid] != minNum)
    {
        swap(p[end], p[mid]);
    }
    else if (p[start] != maxNum && p[start] != minNum)
    {
        swap(p[start], p[end]);
    }
}