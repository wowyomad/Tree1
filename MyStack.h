#pragma once
struct Stack
{
	int _data;
	Stack* _next;

};


void Push(Stack** stack, const int val = 0);
void PushRandom(Stack** stack, int n);
void Pop(Stack** stack, int* dst = 0);

void Print(Stack** stack);
void Erase(Stack** stack);

void SortValues(Stack** stack);
void SortPointers(Stack** stack);