#pragma once
#include <mutex>
#include <iostream>

#include <sys/types.h>
#include <unistd.h>

/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.  In
///       this implementation, each list should have a "Sentinel" Node that
///       contains the lock, so we can't just reuse the clist implementation.
///       In addition, the API now allows for multiple keys on each
///       operation.
class shash2 {

	struct Node {
        int value;
        Node* next = NULL;
    };

    struct Sentinel {
        std::mutex mtx;
        Node* head = NULL;
    };

    int num_buckets;
    Sentinel **buckets;

public:

	shash2(unsigned _buckets) {
		buckets = (Sentinel**)malloc(sizeof(Sentinel*) * _buckets);
        num_buckets = _buckets;
        for (int i = 0; i < num_buckets; i++) {
            buckets[i] = new Sentinel();
        }
	}

	/// insert /num/ values from /keys/ array into the hash, and return the
	/// success/failure of each insert in /results/ array.
	void insert(int* keys, bool* results, int num) {
        bool found_node;
        Sentinel* sentinel_node;
        Node* head;
        Node* current_node;
        Node* temp_node;
        bool check;

		for (int i = 0; i < num; i++) {
           sentinel_node = buckets[keys[i] % num_buckets];
           std::lock_guard<std::mutex> lock(sentinel_node->mtx);

            if (sentinel_node->head == NULL) {
                sentinel_node->head = new Node();
                sentinel_node->head->value = keys[i];
                results[i] = true;
                continue;
            }

            head = sentinel_node->head;
            if (head->value == keys[i]) {
                results[i] = false;
                continue;
            } else if (head->value > keys[i]) {
                sentinel_node->head = new Node();
                sentinel_node->head->value = keys[i];
                sentinel_node->head->next = head;
                results[i] = true;
                continue;
            }

            current_node = head;
            found_node = false;
            check = false;
            while (current_node->next != NULL && found_node == false) {
                if (current_node->value == keys[i]) {
                    results[i] = false;
                    found_node = true;
                    check = true;
                    break;
                } else if (current_node->next->value > keys[i]) {
                    temp_node = new Node();
                    temp_node->value = keys[i];
                    temp_node->next = current_node->next;
                    current_node->next = temp_node;
                    results[i] = true;
                    found_node = true;
                }
                current_node = current_node->next;
            }

            if (found_node && check) {
               continue;
            }

            temp_node = new Node();
            temp_node->value = keys[i];
            current_node->next = temp_node;
            results[i] = true; 
        }
	}

	/// remove *key* from the list if it was present; return true if the key
	/// was removed successfully.
	void remove(int* keys, bool* results, int num) {
        Sentinel* sentinel_node;
        Node* temp_node;
        Node* current_node;

	    for (size_t i = 0; i < num; i++) {
            sentinel_node = buckets[keys[i] % num_buckets];
            std::lock_guard<std::mutex> lock(sentinel_node->mtx);

            if (sentinel_node->head == NULL) {
                results[i] = false;
                continue;
            } else if (sentinel_node->head->value == keys[i]) {
                temp_node = sentinel_node->head->next;
                delete sentinel_node->head;
                sentinel_node->head = temp_node;
                results[i] = true;
                continue;
            }

            current_node = sentinel_node->head;
            while (current_node->next != NULL) {
                if (current_node->next->value == keys[i]) {
                    temp_node = current_node->next->next;
                    delete current_node->next;
                    current_node->next = temp_node;
                    results[i] = true;
                    break;
                } else if (current_node->next->value < keys[i]) {
                    results[i] = false;
                }

                current_node = current_node->next;
            }

            if(results[i]){
               continue;
            }

            results[i] = false;
        }
	}
	/// return true if *key* is present in the list, false otherwise
	void lookup(int* keys, bool* results, int num) const {
        Sentinel* sentinel_node;
        Node* current_node;

		for (size_t i = 0; i < num; i++) {
            sentinel_node = buckets[keys[i] % num_buckets];
            std::lock_guard<std::mutex> lock(sentinel_node->mtx);

            if (sentinel_node->head == NULL) {
                results[i] = false;
                continue;
            } else if (sentinel_node->head->value == keys[i]) {
                results[i] = true;
                continue;
            }

            current_node = sentinel_node->head;
            while (current_node->next != NULL) {
                if (current_node->next->value == keys[i]) {
                    results[i] = true;
                    break;
                } else if (current_node->next->value < keys[i]) {
                    results[i] = false;            
                }
                current_node = current_node->next;
            }
            if(results[i]){
               continue;
            }

            results[i] = false;
        }
	}

	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.

	//This refers to the number of buckets not the total number of elements.
	size_t getSize() const {
		return num_buckets;
	}

	//This refers to the number of elements in a bucket, not the Sentinel Node.
	size_t getBucketSize() const {
		return sizeof(buckets)/sizeof(buckets[0]);
	}

	int getElement(size_t bucket, size_t idx) const {
		return buckets[bucket][idx].head->value;
	}

	//These functions just need to exist, they do not need to do anything
	int getElement(size_t idx) const {
		return 0;
	}
};

