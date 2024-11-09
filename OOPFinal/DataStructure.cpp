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
				if (presentNode == list.pTail) {
					list.pTail = prevNode;
				}
				delete del;
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
Node* Stack::ReturnHead() const {
	Node* temp = this->stack.pHead;
	return temp;
}

void InitQueue(_Queue& queue) {
	queue.pHead = queue.pTail = nullptr;
}
void DeleteQueue(_Queue& queue) {
	while (queue.pHead != queue.pTail) {
		Node* del = queue.pHead;
		queue.pHead = queue.pHead->next;
		delete del;
		del = nullptr;
	}
	delete queue.pHead;
	queue.pHead = queue.pTail = nullptr;
}
Queue::Queue() {
	InitQueue(queue);
}
Queue::~Queue() {
	DeleteQueue(queue);
}
void Queue::EnQueue(Trash* trash) {
	Node* temp = CreateNode(trash);
	if (temp == nullptr) {
		cout << "Khong du bo nho" << endl;
		return;
	}
	if (queue.pHead == nullptr || queue.pTail == nullptr) {
		queue.pHead = queue.pTail = temp;
	}
	else {
		queue.pTail->next = temp;
		queue.pTail = temp;
	}
}
void Queue::SetTime(const float& time = 0) {
	if (time >= 0) {
		this->queue.pTail->time = time;
	}
}
void Queue::SetThrowingPosX(const int& x) {
	if (queue.pTail != nullptr) {
		this->queue.pTail->throwPositionX = x;
	}
}
void Queue::SetThrowingPosY(const int& y) {
	if (queue.pTail != nullptr) {
		this->queue.pTail->throwPositionY = y;
	}
}
void Queue::SetStopPosition(const int& stopPosition) {
	if (queue.pTail != nullptr) {
		this->queue.pTail->stopPosition = stopPosition;
	}
}
void Queue::SetDisappeared() {
	if (queue.pTail != nullptr) {
		this->queue.pTail->isDisappeared = true;
	}
}
void Queue::SetAppeared() {
	if (queue.pTail != nullptr) {
		this->queue.pTail->isDisappeared = false;
	}
}
void Queue::SetTimeToMaxHeight(const float& Mtime) {
	if (queue.pTail != nullptr) {
		this->queue.pTail->timeToMaxHeight = Mtime;
	}
}
float Queue::GetTime() const {
	if (queue.pTail != nullptr) {
		return this->queue.pTail->time;
	}
	return 0;
}
int Queue::GetThrowingPosX() const {
	if (queue.pTail != nullptr) {
		return this->queue.pTail->throwPositionX;
	}
	return 0;
}
int Queue::GetThrowingPosY()const {
	if (queue.pTail != nullptr) {
		return this->queue.pTail->throwPositionY;
	}
	return 0;
}
int Queue::GetStopPosition() const {
	if (queue.pTail != nullptr) {
		return this->queue.pTail->stopPosition;
	}
	return 0;
}
bool Queue::IsDisappear(Node* node) const {
	return node->isDisappeared;
}
void Queue::SetThrowLeft(bool check) {
	if (check == true) {
		this->queue.pTail->throwLeft = true;
	}
	else {
		this->queue.pTail->throwLeft = false;
	}
}
float Queue::GetTimeToMaxHeight()const {
	if (queue.pTail != nullptr) {
		return this->queue.pTail->timeToMaxHeight;
	}
	return 0;
}
bool Queue::IsThrowLeft()const {
	return this->queue.pTail->throwLeft;
}
Node* Queue::ReturnHead() const {
	Node* temp = this->queue.pHead;
	return temp;
}
Trash* Queue::DeQueue() {
	if (queue.pHead == nullptr) {
		return nullptr;
	}
	else {
		Node* tempNode = queue.pHead;
		Trash* tempTrash = tempNode->trash;
		queue.pHead = queue.pHead->next;
		if (queue.pTail->next == queue.pHead) {
			queue.pTail = queue.pHead;
		}
		delete tempNode;
		tempNode = nullptr;
		return tempTrash;
	}
}