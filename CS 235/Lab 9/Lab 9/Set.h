#ifndef SET_H
#define SET_H
#include "SetInterface.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<typename T>
class Set : public SetInterface<T>

{
private:

	struct Node
	{
		T data;
		Node* left;
		Node* right;
		Node(T d) : data(d), left(nullptr), right(nullptr) {}
	};
	Node* root = nullptr;
	int nodeCount = 0;
	
public:
	Set<T>()
	{
		root = nullptr;
	}
	~Set<T>()
	{
		clear();
	}

	/** Inserts item into the set, if the container doesn't
		already contain an element with an equivalent value.
		@return: pair.first = pointer to item
				 pair.second = true if successfully inserted, else false. */
				 //Pair<T*, bool> insert(const T& item)
	bool insert(const T& item)
	{
		if (insertNode(root, item))
		{
			++nodeCount;
			return true;
		}
		return false;
	}


	/** Removes all items from the set. */
	void clear() {
		clearTree(root);
		nodeCount = 0;
	}

	/** @return: the number of elements contained by the Set. */
	size_t size() const { return nodeCount; }

	/** @return: return 1 if contains element equivalent to item, else 0. */
	size_t count(const T& item) 
	{
		if (findR(root, item))
		{
			return 1;
		}
		return 0;
	}

	/** @return: string representation of items in Set. */
	virtual std::string toString() const;

	friend std::ostream& operator<< (std::ostream& os, const Set& set) {  //use to output object as a stream using << 
		os << set.toString();
		return os;
	}

	bool inOrder(Node* node, ostringstream& out) const;

	bool addNode(const T& dataToAdd);

	bool insertNode(Node* &n, const T& dataToAdd);

	bool find(const T& target) const;

	bool findR(Node* localRoot, const T& target) const;

	bool clearTree(Node* &n);

};

#endif //SET_H
template<typename T>
inline bool Set<T>::inOrder(Node * node, ostringstream& out) const 
{
	if (node == nullptr) return false;
	inOrder(node->left, out);
	out << node->data << ", ";
	inOrder(node->right, out);
	return true;
}

template<typename T>
inline std::string Set<T>::toString() const
{
	ostringstream out;
	string setVal;
	inOrder(root, out);
	setVal = out.str();
	setVal.erase(setVal.size() - 2, 2);
	return setVal;
}


template<typename T>
bool Set<T>::addNode(const T& dataToAdd)
{
	if (root == nullptr)
	{
		Node * node = new Node(dataToAdd);
		//cout << endl << "ADDED " << dataToAdd << " at ROOT: " << root << endl;
		root = node;
		return true;
	}
	else if (insertNode(root, dataToAdd))
	{
		cout << dataToAdd << ": TRUE" << endl;
		return true;
	}
	else
	{
		cout << dataToAdd << ": FALSE" << endl;
		return false;
	}
}

template<typename T>
bool Set<T>::insertNode(Node* &n, const T& dataToAdd)
{
	if (n == nullptr)
	{
		Node* node = new Node(dataToAdd);
		//cout << endl << "ADDED " << dataToAdd << " at ROOT: " << root << endl;
		n = node;
		return true;
	}
	else if (dataToAdd == n->data)
	{
		return false;
	}
	else if (dataToAdd < n->data)
	{
		return insertNode(n->left, dataToAdd);
	}
	else if (dataToAdd > n->data)
	{
		return insertNode(n->right, dataToAdd);
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Set<T>::find(const T& target) const
{
	return findR(root, target);
}

template<typename T>
bool Set<T>::findR(Node* localRoot, const T& target) const
{
	if (localRoot == nullptr) return false;
	if (target < localRoot->data)
		return findR(localRoot->left, target);
	if (target > localRoot->data)
		return findR(localRoot->right, target);
	else
		return true;
}


template<typename T>
bool Set<T>::clearTree(Node* &n)
{
	if (n == nullptr)
	{
		return true;
	}
	clearTree(n->left);
	clearTree(n->right);

	Node * temp = n;
	n = nullptr;
	delete temp;
	return true;
}

//template<typename T>
//size_t Set<T>::size() const
//{
//	if (root == nullptr)
//	{
//		return 0;
//	}
//	else
//	{
//		return sizeN(root);
//	}
//}
//
///*recursive part of int size() function*/
//template<typename T>
//size_t Set<T>::sizeN(Node * &n)
//{
//	if (n == nullptr)
//	{
//		return 0;
//	}
//	else
//	{
//		return (sizeN(n->left) + 1 + sizeN(n->right));
//	}
//}

