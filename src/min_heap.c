#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"

inline node_dist node_dist_init(node *np, unsigned long int dist) 
{
	return (node_dist) {np, dist};/* So hardcore */
}

min_heap *min_heap_init(void) 
{
	min_heap *ret = (min_heap *) malloc(1 * sizeof(min_heap));
	ret->allocated_sz = 4; /* Default size will be four */
	ret->size = 0; /* We're starting to count at One */
	ret->cont = (node_dist *) malloc(ret->allocated_sz * sizeof(node_dist));
return ret;
}

void min_heap_destroy(min_heap *target) 
{
	free(target->cont);
	free(target);
}

char min_heap_insert(min_heap *target, node_dist victim) 
{ /* Insertion will work in Theta(lg n) time */
	if (target->allocated_sz == target->size) { /* Doubling the array size */
		target->cont = (node_dist *) realloc(target->cont, target->allocated_sz * 2 * sizeof(node_dist));
		if (target->cont == NULL)
			return 0; /* u wot m8? */
		target->allocated_sz *= 2;
	}
	target->cont[target->size] = victim;
	target->size++;
	min_heap_build(target, target->size);
return 0;
}

static inline unsigned shit(unsigned i) {
	return i <= 0 ? 0 : i - 1 ;
}

/*The following function shall be the one responsible for perserving the min-heap property.*/
void min_heap_build(min_heap *target, unsigned i) 
{ /* i for index */ /* This is really bad, but it works in Theta(lg n) */
	node_dist tmp;
	/*printf("WOO %u:: [%u](%d) - [%u](%d)\n", i, shit(i), target->cont[shit(i)], shit(i/2), target->cont[shit(i/2)]);*/
	if (shit(i) == 0) {
		return;
	} else if ((target->cont[shit(i)]).distance < (target->cont[shit(i/2)]).distance) {
		tmp = target->cont[shit(i)];
		target->cont[shit(i)] = target->cont[shit(i/2)];
		target->cont[shit(i/2)] = tmp;
	}
	min_heap_build(target, i/2);
}

void min_heapify(min_heap *target) 
{ /* I'm going to need this. */
	unsigned i = target->size/2;
	for (; i > 0; i--) 
		min_heap_build(target, i);
}

node_dist min_heap_pull(min_heap *target) 
{ /* I have no idea if this is supposed to work like this, but whatever */
	node_dist ret = *(target->cont);
	/*int i;*/
	target->cont++;
	min_heapify(target);
	target->size--;
return ret;
}

#ifdef __TEST_HEAP__
int main(int argc, const char *argv[]) {
	min_heap *f = min_heap_init();
	min_heap_insert(f, 1);
	min_heap_insert(f, 0);
	min_heap_insert(f, -1);
	min_heap_insert(f, -3);
	min_heap_insert(f, -3);
	min_heap_insert(f, 3);
	min_heap_insert(f, -19);
	int i = 0;
	for (i = 0; i < f->size; i++) {
		printf("%d; ", f->cont[i]);
	}
	printf("--------%d\n", f->size);
	while (f->size != 0) {
		printf("%ld  ", min_heap_pull(f));
	}
	printf("%d\n", i);
return 0;
}
#endif

