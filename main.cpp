#include "LLRBTree.h"
/* #include "LLRBNode.h" */
#include <iostream> 
using namespace std;

int main()
{
    LLRBTree<int,int> tree;
   tree.Insert(44, 45);
    int * tmp = tree.Search(44);
    if (tmp)
    {
        /* cout << tree.Search(44); */
        cout << *tmp;
    }
    else
    {
        cout << "nope...";
    }
}
