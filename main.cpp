#include "LLRBTree.h"
/* #include "LLRBNode.h" */
#include <iostream> 
using namespace std;

int main()
{
   LLRBTree<int,int> tree;
   tree.Insert(33, 54);
   tree.Insert(23, 45);
   tree.Insert(113, 45);
   tree.Insert(78, 45);
   tree.Insert(7, 45);

   tree.Insert(423, 425);
   tree.Insert(1413, 45);
   tree.Insert(478, 45);
   tree.Insert(74, 45);
   /* tree.Draw(); */

   tree.Insert(4323, 45);
   tree.Insert(1913, 41115);
   tree.Insert(4278, 45);
   tree.Insert(724, 45);

   tree.Insert(3323, 45);
   tree.Insert(9913, 45);
   tree.Insert(2278, 45);
   tree.Insert(2724, 45);

   /* cout << "test " << *tree.Search(1913); */

   tree.Draw();
}
