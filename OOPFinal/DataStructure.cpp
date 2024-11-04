#include "DataStructure.h"
void InitList(List& list) {
	list.pHead = list.pTail = nullptr;
}
void DeleteList(List& list) {
	while (list.pHead != nullptr) {
		Node* del = list.pHead;
		list.pHead = list.pHead->next;
		delete del;
		del = nullptr;
	}
}
Node* CreateNode(Trash* trash) {
	Node* temp = new Node;
	if (temp == nullptr) {
		cout << "Khong du bo nho" << endl;
		return nullptr;
	}
	temp->trash = trash;
	temp->next = nullptr;
	return temp;
}
void AddNode(List& list, Trash* trash) {
	Node* temp = CreateNode(trash);
	if (list.pHead == nullptr || list.pTail == nullptr) {
		list.pHead = temp;
		list.pTail = temp;
	}
	else {
		list.pTail->next = temp;
		list.pTail = temp;
	}
}
void DeleteNode(List& list, Trash* trash) {
	if (list.pHead == nullptr) return;

	if (list.pHead->trash == trash) {
		Node* del = list.pHead;
		list.pHead = list.pHead->next;
		delete del;
		if (list.pHead == nullptr)
			list.pTail = nullptr;
		return;
	}
	else {
		Node* prevNode = list.pHead;
		Node* presentNode = list.pHead->next;
		while (presentNode != nullptr) {
			if (presentNode->trash == trash) {
				Node* del = presentNode;
				prevNode->next = presentNode->next;
				delete del;
				del = nullptr;
				break;
			}
			prevNode = presentNode;
			presentNode = presentNode->next;
		}
	}
}

void InitStack(_Stack& stack) {
	stack.pHead = nullptr;
}
void DeleteStack(_Stack& stack) {
	Node* temp = stack.pHead;
	while (temp != nullptr) {
		Node* del = temp;
		temp = temp->next;
		delete del;
		del = nullptr;
	}
}
Stack::Stack() {
	InitStack(stack);
}
Stack::~Stack() {
	DeleteStack(stack);
}
void Stack::Push(Trash* trash) {
	Node* temp = CreateNode(trash);
	if (temp == nullptr) {
		cout << "Khong du bo nho cho stack" << endl;
		return;
	}
	temp->next = stack.pHead;
	stack.pHead = temp;
}
Trash* Stack::Pop() {
	if (stack.pHead == nullptr) {
		return nullptr;
	}
	else {
		Node* temp = stack.pHead;
		stack.pHead = stack.pHead->next;
		Trash* trash = temp->trash;
		delete temp;
		temp = nullptr;
		return trash;
	}
}