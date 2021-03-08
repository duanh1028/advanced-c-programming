#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

typedef struct array_info {
	int* array;
	int start_index;
	int end_index;
	int num_to_change;
} array_info;

void* worker(void* value) {
	array_info* args= value;
	int* array = args -> array;
	int start_index = args -> start_index;
	int end_index = args -> end_index;
	int num_to_change = args -> num_to_change;
	
	for(int i = start_index; i < end_index + 1; i++) {
		array[i] = num_to_change;
	}
	return NULL;
}


bool zero_array(int* array, int array_length, int num_threads, const char** a_error) {
	/* Given an array, set every element to 0 using multiple threads.
	 *
	 * - If successful, return true and, if a_error != NULL, set *a_error = NULL.
	 *
	 * - In case of any failure, return false and, if a_error != NULL,
	 *   set *a_error to the address of an error message on the heap.
	 *   The caller will be responsible for freeing it.
	 */
	pthread_t* threads = malloc(num_threads * sizeof(*threads));
	array_info* info = malloc(sizeof(*info) * num_threads);

	for(int i = 0; i < num_threads; i++) {
		info[i] = (array_info) {
			.array = array,
			.start_index = i * array_length / num_threads,
			.end_index = (i + 1) * array_length / num_threads,
			.num_to_change = 0,
		};
		pthread_create(&threads[i], NULL, worker, &info[i]);
	}
	for(int i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}
	free(threads);
	free(info);	
	return true;
}

int main(int argc, char* argv[]) {
	int num_threads = 4;

	int array[16] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
	int array_length = sizeof(array)/sizeof(*array);

	for(int i=0; i<array_length; i++) {
		assert(array[i] == 2);
	}

	const char* error = NULL;
	bool did_succeed = zero_array(array, array_length, num_threads, &error);
	if(did_succeed) {
		for(int i=0; i<array_length; i++) {
			assert(array[i] == 0);
		}
		return EXIT_SUCCESS;
	}
	else {
		fprintf(stderr, "%s\n", error);
		return EXIT_FAILURE;
	}
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
