#include <iostream>

using namespace std;

template <class ItemType>
class Node {
public:
	ItemType data;
	Node<ItemType> *link;

	Node() {
		this->link = NULL;
	}

	Node(ItemType data) {
		this->data = data;
		this->link = NULL;
	}
};

template<class List_ItemType>
class LinkedList {
	Node<List_ItemType>* head;
	int count;

protected:
	int InsertNode(Node<List_ItemType>* pPre,
		List_ItemType value);

	List_ItemType DeleteNode(Node<List_ItemType>* pPre,
		Node<List_ItemType>* pLoc);

	int Search(List_ItemType value,
		Node<List_ItemType>* &pPre,
		Node<List_ItemType>* &pLoc);

public:
	LinkedList();
	~LinkedList();

	int GetSize();
	void InsertFirst(List_ItemType value);
	void InsertLast(List_ItemType value);
	int InsertItem(List_ItemType value, int position);
	void DeleteFirst();
	void DeleteLast();
	int DeleteItem(int postion);
	int GetItem(int position, List_ItemType &dataOut);
	void Print2Console();
	void Clear();
	void Reverse();
	void Traverse();
	void Traverse2(List_ItemType *&);

	LinkedList<List_ItemType>* Clone();
};

template<class List_ItemType>
LinkedList<List_ItemType>::LinkedList() {
	this->head = NULL;
	this->count = 0;
}

template<class List_ItemType>
void LinkedList<List_ItemType>::Clear() {
	Node<List_ItemType> *temp;
	while (this->head != NULL) {
		temp = this->head;
		this->head = this->head->link;
		delete temp;
	}
	this->count = 0;
}

template<class List_ItemType>
LinkedList<List_ItemType>::~LinkedList() {
	this->Clear();
}

template<class List_ItemType>
int LinkedList<List_ItemType>::GetSize() {
	return this->count;
}

template<class List_ItemType>
int LinkedList<List_ItemType>::InsertNode(
	Node<List_ItemType> *pPre,
	List_ItemType value) {
	Node<List_ItemType> *pNew
		= new Node<List_ItemType>();
	if (pNew == NULL)
		return 0;
	pNew->data = value;
	if (pPre == NULL) {
		pNew->link = this->head;
		this->head = pNew;
	}
	else {
		pNew->link = pPre->link;
		pPre->link = pNew;
	}
	this->count++;
	return 1;
}

template<class List_ItemType>
List_ItemType LinkedList<List_ItemType>::
DeleteNode(Node<List_ItemType> *pPre,
	Node<List_ItemType> *pLoc) {
	List_ItemType result = pLoc->data;

	if (pPre == NULL) {
		this->head = pLoc->link;
	}
	else {
		pPre->link = pLoc->link;
	}

	this->count--;
	delete pLoc;
	return result;
}

template<class List_ItemType>
int LinkedList<List_ItemType>::Search(
	List_ItemType value,
	Node<List_ItemType>* &pPre,
	Node<List_ItemType>* &pLoc) {
	pPre = NULL;
	pLoc = this->head;
	while (pLoc != NULL && pLoc->data != value) {
		pPre = pLoc;
		pLoc = pLoc->link;
	}
	return (pLoc != NULL);
	// found: 1; notfound: 0
}

template<class List_ItemType>
void LinkedList<List_ItemType>::InsertFirst(
	List_ItemType value) {
	InsertItem(value, 0);
}

template<class List_ItemType>
void LinkedList<List_ItemType>::InsertLast(
	List_ItemType value) {
	InsertItem(value, this->count);
}

template<class List_ItemType>
int LinkedList<List_ItemType>::InsertItem(
	List_ItemType value, int position) {

	if (position < 0 || position > this->count)
		return 0;

	Node<List_ItemType> *pPre;

	if (position == 0)
		pPre = NULL;
	else {
		pPre = this->head;
		for (int i = 0; i < position - 1; i++)
			pPre = pPre->link;
	}

	return InsertNode(pPre, value);
}

template<class List_ItemType>
void LinkedList<List_ItemType>::DeleteFirst() {
	DeleteItem(0);
}

template<class List_ItemType>
void LinkedList<List_ItemType>::DeleteLast() {
	DeleteItem(this->count - 1);
}

template<class List_ItemType>
int LinkedList<List_ItemType>::DeleteItem(int position) {
	if (position < 0 || position >= this->count)
		return 0;

	Node<List_ItemType> *pPre, *pLoc;

	if (position == 0) {
		pPre = NULL;
		pLoc = this->head;
	}
	else {
		pPre = this->head;
		for (int i = 0; i < position - 1; i++)
			pPre = pPre->link;
		pLoc = pPre->link;
	}
	DeleteNode(pPre, pLoc);
	return 1;
}

template <class List_ItemType>
LinkedList<List_ItemType>*
LinkedList<List_ItemType>::Clone() {
	LinkedList<List_ItemType>* result =
		new LinkedList<List_ItemType>();

	Node<List_ItemType>* p = this->head;

	while (p != NULL) {
		result->InsertLast(p->data);
		p = p->link;
	}

	result->count = this->count;
	return result;
}

template <class List_ItemType>
int LinkedList<List_ItemType>::GetItem(int position, List_ItemType &dataOut) {
	if (position < 0 || position >= this->count)
		return 0;

	Node<List_ItemType>* p = this->head;
	for (int i = 0; i < position; i++) {
		p = p->link;
	}
	dataOut = p->data;
	return 1;
}

template <class List_ItemType>
void LinkedList<List_ItemType>::Reverse() {
	Node<List_ItemType>* prev = NULL;
	Node<List_ItemType>* current = this->head;
	Node<List_ItemType>* next;
	while (current != NULL) {
		next = current->link;
		current->link = prev;
		prev = current;
		current = next;
	}
	head = prev;
}

template<class List_ItemType>
void LinkedList<List_ItemType>::Print2Console() {
	Node<List_ItemType>* pLoc = this->head;
	for (int i = 0; i < this->count; i++) {
		cout << pLoc->data << " ";
		pLoc = pLoc->link;
	}
	cout << endl;
}

template<class List_ItemType>
void LinkedList<List_ItemType>::Traverse() {
	Node<List_ItemType> *p = head;
	while (p != NULL) {
		p->data++; // process data here!!!
		p = p->link;
	}
}

template<class List_ItemType>
void LinkedList<List_ItemType>::
Traverse2(List_ItemType *&visit) {
	Node<List_ItemType> *p = this->head;
	int i = 0;
	while (p != NULL && i < this->count) {
		visit[i] = p->data;
		p = p->link;
		i++;
	}
}

int main() {
	LinkedList<int>* myList =
		new LinkedList<int>();
	myList->InsertFirst(15);
	myList->InsertFirst(10);
	myList->InsertFirst(5);
	myList->InsertItem(18, 3);
	myList->InsertLast(25);
	myList->InsertItem(20, 3);
	myList->DeleteItem(2);
	myList->DeleteFirst();
	myList->InsertItem(83, 2);
	myList->DeleteLast();
	cout << "List 1:" << endl;
	myList->Print2Console();

	LinkedList<int>* myList2 = myList->Clone();
	myList2->Reverse();
	myList2->Traverse();
	cout << "List 2:" << endl;
	myList2->Print2Console();
	int value = 0;
	myList2->GetItem(1, value);
	cout << "Value at position 1: " << value << endl;

	int *arr = new int[myList2->GetSize()];
	myList2->Traverse2(arr);
	cout << "Copied array: ";
	for (int i = 0; i<4; i++) {
		cout << arr[i] << " ";
	}

	delete myList;
	delete myList2;
	return 1;
}