#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "LinkedListInterface.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
class LinkedList : public LinkedListInterface <T>
{
private:

public:
	
	struct Node
	{
		//the data contained in the node
		T data;
		//pointer to next node
		Node* next;
		//creates a new node
		// @param data is the data stored
		Node(const T& d) : data(d), next(nullptr) {}
		// Creates a new Node that points to another Node
		// @param data the data stored
		// @param nextPtr pointer to next node
		//Node(const T& data, Node* nextPtr = nullptr) : data(data), next(nextPtr) {}
	};

	size_t listSize = 0;
	Node* head = nullptr;

	LinkedList() 
	{ 
		listSize = 0;
		head = nullptr;
	}
	virtual ~LinkedList() { clear(); }


	//Check if there is a duplicate node in linked list
	//@param value is the value to check against existing nodes
	//return bool true if duplicate found, return false if no duplicate is found
	bool checkDuplicate(T value)
	{
		Node* temp = nullptr;
		temp = head;
		while (temp->data != value)
		{
			if (temp->next == nullptr)
			{
				return false;
			}
			temp = temp->next;
		}
		return true;
	}

	/** Insert Node at beginning of linked list (no duplicates) */
	//@param value is value is the data to be instantiated with the new head
	virtual bool insertHead(T value) 
	{
		if (listSize == 0)
		{
			Node* newNode = new Node(value);
			newNode->next = nullptr;
			head = newNode;
			listSize++;
			return true;
		}
		if (listSize > 0)
		{
			if (checkDuplicate(value))
			{
				return false;
			}
			else
			{
				Node* newNode = new Node(value);
				newNode->next = head;
				head = newNode;
				listSize++;
				return true;
			}
		}
		return false; //fixme
	}

	/** Insert Node at end of linked list (no duplicates) */
	virtual bool insertTail(T value) 
	{
		if (listSize == 0) 
		{
			Node* newNode = new Node(value);
			head = newNode;
			head->next = nullptr;
			listSize++;
			return true;
		}
		if (listSize > 0)
		{
			if (checkDuplicate(value))
			{
				return false;
			}
			else
			{
				Node* temp = nullptr;
				temp = head;
				while (temp != nullptr)
				{
					if (temp->next == nullptr)
					{
						Node* newNode = new Node(value);
						temp->next = newNode;
						newNode->next = nullptr;
						listSize++;
						return true;
					}
					temp = temp->next;
				}
			}
		}
		return false;
	}

	/** Insert node after matchNode (no duplicates) */
	virtual bool insertAfter(T matchNode, T node) 
	{
		Node* temp = nullptr;
		temp = head;
		if (listSize == 0)
		{
			return false;
		}
		if (!(checkDuplicate(node)))
		{
			while (temp != nullptr)
			{
				if (temp->data == matchNode)
				{
					Node* newNode = new Node(node);
					newNode->next = temp->next;
					temp->next = newNode;
					listSize++;
					return true;
				}
				temp = temp->next;
			}
		}
		return false;/*fixme*/
	}

	/** Remove Node from linked list */
	virtual bool remove(T value) 
	{
		Node *curr;
		Node *prev;
		curr = head;
		prev = nullptr;
		if (listSize == 0)
		{
			return false;
		}

		if (checkDuplicate(value))
		{
			while (curr != nullptr)
			{
				if (curr->data == value)
				{
					if (head == curr)
					{
						head = head->next;
						//curr->next = NULL;
						delete curr;
						listSize--;
						return true;
					}
					else
					{
						prev->next = curr->next;
						curr->next = nullptr;
						delete curr;
						listSize--;
						return true;
					}
				}
				prev = curr;
				curr = curr->next;
			}
			if (listSize == 1)
			{
				head->next = nullptr;
				delete head;
				listSize--;
				return true;
			}
			if (listSize == 0)
			{
				head = nullptr;
				
			}
			return false;
		}
		return false;
	}

	/** Remove all Nodes from linked list */
	virtual bool clear() 
	{
		Node* temp = nullptr;
		Node* prev = nullptr;
		if (listSize == 0)
		{
			return true;
		}
		temp = head;
		while (temp->next != nullptr)
		{
			prev = temp;
			temp = temp->next;
			delete prev;
		}
		delete temp;
		head = nullptr;
		listSize = 0;
		return true;
	}

	/** Return Node at index (0 based) via value parameter
	NOTE: STL list does NOT support the at accessor. */
	virtual bool at(size_t index, std::string& value)
	{
		Node* curr = nullptr;
		curr = head;

		if (index >= (listSize) || index < 0)
		{
			throw out_of_range("Invalid Index");
			return false;
		}
		for (size_t i = 0; i < index; i++)
		{
			curr = curr->next;
		}
		ostringstream os;
		os << curr->data;
		value = os.str();
		return true;
	} 

	/** Returns the number of nodes in the linked list */
	virtual size_t size() const 
	{ 
		return listSize;
	}

	/** Return a level order traversal of a Linked List as a string */
	virtual std::string toString() const 
	{
		ostringstream os;
		Node* temp = nullptr;
		temp = head;
		if (listSize == 0)
		{
			return os.str();
		}
		os << temp->data;
		temp = temp->next;

		if (listSize == 1)
		{

			return os.str();
		}

		while (temp != nullptr)
		{
			os << " " << temp->data;
			temp = temp->next;
		}

		return os.str();
	}
	
	/* return the toString() method whenever (<<) is used*/
	friend ostream& operator<<(ostream& os, const LinkedList& LL)
	{
		os << LL.toString();
		return os;
	}
};
#endif //Linked List 

