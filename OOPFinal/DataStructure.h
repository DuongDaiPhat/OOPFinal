#pragma once
#include "Trash.h"

typedef struct Node {
	Trash *trash;
	int throwPositionX;
	int throwPositionY;
	float time;
	float timeCal;
	float timeToMaxHeight;
	int stopPosition;
	bool isDisappeared;
	bool throwLeft;
	Node* next;
}Node;
typedef struct List {
	Node* pHead;
	Node* pTail;
}List;
void InitList(List& list);
void DeleteList(List& list);
Node* CreateNode(Trash *trash);
void AddNode(List& list, Trash *trash);
void DeleteNode(List& list, Trash *trash);

typedef struct _Stack {
	Node* pHead;
}_Stack;
class Stack {
private:
	_Stack stack;
public:
	Stack();
	virtual ~Stack();
	virtual void Push(Trash* trash);
	Trash* Pop();
	Node* ReturnHead()const;
	void DeleteNodeStack(Node* node);
	friend void InitStack(_Stack& stack);
	friend void DeleteStack(_Stack& stack);
	friend class Inventory;
};
typedef struct _Queue {
	Node* pHead;
	Node* pTail;
}_Queue;
class Queue {
protected:
	_Queue queue;
public:
	Queue();
	virtual ~Queue();
	virtual void EnQueue(Trash* trash);
	void SetTime(const float& time);
	void SetThrowingPosX(const int& x);
	void SetThrowingPosY(const int& y);
	void SetStopPosition(const int& stopPosition);
	void SetDisappeared();
	void SetAppeared();
	void SetThrowLeft(bool check);
	void SetTimeToMaxHeight(const float& Mtime);
	void SetTimeCal(const float& Ftime);
	float GetTime() const;
	int GetThrowingPosX() const;
	int GetThrowingPosY() const;
	int GetStopPosition() const;
	float GetTimeToMaxHeight() const;
	float GetTimeCal() const;
	bool IsDisappear(Node* node) const;
	bool IsThrowLeft() const;
	Trash* DeQueue();
	Node* ReturnHead()const;
	friend void InitQueue(_Queue& stack);
	friend void DeleteQueue(_Queue& stack);
};
