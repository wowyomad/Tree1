#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <algorithm>
#include <stdlib.h>
#include <Windows.h>

#define STRING_BUFFER 1000
#define SPACE 5

struct Data
{
	int id;
	char* name;
};
struct Tree
{
	Data data;
	Tree* left = NULL;
	Tree* right = NULL;
};

//прямой(NLR)(PreOrder)
//обратный(LRN)(PostOrder)
//в порядке(LNR)(InOrder)

Tree* NewLeaf(const Data data);
void Insert(Tree** root, const Data key);
void DeleteNode(Tree** root, const int key);
void DeleteTree(Tree** root);

void SearchElement(Tree* root, const int key);

void GetTreeSize(Tree* root, int* count);
int GetTreeSize(Tree* root);

Tree* MinNode_key(Tree* root);
Tree* MaxNode(Tree* root);

void MakeRandomTree(Tree** root, const int amount);
void MakeBalancedTree(Tree* original, Tree** balancedTree);
void BalanceTree(Tree** root, Data* arr, int low, int high);
void TreeToArr(Tree* root, Data* arr);
void TreeToArr(Tree* root, Data** arr);

void PrintTree_Tree(Tree* root, int space);
void PrintTree_LNR(Tree* root);
void PrintTree_NLR(Tree* root);
void PrintTree_LRN(Tree* root);


void UI_Add(Tree** root);
void UI_View(Tree** root);
void UI_Search(Tree** root);
void UI_DeleteNode(Tree** root);
void UI_FillRandom(Tree** root);
void UI_DeleteTree(Tree** root);

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Tree* tree = NULL;
	Tree* balancedTree = NULL;
	bool done = false;
	while (!done)
	{
		std::cout
			<< "1. Добавить элемент \n"
			<< "2. Просмотреть дерево\n"
			<< "3. Найти элемент\n"
			<< "4. Удалить элемент\n"
			<< "5. Заполнить случайными числами\n"
			<< "6. Очистить дерево\n"
			<< "0. Выйти\n" << std::endl;
		char option;
		option = _getch();
		fflush(stdin);
		switch (option)
		{
		case '1':
			UI_Add(&tree);
			break;
		case '2':
			UI_View(&tree);
			break;
		case '3':
			UI_Search(&tree);
			break;
		case '4':
			UI_DeleteNode(&tree);
			break;
		case '5':
			UI_FillRandom(&tree);
			break;
		case '6':
			DeleteTree(&tree);
			break;
		case '0':
			done = true;
			break;
		default:
			std::cout << "Неверный ввод\n";
			break;
		}
	}
	_getch();
}

Tree* NewLeaf(const Data data)
{
	Tree* t = new Tree{ data };
	return t;
}

void Insert(Tree** root, const Data key)
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
		if (key.id == t->data.id)
		{
			std::cout << "Беда!\n";
			return;
		}
		if (key.id > t->data.id)
			t = t->right;
		else
			t = t->left;
	}
	t = NewLeaf(key);
	if (key.id > prev->data.id)
		prev->right = t;
	else
		prev->left = t;
}

void DeleteNode(Tree** root, const int key)
{
	if (*root == NULL)
	{
		return;
	}
	if (key < (*root)->data.id)
		DeleteNode(&(*root)->left, key);
	else if (key > (*root)->data.id)
		DeleteNode(&(*root)->right, key);
	else
	{
		Tree* temp = *root;
		if ((*root)->left == NULL)
		{
			(*root) = (*root)->right;
			delete temp;
			return;
		}
		else if ((*root)->right == NULL)
		{
			(*root) = (*root)->left;
			delete temp;
			return;
		}
		else
		{
			temp = MaxNode((*root)->left);
			(*root)->data = temp->data;
			DeleteNode(&(*root)->right, temp->data.id);
		}
	}
}
void DeleteTree(Tree** root)
{
	if (*root == NULL) return;
	DeleteTree(&(*root)->left);
	DeleteTree(&(*root)->right);
	delete[](*root)->data.name;
	delete* root;
	*root = NULL;
}
void SearchElement(Tree* root, const int key)
{
	while (root != NULL)
	{
		if (key > root->data.id)
			root = root->right;
		else if (key < root->data.id)
			root = root->left;
		else
			break;
	}
	if (root != NULL)
		std::cout << key << " нашёлся.\n"
		<< "Его имя " << root->data.name << '\n' << std::endl;
	else
		std::cout << key << " не нашёлся\n" << std::endl;
}

void GetTreeSize(Tree* root, int* count)
{
	if (root == NULL) return;
	GetTreeSize(root->left, count);
	(*count)++;
	GetTreeSize(root->right, count);
}

int GetTreeSize(Tree* root)
{
	int count = 0;
	GetTreeSize(root, &count);
	return count;
}

Tree* MinNode_key(Tree* root)
{
	if (root == NULL) return root;
	Tree* min = root;
	while (min->left != NULL)
		min = min->left;
	return min;
}

Tree* MaxNode(Tree* root)
{
	if (root == NULL) return root;
	Tree* max = root;
	while (max->right != NULL)
		max = max->right;
	return max;
}

void PrintTree_LNR(Tree* root)
{
	if (root == NULL) return;
	PrintTree_LNR(root->left);
	printf("%d\n", root->data.id);
	printf("%s\n\n", root->data.name);
	PrintTree_LNR(root->right);
}

void PrintTree_NLR(Tree* root)
{
	if (root == NULL) return;
	printf("%d\n", root->data.id);
	printf("%s\n\n", root->data.name);
	PrintTree_NLR(root->left);
	PrintTree_NLR(root->right);
}

void PrintTree_LRN(Tree* root)
{
	if (root == NULL) return;
	PrintTree_LRN(root->left);
	PrintTree_LRN(root->right);
	printf("%d\n", root->data.id);
	printf("%s\n\n", root->data.name);

}

void TreeToArr(Tree* root, Data** arr)
{
	if (root == NULL) return;
	TreeToArr(root->left, arr);
	*((*arr)++) = root->data;
	TreeToArr(root->right, arr);
}

void TreeToArr(Tree* root, Data* arr)
{
	if (root == NULL)
		return;
	Tree** stack = new Tree * [GetTreeSize(root)];
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
	delete[] stack;
}

void PrintTree_Tree(Tree* root, int space)
{
	if (root == NULL)
		return;
	space += SPACE;
	PrintTree_Tree(root->right, space);
	for (int i = SPACE; i < space; i++)
	{
		printf(" ");
	}
	printf("%d\n", root->data.id);
	PrintTree_Tree(root->left, space);
}

void MakeRandomTree(Tree** root, const int amount)
{
	int* arr = new int[amount];
	for (int i = 0; i < amount; i++)
	{
		arr[i] = i;
	}
	std::random_shuffle(arr, arr + amount);
	for (int i = 0; i < amount; i++)
	{
		Data temp;
		temp.id = arr[i];
		temp.name = new char{ '\0' };
		Insert(root, temp);
	}
	delete[] arr;
}


void MakeBalancedTree(Tree* original, Tree** balancedTree)
{
	int size = GetTreeSize(original);
	Data* arr = new Data[size];
	TreeToArr(original, arr);
	BalanceTree(balancedTree, arr, 0, size - 1);
	delete[] arr;
}

void BalanceTree(Tree** root, Data* arr, int low, int high)
{
	if (low > high) return;
	int mid = (low + high) / 2;
	*root = new Tree{ arr[mid] };
	BalanceTree(&(*root)->left, arr, low, mid - 1);
	BalanceTree(&(*root)->right, arr, mid + 1, high);

}


void UI_Add(Tree** root)
{
	Data input;
	char* temp = new char[STRING_BUFFER];
	std::cout << "id:\t";
	std::cin >> input.id;
	std::cout << "Имя\t";
	std::cin >> temp;
	if (!(std::cin))
	{
		std::cout << "\n\nНекорректный ввод!\n\n";
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		return;

	}
	int length = strlen(temp) + 1;
	input.name = new char[length];
	strcpy_s(input.name, length, temp);
	delete[] temp;
	Insert(root, input);
	std::cout << '\n';
}

void UI_View(Tree** root)
{
	bool done = false;
	while (!done)
	{
		std::cout
			<< "1. Прямой обход\n"
			<< "2. Обратный обход\n"
			<< "3. Обход по порядку\n"
			<< "4. Лежачее дерево\n"
			<< "0. Назад\n" << std::endl;
		char option;
		option = _getch();
		fflush(stdin);
		printf("\n");
		switch (option)
		{
		case '1':
			PrintTree_NLR(*root);
			break;
		case '2':
			PrintTree_LRN(*root);
			break;
		case '3':
			PrintTree_LNR(*root);
			break;
		case '4':
			PrintTree_Tree(*root, 0);
			break;
		case '0':
			done = true;
			break;
		default:
			printf("Неверный ввод\n");
			break;
		}
		printf("\n");
	}
}

void UI_Search(Tree** root)
{
	std::cout << "Введите id для поиска: ";
	int id;
	std::cin >> id;
	std::cout << std::endl;
	SearchElement(*root, id);
}

void UI_DeleteNode(Tree** root)
{
	std::cout << "Ввведите ключ, по которому будет\n"
		<< "удалён элемент\n";
	int id;
	std::cout << "id: ";
	while (!(std::cin >> id))
	{
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "Некорректный ввод\n"
			<< "id: ";
	}
	DeleteNode(root, id);

}

void UI_FillRandom(Tree** root)
{
	if (*root != NULL)
	{
		std::cout << "Очистите дерево, перед совершением операции\n";
		return;
	}
	else
	{
		int amount;
		std::cout << "Введите кол-во случайных чисел: ";
		std::cin >> amount;
		MakeRandomTree(root, amount);
	}
}

void UI_DeleteTree(Tree** root)
{
	char option;
	bool done = false;
	while (!done)
	{
		std::cout << "Вы уверены, что хотите УДАЛИТЬ?\n"
			<< "1. Да\n"
			<< "0. Нет\n" << std::endl;
		option = _getch();
		fflush(stdin);
		switch (option)
		{
		case '1':
			DeleteTree(root);
			done = true;
			break;
		case '0':
			done = true;
			break;
		default:
			std::cout << "Неверный ввод\n\n";
			break;
		}
	}
}
