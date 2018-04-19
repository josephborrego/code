#pragma once
#include "clist.h"
#include <mutex>
static std::mutex smutex;

/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.
class snode
{
public:
	std::mutex nodemutex;
	clist::Node* element;
	snode(): element(NULL)
	{
	}
};

class shash
{
public:
	snode** buckets;
	shash(unsigned _buckets)
	{
		numbuck = _buckets;
		parray = new clist[numbuck];
		int num = sizeof(snode) * _buckets; 
		buckets = new snode*[num];
		for(int i = 0; i < numbuck; ++i)
		{
			buckets[i] = new snode;	
		}
	}
	/// insert *key* into the appropriate linked list if it doesn't already
	/// exist; return true if the key was added successfully.
	bool insert(int key)
	{
		int bucket = key % numbuck;
		if(parray[bucket].getSize() == 0)
		{
			snode* sentNode = new snode();
			std::lock_guard<std::mutex> lguard(sentNode->nodemutex); 
			clist::Node *node = new clist::Node;
			node->value = key;
			node->next = nullptr;
		}
		return parray[bucket].insert(key);
	}
	/// remove *key* from the appropriate list if it was present; return true
	/// if the key was removed successfully.
	bool remove(int key)
	{
		int bucket = key % numbuck;
		auto node = buckets[bucket];
		while(node != nullptr)
		{
			std::lock_guard<std::mutex> lguard(node->nodemutex); 
			if(node->element->value == key)
			{
				node->element->value = 0;
				node->element = nullptr;
				while(node != nullptr && node->element->next)
				{
					node->element->value = (++node)->element->value;
					node->element = (++node)->element;
				}
				return true;
			}
			++node;
		} 
		return false;
	}
	/// return true if *key* is present in the appropriate list, false
	/// otherwise
	bool lookup(int key) const
	{
		int bucket = key % numbuck;
		auto node = buckets[bucket];
		while(node->element)
		{
			std::lock_guard<std::mutex> lguard(node->nodemutex); 			
			if(node->element->value == key)
			{
				return true;	
			}
			else
			{
				++node;
			}
		}
		return false;		
	}
	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.
	//This refers to the number of buckets not the total number of elements.
	size_t getSize() const
	{
		return numbuck;
	}
	//This refers to the number of elements in a bucket, not the sentinel node.
	size_t getBucketSize(size_t bucket) const
	{
		return parray[bucket].getSize();
	}
	int getElement(size_t bucket, size_t idx) const
	{
		return parray[bucket].getElement(idx);
	}
	//These functions just need to exist, they do not need to do anything
	int getElement(size_t idx) const
	{
		return 0;
	}
private:
	clist* parray;
	unsigned int numbuck; 
};




