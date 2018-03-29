#include "treeclass.hpp"

tree* treeclass::newelement (int element)//protected
{
    tree * head = (tree*)malloc(sizeof(tree));
    head->val = element;
    head->deep = 0;
    head->left = NULL;
    head->right = NULL;
    head->back = NULL;
    return head;
}

void treeclass::printtree(tree* node)//protected
{	
	if (node == NULL)
		return;
	if (node->left != NULL)
    	printtree(node->left);
		printf("%d(%d)   ", node->val, node->deep);
	if (node->right != NULL)
	   	printtree(node->right);
}

int treeclass::setdeep(tree * head)//protected
{
    if (head == NULL)
         return -1;
         
	int left = setdeep(head->left);
    int right = setdeep(head->right);
	if ( ((head->left)==NULL) && ((head->right)==NULL) )
    {
    	 head->deep = 0;
         return 0;
    }
    if (left > right)
        head->deep = left + 1;
    if (left <= right)
        head->deep = right + 1;

   return head->deep;
}

int treeclass::deep(tree * node)//protected
{
	if (node == NULL)
		return -1;
	return node->deep;	
}

void treeclass::addelement (tree* head, tree* element)
{	
	if (element == NULL)
		return;   
	if (head == NULL)
		return;   
	   
    if (head->val <= element->val)
    {
        if (head->right == NULL)
        {
            head->right = element;
            element->back = head;
            head = head->right;
            return;
        }
        if (head->right != NULL)
            addelement(head->right, element);
    }

    if (head->val > element->val)
    {
        if (head->left == NULL)
        {
            head->left = element;
            element->back = head;
            head = head->left;
            return;
        }
        else
            addelement(head->left, element);
    }
    setdeep(head);
}

tree * treeclass::searchbyval(tree* head, int x)//protected
{
	tree * res = NULL;
    if (head->val == x)
    {
        return head;
    }
    if ( (head->val > x) && (head->left != NULL) )
    {
       res = searchbyval(head->left, x);
    }
        
    if (head->val < x)
    {
    	if (head->right != NULL)
        	res = searchbyval(head->right, x);
    }

    return res;
}

int treeclass::deltree(tree * *phead)//protected
{
	if (*phead == NULL)
		return 0;
		
	int res = (*phead)->val;
	if ((*phead)->back != NULL)
	{
		tree * back = (*phead)->back;
		tree * left = (*phead)->left;
		tree * right = (*phead)->right;
		
	    if ((*phead)->back->right == (*phead))
		{
	        (*phead)->back->right = NULL;
	    }
	    if ((*phead)->back->left == (*phead))
	    {
	        (*phead)->back->left = NULL;
	    }
	    free(*phead);
	    
	    if (right != NULL)
	    {
	    	addelement (back, right); 
		}
	    if ((*phead)->left != NULL)
		{
			addelement (back, left);
	    }
	}
	printf("TUT\n");
	if ((*phead)->back == NULL)
	{
		if ((*phead)->left != NULL)
		{
			addelement ((*phead)->left, (*phead)->right);
			(*phead) = (*phead)->left;
			free((*phead)->back);
		}
		if ((*phead)->right != NULL)
		{
			addelement ((*phead)->right, (*phead)->left);
			(*phead) = (*phead)->right;
			free((*phead)->back);
		}
		free(*phead);
	}
    return res;
}

void treeclass::destroy(tree * head)//protected
{
	tree * right = (head)->right;
	tree * left = (head)->left;
	if (left)
		destroy(left);	
	if (right)
		destroy(right);
	free(head);
	return;
}

void treeclass::smallright(tree ** phead)//protected
{
	if (*phead == NULL)
		return;
	if ((*phead)->left == NULL)
		return;
		
	tree * a = *phead;
	tree * b = (*phead)->left;
	a->left = b->right;
	
	if(b->right != NULL)
	{
		b->right->back = a;
	}
	b->right = a;
	if (a->back != NULL)
	{
		if (a->val >= a->back->val)
		{
			a->back->right = b;
		}
		
		if (a->val < a->back->val)
		{
			a->back->left = b;
		}
	}	b->back = a->back;
	a->back = b;
	*phead = b;
	setdeep(*phead);
}

void treeclass::smallleft(tree ** phead)//protected
{
	if (*phead == NULL)
		return;
	if ((*phead)->right == NULL)
		return;
		
	tree * a = *phead;
	tree * b = (*phead)->right;
	a->right = b->left;
	
	if(b->left != NULL)
	{
		b->left->back = a;
	}
	b->left = a;
	if (a->back != NULL)
	{
		if (a->val >= a->back->val)
		{
			a->back->right = b;
		}
		
		if (a->val < a->back->val)
		{
			a->back->left = b;
		}
	}
	b->back = a->back;
	a->back = b;
	*phead = b;
	setdeep(*phead);
}

void treeclass::bigleft(tree ** phead)//protected
{
	if ((*phead)->right == NULL)
		return;
	if ((*phead)->right->left == NULL)
		return;	
	tree * a = *phead;
	tree * b = (*phead)->right;		
	tree * c = (*phead)->right->left;
	a->right = c->left;
	c->back = a->back;
	
	if (a->back != NULL)
	{
		if (a->val >= a->back->val)
		{
			a->back->right = b;
		}
		
		if (a->val < a->back->val)
		{
			a->back->left = b;
		}
	}	a->back = c;
	b->back = c;	
	b->left = c->right;
	c->right = b;
	c->left = a;
	if (a->right != NULL)
	{
		a->right->back = a;
	}
	if (b->left != NULL)
	{
		b->left->back = b;
	}
	*phead = c;
	setdeep(*phead);
}

void treeclass::bigright(tree ** phead)//protected
{
	if ((*phead)->left == NULL)
		return;
	if ((*phead)->left->right == NULL)
		return;	
	tree * a = *phead;
	tree * b = (*phead)->left;		
	tree * c = (*phead)->left->right;
	a->left = c->right;
	c->back = a->back;
	
	if (a->back != NULL)
	{
		if (a->val >= a->back->val)
		{
			a->back->right = b;
		}
		
		if (a->val < a->back->val)
		{
			a->back->left = b;
		}
	}	a->back = c;
	b->back = c;	
	b->right = c->left;
	c->left = b;
	c->right = a;
	if (a->left != NULL)
	{
		a->left->back = a;
	}
	if (b->right != NULL)
	{
		b->right->back = b;
	}
	*phead = c;
	setdeep(*phead);
}

int treeclass::bal(tree ** phead)//protected
{
	//printf("bal  ");
	if ((deep((*phead)->right) - deep((*phead)->left) >= 2) &&
	(deep((*phead)->right->left) <= deep((*phead)->right->right)))
	{
		printf("smallleft[%d]    ",((*phead)->val));
		setdeep(*phead);
		smallleft(phead);
		setdeep(*phead);
		return 1;
	}
	
	if ((deep((*phead)->left) - deep((*phead)->right) >= 2) &&
	(deep((*phead)->left->right) <= deep((*phead)->left->left)))
	{
		printf("smallright[%d]    ",((*phead)->val));
		setdeep(*phead);
		smallright(phead);
		setdeep(*phead);
		return 1;	
	}
	
	if ((deep((*phead)->right) - deep((*phead)->left) >= 2) &&
		(deep((*phead)->right->left) > deep((*phead)->right->right)))	
	{
		printf("bigleft[%d]    ",((*phead)->val));
		setdeep(*phead);
		bigleft(phead);
		setdeep(*phead);
		return 1;
	}
	
	if ((deep((*phead)->left) - deep((*phead)->right) >= 2) &&
	(deep((*phead)->left->right) > deep((*phead)->left->left)))
	{
		printf("bigright[%d]    ",((*phead)->val));
		setdeep(*phead);
		bigright(phead);
		setdeep(*phead);
		return 1;
	}
	setdeep(*phead);
	return 0;
}

int treeclass::balance(tree ** phead, int * res)//protected
{
	if ((*phead)->left != NULL)
        balance(&((*phead)->left), res);
	
	*res = bal(phead);
    
	if ((*phead)->right != NULL)
        balance(&((*phead)->right), res);
    return *res;
}

int treeclass::balanceall(tree * *phead)//protected
{
	int res = 0;
	while (balance(phead, &res) != balance(phead, &res))
		;
}


treeclass::treeclass()//public
{
    this->root = NULL;
};

void treeclass::insert(int val)//public
{
	tree * t = newelement (val);
	if (this->root != NULL)
		addelement (this->root, t);
		
	if (this->root == NULL)
		this->root = t;	
}

bool treeclass::exists(int val)//public
{
	tree * t = searchbyval(this->root, val);
	if (t != NULL)
		return true;
	if (t == NULL)
		return false;
}
	
void treeclass::remove(int val)//public
{
	tree * t = searchbyval(this->root, val);
	printf("t->val = %d\n", t->val);
	deltree(&t);
}	
	
void treeclass::printtree()//public	
{
	printtree(this->root);
}

void treeclass::balancetree()//public
{
	balanceall(&(this->root));
}

treeclass::~treeclass()//public
{
	destroy(this->root);
}
