#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include"sorts.h"

int _helper_compfunc (const void *a, const void* b) {
	return(*(int*)a - *(int*)b);
}

void quick_sort_array(int* array, size_t size) {
	qsort((void*)array, size, sizeof(array[0]), _helper_compfunc);
}

void _helper_traversal(BSTNode* root, int* array, int* size) {
	if(root != NULL) {
		_helper_traversal(root -> left, array, size);
		array[(*size)++] = root -> value;
		_helper_traversal(root -> right, array, size);
	}
}

void tree_sort_array(int* array, size_t size) {
	BST bst = create_bst(array, size);
	int changdu = 0;
	_helper_traversal(bst.root, array, &changdu);
	empty_bst(&bst);
}



BST create_bst(const int* array, int size) {
	BST tree = {.root = NULL, .size = size};	
	for(int i = 0; i < size; i++) {
		_helper_insert(&tree.root, array[i]);
	}
	return tree;
}

BSTNode* _helper_create_node(int value){
		BSTNode* node = malloc(sizeof(BSTNode*));
		printf("it passed here\n");
		node -> value = value;
		node -> left = NULL;
		node -> right = NULL;
		return node;
}

void _helper_insert(BSTNode** a_root, int value){
	if(*a_root == NULL) {
		*a_root = _helper_create_node(value);
	}
	else if(value <= (*a_root) -> value) {
		_helper_insert(&(*a_root) -> left, value);
	}
	else {
		_helper_insert(&(*a_root) -> right, value);
	}	
}

void empty_bst(BST* bst) {
	if(bst -> root != NULL) {
		BST n1 = {.root = bst -> root -> left};
		empty_bst(&n1);
		BST n2 = {.root = bst -> root -> right};
		empty_bst(&n2);
		free(bst -> root);
		bst -> root = NULL;
		bst -> size = 0;
	}
}

void merge_sort_array(int* array, size_t size) {
	List list = create_list(array, size);
	merge_sort_list(&list);
	for(int i = 0; i < size; i++) {
		array[i] = list.head -> value;
		list.head = list.head -> next;
	}
	empty_list(&list);
}

List create_list(const int* array, int size) {
	List list1 = {.tail = NULL, .head = NULL, .size = size};

	for(int i = 0; i < size; i++) {
		ListNode* temp = malloc(sizeof(ListNode*));
		temp -> value = array[i];
		temp -> next = NULL;
		if(list1.head == NULL) {
			list1.head = temp;
			list1.tail = list1.head;
		}
		else {
			list1.tail -> next = temp;
		}
		list1.tail = temp;
	}
	return list1;
}

void merge_sort_list(List* list) {
	if((*list).size <= 1) {
		return;
	}
	List first_list = {.size = (*list).size / 2, .head = (*list).head, .tail = (*list).head};
	for(int i = 0; i < first_list.size - 1; i++) {
		first_list.tail = first_list.tail -> next;
	}

	List second_list = {.size = (*list).size - first_list.size, .head = first_list.tail -> next, .tail = (*list).tail};
	first_list.tail->next = NULL;
	
	merge_sort_list(&first_list);
	merge_sort_list(&second_list);

	(*list).head = _helper_sort(first_list.head, second_list.head);
}

ListNode* _helper_sort(ListNode* fhead, ListNode* shead) {
	ListNode* result;
	if (shead == NULL) {
		return fhead;
	}
	if (fhead == NULL) {
		return shead;
	}

	if(fhead -> value <= shead -> value) {
		result = fhead;
		result -> next = _helper_sort(fhead -> next, shead);
	}
	else {
		result = shead;
		result -> next = _helper_sort(fhead, shead -> next);
	}	
	return(result);
}

void _helper_split(List* list, ListNode** first_list, ListNode** second_list) {
	ListNode* fast;
	ListNode* slow;
	int size = 0;
	slow = (*list).head;
	fast = (*list).head -> next;

	while(fast != NULL) {
		size++;
		fast = fast -> next;
		if(fast != NULL) {
			slow = slow -> next;
			fast = fast -> next;
		}
	}
	*first_list = (*list).head;
	*second_list = slow -> next;
	slow -> next = NULL;
	(*list).size = size;
}

void empty_list(List* a_list) {
	if((*a_list).head == NULL) {
		return;
	}
	(*a_list).head = (*a_list).head -> next;
	free((*a_list).head);
	empty_list(a_list);
}
