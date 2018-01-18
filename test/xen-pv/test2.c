#include "numa.h"
#include "numaif.h"
#include <sys/mman.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define err(x) perror(x),exit(1)

int main(void)
{
	int i, j, err = 0;
	int max_node = numa_max_node();
	int num_possible_nodes = numa_num_possible_nodes();
	int max_possible_node = numa_max_possible_node();

	struct bitmask *mask0 = numa_allocate_cpumask();
	struct bitmask *mask1 = numa_allocate_cpumask();

	int avail = numa_available();
	int configured_nodes = numa_num_configured_nodes();

	numa_node_to_cpus(0, mask0);
	numa_node_to_cpus(1, mask1);

	printf("numa available? %d\n", avail);
	printf("configured nodes: %d\n", configured_nodes);

	printf("max node:%d possible nodes:%d max possible node:%d\n", 
			max_node, num_possible_nodes, max_possible_node);

	printf("cpus for node 0: %lx, weight: %d\n", 
				*(mask0->maskp), 
				numa_bitmask_weight(mask0));
	printf("cpus for node 1: %lx, weight: %d\n", 
				*(mask1->maskp),
				numa_bitmask_weight(mask1));

	printf("numa_all_nodes: %lu\n", *((unsigned long *)&numa_all_nodes));
	printf("numa_all_nodes_ptr: %lx, weight: %d\n", 
			*(numa_all_nodes_ptr->maskp), 
			numa_bitmask_weight(numa_all_nodes_ptr));
	printf("numa_nodes_ptr: %lx, weight: %d\n", 
			*(numa_nodes_ptr->maskp),
			numa_bitmask_weight(numa_nodes_ptr));

	for (i = 0; i <= max_node; i++)
		for (j = 0; j < max_node; j++)
			printf("distance(%d, %d) = %d\n", 
				i, j, numa_distance(i, j));

	return err;
}
