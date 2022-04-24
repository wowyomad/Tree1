#include "MyStack.h"
#include <cstdio>
#include <iostream>


void Print(Stack** stack)
{
	Stack* cur = *stack;
	while (cur != NULL)
	{
		printf("%d%c", cur->_data, '\t');
		cur = cur->_next;
	}
	printf("%c", '\n');
}

void Erase(Stack** stack)
{
	Stack* temp;
	while (*stack != NULL)
	{
		temp = *stack;
		*stack = (*stack)->_next;
		delete temp;
	}
}

void Push(Stack** stack, const int val)
{
	Stack* cur = new Stack;
	cur->_data = val;
	cur->_next = *stack;
	*stack = cur;
}

void Pop(Stack** stack, int* dst)
{
	Stack* temp;
	if (stack != NULL)
	{
		temp = (*stack)->_next;
		if (dst != NULL)
		{
			*dst = (*stack)->_data;
		}
		delete* stack;
		*stack = temp;
	}
}

void SortValues(Stack** stack)
{
	if (*stack == NULL) return;
	if ((*stack)->_next == NULL) return;
	Stack* i = NULL;
	Stack* j;
	int temp;
	do
	{
		for (j = *stack; j->_next != i; j = j->_next)
		{
			if (j->_data > j->_next->_data)
			{
				temp = j->_data;
				j->_data = j->_next->_data;
				j->_next->_data = temp;
			}
		}
		i = j;
	} while ((*stack)->_next != i);
}

void SortPointers(Stack** stack)
{
	if (*stack == NULL) return;
	if ((*stack)->_next == NULL) return;

	Push(stack);

	Stack* i = NULL;
	Stack* j;
	Stack* temp;
	do
	{
		for (j = *stack; j->_next->_next != i; j = j->_next)
		{
			if (j->_next->_data > j->_next->_next->_data)
			{
				temp = j->_next->_next;
				j->_next->_next = temp->_next;
				temp->_next = j->_next;
				j->_next = temp;
			}
		}
		i = j->_next;
	} while ((*stack)->_next != i);
	Pop(stack);
}
