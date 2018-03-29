#include <iostream>
#include <stdio.h>
#include "treeclass.hpp"

int main()
{
	printf("it is better to balance onece in the end of insert to economy time\n");
	treeclass * tree = new treeclass();
	tree->insert(0);
	tree->insert(1);
	tree->insert(2);
	tree->insert(3);
	tree->insert(4);
	
    if (tree->exists(2) == 1)
    	printf("2 exists in the tree\n");
    tree->remove(2);
	tree->printtree();
	tree->balancetree();
	tree->printtree();
    tree->~treeclass();

   
   return 0;
}