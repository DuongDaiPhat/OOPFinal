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
void Stack::DeleteNodeStack(Node* node) {
	if (stack.pHead == nullptr) {
		return;
	}
	else if (stack.pHead == node) {
		Node* del = stack.pHead;
		stack.pHead = stack.pHead->next;
		delete del;
		del = nullptr;
		return;
	}
	else {
		Node* prev = stack.pHead;
		Node* del = stack.pHead->next;
		while (del != NULL) {
			if (del == node) {
				prev->next = del->next;
				delete del;
				del = nullptr;
				return;
			}
			prev = prev->next;
			del = del->next;
		}
	}
}
void Stack::SetTime(const float &time = 0) {
	if (time >= 0) {
		this->stack.pHead->time = time;
	}
}
void Stack::SetThrowingPosX(const int& x) {
	if (stack.pHead != nullptr) {
		this->stack.pHead->throwPositionX = x;
	}
}
void Stack::SetThrowingPosY(const int& y) {
	if (stack.pHead != nullptr) {
		this->stack.pHead->throwPositionY = y;
	}
}
void Stack::SetStopPosition(const int& stopPosition) {
	if (stack.pHead != nullptr) {
		this->stack.pHead->stopPosition = stopPosition;
	}
}
void Stack::SetDisappeared() {
	if (stack.pHead != nullptr) {
		this->stack.pHead->isDisappeared = true;
	}
}
void Stack::SetAppeared() {
	if (stack.pHead != nullptr) {
		this->stack.pHead->isDisappeared = false;
	}
}
void Stack::SetTimeToMaxHeight(const float& Mtime) {
	if (stack.pHead != nullptr) {
		this->stack.pHead->timeToMaxHeight = Mtime;
	}
}
float Stack::GetTime() const{
	if (stack.pHead != nullptr) {
		return this->stack.pHead->time;
	}
	return 0;
}
int Stack::GetThrowingPosX() const {
	if (stack.pHead != nullptr) {
		return this->stack.pHead->throwPositionX;
	}
	return 0;
}
int Stack::GetThrowingPosY()const {
	if (stack.pHead != nullptr) {
		return this->stack.pHead->throwPositionY;
	}
	return 0;
}
int Stack::GetStopPosition() const {
	if (stack.pHead != nullptr) {
		return this->stack.pHead->stopPosition;
	}
	return 0;
}
bool Stack::IsDisappear(Node* node) const {
	return node->isDisappeared;
}
void Stack::SetThrowLeft(bool check) {
	if (check == true) {
		this->stack.pHead->throwLeft = true;
	}
	else {
		this->stack.pHead->throwLeft = false;
	}
}
float Stack::GetTimeToMaxHeight()const {
	if (stack.pHead != nullptr) {
		return this->stack.pHead->timeToMaxHeight;
	}
	return 0;
}
bool Stack::IsThrowLeft()const {
	return this->stack.pHead->throwLeft;
}
Node* Stack::ReturnHead() const {
	Node* temp = this->stack.pHead;
	return temp;
}
Trash* Stack::GetTrashInStack(Node* node) {
	if (stack.pHead == nullptr) {
		cout << "Stack rong" << endl;
		return nullptr;
	}
	if (stack.pHead == node) {
		Node* del = stack.pHead;
		Trash* getTrash = stack.pHead->trash;
		stack.pHead = stack.pHead->next;
		delete del;
		del = nullptr;
		return getTrash;
	}
	else {
		Node* prev = stack.pHead;
		Node* del = stack.pHead->next;
		while (del != nullptr) {
			if (del == node) {
				Trash* getTrash = del->trash;
				prev->next = del->next;
				delete del;
				del = nullptr;
				return getTrash;
			}
			del = del->next;
		}
	}
}