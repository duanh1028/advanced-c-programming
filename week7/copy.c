
#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>

void merge_sort_array(int* array, size_t size) {
	List HEAD = NULL;
	HEAD = create_list(array, size);
	while(HEAD.tail != NULL) {
		printf("the value is %d\n", HEAD.tail -> value);
		HEAD.tail = HEAD.tail -> next; 
	}
//	merge_sort_list(HEAD);
	free(HEAD);
}

List create_list(const int* array, int size) {
	List head;
	ListNode* temp;
	head.tail = NULL;
	head.head = NULL;

	for(int i = 0; i < size; i++) {
		temp = malloc(sizeof(ListNode*));
		temp -> value = array[i];
		temp -> next = NULL;

		if(head.head == NULL) {
			head.head = temp;
			head.tail = head.head;
		}
		else {
		 //	head.tail -> next = temp;
		//	head.tail = temp;

			head.tail = temp;
			head.tail -> next = NULL;

	}
	head.size = size;
	return head;
}
/*
void merge_sort_list(list* a_list) {
	
}

void empty_list(list* a_list) {
	
}*/
