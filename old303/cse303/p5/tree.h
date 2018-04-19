#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <thread>       
#include <mutex>   
#include <string> 
#include <stack>

/// TODO: complete this implementation of a thread-safe (concurrent) AVL
///       tree of integers, implemented as a set of Node objects.
///       In addition, the API now allows for multiple insertions on each
///       operation.
///       Less than goes to the left. Greater than goes to the right.
class tree
{
//This is for testing purposes. Do not access your Node directly.
public:
	struct Node
	{
	public:
		int value;
		Node* left;
		Node* right;
		int height;
		int idx; 

		Node(int d) { 
			value = d;
			left = NULL;
			right = NULL;
			height = 0;
		}
		
	};
	Node* head;

public:
	tree(int):head(NULL){}

	mutable std::mutex mtx;

	void updateNodeHeight(Node *&leaf){
		int right_height = 0;
		int left_height = 0;
		int max;

		if (leaf->right != NULL ){
			right_height = leaf->right->height;
		}

		if (leaf->left != NULL){
			left_height = leaf->left->height;
		}

		max = (left_height > right_height) ? left_height : right_height;
      leaf->height = max + 1;
	}

	int getHeightDiff(Node *leaf){
      int right_height = 0;
      int left_height = 0;
        
      if (leaf->right != NULL) {
         right_height = leaf->right->height;
      }

      if (leaf->left != NULL) {
         left_height =  leaf->left->height;
      }
      return left_height - right_height;
   }

	Node* leftRotate(Node *&leaf){
      Node* temp = leaf->right;
      leaf->right = temp->left;
      temp->left = leaf;
      updateNodeHeight(leaf);
      return temp;
   }
 
   Node* rightRotate(Node *&leaf){
      Node* temp = leaf->left;
      leaf->left = temp->right;
      temp->right = leaf;
      updateNodeHeight(leaf);
      return temp;
   }

   Node* rightLeftRotate(Node *&leaf){
      Node* temp = leaf->right;
      leaf->right = rightRotate(temp);
      return leftRotate(leaf);
   }
 
   Node* leftRightRotate(Node *&leaf){
      Node* temp = leaf->left;
      leaf->left = leftRotate(temp);
      return rightRotate(leaf);
   }

   Node* rebalanceTree(Node *&leaf){
      int height_diff = getHeightDiff(leaf);
      if (height_diff > 1){
         if (getHeightDiff(leaf->left) > 0) {
            leaf = rightRotate(leaf);
         } else {
            leaf = leftRightRotate(leaf);
         }
      } else if(height_diff < -1) {
         if (getHeightDiff(leaf->right) < 0) {
            leaf = leftRotate(leaf);
         } else {
            leaf = rightLeftRotate(leaf);
         }
      }
      return leaf;
   }

   Node* findMinNode(Node* leaf) {
	   return leaf->left ? findMinNode(leaf->left) : leaf;
	}

	Node* removeMinNode(Node* leaf) {
	   if(leaf->left == 0) { 
	      return leaf->right;
      }
	   leaf->left = removeMinNode(leaf->left);
	   return rebalanceTree(leaf);
	}

	/// insert /num/ values from /data/ array into the tree, and return the
	/// success/failure of each insert in /results/ array.
	void insert(int* data, bool* results, int num) {
		std::lock_guard<std::mutex> lock(mtx);
		for(int i = 0; i < num; i++) {
			results[i] = insert_helper(data[i], NULL);
		}
	}

	bool insert_helper(int d, Node *leaf){
      if (leaf == NULL){
         leaf = new Node(d);
         updateNodeHeight(leaf);
      }
      else {
         if (d < leaf->value){
            insert_helper(d, leaf->left);
            updateNodeHeight(leaf);
            rebalanceTree(leaf);
         }
         else {
            insert_helper(d, leaf->right);
            updateNodeHeight(leaf);
            rebalanceTree(leaf);
         }
      }
      return true;
   }

	/// remove *data* from the list if it was present; return true if the data
	/// was removed successfully.
	void remove(int* data, bool* results, int num) {
		std::lock_guard<std::mutex> lock(mtx);
		for(int i = 0; i < num; i++) {
		   results[i] = (remove_helper(head, data[i]) != NULL);			
		}
	}

	Node* remove_helper(Node* leaf, int i) {
		Node* left_child;
		Node* right_child;
		Node* min_node;

	   if(!leaf) {
	   	return NULL;
      } 

      if(i < leaf->value){
	      leaf->left = remove_helper(leaf->left, i);
      } else if(i > leaf->value) {
	      leaf->right = remove_helper(leaf->right, i);	
      } else {
	      left_child = leaf->left;
	      right_child = leaf->right;
	      delete leaf;
	      if(!right_child) {
	         return left_child;
        	} 
	      min_node = findMinNode(leaf);
	      min_node->right = removeMinNode(leaf);
	      min_node->left = left_child;
	      return rebalanceTree(min_node);
	   }
	   return rebalanceTree(leaf);
	}

	/// return true if *data* is present in the list, false otherwise
	void lookup(int* data, bool* results, int num) const {
		std::lock_guard<std::mutex> lock(mtx);
		for(int i = 0; i < num; i++) {		
			results[i] = lookup_helper(data[i], head);
		}		
	} 

	bool lookup_helper(int s, Node* tree) const{
		if(tree == NULL) {
	         return false;
	    } else if(s < tree->value) {
	         return lookup_helper(s, tree->left);
	    } else if(tree->value < s) {
	         return lookup_helper(s, tree->right);
	    } 
	    return true;
	}

	//The following are not tested by the given tester but are required for grading
	//No locks are required for these.

	//Total number of elements in the tree
	size_t getSize() const {
		size_t out = (size_t)getSize_helper(head);
		return out;
	}

	int getSize_helper(Node *leaf) const {
		if(leaf == NULL) { 
	      return 0;
	   } else { 
	      return getSize_helper(leaf->left) + getSize_helper(leaf->right) + 1;
	   }
	}

	int getElement(size_t idx) const {
		return getElement(idx, head);
	}


	//These functions need to exist, they do not need to do anyting
	size_t getBucketSize() const {
		return 0;
	}

	int getElement(size_t bucket, size_t idx) const {
		return 0;
	}

private:
	//Returns the idx'th element from the tree assuming an inorder traversal.
	int getElement(size_t idx, Node* at) const {
		int count = 0;
		std::stack<Node*> stack;

		while(stack.size() != 0 && at != NULL){
			if(at != NULL){
				stack.push(at);
				at = at->left;
			} else {
				at = stack.top();
				stack.pop();
				if(count == idx){
					return at->value;
				}
				count++;
				at = at->right;
			}
		}

	return 0;
	}	
};

