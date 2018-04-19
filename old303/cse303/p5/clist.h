#pragma once
#include <mutex>
static std::mutex mewtex;

/// TODO: complete this implementation of a thread-safe (concurrent) sorted
/// linked list of integers
class clist
{
public:	
	/// a Node consists of a value and a pointer to another node
	struct Node
	{
		int value;
		Node* next;
	};
	/// The head of the list is referenced by this pointer
	Node* head;

	clist(int) : head(NULL)
	{
		head = new Node;
	}
	clist() : head(NULL) 
	{
		head = new Node;
	}
	~clist()
	{
		delete head;
	}
	/// insert *key* into the linked list if it doesn't already exist; return
	/// true if the key was added successfully.
	bool insert(int key)
	{
		std::lock_guard<std::mutex> lguard(mewtex);
		if(head == nullptr)
		{
			return false;
		}
		if(head->value == key) 
		{
			return false;
		}
		struct Node* temp = head->next;
		while(temp != NULL)
		{
			if(temp->value == key)
			{
				return false;
			}
			temp = temp->next;
		}
		if(temp == NULL)
		{
			Node* node = new Node;
			temp = node;
			node->value = key;
			return true;
		}
		return false;
	}
	/// remove *key* from the list if it was present; return true if the key
	/// was removed successfully.
	bool remove(int key)
	{
		std::lock_guard<std::mutex> lguard(mewtex);
		if(head == nullptr)
		{
			return false;
		}
		if(head->value == key)
		{
			head->value = 0;
			Node* temp = head;
			head = head->next;
			return true;
		}
		struct Node* temp = head->next;
		while(temp != NULL)
		{
			if(temp->value == key)
			{
				temp->value = temp->next->value;
				temp = temp->next;
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	/// return true if *key* is present in the list, false otherwise
	bool lookup(int key) const
	{
		std::lock_guard<std::mutex> lguard(mewtex);
		if(head == nullptr)
		{
			return false;
		}
		if(head->value == key)
		{
			return true;
		}
		struct Node* temp = head->next;
		while(temp != NULL)
		{
			if(temp->value == key)
			{
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.
	size_t getSize() const
	{
		size_t count = 0;
		struct Node* temp = head;
		while(temp != NULL)
		{
			count++;
			temp = temp->next;
		}
		return count;
	}
	int getElement(size_t idx) const
	{
		int count = 0;
		struct Node* temp = head;
		while(temp != NULL)
		{
			if(count == idx)
			{
				return temp->value;
			}
			count++;
			temp = temp->next;
		}
		return 0;
	}

	//These functions just need to exist, they do not need to do anything
	size_t getBucketSize(size_t bucket) const
	{
		return 0;
	}
	int getElement(size_t bucket, size_t idx) const
	{
		return 0;
	}
};

