#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *leftChild = NULL;
    Node *rightChild = NULL;
    int height = 1; //定义树高
};
int GetHeight(Node *p)//这里使用这个函数进行节点树高度的获取
{
    if (p != NULL)
        return p->height;
    else if (p == NULL)//这个部分非常关键，若对一个NULL指针取height是会SegmentationFault的
    {
        return 0;
    }
}
/* 旋转分为四种 */
//ll旋转
Node *leftRotation(Node *p)
{
    Node *root = p->leftChild;
    p->leftChild = root->rightChild;
    root->rightChild = p;
    //更新树高
    p->height = max(GetHeight(p->leftChild), GetHeight(p->rightChild)) + 1;//这里需要先更新子树高度
    root->height = max(GetHeight(root->leftChild), GetHeight(root->rightChild)) + 1;
    return root;
}
//rr旋转
Node *rightRotation(Node *p)
{
    Node *root = p->rightChild;
    p->rightChild = root->leftChild;
    root->leftChild = p;
    //更新树高
    p->height = max(GetHeight(p->leftChild), GetHeight(p->rightChild)) + 1;
    root->height = max(GetHeight(root->leftChild), GetHeight(root->rightChild)) + 1;
    return root;
}
//lr旋转
Node *lrRotation(Node *p)//像lr旋转这种问题一般十分的不好理解，所以说直接使用了暴力的方式进行挂载
{
    //这里课件提出是rr旋转和ll旋转的组合，暂且持保留意见
    Node *root = p->leftChild->rightChild;
    p->leftChild->rightChild = root->leftChild;
    root->leftChild = p->leftChild;
    p->leftChild = root->rightChild;
    root->rightChild = p;
    //更新树高
    root->leftChild->height = max(GetHeight(root->leftChild->leftChild), GetHeight(root->leftChild->rightChild)) + 1;
    root->rightChild->height = max(GetHeight(root->rightChild->leftChild), GetHeight(root->rightChild->rightChild)) + 1;
    root->height = max(GetHeight(root->leftChild), GetHeight(root->rightChild)) + 1;
    return root;
}
//rl旋转
Node *rlRotation(Node *p)
{
    //这里课件提出是rr旋转和ll旋转的组合，暂且持保留意见
    Node *root = p->rightChild->leftChild;
    p->rightChild->leftChild = root->rightChild;
    root->rightChild = p->rightChild;
    p->rightChild = root->leftChild;
    root->leftChild = p;
    //更新树高
    root->leftChild->height = max(GetHeight(root->leftChild->leftChild), GetHeight(root->leftChild->rightChild)) + 1;
    root->rightChild->height = max(GetHeight(root->rightChild->leftChild), GetHeight(root->rightChild->rightChild)) + 1;
    root->height = max(GetHeight(root->leftChild), GetHeight(root->rightChild)) + 1;
    return root;
}
Node *insertData(Node *p, Node *data) //返回当前节点插入后结果
{
    if (p == NULL)
    {
        return data;
    }
    //插入节点
    if (data->data > p->data) //右插入
    {
        p->rightChild = insertData(p->rightChild, data);
        //判定旋转
        if (GetHeight(p->rightChild) - GetHeight(p->leftChild) == 2)
        {
            //旋转
            if (data->data > p->rightChild->data)
            {
                //rr旋转
                p = rightRotation(p);
            }
            else
            {
                //rl旋转
                p = rlRotation(p);
            }
        }
    }
    else if (data->data < p->data) //左插入
    {
        p->leftChild = insertData(p->leftChild, data);
        if (GetHeight(p->rightChild) - GetHeight(p->leftChild) == -2)
        {
            //旋转
            if (data->data < p->leftChild->data)
            {
                //ll旋转
                p = leftRotation(p);
            }
            else
            {
                //lr旋转
                p = lrRotation(p);
            }
        }
    }
    //更新树高
    p->height = max(GetHeight(p->leftChild), GetHeight(p->rightChild)) + 1;
    return p;
}
int main()
{
    int data, count = 0;
    cin >> count;

    Node *p = NULL;
    for (int i = 0; i < count; i++)
    {
        cin >> data;
        Node *shit = new Node;
        shit->data = data;//不止没转，数据insert也有问题
        p = insertData(p, shit);
    }
    cout << p->data << endl;
}