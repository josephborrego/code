#pragma once

//**************GOING TO BE THE SAME AS rwlist.h *****************

/// TODO: complete this implementation of a thread-safe (concurrent) sorted
/// linked list of integers
class clist
{
	/// a Node consists of a value and a pointer to another node
	struct Node
	{
		int value;
		Node* next;
	};

	/// The head of the list is referenced by this pointer
	Node* head;

public:
	clist(int)
	: head(NULL)
	{}

	/// insert *key* into the linked list if it doesn't already exist; return
	/// true if the key was added successfully.
	bool insert(int key)
	{
		if(head == NULL)
		{
			head = (struct Node*)malloc(sizeof(struct Node));
			head->value = key;
			head->next = NULL;
			return false;
		}
		else
		{
			struct Node* temp = head;
			while(temp->next != NULL)
			{
				if(temp->value == key)
				{
					free(temp);
					return true;
				}
				temp = temp->next;
			}
			if(temp->next == NULL)
			{
				temp->value = key;
				return true;
			}
		}
		return false;
	}

	/// remove *key* from the list if it was present; return true if the key
	/// was removed successfully.
	bool remove(int key)
	{
		if(head->value == key)
		{
			head->value = 0;
			return true;
		}
		else
		{
			struct Node* temp = head;
			while(temp->next != NULL)
			{
				if(temp->value == key)
				{
					temp->value = 0;
					free(temp);
					return true;
				}
				temp = temp->next;
			}
			if(temp->next == NULL)
			{
				if(temp->value == key)
				{
					free(temp);
					return true;
				}
				else return false;
			}
		}
		return false;
	}

	/// return true if *key* is present in the list, false otherwise
	bool lookup(int key) const
	{
		if(head == NULL) return false;
		struct Node* temp = head;
		while(temp->next != NULL)
		{
			if(temp->value == key)
			{
				//i don't think i should free it
				free(temp);
				return true;
			}
			temp = temp->next;
		}
		if(temp->next == NULL)
		{
			if(temp->value == key)
			{
				free(temp);
				return true;
			}
		}
		free(temp);
		return false;
	}


	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.
	size_t getSize() const
	{
		size_t counter = 0;
		if(head == NULL) return counter;
		struct Node* temp = head;
		while(temp->next != NULL)
		{
			counter++;
			temp = temp->next;
		}
		if(temp->next == NULL)
		{
			counter++;
			free(temp);
			return counter;
		}
		return 0;
	}

	int getElement(size_t idx) const
	{
		struct Node* temp = head;
		while(temp->next != NULL)
		{
			if(temp->value == idx) return temp->value;
			temp = temp->next;
		}
		if(temp->next == NULL)
		{
			if(temp->value == idx) return temp->value;
			else return 0;
		}
		else return 0;
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
