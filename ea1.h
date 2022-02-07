//#pragma once

#include "ea1.c"

struct linked_node;

struct linked_node* generate_random_list(int size, float bound);

float get_ith_value(struct linked_node* head, int ith);

void set_ith_value(struct linked_node* head, int ith, float new_value);

void update_coords(struct linked_node* xs, struct linked_node* ys, struct linked_node* zs, 
				   struct linked_node* vx, struct linked_node* vy, struct linked_node* vz, int size);

float list_sum(head);

