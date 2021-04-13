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


// �Ӹ��� ���ο� ��� �ϳ��� �߰��ϴ� �Լ�.
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


// ���� ��带 �����ϴ� �Լ�.
void DeleteTail()
{
	// �����Ͱ� ���� ��.
	if ( head == nullptr ) return;

	// �����Ͱ� 1���� ��.
	if ( head->next == nullptr )
	{
		delete head;
		head = nullptr;
	}

	// �����Ͱ� 2�� �̻��� ��/
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

// �Ӹ� ��带 �����ϴ� �Լ�
void DeleteHead()
{
	// ���� �����غ���.
	
	// �����Ͱ� ���� ��.
	if (head == nullptr) return;

	// �����Ͱ� 1���� ��.
	if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
	}

	// �����Ͱ� 2�� �̻��� ��/
	else
	{
		Node *n = head->next;
		delete head;
		head = n;
	}
}

// ������ ���ο� ��� �ϳ��� �߰��ϴ� �Լ�.
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
	// �Ӹ��� ������ �߰��ϱ� 
	AddNodeAtFront();
	head->data = 0;

	// �Ӹ��� ������ �߰��ϱ� 
	AddNodeAtFront();
	head->data = 4;

	// �Ӹ��� ������ �߰��ϱ� 
	AddNodeAtFront();
	head->data = 5;

	// List�� �ִ� ��ü ������ ����ϱ�.
	Node *n = head;
	while ( n != nullptr )
	{
		std::cout << n->data << " ";
		n = n->next;
	}
	std::cout << "�Ӹ��� ������ �߰�";
	std::cout << std::endl;	// ��ٲ�


	// ���� ������ �����ϱ�
	DeleteTail();

	// List�� �ִ� ��ü ������ ����ϱ�.
	n = head;
	while ( n != nullptr )
	{
		std::cout << n->data << " ";
		n = n->next;
	}
	std::cout << "���� ������ ����";
	std::cout << std::endl;	// ��ٲ�

	// �Ӹ��� ������ �����ϱ�
	DeleteHead();

	// List�� �ִ� ��ü ������ ����ϱ�.
	n = head;
	while (n != nullptr)
	{
		std::cout << n->data << " ";
		n = n->next;
	}
	std::cout << "�Ӹ� ������ ����";
	std::cout << std::endl;	// ��ٲ�

	//������ ������ �߰��ϱ�
	AddNodeAtTail(1);

	//������ ������ �߰��ϱ�
	AddNodeAtTail(10);

	//������ ������ �߰��ϱ�
	AddNodeAtTail(6);

	// List�� �ִ� ��ü ������ ����ϱ�.
	n = head;
	while (n != nullptr)
	{
		std::cout << n->data << " ";
		n = n->next;
	}
	std::cout << "������ ������ �߰�";
	std::cout << std::endl;	// ��ٲ�



	/*
	//������������ �Ӹ��� ��� �߰��ϱ�
	AddNodeFromTail(15);

	// List�� �ִ� ��ü ������ ����ϱ�.
	n = head;
	while (n != nullptr)
	{
		std::cout << n->data << " ";
		n = n->next;
	}
	std::cout << "������ ������ �߰�";
	std::cout << std::endl;	// ��ٲ�
	*/
	return 0;
}