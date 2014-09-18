#ifndef MIN_HEAP_RFWYZG10

#define MIN_HEAP_RFWYZG10

typedef struct _node_dist {
	node *np;
	unsigned long int distance;
} node_dist;

typedef struct _min_heap {
	node_dist *cont;
	unsigned allocated_sz;
	unsigned size;
} min_heap;

min_heap *min_heap_init(void);
char min_heap_insert(min_heap *, long int); 
long int min_heap_pull(min_heap *);
void min_heap_build(min_heap *, unsigned);
void min_heapify(min_heap *); /* Not as it seems */
void min_heap_destroy(min_heap *);

#endif /* end of include guard: MIN_HEAP_RFWYZG10 */
