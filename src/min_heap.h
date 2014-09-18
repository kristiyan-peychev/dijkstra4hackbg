#ifndef MIN_HEAP_RFWYZG10

#define MIN_HEAP_RFWYZG10

#include "graph.h"

typedef struct _node_dist { 	/* I'll be using this for the dijkstra implementation */
	node *np; 		/* more specifically - for the min priority queue with */
	unsigned long int distance; /* which I'm going to impement it with */
} node_dist; 

/* The following min-heap will use the distance instance in the node_dist structure to */
/* implement the min priority queue property */

typedef struct _min_heap {
	node_dist *cont; /* The container array */
	unsigned allocated_sz; /* The container array allocated size */
	unsigned size; /* The number of elements the container array has */
} min_heap;

min_heap *min_heap_init(void); /* Constructor */
char min_heap_insert(min_heap *, node_dist); /* Insert into the heap like this */
node_dist min_heap_pull(min_heap *); /* Pull the min distance element from the heap */
void min_heap_build(min_heap *, unsigned); /* This will be called to perserve the min-heap property */
void min_heapify(min_heap *); /* Not as it seems */
void min_heap_destroy(min_heap *); /* Destructor */

#endif /* end of include guard: MIN_HEAP_RFWYZG10 */
