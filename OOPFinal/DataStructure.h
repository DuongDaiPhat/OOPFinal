#pragma once
#include "Trash.h"

typedef struct Node {
	Trash* trash;
	Node* next;
}Node;
typedef struct List {
	Node* pHead;
	Node* pTail;
}List;
void InitList(List& list);
void DeleteList(List& list);
Node* CreateNode(Trash* trash);
void AddNode(List& list, Trash* trash);
void DeleteNode(List& list, Trash* trash);

typedef struct _Stack {
	Node* pHead;
}_Stack;
class Stack {
private:
	_Stack stack;
public:
	Stack();
	~Stack();
	void Push(Trash* trash);
	Trash* Pop();
	friend void InitStack(_Stack& stack);
	friend void DeleteStack(_Stack& stack);
	friend class Inventory;
};
