#include <iostream>
#include <conio.h>
#include <algorithm>
#include <chrono>
struct Tree
{
	int data;
	Tree* left = NULL;
	Tree* right = NULL;
};

//прямой(NLR)(PreOrder)
//обратный(LRN)(PostOrder)
//в порядке(LNR)(InOrder)
#define SIZE 15
#define SPACE 5

Tree* NewLeaf(const int data);
void Insert(Tree** root, const int key);
Tree* DeleteNode(Tree* root, const int key);

int CountTreeElements(Tree* root, int* count);
int CountTreeElements(Tree* root);


void MakeBalancedTree(Tree* original, Tree** balancedTree);
void BalanceTree(Tree** root, int* arr, int low, int high);
void Tree_ToIntArr(Tree* root, int* arr);
void InOrder_ToIntArr(Tree* root, int** arr);

void PrintTree_Diagram(Tree* root, int space);
void PrintTree_LNR(Tree* root);

int main()
{
	using namespace std::literals::chrono_literals;

	setlocale(LC_ALL, "Russian");
	Tree* root = NULL;
	int nums[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		nums[i] = i;
	}
	std::random_shuffle(nums, nums + SIZE);
	std::cout << "nums:\t\t";
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", nums[i]);
		Insert(&root, nums[i]);
	}
	int count = CountTreeElements(root);
	printf("\n\n");
	int* arr = new int[SIZE];
	Tree* balancedTree = NULL;
	MakeBalancedTree(root, &balancedTree);
	printf("original\n\n");
	PrintTree_Diagram(root, 0);
	printf("balanced\n\n");
	PrintTree_Diagram(balancedTree, 0);



	_getch();
}

Tree* NewLeaf(const int data)
{
	Tree* t = new Tree{ data, NULL, NULL };
	return t;
}

void Insert(Tree** root, const int key)
{
	if (*root == NULL)
	{
		*root = NewLeaf(key);
		return;
	}
	Tree* prev = NULL;
	Tree* t = *root;
	while (t != NULL)
	{
		prev = t;
		if (key == t->data)
		{
			std::cout << "Беда!\n";
			return;
		}
		if (key > t->data)
			t = t->right;
		else
			t = t->left;
	}
	t = NewLeaf(key);
	if (key > prev->data)
		prev->right = t;
	else
		prev->left = t;
}

Tree* DeleteNode(Tree* root, const int key)
{

	Tree* Old_Prev = NULL, * Old = root;
	Tree* New_Prev = NULL, * New = NULL;

	while (Old != NULL && Old->data != key)
	{
		Old_Prev = Old;
		if (key > Old->data)
			Old = Old->right;
		else
			Old = Old->left;
	}

	if (Old == NULL)
	{
		std::cout << "Не нашёл\n";
		return root;
	}

	if (Old->right == NULL)
		New = Old->left;
	else if (Old->left == NULL)
		New = Old->right;
	else
	{
		New_Prev = Old;
		New = Old->left;
		while (New->right != NULL)
		{
			New_Prev = New;
			New = New->right;
		}
		if (New_Prev == Old) New->right = Old->right;
		else
		{
			New->right = Old->right;
			New_Prev->right = New->left;
			New->left = New_Prev;
		}
	}
	if (Old == root)
		root = New;
	else if (Old->data < Old_Prev->data)
		Old_Prev->left = New;
	else
		Old_Prev->right = New;

	delete Old;
	return root;
}
int CountTreeElements(Tree* root, int* count)
{
	if (root == NULL) return (*count);
	CountTreeElements(root->left, count);
	(*count)++;
	CountTreeElements(root->right, count);


}
int CountTreeElements(Tree* root)
{
	int count = 0;
	count = CountTreeElements(root, &count);
	return count;
}

void PrintTree_LNR(Tree* root)
{
	if (root == NULL) return;
	PrintTree_LNR(root->left);
	printf("%d ", root->data);
	PrintTree_LNR(root->right);

}
void InOrder_ToIntArr(Tree* root, int** arr)
{
	if (root == NULL) return;
	InOrder_ToIntArr(root->left, arr);
	*((*arr)++) = root->data;
	InOrder_ToIntArr(root->right, arr);
}

void Tree_ToIntArr(Tree* root, int* arr)
{
	if (root == NULL)
		return;
	Tree* stack[SIZE];
	int top = -1;
	int i = 0;
	bool done = false;
	while (!done)
	{
		if (root != NULL)
		{
			stack[++top] = root;
			root = root->left;
		}
		else
		{
			if (top > -1)
			{
				arr[i++] = stack[top]->data;
				root = stack[top--]->right;
			}
			else
				done = true;
		}
	}
}

void PrintTree_Diagram(Tree* root, int space)
{
	if (root == NULL)
		return;
	space += SPACE;
	PrintTree_Diagram(root->right, space);
	for (int i = SPACE; i < space; i++)
	{
		printf(" ");
	}
	printf("%d\n", root->data);
	PrintTree_Diagram(root->left, space);
}

void MakeBalancedTree(Tree* original, Tree** balancedTree)
{
	int size = CountTreeElements(original);
	int* arr = new int[size];
	Tree_ToIntArr(original, arr);
	BalanceTree(balancedTree, arr, 0, size - 1);
	delete[] arr;
}

void BalanceTree(Tree** root, int* arr, int low, int high)
{
	if (low > high) return;
	int mid = (low + high) / 2;
	*root = new Tree{ arr[mid] };
	BalanceTree(&(*root)->left, arr, low, mid - 1);
	BalanceTree(&(*root)->right, arr, mid + 1, high);

}
