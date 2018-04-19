#pragma once
#include <pthread.h>
static pthread_rwlock_t plock;

/// TODO: complete this implementation of a thread-safe (concurrent) sorted
/// linked list of integers, which should use readers/writer locking.
class rwlist
{
	/// a node consists of a value and a pointer to another node
	struct Node
	{
		int value;
		Node* next;
	};
	/// The head of the list is referenced by this pointer
	Node* head;
public:
	rwlist(int)	: head(NULL)
	{
		pthread_rwlock_init(&plock, NULL);
	}
	/// insert *key* into the linked list if it doesn't already exist; return
	/// true if the key was added successfully.
	bool insert(int key)
	{
		pthread_rwlock_wrlock(&plock);
		if(head->value == key) 
		{
			head->next->value = key; 
			pthread_rwlock_unlock(&plock);					
			return false;
		}
		struct Node* temp = head->next;
		while(temp != NULL)
		{
			if(temp->value == key)
			{
				pthread_rwlock_unlock(&plock);						
				return false;
			}
			temp = temp->next;
		}
		if(temp == NULL)
		{
			temp->value = key;
			pthread_rwlock_unlock(&plock);					
			return true;
		}
		pthread_rwlock_unlock(&plock);		
		return false;		
	}
	/// remove *key* from the list if it was present; return true if the key
	/// was removed successfully.
	bool remove(int key)
	{
		pthread_rwlock_wrlock(&plock);		
		if(head->value == key)
		{
			head->value = 0;
			pthread_rwlock_unlock(&plock);					
			return true;
		}
		struct Node* temp = head->next;
		while(temp != NULL)
		{
			if(temp->value == key)
			{
				temp->value = 0;
				pthread_rwlock_unlock(&plock);						
				return true;
			}
			temp = temp->next;
		}
		pthread_rwlock_unlock(&plock);		
		return false;
	}
	/// return true if *key* is present in the list, false otherwise
	bool lookup(int key) const
	{
		pthread_rwlock_rdlock(&plock);		
		if(head->value == key)
		{
			pthread_rwlock_unlock(&plock);					
			return true;
		}
		struct Node* temp = head;
		while(temp != NULL)
		{
			if(temp->value == key)
			{
				pthread_rwlock_unlock(&plock);						
				return true;
			}
			temp = temp->next;
		}
		pthread_rwlock_unlock(&plock);		
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

