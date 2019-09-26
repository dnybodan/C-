#ifndef BST_H
#define BST_h
#include "BSTInterface.h"
#include <sstream>
#include <iostream>

using namespace std;

template<typename T>
class BST : public BSTInterface<T>
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

public:
	BST() { root = nullptr; }
	~BST() 
	{
		clearTree();
	}
	/** Return a level order traversal of a BST as a string */
	string toString() const
	{
		int level = -1;
		ostringstream os;
		if (root == nullptr)
		{
			return os.str();
		}
		do
		{
			os << endl << " " << level + 2 << ":";
			++level;
		} while (outLevel(root, level, os));
		return os.str();
	}

	/* Output nodes at a given level */
	bool outLevel(Node* root, int level, ostringstream& os) const
	{
		if (root == nullptr)
		{
			return false;
		}
		if (level == 0)
		{
			os << " " << root->data;
			if ((root->left != nullptr) || (root->right != nullptr))
			{
				return true;
			}
			return false;
		}
		if ((level == 1) && !root->left && root->right)
		{
			os << " _";
		}
		bool left = outLevel(root->left, level - 1, os);
		bool right = outLevel(root->right, level - 1, os);
		if ((level == 1) && root->left && !root->right)
		{
			os << " _";
		}
		return left || right;
	}

	/** Return true if node added to BST, else false */
	bool addNode(const T& dataToAdd)
	{
		if (root == nullptr)
		{
			Node * node = new Node(dataToAdd);
			cout << endl << "ADDED " << dataToAdd << " at ROOT: " << root << endl;
			root = node;
			return true;
		}
		else if (insert(root, dataToAdd))
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

	bool insert(Node* &n, const T& dataToAdd)
	{
		if (n == nullptr)
		{
			Node* node = new Node(dataToAdd);
			cout << endl << "ADDED " << dataToAdd << " at ROOT: " << root << endl;
			n = node;
			return true;
		}
		else if (dataToAdd == n->data)
		{
			return false;
		}
		else if (dataToAdd < n->data)
		{
			return insert(n->left, dataToAdd);
		}
		else if (dataToAdd > n->data)
		{
			return insert(n->right, dataToAdd);
		}
		else
		{
			return false;
		}
	}

	bool find(const T& target) const
	{
		return findR(root, target);
	}

	bool findR(Node* localRoot, const T& target) const
	{
		if (localRoot == nullptr) return false;
		if (target < localRoot->data)
			return findR(localRoot->left, target);
		if (target > localRoot->data)
			return findR(localRoot->right, target);
		else
			return true;
	}

	/** Return true if node removed from BST, else false */
	bool removeNode(const T& dataToRemove)
	{
		return remove(root, dataToRemove);
	}

	bool remove(Node* &n, const T& dataToRemove)
	{
		if (n == nullptr)
		{
			return false;
		}
		else
		{
			if (dataToRemove < n->data)
			{
				return remove(n->left, dataToRemove);
			}
			else if (n->data < dataToRemove)
			{
				return remove(n->right, dataToRemove);
			}
			
			else //dataToRemove is found
			{
				Node * oldRoot = n;
				if (n->left == nullptr)
				{
					n = n->right;
				}
				else if (n->right == nullptr)
				{
					n = n->left;
				}
				else
				{
					replaceParent(oldRoot, oldRoot->left);
				}
				Node * temp = oldRoot;
				oldRoot = nullptr;
				delete temp;
				return true;

			}
		}
	}

	/* ReplaceParent function gets inorder predecessor and replaces the root */
	void replaceParent(Node* &oldRoot, Node* &localRoot)
	{
		if (localRoot->right != nullptr)
		{
			replaceParent(oldRoot, localRoot->right);
		}
		else
		{
			oldRoot->data = localRoot->data;
			oldRoot = localRoot;
			localRoot = localRoot->left;
		}
	}

	/** Return true if BST cleared of all nodes, else false */
	bool clearTree()
	{
		if (root == nullptr)
		{
			return true;
		}
		else
		{
			return clear(root);
		}
	}

	bool clear(Node* &n) 
	{ 
		if (n == nullptr)
		{
			return true;
		}
		clear(n->left);
		clear(n->right);

		Node * temp = n;
		n = nullptr; 
		delete temp;
		return true;
	}

	/* Override the insertion operator, inserts a BST string*/
	/*friend ostream& operator<< (ostream*os, const BST<T>& bst) const 
	{
		os << bst.toString();
		return os;
	}*/
	
	/*returns number of nodes in BST*/
	int size()
	{
		if (root == nullptr)
		{
			return 0;
		}
		else
		{
			return sizeN(root);
		}
	}

	/*recursive part of int size() function*/
	int sizeN(Node * &n)
	{
		if (n == nullptr)
		{
			return 0;
		}
		else
		{
			return (sizeN(n->left) + 1 + sizeN(n->right));
		}
	}

	/* delete all nodes in tree*/
	void deleteTree(Node* &n)
	{
		if (n == nullptr)
		{
			return;
		}
		deleteTree(n->left);
		deleteTree(n->right);

		Node * temp = n;
		n = nullptr;
		delete temp;
	}
};
#endif //BST_H


