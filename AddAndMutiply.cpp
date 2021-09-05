#include <iostream>
using namespace std;
struct Block
{
    int exp;
    int data;
    Block *next;
};
void input(Block *a);
Block *Add(Block *a, Block *b);
Block *Mutiply(Block *a, Block *b);
/* 目前有个问题就是没有办法处理当data==0的时候的链表节点浪费 */
/* 下一个可行思路，先生成s，在里边判断数值，若满足条件则attach，不满足则continue */
int main()
{
    Block *F1, *F2, *F3;
    F1 = new Block;
    F2 = new Block;
    input(F1);
    input(F2);
    F3 = Add(F1, F2);
}

void input(Block *a)
{
    int count = 0;
    cin >> count;
    Block *p, *s;
    p = a;
    for (int i = 0; i < count; i++)
    {
        int exp, data;
        cin >> exp >> data;
        p->exp = exp;
        p->data = data;
        if (i != count - 1)
        {
            s = new Block;
            p->next = s;
            p = s;
        }
        else
        {
            p->next = NULL;
        }
    }
    return;
}
/* 加法，应当输入两个结尾为NULL指针的链表 */
/* 下一个可行思路，先生成s，在里边判断数值，若满足条件则attach，不满足则continue */
Block *Add(Block *a, Block *b)
{
    Block *res, *p1, *p2, *s, *p;
    p1 = a;
    p2 = b;
    p = new Block;
    res = p;
    while (p1 || p2)
    {
        s = new Block;
        p->next = s;
        p = s;

        if (p1 && p2)
        {
            if (p1->exp == p2->exp)
            {
                p->exp = p1->exp;
                p->data = p1->data + p2->data;
                p1 = p1->next;
                p2 = p2->next;
            }
            else if (p1->exp > p2->exp)
            {
                p->exp = p1->exp;
                p->data = p1->data;
                p1 = p1->next;
            }
            else if (p1->exp < p2->exp)
            {
                p->exp = p2->exp;
                p->data = p2->data;
                p2 = p2->next;
            }
        }
        else if (p1)
        {
            p->exp = p1->exp;
            p->data = p1->data;
            p1 = p1->next;
        }
        else if (p2)
        {
            p->exp = p2->exp;
            p->data = p2->data;
            p2 = p2->next;
        }
    }
    p->next = NULL;
    return res->next;
}
/* 乘法
应当输入两个结尾为NULL指针的链表 */
Block *Mutiply(Block *a, Block *b)
{
    Block *res, *p1, *p2, *tempP, *temp, *s;
    res = new Block;
    res->next = NULL;
    res->data = 0;
    res->exp = 0;
    p1 = a;
    p2 = b;
    while (p2)
    {
        tempP = new Block;
        temp = tempP;
        while (p1)
        {
            s = new Block;
            tempP->next = s;
            tempP = s;
            tempP->exp = p1->exp + p2->exp;
            tempP->data = p1->data * p2->data;
            p1 = p1->next;
        }
        tempP->next = NULL;
        res = Add(res, temp->next);
        p2 = p2->next;
    }
    return res;
}