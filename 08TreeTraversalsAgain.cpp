#include <iostream>
#include <cstring>
/* 理解有误，不能AC */
using namespace std;
struct Node
    {
        int data;
        int parent = -1;
        int leftChild = -1;
        int rightChild = -1;
    };
Node *chain;
int *finalData;
int dataCount=0;
void backward(int pos);
void printData(int count);
int main()
{
    int count = 0;
    cin >> count;
    chain=new Node[count];
    finalData=new int[count];
    
    string command;
    int item;
    int pos = -1, Position = -1; //表示当前实际节点位置，类似pointer；pos为数组所处位置
    int i = 0;
    cin >> command;
    if (command == "Push" && i == 0) //单独把第一次拉出来
    {
        cin >> item;
        pos++;
        Position++;
        chain[pos].data = item;
    }
    i++;
    while (i<count*2)//这一块全是创建树
    {
        if (chain[Position].leftChild>0 && chain[Position].rightChild>0&&chain[Position].parent!=-1)
        {
            Position = chain[Position].parent;
            continue;
        }
        cin>>command;
        if (command == "Push")
        {
            cin >> item;
            pos++; //指针指向下一个位置记录Node
            chain[pos].data = item;
            if (chain[Position].leftChild < 0)
            {
                chain[Position].leftChild = pos;
                chain[pos].parent = Position;
            }
            else if (chain[Position].rightChild < 0)
            {
                chain[Position].rightChild = pos;
                chain[pos].parent = Position;
            }
            Position = pos;
        }
        else if (command == "Pop")
        {
            if (chain[pos].leftChild == -1)
            {
                chain[pos].leftChild = -2;
            }
            else if (chain[pos].rightChild == -1)
            {
                chain[pos].rightChild = -2;
                Position = chain[pos].parent;
            }
        }
        i++;
    }
    //这一块是后序遍历树
    backward(0);
    printData(count);
}
void backward(int pos){
    if(chain[pos].leftChild>0||chain[pos].rightChild>0){
        if(chain[pos].leftChild>0) backward(chain[pos].leftChild);
        if(chain[pos].rightChild>0) backward(chain[pos].rightChild);
        finalData[dataCount] =chain[pos].data;
        dataCount++;
    }else{
        finalData[dataCount] =chain[pos].data;
        dataCount++;
    }
}
void printData(int count){
    for(int i=0;i<count;i++){
        cout<<finalData[i];
        if(i!=count-1){
            cout<<" ";
        }
    }
}