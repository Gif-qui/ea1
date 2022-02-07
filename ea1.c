#pragma once
#include "ea1.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


struct linked_node {
	float value;
	struct node *next;
};

struct linked_node* generate_random_list(int size, float bound) {
	struct linked_node* head = NULL;
	head = malloc(sizeof(struct linked_node));
	
	float new_value = (float)rand()/(float)(RAND_MAX/bound);
	if ((rand()%2 == 0)){
		new_value = new_value * -1.0;
	}

	head->value = new_value;

	struct linked_node* curr_node = head;
	for (int i = 1; i <= size; ++i) {
		struct linked_node* new_node = NULL;
		new_node = malloc(sizeof(struct linked_node));
		float new_value = (float)rand()/(float)(RAND_MAX/bound);
		if ((rand()%2 == 0)){
			new_value = new_value * -1.0;
		}

		head->value = new_value;

		curr_node->next = new_node;

		curr_node = new_node;
	}
	return head;
};

float get_ith_value(struct linked_node* head, int ith) {
	if (ith == 0) {
		return head->value;
	} else {
		struct linked_node* curr_node = head;
		for (int i = 1; i <= ith; i++) {
			curr_node = curr_node->next;
		}
		return curr_node->value;
	}
};

void set_ith_value(struct linked_node* head, int ith, float new_value){
	if (ith == 0) {
		head->value = new_value;
	} else {
		struct linked_node* curr_node = head;
		for (int i = 1; i <= ith; i++) {
			curr_node = curr_node->next;
		}	
		curr_node->value = new_value;
	}
};

void update_coords(struct linked_node* xs, struct linked_node* ys, struct linked_node* zs, 
				   struct linked_node* vx, struct linked_node* vy, struct linked_node* vz, int size) {

	for (int i = 1; i <= size; i++) {
		float xsvx = get_ith_value(xs, i) + get_ith_value(vx, i);
		set_ith_value(xs, i, xsvx);

		float ysvy = get_ith_value(ys, i) + get_ith_value(vy, i);
		set_ith_value(ys, i, ysvy);

		float zsvz = get_ith_value(zs, i) + get_ith_value(vz, i);
		set_ith_value(zs, i, zsvz);
	}
};

float list_sum(struct linked_node* head) {
	float total = head->value;
	struct linked_node* curr_node = head;
	while (curr_node->next) {
		total += curr_node->value;
		curr_node = curr_node->next;
	}

	return total;
};


int main(int argc, char const *argv[]) {
	if (argc != 3) {
		printf("Improper command line\n");
	}
	else {
		int size = argv[1] - 0;
		int iters = argv[2] - 0;

		srand(size);

		struct linked_node* xs = NULL;
		struct linked_node* ys = NULL;
		struct linked_node* zs = NULL;
		struct linked_node* vx = NULL;
		struct linked_node* vy = NULL;
		struct linked_node* vz = NULL;

		xs = generate_random_list(size, 1000.0);
		ys = generate_random_list(size, 1000.0);
		zs = generate_random_list(size, 1000.0);
		vx = generate_random_list(size, 1.0);
		vy = generate_random_list(size, 1.0);
		vz = generate_random_list(size, 1.0);

		clock_t start = clock();
			for (int i = 1; i <= iters; i++) {
				update_coords(xs, ys, zs, vx, vy, vz, size);	
			}
		clock_t end = clock();
		double length = end - start;

		float chksum = list_sum(xs) + list_sum(ys) + list_sum(zs);
		double mean_time = 1000000 * length / (size * iters);

		printf("Mean time per coordinate: %f\n", mean_time);
		printf("Final checksum is: %f\n", chksum);
	}

	return 0;
};
