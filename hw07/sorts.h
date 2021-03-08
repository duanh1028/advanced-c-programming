#ifndef SORT_H
#define SORT_H
#include<stdbool.h>
#include<stdlib.h>
//#include<assert.h>


typedef struct ListNode {
	int	value;
	struct ListNode* next;
} ListNode;

typedef struct List {
	struct ListNode* head;
	struct ListNode* tail;
	int       size;
} List;


typedef struct _BSTNode {
	int value;
	struct _BSTNode* right;
	struct _BSTNode* left;
} BSTNode;

typedef struct BST {
	BSTNode* root;
	int size;	
} BST;



void merge_sort_array(int* array, size_t size);
void tree_sort_array(int* array, size_t size);
void quick_sort_array(int* array, size_t size);
List create_list(const int* array, int size);
void merge_sort_list(List* list);
void empty_list(List* a_list);
void _helper_split(List*, ListNode**, ListNode**);
ListNode* _helper_sort(ListNode* first, ListNode* second);
ListNode* _helper_exchange(ListNode*);
BST create_bst(const int* array, int size);
void empty_bst(BST* bst);
void _helper_insert(BSTNode**, int);
BSTNode* _helper_create_node(int);
void _helper_traversal(BSTNode*, int*, int*);
#endif
