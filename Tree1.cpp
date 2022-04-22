#include <iostream>

struct Tree
{
	int data;
	Tree* left;
	Tree* right;
};

void TreeConstruct(Tree* root,const int data);

int main()
{
	Tree* root = NULL;
	TreeConstruct(root, 0);
}

void TreeConstruct(Tree* root, const int data)
{
	root = new Tree{ data, NULL, NULL };
}