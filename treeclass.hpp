#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#ifndef treeclass_H
//#define treeclass_H
  
typedef struct Tree
{
    struct Tree * left;
    struct Tree * right;
    struct Tree * back;
    int deep;
    int val;
} tree;

class treeclass
{
public:
    treeclass();
    void insert(int value);
    bool exists(int value);
    void remove(int value);
	void printtree();
	void balancetree();
    ~treeclass();



protected:
    tree* newelement (int element);
	void printtree(tree* node);
	int setdeep(tree * head);
	int deep(tree * node);
	void addelement (tree* head, tree* element);
	tree * searchbyval(tree* head, int x);
	int deltree(tree ** phead);
	void destroy(tree * head);
	
	void smallright(tree ** phead);
	void smallleft(tree ** phead);
	void bigleft(tree ** phead);
	void bigright(tree ** phead);
	int bal(tree ** phead);
	int balance(tree ** phead, int * res);
	int balanceall(tree ** phead);
	
	tree * root;
};
