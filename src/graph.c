#include "graph.h"
#include <stdio.h>

edge edge_init(long int label, long int weight) 
{
	return (edge) {label, weight}; /* Just return the label of the next node and a weight value */
}

long int edge_weight(edge target) 
{
	return target.weight; 
}

long int edge_next(edge target) 
{
	return target.next;
}

/* Nodes */

node *node_init(long int label) 
{
	node *ret = (node *) malloc(1 * sizeof(node));
	ret->label = label;
	ret->edge_sz = 4; /* Initializing the edges array to four, because I doubt anyone will use more */
	ret->edges = (edge *) malloc(ret->edge_sz * sizeof(edge));
	ret->count = ret->itr_c = 0;
return ret;
}

/*inline */void node_reset_itr(node *target) 
{
	target->itr_c = 0;
}

edge node_itr_next(node *target) /* Will return an edge with label -1 and */
{ 				/* a weight of -1 as an error */
	if (target->itr_c == target->count) 
		return (edge) {-1l, -1l};
return *(target->edges + target->itr_c++);
}

char rl_node_add_edge(node *target, edge victim) 
{
	edge *buff/*, buf*/;
	unsigned cc = 0;
	/*fprintf(stderr, "Call %d\n", target->edge_sz - target->count);*/
	if (target->edge_sz == target->count) { /* Doubling the array size */
		/*printf("YEA! %d\n", target->edge_sz);*/
		buff = (edge *) malloc((target->edge_sz * 2) * sizeof(edge));
		if (buff == NULL)
			return 1; /* Holy crap, how can this even happen */
		while (cc < target->count) {
			*(buff + cc) = *(target->edges + cc);
			cc++;
		}
		free(target->edges);
		target->edges = buff;
		target->edge_sz *= 2; /* *= 2 */
		/*printf("Doubled.\n");*/
	}
	*(target->edges + target->count) = victim; 
	target->count++;
return 0;
}

char node_add_edge(node *target, node *victim, long int weight) 
{ /* FIXME more efficient alg for multigraph checks */
	edge f, g;
	#ifndef _MULTIGRAPHS_
	for (node_reset_itr(target), f = node_itr_next(target); f.next != -1 && f.weight != -1; f = node_itr_next(target)) {
		for(node_reset_itr(victim), g = node_itr_next(victim); g.next != -1 && g.weight != -1; g = node_itr_next(target)) {
			if (f.next == g.next) 	/* Since we're not in a multigraph, we can't have more than one edge */
				return 0;	/* between each two nodes. We're just ignoring the new weight. */
		}
	}
	#endif
	f = edge_init(target->label, weight);
	g = edge_init(victim->label, weight);
	#ifndef _DIRECTED_GRAPHS_
	return rl_node_add_edge(target, g) & rl_node_add_edge(victim, f);
	#else
	return rl_node_add_edge(target, g);
	#endif
}

/*inline */unsigned node_edges(node *target) 
{
	return target->count;
}

node *node_copy(node *target) 
{
	node *ret = node_init(target->label);
	unsigned cc = 0;
	ret->edges = (edge *) malloc(target->edge_sz * sizeof(edge));
	while (cc < target->count) {
		*(ret->edges + cc) = *(target->edges + cc);
		cc++;
	}
	ret->edge_sz = target->edge_sz;
	ret->count = target->count;
	ret->itr_c = target->itr_c;
return ret;
}

void node_destroy(node *target)
{ /* Freeing the edges array is the main reason you should use this */
	free(target->edges);
	free(target);
}

/* At last - the graph */

graph *graph_init(void) 
{
	graph *ret = (graph *) malloc(1 * sizeof(graph));
	ret->nodes_sz = 4; /* Defaulting to a four nodes array */
	ret->nodes = (node **) malloc(ret->nodes_sz * sizeof(node *));
	ret->count = ret->itr_c = 0;
return ret;
}

/*inline */void graph_reset_itr(graph *target) 
{ /* Can turn into a macro */
	target->itr_c = 0; /* Just setting the counter to 0 */
}

node *graph_itr_next(graph *target) 
{ /* Can turn into a macro */
	if (target->itr_c >= target->count) 
		return NULL;
return *(target->nodes + target->itr_c++);
}

void graph_add_node(graph *target, node *victim) 
{
	node /***nbuf,*/ *buf;
	unsigned cb0 = 0;
	if (target->count == target->nodes_sz) { /* Doubling the array size | And don't ask me why I don't use realloc- */ 
		#if 0
		nbuf = (node **) malloc((target->nodes_sz * 2) * sizeof(node *)); /* I have no idea myself. */
		for (graph_reset_itr(target), buf = graph_itr_next(target); (buf = graph_itr_next(target)); cb0++) {
			*(nbuf + cb0) = node_copy(buf);
			node_destroy(buf); /* Calling the destructor for each node, otherwise we will leak memory */
		}
		free(target->nodes);
		target->nodes = nbuf;
		target->nodes_sz *= 2; /* *= 2 */
		#endif
		target->nodes = (node **) realloc(target->nodes, target->nodes_sz * 2 * sizeof(node *));
		target->nodes_sz *= 2;
	}
	for (graph_reset_itr(target), buf = graph_itr_next(target), cb0 = 0; (buf = graph_itr_next(target)) != NULL; cb0++) {
		/* fprintf(stderr, "%d - %d\n", buf->label, victim->label); */
		if (buf->label == victim->label)  /* Since we identify our nodes by their label, this is a problem */
			return;
	}
	cb0 = 0;
	/*fprintf(stderr, "TT: %d\n", target->count);*/
	while (cb0 < target->count - 1 && (target->count > 0)) {
		buf = *(target->nodes + cb0);
		if (buf != NULL && buf->label == victim->label)
			return;
		cb0++;
	}
	*(target->nodes + target->count++) = node_copy(victim);
}

unsigned graph_node_c(graph *target) 
{ /* Node count */
	return target->count;
}

void graph_destroy(graph *target) 
{ /* Destructor */
	node *buf;
	for (graph_reset_itr(target), buf = graph_itr_next(target); (buf = graph_itr_next(target));) 
		node_destroy(buf);
	/*fprintf(stderr, "%d\n", 5);*/
	free(target->nodes);
}

graph *graph_copy(graph *target) 
{ /* Use this instead of = */
	graph *ret = graph_init();
	unsigned cc = 0;
	ret->nodes_sz = target->nodes_sz;
	ret->itr_c = target->itr_c;
	ret->count = target->count;
	ret->nodes = (node **) malloc(ret->nodes_sz * sizeof(node *));
	while (cc < target->count) {
		*(ret->nodes + cc) = node_copy(*(target->nodes + cc));
		cc++;
	}
return ret;
}

#ifdef _TEST_GRAPH_

int main(int argc, const char *argv[]) {
	edge f = edge_init(1, 1);
	node *n[50];
	graph *g, *g1;
	int i, j;
	for (i = 0; i <= 20; i++) {
		n[i] = node_init(i);
		n[20 - i] = node_init(20 - i);
	}
	node_add_edge(*n, n[1], 13);
	node_add_edge(*n, n[5], 13);
	node_add_edge(*n, n[7], 13);
	node_add_edge(*n, n[8], 13);
	node_add_edge(*n, n[9], 13);
	fprintf(stderr, "adf\n");
	for (i = 0; i < 14; i++) {
		fprintf(stderr, "%d\n", i);
		node_add_edge(n[i], n[20 - i], i * i);
		node_add_edge(n[i], n[i + 5], i + 20);
	}
	fprintf(stderr, "SEX\n");
	for (i = 0; i < 20; i++) {
		for (node_reset_itr(n[i]), f = node_itr_next(n[i]); (edge_next(f) != -1l && edge_weight(f) != -1l); f = node_itr_next(n[i])) {
			j = f.next;
			printf("Edge from %d to %d with weight %d.\n", (n[i])->label, f.next, f.weight);
		}
	}
	for (i = 20; i < 40; i++) {
		n[i] = node_copy(n[i - 20]);
		fprintf(stderr, "%d\n", i);
	}
	g = graph_init();
	graph_add_node(g, *n);
	graph_add_node(g, *n);
	graph_add_node(g, *n);
	graph_add_node(g, *n);
	graph_add_node(g, *n);
	fprintf(stderr, "YES\n");
	for (i = 0; i < 19; i++) {
		fprintf(stderr, "%d\n", i);
		graph_add_node(g, n[i]);
	}
	graph_destroy(g);
return 0;
}

#endif

