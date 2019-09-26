#ifndef HASH_MAP_H
#define HASH_MAP_H
#include "HashMapInterface.h"
#include <utility>
#include <cmath>

using namespace std;

template<typename K, typename V>
class HashMap : public HashMapInterface<K, V>
{
private:

	pair<K, V>** myArray;

	/** The number of items currently in the map */
	size_t elementCount = 0;

public:

	/** Construct an empty hash_map. */
	HashMap()
	{
		myArray = new pair<K, V>* [DEFAULT_MAP_HASH_TABLE_SIZE];
		for (size_t i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++)
		{
			myArray[i] = nullptr;
		}
		elementCount = 0;
	}

	~HashMap() 
	{
		for (int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++)
		{
			delete myArray[i];
		}
		delete[] myArray;
	}

	/*Returns a hash value for a specified key*/
	long long hashFunction(string key);
	
	/** Read/write index access operaztor.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	V& operator[](const K& key);

	/** @return: the number of elements that matchthe key in the Map. */
	virtual size_t count(const K& key) { return -1; }

	/** Removes all items from the Map. */
	virtual void clear() { delete[] myArray; }

	/** @return: number of Key-Value pairs stored in the Map. */
	size_t size() const { return elementCount; }

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	size_t max_size() const { return DEFAULT_MAP_HASH_TABLE_SIZE; }

	/** @return: string representation of Key-Value pairs in Map. */
	std::string toString() const;

};

#endif //HASH_MAP_H

template<typename K, typename V>
inline long long HashMap<K, V>::hashFunction(string key)
{
	long long hash = 0;
	for (size_t i = 0; i < key.size(); i++)
	{
		hash = hash + (key[i] * (long long)pow(HASH_CONSTANT, (key.size() - (i + 1))));
	}
	//cout << "KEY: " << key << " has " <<"HASH VALUE: " << hash % DEFAULT_MAP_HASH_TABLE_SIZE;
	return hash % DEFAULT_MAP_HASH_TABLE_SIZE;
}

template<typename K, typename V>
inline V & HashMap<K, V>::operator[](const K & key)
{
	long long hash = 0;
	int k = 1;
	long long hashIndex = 0;
	hash = hashFunction(key);
	hashIndex = hash;
	//cout << hashIndex << endl << endl;
	while (myArray[hashIndex] != nullptr)
	{
		if (myArray[hashIndex]->first == key)
		{
			/*cout << "COLLISION:  " << endl;
			cout << "Key: " << key << " " << hash << endl;
			cout << "in Array: " << myArray[hashIndex]->first << " " << hashIndex << endl << endl;*/
			return myArray[hashIndex]->second;
		}
		else 
		{
			
			hashIndex = (hashIndex + k);
			hashIndex = hashIndex % DEFAULT_MAP_HASH_TABLE_SIZE;
			k += 2;
		}
	}
	//cout << hashIndex << endl << endl;
	myArray[hashIndex] = new pair<K, V>(key, V());
	elementCount++;
	return myArray[hashIndex]->second;
}

template<typename K, typename V>
inline std::string HashMap<K, V>::toString() const
{
	ostringstream os;
	os << elementCount << "/" << DEFAULT_MAP_HASH_TABLE_SIZE << endl;
	for (unsigned int i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++)
	{
		if (myArray[i] != nullptr)
		{
			os << "[" << i << ":" << myArray[i]->first << "->" << myArray[i]->second << "]" << endl;
		}
	}
	os << endl;
	return os.str();
}
