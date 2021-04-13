#include <iostream>

class Node
{
public:
	int data;
	Node *next;
	Node *prev;
};


Node *head = nullptr;
Node *tail = nullptr;


// 머리에 새로운 노드 하나를 추가하는 함수.
void AddNodeAtFront()
{
	Node *n = new Node;//
	n->next = head;
	if (n->next != nullptr)
	{
		head->prev = n;
	}
	head = n;//

}


// 꼬리 노드를 제거하는 함수.
void DeleteTail()
{
	// 데이터가 없을 때.
	if ( head == nullptr ) return;

	// 데이터가 1개일 때.
	if ( head->next == nullptr )
	{
		delete head;
		head = nullptr;
	}

	// 데이터가 2개 이상일 때/
	else
	{
		Node *n = head;
		while ( n->next->next != nullptr )
		{
			n = n->next;
		}

		delete n->next;
		n->next = nullptr;
	}
}

// 머리 노드를 제거하는 함수
void DeleteHead()
{
	// 직접 구현해보자.
	
	// 데이터가 없을 때.
	if (head == nullptr) return;

	// 데이터가 1개일 때.
	if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
	}

	// 데이터가 2개 이상일 때/
	else
	{
		Node *n = head->next;
		delete head;
		head = n;
	}
}

// 꼬리에 새로운 노드 하나를 추가하는 함수.
void AddNodeAtTail(int x)
{

	
	Node *n = head;
	while (n->next != nullptr)
	{
		n = n->next;
	}
	Node *tail = new Node;
	n->next = tail;
	tail->next = nullptr;
	tail->data = x;


}


int main()
{
	// 머리에 데이터 추가하기 
	AddNodeAtFront();
	head->data = 0;

	// 머리에 데이터 추가하기 
	AddNodeAtFront();
	head->data = 4;

	// 머리에 데이터 추가하기 
	AddNodeAtFront();
	head->data = 5;

	// List에 있는 전체 데이터 출력하기.
	Node *n = head;
	while ( n != nullptr )
	{
		std::cout << n->data << " ";
		n = n->next;
	}
	std::cout << "머리에 데이터 추가";
	std::cout << std::endl;	// 출바꿈


	// 꼬리 데이터 제거하기
	DeleteTail();

	// List에 있는 전체 데이터 출력하기.
	n = head;
	while ( n != nullptr )
	{
		std::cout << n->data << " ";
		n = n->next;
	}
	std::cout << "꼬리 데이터 삭제";
	std::cout << std::endl;	// 출바꿈

	// 머리에 데이터 삭제하기
	DeleteHead();

	// List에 있는 전체 데이터 출력하기.
	n = head;
	while (n != nullptr)
	{
		std::cout << n->data << " ";
		n = n->next;
	}
	std::cout << "머리 데이터 삭제";
	std::cout << std::endl;	// 출바꿈

	//꼬리에 데이터 추가하기
	AddNodeAtTail(1);

	//꼬리에 데이터 추가하기
	AddNodeAtTail(10);

	//꼬리에 데이터 추가하기
	AddNodeAtTail(6);

	// List에 있는 전체 데이터 출력하기.
	n = head;
	while (n != nullptr)
	{
		std::cout << n->data << " ";
		n = n->next;
	}
	std::cout << "꼬리에 데이터 추가";
	std::cout << std::endl;	// 출바꿈



	/*
	//꼬리에서부터 머리에 노드 추가하기
	AddNodeFromTail(15);

	// List에 있는 전체 데이터 출력하기.
	n = head;
	while (n != nullptr)
	{
		std::cout << n->data << " ";
		n = n->next;
	}
	std::cout << "꼬리에 데이터 추가";
	std::cout << std::endl;	// 출바꿈
	*/
	return 0;
}