#include "clist.h"

#pragma once
#include<vector>

/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.
class chash
{
	/// The bucket list
	const std::vector<clist> buckets;

public:
	chash(unsigned _buckets)
	{
		numbuck = _buckets;
		parray = new clist[200];
	}

	/// insert *key* into the appropriate linked list if it doesn't already
	/// exist; return true if the key was added successfully.
	bool insert(int key)
	{
		int bucket = key % numbuck;
		return parray[bucket].insert(key);
	}
	/// remove *key* from the appropriate list if it was present; return true
	/// if the key was removed successfully.
	bool remove(int key)
	{
		int bucket = key % numbuck;
		return parray[bucket].remove(key);
	}
	/// return true if *key* is present in the appropriate list, false
	/// otherwise
	bool lookup(int key) const
	{
		int bucket = key % numbuck;
		return parray[bucket].lookup(key);
	}

	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.

	//This refers to the number of buckets not the total number of elements.
	size_t getSize() const
	{
		return numbuck;
	}
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

