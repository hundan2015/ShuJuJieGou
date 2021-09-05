#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string data;
    Node *leftChild = NULL;
    Node *rightChild = NULL;
    Node *parent = NULL;
};
typedef Node *NodeP; //这里是将node的指针定义成NodeP，方便后续建立存放指针的数组
/* 不要太在意为什函数的位置是乱放的 */
void insertData(Node *p, Node *data);
/* 输入一个树 */
Node *inputTree(int count)
{
    Node *answer;
    answer = new Node;
    int data;
    Node *shit;
    shit = new Node; //定义一个新的节点
    cin >> data;     //这里单独将第一次拉出来，也就是说不考虑空树的情况
    answer->data = data;
    for (int i = 0; i < count - 1; i++)
    {
        cin >> data;
        shit->data = data;
        insertData(answer, shit);
        shit = new Node; //刷新节点，将shit指向一个新的节点地址
    }
    return answer;
}
/* 输出前序遍历结果，用string表示 */
string dataPre(Node *p)
{
    string data;
    data = p->data;
    if (p->leftChild != NULL)
    {
        data += dataPre(p->leftChild); //递归调用
    }
    if (p->rightChild != NULL)
    {
        data += dataPre(p->rightChild); //递归调用
    }
    return data;
}
/* 输出中序遍历结果，用string表示 */
string dataMid(Node *p)
{
    string data = "";

    if (p->leftChild != NULL)
    {
        data += dataPre(p->leftChild); //递归调用
    }
    data += p->data;
    if (p->rightChild != NULL)
    {
        data += dataPre(p->rightChild); //递归调用
    }
    return data;
}

int main()
{
    int count = 1;
    int chainCount;
    cin >> count;
    string message = ""; //新建消息队列
    while (count != 0)
    {
        cin >> chainCount;
        //NodeP p[10];
        NodeP *p;
        p = new NodeP[chainCount + 1]; //这里存储着这个所有的数，0储存的是原始树
        /* 对于每一组count和chainCount进行循环 */
        for (int i = 0; i < chainCount + 1; i++) //第一次输入的是原始树
        {
            p[i] = inputTree(count);
        }
        for (int i = 1; i < chainCount + 1; i++) //这个部分是判定树是否相同
        {
            /* 判定原理是前中后序中两种确定一个树 */
            /* 这里是用的前序遍历和中序遍历 */
            if (dataPre(p[0]) == dataPre(p[i]) && dataMid(p[i]) == dataMid(p[0]))
            {
                message += "Yes\n"; //将信息加入到消息队列
            }
            else
            {
                message += "No\n";
            }
        }
        cin >> count;
    }
    cout << message;
    //输入下一个count
}

/* 将节点插入树 */
void insertData(Node *p, Node *data)
{
    if (data->data > p->data)
    {
        if (p->rightChild != NULL)
        {
            insertData(p->rightChild, data);
        }
        else
        {
            p->rightChild = data;
        }
    }
    else if (data->data < p->data)
    {
        if (p->leftChild != NULL)
        {
            insertData(p->leftChild, data);
        }
        else
        {
            p->leftChild = data;
        }
    }
}