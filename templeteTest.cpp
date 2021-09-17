#include <iostream>
using namespace std;
template <class type>
class Stack
{
private:
    struct Node
    {
        type data;
        Node *next;
    };
    Node *ListData,top;
public:
    Stack(){
        ListData = NULL;
        p = ListData;
    }
    ~Stack();
    bool IsEmpty(){
        if(ListData==NULL){
            return true;
        }else{
            return false;
        }
    }
    void AppendNode(type shit){
        Node *newData = new Node;
        newData->data = shit;
        if(p==NULL){
            ListData = newData;
            p = ListData;
        }else{
            p->next = newData;
            p = p->next;
        }
    }
    type pop(){
        
    }
};

int main()
{
}